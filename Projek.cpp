#include <iostream>
#include <iomanip>
using namespace std;

struct Barang {
    string kode;
    string nama;
    int harga;
    int stok;
};

void tampilkanMenu() {
    cout << "\nMenu Manajemen Toko:\n";
    cout << "1. Lihat Daftar Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Keluar\n";
}

void tampilkanSemuaBarang(const Barang toko[], int jumlahbarang) {
    if (jumlahbarang == 0) {
        cout << "\nBelum ada barang di toko.\n";
        return;
    }

    cout << "\nDaftar Semua Barang:\n";
    cout << setw(10) << "Kode" << setw(20) << "Nama" << setw(10) << "Harga" << setw(10) << "Stok" << endl;
    for (int i = 0; i < jumlahbarang; i++) {
        cout << setw(10) << toko[i].kode
             << setw(20) << toko[i].nama
             << setw(10) << toko[i].harga
             << setw(10) << toko[i].stok << endl;
    }
}

void tambahBarang(Barang toko[], int &jumlahbarang) {
    int jmlh;
    cout << "\nJumlah barang yang akan ditambahkan: ";cin>> jmlh;

    if (jumlahbarang + jmlh > 100) {
        cout << "Toko hanya dapat menyimpan maksimal 100 barang. Tidak dapat menambah lebih banyak.\n";
        return;
    }

    for (int i = 0; i < jmlh; i++) {
        cout << "\nMasukkan Kode Barang  : ";
        cin >> toko[jumlahbarang].kode;
        cin.ignore(); 
        cout << "Masukkan Nama Barang  : ";
        getline(cin, toko[jumlahbarang].nama);
        cout << "Masukkan Harga Barang : ";
        cin >> toko[jumlahbarang].harga;
        cout << "Masukkan Stok Barang  : ";
        cin >> toko[jumlahbarang].stok;
        jumlahbarang++;
    }
    cout << "\nBarang berhasil ditambahkan!\n";
}

int main() {
    Barang toko[100];
    int jumlahbarang = 0;
    int pilihan;
    while (true) {
        tampilkanMenu();
        cout << "\nPilih menu (1-3): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanSemuaBarang(toko, jumlahbarang);
                break;
            case 2:
                tambahBarang(toko, jumlahbarang);
                break;
            case 3:
                cout << "Terima kasih telah menggunakan program ini.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}