// ============================================================
// PROGRAM       : PENGURUTAN SEPATU DARI BESAR KE KECIL (DESCENDING)
// TENTANG       : Memodifikasi pencarian nilai dengan menyusun
//                 seluruh 5 ukuran sepatu secara berurutan menurun.
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
DataSepatu temp;
int jumlahData;
int i, j;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    jumlahData = 5;

    // Nilai awal data sebelum diurutkan
    koleksi[0] = {"Nadia", "Nike", 38};
    koleksi[1] = {"Ira", "Adidas", 37};
    koleksi[2] = {"Rania", "New Balance", 42};
    koleksi[3] = {"Zulaeka", "Puma", 36};
    koleksi[4] = {"Laksmiya", "Asics", 40};

    // Header program
    cout << "========================================================\n";
    cout << "   URUTAN 5 UKURAN SEPATU (DARI BESAR MENUJU TERKECIL)  \n";
    cout << "========================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "--------------------------------------------------------\n\n";

    // Tampilkan data acak sebelum proses sorting
    cout << "Data Awal Sebelum Diurutkan:\n";
    for (i = 0; i < jumlahData; i++) {
        cout << koleksi[i].ukuran << " ";
    }
    cout << "\n--------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // Algoritma Pengurutan Menurun (Descending Sort)
    // --------------------------------------------------------
    for (i = 0; i < jumlahData - 1; i++) {
        for (j = i + 1; j < jumlahData; j++) {
            // Apabila nilai di posisi i lebih kecil dari posisi j,
            // lakukan pertukaran posisi agar yang lebih besar maju ke depan
            if (koleksi[i].ukuran < koleksi[j].ukuran) {
                temp       = koleksi[i];
                koleksi[i] = koleksi[j];
                koleksi[j] = temp;
            }
        }
    }

    // --------------------------------------------------------
    // Menampilkan Hasil Pengurutan
    // --------------------------------------------------------
    cout << "Hasil Format Deret Angka (Besar ke Kecil):\n>> ";
    for (i = 0; i < jumlahData; i++) {
        cout << koleksi[i].ukuran << (i < jumlahData - 1 ? "  " : "");
    }
    cout << "\n\n";

    cout << "Daftar Rinci Setelah Diurutkan:\n";
    for (i = 0; i < jumlahData; i++) {
        cout << "  Peringkat " << (i + 1) << " : "
             << "Ukuran " << setw(2) << koleksi[i].ukuran
             << " | Pemilik: " << setw(9) << left << koleksi[i].pemilik
             << " | Merk: " << koleksi[i].merk << "\n";
    }
    cout << "========================================================\n";

    return 0;
}
