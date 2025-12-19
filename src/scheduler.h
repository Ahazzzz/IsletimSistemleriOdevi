#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "FreeRTOS.h"
#include "task.h"

// Çıktıları renklendirmek için ANSI kodları
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

#define MAX_QUEUE_LEVEL 6

// Bir görevin sahip olduğu tüm bilgiler
typedef struct {
    char id[16];
    int arrivalTime;
    int priority;
    int burstTime;
    int remainingTime;
    int startTime;
    int hasStarted;
    int isRunning;
} TaskData;

extern TaskData gorevler[50];
extern int gorevSayisi;
extern int globalTime;

void SimulationTask(void *pvParameters);
void DosyaOku(const char* dosyaAdi);

#endif