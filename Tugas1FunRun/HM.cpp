/*
    Judul     : Perhitungan KM Splits Half-Marathon (ADT Struct)
    Deskripsi : Menghitung total durasi dan rata-rata pace dari KM 1 hingga 21
                berdasarkan alur notasi algoritmik.
    Oleh      : Muhammad Fajri Setyawan
    NIM       : A11.2026.16638

    ========================================================================
    NOTASI PEMBAHASAN / ALUR LOGIKA (ALGORITMA):
    ========================================================================
    1. DEFINISI TIPE DATA:
       - Buat struct 'SplitLari' berisi: km (integer) dan pace (string MM:SS).

    2. FUNGSI KONVERSI PACE:
       - Input string pace "MM:SS".
       - Potong menit (indeks 0..1) dan detik (indeks 3..4).
       - Ubah string menjadi nilai integer.
       - Kembalikan nilai total detik: (menit * 60) + detik.

    3. PROGRAM UTAMA (MAIN):
       - Inisialisasi array struct berisi 21 data split kilometer marathon.
       - Inisialisasi 'totalDetik' = 0 dan 'totalKm' = 21.
       - Lakukan perulangan (loop) dari indeks 0 hingga 20:
           a. Ubah pace string KM saat ini ke satuan detik -> dtk.
           b. Tambahkan ke total akumulasi: totalDetik = totalDetik + dtk.
       - Hitung rata-rata pace per KM: rataPace = totalDetik / totalKm.
       - Tampilkan langsung hasil akhir total waktu tempuh (HH:MM:SS)
         dan rata-rata pace (MM:SS) ke layar.
    ========================================================================
*/

#include <iostream>
#include <string>

using namespace std;

// ========================================================
// KAMUS GLOBAL
// ========================================================

// Definisi struct
struct SplitLari {
  int km;
  string pace; // format MM:SS
};

// Fungsi konversi format pace MM:SS ke detik
int paceKeDetik(string waktu) {
  int m = stoi(waktu.substr(0, 2));
  int s = stoi(waktu.substr(3, 2));

  return (m * 60) + s;
}

// Prosedur menampilkan format HH:MM:SS
void tampilkanWaktuLengkap(int totalDetik) {
  int jam = totalDetik / 3600;
  int sisa = totalDetik % 3600;
  int menit = sisa / 60;
  int detik = sisa % 60;

  cout << jam << ":";
  if (menit < 10)
    cout << "0";
  cout << menit << ":";
  if (detik < 10)
    cout << "0";
  cout << detik;
}

// ========================================================
// DESKRIPSI
// ========================================================
int main() {
  // Inisialisasi data split KM 1 - 21
  SplitLari daftarSplit[21] = {
      {1, "06:05"},  {2, "06:01"},  {3, "05:57"},  {4, "06:05"},  {5, "05:58"},
      {6, "06:04"},  {7, "05:58"},  {8, "05:57"},  {9, "06:05"},  {10, "06:01"},
      {11, "06:02"}, {12, "06:08"}, {13, "06:09"}, {14, "05:58"}, {15, "06:20"},
      {16, "06:13"}, {17, "06:20"}, {18, "06:17"}, {19, "06:26"}, {20, "06:47"},
      {21, "06:11"}};

  int totalDetik = 0;
  int totalKm = 21;

  // Perhitungan di balik layar tanpa mencetak tabel
  for (int i = 0; i < totalKm; i++) {
    int dtk = paceKeDetik(daftarSplit[i].pace);
    totalDetik = totalDetik + dtk;
  }

  // Menghitung rata-rata pace per KM
  int rataPace = totalDetik / totalKm;

  // Tampilkan hasil akhir
  cout << "Hasil Perhitungan Half-Marathon:\n";
  cout << "- Total Jarak      : " << totalKm << " KM\n";
  cout << "- Total Waktu      : ";
  tampilkanWaktuLengkap(totalDetik);
  cout << " (" << totalDetik << " detik)\n";

  cout << "- Pace Rata-rata   : 0" << rataPace / 60 << ":"
       << (rataPace % 60 < 10 ? "0" : "") << rataPace % 60 << " /km ("
       << rataPace << " detik/km)\n";

  return 0;
}