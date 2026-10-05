// ============================================================
// PROGRAM       : PENDATAAN KARTU TANDA PENDUDUK (KTP)
// TENTANG       : Membaca rekaman data kependudukan melalui keyboard
//                 dan menampilkannya kembali dalam format terstruktur.
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// ============================================================
struct IdentitasKTP {
    string nama;
    string nik;
    string tempatLahir;
    string tanggalLahir;
    string jenisKelamin;
    string alamat;
    string agama;
};

IdentitasKTP dataKTP;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    cout << "====================================================\n";
    cout << "            FORMULIR PEREKAMAN DATA KTP             \n";
    cout << "====================================================\n";
    cout << "Oleh          : Muhammad Fajri Setyawan\n";
    cout << "NIM           : A11.2026.16638\n";
    cout << "----------------------------------------------------\n";

    // Membaca masukan data teks (mendukung spasi antar kata)
    cout << "Masukkan Nama Lengkap   : ";
    getline(cin, dataKTP.nama);

    cout << "Masukkan Nomor Induk KTP: ";
    getline(cin, dataKTP.nik);

    cout << "Masukkan Tempat Lahir   : ";
    getline(cin, dataKTP.tempatLahir);

    cout << "Masukkan Tanggal Lahir  : ";
    getline(cin, dataKTP.tanggalLahir);

    cout << "Masukkan Jenis Kelamin  : ";
    getline(cin, dataKTP.jenisKelamin);

    cout << "Masukkan Alamat Domisili: ";
    getline(cin, dataKTP.alamat);

    cout << "Masukkan Agama          : ";
    getline(cin, dataKTP.agama);

    // Menampilkan kembali lembar informasi KTP
    cout << "\n====================================================\n";
    cout << "          REKAP DATA KEPENDUDUKAN ELEKTRONIK        \n";
    cout << "====================================================\n";
    cout << "Nama          : " << dataKTP.nama << "\n";
    cout << "NIK           : " << dataKTP.nik << "\n";
    cout << "Tempat Lahir  : " << dataKTP.tempatLahir << "\n";
    cout << "Tanggal Lahir : " << dataKTP.tanggalLahir << "\n";
    cout << "Jenis Kelamin : " << dataKTP.jenisKelamin << "\n";
    cout << "Alamat        : " << dataKTP.alamat << "\n";
    cout << "Agama         : " << dataKTP.agama << "\n";
    cout << "====================================================\n";

    return 0;
}
