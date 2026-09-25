/*
    Judul     : Pencatatan Data Lari Circle Nadia (ADT Struct)
    Deskripsi : Menghitung selisih waktu/durasi lari per hari dan rata-rata
                durasi menggunakan konsep struct sederhana.
    Oleh      : Muhammad Fajri Setyawan
    NIM       : A11.2026.16638
*/

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// KAMUS GLOBAL (Definisi Tipe Data & Fungsi)
// ==========================================

// Definisi ADT Struct untuk menampung satu baris data kegiatan lari
struct KegiatanLari {
  string nama;           // Menyimpan nama orang yang lari
  string hari;           // Menyimpan hari lari (Senin, Rabu, dll)
  string waktuBerangkat; // Format jam mulai lari "HH:MM:SS"
  string waktuFinish;    // Format jam selesai lari "HH:MM:SS"
  double jarak;          // Jarak tempuh dalam satuan kilometer (km)
  string catatan;        // Keterangan kondisi (misal: cerah, macet)
};

// Fungsi untuk mengubah format teks jam "HH:MM:SS" menjadi total satuan detik
int konversiKeDetik(string waktu) {
  // substr(indeks_awal, panjang_karakter) dipakai untuk memotong teks
  // stoi dipakai untuk mengubah teks potongan tadi jadi angka (string to int)
  int jam = stoi(waktu.substr(0, 2));   // Ambil 2 angka pertama (jam)
  int menit = stoi(waktu.substr(3, 2)); // Ambil 2 angka tengah (menit)
  int detik = stoi(waktu.substr(6, 2)); // Ambil 2 angka terakhir (detik)

  // Rumus: 1 jam = 3600 detik, 1 menit = 60 detik
  return (jam * 3600) + (menit * 60) + detik;
}

// Prosedur untuk mencetak total detik kembali ke tampilan menit:detik (MM:SS)
void cetakWaktu(int detik) {
  int m = detik / 60; // Menghitung jumlah menit
  int s = detik % 60; // Sisa bagi untuk mencari sisa detiknya

  // Menambahkan angka '0' di depan jika angka satuan (di bawah 10) biar rapi
  if (m < 10)
    cout << "0";
  cout << m << ":";

  if (s < 10)
    cout << "0";
  cout << s;
}

// ==========================================
// DESKRIPSI (Program Utama / Main Program)
// ==========================================
int main() {
  // Array struct untuk menyimpan 3 data lari Nadia (Senin, Rabu, Jumat)
  KegiatanLari dataLari[3] = {
      {"Nadia", "Senin", "07:10:00", "07:38:20", 2.5, "Cuaca cerah"},
      {"Nadia", "Rabu", "07:12:00", "07:41:10", 2.6, "Sedikit ramai"},
      {"Nadia", "Jumat", "07:15:30", "07:45:30", 2.5, "Lancar"}};

  // Variabel penampung akumulasi waktu dan jumlah baris data
  int totalDetik = 0;
  int jumlahData = 3;

  // Menampilkan judul header tabel
  cout << "===================================================================="
          "====\n";
  cout << "                    DATA LAPORAN LARI NADIA                         "
          "    \n";
  cout << "===================================================================="
          "====\n";
  cout << "Hari\tBerangkat\tFinish\t\tDurasi\t\tJarak\tCatatan\n";
  cout << "--------------------------------------------------------------------"
          "----\n";

  // Perulangan for untuk membaca data satu per satu dari urutan index ke-0
  // sampai ke-2
  for (int i = 0; i < jumlahData; i++) {
    // Konversi jam mulai dan jam selesai ke satuan detik
    int dtkMulai = konversiKeDetik(dataLari[i].waktuBerangkat);
    int dtkSelesai = konversiKeDetik(dataLari[i].waktuFinish);

    // Durasi didapat dari waktu selesai dikurangi waktu berangkat
    int durasi = dtkSelesai - dtkMulai;

    // Tambahkan durasi hari ini ke total keseluruhan waktu
    totalDetik = totalDetik + durasi;

    // Cetak baris data per hari ke layar konsol
    cout << dataLari[i].hari << "\t" << dataLari[i].waktuBerangkat << "\t"
         << dataLari[i].waktuFinish << "\t";
    cetakWaktu(durasi); // Menampilkan durasi dalam format MM:SS
    cout << "\t\t" << dataLari[i].jarak << " km\t" << dataLari[i].catatan
         << endl;
  }

  cout << "--------------------------------------------------------------------"
          "----\n";

  // Menghitung rata-rata waktu (total detik dibagi 3 hari)
  int rataRata = totalDetik / jumlahData;

  // Menampilkan hasil ringkasan perhitungan
  cout << "\nHasil Perhitungan:\n";
  cout << "- Total waktu lari : " << totalDetik << " detik (";
  cetakWaktu(totalDetik);
  cout << ")\n";

  cout << "- Rata-rata lari   : " << rataRata << " detik (";
  cetakWaktu(rataRata);
  cout << ")\n";

  return 0; // Menandakan program selesai berjalan normal
}