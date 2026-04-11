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

struct Tiket {
    string namaPenumpang;
    string asal;
    string tujuan;
};

const int MAX = 100;
int n = 0;

Tiket antrian[MAX];
int front = -1, rear = -1;

Tiket riwayat[MAX];
int top = -1;

Tiket redoStack[MAX];
int topRedo = -1;


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
    cout << "Data diurutkan berdasarkan harga!\n";
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
    cout << "Asal: "; cin >> asal;
    cout << "Tujuan: "; cin >> tujuan;

    bool found = false;

    for (int i = 0; i < n; i++) {
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "Ditemukan: " << (arr + i)->nama << endl;
            found = true;
        }
    }

    if (!found) cout << "Data tidak ditemukan\n";
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

void enqueue(Tiket* q) {
    if (rear == MAX - 1) {
        cout << "Antrian penuh!\n";
        return;
    }

    Tiket t;
    cout << "Nama: "; cin >> t.namaPenumpang;
    cout << "Asal: "; cin >> t.asal;
    cout << "Tujuan: "; cin >> t.tujuan;

    if (front == -1) front = 0;
    rear++;

    *(q + rear) = t;

    cout << "Masuk antrian!\n";
}

void enqueueDarurat(Tiket* q) {
    if (rear == MAX - 1) {
        cout << "Antrian penuh!\n";
        return;
    }

    Tiket t;
    cout << "Nama: "; cin >> t.namaPenumpang;
    cout << "Asal: "; cin >> t.asal;
    cout << "Tujuan: "; cin >> t.tujuan;

    if (front == -1) {
        front = rear = 0;
        *(q + front) = t;
    } else {
        for (int i = rear; i >= front; i--) {
            *(q + i + 1) = *(q + i);
        }
        rear++;
        *(q + front) = t;
    }

    cout << "Penumpang DARURAT masuk ke depan!\n";
}

void dequeue(Tiket* q, Tiket* s) {
    if (front == -1 || front > rear) {
        cout << "Antrian kosong!\n";
        return;
    }

    Tiket t = *(q + front);

    cout << "Diproses: " << t.namaPenumpang
         << " (" << t.asal << " -> " << t.tujuan << ")\n";

    front++;

    if (top == MAX - 1) {
        cout << "Riwayat penuh!\n";
        return;
    }

    top++;
    *(s + top) = t;

    topRedo = -1;
}

void undo(Tiket* s, Tiket* r) {
    if (top == -1) {
        cout << "Tidak ada data untuk undo\n";
        return;
    }

    topRedo++;
    *(r + topRedo) = *(s + top);

    cout << "Undo: " << (s + top)->namaPenumpang << endl;

    top--;
}

void redo(Tiket* s, Tiket* r) {
    if (topRedo == -1) {
        cout << "Tidak ada data untuk redo\n";
        return;
    }

    top++;
    *(s + top) = *(r + topRedo);

    cout << "Redo: " << (r + topRedo)->namaPenumpang << endl;

    topRedo--;
}

void tampilAntrian(Tiket* q) {
    if (front == -1 || front > rear) {
        cout << "Antrian kosong\n";
        return;
    }

    cout << "\n=== Antrian ===\n";
    for (int i = front; i <= rear; i++) {
        cout << (q + i)->namaPenumpang << " | "
             << (q + i)->asal << " -> "
             << (q + i)->tujuan << endl;
    }
}

void peekAntrian(Tiket* q) {
    if (front == -1 || front > rear) {
        cout << "Antrian kosong\n";
        return;
    }

    cout << "Terdepan: " << (q + front)->namaPenumpang << endl;
}

void tampilRiwayat(Tiket* s) {
    if (top == -1) {
        cout << "Riwayat kosong\n";
        return;
    }

    cout << "\n=== Riwayat ===\n";
    for (int i = top; i >= 0; i--) {
        cout << (s + i)->namaPenumpang << " | "
             << (s + i)->asal << " -> "
             << (s + i)->tujuan << endl;
    }
}

void peekRiwayat(Tiket* s) {
    if (top == -1) {
        cout << "Riwayat kosong\n";
        return;
    }

    cout << "Terakhir: " << (s + top)->namaPenumpang << endl;
}


int main() {
    Kereta data[MAX];
    int pilihan;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Data Kereta\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Rute (Linear)\n";
        cout << "4. Cari Nomor (Jump)\n";
        cout << "5. Sort Nama (Merge)\n";
        cout << "6. Sort Harga (Selection)\n";
        cout << "7. Enqueue Normal\n";
        cout << "8. Enqueue DARURAT\n";
        cout << "9. Dequeue\n";
        cout << "10. Tampil Antrian\n";
        cout << "11. Peek Antrian\n";
        cout << "12. Undo\n";
        cout << "13. Redo\n";
        cout << "14. Tampil Riwayat\n";
        cout << "15. Peek Riwayat\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambah(data); break;
            case 2: tampil(data); break;
            case 3: linearSearch(data); break;
            case 4: {
                int cari;
                cout << "Nomor: ";
                cin >> cari;
                sortNomor(data);
                int idx = jumpSearch(data, cari);
                if (idx != -1)
                    cout << "Ditemukan: " << (data + idx)->nama << endl;
                else
                    cout << "Tidak ditemukan\n";
                break;
            }
            case 5: mergeSort(data, 0, n - 1); break;
            case 6: selectionSort(data); break;
            case 7: enqueue(antrian); break;
            case 8: enqueueDarurat(antrian); break;
            case 9: dequeue(antrian, riwayat); break;
            case 10: tampilAntrian(antrian); break;
            case 11: peekAntrian(antrian); break;
            case 12: undo(riwayat, redoStack); break;
            case 13: redo(riwayat, redoStack); break;
            case 14: tampilRiwayat(riwayat); break;
            case 15: peekRiwayat(riwayat); break;
        }

    } while (pilihan != 0);

    return 0;
}