#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// /Di bawah ini merupakan data buku perpustakaan/
struct DataBuku{
    string nama_buku;
    string genre;
    string penulis;
    int tahun_penerbitan;
    bool status;
};

struct Peminjam{
    string nama;
    string no_hp;
    string alamat;
    string buku;
};


int PinjamBuku(){
    fstream file;

    file.open("data_peminjam.txt", ios::app);
    string line;

    if(file.is_open()){
        Peminjam peminjam;

        cout << "Masukkan nama: " << endl;
        cin.ignore();
        getline(cin, peminjam.nama);
        
        cout << "Masukkan nomor hp: " << endl;
        cin >> peminjam.no_hp;
        cin.ignore();

        cout << "Masukkan alamat: " << endl;
        
        getline(cin, peminjam.alamat);

        cout << "Masukkan judul buku: " << endl;
        
        getline(cin, peminjam.buku);

        file << "Nama: " << peminjam.nama << endl;
        file << "No.Hp: " << peminjam.no_hp << endl;
        file << "Alamat: " << peminjam.alamat << endl;
        file << "Judul buku: " << peminjam.buku << endl;

        cout << "Data anda sudah tercatat!" << endl;

        file.close();
    } else {
        cout << "Tidak dapat dibuka" << endl;
    }

}

int DaftarBuku(){
    ifstream file("data_buku.txt");
    string line;

    if(file.is_open()){
        while(getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Tidak dapat dibuka" << endl;
    }
}

void MainMenu(){
    cout << "        ==== SELAMAT DATANG ====" << endl;
    cout << " ==== Perpustakaan UNESA Ketintang ====" << endl;                  
    cout << "                        " << endl;
    cout << "Pilih menu dibawah ini dengan menekan angka: " << endl;
    cout << "1. Pinjam buku" << endl;
    cout << "2. Daftar buku  " << endl;
    cout << "3. Cari buku  " << endl;
    cout << "4. Admin Mode " << endl;
}

void AdminMenu(){
    cout << "==== ADMIN MODE ====" << endl;
    cout << "1. Tambah buku" << endl;
    cout << "2. Kurangi buku" << endl;
    cout << "3. Lihat data peminjam" << endl;
    cout << "4. Ubah PIN Admin" << endl;
}

int TambahBuku(){
    fstream file;

    file.open("data_buku.txt", ios::app);
    string line;

    if(file.is_open()){
        DataBuku buku;

        cout << "Masukkan judul buku: " << endl;
        cin.ignore();
        getline(cin, buku.nama_buku);
        
        cout << "Masukkan tahun penerbitan: " << endl;
        cin >> buku.tahun_penerbitan;
        cin.ignore();

        cout << "Masukkan genre: " << endl;
        
        getline(cin, buku.genre);

        cout << "Masukkan penulis buku: " << endl;
        
        getline(cin, buku.penulis);

        file << "Judul buku: " << buku.nama_buku << endl;
        file << "Tahun terbit: " << buku.tahun_penerbitan << endl;
        file << "Genre: " << buku.genre << endl;
        file << "Penulis: " << buku.penulis << endl;
        file << " " << endl;

        cout << "Buku baru sudah tercatat!" << endl;
        
        file.close();
    } else {
        cout << "Tidak dapat dibuka" << endl;
    }

}
int lihat_datapeminjam(){
    ifstream file("data_peminjam.txt");
    string line;

    if(file.is_open()){
        while(getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Tidak dapat dibuka" << endl;
    }
}

int UbahPinAdmin(){
    
}



int main(){
    int opsi;
    
    // Untuk Admin Mode
    int pin_admin;
    int opsi_adminmode;

    MainMenu();
    cin >> opsi;
    switch (opsi)
    {
    case 1:
        /* algortima pinjam buku*/
        PinjamBuku();
        break;
    case 2:
        /* algoritma daftar buku*/
        DaftarBuku();
        break;
    case 3:

        break;
    case 4:
        cout << "Mohon input passcode: " << endl;
        cin >> pin_admin;
        if (pin_admin == 1234){
            AdminMenu();
            cin >> opsi_adminmode;
            switch (opsi_adminmode)
            {
                case 1:
                    TambahBuku();
                    break;
                case 2:

                    break;
                case 3:
                    lihat_datapeminjam();
                    break;
                case 4:

                    break;
            }
        }
    default:
        break;
    }




    return 0;
}