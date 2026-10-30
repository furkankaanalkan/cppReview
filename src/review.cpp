/*
 ===========================================================================
 SENG 211 - KUSURSUZ FİNAL ÇALIŞMA REHBERİ (Lab 1 - 4 Kapsamı)
 İçerik: Pointers, References, const, Static, Invariants, Modern C++ ve Hatalar
 ===========================================================================
*/

#include <iostream>
#include <string>
#include <memory> // Smart Pointers (unique_ptr) icin gerekli

using namespace std;

// =========================================================================
// BÖLÜM 1: Pointers, References ve Modern Alternatifleri
// =========================================================================

void test_section_1() {
    cout << "--- BÖLÜM 1: POINTERS & REFERENCES ---" << endl;

    int a = 10;
    
    // 1. Klasik Reference ve Pointer
    int& ref = a;     // a'nin takma adi. Bellekte yeni yer kaplamaz, kopyalama yapmaz.
    int* ptr = &a;    // a'nin bellek adresini tutar.
    
    // Alternatif (Modern ve Guvenli) Adres Alma:
    int* safe_ptr = std::addressof(a); 

    // 2. Dinamik Bellek (Heap) Yonetimi (Rule of Three/Five temelini olusturur)
    
    // ESKI YONTEM: Manuel yonetim (Tehlikeli)
    int* raw_ptr = new int(50);
    delete raw_ptr; // Unutulursa "Memory Leak" (Bellek Sizintisi) olur!

    // MODERN YONTEM: Smart Pointers (C++11)
    // Kendi kendini yok eden akilli isaretciler. Delete yazmaya gerek kalmaz.
    std::unique_ptr<int> smart_ptr = std::make_unique<int>(100);
    
    cout << "Smart pointer adresteki deger: " << *smart_ptr << endl;
    cout << endl;
}

// =========================================================================
// BÖLÜM 2: const, constexpr ve Static Üyeler
// =========================================================================

// Statik uyeler sinifa aittir, nesnelere degil.
class UserManager {
public:
    static int user_count; // Declaration (Bildirim)
    
    UserManager() { user_count++; }
    
    // const member function: Nesnenin internal_data_ uyesini degistirmeyecegini garanti eder.
    int getCount() const { return user_count; }
};

// Statik uyenin bellek tanimi (Definition) - Linker Error almamak icin ZORUNLUDUR!
int UserManager::user_count = 0;

void test_section_2() {
    cout << "--- BÖLÜM 2: CONST & STATIC ---" << endl;

    // Klasik Sabit (Runtime)
    const int max_size = 50; 
    
    // Modern Sabit (Compile-time): Cok daha performanslidir.
    constexpr double PI = 3.14159; 

    // Const - Pointer iliskisi (Sagdan Sola Okunur)
    int x = 5, y = 10;
    const int* p1 = &x; // Pointer to const: Deger degistirilemez (*p1 = 20 YASAK) ama adres degisir (p1 = &y OK).
    int* const p2 = &x; // Const pointer: Adres degistirilemez (p2 = &y YASAK) ama deger degisir (*p2 = 20 OK).

    UserManager u1, u2;
    cout << "Toplam kullanici (Scope :: ile): " << UserManager::user_count << endl;
    cout << endl;
}

// =========================================================================
// BÖLÜM 3: Class Invariant (Sınıf Değişmezi) ve Kapsülleme
// =========================================================================
/*
 Neden Kullanılır? Nesnelerin icindeki verilerin her zaman mantikli ve 
 gecerli bir aralikta kalmasini saglamak icin (Kapsulleme/Encapsulation).
*/

class BankAccount {

private:
    double balance_; // Private yapılarak dışarıdan doğrudan bozulması engellendi.


public:
    // Invariant Kurali: Bakiye (balance_) HİÇBİR ZAMAN sifirdan kucuk olamaz.
    BankAccount(double initial_balance) {
        if (initial_balance >= 0) {
            balance_ = initial_balance;
        } else {
            balance_ = 0; // Kurala uymuyorsa, Invariant'i korumak icin varsayilan atanir.
        }
    }

    bool withdraw(double amount) {
        // Invariant kontrolu yapiliyor: Eksiye dusmeye izin yok.
        if (amount > 0 && balance_ >= amount) {
            balance_ -= amount;
            return true;
        }
        return false;
    }

    double getBalance() const { return balance_; }
};

void test_section_3() {
    cout << "--- BÖLÜM 3: CLASS INVARIANTS ---" << endl;
    
    BankAccount acc(100);
    // Kapsulleme ve pointer/ok (->) operatoru alternatifi:
    BankAccount* acc_ptr = &acc;
    
    // Bu iki cagirimin derleyici gozundeki anlami birebir aynidir:
    acc_ptr->withdraw(30);       // 1. Kisa Yazim (Syntactic Sugar)
    (*acc_ptr).withdraw(20);     // 2. Asil Yazim (Once dereference et, sonra noktayla gir)

    cout << "Guncel Bakiye: " << acc.getBalance() << " (Invariant korundu)" << endl;
    cout << endl;
}

// =========================================================================
// BÖLÜM 4: Yaygın Derleme ve Bağlama Hataları (C++ Errors)
// =========================================================================
/*
 C++'ta karsilasacagin 3 temel hata turu sinavlarda klasiktir:
 
 1. Compiler Error (Derleme Hatası): Syntax veya kural ihlali.
    - Ornek: Private bir degiskene disaridan erismeye calismak. (obj.private_var = 5)
    - Ornek: const bir nesne uzerinden, const olmayan (degisiklik yapan) metot cagirmak.

 2. Linker Error (Bağlama Hatası): Kod yazim kurallarina uyar ama karsiliklari yoktur.
    - Ornek: Class icinde `static int count;` yazip, disarida `int Class::count = 0;` tanimlamamak.
    - Ornek: Sadece bildirimini yaptigin (`void print();`) bir fonksiyonun suslu parantezli govdesini yazmamak.

 3. Runtime Error / Undefined Behavior (Çalışma Zamanı Hatası): Kod derlenir ama calisirken coker.
    - Ornek: nullptr olan bir pointer uzerinden ok/nokta kullanip islem yapmaya calismak. (Segmentation Fault)
    - Ornek: Dizinin (Array) sinirlari disindaki bir index'e erismek.
*/

void test_section_4() {
    cout << "--- BÖLÜM 4: HATA TURLERI (Bkz. Yorum Satirlari) ---" << endl;
    
    // Runtime Error (Çökme) engelleme pratigi:
    int* null_ptr = nullptr;
    if (null_ptr != nullptr) {
        // null kontrolu yapilmazsa ve *null_ptr cagrilirsa program patlar (Runtime Error).
    }
    
    cout << "Tum testler basariyla derlendi ve baglandi (No Linker/Compiler Error)." << endl;
}

int main() {
    test_section_1();
    test_section_2();
    test_section_3();
    test_section_4();
    
    return 0;
}