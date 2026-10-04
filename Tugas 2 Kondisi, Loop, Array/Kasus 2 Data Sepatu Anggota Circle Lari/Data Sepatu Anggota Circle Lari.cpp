// ============================================================
// PROGRAM       : DATA SEPATU ANGGOTA CIRCLE LARI
// TENTANG       : Input dan penayangan data inventaris sepatu
//                 anggota kelompok lari menggunakan struktur data
//                 tipe bentukan (struct) yang dihimpun dalam array.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
// Definisi tipe data bentukan untuk merepresentasikan satu entitas sepatu
struct ProfilSepatu {
    string merk;     // Merk pabrikan sepatu
    int nomor;       // Kode seri / nomor model sepatu
    string warna;    // Kombinasi warna fisik sepatu
    int ukuran;      // Ukuran sol sepatu (standar EU)
    double harga;    // Nilai nominal pembelian (Rp)
};

// Deklarasi array penyimpan objek sepatu dan data anggota
ProfilSepatu sepatu[5];
string nama[5] = {"Nadia", "Ira", "Rania", "Zulaeka", "Laksmiya"};
int i;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // HEADER PROGRAM
    // --------------------------------------------------------
    cout << "========================================================================\n";
    cout << "           SISTEM PENDATAAN SEPATU ANGGOTA CIRCLE LARI                  \n";
    cout << "                   PROGRAM STUDI TEKNIK INFORMATIKA                     \n";
    cout << "========================================================================\n";
    cout << "Pengembang : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "------------------------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // PROSES INPUT DATA ANGGOTA (INTERAKTIF)
    // --------------------------------------------------------
    cout << ">>> PENGISIAN DATA SEPATU ANGGOTA <<<\n";
    for (i = 0; i < 5; i++) {
        cout << "\n[ Data Sepatu Milik: " << nama[i] << " ]\n";

        cout << "  Merk Sepatu        : ";
        getline(cin, sepatu[i].merk);

        cout << "  Nomor Seri Model   : ";
        cin >> sepatu[i].nomor;
        cin.ignore(); // Membersihkan sisa karakter newline dari input buffer

        cout << "  Kombinasi Warna    : ";
        getline(cin, sepatu[i].warna);

        cout << "  Ukuran Sepatu (EU) : ";
        cin >> sepatu[i].ukuran;

        cout << "  Harga Beli (Rp)    : ";
        cin >> sepatu[i].harga;
        cin.ignore(); // Menyiapkan buffer stream untuk getline berikutnya
    }

    // --------------------------------------------------------
    // PENYAJIAN TABEL DATA LENGKAP ANGGOTA
    // --------------------------------------------------------
    cout << fixed << setprecision(0);
    cout << "\n\n========================================================================================\n";
    cout << "                           TABEL DATA SEPATU ANGGOTA CIRCLE LARI                        \n";
    cout << "========================================================================================\n";

    // Header Kolom Tabel
    cout << left
         << setw(5)  << "No"
         << setw(12) << "Nama"
         << setw(16) << "Merk"
         << setw(10) << "Seri"
         << setw(16) << "Warna"
         << setw(10) << "Ukuran"
         << right << setw(15) << "Harga (Rp)" << endl;
    cout << string(88, '-') << endl;

    // Menampilkan Baris Data Hasil Traversal
    for (i = 0; i < 5; i++) {
        cout << left
             << setw(5)  << (i + 1)
             << setw(12) << nama[i]
             << setw(16) << sepatu[i].merk
             << setw(10) << sepatu[i].nomor
             << setw(16) << sepatu[i].warna
             << setw(10) << sepatu[i].ukuran
             << right << setw(15) << sepatu[i].harga << endl;
    }

    cout << "========================================================================================\n";
    cout << "Keterangan: Seluruh rekaman data berhasil disimpan dalam bentuk array tipe bentukan.\n";
    cout << "========================================================================================\n";

    return 0;
}
