#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "queue.h"


// Sabit Kırmızı (Zaman aşımı için)
#define COLOR_RED_FIXED "\033[31m"
#define RESET "\033[0m"

// ID'lere atanacak renk havuzu (Kırmızı hariç diğer tonları ağırlıklı kullanıyoruz ki karışmasın)
const char *ID_COLORS[] = {
    "\033[32m", // Yeşil
    "\033[33m", // Sarı
    "\033[34m", // Mavi
    "\033[35m", // Magenta
    "\033[36m", // Cyan
    "\033[92m", // Parlak Yeşil
    "\033[93m", // Parlak Sarı
    "\033[94m", // Parlak Mavi
    "\033[95m", // Parlak Magenta
    "\033[96m"  // Parlak Cyan
};
#define COLOR_COUNT 10

const char* GetColorById(char* idStr) {
    int id = atoi(idStr); 
    return ID_COLORS[id % COLOR_COUNT]; 
}

/* -------------------------------------------------------------------------- */

TaskData gorevler[50];
int gorevSayisi = 0;
int globalTime = 0;

// Öncelik seviyelerine göre ayrılmış kuyruklar
TaskData* queues[MAX_QUEUE_LEVEL][50];
int queue_lens[MAX_QUEUE_LEVEL] = {0};

// Kuyruğa yeni eleman ekleme
void Enqueue(int p, TaskData* t) {
    if (p >= MAX_QUEUE_LEVEL) p = MAX_QUEUE_LEVEL - 1;
    queues[p][queue_lens[p]] = t;
    queue_lens[p]++;
}

// Kuyruktan eleman çıkarma
TaskData* Dequeue(int p) {
    if (queue_lens[p] == 0) return NULL;
    TaskData* t = queues[p][0];
    for (int i = 0; i < queue_lens[p] - 1; i++) {
        queues[p][i] = queues[p][i+1];
    }
    queue_lens[p]--;
    return t;
}

// Kuyruktan belirli bir görevi silme
void RemoveTaskFromQueue(int p, TaskData* t) {
    int foundIndex = -1;
    for (int i = 0; i < queue_lens[p]; i++) {
        if (queues[p][i] == t) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1) {
        for (int i = foundIndex; i < queue_lens[p] - 1; i++) {
            queues[p][i] = queues[p][i+1];
        }
        queue_lens[p]--;
    }
}

// Dosya okuma
void DosyaOku(const char* dosyaAdi) {
    FILE *file = fopen(dosyaAdi, "r");
    if (file == NULL) { printf("HATA: Dosya yok!\n"); exit(1); }
    char line[100];
    int idCounter = 0;
    while (fgets(line, sizeof(line), file)) {
        int arrival, prio, burst;
        if (sscanf(line, "%d, %d, %d", &arrival, &prio, &burst) == 3) {
            sprintf(gorevler[gorevSayisi].id, "%04d", idCounter++);
            gorevler[gorevSayisi].arrivalTime = arrival;
            gorevler[gorevSayisi].priority = prio;
            gorevler[gorevSayisi].burstTime = burst;
            gorevler[gorevSayisi].remainingTime = burst;
            gorevler[gorevSayisi].hasStarted = 0;
            gorevler[gorevSayisi].startTime = -1;
            gorevler[gorevSayisi].isRunning = 0;
            gorevSayisi++;
        }
    }
    fclose(file);
}

