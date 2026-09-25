/*
judul : perhitungan total waktu dan pace rata-rata half marathon

kamus :
    type SplitLari : <
        km : integer,
        pace : string
    >
    daftarSplit[21] : SplitLari
    totalDetik, totalKm, rataPace : integer
    i, dtk : integer

diskripsi :
    // inisialisasi data split marathon
    totalDetik <-- 0
    totalKm <-- 21

    // akumulasi total detik dari setiap km
    traversal (i <-- 0 to totalKm-1)
        dtk <-- paceKeDetik(daftarSplit[i].pace)
        totalDetik <-- totalDetik + dtk

    // hitung rata-rata pace per km
    rataPace <-- totalDetik / totalKm

    // output hasil akhir
    output(totalKm)
    output(totalDetik)
    output(rataPace)

Oleh : Muhammad Fajri Setyawan
NIM  : A11.2026.16638
*************************************************************/

#include <iostream>
#include <string>

using namespace std;

// kamus global
struct SplitLari {
  int km;
  string pace;
};

// fungsi konversi pace mm:ss ke detik
int paceKeDetik(string waktu) {
  int m = stoi(waktu.substr(0, 2));
  int s = stoi(waktu.substr(3, 2));
  return (m * 60) + s;
}

// prosedur cetak waktu format hh:mm:ss
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

// diskripsi program utama
int main() {
  // kamus lokal
  SplitLari daftarSplit[21] = {
      {1, "06:05"},  {2, "06:01"},  {3, "05:57"},  {4, "06:05"},  {5, "05:58"},
      {6, "06:04"},  {7, "05:58"},  {8, "05:57"},  {9, "06:05"},  {10, "06:01"},
      {11, "06:02"}, {12, "06:08"}, {13, "06:09"}, {14, "05:58"}, {15, "06:20"},
      {16, "06:13"}, {17, "06:20"}, {18, "06:17"}, {19, "06:26"}, {20, "06:47"},
      {21, "06:11"}};

  int totalDetik = 0;
  int totalKm = 21;

  // proses akumulasi detik per km
  for (int i = 0; i < totalKm; i++) {
    int dtk = paceKeDetik(daftarSplit[i].pace);
    totalDetik = totalDetik + dtk;
  }

  // hitung rata-rata pace
  int rataPace = totalDetik / totalKm;

  // output hasil perhitungan
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