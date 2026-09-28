#include<iostream>

using namespace std;

int main() {
 int i = 15, *p, *q;
 p = &i;
 *p = 20;

 // 1. Tampilkan nilai dari variabel
cout << "1. Nilai i : " << i << endl;

// 2. jika i = 50, tampilkan variabel i dan p (*p)
i = 50;
cout << "2. Nilai i : " << i << endl;
cout << "   Nilai *p: " << *p << " (Alamat p: " << p << ")" << endl;

// 3. q = &i dan *q = 100
q = &i;
*q = 100;
cout << "3. a. Nilai i : " << i << endl;
cout << "      Nilai *q: " << *q << " (Alamat q: " << q << ")" << endl;
cout << "      Nilai *p: " << *p << " (Alamat p: " << p << ")" << endl;

return 0;
}



