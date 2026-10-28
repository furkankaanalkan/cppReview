/*
 ===========================================================================
 SENG 211 - Lab 4 Quiz Pratiği 2 (Özel Sınav Seti)
 ===========================================================================
 Bu dosya, Pointers, References, Static Class Members, const member functions,
 Class Invariants ve Error Handling konularını pekiştirmen için hazırlanmıştır.
 
 Sorular ve açıklamalar yorum satırı olarak, C++ kodları ise çalıştırılabilir 
 (veya incelenebilir) formatta aşağıda yer almaktadır. Kodu derleyip
 çalıştırarak kendi gözlerinle de test edebilirsin.
*/

#include <iostream>
using namespace std;

/* 
 ===========================================================================
 SORU 1: Pointers, References & Side Effects
 ===========================================================================
 Soru: Bu program ne yazdırır?
 
 Açıklama/Çözüm:
 - Başlangıç: x = 2, y = 3, z = 4
 - process(&x, y, z) çağrıldığında:
   p -> x'in adresi, r -> y'nin referansı, v -> z'nin kopyası (4)
 - *p += v  => x = 2 + 4 = 6
 - r += *p  => y = 3 + 6 = 9
 - p = &v   => p artık yerel v değişkenini işaret ediyor
 - *p = 50  => v = 50 olur ama z değişmez (değer ile geçtiği için)
 - Sonuç: 6 9 4 (Cevap A)
*/

void process(int* p, int& r, int v) {
    *p += v;     
    r += *p;     
    p = &v;      
    *p = 50;     
}

void test_question_1() {
    cout << "--- Soru 1 Testi ---" << endl;
    int x = 2, y = 3, z = 4;
    process(&x, y, z);
    cout << "Cikti: " << x << " " << y << " " << z << '\n';
    cout << "Beklenen: 6 9 4\n\n";
}

/* 
 ===========================================================================
 SORU 2: Static Members & Compilation/Linking
 ===========================================================================
 Soru 2a: Asagidaki dosyalar derlendiginde hangi durum olusur?
 Cevap 2a: D (Linker error: Counter::total is declared but not defined.)
 Aciklama: Static üyeler header'da bildirilir (declare), ama .cpp dosyasinda 
 (sinif disinda) tanimlanmalidir (define). Tanimlanmadigi icin linker hatasi verir.
 
 Soru 2b: counter.cpp'ye 'int Counter::total = 0;' eklenirse ne yazdirir?
 Cevap 2b: A (1 2 2)
 Aciklama: c1 icin id_=1, total=1 olur. c2 icin id_=2, total=2 olur.
*/

class Counter {
public:
    static int total;
    Counter() {
        id_ = ++total;
    }
    int getID() const {
        return id_;
    }
private:
    int id_{0};
};

// Linker hatasini önlemek icin static üye tanimlamasi (Soru 2b icin eklenen satir):
int Counter::total = 0;

void test_question_2() {
    cout << "--- Soru 2 Testi ---" << endl;
    Counter c1;
    Counter c2;
    cout << "Cikti: " << c1.getID() << " " << c2.getID() << " " << Counter::total << '\n';
    cout << "Beklenen: 1 2 2\n\n";
}

/* 
 ===========================================================================
 SORU 3: Class Invariant & Error Analysis
 ===========================================================================
 Soru (a): Bosluklari doldurma
 1) static int transaction_count;
 2) int getBalance() const { ... }
 3) int BankAccount::transaction_count = 0;
 4) bool BankAccount::withdraw(...)
 5) balance_ < amount
*/

class BankAccount {
public:
    // (1) 
    static int transaction_count;
    
    bool deposit(int amount);
    bool withdraw(BankAccount& target, int amount);
    
    // (2)
    int getBalance() const { return balance_; }

private:
    int balance_{0};
};

// (3)
int BankAccount::transaction_count = 0;

bool BankAccount::deposit(int amount) {
    if (amount <= 0) return false;
    balance_ += amount;
    return true;
}

// (4)
bool BankAccount::withdraw(BankAccount& target, int amount) {
    // (5)
    if (amount <= 0 || balance_ < amount) {
        return false;
    }
    balance_ -= amount;
    target.balance_ += amount;
    transaction_count++;
    return true;
}

/*
 Soru (b): Çikti Tahmini
 acc1.deposit(300) -> BASARILI (acc1=300)
 acc2.deposit(-50) -> BASARISIZ (acc2=0)
 r.withdraw(*p, 100) -> acc1'den acc2'ye 100 transfer (acc1=200, acc2=100, count=1)
 p->withdraw(acc1, 250) -> Yetersiz bakiye BASARISIZ
 acc1.withdraw(acc1, 50) -> Kendi kendine BASARILI (acc1=200, count=2)
 p->withdraw(acc2, 0) -> Miktar 0 BASARISIZ
 Sonuc: 200 100 2
 
 Soru (c): Hata Siniflandirma
 1. acc1.balance_ = 1000; => Compiler Error (private member)
 2. const BankAccount& cb = acc1; cb.withdraw(acc2, 50); => Compiler Error (withdraw const degil)
 3. const BankAccount& cb = acc1; cout << cb.getBalance(); => OK (getBalance const metod)
 4. BankAccount* ptr = nullptr; ptr->deposit(100); => Runtime error (Null Pointer Dereference)
 5. int& b = acc1.getBalance(); => Compiler Error (gecici rvalue'ya lvalue referansi baglanamaz)
*/

void test_question_3() {
    cout << "--- Soru 3 Testi ---" << endl;
    BankAccount acc1, acc2;
    acc1.deposit(300);
    acc2.deposit(-50);
    
    BankAccount* p = &acc2;
    BankAccount& r = acc1;

    r.withdraw(*p, 100);
    p->withdraw(acc1, 250);
    acc1.withdraw(acc1, 50);
    
    p = &acc1;
    p->withdraw(acc2, 0);

    cout << "Cikti: " << acc1.getBalance() << " " << acc2.getBalance() << " " << BankAccount::transaction_count << '\n';
    cout << "Beklenen: 200 100 2\n\n";
}

int main() {
    test_question_1();
    test_question_2();
    test_question_3();
    
    cout << "Tum testler basariyla calisti! Sinavda basarilar dilerim! :)" << endl;
    return 0;
}