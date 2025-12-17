CC = gcc

CFLAGS = -I. -I./include -I./FreeRTOS/include \
         -I./FreeRTOS/portable/ThirdParty/GCC/Posix \
         -I./FreeRTOS/portable/ThirdParty/GCC/Posix/utils \
         -w -DprojCOVERAGE_TEST=0

SRC = src/main.c \
      src/scheduler.c \
      FreeRTOS/src/tasks.c \
      FreeRTOS/src/queue.c \
      FreeRTOS/src/list.c \
      FreeRTOS/src/timers.c \
      FreeRTOS/portable/ThirdParty/GCC/Posix/port.c \
      FreeRTOS/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c \
      FreeRTOS/portable/MemMang/heap_4.c

TARGET = freertos_sim

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lpthread

run:
	@echo "📂 Calisma dizini:"
	@pwd
	@echo ""
	@if [ ! -f giris.txt ]; then \
		echo "❌ HATA: giris.txt bulunamadi!"; \
		echo "📌 Lutfen dosyayi bu dizine koy:"; \
		pwd; \
		exit 1; \
	fi
	@echo "✅ giris.txt bulundu, program calistiriliyor..."
	./freertos_sim giris.txt

clean:
	rm -f $(TARGET)
