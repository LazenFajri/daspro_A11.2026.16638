// ============================================================
// PROGRAM       : ANALISIS DAN PENGURUTAN 3 BILANGAN
// TENTANG       : Menentukan bilangan terbesar dengan pohon keputusan
//                 serta mengurutkan ketiga nilai dari besar ke kecil.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
int a, b, c;
int temp;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "====================================================\n";
    cout << "       KOMPARASI & PENGURUTAN TIGA BILANGAN         \n";
    cout << "====================================================\n";
    cout << "Oleh : Muhammad Fajri Setyawan (A11.2026.16638)\n";
    cout << "----------------------------------------------------\n";

    cout << "Masukkan bilangan pertama (a): ";
    cin >> a;
    cout << "Masukkan bilangan kedua   (b): ";
    cin >> b;
    cout << "Masukkan bilangan ketiga  (c): ";
    cin >> c;

    cout << "\nData Terbaca: a = " << a << ", b = " << b << ", c = " << c << "\n\n";

    // --------------------------------------------------------
    // Evaluasi Bilangan Terbesar Sesuai Pohon Keputusan
    // --------------------------------------------------------
    cout << "[ Status Analisis Nilai Terbesar ]\n";
    if (a > b) {
        if (a > c) {
            cout << "-> Bilangan a (" << a << ") adalah yang terbesar.\n";
        } else if (a < c) {
            cout << "-> Bilangan c (" << c << ") adalah yang terbesar.\n";
        } else {
            cout << "-> Bilangan a (" << a << ") dan c (" << c << ") sama-sama terbesar.\n";
        }
    } else if (a < b) {
        if (b > c) {
            cout << "-> Bilangan b (" << b << ") adalah yang terbesar.\n";
        } else if (b < c) {
            cout << "-> Bilangan c (" << c << ") adalah yang terbesar.\n";
        } else {
            cout << "-> Bilangan b (" << b << ") dan c (" << c << ") sama-sama terbesar.\n";
        }
    } else {
        if (a > c) {
            cout << "-> Bilangan a (" << a << ") dan b (" << b << ") sama-sama terbesar.\n";
        } else if (a < c) {
            cout << "-> Bilangan c (" << c << ") adalah yang terbesar.\n";
        } else {
            cout << "-> Ketiga bilangan memiliki nilai sama persis (" << a << ").\n";
        }
    }

    // --------------------------------------------------------
    // Menata Urutan dari Nilai Terbesar ke Terkecil
    // --------------------------------------------------------
    if (a < b) {
        temp = a; a = b; b = temp;
    }
    if (a < c) {
        temp = a; a = c; c = temp;
    }
    if (b < c) {
        temp = b; b = c; c = temp;
    }

    cout << "\n[ Urutan Menurun (Besar ke Kecil) ]\n";
    cout << "Hasil Penataan: " << a << " >= " << b << " >= " << c << "\n";
    cout << "====================================================\n";

    return 0;
}
