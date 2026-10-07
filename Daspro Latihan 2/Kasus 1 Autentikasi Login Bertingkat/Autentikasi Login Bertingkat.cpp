// ============================================================
// PROGRAM       : AUTENTIKASI KREDENSIAL LOGIN PENGGUNA
// TENTANG       : Memverifikasi kombinasi nama pengguna (username)
//                 dan kata sandi (password) menggunakan percabangan
//                 bertingkat (Nested IF - ELSE).
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// KAMUS
// Variabel program dideklarasikan di sini
// ============================================================
string inputUser;
string inputPass;
string statusLogin;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // HEADER SISTEM
    // --------------------------------------------------------
    cout << "========================================================\n";
    cout << "         SISTEM AUTENTIKASI KREDENSIAL PENGGUNA         \n";
    cout << "========================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "--------------------------------------------------------\n\n";

    // --------------------------------------------------------
    // TAHAP 1: INPUT IDENTITAS PENGGUNA
    // --------------------------------------------------------
    cout << "Masukkan Username    : ";
    cin >> inputUser;

    cout << "Masukkan Password    : ";
    cin >> inputPass;

    // --------------------------------------------------------
    // TAHAP 2: PROSES EVALUASI LOGIN (NESTED IF - ELSE)
    // --------------------------------------------------------
    if (inputUser == "ifan") {
        if (inputPass == "12345") {
            statusLogin = "LOGIN BERHASIL! Selamat datang, Pak Ifan.";
        } else {
            statusLogin = "PASSWORD SALAH! Periksa kembali kata sandi Anda.";
        }
    }
    else if (inputUser == "budi") {
        if (inputPass == "abc123") {
            statusLogin = "LOGIN BERHASIL! Selamat datang, Budi.";
        } else {
            statusLogin = "PASSWORD SALAH! Periksa kembali kata sandi Anda.";
        }
    }
    else if (inputUser == "siti") {
        if (inputPass == "siti2026") {
            statusLogin = "LOGIN BERHASIL! Selamat datang, Siti.";
        } else {
            statusLogin = "PASSWORD SALAH! Periksa kembali kata sandi Anda.";
        }
    }
    else {
        statusLogin = "USERNAME TIDAK TERDAFTAR! Akun tidak ditemukan.";
    }

    // --------------------------------------------------------
    // TAHAP 3: OUTPUT HASIL AUTENTIKASI
    // --------------------------------------------------------
    cout << "\n========================================================\n";
    cout << "                    HASIL VERIFIKASI                    \n";
    cout << "========================================================\n";
    cout << "Akun Pengguna : " << inputUser << "\n";
    cout << "Status Akses  : " << statusLogin << "\n";
    cout << "========================================================\n";

    return 0;
}
