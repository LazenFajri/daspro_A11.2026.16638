// ============================================================
// PROGRAM       : KONVERSI ANGKA KE TEKS KATA (1 - 100)
// TENTANG       : Menerjemahkan angka bilangan bulat 1 sampai 100
//                 menjadi ejaan kata Bahasa Indonesia yang baku.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
int angka;
int satuan;
int puluhan;
string hasilKata;

// Fungsi pembantu pemetaan satuan
string dapatkanNamaSatuan(int s) {
    if (s == 1) return "satu";
    if (s == 2) return "dua";
    if (s == 3) return "tiga";
    if (s == 4) return "empat";
    if (s == 5) return "lima";
    if (s == 6) return "enam";
    if (s == 7) return "tujuh";
    if (s == 8) return "delapan";
    if (s == 9) return "sembilan";
    return "";
}

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "====================================================\n";
    cout << "        KONVERSI ANGKA KE KATA (RENTANG 1-100)      \n";
    cout << "====================================================\n";
    cout << "Oleh : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "----------------------------------------------------\n";

    cout << "Masukkan bilangan bulat (1 - 100): ";
    cin >> angka;

    // Evaluasi sesuai alur bagan alir (flowchart)
    if (angka == 100) {
        hasilKata = "seratus";
    } else if (angka < 10 && angka >= 1) {
        hasilKata = dapatkanNamaSatuan(angka);
    } else if (angka == 10) {
        hasilKata = "sepuluh";
    } else if (angka == 11) {
        hasilKata = "sebelas";
    } else if (angka < 20 && angka >= 12) {
        satuan    = angka % 10;
        hasilKata = dapatkanNamaSatuan(satuan) + " belas";
    } else if (angka >= 20 && angka <= 99) {
        puluhan = angka / 10;
        satuan  = angka % 10;

        if (satuan == 0) {
            hasilKata = dapatkanNamaSatuan(puluhan) + " puluh";
        } else {
            hasilKata = dapatkanNamaSatuan(puluhan) + " puluh " + dapatkanNamaSatuan(satuan);
        }
    } else {
        hasilKata = "[Nilai tidak valid atau di luar batas 1 sampai 100]";
    }

    // Tampilkan hasil ejaan
    cout << "\n----------------------------------------------------\n";
    cout << "Angka Masukan : " << angka << "\n";
    cout << "Ejaan Kata    : \"" << hasilKata << "\"\n";
    cout << "====================================================\n";

    return 0;
}
