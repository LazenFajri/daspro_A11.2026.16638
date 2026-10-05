// ============================================================
// PROGRAM       : PENGHITUNG VOLUME BALOK
// TENTANG       : Menghitung volume bangun ruang balok berdasarkan
//                 parameter panjang, lebar, dan tinggi masukan.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <iomanip>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
double panjang;
double lebar;
double tinggi;
double volume;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "====================================================\n";
    cout << "          KALKULATOR VOLUME RUANG BALOK             \n";
    cout << "====================================================\n";
    cout << "Oleh : Muhammad Fajri Setyawan (A11.2026.16638)\n";
    cout << "----------------------------------------------------\n";

    // Menerima parameter dimensi objek
    cout << "Masukkan ukuran panjang (cm) : ";
    cin >> panjang;

    cout << "Masukkan ukuran lebar (cm)   : ";
    cin >> lebar;

    cout << "Masukkan ukuran tinggi (cm)  : ";
    cin >> tinggi;

    // Menghitung volume dengan rumus geometris balok
    volume = panjang * lebar * tinggi;

    // Menampilkan hasil komputasi
    cout << fixed << setprecision(2);
    cout << "\n----------------------------------------------------\n";
    cout << "Dimensi Objek  : " << panjang << " x " << lebar << " x " << tinggi << " cm\n";
    cout << "Volume Balok   : " << volume << " cm3\n";
    cout << "====================================================\n";

    return 0;
}
