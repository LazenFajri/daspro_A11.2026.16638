// ============================================================
// PROGRAM       : INVENTARISASI KOLEKSI KENDARAAN
// TENTANG       : Pengelolaan koleksi unit kendaraan bermotor
//                 menggunakan Abstract Data Type (ADT Struct)
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
struct Kendaraan {
    string namaKendaraan;
    string merek;
    string tipeModel;
    string warna;
    int tahun;
    int kapasitas;
    string bahanBakar;
    double hargaBeli;
    double nilaiSekarang;
    string fungsi;
    bool statusAktif;
};

Kendaraan garasi[4];
int jumlahUnit;
int i;
double totalBeli;
double totalSekarang;
double penyusutan;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    jumlahUnit    = 4;
    totalBeli     = 0;
    totalSekarang = 0;

    // Inisialisasi Data Mobil
    garasi[0].namaKendaraan = "Mobil";
    garasi[0].merek         = "Toyota";
    garasi[0].tipeModel     = "Rush";
    garasi[0].warna         = "Putih";
    garasi[0].tahun         = 2022;
    garasi[0].kapasitas     = 1500;
    garasi[0].bahanBakar    = "Bensin";
    garasi[0].hargaBeli     = 280000000;
    garasi[0].nilaiSekarang = 230000000;
    garasi[0].fungsi        = "Bepergian jauh bersama keluarga";
    garasi[0].statusAktif   = true;

    // Inisialisasi Data Motor Sport
    garasi[1].namaKendaraan = "Motor";
    garasi[1].merek         = "Honda";
    garasi[1].tipeModel     = "CBR250RR";
    garasi[1].warna         = "Merah";
    garasi[1].tahun         = 2021;
    garasi[1].kapasitas     = 250;
    garasi[1].bahanBakar    = "Bensin";
    garasi[1].hargaBeli     = 95000000;
    garasi[1].nilaiSekarang = 78000000;
    garasi[1].fungsi        = "Hobi dan touring akhir pekan";
    garasi[1].statusAktif   = true;

    // Inisialisasi Data Motor Matik
    garasi[2].namaKendaraan = "Motor";
    garasi[2].merek         = "Yamaha";
    garasi[2].tipeModel     = "NMAX";
    garasi[2].warna         = "Hitam Doff";
    garasi[2].tahun         = 2023;
    garasi[2].kapasitas     = 155;
    garasi[2].bahanBakar    = "Bensin";
    garasi[2].hargaBeli     = 33000000;
    garasi[2].nilaiSekarang = 28000000;
    garasi[2].fungsi        = "Transportasi kuliah harian";
    garasi[2].statusAktif   = true;

    // Inisialisasi Data Motor Klasik
    garasi[3].namaKendaraan = "Motor";
    garasi[3].merek         = "Vespa";
    garasi[3].tipeModel     = "Primavera";
    garasi[3].warna         = "Cream";
    garasi[3].tahun         = 2020;
    garasi[3].kapasitas     = 150;
    garasi[3].bahanBakar    = "Bensin";
    garasi[3].hargaBeli     = 55000000;
    garasi[3].nilaiSekarang = 46000000;
    garasi[3].fungsi        = "Santai dan kumpul komunitas";
    garasi[3].statusAktif   = true;

    // Pemrosesan kalkulasi total
    for (i = 0; i < jumlahUnit; i++) {
        totalBeli     += garasi[i].hargaBeli;
        totalSekarang += garasi[i].nilaiSekarang;
    }
    penyusutan = totalBeli - totalSekarang;

    // Penayangan Laporan Terstruktur
    cout << fixed << setprecision(0);
    cout << "========================================================================" << endl;
    cout << "                   SISTEM MANAJEMEN ASET KENDARAAN                      " << endl;
    cout << "========================================================================" << endl;
    cout << "Penyusun : Muhammad Fajri Setyawan" << endl;
    cout << "NIM      : A11.2026.16638" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (i = 0; i < jumlahUnit; i++) {
        cout << "[ Unit " << (i + 1) << " : " << garasi[i].merek << " " << garasi[i].tipeModel << " ]" << endl;
        cout << "  Jenis Kendaraan: " << garasi[i].namaKendaraan << " (" << garasi[i].kapasitas << " cc)" << endl;
        cout << "  Tahun / Warna  : " << garasi[i].tahun << " / " << garasi[i].warna << endl;
        cout << "  Fungsi Utama   : " << garasi[i].fungsi << endl;
        cout << "  Harga Beli     : Rp " << garasi[i].hargaBeli << endl;
        cout << "  Nilai Taksiran : Rp " << garasi[i].nilaiSekarang << endl;
        cout << "  Status Armada  : " << (garasi[i].statusAktif ? "Aktif Beroperasi" : "Tidak Aktif") << endl;
        cout << "------------------------------------------------------------------------" << endl;
    }

    cout << "\n========================================================================" << endl;
    cout << "                       RINGKASAN VALUASI KENDARAAN                      " << endl;
    cout << "========================================================================" << endl;
    cout << " Total Nilai Perolehan Awal : Rp " << totalBeli << endl;
    cout << " Total Estimasi Nilai Kini  : Rp " << totalSekarang << endl;
    cout << " Total Selisih / Depresiasi : Rp " << penyusutan << endl;
    cout << "========================================================================" << endl;

    return 0;
}
