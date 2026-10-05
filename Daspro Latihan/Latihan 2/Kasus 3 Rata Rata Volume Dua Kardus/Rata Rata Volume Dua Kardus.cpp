// ============================================================
// PROGRAM       : RATA-RATA VOLUME DUA KARDUS
// TENTANG       : Menghitung volume dari dua buah wadah kardus serta
//                 mencari nilai rerata kapasitas keduanya.
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
struct DimensiKardus {
    string namaKardus;
    double panjang;
    double lebar;
    double tinggi;
    double volume;
};

DimensiKardus kardus1, kardus2;
double rataRataVolume;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "====================================================\n";
    cout << "       KOMPUTASI RATA-RATA VOLUME DUA KARDUS        \n";
    cout << "====================================================\n";
    cout << "Oleh : Muhammad Fajri Setyawan (A11.2026.16638)\n";
    cout << "----------------------------------------------------\n";

    // Membaca spesifikasi Kardus 1
    cout << "Kardus 1 - Label/Nama  : ";
    getline(cin, kardus1.namaKardus);
    cout << "Kardus 1 - Panjang (cm): ";
    cin >> kardus1.panjang;
    cout << "Kardus 1 - Lebar (cm)  : ";
    cin >> kardus1.lebar;
    cout << "Kardus 1 - Tinggi (cm) : ";
    cin >> kardus1.tinggi;
    kardus1.volume = kardus1.panjang * kardus1.lebar * kardus1.tinggi;
    cin.ignore();

    // Membaca spesifikasi Kardus 2
    cout << "\nKardus 2 - Label/Nama  : ";
    getline(cin, kardus2.namaKardus);
    cout << "Kardus 2 - Panjang (cm): ";
    cin >> kardus2.panjang;
    cout << "Kardus 2 - Lebar (cm)  : ";
    cin >> kardus2.lebar;
    cout << "Kardus 2 - Tinggi (cm) : ";
    cin >> kardus2.tinggi;
    kardus2.volume = kardus2.panjang * kardus2.lebar * kardus2.tinggi;

    // Menghitung nilai rerata
    rataRataVolume = (kardus1.volume + kardus2.volume) / 2.0;

    // Output penyajian data
    cout << fixed << setprecision(2);
    cout << "\n====================================================\n";
    cout << "               REKAPITULASI HASIL                   \n";
    cout << "====================================================\n";
    cout << "Volume " << kardus1.namaKardus << " : " << kardus1.volume << " cm3\n";
    cout << "Volume " << kardus2.namaKardus << " : " << kardus2.volume << " cm3\n";
    cout << "----------------------------------------------------\n";
    cout << "Rata-rata Volume : " << rataRataVolume << " cm3\n";
    cout << "====================================================\n";

    return 0;
}
