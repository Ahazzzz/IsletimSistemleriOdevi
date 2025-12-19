#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "queue.h"

TaskData gorevler[50];
int gorevSayisi = 0;
int globalTime = 0;

// Öncelik seviyelerine göre ayrılmış kuyruklar
TaskData* queues[MAX_QUEUE_LEVEL][50];
int queue_lens[MAX_QUEUE_LEVEL] = {0};

// Kuyruğa yeni eleman ekleme (en sona ekler)
void Enqueue(int p, TaskData* t) {
    if (p >= MAX_QUEUE_LEVEL) p = MAX_QUEUE_LEVEL - 1;
    queues[p][queue_lens[p]] = t;
    queue_lens[p]++;
}

// Kuyruğun başından eleman çıkarma
TaskData* Dequeue(int p) {
    if (queue_lens[p] == 0) return NULL;
    TaskData* t = queues[p][0];
    for (int i = 0; i < queue_lens[p] - 1; i++) {
        queues[p][i] = queues[p][i+1];
    }
    queue_lens[p]--;
    return t;
}

// Belirli bir görevi kuyruktan silme (özellikle zaman aşımında lazım oluyor)
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

// Dosyadan satır satır verileri çekip TaskData dizisine dolduruyoruz
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

// Ana simülasyon döngüsü
void SimulationTask(void *pvParameters) {
    (void) pvParameters;
    printf("Simulasyon Basliyor...\n");

    TaskData* currentTask = NULL;
    TaskData* previousTask = NULL;

    for(;;) {
        // Geliş zamanı gelen prosesleri kuyruğa alalım
        for(int i=0; i<gorevSayisi; i++) {
            if (gorevler[i].arrivalTime == globalTime) {
                gorevler[i].startTime = globalTime;
                Enqueue(gorevler[i].priority, &gorevler[i]);
            }
        }

        // Karar mekanizması: Çalışacak görevi seç
        // Eğer 0 öncelikli (en yüksek) bir iş varsa, o bitene kadar devam eder (Gerçek zamanlı)
        if (currentTask != NULL && currentTask->priority == 0 && currentTask->remainingTime > 0) {
            // Devam...
        } else {
            // Değilse, kuyrukları sırayla kontrol et (En üstten alta)
            currentTask = NULL;
            for(int p=0; p < MAX_QUEUE_LEVEL; p++) {
                if (queue_lens[p] > 0) {
                    currentTask = queues[p][0];
                    break;
                }
            }
        }

        // Seçilen görevi ekrana yazdır ve süresini düş
        if (currentTask != NULL && currentTask->remainingTime > 0) {
            if (currentTask->hasStarted == 0) {
                printf(BLUE "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)\n" RESET,
                       globalTime, "proses başladı",
                       currentTask->id, currentTask->priority, currentTask->remainingTime);
                currentTask->hasStarted = 1;
                currentTask->isRunning = 1;
            }
            else if (currentTask != previousTask) {
                printf(BLUE "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)\n" RESET,
                       globalTime, "proses başladı",
                       currentTask->id, currentTask->priority, currentTask->remainingTime);
                currentTask->isRunning = 1;
            }
            else {
                printf(GREEN "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)\n" RESET,
                       globalTime, "proses yürütülüyor",
                       currentTask->id, currentTask->priority, currentTask->remainingTime);
            }

            currentTask->remainingTime--;
            previousTask = currentTask;
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 saniye bekle (Gerçek zamanlı simülasyon)
        globalTime++;

        // Görev bittiyse veya önceliği düşürülecekse yapılacak işlemler
        if (currentTask != NULL) {
            if (currentTask->remainingTime == 0) {
                printf(MAGENTA "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre: 0 sn)\n" RESET,
                       globalTime, "proses sonlandı",
                       currentTask->id, currentTask->priority);

                Dequeue(currentTask->priority);
                currentTask->isRunning = 0;
                currentTask = NULL;
                previousTask = NULL;
            }
            else if (currentTask->priority > 0) {
                // Önceliği 0'dan büyükse, her saniye önceliğini bir düşürüp (sayıca artış) alt kuyruğa atıyoruz
                Dequeue(currentTask->priority);
                if (currentTask->priority < MAX_QUEUE_LEVEL - 1) {
                    currentTask->priority++;
                }

                printf(YELLOW "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)\n" RESET,
                       globalTime, "proses askıda",
                       currentTask->id, currentTask->priority, currentTask->remainingTime);

                Enqueue(currentTask->priority, currentTask);
                currentTask->isRunning = 0;
                currentTask = NULL;
            }
        }

        // Tüm görevler bitti mi kontrolü
        int aktif = 0;
        for(int i=0; i<gorevSayisi; i++)
            if (gorevler[i].remainingTime > 0) aktif = 1;

        if (!aktif && globalTime > 5) {
            exit(0);
        }

        // Zaman aşımı (Timeout) kontrolü: 20 saniye kuralı
        for(int i=0; i<gorevSayisi; i++) {
            if (gorevler[i].startTime != -1 && gorevler[i].remainingTime > 0) {
                int timePassed = globalTime - gorevler[i].startTime;
                if (timePassed >= 20) {
                    int kill = 0;
                    if (gorevler[i].hasStarted == 0) kill = 1; // Hiç başlamadıysa
                    else if (gorevler[i].priority < 3) kill = 1; // Başladı ama önceliği düşükse

                    if (kill) {
                        printf(RED "%-2d.0000 sn %-20s (id:%-4s  öncelik:%2d  kalan süre:%2d sn)\n" RESET,
                               globalTime, "proses zamanaşımı",
                               gorevler[i].id, gorevler[i].priority, gorevler[i].remainingTime);

                        RemoveTaskFromQueue(gorevler[i].priority, &gorevler[i]);
                        gorevler[i].remainingTime = 0;
                        if (currentTask == &gorevler[i]) currentTask = NULL;
                    }
                }
            }
        }
    }
}