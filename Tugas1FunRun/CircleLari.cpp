/*
    Judul     : Pencatatan Data Lari Circle Nadia (ADT Struct)
    Deskripsi : Menghitung selisih waktu/durasi harian dan rata-rata durasi
                secara berurutan tanpa sorting.
    Oleh      : Muhammad Fajri Setyawan
    NIM       : A11.2026.16638
*/

#include <iostream>
#include <string>

using namespace std;

// ========================================================
// KAMUS GLOBAL (Tipe Data Buatan & Deklarasi Fungsi)
// ========================================================

// Mendefinisikan struct untuk mengelompokkan data aktivitas lari
struct KegiatanLari {
  string nama;           // Menyimpan nama pelari
  string hari;           // Hari pelaksanaan kegiatan (Senin, Rabu, Jumat)
  string waktuBerangkat; // Jam awal lari dengan format string "HH:MM:SS"
  string waktuFinish;    // Jam selesai lari dengan format string "HH:MM:SS"
  double jarak;          // Jarak tempuh dalam satuan kilometer (km)
  string catatan;        // Keterangan kondisi cuaca atau lintasan
};

// Fungsi untuk mengonversi format teks "HH:MM:SS" menjadi satuan total detik
int konversiKeDetik(string waktu) {
  // substr(awal, panjang) digunakan untuk memotong bagian string
  // stoi digunakan untuk mengubah teks string menjadi bilangan bulat (int)
  int jam = stoi(waktu.substr(0, 2));   // Mengambil 2 digit pertama sebagai jam
  int menit = stoi(waktu.substr(3, 2)); // Mengambil 2 digit kedua sebagai menit
  int detik =
      stoi(waktu.substr(6, 2)); // Mengambil 2 digit terakhir sebagai detik

  // Rumus matematis: 1 jam = 3600 detik, 1 menit = 60 detik
  return (jam * 3600) + (menit * 60) + detik;
}

// Prosedur untuk mencetak angka detik ke format tampilan menit dan detik
// (MM:SS)
void cetakWaktu(int detik) {
  int m = detik / 60; // Menghitung jumlah menit
  int s = detik % 60; // Menghitung sisa detik setelah dibagi 60

  // Pengecekan angka di bawah 10 agar ditambahkan angka 0 di depannya
  if (m < 10)
    cout << "0";
  cout << m << ":";

  if (s < 10)
    cout << "0";
  cout << s;
}

// ========================================================
// DESKRIPSI (Program Utama / Eksekusi)
// ========================================================
int main() {
  // Pengisian data array struct 3 hari lari Nadia sesuai modul (tanpa
  // di-sorting)
  KegiatanLari dataLari[3] = {
      {"Nadia", "Senin", "07:10:00", "07:38:20", 2.5, "Cuaca cerah"},
      {"Nadia", "Rabu", "07:12:00", "07:41:10", 2.6, "Sedikit ramai"},
      {"Nadia", "Jumat", "07:15:30", "07:45:30", 2.5, "Lancar"}};

  // Variabel akumulator untuk menampung total durasi seluruh hari
  int totalDetik = 0;
  // Variabel penyimpan total baris data yang akan diproses
  int jumlahData = 3;

  // Menampilkan header tabel keluaran program
  cout << "===================================================================="
          "====\n";
  cout << "                    DATA LAPORAN LARI NADIA                         "
          "    \n";
  cout << "===================================================================="
          "====\n";
  cout << "Hari\tBerangkat\tFinish\t\tDurasi\t\tJarak\tCatatan\n";
  cout << "--------------------------------------------------------------------"
          "----\n";

  // Perulangan untuk membaca dan menghitung array mulai dari indeks ke-0 sampai
  // ke-2
  for (int i = 0; i < jumlahData; i++) {
    // 1. Ubah waktu string berangkat dan finish ke satuan detik
    int dtkMulai = konversiKeDetik(dataLari[i].waktuBerangkat);
    int dtkSelesai = konversiKeDetik(dataLari[i].waktuFinish);

    // 2. Hitung durasi selisih antara selesai dan berangkat
    int durasi = dtkSelesai - dtkMulai;

    // 3. Tambahkan durasi harian ke variabel total akumulasi
    totalDetik = totalDetik + durasi;

    // 4. Cetak hasil per baris data ke layar
    cout << dataLari[i].hari << "\t" << dataLari[i].waktuBerangkat << "\t"
         << dataLari[i].waktuFinish << "\t";
    cetakWaktu(durasi); // Menampilkan durasi dalam format MM:SS
    cout << "\t\t" << dataLari[i].jarak << " km\t" << dataLari[i].catatan
         << endl;
  }

  cout << "--------------------------------------------------------------------"
          "----\n";

  // Menghitung rata-rata waktu (total detik dibagi jumlah hari)
  int rataRata = totalDetik / jumlahData;

  // Menampilkan hasil ringkasan perhitungan akhir
  cout << "\nHasil Perhitungan:\n";
  cout << "- Total waktu lari : " << totalDetik << " detik (";
  cetakWaktu(totalDetik);
  cout << ")\n";

  cout << "- Rata-rata lari   : " << rataRata << " detik (";
  cetakWaktu(rataRata);
  cout << ")\n";

  return 0; // Mengindikasikan program berhasil berjalan normal
}