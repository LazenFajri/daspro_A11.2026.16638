#include<iostream>
#include<cmath>

using namespace std;

int main (){
//1. y = a^3 + 7
double a1 = 2;
double y1 = pow(a1, 3) + 7;
cout << "1. Nilai y (a=2): " << y1 << endl;

// 2. y = ax^2 + bx + c
double a2 = 2, b2 = 3, c2 = 4, x2 = 5;
double y2 = (a2 * pow(x2, 2)) + (b2 * x2) + c2;
cout << "2. Nilai y (ax^2 + bx + c): " << y2 << endl;

// 3. Input 5 bilangan, jumlah dan rata - rata
cout << "\n3. Masukkan 5 bilangan:\n";
double bil, total = 0;
for (int i =1; i<=5; i++) {
        cout << "bilangan ke-" << i << ": ";
        cin >> bil;
        total += bil;
}
cout << "a. jumlah: " << total << endl;
cout << "b. Rata-rata: " << total / 5.0 << endl;

// 4. Konversi suhu
double c;
cout << "\n4. Masukkan suhu dalam Celcius: ";
cin >> c;
double f = (9.0 / 5.0) * c * 32;
double k = c + 273;
double r = (4.0 / 5.0) * c;
cout << "a. Farenheit: " << f << endl;
cout << "b. kelvin: " << k << endl;
cout << "c. Reamur: " << r << endl;

return 0;
}
