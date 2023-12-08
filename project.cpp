#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

const int BUKU_MAX = 100;

// /Di bawah ini merupakan data buku perpustakaan/
struct DataBuku{
    string nama_buku;
    string genre;
    string penulis;
    string tahun_penerbitan;
    bool status;
};

struct Peminjam{
    string nama;
    string no_hp;
    string alamat;
    string buku;
    string tanggal_pinjam;
};

void KembaliKeMenuSebelumnya() {
    cout << "Tekan 'Enter' untuk kembali ke Menu Sebelumnya...";
    cin.ignore();
    cin.get();
}

void PinjamBuku(){
    fstream file;

    file.open("data_peminjam.dat", ios::app);
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

         // Mendapatkan waktu saat ini
        auto now = system_clock::to_time_t(system_clock::now());

        // Format tanggal (DD/MM/YYYY)
        char formatted_date[11];
        strftime(formatted_date, sizeof(formatted_date), "%d/%m/%Y", localtime(&now));
        peminjam.tanggal_pinjam = formatted_date;

        file << "Nama: " << peminjam.nama << endl;
        file << "No.Hp: " << peminjam.no_hp << endl;
        file << "Alamat: " << peminjam.alamat << endl;
        file << "Judul buku: " << peminjam.buku << endl;
        file << "Tanggal peminjaman: " << peminjam.tanggal_pinjam << endl;
        cout << "Data anda sudah tercatat!" << endl;

        file.close();
    } else {
        cout << "Tidak dapat dibuka" << endl;
    }
}

