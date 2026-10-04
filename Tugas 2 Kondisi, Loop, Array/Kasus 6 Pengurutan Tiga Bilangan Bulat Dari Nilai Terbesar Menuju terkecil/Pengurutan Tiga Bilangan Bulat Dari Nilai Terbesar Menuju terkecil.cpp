// ============================================================
// PROGRAM       : PENGURUTAN TIGA BILANGAN (BESAR KE KECIL)
// TENTANG       : Mengurutkan tiga buah bilangan bulat dari nilai
//                 terbesar menuju terkecil secara langsung berdasarkan
//                 pohon keputusan logika perbandingan bertingkat (IF).
// OLEH          : Muhammad Fajri Setyawan
// NIM           : A11.2026.16638
// ============================================================

#include <iostream>

using namespace std;

// ============================================================
// KAMUS
// Semua variabel program dideklarasikan di bagian ini
// ============================================================
int a;
int b;
int c;

// ============================================================
// DISKRIPSI
// ============================================================
int main()
{
    // --------------------------------------------------------
    // TAMPILAN HEADER PROGRAM
    // --------------------------------------------------------
    cout << "====================================================\n";
    cout << "    PENGURUTAN 3 BILANGAN (DARI BESAR KE KECIL)     \n";
    cout << "====================================================\n";
    cout << "Oleh       : Muhammad Fajri Setyawan\n";
    cout << "NIM        : A11.2026.16638\n";
    cout << "----------------------------------------------------\n\n";

    // --------------------------------------------------------
    // TAHAP 1: INPUT DATA
    // Membaca masukan tiga buah bilangan bulat dari pengguna
    // --------------------------------------------------------
    cout << "Masukkan angka ke-1 (a) : ";
    cin >> a;

    cout << "Masukkan angka ke-2 (b) : ";
    cin >> b;

    cout << "Masukkan angka ke-3 (c) : ";
    cin >> c;

    cout << "\nData input terbaca: a = " << a << ", b = " << b << ", c = " << c << endl;
    cout << "----------------------------------------------------\n";

    // --------------------------------------------------------
    // TAHAP 2 & 3: PROSES POHON KEPUTUSAN & OUTPUT
    // Menelusuri jalur percabangan IF sesuai relasi nilai
    // --------------------------------------------------------
    cout << "Urutan dari besar ke kecil:\n>> ";

    if (a > b) {
        // Jalur Cabang Kiri (a > b)
        if (b > c) {
            // Kasus 1: a > b > c
            cout << a << " > " << b << " > " << c << endl;
        } else {
            // b <= c, maka perlu membandingkan posisi a terhadap c
            if (a > c) {
                // Kasus 2: a > c > b
                cout << a << " > " << c << " > " << b << endl;
            } else {
                // Kasus 5: c >= a > b
                cout << c << " > " << a << " > " << b << endl;
            }
        }
    } else {
        // Jalur Cabang Kanan (a <= b)
        if (a > c) {
            // Kasus 3: b >= a > c
            cout << b << " > " << a << " > " << c << endl;
        } else {
            // a <= c, maka perlu membandingkan posisi b terhadap c
            if (b > c) {
                // Kasus 4: b > c >= a
                cout << b << " > " << c << " > " << a << endl;
            } else {
                // Kasus 6: c >= b >= a
                cout << c << " > " << b << " > " << a << endl;
            }
        }
    }

    cout << "====================================================\n";

    return 0; // Mengakhiri program secara normal
}
