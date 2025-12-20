# 🚀 İşletim Sistemleri Ödevi

**FreeRTOS ile Zaman Paylaşımlı Görev Planlayıcı & PC Üzerinde Scheduler Simülasyonu**

---

## 📌 Proje Hakkında

Bu proje, **İşletim Sistemleri dersi** ödevi kapsamında geliştirilmiştir.

Ana amaçlar:
- FreeRTOS kernel'i kullanarak **zaman paylaşımlı (time-sliced) görev planlayıcı** implementasyonu yapmak
- Eşit önceliğe sahip görevlerin CPU zamanını adil şekilde paylaşmasını sağlamak (time quanta ile)
- Gerçek zamanlı işletim sistemi (RTOS) davranışlarını **PC ortamında simüle etmek** ve görselleştirmek

Proje, FreeRTOS kavramlarını pratikte uygulamayı ve görev yönetimi, önceliklendirme ile zaman paylaşımı mekanizmalarını anlamayı hedefler.

Repo içerikleri:
- FreeRTOS kernel kaynak kodları
- Proje kaynak kodları (yorumlu ve yorumlusuz versiyonlar)
- Ödev raporu (PDF)
- Makefile ve derleme dosyaları
- Örnek giriş/çıkış dosyaları
- Program çıktısı görselleri


---

## 🛠️ Başlarken

### Gereksinimler
Projeyi derleyip çalıştırmak için:
- **GCC** (Linux, macOS veya Windows'ta MinGW/WSL)
- **Make** aracı
- Standart C kütüphaneleri (FreeRTOS repo içinde mevcut)

### Kurulum ve Derleme

```bash
# Repoyu klonlayın
git clone https://github.com/Ahazzzz/IsletimSistemleriOdevi.git

# Klasöre girin
cd IsletimSistemleriOdevi

# Projeyi derleyin
make

# Çalıştırın (derleme sonrası oluşan executable genellikle 'scheduler' adını alır)
./scheduler
```
## ⚙️ Kullanım ve Önemli Özellikler
Proje, giriş dosyasındaki görevleri okuyarak FreeRTOS tarzı bir planlayıcı ile yürütür:

Görev oluşturma ve öncelik atama
Eşit öncelikli görevlerde zaman dilimli (time-sliced) planlama
Görevlerin sırayla CPU zamanını paylaşması
Simülasyon çıktıları ile gerçek zamanlı davranış gözlemlenebilir

Daha detaylı açıklama ve FreeRTOS yapılandırması (FreeRTOSConfig.h vb.) için rapora bakınız.
