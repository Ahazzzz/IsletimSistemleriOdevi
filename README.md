🚀 İşletim Sistemleri Ödevi: FreeRTOS Zaman Paylaşımlı Planlayıcı
Bu proje, İşletim Sistemleri dersi kapsamında, FreeRTOS çekirdeği kullanılarak geliştirilmiş bir Zaman Paylaşımlı Görev Planlayıcı (Time-Sliced Task Scheduler) uygulamasıdır. Proje, gerçek zamanlı işletim sistemi (RTOS) kavramlarını PC ortamında simüle ederek görev yönetimini görselleştirmeyi amaçlar.

📌 Proje Özellikleri
FreeRTOS Entegrasyonu: Gerçek zamanlı işletim sistemi çekirdeği üzerinde görev yönetimi.

Zaman Paylaşımlı Planlama: Görevlerin önceliklerine ve zaman dilimlerine (time-quantums) göre adil bir şekilde çalıştırılması.

PC Simülasyonu: Geliştirilen planlayıcının standart bir bilgisayar üzerinde (Linux/Windows/Mac) test edilebilir yapısı.

Detaylı Analiz: Rapor.pdf içerisinde sistemin çalışma mantığı ve performans çıktıları yer almaktadır.

📁 Proje Klasör Yapısı
Plaintext

📦 IsletimSistemleriOdevi
 ┣ 📂 FreeRTOS      # FreeRTOS çekirdek dosyaları
 ┣ 📂 include       # Başlık dosyaları (.h)
 ┣ 📂 src           # Kaynak kodlar (.c)
 ┣ 📜 Makefile      # Derleme yapılandırması
 ┣ 📜 Rapor.pdf     # Proje teknik dökümantasyonu ve analizler
 ┣ 📜 Çıktı.jpg     # Uygulamanın çalışma ekran görüntüsü
 ┣ 📜 giris.txt     # Örnek girdi verileri
 ┗ 📜 IsletimSistemleriOdevi_yorumlu.zip  # Açıklama satırlı kaynak kod arşivi
🛠️ Başlarken
Gereksinimler
Projeyi yerel makinenizde derlemek ve çalıştırmak için aşağıdaki araçların kurulu olması gerekir:

GCC Toolchain: Linux, macOS (Xcode) veya Windows (MinGW/MSYS2).

GNU Make: Derleme işlemlerini otomatize etmek için.

POSIX Standartları: PC üzerinde FreeRTOS simülasyonu için POSIX kütüphanesi desteği.

Kurulum ve Çalıştırma
Depoyu Klonlayın:

Bash

git clone https://github.com/Ahazzzz/IsletimSistemleriOdevi.git
cd IsletimSistemleriOdevi
Projeyi Derleyin:

Bash

make
Uygulamayı Çalıştırın:

Bash

./scheduler
(Not: Derleme sonrası oluşan çalıştırılabilir dosya adı Makefile içeriğine göre farklılık gösterebilir.)

⚙️ Çalışma Mantığı
Proje, giris.txt dosyasından okunan veya kod içerisinde tanımlanan görevleri (tasks) FreeRTOS yapısına uygun olarak oluşturur.

Görev Öncelikleri: Her görevin belirli bir öncelik değeri vardır.

Zaman Dilimi: Aynı önceliğe sahip görevler, işlemciyi sırayla ve eşit sürelerle kullanır.

İzleme: Çalışma esnasında hangi görevin ne zaman işlemciyi aldığı terminal üzerinden takip edilebilir.

📄 Belgeler ve Raporlama
Proje ile ilgili tüm teknik detaylara Rapor.pdf dosyasından ulaşabilirsiniz. Rapor şunları içerir:

Sistem mimarisi ve tasarım kararları.

FreeRTOS konfigürasyonu (FreeRTOSConfig.h).

Deneysel sonuçlar ve karşılaşılan zorluklar.
