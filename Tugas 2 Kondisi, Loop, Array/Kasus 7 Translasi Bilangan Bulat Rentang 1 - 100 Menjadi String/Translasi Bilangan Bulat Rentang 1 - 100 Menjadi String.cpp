// ============================================================
// PROGRAM       : KONVERSI ANGKA MENJADI KATA (1 - 100)
// TENTANG       : Mengubah inputan numerik bulat dari rentang 1
//                 hingga 100 menjadi ejaan kata teks bahasa Indonesia
//                 menggunakan logika IF, operasi DIV (/), dan MOD (%).
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// Semua variabel program dideklarasikan di bagian ini
// ============================================================
int angka;
int satuan;
int puluhan;
string kataSatuan[10];
string hasilKata;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // TAMPILAN HEADER PROGRAM
    // --------------------------------------------------------
    cout << "========================================================\n";
    cout << "       PROGRAM TRANSLASI ANGKA KE KATA (1 - 100)        \n";
    cout << "========================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "--------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // INISIALISASI KAMUS SATUAN DASAR (1 - 9)
    // --------------------------------------------------------
    kataSatuan[1] = "satu";
    kataSatuan[2] = "dua";
    kataSatuan[3] = "tiga";
    kataSatuan[4] = "empat";
    kataSatuan[5] = "lima";
    kataSatuan[6] = "enam";
    kataSatuan[7] = "tujuh";
    kataSatuan[8] = "delapan";
    kataSatuan[9] = "sembilan";

    // --------------------------------------------------------
    // TAHAP 1: INPUT NILAI NUMERIK
    // --------------------------------------------------------
    cout << "Masukkan bilangan bulat (1 - 100): ";
    cin >> angka;

    // --------------------------------------------------------
    // TAHAP 2: PROSES LOGIKA PERCABANGAN (SESUAI FLOWCHART)
    // --------------------------------------------------------
    if (angka == 100) {
        // Kondisi 1: Nilai batas maksimum 100 (Khusus)
        hasilKata = "seratus";
    }
    else if (angka < 10 && angka >= 1) {
        // Kondisi 2: Rentang angka satuan 1 - 9
        hasilKata = kataSatuan[angka];
    }
    else if (angka == 10) {
        // Kondisi 3: Angka sepuluh (Kasus Khusus)
        hasilKata = "sepuluh";
    }
    else if (angka == 11) {
        // Kondisi 4: Angka sebelas (Kasus Khusus)
        hasilKata = "sebelas";
    }
    else if (angka < 20 && angka >= 12) {
        // Kondisi 5: Rentang belasan (12 - 19)
        // Diambil nilai satuannya menggunakan operator modulo (%)
        satuan    = angka % 10;
        hasilKata = kataSatuan[satuan] + " belas";
    }
    else if (angka >= 20 && angka < 100) {
        // Kondisi 6: Rentang puluhan (20 - 99)
        // Memecah komponen puluhan (DIV /) dan komponen satuan (MOD %)
        puluhan = angka / 10;
        satuan  = angka % 10;

        if (satuan == 0) {
            // Jika satuan bernilai 0 (contoh: 20, 30, 40, 70)
            hasilKata = kataSatuan[puluhan] + " puluh";
        } else {
            // Jika satuan bukan 0 (contoh: 37 -> tiga puluh tujuh)
            hasilKata = kataSatuan[puluhan] + " puluh " + kataSatuan[satuan];
        }
    }
    else {
        hasilKata = "[Angka di luar jangkauan pengujian 1 sampai 100]";
    }

    // --------------------------------------------------------
    // TAHAP 3: OUTPUT HASIL TRANSLASI
    // --------------------------------------------------------
    cout << "\n--------------------------------------------------------\n";
    cout << "Nilai Angka  : " << angka << "\n";
    cout << "Hasil Kalimat: \"" << hasilKata << "\"\n";
    cout << "========================================================\n";

    return 0; // Mengakhiri program secara normal
}
