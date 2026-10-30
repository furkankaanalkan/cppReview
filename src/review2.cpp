#include <iostream>
#include <string>

// ========================================================================
// BÖLÜM 1: CONSTEXPR (Derleme Zamanı Sabitleri)
// ========================================================================
// Program çalışmadan önce, kod derlenirken hesaplanır. Çok hızlıdır.
constexpr int kareAl(int x) {
    return x * x; 
}

// ========================================================================
// BÖLÜM 2: SINIFLAR (OOP, Kapsülleme, Invariant, Const Fonksiyonlar)
// ========================================================================
class BankaHesabi {
private: // KAPSÜLLEME: Dışarıdan doğrudan erişim yasak!
    double bakiye_; 

public:
    // SINIF İÇİ STATIC: Tüm nesneler bu değişkeni ortak paylaşır.
    static int toplam_hesap_sayisi;

    // CONSTRUCTOR (Kurucu Fonksiyon): Nesne Stack veya Heap'te oluşurken 1 kez çalışır.
    BankaHesabi(double bakiye) {
        // INVARIANT KURALI: Bakiye asla negatif olamaz.
        if (bakiye >= 0) {
            // this-> kullanımı: Parametre ismiyle sınıf değişkeni aynı olsaydı zorunluydu.
            // Burada isimler farklı (bakiye ve bakiye_) ama örnek olsun diye ekledik.
            this->bakiye_ = bakiye;
        } else {
            this->bakiye_ = 0; 
        }
        toplam_hesap_sayisi++; // Her nesne üretildiğinde ortak sayaç artar.
    }

    // CONST FONKSİYON: Bu fonksiyon nesnenin hiçbir verisini (bakiye_) değiştiremez!
    double bakiyeGoster() const {
        // bakiye_ = 5000; // YAZILAMAZ! Derleyici (Compiler Error) hatası verir.
        return bakiye_;
    }

    void paraCek(double miktar) {
        if (miktar > 0 && bakiye_ >= miktar) {
            bakiye_ -= miktar;
        }
    }
};

// LİNK HATASI (Linker Error) ALMAMAK İÇİN ZORUNLU: Static değişkenin bellek tanımı
int BankaHesabi::toplam_hesap_sayisi = 0;

// ========================================================================
// BÖLÜM 3: FONKSİYON İÇİ STATIC
// ========================================================================
void sayacGoster() {
    // Fonksiyon bitse bile silinmez, hafızada kalır ve değerini korur.
    static int cagrilma_sayisi = 0; 
    cagrilma_sayisi++;
    std::cout << "sayacGoster() " << cagrilma_sayisi << ". kez cagirildi.\n";
}

// ========================================================================
// BÖLÜM 4: ANA PROGRAM (MAIN)
// ========================================================================
int main() {
    std::cout << "--- CONSTEXPR TEST ---\n";
    constexpr int sonuc = kareAl(5); // Derleyici bunu arka planda direkt '25' yapar.
    std::cout << "Kare: " << sonuc << "\n\n";

    std::cout << "--- REFERANS VE POINTER TEST ---\n";
    int a = 17;
    int* selam = &a; // Pointer (a'nın bellek adresini tutar)
    int& ref = a;    // Referans (a'ya yeni bir takma ad)
    int ref2 = *selam; // Dereference (selam adresindeki değeri okur, 17 olur)

    std::cout << "a: " << a << ", ref: " << ref << ", ref2: " << ref2 << "\n\n";

    std::cout << "--- CONST POINTER KURALLARI ---\n";
    int x = 10;
    int y = 20;
    const int* p1 = &x; // P1'in GÖSTERDİĞİ DEĞER sabit. (*p1 = 5 YASAK, p1 = &y SERBEST)
    int* const p2 = &x; // P2'nin ADRESİ sabit. (*p2 = 5 SERBEST, p2 = &y YASAK)

    std::cout << "--- BELLEK YONETIMI (STACK vs HEAP) ---\n";
    // 1. STACK ÜRETİMİ (new KULLANMADAN - Otomatik silinir)
    BankaHesabi acc1(100); 

    // 2. HEAP ÜRETİMİ (new KULLANARAK - Manuel silinmeli!)
    BankaHesabi* acc2_ptr = new BankaHesabi(500);

    // -> OPERATÖRÜ (Pointer üzerinden nesne fonksiyonu çağırmak)
    acc2_ptr->paraCek(100); // Kisa yazim
    (*acc2_ptr).paraCek(50); // Uzun yazim (Dereference + Nokta)

    std::cout << "acc1 Bakiye: " << acc1.bakiyeGoster() << "\n";
    std::cout << "acc2 Bakiye: " << acc2_ptr->bakiyeGoster() << "\n";
    
    // HEAP'TEN ALINAN BELLEK GERİ VERİLMELİ (Memory Leak olmaması için)
    delete acc2_ptr; 
    std::cout << "\n";

    std::cout << "--- STATIC TEST ---\n";
    sayacGoster(); // Çıktı: 1
    sayacGoster(); // Çıktı: 2
    sayacGoster(); // Çıktı: 3
    std::cout << "Toplam uretilen BankaHesabi nesnesi: " << BankaHesabi::toplam_hesap_sayisi << "\n\n";

    std::cout << "--- HATA TURLERI (Yorum Satirlari) ---\n";
    /*
    1. COMPILER ERROR (Derleme Hatası - Kuralları Çiğnemek):
       acc1.bakiye_ = 50; // Hata: private değişkene dışarıdan erişilemez.
    
    2. LINKER ERROR (Bağlama Hatası):
       int BankaHesabi::toplam_hesap_sayisi = 0; satırını koddan silersen derleyici uyarı vermez 
       ama bağlayıcı (linker) bellekte değişkeni bulamadığı için kodu derleyemez.

    3. RUNTIME ERROR (Çalışma Zamanı Çökmesi):
       BankaHesabi* bos_ptr = nullptr;
       bos_ptr->bakiyeGoster(); // Hata: Null olan (olmayan) bir nesne üzerinden işlem yaparsan program anında çöker.
    */

    return 0; // Program başarıyla bitti
}