/*
    Judul     : Perhitungan Data Lari Nadia (ADT Struct)
    Deskripsi : Menghitung total waktu dan rata-rata durasi lari 3 hari
                berdasarkan alur notasi algoritmik.
    Oleh      : Muhammad Fajri Setyawan
    NIM       : A11.2026.16638

    ========================================================================
    NOTASI PEMBAHASAN / ALUR LOGIKA (ALGORITMA):
    ========================================================================
    1. DEFINISI TIPE DATA:
       - Buat struct 'KegiatanLari' berisi: nama, hari, waktuBerangkat,
         waktuFinish, jarak, dan catatan.

    2. FUNGSI KONVERSI WAKTU:
       - Input string "HH:MM:SS".
       - Potong jam (indeks 0..1), menit (indeks 3..4), detik (indeks 6..7).
       - Ubah teks potongan jadi angka bulat (integer).
       - Kembalikan nilai: (jam * 3600) + (menit * 60) + detik.

    3. PROGRAM UTAMA (MAIN):
       - Inisialisasi array struct berisi 3 data lari Nadia (Senin, Rabu,
   Jumat).
       - Inisialisasi 'totalDetik' = 0 dan 'jumlahData' = 3.
       - Lakukan perulangan (loop) dari data ke-0 sampai ke-2:
           a. Ubah 'waktuBerangkat' ke satuan detik -> dtkMulai.
           b. Ubah 'waktuFinish' ke satuan detik -> dtkSelesai.
           c. Hitung durasi hari ini: durasi = dtkSelesai - dtkMulai.
           d. Akumulasikan ke total: totalDetik = totalDetik + durasi.
       - Hitung rata-rata: rataRata = totalDetik / jumlahData.
       - Tampilkan langsung hasil akhir totalDetik dan rataRata ke layar.
    ========================================================================
*/

#include <iostream>
#include <string>

using namespace std;

// ========================================================
// KAMUS GLOBAL
// ========================================================

// Definisi struct
struct KegiatanLari {
  string nama;
  string hari;
  string waktuBerangkat;
  string waktuFinish;
  double jarak;
  string catatan;
};

// Fungsi konversi format HH:MM:SS ke detik
int konversiKeDetik(string waktu) {
  int jam = stoi(waktu.substr(0, 2));
  int menit = stoi(waktu.substr(3, 2));
  int detik = stoi(waktu.substr(6, 2));

  return (jam * 3600) + (menit * 60) + detik;
}

// Prosedur menampilkan format MM:SS
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

// ========================================================
// DESKRIPSI
// ========================================================
int main() {
  // Inisialisasi data lari
  KegiatanLari dataLari[3] = {
      {"Nadia", "Senin", "07:10:00", "07:38:20", 2.5, "Cuaca cerah"},
      {"Nadia", "Rabu", "07:12:00", "07:41:10", 2.6, "Sedikit ramai"},
      {"Nadia", "Jumat", "07:15:30", "07:45:30", 2.5, "Lancar"}};

  int totalDetik = 0;
  int jumlahData = 3;

  // Perhitungan di balik layar tanpa mencetak tabel
  for (int i = 0; i < jumlahData; i++) {
    int dtkMulai = konversiKeDetik(dataLari[i].waktuBerangkat);
    int dtkSelesai = konversiKeDetik(dataLari[i].waktuFinish);
    int durasi = dtkSelesai - dtkMulai;

    totalDetik = totalDetik + durasi;
  }

  // Menghitung rata-rata durasi
  int rataRata = totalDetik / jumlahData;

  // Tampilkan hasil akhir
  cout << "Hasil Perhitungan:\n";
  cout << "- Total waktu lari : " << totalDetik << " detik (";
  cetakWaktu(totalDetik);
  cout << ")\n";

  cout << "- Rata-rata lari   : " << rataRata << " detik (";
  cetakWaktu(rataRata);
  cout << ")\n";

  return 0;
}