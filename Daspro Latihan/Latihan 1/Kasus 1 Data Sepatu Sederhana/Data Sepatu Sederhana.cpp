// ============================================================
// PROGRAM       : DATA SEPATU SEDERHANA
// TENTANG       : Mendefinisikan dan menampilkan data identitas sepatu
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
struct AtributSepatu {
    string namaSepatu;
    string merek;
    string warna;
    int ukuran;
    double hargaBeli;
};

AtributSepatu sepatuPribadi;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // Pemberian nilai pada field data sepatu
    sepatuPribadi.namaSepatu = "Air Jordan 1 Low";
    sepatuPribadi.merek      = "Nike";
    sepatuPribadi.warna      = "Hitam Putih";
    sepatuPribadi.ukuran     = 43;
    sepatuPribadi.hargaBeli  = 1950000;

    // Visualisasi data keluaran
    cout << fixed << setprecision(0);
    cout << "========================================" << endl;
    cout << "         DATA IDENTITAS SEPATU          " << endl;
    cout << "========================================" << endl;
    cout << "Pengunggah : Muhammad Fajri Setyawan" << endl;
    cout << "NIM        : A11.2026.16638" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Seri/Model : " << sepatuPribadi.namaSepatu << endl;
    cout << "Produsen   : " << sepatuPribadi.merek << endl;
    cout << "Kelir/Warna: " << sepatuPribadi.warna << endl;
    cout << "Ukuran     : " << sepatuPribadi.ukuran << endl;
    cout << "Harga Beli : Rp " << sepatuPribadi.hargaBeli << endl;
    cout << "========================================" << endl;

    return 0;
}
