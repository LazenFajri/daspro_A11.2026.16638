/*
judul : rekapitulasi durasi jogging nadia 5 hari

kamus :
    type CatatanJogging : <
        hari : string,
        tgl : string,
        jamAwal : string,
        jamAkhir : string,
        jarakKm : real,
        kondisi : string
    >
    aktivitas[5] : CatatanJogging
    totalWaktuDetik, jmlHari, rataDetik : integer
    idx, awal, akhir, selisih : integer

diskripsi :
    totalWaktuDetik <-- 0
    jmlHari <-- 5

    // hitung total detik berjalan
    traversal (idx <-- 0 to jmlHari-1)
        awal <-- hitungDetikTotal(aktivitas[idx].jamAwal)
        akhir <-- hitungDetikTotal(aktivitas[idx].jamAkhir)
        selisih <-- akhir - awal
        totalWaktuDetik <-- totalWaktuDetik + selisih

    // hitung nilai rata-rata durasi
    rataDetik <-- totalWaktuDetik / jmlHari

    // output data
    output(totalWaktuDetik)
    output(jmlHari)
    output(rataDetik)

Oleh : Muhammad Fajri Setyawan
NIM  : A11.2026.16638
*************************************************************/

#include <iostream>
#include <string>

using namespace std;

// kamus global
struct CatatanJogging {
  string hari;
  string tgl;
  string jamAwal;
  string jamAkhir;
  double jarakKm;
  string kondisi;
};

// fungsi mengubah waktu string "HH:MM:SS" jadi total detik
int hitungDetikTotal(string teksJam) {
  int hh = stoi(teksJam.substr(0, 2));
  int mm = stoi(teksJam.substr(3, 2));
  int ss = stoi(teksJam.substr(6, 2));
  return (hh * 3600) + (mm * 60) + ss;
}

// prosedur memformat detik jadi string MM:SS
void cetakFormatMenitDetik(int nilaiDetik) {
  int mnt = nilaiDetik / 60;
  int dtk = nilaiDetik % 60;

  if (mnt < 10)
    cout << "0";
  cout << mnt << ":";
  if (dtk < 10)
    cout << "0";
  cout << dtk;
}

// diskripsi program utama
int main() {
  // kamus lokal: data 5 hari lari nadia
  CatatanJogging aktivitas[5] = {
      {"Senin", "1 Sep 2025", "07:10:00", "07:38:20", 2.5, "Cuaca cerah"},
      {"Selasa", "2 Sep 2025", "07:12:30", "07:41:15", 2.5, "Sedikit ramai"},
      {"Rabu", "3 Sep 2025", "07:05:45", "07:33:50", 2.5, "Lancar"},
      {"Kamis", "4 Sep 2025", "07:15:20", "07:44:10", 2.5, "Sedikit hujan"},
      {"Jumat", "5 Sep 2025", "07:08:10", "07:36:40", 2.5, "Lancar"}};

  int totalWaktuDetik = 0;
  int jmlHari = 5;

  // perulangan kalkulasi akumulasi detik tanpa cetak tabel
  for (int idx = 0; idx < jmlHari; idx++) {
    int awal = hitungDetikTotal(aktivitas[idx].jamAwal);
    int akhir = hitungDetikTotal(aktivitas[idx].jamAkhir);
    int selisih = akhir - awal;

    totalWaktuDetik = totalWaktuDetik + selisih;
  }

  // hitung rata-rata
  int rataDetik = totalWaktuDetik / jmlHari;

  // cetak ringkasan output
  cout << "Hasil Perhitungan Lari 5 Hari:\n";
  cout << "- Total akumulasi waktu : " << totalWaktuDetik << " detik (";
  cetakFormatMenitDetik(totalWaktuDetik);
  cout << ")\n";

  cout << "- Rata-rata per hari    : " << rataDetik << " detik (";
  cetakFormatMenitDetik(rataDetik);
  cout << ")\n";

  return 0;
}