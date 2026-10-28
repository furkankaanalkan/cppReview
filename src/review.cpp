/*
 ===========================================================================
 SENG 211 - Kapsamlı Lab Pratiği (Lab 1 - Lab 3 / Lab 4 Konu Özeti)
 ===========================================================================
 Bu dosya, şimdiye kadar işlenen tüm temel C++ konularını (Pointers, References,
 Static Class Members, const member functions, Class Invariants, Dynamic 
 Memory, Rule of Three/Five vb.) pekiştirmen ve sınava kolayca çalışabilmen 
 için hazırlanmıştır.
 
 Tüm sorular ve detaylı öğretici açıklamalar yorum satırı olarak verilmiştir.
*/

#include <iostream>
#include <string>
using namespace std;

/*
 ===========================================================================
 BÖLÜM 1: Pointers, References ve Bellek Yönetimi (Pointers & References)
 ===========================================================================
 * Pointer (*): Bellek adresini tutar. Değere ulaşmak için dereference (*) edilir.
 * Reference (&): Mevcut bir değişkenin takma adıdır (alias). Başka bir yere 
   yeniden bağlanamaz, oluşturulduğu anda bir değişkene atanmalıdır.
 * const Pointer vs Pointer to const:
   - const int* p;  -> Pointer'ın gösterdiği değer sabittir (değiştirilemez).
   - int* const p;  -> Pointer'ın kendisi sabittir (başka yeri gösteremez).
*/

void test_section_1() {
    cout << "=== BÖLÜM 1 TESTİ: Pointers & References ===" << endl;
    int a = 10;
    int* ptr = &a;    // a'nın adresini tutar
    int& ref = a;     // a'nın takma adıdır

    *ptr = 20;        // a artık 20 oldu
    cout << "a (pointer ile degisti): " << a << endl;

    ref = 30;         // a artık 30 oldu
    cout << "a (reference ile degisti): " << a << endl;
    cout << endl;
}


/*
 ===========================================================================
 BÖLÜM 2: Sınıflar, Static Üyeler ve const Metotlar (Static & const)
 ===========================================================================
 * static int: Sınıfa aittir, nesnelere değil. Tüm nesneler aynı değişkeni paylaşır.
   Not: Sınıf dışında mutlaka tanımlanmalıdır (Definition), aksi takdirde Linker Error alınır.
 * const member functions: `int getVal() const { ... }` şeklinde yazılır. 
   Nesnenin üye değişkenlerinde değişiklik yapılmayacağını derleyiciye garanti eder.
   const nesneler yalnızca const metotları çağırabilir.
*/

class DataManager {
public:
    // Statik üye bildirimi (Declaration)
    static int object_count;

    DataManager() {
        object_count++;
    }

    // const metot: Nesneyi değiştirmez, const nesneler tarafından çağrılabilir
    int getCount() const {
        return object_count;
    }

private:
    int internal_data_{0};
};

// Statik üyenin sınıf dışında bellekte tanımlanması (Definition)
int DataManager::object_count = 0;

void test_section_2() {
    cout << "=== BÖLÜM 2 TESTİ: Static & const Members ===" << endl;
    DataManager d1;
    DataManager d2;
    
    const DataManager d3; // const nesne
    cout << "Toplam olusturulan nesne sayisi (d3.getCount() ile): " << d3.getCount() << endl;
    cout << endl;
}


/*
 ===========================================================================
 BÖLÜM 3: Class Invariant (Sınıf Değişmezi) ve Kapsülleme (Encapsulation)
 ===========================================================================
 * Sınıf Invariantı: Sınıfın içindeki verilerin her zaman tutarlı kalmasını 
   sağlayan kurallardır (Örn: Banka bakiyesi sıfırdan küçük olamaz: balance_ >= 0).
 * Private üyelere dışarıdan doğrudan erişilemez; setter/getter veya özel 
   işlem metotları (deposit, withdraw) üzerinden erişilir.
*/

class SecureAccount {
public:
    SecureAccount(int initial_balance) {
        if (initial_balance >= 0) {
            balance_ = initial_balance;
        } else {
            balance_ = 0; // Invariant korunur
        }
    }

    bool withdraw(int amount) {
        // Invariant kontrolü: Bakiye düşülecek miktardan az olamaz
        if (amount <= 0 || balance_ < amount) {
            return false; // İşlem başarısız, invariant bozulmaz
        }
        balance_ -= amount;
        return true;
    }

    int getBalance() const { return balance_; }

private:
    int balance_; // private: dışarıdan doğrudan değiştirilemez (örn: acc.balance_ = -500 yasak)
};

void test_section_3() {
    cout << "=== BÖLÜM 3 TESTİ: Class Invariant ===" << endl;
    SecureAccount acc(100);
    
    if (acc.withdraw(150)) {
        cout << "Para cekme basarili." << endl;
    } else {
        cout << "Yetersiz bakiye! Invariant korundu, bakiye degismedi." << endl;
    }
    cout << "Guncel Bakiye: " << acc.getBalance() << endl;
    cout << endl;
}


/*
 ===========================================================================
 BÖLÜM 4: Yaygın Derleme ve Bağlama Hataları (Compilation & Linker Errors)
 ===========================================================================
 1. Compiler Error (Derleme Hatası): Syntax hataları, private değişkenlere 
    erişme çabaları, tip uyuşmazlıkları (örn. geçici rvalue'ya lvalue referansı bağlama).
 2. Linker Error (Bağlama Hatası): Bildirilen ama tanımlanmayan static değişkenler 
    veya eksik fonksiyon gövdeleri.
 3. Runtime Error / Undefined Behavior (Çalışma Zamanı Hatası): nullptr dereference 
    (nullptr üzerinden metoda erişme), dizi sınırlarının dışına çıkma.
*/

void test_section_4() {
    cout << "=== BÖLÜM 4 Özet Bilgi ===" << endl;
    cout << "1. Private degiskene dogrudan erisim -> Compiler Error" << endl;
    cout << "2. Static uyenin .cpp/.cpp disinda tanimlanmamasi -> Linker Error" << endl;
    cout << "3. nullptr uzerinden metod cagirimi -> Runtime Error (Segmentation Fault)" << endl;
    cout << endl;
}

int main() {
    test_section_1();
    test_section_2();
    test_section_3();
    test_section_4();
    
    cout << "Tum bolumler basariyla tamamlandi. Sinavda basarilar dilerim!" << endl;
    return 0;
}
