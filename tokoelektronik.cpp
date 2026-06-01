#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <exception>
#include <vector>
#include <sstream>
using namespace std;

// =============================================
// KELAS TokoElektronik (Etalase)
// =============================================
class TokoElektronik {
private:
    // Atribut private - array 3 elemen (enkapsulasi)
    array<string, 3> etalase;

public:
    // Constructor - isi data awal otomatis
    TokoElektronik() {
        etalase[0] = "Laptop ASUS VivoBook - Rp 8.500.000";
        etalase[1] = "Samsung Galaxy S24 - Rp 12.000.000";
        etalase[2] = "TV LED Sony 43 inch - Rp 6.750.000";
    }

    // Method public - ambil produk berdasarkan nomorRak
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (out_of_range& e) {
            throw string("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

// =============================================
// STRUCT Barang (untuk CRUD)
// =============================================
struct Barang {
    string kode;
    string nama;
    string harga;
    string stok;
};

// =============================================
// FUNGSI FILE I/O
// =============================================
const string FILE_GUDANG = "gudang.txt";

// Baca semua barang dari file
vector<Barang> bacaSemuaBarang() {
    vector<Barang> daftar;
    ifstream infile(FILE_GUDANG);

    if (infile.is_open()) {
        string baris;
        while (getline(infile, baris)) {
            if (baris.empty()) continue;

            // Format: kode|nama|harga|stok
            stringstream ss(baris);
            Barang b;
            getline(ss, b.kode,  '|');
            getline(ss, b.nama,  '|');
            getline(ss, b.harga, '|');
            getline(ss, b.stok,  '|');
            daftar.push_back(b);
        }
        infile.close();
    }
    return daftar;
}

// Tulis semua barang ke file
void tulisSemuaBarang(const vector<Barang>& daftar) {
    ofstream outfile(FILE_GUDANG, ios::out | ios::trunc);
    if (outfile.is_open()) {
        for (const Barang& b : daftar) {
            outfile << b.kode << "|" << b.nama << "|" << b.harga << "|" << b.stok << "\n";
        }
        outfile.close();
    }
}

// =============================================
// FUNGSI CRUD
// =============================================

// READ - tampilkan semua barang
void tampilkanBarang() {
    vector<Barang> daftar = bacaSemuaBarang();

    cout << "\n========================================" << endl;
    cout << "       DAFTAR BARANG GUDANG" << endl;
    cout << "========================================" << endl;

    if (daftar.empty()) {
        cout << "  [!] Gudang masih kosong." << endl;
    } else {
        cout << "No | Kode     | Nama Barang              | Harga           | Stok" << endl;
        cout << "---|----------|--------------------------|-----------------|-----" << endl;
        for (int i = 0; i < daftar.size(); i++) {
            cout << (i + 1) << "  | "
                 << daftar[i].kode  << " | "
                 << daftar[i].nama  << " | "
                 << daftar[i].harga << " | "
                 << daftar[i].stok  << endl;
        }
    }
    cout << "========================================\n" << endl;
}

// CREATE - tambah barang baru
void tambahBarang() {
    Barang b;
    cout << "\n--- TAMBAH BARANG BARU ---" << endl;
    cout << "Kode Barang  : "; cin >> b.kode;
    cin.ignore();
    cout << "Nama Barang  : "; getline(cin, b.nama);
    cout << "Harga        : "; getline(cin, b.harga);
    cout << "Stok         : "; getline(cin, b.stok);

    ofstream outfile(FILE_GUDANG, ios::app);
    if (outfile.is_open()) {
        outfile << b.kode << "|" << b.nama << "|" << b.harga << "|" << b.stok << "\n";
        outfile.close();
        cout << "\n[✓] Barang berhasil ditambahkan ke gudang!\n" << endl;
    } else {
        cout << "\n[!] Gagal membuka file gudang.\n" << endl;
    }
}

// UPDATE - perbarui data barang
void updateBarang() {
    tampilkanBarang();
    vector<Barang> daftar = bacaSemuaBarang();

    if (daftar.empty()) return;

    int pilihan;
    cout << "Masukkan nomor barang yang ingin diupdate: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > (int)daftar.size()) {
        cout << "\n[!] Nomor tidak valid.\n" << endl;
        return;
    }

    Barang& b = daftar[pilihan - 1];
    cout << "\nData lama -> Nama: " << b.nama << " | Harga: " << b.harga << " | Stok: " << b.stok << endl;

    cin.ignore();
    cout << "Nama Baru  : "; getline(cin, b.nama);
    cout << "Harga Baru : "; getline(cin, b.harga);
    cout << "Stok Baru  : "; getline(cin, b.stok);

    tulisSemuaBarang(daftar);
    cout << "\n[✓] Data barang berhasil diperbarui!\n" << endl;
}

// DELETE - hapus barang
void hapusBarang() {
    tampilkanBarang();
    vector<Barang> daftar = bacaSemuaBarang();

    if (daftar.empty()) return;

    int pilihan;
    cout << "Masukkan nomor barang yang ingin dihapus: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > (int)daftar.size()) {
        cout << "\n[!] Nomor tidak valid.\n" << endl;
        return;
    }

    string namaHapus = daftar[pilihan - 1].nama;
    daftar.erase(daftar.begin() + (pilihan - 1));
    tulisSemuaBarang(daftar);

    cout << "\n[✓] Barang \"" << namaHapus << "\" berhasil dihapus!\n" << endl;
}

// =============================================
// SIMULASI ETALASE (Exception Handling)
// =============================================
void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n========================================" << endl;
    cout << "       SIMULASI ETALASE TOKO" << endl;
    cout << "========================================" << endl;

    // Skenario 1 - Indeks ke-1 (sukses)
    cout << "\n[Skenario 1] Ambil barang di rak indeks 1..." << endl;
    try {
        string produk = toko.ambilProduk(1);
        cout << "[✓] Berhasil: " << produk << endl;
    }
    catch (string& pesanError) {
        cout << "[✗] " << pesanError << endl;
    }

    // Skenario 2 - Indeks ke-5 (gagal)
    cout << "\n[Skenario 2] Ambil barang di rak indeks 5..." << endl;
    try {
        string produk = toko.ambilProduk(5);
        cout << "[✓] Berhasil: " << produk << endl;
    }
    catch (string& pesanError) {
        cout << "[✗] " << pesanError << endl;
    }

    cout << "\n========================================\n" << endl;
}

// =============================================
// MAIN - Menu Utama
// =============================================
int main() {
    int pilihan;

    cout << "========================================" << endl;
    cout << "   SISTEM MANAJEMEN TOKO ELEKTRONIK" << endl;
    cout << "          \"GIBRAN JAYA\"" << endl;
    cout << "========================================" << endl;

    do {
        // Auto tampilkan daftar barang saat menu dibuka
        tampilkanBarang();

        cout << "MENU UTAMA:" << endl;
        cout << "1. Tambah Barang (Create)" << endl;
        cout << "2. Update Barang (Update)" << endl;
        cout << "3. Hapus Barang  (Delete)" << endl;
        cout << "4. Simulasi Etalase (Exception Handling)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahBarang();    break;
            case 2: updateBarang();    break;
            case 3: hapusBarang();     break;
            case 4: simulasiEtalase(); break;
            case 0: cout << "\n[!] Terima kasih, program selesai.\n" << endl; break;
            default: cout << "\n[!] Pilihan tidak valid!\n" << endl; break;
        }

    } while (pilihan != 0);

    return 0;
}