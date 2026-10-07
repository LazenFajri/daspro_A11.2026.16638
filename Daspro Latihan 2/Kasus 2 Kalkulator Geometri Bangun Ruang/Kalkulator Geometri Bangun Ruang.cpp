// ============================================================
// PROGRAM       : KALKULATOR GEOMETRI BANGUN RUANG
// TENTANG       : Menghitung volume dan luas permukaan bangun ruang
//                 (Tabung dan Balok) melalui sistem menu interaktif.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <iomanip>

using namespace std;

// ============================================================
// KAMUS
// Semua variabel program dideklarasikan di sini tanpa 'const'
// ============================================================
int pilihanObjek;
int pilihanHitung;

// Parameter geometri tabung
double r;
double tinggiTabung;

// Parameter geometri balok
double panjang;
double lebar;
double tinggiBalok;

// Variabel penampung hasil kalkulasi
double volume;
double luas;

// Variabel nilai rasio lingkaran
double phi;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // TAHAP AWAL: INISIALISASI VARIABEL & FORMAT TAMPILAN
    // --------------------------------------------------------
    phi = 3.14;

    // --------------------------------------------------------
    // HEADER PROGRAM
    // --------------------------------------------------------
    cout << "========================================================\n";
    cout << "          KALKULATOR GEOMETRI BANGUN RUANG              \n";
    cout << "========================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "--------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // TAHAP 1: PEMILIHAN OBJEK
    // --------------------------------------------------------
    cout << "PILIH BANGUN RUANG:\n";
    cout << "  1. Tabung\n";
    cout << "  2. Balok\n";
    cout << ">> Masukkan pilihan Anda (1/2): ";
    cin >> pilihanObjek;

    cout << "\n--------------------------------------------------------\n";

    // --------------------------------------------------------
    // TAHAP 2: PROSES SELEKSI MENU UTAMA (SWITCH-CASE)
    // --------------------------------------------------------
    switch (pilihanObjek)
    {
        // ----------------------------------------------------
        // KASUS 1: BANGUN TABUNG
        // ----------------------------------------------------
        case 1:
            cout << "[ PARAMETER TABUNG ]\n";
            cout << "Masukkan jari-jari alas (r) : ";
            cin >> r;
            cout << "Masukkan tinggi tabung (t)  : ";
            cin >> tinggiTabung;

            cout << "\nPILIH OPERASI HITUNG:\n";
            cout << "  1. Hitung Volume Tabung\n";
            cout << "  2. Hitung Luas Permukaan Tabung\n";
            cout << ">> Masukkan pilihan hitung (1/2): ";
            cin >> pilihanHitung;

            cout << "\n[ HASIL PERHITUNGAN TABUNG ]\n";
            if (pilihanHitung == 1) {
                volume = phi * r * r * tinggiTabung;
                cout << "Volume Tabung          : " << volume << " satuan kubik\n";
            } else if (pilihanHitung == 2) {
                luas = 2.0 * phi * r * (r + tinggiTabung);
                cout << "Luas Permukaan Tabung  : " << luas << " satuan persegi\n";
            } else {
                cout << "Peringatan: Pilihan jenis perhitungan tidak tersedia.\n";
            }
            break;

        // ----------------------------------------------------
        // KASUS 2: BANGUN BALOK
        // ----------------------------------------------------
        case 2:
            cout << "[ PARAMETER BALOK ]\n";
            cout << "Masukkan panjang balok (p) : ";
            cin >> panjang;
            cout << "Masukkan lebar balok (l)   : ";
            cin >> lebar;
            cout << "Masukkan tinggi balok (t)  : ";
            cin >> tinggiBalok;

            cout << "\nPILIH OPERASI HITUNG:\n";
            cout << "  1. Hitung Volume Balok\n";
            cout << "  2. Hitung Luas Permukaan Balok\n";
            cout << ">> Masukkan pilihan hitung (1/2): ";
            cin >> pilihanHitung;

            cout << "\n[ HASIL PERHITUNGAN BALOK ]\n";
            if (pilihanHitung == 1) {
                volume = panjang * lebar * tinggiBalok;
                cout << "Volume Balok           : " << volume << " satuan kubik\n";
            } else if (pilihanHitung == 2) {
                luas = 2.0 * ((panjang * lebar) + (panjang * tinggiBalok) + (lebar * tinggiBalok));
                cout << "Luas Permukaan Balok   : " << luas << " satuan persegi\n";
            } else {
                cout << "Peringatan: Pilihan jenis perhitungan tidak tersedia.\n";
            }
            break;

        // ----------------------------------------------------
        // DEFAULT: KETIKA PILIHAN TIDAK COCOK
        // ----------------------------------------------------
        default:
            cout << "Kesalahan: Objek bangun ruang tidak tersedia!\n";
            break;
    }

    cout << "========================================================\n";
    cout << "Status: Program kalkulator geometri selesai dieksekusi.\n";

    return 0;
}
