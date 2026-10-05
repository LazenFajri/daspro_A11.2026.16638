#include<iostream>

using namespace std;

int main (){
    double jam_kerja, upah, jam_lembur;

    cout << "Masukkan jam kerja: ";
    cin >> jam_kerja;
    cout << "Masukkan upah per jam: ";
    cin >> upah;
    cout << "Masukkan jam lembur: ";
    cin >> jam_lembur;

    //upah regular
    double upah_regular = jam_kerja * upah;

    //presentase lembur;
    double persen_lembur;
    if (jam_lembur >= 30){
        persen_lembur = 0.40; //40%
    } else {
        persen_lembur = 0.20; //20%
    }

    //perhitungan overpay
    double overpay = (jam_kerja - jam_lembur) * upah * 0.30; //30%
    double total_upah = upah_regular + overpay;

    cout << "\n--- Rincian Upah ---" << endl;
    cout << "Upah Regular: " << upah_regular << endl;
    cout << "Tambahan Persentase Lembur: " << (persen_lembur * 100) << "%" << endl;
    cout << "Overpay     : " << overpay << endl;
    cout << "Total Upah  : " << total_upah << endl;

    return 0;
}
