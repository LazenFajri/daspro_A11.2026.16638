/*
judul : analisis performa lari half marathon berbasis split pace

kamus :
    type RekapKm : <
        urutanKm : integer,
        tempo : string
    >
    catatanSplit[21] : RekapKm
    durasiTotalDetik, jarakTempuh, rerataPace : integer
    pos, konversiDetik : integer

diskripsi :
    durasiTotalDetik <-- 0
    jarakTempuh <-- 21

    // akumulasi total waktu per kilometer
    traversal (pos <-- 0 to jarakTempuh-1)
        konversiDetik <-- ubahTempoKeDetik(catatanSplit[pos].tempo)
        durasiTotalDetik <-- durasiTotalDetik + konversiDetik

    // hitung rata-rata pace per km
    rerataPace <-- durasiTotalDetik / jarakTempuh

    // tampilkan output perhitungan
    output(jarakTempuh)
    output(durasiTotalDetik)
    output(rerataPace)

Oleh : Muhammad Fajri Setyawan
NIM  : A11.2026.16638
*************************************************************/

#include <iostream>
#include <string>

using namespace std;

// kamus global: tipe data bentukan untuk split km
struct RekapKm {
  int urutanKm; // penanda km ke-n
  string tempo; // string tempo "MM:SS"
};

// fungsi konversi string "MM:SS" menjadi satuan detik
int ubahTempoKeDetik(string nilaiTempo) {
  int menit = stoi(nilaiTempo.substr(0, 2));
  int detik = stoi(nilaiTempo.substr(3, 2));
  return (menit * 60) + detik;
}

// prosedur konversi total detik ke format jam:menit:detik
void tampilkanWaktu(int waktuDetik) {
  int j = waktuDetik / 3600;
  int sisa = waktuDetik % 3600;
  int m = sisa / 60;
  int d = sisa % 60;

  cout << j << ":";
  if (m < 10)
    cout << "0";
  cout << m << ":";
  if (d < 10)
    cout << "0";
  cout << d;
}

// diskripsi program utama
int main() {
  // kamus lokal: data split km 1 sampai 21 dari strava
  RekapKm catatanSplit[21] = {
      {1, "06:05"},  {2, "06:01"},  {3, "05:57"},  {4, "06:05"},  {5, "05:58"},
      {6, "06:04"},  {7, "05:58"},  {8, "05:57"},  {9, "06:05"},  {10, "06:01"},
      {11, "06:02"}, {12, "06:08"}, {13, "06:09"}, {14, "05:58"}, {15, "06:20"},
      {16, "06:13"}, {17, "06:20"}, {18, "06:17"}, {19, "06:26"}, {20, "06:47"},
      {21, "06:11"}};

  int durasiTotalDetik = 0;
  int jarakTempuh = 21;

  // perulangan menghitung akumulasi waktu tempuh
  for (int pos = 0; pos < jarakTempuh; pos++) {
    int konversiDetik = ubahTempoKeDetik(catatanSplit[pos].tempo);
    durasiTotalDetik = durasiTotalDetik + konversiDetik;
  }

  // hitung rata-rata pace per km
  int rerataPace = durasiTotalDetik / jarakTempuh;

  // langsung tampilkan hasil perhitungan tanpa cetak tabel
  cout << "Hasil Kalkulasi Half-Marathon:\n";
  cout << "- Total Jarak    : " << jarakTempuh << " KM\n";
  cout << "- Total Durasi   : ";
  tampilkanWaktu(durasiTotalDetik);
  cout << " (" << durasiTotalDetik << " detik)\n";

  cout << "- Rata-rata Pace : 0" << rerataPace / 60 << ":"
       << (rerataPace % 60 < 10 ? "0" : "") << rerataPace % 60 << " /km ("
       << rerataPace << " detik/km)\n";

  return 0;
}