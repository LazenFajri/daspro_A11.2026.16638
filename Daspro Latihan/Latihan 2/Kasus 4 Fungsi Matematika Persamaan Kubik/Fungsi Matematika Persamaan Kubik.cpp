// ============================================================
// PROGRAM       : EVALUASI PERSAMAAN KUBIK (y = a^3 + 7)
// TENTANG       : Menghitung nilai ordinat y berdasarkan fungsi
//                 pangkat tiga dengan modul pustaka cmath pow().
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
double a;
double y;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "====================================================\n";
    cout << "        EVALUASI PERSAMAAN MATEMATIKA: y = a^3 + 7  \n";
    cout << "====================================================\n";
    cout << "Oleh : Muhammad Fajri Setyawan (A11.2026.16638)\n";
    cout << "----------------------------------------------------\n";

    cout << "Masukkan nilai parameter a : ";
    cin >> a;

    // Memanfaatkan fungsi pow() dari library cmath
    y = pow(a, 3.0) + 7.0;

    cout << fixed << setprecision(2);
    cout << "\n----------------------------------------------------\n";
    cout << "Nilai input a : " << a << "\n";
    cout << "Hasil nilai y : " << y << "\n";
    cout << "====================================================\n";

    return 0;
}
