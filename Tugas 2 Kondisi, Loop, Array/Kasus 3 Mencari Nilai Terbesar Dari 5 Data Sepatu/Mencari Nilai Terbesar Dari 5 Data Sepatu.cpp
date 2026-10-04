// ============================================================
// PROGRAM       : MENCARI UKURAN SEPATU TERBESAR (5 DATA)
// TENTANG       : Menentukan nilai ukuran sepatu paling besar
//                 dari lima data anggota menggunakan logika IF.
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
struct DataSepatu {
    string pemilik;
    string merk;
    int ukuran;
};

DataSepatu koleksi[5];
DataSepatu terbesar;
int jumlahData;
int i;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    jumlahData = 5;

    // Inisialisasi 5 data sampel sepatu
    koleksi[0] = {"Nadia", "Nike", 38};
    koleksi[1] = {"Ira", "Adidas", 37};
    koleksi[2] = {"Rania", "New Balance", 42};
    koleksi[3] = {"Zulaeka", "Puma", 36};
    koleksi[4] = {"Laksmiya", "Asics", 40};

    // Header program
    cout << "====================================================\n";
    cout << "       PENCARIAN UKURAN SEPATU TERBESAR (5 DATA)    \n";
    cout << "====================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "----------------------------------------------------\n\n";

    // Menampilkan seluruh data yang tersimpan
    cout << "Daftar Data Sepatu Anggota:\n";
    for (i = 0; i < jumlahData; i++) {
        cout << "  " << (i + 1) << ". " << setw(9) << left << koleksi[i].pemilik
             << " | Merk: " << setw(12) << left << koleksi[i].merk
             << " | Ukuran: " << koleksi[i].ukuran << "\n";
    }
    cout << "----------------------------------------------------\n";

    // Logika penentuan nilai terbesar
    // Inisialisasi patokan awal pada elemen indeks 0
    terbesar = koleksi[0];

    // Bandingkan secara berurutan dengan elemen berikutnya
    for (i = 1; i < jumlahData; i++) {
        if (koleksi[i].ukuran > terbesar.ukuran) {
            terbesar = koleksi[i]; // Perbarui pemegang rekor terbesar
        }
    }

    // Tampilkan hasil akhir
    cout << "\n[ KESIMPULAN HASIL ]\n";
    cout << "Ukuran Sepatu Terbesar : " << terbesar.ukuran << "\n";
    cout << "Pemilik Sepatu         : " << terbesar.pemilik << "\n";
    cout << "Merk Sepatu            : " << terbesar.merk << "\n";
    cout << "====================================================\n";

    return 0;
}
