// ============================================================
// PROGRAM       : INVENTARIS BARANG PRIBADI MAHASISWA
// TENTANG       : Mencatat, menyimpan, dan merekapitulasi total
//                 biaya perolehan serta valuasi aset mahasiswa.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// Pendefinisian struktur representasi barang dan variabel program
// ============================================================
struct BarangPribadi {
    string namaBarang;
    string kategori;
    string merek;
    int tahunPeroleh;
    double hargaPeroleh;
    double nilaiSaatIni;
};

BarangPribadi daftarBarang[5];
double totalPerolehan;
double totalNilaiKini;
double selisihNilai;
int jumlahData;
int i;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // Inisialisasi awal nilai komputasi
    // --------------------------------------------------------
    totalPerolehan = 0.0;
    totalNilaiKini = 0.0;
    jumlahData     = 5;

    // --------------------------------------------------------
    // Pengisian data barang inventaris pribadi mahasiswa
    // --------------------------------------------------------
    // Barang 1: Laptop
    daftarBarang[0].namaBarang   = "MacBook Air M1";
    daftarBarang[0].kategori     = "Laptop";
    daftarBarang[0].merek        = "Apple";
    daftarBarang[0].tahunPeroleh = 2022;
    daftarBarang[0].hargaPeroleh = 12500000;
    daftarBarang[0].nilaiSaatIni = 9000000;

    // Barang 2: Kendaraan
    daftarBarang[1].namaBarang   = "Vario 150";
    daftarBarang[1].kategori     = "Kendaraan";
    daftarBarang[1].merek        = "Honda";
    daftarBarang[1].tahunPeroleh = 2021;
    daftarBarang[1].hargaPeroleh = 21000000;
    daftarBarang[1].nilaiSaatIni = 15500000;

    // Barang 3: Handphone
    daftarBarang[2].namaBarang   = "Redmi Note 12 Pro";
    daftarBarang[2].kategori     = "Handphone";
    daftarBarang[2].merek        = "Xiaomi";
    daftarBarang[2].tahunPeroleh = 2023;
    daftarBarang[2].hargaPeroleh = 4500000;
    daftarBarang[2].nilaiSaatIni = 3000000;

    // Barang 4: Sepatu
    daftarBarang[3].namaBarang   = "Nike Air Force 1";
    daftarBarang[3].kategori     = "Sepatu";
    daftarBarang[3].merek        = "Nike";
    daftarBarang[3].tahunPeroleh = 2024;
    daftarBarang[3].hargaPeroleh = 1500000;
    daftarBarang[3].nilaiSaatIni = 1000000;

    // Barang 5: Tas
    daftarBarang[4].namaBarang   = "Backpack Wanderer";
    daftarBarang[4].kategori     = "Tas";
    daftarBarang[4].merek        = "Eiger";
    daftarBarang[4].tahunPeroleh = 2023;
    daftarBarang[4].hargaPeroleh = 750000;
    daftarBarang[4].nilaiSaatIni = 250000;

    // --------------------------------------------------------
    // Proses perhitungan total perolehan dan nilai saat ini
    // --------------------------------------------------------
    for (i = 0; i < jumlahData; i++) {
        totalPerolehan += daftarBarang[i].hargaPeroleh;
        totalNilaiKini += daftarBarang[i].nilaiSaatIni;
    }

    // Perhitungan selisih penyusutan nilai barang
    selisihNilai = totalPerolehan - totalNilaiKini;

    // --------------------------------------------------------
    // Output tampilan user friendly
    // --------------------------------------------------------
    cout << fixed << setprecision(0);

    cout << "========================================================================\n";
    cout << "              INVENTARIS NILAI BARANG PRIBADI MAHASISWA                 \n";
    cout << "========================================================================\n";
    cout << "Pencatat : Muhammad Fajri Setyawan\n";
    cout << "NIM      : A11.2026.16638\n";
    cout << "------------------------------------------------------------------------\n\n";

    for (i = 0; i < jumlahData; i++) {
        cout << "[ Data Barang " << (i + 1) << " ]" << endl;
        cout << "  Nama Barang      : " << daftarBarang[i].namaBarang << endl;
        cout << "  Kategori         : " << daftarBarang[i].kategori << endl;
        cout << "  Merek            : " << daftarBarang[i].merek << endl;
        cout << "  Tahun Diperoleh  : " << daftarBarang[i].tahunPeroleh << endl;
        cout << "  Harga Pembelian  : Rp " << daftarBarang[i].hargaPeroleh << endl;
        cout << "  Estimasi Saat Ini: Rp " << daftarBarang[i].nilaiSaatIni << endl;
        cout << "------------------------------------------------------------------------\n";
    }

    cout << "\n========================================================================\n";
    cout << "                     RINGKASAN TOTAL NILAI EKONOMI                      \n";
    cout << "========================================================================\n";
    cout << " Total Uang yang Pernah Dikeluarkan : Rp " << totalPerolehan << endl;
    cout << " Total Nilai Barang Saat Ini        : Rp " << totalNilaiKini << endl;
    cout << " Selisih Nilai (Depresiasi)         : Rp " << selisihNilai << endl;
    cout << "========================================================================\n";

    return 0;
}
