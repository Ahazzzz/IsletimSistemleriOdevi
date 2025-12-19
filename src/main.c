#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "scheduler.h" 

// Beklenmedik bir hata olursa buraya düşeceğiz
void vAssertCalled(const char *pcFile, unsigned long ulLine) {
    printf("HATA OLUŞTU! Dosya: %s, Satır: %lu\n", pcFile, ulLine);
    exit(-1);
}

int main(int argc, char *argv[]) {
    // Komut satırından dosya ismi gelmezse varsayılan olarak giris.txt'ye bakıyoruz
    const char* filename = (argc > 1) ? argv[1] : "giris.txt";
    
    // Verileri oku ve yapıya aktar
    DosyaOku(filename);

    // Ana simülasyon görevini oluşturuyoruz. Önceliği yüksek tuttuk.
    xTaskCreate(SimulationTask, "Scheduler", 4096, NULL, configMAX_PRIORITIES-1, NULL);

    // FreeRTOS zamanlayıcısını başlat; kontrol artık RTOS'ta
    vTaskStartScheduler();

    return 0;
}