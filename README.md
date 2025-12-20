📘 İşletim Sistemleri Ödevi – FreeRTOS Scheduler

🎓 Ders: İşletim Sistemleri
👨‍💻 Proje: FreeRTOS PC Scheduler Uygulaması
📂 Dil: C
📅 Hazırlayan: Ahazzzz

🧠 Proje Hakkında

Bu proje, FreeRTOS gerçek zamanlı işletim sistemi benzeri bir scheduler (zamanlayıcı) simülasyonu oluşturmayı amaçlar. PC üzerinde çalışan bir scheduler implementasyonu geliştirilmiştir. Proje, işletim sistemleri dersinde scheduler yapısını, görev yönetimini ve zaman paylaştırmalı çalışmayı anlamak için yapılmıştır.

Bu çalışma sayesinde;

Görevlerin belirli zaman aralıklarında nasıl çalıştırıldığı,

Task yönetimi ve idle task konseptleri,

FreeRTOS tarzı scheduler mimarisi,

Zaman paylaştırmalı (time-sharing) çalışan sistemlerin nasıl oluşturulduğu
gibi temel işletim sistemi kavramları uygulamalı olarak deneyimlenmiştir.

📁 Proje İçeriği
IsletimSistemleriOdevi/
├── FreeRTOS/                      # FreeRTOS çekirdek kodları
├── include/                       # Header dosyaları
├── src/                           # Kaynak kodlar
├── Makefile                       # Proje derleme betiği
├── Rapor.pdf                      # Proje raporu (PDF)
├── Makefile.txt                   # Açıklamalı Makefile
├── giris.txt                      # Girdi örneği
├── Çıktı.jpg                     # Program çıktı ekran görüntüsü
├── Çıktı.pdf                     # Çıktı PDF formatında
├── IsletimSistemleriOdevi.zip     # Kaynak arşivi
├── IsletimSistemleriOdevi_yorumlu.zip # Açıklamalı kaynak arşivi
└── README.md                     # Bu belge

🛠️ Özellikler

✨ Proje içeriğinde aşağıdaki özellikler bulunmaktadır:

✔️ FreeRTOS tabanlı scheduler implementasyonu

✔️ Birden fazla task’ın zamanlanması

✔️ Round-Robin benzeri task değişimi

✔️ Idle task ve task state takibi

✔️ PC üzerinde simülasyon olarak çalışabilir yapıda

✔️ Girdi/Çıktı örnekleri ve görsellerle açıklama

🚀 Nasıl Çalıştırılır?

📌 Projeyi klonladıktan sonra terminalden aşağıdaki komutları çalıştırarak derleme ve çalıştırma yapılır:

git clone https://github.com/Ahazzzz/IsletimSistemleriOdevi.git
cd IsletimSistemleriOdevi
make
./scheduler


🛑 make komutu çalışmıyorsa:

gcc src/*.c -Iinclude -o scheduler
./scheduler

📊 Çıktı Örnekleri

📌 Proje içerisinde hem girdi örneği (giris.txt) hem de çıktı ekran görüntüleri (Çıktı.jpg ve Çıktı.pdf) yer almaktadır. Bu örneklerle programın çalışması gözlemlenebilir.

📑 Proje Raporu

Proje raporu Rapor.pdf içinde detaylı olarak verilmiştir. Raporda:

Problem tanımı,

Mimarinin anlatımı,

Kullanılan algoritmalar,

Çalışma örnekleri,

Sonuç ve değerlendirmeler yer almaktadır.

🤝 Katkıda Bulunma

Bu proje açık kaynaklıdır. Herkes katkıda bulunabilir!
Katkı yapmak için:

Repoyu fork’la

Yeni bir branch aç (feature/ozellik)

Değişikliklerini commit’le

Pull request oluştur 😊

📄 Lisans

Bu proje açık kaynak olup özgün öğrenme amaçlı yapılmıştır.
Lisans bilgisi proje içinde ayrıca yer almıyorsa MIT ya da BSD-like lisans ekleyebilirsin.
