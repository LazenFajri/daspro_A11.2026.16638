// ============================================================
// PROGRAM       : HITUNG NILAI STOK SEPATU
// TENTANG       : Menghitung total valuasi nilai barang di gudang
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
struct AsetSepatu {
    string namaSepatu;
    string merek;
    double harga;
    int kuantitas;
    double nilaiTotal;
};

AsetSepatu dataAset;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "========================================" << endl;
    cout << "      PERHITUNGAN NILAI PERSEDIAAN      " << endl;
    cout << "Oleh: Muhammad Fajri Setyawan (A11.2026.16638)" << endl;
    cout << "========================================" << endl;

    cout << "Nama Sepatu        : ";
    getline(cin, dataAset.namaSepatu);

    cout << "Merek              : ";
    getline(cin, dataAset.merek);

    cout << "Harga Satuan (Rp)  : ";
    cin >> dataAset.harga;

    cout << "Jumlah Stok Tersedia: ";
    cin >> dataAset.kuantitas;

    // Kalkulasi nilai total persediaan
    dataAset.nilaiTotal = dataAset.harga * dataAset.kuantitas;

    cout << fixed << setprecision(0);
    cout << endl;
    cout << "========================================" << endl;
    cout << "          RINGKASAN NILAI ASET          " << endl;
    cout << "========================================" << endl;
    cout << "Nama Barang: " << dataAset.namaSepatu << endl;
    cout << "Merek      : " << dataAset.merek << endl;
    cout << "Harga/Unit : Rp " << dataAset.harga << endl;
    cout << "Volume Stok: " << dataAset.kuantitas << " pasang" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Total Aset : Rp " << dataAset.nilaiTotal << endl;
    cout << "========================================" << endl;

    return 0;
}
