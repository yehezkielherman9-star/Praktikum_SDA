#include <iostream>
#include <string>
using namespace std;

struct Tiket {
    string namaPenumpang;
    string asal;
    string tujuan;
    Tiket* next;
};

Tiket* front = NULL;
Tiket* rear = NULL;

Tiket* top = NULL;

void enqueue() {
    Tiket* baru = new Tiket();

    cout << "Nama: "; cin >> baru->namaPenumpang;
    cout << "Asal: "; cin >> baru->asal;
    cout << "Tujuan: "; cin >> baru->tujuan;
    baru->next = NULL;

    if (front == NULL) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }

    cout << "Masuk antrian!\n";
}

void dequeue() {
    if (front == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    Tiket* hapus = front;
    cout << "Diproses: " << hapus->namaPenumpang
         << " (" << hapus->asal << " -> " << hapus->tujuan << ")\n";

    front = front->next;

    if (front == NULL) rear = NULL;

    hapus->next = top;
    top = hapus;
}

void peekAntrian() {
    if (front == NULL) {
        cout << "Antrian kosong\n";
        return;
    }

    cout << "Terdepan: " << front->namaPenumpang << endl;
}

void tampilAntrian() {
    if (front == NULL) {
        cout << "Antrian kosong\n";
        return;
    }

    Tiket* temp = front;
    cout << "\n=== Antrian ===\n";
    while (temp != NULL) {
        cout << temp->namaPenumpang << " | "
             << temp->asal << " -> "
             << temp->tujuan << endl;
        temp = temp->next;
    }
}

void pushManual() {
    Tiket* baru = new Tiket();

    cout << "Nama: "; cin >> baru->namaPenumpang;
    cout << "Asal: "; cin >> baru->asal;
    cout << "Tujuan: "; cin >> baru->tujuan;

    baru->next = top;
    top = baru;

    cout << "Masuk riwayat (push manual)\n";
}

void popRiwayat() {
    if (top == NULL) {
        cout << "Riwayat kosong!\n";
        return;
    }

    Tiket* hapus = top;
    cout << "Hapus: " << hapus->namaPenumpang << endl;

    top = top->next;
    delete hapus;
}

void peekRiwayat() {
    if (top == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }

    cout << "Terakhir: " << top->namaPenumpang << endl;
}

void tampilRiwayat() {
    if (top == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }

    Tiket* temp = top;
    cout << "\n=== Riwayat ===\n";
    while (temp != NULL) {
        cout << temp->namaPenumpang << " | "
             << temp->asal << " -> "
             << temp->tujuan << endl;
        temp = temp->next;
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n=== MENU LINKED LIST ===\n";
        cout << "1. Enqueue (Pesan Tiket)\n";
        cout << "2. Dequeue (Proses Tiket)\n";
        cout << "3. Peek Antrian\n";
        cout << "4. Tampil Antrian\n";
        cout << "5. Push Manual (Riwayat)\n";
        cout << "6. Pop Riwayat\n";
        cout << "7. Peek Riwayat\n";
        cout << "8. Tampil Riwayat\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: peekAntrian(); break;
            case 4: tampilAntrian(); break;
            case 5: pushManual(); break;
            case 6: popRiwayat(); break;
            case 7: peekRiwayat(); break;
            case 8: tampilRiwayat(); break;
        }

    } while (pilihan != 0);

    return 0;
}