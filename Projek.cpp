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
    cout << "3. Hitung Total Stok Barang\n";
    cout << "4. Cari barang\n";
    cout << "5. Keluar\n";
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

int hitungtotalstok(const Barang toko[], int jumlahbarang, int n = 0) {
    if (n >= jumlahbarang) {
        return 0;  
    }
    return toko[n].stok + hitungtotalstok(toko, jumlahbarang, n + 1);
}

void cariBarang(const Barang toko[], int jumlahBarang, string kode) { //sequensial
    bool ditemukan = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (toko[i].kode == kode) {
            cout << "\nBarang ditemukan: \n";
            cout << "Kode  : " << toko[i].kode << "\n";
            cout << "Nama  : " << toko[i].nama << "\n";
            cout << "Harga : " << toko[i].harga << "\n";
            cout << "Stok  : " << toko[i].stok << "\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Barang dengan kode " << kode << " tidak ditemukan.\n";
    }
}

int main() {
    Barang toko[100];
    int jumlahbarang = 0;
    int pilihan;
    string kode;
    while (true) {
        tampilkanMenu();
        cout << "\nPilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanSemuaBarang(toko, jumlahbarang);
                break;
            case 2:
                tambahBarang(toko, jumlahbarang);
                break;
            case 3:
                cout << "\nTotal stok barang di toko : " << hitungtotalstok(toko,jumlahbarang) << " stok barang" << endl;
                break;
            case 4:
                cout << "\nMasukkan Kode Barang yang dicari: ";cin >> kode;
                cariBarang(toko, jumlahbarang, kode);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}