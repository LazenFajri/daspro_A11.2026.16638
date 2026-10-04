// ============================================================
// PROGRAM       : SPESIFIKASI LENGKAP SEPATU
// TENTANG       : Mendata atribut fisik dan logistik sepatu
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
struct SpesifikasiSepatu {
    string namaSepatu;
    string merek;
    string kategori;
    string kelir;
    string material;
    int ukuran;
    int stok;
    double hargaBeli;
};

SpesifikasiSepatu koleksi;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "========================================" << endl;
    cout << "    INPUT SPESIFIKASI LENGKAP SEPATU    " << endl;
    cout << "Oleh: Muhammad Fajri Setyawan (A11.2026.16638)" << endl;
    cout << "========================================" << endl;

    cout << "Nama Seri/Model : ";
    getline(cin, koleksi.namaSepatu);

    cout << "Merek Dagang    : ";
    getline(cin, koleksi.merek);

    cout << "Kategori/Jenis  : ";
    getline(cin, koleksi.kategori);

    cout << "Warna Fisik     : ";
    getline(cin, koleksi.kelir);

    cout << "Bahan Material  : ";
    getline(cin, koleksi.material);

    cout << "Ukuran Sol (EU) : ";
    cin >> koleksi.ukuran;

    cout << "Kuantitas Stok  : ";
    cin >> koleksi.stok;

    cout << "Harga Satuan    : ";
    cin >> koleksi.hargaBeli;

    // Cetak lembar spesifikasi
    cout << fixed << setprecision(0);
    cout << endl;
    cout << "========================================" << endl;
    cout << "      LEMBAR SPESIFIKASI SEPATU         " << endl;
    cout << "========================================" << endl;
    cout << "Nama Model : " << koleksi.namaSepatu << endl;
    cout << "Merek      : " << koleksi.merek << endl;
    cout << "Kategori   : " << koleksi.kategori << endl;
    cout << "Warna      : " << koleksi.kelir << endl;
    cout << "Material   : " << koleksi.material << endl;
    cout << "Ukuran     : " << koleksi.ukuran << endl;
    cout << "Persediaan : " << koleksi.stok << " pasang" << endl;
    cout << "Harga      : Rp " << koleksi.hargaBeli << endl;
    cout << "========================================" << endl;

    return 0;
}
