#include <iostream>

using namespace std;

int Luas_Persegi(int n) {
    return n * n;
}

bool is_ganjil(int n) {
    return (n % 2 != 0);
}

bool is_genap(int n) {
    return (n % 2 == 0);
}

int sum_n(int n){
    int total = 0;
    cout << "Deret: ";
    for (int i= 1; i<= n; i++) {
            cout << i << (i == n ? "" : " + ");
            total += i;
    }
    cout << endl;
    return total;
}

double avg_n(int n){
    return (double)sum_n(n) / n;
}

int main(){
    int n;
    cout << "Masukkan bilangan bulat n: ";
    cin >> n;

    cout << "Luas Persegi (" << n << ")  : " << Luas_Persegi(n) << endl;
    cout << "is_ganjil(" << n << ")      : " << (is_ganjil(n) ? "True" : "False") << endl;
    cout << "is_genap(" << n << ")       : " << (is_genap(n) ? "True" : "False") << endl;
    cout << "\nMenghitung avg_n(" << n << "):" << endl;
    double rata = avg_n(n);
    cout << "Rata-rata deret: " << rata << endl;

    return 0;
}
