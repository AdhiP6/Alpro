#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Barang {
    string kode;
    string nama;
    int harga;
    int stok;
};

Barang toko[100];
int jumlahbarang = 0;
const string namaFile = "datatoko2.txt";

void simpanKeFile(Barang* dataBarang, int jumlahbarang) {
    ofstream file(namaFile);
    if (file.is_open()) {
        file << jumlahbarang << endl;
        for (int i = 0; i < jumlahbarang; i++) {
            file << dataBarang[i].kode << endl;
            file << dataBarang[i].nama << endl;
            file << dataBarang[i].harga << endl;
            file << dataBarang[i].stok << endl;
        }
        file.close();
        cout << "Data berhasil disimpan ke file!\n";
    } else {
        cout << "Error: Tidak dapat membuka file untuk menyimpan!\n";
    }
}

void bacaDariFile(Barang* dataBarang, int* jumlahbarang) {
    ifstream file(namaFile);
    if (file.is_open()) {
        file >> *jumlahbarang;
        file.ignore(); 
        
        for (int i = 0; i < *jumlahbarang; i++) {
            getline(file, dataBarang[i].kode);
            getline(file, dataBarang[i].nama);
            file >> dataBarang[i].harga;
            file >> dataBarang[i].stok;
            file.ignore();
        }
        file.close();
        cout << "Data berhasil dimuat dari file!\n";
    } else {
        cout << "File tidak ditemukan, menggunakan data default.\n";
    }
}

bool cekkode(const Barang* toko, int jumlahbarang, const string& kode) {
    const Barang* ptr = toko;
    for (int i = 0; i < jumlahbarang; i++) {
        if (ptr->kode == kode) {
            return true; 
        }
        ptr++;
    }
    return false; 
}

void tampilkanMenu() {
    cout << "\033c";
    cout << "\n==========================================\n";
    cout << "           MENU MANAJEMEN TOKO\n";
    cout << "==========================================\n";
    cout << "1. Lihat Daftar Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Cari Barang\n";
    cout << "4. Urutkan Barang\n";
    cout << "5. Hapus Barang\n";
    cout << "6. Keluar\n";
    cout << "==========================================\n";
}

void menuSorting(){
    cout << "\033c";
    cout << "\n==========================================\n";
    cout << "           PILIHAN SORTING\n";
    cout << "==========================================\n";
    cout << "1. Bubble Sort (berdasarkan nama)\n";
    cout << "2. Quick Sort (berdasarkan kode)\n";
    cout << "==========================================\n";
}

void tampilkanSemuaBarang(const Barang* toko, int jumlahbarang) {
    cout << "\n==========================================\n";
    cout << "           DAFTAR SEMUA BARANG\n";
    cout << "==========================================\n";
    if (jumlahbarang == 0) {
        cout << "\nBelum ada barang di toko.\n\n";
        system("pause");
        return;
    }
    cout << left << setw(10) << "Kode" 
         << setw(15) << "Nama" 
         << setw(12) << "Harga" 
         << setw(8) << "Stok" << endl;
    cout << "------------------------------------------\n";
    
    for (int i = 0; i < jumlahbarang; i++) {
        cout << left << setw(10) << (toko + i)->kode
             << setw(15) << (toko + i)->nama
             << "Rp " << setw(10) << (toko + i)->harga
             << setw(10) << (toko + i)->stok << endl;
    }
    cout << "==========================================\n";
    cout<<endl;
    system("pause");
}

void tambahBarang(Barang* toko, int& jumlahbarang) {
    int jmlh;
    cout << "\033c";
    cout << "\n==========================================\n";
    cout << "            TAMBAH BARANG BARU\n";
    cout << "==========================================\n";
    cout << "\nJumlah barang yang akan ditambahkan: ";cin>> jmlh;

    if (jumlahbarang + jmlh > 100) {
        cout << "Toko hanya dapat menyimpan maksimal 100 barang. Tidak dapat menambah lebih banyak.\n";
        return;
    }

    Barang* ptr = toko + jumlahbarang; 
    for (int i = 0; i < jmlh; i++) {
        string kodeinput;
        bool kodevalid = false;
        do{
        cout << "\nMasukkan Kode Barang  : ";cin >>kodeinput;
        if (cekkode(toko, jumlahbarang, kodeinput)) {
                cout << "ERROR: Kode '" << kodeinput << "' sudah ada! Silakan masukkan kode yang berbeda.\n";
                kodevalid = false;
            } else {
                ptr->kode = kodeinput;
                kodevalid = true;
            }
        }while(!kodevalid);

        cin.ignore(); 
        cout << "Masukkan Nama Barang  : ";
        getline(cin, ptr->nama);
        cout << "Masukkan Harga Barang : ";
        cin >> ptr->harga;
        cout << "Masukkan Stok Barang  : ";
        cin >> ptr->stok;
        ptr++; 
        jumlahbarang++;
    }
    cout << "\nBarang berhasil ditambahkan!\n\n";
    simpanKeFile(toko, jumlahbarang);
    system("pause");
}

