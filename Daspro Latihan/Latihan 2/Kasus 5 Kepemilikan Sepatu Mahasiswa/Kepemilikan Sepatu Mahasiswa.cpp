// ============================================================
// PROGRAM       : DATA KEPEMILIKAN SEPATU MAHASISWA
// TENTANG       : Pengelolaan informasi kepemilikan alas kaki menggunakan
//                 arsitektur tipe bentukan bertingkat (Nested Struct).
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
// Sub-struktur spesifikasi barang
struct TipeSepatu {
    string kodeSepatu;
    string merk;
    double harga;
    string tipeModel;
    string warna;
};

// Sub-struktur tanggal perolehan
struct WaktuBeli {
    int tgl;
    int bln;
    int thn;
};

// Sub-struktur identitas pemilik
struct Pemilik {
    string nama;
    string noHp;
    string email;
};

// Struktur komposit utama
struct TransaksiSepatu {
    TipeSepatu sepatu;
    WaktuBeli  tanggal;
    Pemilik    pemilik;
};

TransaksiSepatu sepatuIda1, sepatuIda2;
TransaksiSepatu sepatuIwan1, sepatuIwan2;
TransaksiSepatu sepatuDian1;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << fixed << setprecision(0);

    // Inisialisasi Data Sepatu Milik Ida
    sepatuIda1 = {{"S001", "Nike", 1200000, "Running", "Putih"}, {12, 3, 2026}, {"Ida", "081234567801", "ida@email.com"}};
    sepatuIda2 = {{"S002", "Adidas", 950000, "Casual", "Hitam"}, {15, 4, 2026}, {"Ida", "081234567801", "ida@email.com"}};

    // Inisialisasi Data Sepatu Milik Iwan
    sepatuIwan1 = {{"S003", "Puma", 850000, "Sport", "Biru"}, {10, 2, 2026}, {"Iwan", "081234567802", "iwan@email.com"}};
    sepatuIwan2 = {{"S004", "New Balance", 1500000, "Running", "Abu-abu"}, {20, 5, 2026}, {"Iwan", "081234567802", "iwan@email.com"}};

    // Inisialisasi Data Sepatu Milik Dian
    sepatuDian1 = {{"S005", "Converse", 750000, "Casual", "Merah"}, {8, 6, 2026}, {"Dian", "081234567803", "dian@email.com"}};

    cout << "========================================================================\n";
    cout << "             SISTEM ARSIP KEPEMILIKAN SEPATU MAHASISWA                  \n";
    cout << "========================================================================\n";
    cout << "Oleh : Muhammad Fajri Setyawan (A11.2026.16638)\n";
    cout << "------------------------------------------------------------------------\n";

    // 1. Rekap Pemilik: Ida
    cout << "\n[ DATA SEPATU - PEMILIK: " << sepatuIda1.pemilik.nama << " ]\n";
    cout << " Kontak   : " << sepatuIda1.pemilik.noHp << " | " << sepatuIda1.pemilik.email << "\n";
    cout << "  1. " << setw(13) << left << sepatuIda1.sepatu.merk
         << " (" << sepatuIda1.sepatu.tipeModel << ", " << sepatuIda1.sepatu.warna << ")"
         << " - Rp " << setw(10) << left << sepatuIda1.sepatu.harga
         << " | Beli: " << sepatuIda1.tanggal.tgl << "/" << sepatuIda1.tanggal.bln << "/" << sepatuIda1.tanggal.thn << "\n";
    cout << "  2. " << setw(13) << left << sepatuIda2.sepatu.merk
         << " (" << sepatuIda2.sepatu.tipeModel << ", " << sepatuIda2.sepatu.warna << ")"
         << " - Rp " << setw(10) << left << sepatuIda2.sepatu.harga
         << " | Beli: " << sepatuIda2.tanggal.tgl << "/" << sepatuIda2.tanggal.bln << "/" << sepatuIda2.tanggal.thn << "\n";

    // 2. Rekap Pemilik: Iwan
    cout << "\n[ DATA SEPATU - PEMILIK: " << sepatuIwan1.pemilik.nama << " ]\n";
    cout << " Kontak   : " << sepatuIwan1.pemilik.noHp << " | " << sepatuIwan1.pemilik.email << "\n";
    cout << "  1. " << setw(13) << left << sepatuIwan1.sepatu.merk
         << " (" << sepatuIwan1.sepatu.tipeModel << ", " << sepatuIwan1.sepatu.warna << ")"
         << " - Rp " << setw(10) << left << sepatuIwan1.sepatu.harga
         << " | Beli: " << sepatuIwan1.tanggal.tgl << "/" << sepatuIwan1.tanggal.bln << "/" << sepatuIwan1.tanggal.thn << "\n";
    cout << "  2. " << setw(13) << left << sepatuIwan2.sepatu.merk
         << " (" << sepatuIwan2.sepatu.tipeModel << ", " << sepatuIwan2.sepatu.warna << ")"
         << " - Rp " << setw(10) << left << sepatuIwan2.sepatu.harga
         << " | Beli: " << sepatuIwan2.tanggal.tgl << "/" << sepatuIwan2.tanggal.bln << "/" << sepatuIwan2.tanggal.thn << "\n";

    // 3. Rekap Pemilik: Dian
    cout << "\n[ DATA SEPATU - PEMILIK: " << sepatuDian1.pemilik.nama << " ]\n";
    cout << " Kontak   : " << sepatuDian1.pemilik.noHp << " | " << sepatuDian1.pemilik.email << "\n";
    cout << "  1. " << setw(13) << left << sepatuDian1.sepatu.merk
         << " (" << sepatuDian1.sepatu.tipeModel << ", " << sepatuDian1.sepatu.warna << ")"
         << " - Rp " << setw(10) << left << sepatuDian1.sepatu.harga
         << " | Beli: " << sepatuDian1.tanggal.tgl << "/" << sepatuDian1.tanggal.bln << "/" << sepatuDian1.tanggal.thn << "\n";

    cout << "\n========================================================================\n";
    cout << "                      AKHIR DOKUMENTASI DATA                            \n";
    cout << "========================================================================\n";

    return 0;
}
