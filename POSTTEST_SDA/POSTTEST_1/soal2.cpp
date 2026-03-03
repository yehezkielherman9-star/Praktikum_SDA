#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    Mahasiswa mhs[5];
    int indexTertinggi = 0;

    for(int i = 0; i < 5; i++) {
        cout << "Mahasiswa ke-" << i+1 << endl;
        cout << "Nama: ";
        cin >> mhs[i].nama;
        cout << "NIM: ";
        cin >> mhs[i].nim;
        cout << "IPK: ";
        cin >> mhs[i].ipk;
        cout << endl;
    }

    for(int i = 1; i < 5; i++) {
        if(mhs[i].ipk > mhs[indexTertinggi].ipk) {
            indexTertinggi = i;
        }
    }

    cout << "Mahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama: " << mhs[indexTertinggi].nama << endl;
    cout << "NIM: " << mhs[indexTertinggi].nim << endl;
    cout << "IPK: " << mhs[indexTertinggi].ipk << endl;

    return 0;
}