void cariBarang(const Barang* toko, int jumlahbarang) { //sequensial
    cout << "\033c";
    string kode;
    cout << "\n==========================================\n";
    cout << "              CARI BARANG\n";
    cout << "==========================================\n";
    cout << "Masukkan kode yang dicari : ";cin>>kode;
    bool ditemukan = false;
    const Barang* ptr = toko; 
    
    for (int i = 0; i < jumlahbarang; i++) {
        if (ptr->kode == kode) {
            cout << "\n--- BARANG DITEMUKAN ---\n";
            cout << "Kode  : " << ptr->kode << "\n";
            cout << "Nama  : " << ptr->nama << "\n";
            cout << "Harga : Rp " << ptr->harga << "\n";
            cout << "Stok  : " << ptr->stok << "\n";
            ditemukan = true;
            break;
        }
        ptr++;
    }
    if (!ditemukan) {
        cout << "Barang dengan kode " << kode << " tidak ditemukan.\n\n";
    }
    system("pause");
}

void tampilkanBarang(const Barang* toko, int jumlahbarang) {
    cout << left << setw(10) << "Kode" 
         << setw(15) << "Nama" 
         << setw(12) << "Harga" 
         << setw(8) << "Stok" << endl;
    cout << "------------------------------------------\n";
    
    const Barang* ptr = toko; 
    for (int i = 0; i < jumlahbarang; i++) {
        cout << left << setw(10) << ptr->kode
             << setw(15) << ptr->nama
             << "Rp " << setw(10) << ptr->harga
             << setw(10) << ptr->stok << endl;
        ptr++; 
    }
    cout << endl;
}

void bubbleSort(Barang* toko, int jumlahbarang, bool ascending) {
    cout << "\nData sebelum diurutkan (berdasarkan nama):\n";
    cout << "==========================================\n";
    tampilkanBarang(toko, jumlahbarang);

    for (int i = 0; i < jumlahbarang - 1; i++) {
        for (int j = 0; j < jumlahbarang - i - 1; j++) {
            Barang* ptr1 = toko + j;
            Barang* ptr2 = toko + j + 1;
            
            bool Swap = false;
            if (ascending) {
                Swap = (ptr1->nama > ptr2->nama);
            } else {
                Swap = (ptr1->nama < ptr2->nama);
            }
            if (Swap) {
                swap(*ptr1, *ptr2);
            }
        }
    }
    cout << "\nData setelah diurutkan " << (ascending ? "(A-Z)" : "(Z-A)") << ":\n";
    cout << "==========================================\n";
    tampilkanBarang(toko, jumlahbarang);
    system("pause");
}

string cekangka(const string& kode) {
    bool Angka = true;
    for (int i = 0; i < kode.length(); i++) {
        if (kode[i] < '0' || kode[i] > '9') {
            Angka = false;
            break;
        }
    }
    
    if (Angka) {
        // Tambahkan nol di depan hingga 10 digit untuk konsistensi
        string hasil = "";
        for (int i = 0; i < 10 - kode.length(); i++) {
            hasil += "0";
        }
        hasil += kode;
        return hasil;
    }
    return kode; // Kembalikan apa adanya jika bukan angka
}

int partition(Barang* toko, int low, int high, bool ascending) {
    string pivot = cekangka((toko + high)->kode);
    int i = (low - 1);
    
    for (int j = low; j < high; j++) {
        bool condition = false;
        string kodeSekarang = cekangka((toko + j)->kode);
        if (ascending) {
            condition = (kodeSekarang < pivot);
        } else {
            condition = (kodeSekarang > pivot);
        }
        
        if (condition) {
            i++;
            swap(*(toko + i), *(toko + j));
        }
    }
    swap(*(toko + i + 1), *(toko + high));
    return (i + 1);
}

void quickSort(Barang* toko, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(toko, low, high, ascending);
        quickSort(toko, low, pi - 1, ascending);
        quickSort(toko, pi + 1, high, ascending);
    }
}

void prosesQuickSort(Barang* toko, int jumlahbarang, bool ascending) {
    cout << "\nData sebelum diurutkan (berdasarkan kode):\n";
    cout << "==========================================\n";
    tampilkanBarang(toko, jumlahbarang);
    quickSort(toko, 0, jumlahbarang - 1, ascending);
    cout << "\nData setelah diurutkan " << (ascending ? "(A-Z)" : "(Z-A)") << ":\n";
    cout << "==========================================\n";
    tampilkanBarang(toko, jumlahbarang);
    system("pause");
}