int DaftarBuku(){
    ifstream file("data_buku.dat");
    string line;

    if(file.is_open()){
        while(getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Tidak dapat dibuka" << endl;
    }
    KembaliKeMenuSebelumnya();
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
     // Untuk Admin Mode
    int pin_admin;
    cout << "Mohon input passcode: " << endl;
        cin >> pin_admin;
        system("cls"); // clear pin
        if (pin_admin == 1234){
        cout << "==== ADMIN MODE ====" << endl;
        cout << "1. Tambah buku" << endl;
        cout << "2. Kurangi buku" << endl;
        cout << "3. Lihat data peminjam" << endl;
        cout << "4. Ubah PIN Admin" << endl;
        }
        else { // semisal input pin salah
            cout<< "PIN yang anda input salah!" << endl;
            return AdminMenu();
        }
}
DataBuku addBook(){
    DataBuku buku;

    do{
    cout<< "Masukkan judul buku: " << endl;
    getline(cin, buku.nama_buku);
    if(buku.nama_buku.empty()){
            cout<< "Nama buku tidak boleh kosong, silahkan ulangi lagi" << endl;
        }
    } while (buku.nama_buku.empty());
    

    do{
    cout << "Masukkan tahun buku: " << endl;
    getline(cin, buku.tahun_penerbitan);
    if(buku.tahun_penerbitan.empty()){
            cout<< "Tahun buku tidak boleh kosong, silahkan ulangi lagi" << endl;
        }
    } while (buku.tahun_penerbitan.empty());

    do{
    cout << "Masukkan genre buku: " << endl;
    getline(cin, buku.genre);
        if(buku.genre.empty()){
            cout<< "Genre buku tidak boleh kosong, silahkan ulangi lagi" << endl;
        }
    } while (buku.genre.empty());

    do{
    cout << "Masukkan nama penulis: " << endl;
    getline(cin, buku.penulis);
    if(buku.penulis.empty()){
            cout<< "Penulis buku tidak boleh kosong, silahkan ulangi lagi" << endl;
        }
    } while (buku.penulis.empty());

    return buku;
}

int WriteBookData(){
    DataBuku array_buku[BUKU_MAX];
    int jumlah_buku = 0;

    //Hasil input dari fungsi addBook() dimasukkan ke array
    while (jumlah_buku <= BUKU_MAX) {
        array_buku[jumlah_buku] = addBook();
        jumlah_buku++;

        char opsi_lanjut;
        cout<< "Tambah buku lain? (y/n)" << endl;
        cin >> opsi_lanjut;
        cin.ignore(); //bersihkan input buffer

        if (opsi_lanjut != 'y' && opsi_lanjut != 'Y') {
            break;
        }
    }

    fstream file;
    file.open("data_buku.dat", ios::out | ios::app);  // Membuka file dengan mode penulisan dan append

    // Menulis setiap buku dalam array ke file
    for (int i = 0; i < jumlah_buku; i++) {
        file << "Judul buku: " << array_buku[i].nama_buku << endl;
        file << "Tahun terbit: " << array_buku[i].tahun_penerbitan << endl;
        file << "Genre: " << array_buku[i].genre << endl;
        file << "Penulis: " << array_buku[i].penulis << endl;
        file << " " << endl;
    }

    file.close();  // Menutup file
    return 0;
}

int DeleteBookData() {
    string array_buku[BUKU_MAX];
    int jumlah_buku = 0;
    string line;

    fstream file;
    file.open("data_buku.dat", ios::in);  // Membuka file dengan mode pembacaan

    // Membaca setiap buku dalam file ke array
    while (getline(file, line)) {
        array_buku[jumlah_buku] = line;
        jumlah_buku++;
    }

    file.close();  // Menutup file

    // Menampilkan daftar buku
    for (int i = 0; i < jumlah_buku; i++) {
        cout << i+1 << ". " << array_buku[i].substr(12) << endl;  // asumsikan judul buku ada setelah "Judul buku: "
    }

    // Meminta pengguna untuk memilih buku untuk dihapus
    int index;
    cout << "Masukkan nomor buku yang ingin dihapus: ";
    cin >> index;
    cin.ignore(); //bersihkan input buffer

    // Menghapus buku dari array
    for (int i = index-1; i < jumlah_buku-1; i++) {
        array_buku[i] = array_buku[i+1];
    }
    jumlah_buku--;

    file.open("data_buku.dat", ios::out);  // Membuka file dengan mode penulisan

    // Menulis setiap buku dalam array ke file
    for (int i = 0; i < jumlah_buku; i++) {
        file << array_buku[i] << endl;
    }

    file.close();  // Menutup file

    return 0;
}

//fungsi old buat nambahin buku
void TambahBuku() {
    static DataBuku data_buku[BUKU_MAX];  // Menjadi static agar nilainya persist antar panggilan fungsi
    static int jumlah_buku = 0;

    fstream file;

    if (jumlah_buku >= BUKU_MAX) {
        cout << "Maaf, jumlah buku sudah mencapai batas maksimal." << endl;
        return;
    }

    file.open("data_buku.dat", ios::app | ios::out);

    if (file.is_open()) {
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

        data_buku[jumlah_buku++] = buku;

        file << "Judul buku: " << buku.nama_buku << endl;
        file << "Tahun terbit: " << buku.tahun_penerbitan << endl;
        file << "Genre: " << buku.genre << endl;
        file << "Penulis: " << buku.penulis << endl;
        file << " " << endl;

        cout << "Buku baru sudah tercatat!" << endl;

        file.close();
    } else {
        cout << "Tidak dapat membuka file" << endl;
    }
}

void KurangiBuku() {
    static DataBuku array_buku[BUKU_MAX];

    fstream file;
    file.open("data_buku.dat", ios::in);

    if (file.is_open()) {
        string line;
        int i = 0;

        cout << "List buku yang sudah terdaftar : " << endl;
        while (getline(file, line)) {
            if (line.find("Judul buku:") != string::npos) {
                cout << i + 1 << ". " << line.substr(line.find(":") + 2) << endl;
                i++;
            }
        }

        file.close();

        if (i == 0) {
            cout << "Tidak ada buku yang tersedia." << endl;
            return;
        }

        int nomor_buku;
        cout << "Pilih nomor buku yang ingin dihapus: ";
        cin >> nomor_buku;

        if (nomor_buku < 1 || nomor_buku > i) {
            cout << "Nomor buku tidak valid." << endl;
            return;
        }

        file.open("data_buku.dat", ios::out);

        for (int j = 0; j < i; j++) {
            if (j != nomor_buku - 1) {
                file << "Judul buku: " << array_buku[j].nama_buku << endl;
                file << "Tahun terbit: " << array_buku[j].tahun_penerbitan << endl;
                file << "Genre: " << array_buku[j].genre << endl;
                file << "Penulis: " << array_buku[j].penulis << endl;
                file << " " << endl;
            }
        }

        cout << "Buku berhasil dihapus." << endl;

        file.close();
    } else {
        cout << "Tidak dapat membuka file" << endl;
    }
}

int LihatDataPeminjam(){
    ifstream file("data_peminjam.dat");
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
    //Untuk main menu
    int opsi;

    MainMenu();
    cin >> opsi;
    system("cls"); //clear menu dari layar
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
        int opsi_adminmode;
        AdminMenu();
        cin >> opsi_adminmode;
        cin.ignore(); //clear input buffer
            system("cls");
            switch (opsi_adminmode)
            {
                case 1:
                    WriteBookData();
                    break;
                case 2:
                    DeleteBookData();
                    break;
                case 3:
                    LihatDataPeminjam();
                    break;
                case 4:
                    break;
            }
    default:
        break;
    }
    return 0;
}
