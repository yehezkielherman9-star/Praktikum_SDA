#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct Kereta {
    int nomor;
    string nama;
    string asal;
    string tujuan;
    int harga;
};

const int MAX = 100;
int n = 0;

void tampil(Kereta* arr) {
    cout << "\n=== Jadwal Kereta ===\n";
    for (int i = 0; i < n; i++) {
        cout << (arr + i)->nomor << " | "
             << (arr + i)->nama << " | "
             << (arr + i)->asal << " -> "
             << (arr + i)->tujuan << " | Rp"
             << (arr + i)->harga << endl;
    }
}

void tambah(Kereta* arr) {
    cout << "\nTambah Data Kereta\n";
    cout << "Nomor: "; cin >> (arr + n)->nomor;
    cout << "Nama: "; cin >> (arr + n)->nama;
    cout << "Asal: "; cin >> (arr + n)->asal;
    cout << "Tujuan: "; cin >> (arr + n)->tujuan;
    cout << "Harga: "; cin >> (arr + n)->harga;
    n++;
}

void swap(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(Kereta* arr) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + min)->harga) {
                min = j;
            }
        }
        swap(arr + i, arr + min);
    }
    cout << "\nData berhasil diurutkan berdasarkan harga!\n";
}

void merge(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta L[50], R[50];

    for (int i = 0; i < n1; i++)
        L[i] = *(arr + l + i);
    for (int j = 0; j < n2; j++)
        R[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = L[i];
        i++; k++;
    }

    while (j < n2) {
        *(arr + k) = R[j];
        j++; k++;
    }
}

void mergeSort(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void linearSearch(Kereta* arr) {
    string asal, tujuan;
    cout << "\nCari berdasarkan rute\n";
    cout << "Asal: "; cin >> asal;
    cout << "Tujuan: "; cin >> tujuan;

    bool found = false;

    for (int i = 0; i < n; i++) {
        cout << "Cek data ke-" << i << endl;

        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "Ditemukan: " << (arr + i)->nama << endl;
            found = true;
        }
    }

    if (!found) cout << "Data tidak ditemukan\n";
}

int jumpSearch(Kereta* arr, int x) {
    int step = sqrt(n);
    int prev = 0;

    while ((arr + min(step, n) - 1)->nomor < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if ((arr + i)->nomor == x)
            return i;
    }

    return -1;
}

void sortNomor(Kereta* arr) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((arr + i)->nomor > (arr + j)->nomor) {
                swap(arr + i, arr + j);
            }
        }
    }
}

int main() {
    Kereta data[MAX];
    int pilihan;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Linear Search (Rute)\n";
        cout << "4. Jump Search (Nomor)\n";
        cout << "5. Merge Sort (Nama A-Z)\n";
        cout << "6. Selection Sort (Harga)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambah(data); break;
            case 2: tampil(data); break;
            case 3: linearSearch(data); break;
            case 4: {
                int cari;
                cout << "Masukkan nomor kereta: ";
                cin >> cari;
                sortNomor(data); // wajib sorted
                int idx = jumpSearch(data, cari);
                if (idx != -1)
                    cout << "Ditemukan: " << (data + idx)->nama << endl;
                else
                    cout << "Tidak ditemukan\n";
                break;
            }
            case 5:
                mergeSort(data, 0, n - 1);
                cout << "Data diurutkan berdasarkan nama!\n";
                break;
            case 6:
                selectionSort(data);
                break;
        }

    } while (pilihan != 0);

    return 0;
}