int PilihanUrutan() {
    int urut;
    do {
        cout << "\nPilihan Urutan:\n";
        cout << "1. Ascending (A-Z)\n";
        cout << "2. Descending (Z-A)\n";
        cout << "Pilih (1-2): ";cin >> urut;
        if (urut < 1 || urut > 2) {
            cout << "Pilihan tidak valid! Silakan pilih 1 atau 2.\n";
        }
    } while (urut < 1 || urut > 2);
    return urut;
}

void menuUrutkan(Barang* toko, int jumlahbarang) {
    menuSorting();
    int pilih;
    cout << "Pilih sorting (1-2): ";cin >> pilih;
    
    switch (pilih) {
        case 1: {
            cout << "\033c";
            cout << "\n==========================================\n";
            cout << "      BUBBLE SORT (Berdasarkan Nama)\n";
            cout << "==========================================\n";
            int urut = PilihanUrutan();
            bool ascending = (urut == 1);
            cout << "\033c";
            bubbleSort(toko, jumlahbarang, ascending);
            break;
        }
        case 2: {
            cout << "\033c";
            cout << "\n==========================================\n";
            cout << "      QUICK SORT (Berdasarkan Kode)\n";
            cout << "==========================================\n";
            int urut = PilihanUrutan();
            bool ascending = (urut == 1);
            cout << "\033c";
            prosesQuickSort(toko, jumlahbarang, ascending);
            break;
        }
        default:
            cout << "\033c";
            cout << "Pilihan tidak valid!\n";
            system("pause");
            break;
    }
}

void hapusdata(Barang* toko, int* jumlahbarang) {
    cout << "\n==========================================\n";
    cout << "              HAPUS BARANG\n";
    cout << "==========================================\n";
    if (*jumlahbarang == 0) {
        cout << "\nTidak ada data barang untuk dihapus." << endl;
        system("pause");
        return;
    }

    string kodehapus;
    cout << "\nMasukkan kode barang yang akan dihapus: ";cin >> kodehapus;
    bool ditemukan = false;
    int indexhapus = -1;
    
    for (int i = 0; i < *jumlahbarang; i++) {
        if ((toko + i)->kode == kodehapus) {
            ditemukan = true;
            indexhapus = i;
            break;
        }
    }
    
    if (ditemukan) {
        Barang* barangtarget = toko + indexhapus;
        cout << "\nBarang yang akan dihapus:" << endl;
        cout << "Kode  : " << barangtarget->kode << "\n";
        cout << "Nama  : " << barangtarget->nama << "\n";
        cout << "Harga : Rp " << barangtarget->harga << "\n";
        cout << "Stok  : " << barangtarget->stok << "\n";
        
        char konfirmasi;
        cout << "\nYakin ingin menghapus? (y/n): ";
        cin >> konfirmasi;
        
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            for (int i = indexhapus; i < *jumlahbarang - 1; i++) {
                *(toko + i) = *(toko + i + 1);
            }
            (*jumlahbarang)--;
            cout << "\nData berhasil dihapus!" << endl;
            simpanKeFile(toko, *jumlahbarang);
        } else {
            cout << "\nPenghapusan dibatalkan." << endl;
        }
    } else {
        cout << "\nBarang dengan kode '" << kodehapus << "' tidak ditemukan." << endl;
    }
    system("pause");
}

int main() {
    int pilihan;
    system("cls");
    // Muat data dari file saat program dimulai
    bacaDariFile(toko, &jumlahbarang);
    
    do{
        tampilkanMenu();
        cout << "\nPilih menu (1-6): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\033c";
                tampilkanSemuaBarang(toko, jumlahbarang);
                break;
            case 2:
                cout << "\033c";
                tambahBarang(toko, jumlahbarang);
                break;
            case 3:
                cariBarang(toko, jumlahbarang);
                break;
            case 4:
                menuUrutkan(toko, jumlahbarang);
                break;
            case 5 :
                cout << "\033c";
                hapusdata(toko, &jumlahbarang);
                break;
            case 6:
                cout << "\033c";
                cout << "Menyimpan data sebelum keluar...\n";
                simpanKeFile(toko, jumlahbarang);
                cout << "\nTerima kasih telah menggunakan program ini.\n";
                return 0;
            default:
                cout << "\033c";
                cout << "Pilihan tidak valid.\n";
        }
    }while(pilihan != 6);
    return 0;
}