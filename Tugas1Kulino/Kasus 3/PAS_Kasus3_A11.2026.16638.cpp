#include<iostream>

using namespace std;

int main(){
    int a, b;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;

    //Jika A lebih besar dari B, maka B dikalikan 2
    if (a < b) {
        b = b * 2;
    }

    //Deret angka dari B mundur ke A
    for(int i = b; i>=a; i--){
        cout << i << " ";
    }
    for(int i = a; i>=b; i--){
        cout << i << " ";
    }

    return 0;
}