// Ana simülasyon
void SimulationTask(void *pvParameters) {
    (void) pvParameters;
    printf("Simulasyon Basliyor...\n");

    TaskData* currentTask = NULL;
    TaskData* previousTask = NULL;

    for(;;) {
        // Yeni gelenleri kuyruğa ekle
        for(int i=0; i<gorevSayisi; i++) {
            if (gorevler[i].arrivalTime == globalTime) {
                gorevler[i].startTime = globalTime;
                Enqueue(gorevler[i].priority, &gorevler[i]);
            }
        }

        // Görev seçimi
        if (currentTask != NULL && currentTask->priority == 0 && currentTask->remainingTime > 0) {
            // Priority 0 (Gerçek Zamanlı) kesilmez
        } else {
            currentTask = NULL;
            for(int p=0; p < MAX_QUEUE_LEVEL; p++) {
                if (queue_lens[p] > 0) {
                    currentTask = queues[p][0];
                    break;
                }
            }
        }

        // Çıktı ve yürütme
        if (currentTask != NULL && currentTask->remainingTime > 0) {
            // Normal durumlarda ID'ye özel rengi al
            const char* taskColor = GetColorById(currentTask->id);

            if (currentTask->hasStarted == 0) {
                printf("%s%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)%s\n",
                       taskColor, globalTime, "proses başladı",
                       currentTask->id, currentTask->priority, currentTask->remainingTime, RESET);
                currentTask->hasStarted = 1;
                currentTask->isRunning = 1;
            }
            else if (currentTask != previousTask) {
                printf("%s%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)%s\n",
                       taskColor, globalTime, "proses başladı",
                       currentTask->id, currentTask->priority, currentTask->remainingTime, RESET);
                currentTask->isRunning = 1;
            }
            else {
                printf("%s%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)%s\n",
                       taskColor, globalTime, "proses yürütülüyor",
                       currentTask->id, currentTask->priority, currentTask->remainingTime, RESET);
            }

            currentTask->remainingTime--;
            previousTask = currentTask;
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
        globalTime++;

        // Görev bitişi veya öncelik düşümü
        if (currentTask != NULL) {
            if (currentTask->remainingTime == 0) {
                // Sonlanma durumu (Normal renk)
                const char* taskColor = GetColorById(currentTask->id);
                printf("%s%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre: 0 sn)%s\n",
                       taskColor, globalTime, "proses sonlandı",
                       currentTask->id, currentTask->priority, RESET);

                Dequeue(currentTask->priority);
                currentTask->isRunning = 0;
                currentTask = NULL;
                previousTask = NULL;
            }
            else if (currentTask->priority > 0) {
                // Öncelik düşürme (User process)
                Dequeue(currentTask->priority);
                if (currentTask->priority < MAX_QUEUE_LEVEL - 1) {
                    currentTask->priority++;
                }

                // Askıya alınma durumu (Normal renk)
                const char* taskColor = GetColorById(currentTask->id);
                printf("%s%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)%s\n",
                       taskColor, globalTime, "proses askıda",
                       currentTask->id, currentTask->priority, currentTask->remainingTime, RESET);

                Enqueue(currentTask->priority, currentTask);
                currentTask->isRunning = 0;
                currentTask = NULL;
            }
        }

        // Simülasyon bitiş kontrolü
        int aktif = 0;
        for(int i=0; i<gorevSayisi; i++)
            if (gorevler[i].remainingTime > 0) aktif = 1;

        if (!aktif && globalTime > 5) {
            exit(0);
        }

        // Zaman aşımı (20 sn kuralı)
        for(int i=0; i<gorevSayisi; i++) {
            if (gorevler[i].startTime != -1 && gorevler[i].remainingTime > 0) {
                int timePassed = globalTime - gorevler[i].startTime;
                if (timePassed >= 20) {
                    int kill = 0;
                    if (gorevler[i].hasStarted == 0) kill = 1; 
                    else if (gorevler[i].priority < 3) kill = 1;

                    if (kill) {
                        // BURASI DEĞİŞTİ: Zaman aşımı KESİNLİKLE KIRMIZI olacak
                        printf(COLOR_RED_FIXED "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)%s\n",
                               globalTime, "proses zamanaşımı",
                               gorevler[i].id, gorevler[i].priority, gorevler[i].remainingTime, RESET);

                        RemoveTaskFromQueue(gorevler[i].priority, &gorevler[i]);
                        gorevler[i].remainingTime = 0;
                        if (currentTask == &gorevler[i]) currentTask = NULL;
                    }
                }
            }
        }
    }
}