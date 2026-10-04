// ============================================================
// PROGRAM       : ESTIMASI TINGGI GEDUNG UDINUS
// TENTANG       : Menghitung taksiran ketinggian beberapa gedung
//                 kampus UDINUS menggunakan kaidah trigonometri.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

// ============================================================
// KAMUS
// Pendefinisian tipe data bentukan (struct) serta variabel global
// ============================================================
struct DataUkurGedung {
  string namaGedung;
  string lokasiTitik;
  double jarakDatar;   // dalam meter
  double sudutDerajat; // dalam derajat (°)
  double sudutRadian;  // hasil konversi derajat ke radian
  double tinggiGedung; // hasil estimasi tinggi dalam meter
};

DataUkurGedung dataPengukuran[3];
int jumlahData;
int i;
const double PI = 3.141592653589793;

// ============================================================
// DISKRIPSI
// ============================================================
int main() {
  // --------------------------------------------------------
  // Inisialisasi batasan data dan sampel pengukuran empiris
  // --------------------------------------------------------
  jumlahData = 3;

  // Sampel 1: Gedung Rektorat
  dataPengukuran[0].namaGedung = "Gedung Rektorat UDINUS";
  dataPengukuran[0].lokasiTitik = "Pelataran Utama";
  dataPengukuran[0].jarakDatar = 30.0;
  dataPengukuran[0].sudutDerajat = 38.0;

  // Sampel 2: Gedung H
  dataPengukuran[1].namaGedung = "Gedung H UDINUS";
  dataPengukuran[1].lokasiTitik = "Kawasan Parkir Barat";
  dataPengukuran[1].jarakDatar = 25.0;
  dataPengukuran[1].sudutDerajat = 35.7;

  // Sampel 3: Gedung I
  dataPengukuran[2].namaGedung = "Gedung I UDINUS";
  dataPengukuran[2].lokasiTitik = "Depan Selasar Fasilkom";
  dataPengukuran[2].jarakDatar = 20.0;
  dataPengukuran[2].sudutDerajat = 36.9;

  // --------------------------------------------------------
  // Pemrosesan matematis (Transformasi Radian & Tangen)
  // --------------------------------------------------------
  for (i = 0; i < jumlahData; i++) {
    // Konversi sudut derajat ke bentuk radian
    dataPengukuran[i].sudutRadian =
        dataPengukuran[i].sudutDerajat * (PI / 180.0);

    // Komputasi ketinggian: tinggi = jarak * tan(sudut_radian)
    dataPengukuran[i].tinggiGedung =
        dataPengukuran[i].jarakDatar * tan(dataPengukuran[i].sudutRadian);
  }

  // --------------------------------------------------------
  // Output penyajian rekapitulasi data pengamatan
  // --------------------------------------------------------
  cout << fixed << setprecision(2);
  cout << "===================================================================="
          "\n";
  cout << "            REKAPITULASI PENGUKURAN KETINGGIAN GEDUNG               "
          "\n";
  cout << "                   UNIVERSITAS DIAN NUSWANTORO                      "
          "\n";
  cout << "===================================================================="
          "\n";
  cout << "Oleh : Muhammad Fajri Setyawan\n";
  cout << "NIM  : A11.2026.16638\n";
  cout << "--------------------------------------------------------------------"
          "\n\n";

  for (i = 0; i < jumlahData; i++) {
    cout << "[ Pengukuran Objek " << (i + 1) << " ]" << endl;
    cout << "  Gedung Target      : " << dataPengukuran[i].namaGedung << endl;
    cout << "  Titik Pengamatan   : " << dataPengukuran[i].lokasiTitik << endl;
    cout << "  Jarak Horizontal   : " << dataPengukuran[i].jarakDatar
         << " meter" << endl;
    cout << "  Sudut Kemiringan   : " << dataPengukuran[i].sudutDerajat
         << " derajat" << endl;
    cout << "  Estimasi Ketinggian: " << dataPengukuran[i].tinggiGedung
         << " meter" << endl;
    cout << "------------------------------------------------------------------"
            "--"
         << endl;
  }

  cout << "\nCatatan: Hasil ketinggian di atas diperoleh dari formulasi sudut "
          "elevasi"
       << endl;
  cout << "         dengan toleransi ketinggian sudut pandang "
          "instrumen/pengamat."
       << endl;
  cout << "===================================================================="
       << endl;

  return 0;
}