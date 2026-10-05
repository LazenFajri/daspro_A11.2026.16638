// ============================================================
// PROGRAM       : KLASIFIKASI KARAKTERISTIK BILANGAN BULAT
// TENTANG       : Menentukan apakah bilangan bertanda positif/negatif,
//                 berparitas ganjil/genap, kombinasi keduanya,
//                 serta penanganan khusus untuk input angka NOL.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
int bilangan;
string statusTanda;
string statusParitas;
string kategoriGabungan;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // Header program
    cout << "====================================================\n";
    cout << "       PROGRAM ANALISIS KARAKTERISTIK BILANGAN      \n";
    cout << "====================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "----------------------------------------------------\n\n";

    // Input data bilangan dari keyboard
    cout << "Masukkan sembarang bilangan bulat : ";
    cin >> bilangan;

    // --------------------------------------------------------
    // PROSES EVALUASI KONDISI (LOGIKA IF-ELSE)
    // --------------------------------------------------------
    if (bilangan == 0) {
        // Penanganan Khusus untuk Angka NOL
        statusTanda      = "Netral (Bukan Positif maupun Negatif)";
        statusParitas    = "Genap (Karena habis dibagi 2)";
        kategoriGabungan = "Bilangan Nol";
    } else {
        // 1. Analisis Tanda Bilangan (Positif / Negatif)
        if (bilangan > 0) {
            statusTanda = "Positif";
        } else {
            statusTanda = "Negatif";
        }

        // 2. Analisis Paritas (Ganjil / Genap)
        // Operator modulo (%) menghasilkan 0 jika habis dibagi 2
        if (bilangan % 2 == 0) {
            statusParitas = "Genap";
        } else {
            statusParitas = "Ganjil";
        }

        // 3. Analisis Gabungan (Positif/Negatif + Ganjil/Genap)
        if (bilangan > 0 && bilangan % 2 == 0) {
            kategoriGabungan = "Positif Genap";
        } else if (bilangan > 0 && bilangan % 2 != 0) {
            kategoriGabungan = "Positif Ganjil";
        } else if (bilangan < 0 && bilangan % 2 == 0) {
            kategoriGabungan = "Negatif Genap";
        } else {
            kategoriGabungan = "Negatif Ganjil";
        }
    }

    // --------------------------------------------------------
    // PENYAJIAN LAPORAN KELUARAN
    // --------------------------------------------------------
    cout << "\n====================================================\n";
    cout << "                  HASIL IDENTIFIKASI                \n";
    cout << "====================================================\n";
    cout << " Nilai Input         : " << bilangan << "\n";
    cout << " Tanda Bilangan      : " << statusTanda << "\n";
    cout << " Sifat Paritas       : " << statusParitas << "\n";
    cout << " Klasifikasi Lengkap : " << kategoriGabungan << "\n";
    cout << "----------------------------------------------------\n";

    // Catatan akademik penjelasan output nol
    if (bilangan == 0) {
        cout << "Catatan Khusus:\n";
        cout << "Angka 0 secara matematis merupakan bilangan genap\n";
        cout << "(0 = 2 x 0), namun bersifat netral (tidak bernilai\n";
        cout << "positif dan tidak bernilai negatif).\n";
        cout << "====================================================\n";
    } else {
        cout << "Status: Analisis karakteristik bilangan selesai dievaluasi.\n";
        cout << "====================================================\n";
    }

    return 0;
}
