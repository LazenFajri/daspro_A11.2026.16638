#include<iostream>

using namespace std;

int main() {
    int n;
    cout << "Input N: ";
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++){
            cout << "Input ke-" << (i+1) << ": ";
            cin >> arr[i];
    }

    int max_val = arr[0];
    int min_val = arr[0];
    int sum = 0;

    cout << "\nHasil Array: ";
    for(int i= 0; i < n; i++) {
    cout << arr[i] << " ";
    sum += arr[i];
    if (arr[i] > max_val) max_val = arr[i];
    if (arr[i] < min_val) min_val = arr[i];
    }
    cout << endl;

    double rata_rata = (double)sum / n;
    cout << "Nilai terbesar: " << max_val << endl;
    cout << "Nilai terkecil: " << min_val << endl;
    cout << "Jumlah array  : " << sum << endl;
    cout << "Rata-rata     : " << rata_rata << endl;

    return 0;
}
