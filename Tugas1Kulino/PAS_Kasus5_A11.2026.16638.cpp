#include<iostream>

using namespace std;

// typedef
typedef struct {
    int x;
    int y;
} Nilai;

int main () {
    //Variabel n1 bertipe Nilai
    Nilai n1;

    //Mengisi member n1
    n1.x= 5;
    n1.y= 10;

    //tampilkan nilai
    cout << "Nilai x: " << n1.x << endl;
    cout << "Nilai y: " << n1.y << endl;

    return 0;
}
