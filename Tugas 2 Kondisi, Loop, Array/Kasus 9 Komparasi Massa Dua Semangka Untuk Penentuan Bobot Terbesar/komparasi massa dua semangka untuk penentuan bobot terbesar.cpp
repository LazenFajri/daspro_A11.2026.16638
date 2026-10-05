// ============================================================
// PROGRAM       : KOMPARASI BOBOT DUA SEMANGKA
// TENTANG       : Membandingkan massa dua buah semangka (A dan B)
//                 guna menentukan semangka yang lebih berat
//                 atau mendeteksi kondisi bobot seimbang.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
double beratA;
double beratB;
string kesimpulan;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // Pengaturan tampilan angka desimal
    cout << fixed << setprecision(2);

    // --------------------------------------------------------
    // HEADER PROGRAM
    // --------------------------------------------------------
    cout << "========================================================\n";
    cout << "          UJI KOMPARASI BOBOT DUA BUAH SEMANGKA         \n";
    cout << "========================================================\n";
    cout << "NAMA     : Muhammad Fajri Setyawan\n";
    cout << "NIM      : A11.2026.16638\n";
    cout << "--------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // TAHAP 1: INPUT DATA
    // --------------------------------------------------------
    cout << "Masukkan berat Semangka A (kg) : ";
    cin >> beratA;

    cout << "Masukkan berat Semangka B (kg) : ";
    cin >> beratB;

    // --------------------------------------------------------
    // TAHAP 2: EVALUASI KONDISI PERBANDINGAN
    // --------------------------------------------------------
    if (beratA > beratB) {
        kesimpulan = "Semangka A lebih berat daripada Semangka B.";
    }
    else if (beratB > beratA) {
        kesimpulan = "Semangka B lebih berat daripada Semangka A.";
    }
    else {
        kesimpulan = "Kedua semangka memiliki bobot yang sama berat.";
    }

    // --------------------------------------------------------
    // TAHAP 3: OUTPUT HASIL ANALISIS
    // --------------------------------------------------------
    cout << "\n========================================================\n";
    cout << "                    HASIL ANALISIS                      \n";
    cout << "========================================================\n";
    cout << "Massa Semangka A : " << beratA << " kg\n";
    cout << "Massa Semangka B : " << beratB << " kg\n";
    cout << "--------------------------------------------------------\n";
    cout << "Hasil Evaluasi   : " << kesimpulan << "\n";
    cout << "========================================================\n";

    return 0;
}
