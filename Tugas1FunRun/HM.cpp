/*
    Judul     : Pencatatan KM Splits Half-Marathon (ADT Struct)
    Deskripsi : Mencatat dan menghitung pace waktu per kilometer dari hasil lari
                setengah maraton menggunakan struct.
    Oleh      : Muhammad Fajri Setyawan
    NIM       : A11.2026.16638
*/

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// KAMUS GLOBAL (Definisi Tipe Data & Fungsi)
// ==========================================

// Struct untuk menampung nomor kilometer dan waktu/pace per km
struct SplitLari {
  int km;      // Penunjuk kilometer ke berapa (1, 2, dst)
  string pace; // Waktu tempuh per km dalam teks format "MM:SS"
};

// Fungsi konversi format pace "MM:SS" menjadi satuan detik
int paceKeDetik(string waktu) {
  int m = stoi(
      waktu.substr(0, 2)); // Potong 2 digit awal untuk menit, ubah ke angka
  int s = stoi(
      waktu.substr(3, 2)); // Potong 2 digit akhir untuk detik, ubah ke angka
  return (m * 60) + s;     // Hitung total detiknya
}

// Prosedur menampilkan format waktu marathon lengkap (Jam:Menit:Detik /
// HH:MM:SS)
void tampilkanWaktuLengkap(int totalDetik) {
  int jam = totalDetik / 3600;  // 1 jam = 3600 detik
  int sisa = totalDetik % 3600; // Sisa detik setelah diambil jam
  int menit = sisa / 60;        // Sisa tadi diubah jadi menit
  int detik = sisa % 60;        // Sisa akhir jadi detik

  // Cetak jam
  cout << jam << ":";

  // Jika menit di bawah 10 tambahkan 0 di depannya
  if (menit < 10)
    cout << "0";
  cout << menit << ":";

  // Jika detik di bawah 10 tambahkan 0 di depannya
  if (detik < 10)
    cout << "0";
  cout << detik;
}

// ==========================================
// DESKRIPSI (Program Utama / Main Program)
// ==========================================
int main() {
  // Array struct berisi rekapan pace lari dari KM 1 sampai KM 21 (Data dari
  // Strava)
  SplitLari daftarSplit[21] = {
      {1, "06:05"},  {2, "06:01"},  {3, "05:57"},  {4, "06:05"},  {5, "05:58"},
      {6, "06:04"},  {7, "05:58"},  {8, "05:57"},  {9, "06:05"},  {10, "06:01"},
      {11, "06:02"}, {12, "06:08"}, {13, "06:09"}, {14, "05:58"}, {15, "06:20"},
      {16, "06:13"}, {17, "06:20"}, {18, "06:17"}, {19, "06:26"}, {20, "06:47"},
      {21, "06:11"}};

  int totalDetik = 0; // Variabel akumulator untuk total seluruh waktu
  int totalKm = 21;   // Jumlah total jarak kilometer

  // Header rekap tabel
  cout << "========================================\n";
  cout << "       REKAP SPLIT HALF-MARATHON        \n";
  cout << "========================================\n";
  cout << "Kilometer\tPace (Waktu)\n";
  cout << "----------------------------------------\n";

  // Perulangan for untuk membaca data array split dari indeks 0 hingga 20
  for (int i = 0; i < totalKm; i++) {
    // Konversikan pace teks MM:SS milik KM saat ini ke detik
    int dtk = paceKeDetik(daftarSplit[i].pace);

    // Tambahkan detik KM ini ke totalDetik
    totalDetik = totalDetik + dtk;

    // Cetak kilometer dan pacenya ke layar
    cout << "KM " << daftarSplit[i].km << "\t\t" << daftarSplit[i].pace
         << " /km\n";
  }

  cout << "----------------------------------------\n";

  // Hitung rata-rata pace (total waktu detik dibagi 21 km)
  int rataPace = totalDetik / totalKm;

  // Tampilkan rangkuman total hasil lari
  cout << "Total Jarak      : 21 KM\n";
  cout << "Estimasi Waktu   : ";
  tampilkanWaktuLengkap(
      totalDetik); // Tampilkan total waktu dalam format jam:menit:detik
  cout << "\n";

  // Tampilkan rata-rata pace tempuh per kilometer
  cout << "Pace Rata-rata   : 0" << rataPace / 60 << ":"
       << (rataPace % 60 < 10 ? "0" : "") << rataPace % 60 << " /km\n";

  return 0; // Selesai
}