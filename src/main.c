#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "scheduler.h" 

void vAssertCalled(const char *pcFile, unsigned long ulLine) {
    printf("ASSERTION FAILED! File: %s, Line: %lu\n", pcFile, ulLine);
    exit(-1);
}

int main(int argc, char *argv[]) {
 
    const char* filename = (argc > 1) ? argv[1] : "giris.txt";
    DosyaOku(filename);

 
    xTaskCreate(SimulationTask, "Scheduler", 4096, NULL, configMAX_PRIORITIES-1, NULL);

  
    vTaskStartScheduler();

    return 0;
}