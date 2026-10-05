// ============================================================
// PROGRAM       : INPUT DATA SEPATU
// TENTANG       : Membaca masukan dinamis keyboard dan menampilkan data
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
struct ProfilSepatu {
    string namaSepatu;
    string merek;
    string warna;
    int ukuran;
    double hargaBeli;
};

ProfilSepatu sepatuInput;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "========================================" << endl;
    cout << "         PENCATATAN DATA SEPATU         " << endl;
    cout << "Oleh: Muhammad Fajri Setyawan (A11.2026.16638)" << endl;
    cout << "========================================" << endl;

    // Membaca masukan pengguna
    cout << "Nama Sepatu / Model : ";
    getline(cin, sepatuInput.namaSepatu);

    cout << "Merek Produsen      : ";
    getline(cin, sepatuInput.merek);

    cout << "Varian Warna        : ";
    getline(cin, sepatuInput.warna);

    cout << "Nomor Ukuran (EU)   : ";
    cin >> sepatuInput.ukuran;

    cout << "Harga Perolehan (Rp): ";
    cin >> sepatuInput.hargaBeli;

    // Menampilkan hasil penangkapan data
    cout << fixed << setprecision(0);
    cout << endl;
    cout << "========================================" << endl;
    cout << "         DATA SEPATU TERSIMPAN          " << endl;
    cout << "========================================" << endl;
    cout << "Nama/Model : " << sepatuInput.namaSepatu << endl;
    cout << "Merek      : " << sepatuInput.merek << endl;
    cout << "Warna      : " << sepatuInput.warna << endl;
    cout << "Ukuran     : " << sepatuInput.ukuran << endl;
    cout << "Harga      : Rp " << sepatuInput.hargaBeli << endl;
    cout << "========================================" << endl;

    return 0;
}
