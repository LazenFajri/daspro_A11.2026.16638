// ============================================================
// PROGRAM       : SELEKSI KONDISI SWITCH-CASE
// TENTANG       : Mengonversi masukan kode numerik menjadi representasi
//                 teks kata menggunakan struktur kendali switch-case.
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
int bilanganPilihan;
string teksKeluaran;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // TAMPILAN HEADER PROGRAM
    // --------------------------------------------------------
    cout << "========================================================\n";
    cout << "          LATIHAN KONDISI PERCABANGAN SWITCH-CASE       \n";
    cout << "========================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "--------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // TAHAP 1: INPUT DATA
    // --------------------------------------------------------
    cout << "Masukkan kode angka (contoh: 1, 2, 3, ...): ";
    cin >> bilanganPilihan;

    // --------------------------------------------------------
    // TAHAP 2: PROSES SELEKSI SWITCH-CASE
    // --------------------------------------------------------
    switch (bilanganPilihan)
    {
        case 1:
            teksKeluaran = "satu";
            break;

        case 2:
            teksKeluaran = "dua";
            break;

        case 3:
            teksKeluaran = "tiga";
            break;

        case 4:
            teksKeluaran = "empat";
            break;

        case 5:
            teksKeluaran = "lima";
            break;

        default:
            // Dijalankan bila input tidak cocok dengan case mana pun
            teksKeluaran = "lainnya (angka di luar rentang 1 - 5)";
            break;
    }

    // --------------------------------------------------------
    // TAHAP 3: OUTPUT HASIL EVALUASI
    // --------------------------------------------------------
    cout << "\n--------------------------------------------------------\n";
    cout << "Angka yang dimasukkan : " << bilanganPilihan << "\n";
    cout << "Teks representasi     : \"" << teksKeluaran << "\"\n";
    cout << "========================================================\n";

    return 0; // Mengakhiri program secara normal
}
