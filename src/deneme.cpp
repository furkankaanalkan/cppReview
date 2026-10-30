#include <iostream>

#include <string>

void sayacGoster() {
        static int sayac = 0; // Sadece ilk çağrıldığında 1 kez oluşturulur ve sıfırlanır
        sayac++;
        std::cout << "Bu fonksiyon " << sayac << ". kez çağrıldı." << std::endl;
    }

    

class MyClass {
    int value;

    private:
    int value2;

    public:
    MyClass(int value , int myvalue2) {
        this->value = value;
        value2 = myvalue2; // adları farklı olduğu için this-> kullanmaya gerek yok
        std::cout << "selam " << std::endl;
        
    }
};
    
    


int main() {
    int a = 17;

    // pointer tanınımı / int* --> int değişkeninin adresi tutan değişken tanımlamak için kullanılır 
    // &a --> a nın adresini verir 
    int* selam = &a;

    // direk a nın referansı 
    int& ref = a;

    // selam adresindeki değer yani (*selam = 17) --> referansı dolaylı yoldan a nın referansı  
    int& ref2 = *selam;

    // direk yeni değişkene atanır referans değil anın adresini tutan selamın pointerırın değerini yeni değişken fura kopyalar
    int fur = *selam;

    std::cout << ref << std::endl;
    std::cout << ref2 << std::endl;
    std::cout << *selam << std::endl;
    std::cout << fur << std::endl;
    std::cout << selam << std::endl;
    std::cout << &a << std::endl;


    const int* ptr = &a; // pointerın kendisi değiştirilebilir ama pointerın gösterdiği değer değiştirilemez
    int* const ptr2 = &a; // pointerın kendisi değiştirilemez
    const int* const ptr3 = &a; // pointerın kendisi ve gösterdiği değer değiştirilemez

    sayacGoster();
    sayacGoster();
    sayacGoster();
    sayacGoster();

    MyClass myfru(10, 20);






    return 0;
}
