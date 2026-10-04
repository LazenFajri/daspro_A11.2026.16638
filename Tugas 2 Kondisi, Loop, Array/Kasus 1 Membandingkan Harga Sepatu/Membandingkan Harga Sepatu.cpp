// ============================================================
// PROGRAM       : KOMPARASI DAN PENGURUTAN HARGA SEPATU
// TENTANG       : Mengelola data sepatu anggota circle lari,
//                 membandingkan harga dua entitas, serta
//                 mengurutkan 3 data menggunakan seleksi kondisi IF.
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
struct SepatuLari {
    string namaPemilik;
    string merk;
    int nomor;
    string warna;
    int ukuran;
    double harga;
};

// Deklarasi array sepatu dan variabel bantu sorting
SepatuLari sepatu[5];
SepatuLari temp;
int a, b, c;
int i;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // Format desimal bilangan bulat rupiah
    cout << fixed << setprecision(0);

    // --------------------------------------------------------
    // Inisialisasi basis data 5 anggota circle lari
    // --------------------------------------------------------
    sepatu[0] = {"Nadia", "Nike", 101, "Pink White", 38, 1200000};
    sepatu[1] = {"Ira", "Adidas", 102, "Black Purple", 37, 1100000};
    sepatu[2] = {"Rania", "New Balance", 103, "Blue", 39, 1350000};
    sepatu[3] = {"Zulaeka", "Puma", 104, "Mint", 36, 1000000};
    sepatu[4] = {"Laksmiya", "Asics", 105, "Black Orange", 38, 1250000};

    // --------------------------------------------------------
    // Tampilan Header Program
    // --------------------------------------------------------
    cout << "========================================================================\n";
    cout << "          DATA SEPATU ANGGOTA CIRCLE LARI (STRUCT + ARRAY + IF)         \n";
    cout << "========================================================================\n";
    cout << "Programmer : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "------------------------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // 1. Tampilkan Seluruh Data Master Anggota
    // --------------------------------------------------------
    cout << "------------------------------------------------------------------------\n";
    cout << " DAFTAR LENGKAP SEPATU ANGGOTA\n";
    cout << "------------------------------------------------------------------------\n";
    for (i = 0; i < 5; i++) {
        cout << " [" << i << "] Pemilik: " << setw(9) << left << sepatu[i].namaPemilik
             << " | Merk: " << setw(12) << left << sepatu[i].merk
             << " | Seri: " << sepatu[i].nomor
             << " | Warna: " << setw(13) << left << sepatu[i].warna
             << " | Ukuran: " << sepatu[i].ukuran
             << " | Harga: Rp " << sepatu[i].harga << "\n";
    }
    cout << "------------------------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // 2. Perbandingan 2 Sepatu: Nadia (indeks 0) vs Zulaeka (indeks 3)
    // --------------------------------------------------------
    cout << "========================================================================\n";
    cout << " KASUS A : PERBANDINGAN 2 SEPATU (NADIA VS ZULAEKA)\n";
    cout << "========================================================================\n";
    cout << " Sepatu Nadia   : " << sepatu[0].merk << " (Rp " << sepatu[0].harga << ")\n";
    cout << " Sepatu Zulaeka : " << sepatu[3].merk << " (Rp " << sepatu[3].harga << ")\n";
    cout << " Kesimpulan     : ";
    if (sepatu[0].harga > sepatu[3].harga) {
        cout << "Sepatu milik Nadia lebih mahal dibandingkan sepatu milik Zulaeka.\n";
    } else {
        cout << "Sepatu milik Zulaeka lebih mahal atau sama dengan sepatu milik Nadia.\n";
    }
    cout << "------------------------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // 3. Pengurutan 3 Sepatu: Nadia (0), Ira (1), Rania (2)
    //    Mengurutkan harga dari yang terkecil ke terbesar
    // --------------------------------------------------------
    cout << "========================================================================\n";
    cout << " KASUS B : URUTKAN 3 SEPATU DARI TERMURAH (NADIA, IRA, RANIA)\n";
    cout << "========================================================================\n";

    a = 0; // Posisi Nadia
    b = 1; // Posisi Ira
    c = 2; // Posisi Rania

    // Seleksi 1: Bandingkan dan tukar jika posisi 'a' lebih mahal dari 'b'
    if (sepatu[a].harga > sepatu[b].harga) {
        temp      = sepatu[a];
        sepatu[a] = sepatu[b];
        sepatu[b] = temp;
    }

    // Seleksi 2: Bandingkan dan tukar jika posisi 'a' lebih mahal dari 'c'
    if (sepatu[a].harga > sepatu[c].harga) {
        temp      = sepatu[a];
        sepatu[a] = sepatu[c];
        sepatu[c] = temp;
    }

    // Seleksi 3: Bandingkan dan tukar jika posisi 'b' lebih mahal dari 'c'
    if (sepatu[b].harga > sepatu[c].harga) {
        temp      = sepatu[b];
        sepatu[b] = sepatu[c];
        sepatu[c] = temp;
    }

    // Tampilkan urutan hasil sorting
    cout << "Hasil Pengurutan Harga (Terkecil ke Terbesar):\n";
    cout << " 1. " << setw(7) << left << sepatu[a].namaPemilik
         << " (" << setw(11) << left << sepatu[a].merk << ") - Rp " << sepatu[a].harga << "\n";
    cout << " 2. " << setw(7) << left << sepatu[b].namaPemilik
         << " (" << setw(11) << left << sepatu[b].merk << ") - Rp " << sepatu[b].harga << "\n";
    cout << " 3. " << setw(7) << left << sepatu[c].namaPemilik
         << " (" << setw(11) << left << sepatu[c].merk << ") - Rp " << sepatu[c].harga << "\n";
    cout << "========================================================================\n";

    return 0;
}
