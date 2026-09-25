/*
judul : perhitungan durasi dan rata-rata lari nadia

kamus :
    type KegiatanLari : <
        nama : string,
        hari : string,
        waktuBerangkat : string,
        waktuFinish : string,
        jarak : real,
        catatan : string
    >
    dataLari[3] : KegiatanLari
    totalDetik, jumlahData, rataRata : integer
    i, dtkMulai, dtkSelesai, durasi : integer

diskripsi :
    // inisialisasi data lari nadia (3 hari)
    totalDetik <-- 0
    jumlahData <-- 3

    // proses perulangan hitung selisih waktu
    traversal (i <-- 0 to jumlahData-1)
        dtkMulai <-- konversiKeDetik(dataLari[i].waktuBerangkat)
        dtkSelesai <-- konversiKeDetik(dataLari[i].waktuFinish)
        durasi <-- dtkSelesai - dtkMulai
        totalDetik <-- totalDetik + durasi

    // hitung rata-rata
    rataRata <-- totalDetik / jumlahData

    // output hasil perhitungan
    output(totalDetik)
    output(rataRata)

Oleh : Muhammad Fajri Setyawan
NIM  : A11.2026.16638
*************************************************************/

#include <iostream>
#include <string>

using namespace std;

// kamus global
struct KegiatanLari {
  string nama;
  string hari;
  string waktuBerangkat;
  string waktuFinish;
  double jarak;
  string catatan;
};

// fungsi konversi string ke detik
int konversiKeDetik(string waktu) {
  int jam = stoi(waktu.substr(0, 2));
  int menit = stoi(waktu.substr(3, 2));
  int detik = stoi(waktu.substr(6, 2));
  return (jam * 3600) + (menit * 60) + detik;
}

// prosedur cetak waktu mm:ss
void cetakWaktu(int detik) {
  int m = detik / 60;
  int s = detik % 60;
  if (m < 10)
    cout << "0";
  cout << m << ":";
  if (s < 10)
    cout << "0";
  cout << s;
}

// diskripsi program utama
int main() {
  // kamus lokal
  KegiatanLari dataLari[3] = {
      {"Nadia", "Senin", "07:10:00", "07:38:20", 2.5, "Cuaca cerah"},
      {"Nadia", "Rabu", "07:12:00", "07:41:10", 2.6, "Sedikit ramai"},
      {"Nadia", "Jumat", "07:15:30", "07:45:30", 2.5, "Lancar"}};

  int totalDetik = 0;
  int jumlahData = 3;

  // proses hitung total durasi
  for (int i = 0; i < jumlahData; i++) {
    int dtkMulai = konversiKeDetik(dataLari[i].waktuBerangkat);
    int dtkSelesai = konversiKeDetik(dataLari[i].waktuFinish);
    int durasi = dtkSelesai - dtkMulai;

    totalDetik = totalDetik + durasi;
  }

  // hitung rata-rata
  int rataRata = totalDetik / jumlahData;

  // output hasil perhitungan
  cout << "Hasil Perhitungan:\n";
  cout << "- Total waktu lari : " << totalDetik << " detik (";
  cetakWaktu(totalDetik);
  cout << ")\n";

  cout << "- Rata-rata lari   : " << rataRata << " detik (";
  cetakWaktu(rataRata);
  cout << ")\n";

  return 0;
}