//judul : Mini Project Looping
//Oleh : Muhammad Fajri Setyawwan NIM : A11.2026.16638
#include <iostream>
#include <string>

using namespace std;

//kamus
int pilih, tipe, n, panjang, lebar, batas;
int i, j, k;
char ulang;
string teks;

//deskripsi
int main() {
    ulang = 'y';

    while (ulang == 'y' || ulang == 'Y') {
        cout << "---------------------------------------\n";
        cout << "\tGandakan & Deret Pola!\n";
        cout << "---------------------------------------\n";
        cout << "\t    pilih 1 / 2 \n";
        cout << "\n1. Angka\n2. Nama \n";
        cout << "\nmemilih : ";
        cin >> pilih;

        // Tangani jika input pilihan menu bukan angka
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInput harus berupa angka 1 atau 2!\n\n";
            continue;
        }

        if (pilih == 1) {
            int angka;
            cout << "masukkan angkamu : ";
            cin >> angka;

            // Tangani jika input angka malah diisi huruf
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nError: Anda memilih menu angka, jangan masukkan huruf!\n\n";
                continue;
            }

            teks = to_string(angka);
            batas = angka;
        } else if (pilih == 2) {
            cout << "masukkan namamu : ";
            cin.ignore();
            getline(cin, teks);
            batas = teks.length();
        } else {
            cout << "\ntidak ada pilihan seperti itu\n\n";
            continue;
        }

        cout << "\n------------------------------------------\n";
        cout << "\tMasukkan tipe pola!\n";
        cout << "------------------------------------------\n";
        cout << "\t    pilih 1, 2, 3, 4, 5, 6, 7 \n";
        cout << "\n1. Penggandaan biasa (diulang ke bawah)";
        cout << "\n2. Hitung 1 s/d batas (Maju)";
        cout << "\n3. Hitung batas s/d 1 (Mundur)";
        cout << "\n4. Hilang dari kanan (Maju: 1 s/d batas berkurang)";
        cout << "\n5. Hilang dari kanan (Mundur: batas s/d 1 berkurang)";
        cout << "\n6. deret maju (panjang x lebar)";
        cout << "\n7. deret mundur (panjang x lebar)\n";
        cout << "\nmemilih : ";
        cin >> tipe;

        // Menangani jika input tipe pola bukan angka
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInput tipe pola harus angka!\n\n";
            continue;
        }

        cout << "\n--- Hasil Looping ---\n";

        switch (tipe) {
            case 1: { // Penggandaan biasa
                cout << "Mau digandakan berapa kali? : ";
                cin >> n;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Input harus berupa angka!\n";
                    break;
                }
                i = 0;
                while (i < n) {
                    cout << teks << "\n";
                    i++;
                }
                break;
            }

            case 2: { // Hitung maju 1 s/d batas
                i = 1;
                while (i <= batas) {
                    if (pilih == 1) {
                        cout << i << " ";
                    } else {
                        cout << teks.substr(0, i) << "\n";
                    }
                    i++;
                }
                if (pilih == 1) cout << "\n";
                break;
            }

            case 3: { // Hitung mundur batas s/d 1
                i = batas;
                while (i >= 1) {
                    if (pilih == 1) {
                        cout << i << " ";
                    } else {
                        cout << teks.substr(0, i) << "\n";
                    }
                    i--;
                }
                if (pilih == 1) cout << "\n";
                break;
            }

            case 4: { // Hilang dari kanan (Maju)
                i = batas;
                while (i >= 1) {
                    j = 1;
                    while (j <= i) {
                        if (pilih == 1) {
                            cout << j << " ";
                        } else {
                            cout << teks[j - 1];
                        }
                        j++;
                    }
                    cout << "\n";
                    i--;
                }
                break;
            }

            case 5: { // Hilang dari kanan (Mundur)
                i = 1;
                while (i <= batas) {
                    j = batas;
                    while (j >= i) {
                        if (pilih == 1) {
                            cout << j << " ";
                        } else {
                            cout << teks[j - 1];
                        }
                        j--;
                    }
                    cout << "\n";
                    i++;
                }
                break;
            }

            case 6: { // Kotak maju (panjang baris x lebar kolom)
                cout << "Masukkan panjang (baris ke bawah): ";
                cin >> panjang;
                cout << "Masukkan lebar (kolom ke samping): ";
                cin >> lebar;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Panjang dan lebar harus berupa angka!\n";
                    break;
                }

                i = 0;
                while (i < panjang) {
                    j = 0;
                    while (j < lebar) {
                        if (pilih == 1) {
                            k = 1;
                            while (k <= batas) {
                                cout << k << " ";
                                k++;
                            }
                            cout << "  ";
                        } else {
                            cout << teks << " ";
                        }
                        j++;
                    }
                    cout << "\n";
                    i++;
                }
                break;
            }

            case 7: { // Kotak mundur (panjang baris x lebar kolom)
                cout << "Masukkan panjang (baris ke bawah): ";
                cin >> panjang;
                cout << "Masukkan lebar (kolom ke samping): ";
                cin >> lebar;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Panjang dan lebar harus berupa angka!\n";
                    break;
                }

                i = 0;
                while (i < panjang) {
                    j = 0;
                    while (j < lebar) {
                        if (pilih == 1) {
                            k = batas;
                            while (k >= 1) {
                                cout << k << " ";
                                k--;
                            }
                            cout << "  ";
                        } else {
                            k = batas;
                            while (k >= 1) {
                                cout << teks[k - 1];
                                k--;
                            }
                            cout << " ";
                        }
                        j++;
                    }
                    cout << "\n";
                    i++;
                }
                break;
            }

            default:
                cout << "\nTipe tidak valid!\n";
                break;
        }

        cout << "\nIngin mencoba lagi? (y/n): ";
        cin >> ulang;
        cout << "\n";
    }

    cout << "Program selesai, terima kasih!\n";
    return 0;
}
