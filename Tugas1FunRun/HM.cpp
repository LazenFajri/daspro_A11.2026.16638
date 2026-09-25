/*
    Judul     : Rekap KM Splits Half-Marathon (ADT Struct)
    Deskripsi : Menghitung total durasi dan rata-rata pace dari KM 1 hingga 21
                berdasarkan urutan kilometer lari asli secara langsung tanpa
   sorting. Oleh      : Muhammad Fajri Setyawan NIM       : A11.2026.16638
*/

#include <iostream>
#include <string>

using namespace std;

// ========================================================
// KAMUS GLOBAL (Tipe Data Buatan & Deklarasi Fungsi)
// ========================================================

// Mendefinisikan struct untuk menyimpan data tiap kilometer
struct SplitLari {
  int km;      // Nomor kilometer (1, 2, 3, dst.)
  string pace; // Waktu tempuh per km dalam format teks "MM:SS"
};

// Fungsi untuk mengonversi format teks pace "MM:SS" ke total detik
int paceKeDetik(string waktu) {
  // Ambil 2 digit pertama untuk nilai menit lalu ubah ke int
  int m = stoi(waktu.substr(0, 2));
  // Ambil 2 digit kedua untuk nilai detik lalu ubah ke int
  int s = stoi(waktu.substr(3, 2));

  // Rumus konversi pace: menit dikalikan 60 ditambah detik
  return (m * 60) + s;
}

// Prosedur untuk menampilkan waktu lengkap format jam:menit:detik (HH:MM:SS)
void tampilkanWaktuLengkap(int totalDetik) {
  int jam = totalDetik / 3600;  // Menghitung total jam (3600 detik per jam)
  int sisa = totalDetik % 3600; // Mendapatkan sisa detik setelah diambil jam
  int menit = sisa / 60;        // Sisa detik diubah menjadi nilai menit
  int detik = sisa % 60;        // Sisa pembagian akhir adalah satuan detik

  // Cetak nilai jam
  cout << jam << ":";

  // Tambahkan angka 0 di depan jika nilai menit kurang dari 10
  if (menit < 10)
    cout << "0";
  cout << menit << ":";

  // Tambahkan angka 0 di depan jika nilai detik kurang dari 10
  if (detik < 10)
    cout << "0";
  cout << detik;
}

// ========================================================
// DESKRIPSI (Program Utama / Eksekusi)
// ========================================================
int main() {
  // Menyimpan 21 data split kilometer lari murni berurutan sesuai rute lari
  SplitLari daftarSplit[21] = {
      {1, "06:05"},  {2, "06:01"},  {3, "05:57"},  {4, "06:05"},  {5, "05:58"},
      {6, "06:04"},  {7, "05:58"},  {8, "05:57"},  {9, "06:05"},  {10, "06:01"},
      {11, "06:02"}, {12, "06:08"}, {13, "06:09"}, {14, "05:58"}, {15, "06:20"},
      {16, "06:13"}, {17, "06:20"}, {18, "06:17"}, {19, "06:26"}, {20, "06:47"},
      {21, "06:11"}};

  // Variabel akumulator untuk menjumlahkan semua detik pace
  int totalDetik = 0;
  // Variabel total jarak kilometer yang ditempuh
  int totalKm = 21;

  // Header tabel rekapitulasi data
  cout << "========================================\n";
  cout << "       REKAP SPLIT HALF-MARATHON        \n";
  cout << "========================================\n";
  cout << "Kilometer\tPace (Waktu)\n";
  cout << "----------------------------------------\n";

  // Looping berurutan dari KM 1 (indeks 0) sampai KM 21 (indeks 20)
  for (int i = 0; i < totalKm; i++) {
    // Konversi pace teks "MM:SS" pada kilometer saat ini ke detik
    int dtk = paceKeDetik(daftarSplit[i].pace);

    // Akumulasikan ke total detik
    totalDetik = totalDetik + dtk;

    // Tampilkan nomor kilometer dan waktu pacenya ke layar
    cout << "KM " << daftarSplit[i].km << "\t\t" << daftarSplit[i].pace
         << " /km\n";
  }

  cout << "----------------------------------------\n";

  // Hitung rata-rata pace (total keseluruhan detik dibagi 21 kilometer)
  int rataPace = totalDetik / totalKm;

  // Menampilkan total jarak tempuh
  cout << "Total Jarak      : 21 KM\n";

  // Menampilkan total durasi waktu yang dihabiskan
  cout << "Total Waktu      : ";
  tampilkanWaktuLengkap(totalDetik);
  cout << "\n";

  // Menampilkan rata-rata pace per kilometer (menit dan sisa detiknya)
  cout << "Pace Rata-rata   : 0" << rataPace / 60 << ":"
       << (rataPace % 60 < 10 ? "0" : "") << rataPace % 60 << " /km\n";

  return 0; // Mengindikasikan program berhasil berjalan normal
}