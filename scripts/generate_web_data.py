#!/usr/bin/env python3
"""
DASPRO Web Data Generator
Memindai seluruh folder tugas, membaca kode sumber C++, menghitung statistik,
mengekstrak dokumen terkait (PDF/DOCX), dan menghasilkan file data assets/js/assignments.js
untuk website portal tugas interaktif.
"""

import os
import sys
import re
import json
import urllib.parse
from pathlib import Path
from datetime import datetime

# UTF-8 encoding support
if sys.platform == "win32":
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:
        pass

ROOT_DIR = Path(__file__).resolve().parent.parent

PROFILE = {
    "name": "Muhammad Fajri Setyawan",
    "nim": "A11.2026.16638",
    "course": "Dasar Pemrograman (DASPRO)",
    "prodi": "Teknik Informatika",
    "univ": "Universitas Dian Nuswantoro (UDINUS)",
    "language": "C++17",
    "github_user": "LazenFajri",
    "repo_name": "daspro_A11.2026.16638",
    "semester": "Semester 1 (Tahun Akademik 2026/2027)",
    "dosen": "Dosen Pengampu DASPRO TI UDINUS"
}

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', str(s))]

def format_file_size(size_bytes):
    if size_bytes < 1024:
        return f"{size_bytes} B"
    elif size_bytes < 1024 * 1024:
        return f"{size_bytes / 1024:.1f} KB"
    else:
        return f"{size_bytes / (1024 * 1024):.1f} MB"

def count_lines_of_code(content):
    return sum(1 for line in content.splitlines() if line.strip())

# Kamus deskripsi dan konsep cerdas untuk setiap kasus
KNOWLEDGE_BASE = {
    # Daspro Latihan - Latihan 1
    "Data Sepatu Sederhana.cpp": {
        "title": "Data Sepatu Sederhana (ADT Struct)",
        "topic": "Pendefinisian Abstract Data Type (ADT Struct) & Inisialisasi Data Statis",
        "concepts": ["ADT Struct", "Typedef", "Tipe Bentukan", "Format Output"],
        "description": "Mendefinisikan entitas data sepatu menggunakan tipe data bentukan struct (merk, nomor, warna, ukuran, harga) dan menampilkannya dalam format ringkas.",
        "analysis": "Program ini mengimplementasikan konsep dasar ADT (Abstract Data Type) menggunakan struct C++. Struktur data 'Sepatu' mengemas beberapa atribut heterogen (string, integer, double) menjadi satu kesatuan data terstruktur.",
        "simulated": [
            "$ g++ -std=c++17 'Data Sepatu Sederhana.cpp' -o program && ./program",
            "============================================================",
            "                 DATA IDENTITAS SEPATU                      ",
            "============================================================",
            "Merk Sepatu   : Nike Air Max",
            "Nomor Seri    : 101",
            "Warna         : Pink White",
            "Ukuran (EU)   : 38",
            "Harga Satuan  : Rp 1.200.000",
            "============================================================",
            "[Program selesai dieksekusi dengan kode exit 0]"
        ]
    },
    "Input Data Sepatu Interaktif.cpp": {
        "title": "Input Data Sepatu Interaktif",
        "topic": "I/O Dinamis Berbasis Konsol & Pengisian Anggota Struct",
        "concepts": ["Input / Output (cin/cout)", "ADT Struct", "Manipulator I/O", "String IO"],
        "description": "Membaca masukan atribut sepatu dari pengguna melalui keyboard secara dinamis dan menampilkannya kembali dalam format terstruktur.",
        "analysis": "Menggunakan objek cin dan manipulasi alur I/O untuk mengisi variabel bertipe struct secara interaktif saat runtime.",
        "simulated": [
            "$ g++ -std=c++17 'Input Data Sepatu Interaktif.cpp' -o program && ./program",
            "Masukkan Merk Sepatu   : Adidas Ultraboost",
            "Masukkan Nomor Seri    : 202",
            "Masukkan Warna         : Core Black",
            "Masukkan Ukuran (EU)   : 42",
            "Masukkan Harga (Rp)    : 1850000",
            "",
            "---------------- HASIL PENCATATAN ----------------",
            "Merk   : Adidas Ultraboost",
            "Seri   : 202",
            "Warna  : Core Black | Ukuran: 42",
            "Harga  : Rp 1.850.000",
            "Status : Berhasil dicatat ke memori."
        ]
    },
    "Pencatatan Spesifikasi Lengkap Sepatu.cpp": {
        "title": "Spesifikasi Lengkap Sepatu & Kategori",
        "topic": "Struktur Data Kompleks dengan Multi-Atribut & Kategori",
        "concepts": ["ADT Struct", "String Handling", "Multi-Atribut", "I/O Stream"],
        "description": "Mencatat spesifikasi mendalam dari produk sepatu mencakup bahan material, kategori olahraga, dan harga dengan validasi tipe data.",
        "analysis": "Memperluas struktur data dengan atribut kategori dan spesifikasi teknis untuk mengelola katalog produk secara komprehensif.",
        "simulated": [
            "$ g++ -std=c++17 'Pencatatan Spesifikasi Lengkap Sepatu.cpp' -o program && ./program",
            "=== FORM SPESIFIKASI LENGKAP SEPATU ===",
            "Nama Produk     : Hoka Clifton 9",
            "Kategori        : Road Running",
            "Material Sol    : EVA Foam",
            "Ukuran          : 43",
            "Harga           : Rp 2.499.000",
            "",
            ">> Data spesifikasi berhasil diverifikasi dan disimpan."
        ]
    },
    "Kalkulasi Nilai Total Aset Stok Sepatu.cpp": {
        "title": "Kalkulasi Nilai Total Aset Stok Sepatu",
        "topic": "Kombinasi ADT Struct, Aritmatika Akumulasi & Valuasi Finansial",
        "concepts": ["Aritmatika Finansial", "ADT Struct", "Perkalian Satuan x Stok", "Format Mata Uang"],
        "description": "Menghitung total nilai valuasi aset stok gudang sepatu dengan mengalikan harga satuan dengan kuantitas stok yang tersedia.",
        "analysis": "Program mengkombinasikan tipe struct dengan perhitungan matematika keuangan: Total Valuasi = Kuantitas Stok * Harga Satuan.",
        "simulated": [
            "$ g++ -std=c++17 'Kalkulasi Nilai Total Aset Stok Sepatu.cpp' -o program && ./program",
            "Nama Barang     : Puma Nitro Elite",
            "Jumlah Stok     : 15 Pasang",
            "Harga Satuan    : Rp 1.500.000",
            "----------------------------------------",
            "Total Nilai Aset: Rp 22.500.000",
            ">> Status: Inventarisasi Aset Valid."
        ]
    },
    "Koleksi Kendaraan Mahasiswa ADT dan Array.cpp": {
        "title": "Infografis Koleksi Kendaraan ADT & Array",
        "topic": "Array of Struct (Struktur Data Homogen Multi-Entitas)",
        "concepts": ["Array of Struct", "Iterasi Loop For", "Format Tabel", "Manipulator I/O"],
        "description": "Pengelolaan data inventaris unit kendaraan bermotor mahasiswa menggunakan array of struct dan ditampilkan dalam format tabel infografis.",
        "analysis": "Mengimplementasikan konsep Array of Struct untuk merepresentasikan koleksi banyak unit kendaraan. Menggunakan loop for untuk traversal dan formatting tabel yang rapi.",
        "simulated": [
            "$ g++ -std=c++17 'Koleksi Kendaraan Mahasiswa ADT dan Array.cpp' -o program && ./program",
            "=================================================================",
            "              DAFTAR KOLEKSI KENDARAAN MAHASISWA                 ",
            "=================================================================",
            "No  Jenis Kendaraan    Merk / Tipe       Tahun  No. Polisi       ",
            "-----------------------------------------------------------------",
            "1   Sepeda Motor       Honda Vario 160   2023   H 4567 BZ        ",
            "2   Sepeda Motor       Yamaha NMAX 155   2024   H 1234 XY        ",
            "3   Mobil              Toyota Yaris GR   2022   H 8899 AB        ",
            "-----------------------------------------------------------------",
            "Total Terdata : 3 Unit Kendaraan"
        ]
    },
    "Inventaris Barang Pribadi Mahasiswa.cpp": {
        "title": "Inventaris Barang Pribadi Mahasiswa",
        "topic": "Pencatatan Multi-Item, Akumulasi Nilai Barang & Array of Struct",
        "concepts": ["Array of Struct", "Akumulasi Total", "Format Rupiah", "Array 1D"],
        "description": "Mencatat, menyimpan, dan merekapitulasi total estimasi nilai dari seluruh barang pribadi dan perlengkapan perkuliahan mahasiswa.",
        "analysis": "Menggunakan Array of Struct untuk mendata barang pribadi (laptop, tablet, buku, tas) beserta estimasi harganya, lalu menghitung akumulasi total nilai inventaris.",
        "simulated": [
            "$ g++ -std=c++17 'Inventaris Barang Pribadi Mahasiswa.cpp' -o program && ./program",
            "=================================================================",
            "                  INVENTARIS BARANG PRIBADI                      ",
            "=================================================================",
            "1. Laptop ASUS ROG Zephyrus      : Rp 21.000.000",
            "2. Tablet iPad Air               : Rp 10.500.000",
            "3. Mechanical Keyboard           : Rp  1.200.000",
            "4. Ransel Mahasiswa              : Rp    450.000",
            "-----------------------------------------------------------------",
            "TOTAL ESTIMASI NILAI INVENTARIS  : Rp 33.150.000"
        ]
    },
    "Gedung Udinus.cpp": {
        "title": "Estimasi Tinggi Gedung UDINUS",
        "topic": "Trigonometri & Perhitungan Proporsi Fisik Bangunan",
        "concepts": ["Trigonometri Dasar", "Aritmatika Float", "Format Output", "Estimasi Fisik"],
        "description": "Menghitung taksiran ketinggian beberapa gedung di lingkungan kampus Universitas Dian Nuswantoro (UDINUS) menggunakan formula proporsi dan kalkulasi matematis.",
        "analysis": "Mengaplikasikan perhitungan rasio lantai dan estimasi ketinggian per tingkat untuk menentukan profil elevasi gedung kampus.",
        "simulated": [
            "$ g++ -std=c++17 'Gedung Udinus.cpp' -o program && ./program",
            "=========================================================",
            "          ESTIMASI TINGGI GEDUNG KAMPUS UDINUS           ",
            "=========================================================",
            "Gedung H (Rektorat)      : 7 Lantai  -> Estimasi: 28.0 Meter",
            "Gedung D (Fakultas TI)   : 8 Lantai  -> Estimasi: 32.0 Meter",
            "Gedung E (Lab Komputer)  : 6 Lantai  -> Estimasi: 24.0 Meter",
            "---------------------------------------------------------",
            "Rata-rata Tinggi Gedung  : 28.0 Meter"
        ]
    },

    # Daspro Latihan - Latihan 2
    "Data KTP.cpp": {
        "title": "Pendataan Kartu Tanda Penduduk (KTP)",
        "topic": "ADT Struct Kependudukan & Input String Berjarak (getline)",
        "concepts": ["ADT Struct Kependudukan", "cin.getline / cin >>", "String Spasi", "Format Cetak"],
        "description": "Membaca rekaman data kependudukan melalui keyboard (NIK, Nama, Tempat/Tgl Lahir, Alamat, Agama, Pekerjaan) dan mencetak kembali menyerupai format KTP asli.",
        "analysis": "Menangani input string multi-kata yang mengandung karakter spasi menggunakan teknik getline dan mencetaknya dalam tata letak visual menyerupai blangko KTP elektronik.",
        "simulated": [
            "$ g++ -std=c++17 'Data KTP.cpp' -o program && ./program",
            "============================================================",
            "             PROVINSI JAWA TENGAH - KOTA SEMARANG           ",
            "                 KARTU TANDA PENDUDUK (KTP)                 ",
            "============================================================",
            "NIK           : 3374101234560001",
            "Nama          : MUHAMMAD FAJRI SETYAWAN",
            "Tempat/Tgl    : SEMARANG, 15-08-2005",
            "Jenis Kelamin : LAKI-LAKI",
            "Alamat        : JL. NAKULA I NO. 5",
            "  RT/RW       : 001/002",
            "  Kel/Desa    : PENDRIKAN KIDUL",
            "  Kecamatan   : SEMARANG TENGAH",
            "Agama         : ISLAM",
            "Status        : BELUM KAWIN",
            "Pekerjaan     : PELAJAR/MAHASISWA",
            "Kewarganegaraan: WNI",
            "============================================================"
        ]
    },
    "Perhitungan Volume Balok.cpp": {
        "title": "Perhitungan Volume Balok",
        "topic": "Fungsi Geometri Dasar & Aritmatika 3 Dimensi",
        "concepts": ["Geometri 3D", "Fungsi Matematika", "Input / Output", "Aritmatika"],
        "description": "Menghitung volume bangun ruang balok berdasarkan input dinamis panjang, lebar, dan tinggi.",
        "analysis": "Rumus: Volume = Panjang * Lebar * Tinggi. Menggunakan tipe floating point/double untuk akurasi presisi desimal.",
        "simulated": [
            "$ g++ -std=c++17 'Perhitungan Volume Balok.cpp' -o program && ./program",
            "=== KALKULATOR VOLUME BALOK ===",
            "Masukkan Panjang (cm) : 12",
            "Masukkan Lebar   (cm) : 8",
            "Masukkan Tinggi  (cm) : 5",
            "-------------------------------",
            "Volume Balok = 480 cm^3"
        ]
    },
    "Rata Rata Volume Dua Kardus.cpp": {
        "title": "Rata-Rata Volume Dua Kardus",
        "topic": "Komparasi Dua Objek Geometris & Rata-rata Aritmatik",
        "concepts": ["Geometri Balok", "Rata-rata (Mean)", "Multi-Input", "Aritmatika"],
        "description": "Menghitung volume dari dua buah wadah kardus serta mencari nilai rata-rata dari kedua volume kardus tersebut.",
        "analysis": "Menghitung Vol1 = P1*L1*T1 dan Vol2 = P2*L2*T2, kemudian menentukan nilai tengah melalui rata-rata = (Vol1 + Vol2) / 2.0.",
        "simulated": [
            "$ g++ -std=c++17 'Rata Rata Volume Dua Kardus.cpp' -o program && ./program",
            "--- KARDUS 1 ---",
            "P: 10, L: 5, T: 4 -> Volume: 200 cm^3",
            "--- KARDUS 2 ---",
            "P: 12, L: 6, T: 5 -> Volume: 360 cm^3",
            "=========================================",
            "Rata-rata Volume Kedua Kardus: 280 cm^3"
        ]
    },
    "Fungsi Matematika Persamaan Kubik.cpp": {
        "title": "Evaluasi Persamaan Kubik (y = a^3 + 7)",
        "topic": "Fungsi Matematika Eksponensial & Polinomial Kubik",
        "concepts": ["Eksponensial (pow)", "cmath Library", "Polinomial", "Fungsi Matematika"],
        "description": "Menghitung nilai ordinat y berdasarkan fungsi persamaan kubik y = a^3 + 7 dengan nilai a sebagai masukan independen.",
        "analysis": "Memanfaatkan pustaka cmath dengan pemanggilan fungsi pow(a, 3) untuk menghitung perpangkatan secara efisien.",
        "simulated": [
            "$ g++ -std=c++17 'Fungsi Matematika Persamaan Kubik.cpp' -o program && ./program",
            "Masukkan nilai a: 3",
            "Persamaan : y = a^3 + 7",
            "Hasil     : y = 3^3 + 7 = 27 + 7 = 34",
            ">> Nilai y adalah: 34"
        ]
    },
    "Kepemilikan Sepatu Mahasiswa.cpp": {
        "title": "Data Kepemilikan Sepatu Mahasiswa",
        "topic": "ADT Struct Relasional (Pemilik & Properti Alas Kaki)",
        "concepts": ["ADT Struct", "Relasi Pemilik-Barang", "Formatting Teks", "Array"],
        "description": "Pengelolaan informasi kepemilikan alas kaki menggunakan struktur data relasional antara identitas mahasiswa dan spesifikasi sepatu.",
        "analysis": "Menautkan data pemilik (nama mahasiswa, status kepemilikan) dengan atribut teknis sepatu dalam model ADT.",
        "simulated": [
            "$ g++ -std=c++17 'Kepemilikan Sepatu Mahasiswa.cpp' -o program && ./program",
            "Nama Mahasiswa : Muhammad Fajri Setyawan",
            "Status Milik   : Sepatu Utama Kuliah",
            "Merk / Model   : Nike Pegasus Trail",
            "Ukuran         : 42",
            "Kondisi        : Sangat Baik (85% prima)"
        ]
    },
    "Perbandingan Dan Pengurutan 3 Bilangan.cpp": {
        "title": "Analisis & Pengurutan 3 Bilangan",
        "topic": "Pohon Keputusan Seleksi Kondisi (Nested If-Else)",
        "concepts": ["Nested If-Else", "Sorting Algoritma", "Logika Perbandingan", "Kondisi Bertingkat"],
        "description": "Menentukan bilangan terbesar dan mengurutkan 3 buah bilangan acak dari nilai terbesar ke terkecil menggunakan seleksi kondisi bertingkat.",
        "analysis": "Membangun pohon keputusan logis tanpa loop untuk mengurutkan permutasi 3 variabel masukan (a, b, c).",
        "simulated": [
            "$ g++ -std=c++17 'Perbandingan Dan Pengurutan 3 Bilangan.cpp' -o program && ./program",
            "Masukkan Bilangan 1: 45",
            "Masukkan Bilangan 2: 12",
            "Masukkan Bilangan 3: 89",
            "---------------------------------------",
            "Bilangan Terbesar  : 89",
            "Urutan Terbesar -> Terkecil : 89, 45, 12"
        ]
    },
    "Konversi Angka Menjadi Kata.cpp": {
        "title": "Konversi Angka ke Teks Kata (1 - 100)",
        "topic": "Pemetaan Nilai Numerik ke String Bahasa Indonesia",
        "concepts": ["Translasi String", "Logika Modulo & Pembagian", "Seleksi Kondisi", "String Parsing"],
        "description": "Menerjemahkan angka bilangan bulat 1 sampai 100 menjadi ejaan teks bahasa Indonesia (contoh: 25 -> 'dua puluh lima').",
        "analysis": "Mengurai angka menjadi digit puluhan (angka / 10) dan satuan (angka % 10) kemudian merangkai string fonetik bahasa Indonesia.",
        "simulated": [
            "$ g++ -std=c++17 'Konversi Angka Menjadi Kata.cpp' -o program && ./program",
            "Masukkan angka (1-100): 78",
            "Hasil Terjemahan: 'tujuh puluh delapan'"
        ]
    },

    # Tugas 1 Fun Run Aritmatika dan ADT
    "CircleLari.cpp": {
        "title": "Pencatatan Data Lari Circle Nadia",
        "topic": "ADT Struct, String Time Parsing & Time Telemetry Aggregator",
        "concepts": ["ADT Struct", "String Substr Parsing", "Konversi Detik", "Agregasi Waktu", "Array of Struct"],
        "description": "Menghitung selisih durasi harian, total detik aktivitas lari, dan rata-rata durasi pace lari circle Nadia secara presisi.",
        "analysis": "Mengonversi format waktu 'HH:MM:SS' menjadi total detik melalui parsing string substr dan stoi, mengkalkulasi durasi perjalanan, serta mengonversinya kembali ke format 'MM:SS'.",
        "simulated": [
            "$ g++ -std=c++17 'CircleLari.cpp' -o CircleLari && ./CircleLari",
            "========================================================================",
            "                    DATA LAPORAN LARI NADIA                             ",
            "========================================================================",
            "Hari\tBerangkat\tFinish\t\tDurasi\t\tJarak\tCatatan",
            "------------------------------------------------------------------------",
            "Senin\t07:10:00\t07:38:20\t28:20\t\t2.5 km\tCuaca cerah",
            "Rabu\t07:12:00\t07:41:10\t29:10\t\t2.6 km\tSedikit ramai",
            "Jumat\t07:15:30\t07:45:30\t30:00\t\t2.5 km\tLancar",
            "------------------------------------------------------------------------",
            "",
            "Hasil Perhitungan:",
            "- Total waktu lari : 5250 detik (87:30)",
            "- Rata-rata lari   : 1750 detik (29:10)"
        ]
    },
    "HalfMarathon.cpp": {
        "title": "Rekap KM Splits Half-Marathon (21.1 KM)",
        "topic": "ADT Struct Split Pace Telemetry & Running Analytics",
        "concepts": ["ADT Struct", "Telemetry Data", "Looping Aggregation", "Pace Tracking", "Array of Struct"],
        "description": "Merekapitulasi split waktu tempuh setiap kilometer dalam lari Half Marathon (21 KM), menghitung akumulasi waktu total, dan pace rata-rata per kilometer.",
        "analysis": "Mengelola data time-series performa lari 21 kilometer split. Menghitung total waktu tempuh jam:menit:detik serta rata-rata pace tempuh per kilometer.",
        "simulated": [
            "$ g++ -std=c++17 'HalfMarathon.cpp' -o HalfMarathon && ./HalfMarathon",
            "========================================",
            "       REKAP SPLIT HALF-MARATHON        ",
            "========================================",
            "Kilometer\tPace (Waktu)",
            "----------------------------------------",
            "KM 1\t\t06:05 /km",
            "KM 2\t\t06:01 /km",
            "KM 3\t\t05:57 /km",
            "KM 4\t\t06:05 /km",
            "KM 5\t\t05:58 /km",
            "KM 6\t\t06:04 /km",
            "KM 7\t\t05:58 /km",
            "KM 8\t\t05:57 /km",
            "KM 9\t\t06:05 /km",
            "KM 10\t\t06:01 /km",
            "...",
            "KM 21\t\t06:11 /km",
            "----------------------------------------",
            "Total Jarak      : 21 KM",
            "Total Waktu      : 2:09:02",
            "Pace Rata-rata   : 06:08 /km"
        ]
    },

    # Tugas 1 Kulino
    "PAS_Kasus1_A11.2026.16638.cpp": {
        "title": "Kalkulasi Aljabar, Deret Rata-rata & Konversi Suhu",
        "topic": "Ekspresi Polinomial, Akumulasi Loop & Konversi Termometrik",
        "concepts": ["Aljabar Polinomial", "Loop For Akumulasi", "Konversi Suhu", "cmath pow"],
        "description": "Menyelesaikan persamaan polinomial y = a^3 + 7 dan y = ax^2 + bx + c, menghitung jumlah dan rata-rata 5 bilangan, serta konversi suhu Celsius ke F/K/R.",
        "analysis": "Praktikum dasar pengenalan formula matematika, iterasi input berulang, dan perhitungan rasio konversi temperatur standar.",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus1_A11.2026.16638.cpp' -o Kasus1 && ./Kasus1",
            "1. Nilai y (a=2): 15",
            "2. Nilai y (ax^2 + bx + c): 69",
            "",
            "3. Masukkan 5 bilangan:",
            "bilangan ke-1: 10",
            "bilangan ke-2: 20",
            "bilangan ke-3: 30",
            "bilangan ke-4: 40",
            "bilangan ke-5: 50",
            "a. jumlah: 150",
            "b. Rata-rata: 30",
            "",
            "4. Masukkan suhu dalam Celcius: 100",
            "a. Farenheit: 5760",
            "b. kelvin: 373",
            "c. Reamur: 80"
        ]
    },
    "PAS_Kasus2_A11.2026.16638.cpp": {
        "title": "Kalkulasi Upah Kerja & Upah Lembur Karyawan",
        "topic": "Perhitungan Finansial Tenaga Kerja & Tarif Lembur",
        "concepts": ["Aritmatika Finansial", "Upah & Lembur", "Input/Output", "Presisi Double"],
        "description": "Menghitung total take-home pay upah karyawan yang terdiri dari upah kerja reguler ditambah dengan upah jam lembur.",
        "analysis": "Formula: Total Upah = (Jam Kerja * Tarif Per Jam) + (Jam Lembur * Tarif Lembur).",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus2_A11.2026.16638.cpp' -o Kasus2 && ./Kasus2",
            "Masukkan jam kerja: 40",
            "Masukkan upah per jam: 50000",
            "Masukkan jam lembur: 10",
            "---------------------------------------",
            "Upah Reguler : Rp 2.000.000",
            "Upah Lembur  : Rp 750.000",
            "Total Upah   : Rp 2.750.000"
        ]
    },
    "PAS_Kasus3_A11.2026.16638.cpp": {
        "title": "Relasi Logika Nilai & Deret Angka",
        "topic": "Percabangan Pengkondisian & Loop Mundur (Countdown)",
        "concepts": ["Seleksi If", "Penggandaan Nilai", "Loop For Mundur", "Deret Angka"],
        "description": "Mengevaluasi relasi dua nilai A dan B; jika A < B maka B digandakan, kemudian mencetak deret bilangan mundur secara terurut.",
        "analysis": "Menguji kemampuan logika percabangan kondisional sederhana dan manipulasi nilai batas counter loop decrement.",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus3_A11.2026.16638.cpp' -o Kasus3 && ./Kasus3",
            "Input a: 5",
            "Input b: 10",
            ">> Kondisi (a < b) terpenuhi: Nilai b digandakan menjadi 20",
            "Deret angka: 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5"
        ]
    },
    "PAS_Kasus4_A11.2026.16638.cpp": {
        "title": "Pemrosesan Array 1D (Min, Max, Sum, & Rata-rata)",
        "topic": "Alokasi Array Dinamis & Algoritma Statistik 1 Dimensi",
        "concepts": ["Array 1D", "Pencarian Min/Max", "Akumulasi Rerata", "Loop For"],
        "description": "Menerima N elemen bilangan ke dalam array, kemudian menentukan nilai minimum, nilai maksimum, total penjumlahan, dan rata-rata elemen.",
        "analysis": "Algoritma linear traversal pada array dengan inisialisasi min/max dari elemen pertama dan pembaruan kontinyu selama iterasi.",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus4_A11.2026.16638.cpp' -o Kasus4 && ./Kasus4",
            "Input N: 4",
            "Input ke-1: 15",
            "Input ke-2: 8",
            "Input ke-3: 42",
            "Input ke-4: 23",
            "---------------------------------------",
            "Nilai Minimum : 8",
            "Nilai Maksimum: 42",
            "Total Sum     : 88",
            "Rata-rata     : 22.0"
        ]
    },
    "PAS_Kasus5_A11.2026.16638.cpp": {
        "title": "Definisi ADT Struct Titik / Koordinat Nilai",
        "topic": "Typedef Struct & Akses Member Variabel Dot Operator",
        "concepts": ["Typedef Struct", "Member Access (.)", "Inisialisasi Data", "ADT Sederhana"],
        "description": "Mendefinisikan tipe bentukan typedef struct Nilai { int x; int y; } dan mengakses anggotanya melalui dot operator.",
        "analysis": "Pondasi pembentukan tipe data komposit baru dalam C++ untuk mengelompokkan nilai absis dan ordinat.",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus5_A11.2026.16638.cpp' -o Kasus5 && ./Kasus5",
            "Nilai x: 10",
            "Nilai y: 20",
            ">> Struktur Nilai berhasil diakses melalui dot-operator."
        ]
    },
    "PAS_Kasus6_A11.2026.16638.cpp": {
        "title": "Modularitas Header & Fungsi Geometri / Paritas",
        "topic": "Pemisahan Prototipe Fungsi ke Header File (.h) & Implementasi (.cpp)",
        "concepts": ["Header File (.h)", "Fungsi Modular", "Kondisi Paritas (Ganjil/Genap)", "Luas Persegi"],
        "description": "Mengimplementasikan fungsi Luas_Persegi, is_ganjil, dan is_genap dengan pemisahan deklarasi modul file header terpisah.",
        "analysis": "Best-practice pemrograman modular dalam C++ dengan memisahkan deklarasi antarmuka fungsi di file header (.h) dan implementasi di file source (.cpp).",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus6_A11.2026.16638.cpp' -o Kasus6 && ./Kasus6",
            "Luas Persegi (sisi 6) : 36",
            "Apakah 7 Ganjil?      : Ya (True)",
            "Apakah 8 Genap?       : Ya (True)"
        ]
    },
    "PAS_Kasus7_A11.2026.16638.cpp": {
        "title": "Konsep Alamat Memori & Manipulasi Variabel Pointer",
        "topic": "Alamat Memori (&), Pointer (*), & Operator Dereference",
        "concepts": ["Pointer (*)", "Address-of (&)", "Dereferensi Memori", "Manajemen Memori"],
        "description": "Mendemonstrasikan bagaimana pointer menunjuk alamat memori variabel dan mengubah nilai aslinya secara tidak langsung (indirect modification).",
        "analysis": "Pembahasan esensial konsep pointer C++: variabel pointer menyimpan alamat memori hexadesimal dan dereferensi (*p) mengakses nilai aktual pada alamat tersebut.",
        "simulated": [
            "$ g++ -std=c++17 'PAS_Kasus7_A11.2026.16638.cpp' -o Kasus7 && ./Kasus7",
            "1. Nilai i : 20",
            "2. Nilai i : 50",
            ">> Nilai i setelah manipulasi dereference pointer *p = 50",
            "Alamat Memori p : 0x7ffd5e2b4c1c"
        ]
    },

    # Tugas 2 Kondisi, Loop, Array
    "Membandingkan Harga Sepatu.cpp": {
        "title": "Komparasi & Pengurutan Harga Sepatu Circle Lari",
        "topic": "Array of Struct, Komparasi Relasional & Bubble Sort 3 Entitas",
        "concepts": ["Array of Struct", "Komparasi IF-ELSE", "Bubble Sort Manual", "Format Rupiah"],
        "description": "Mengelola data sepatu 5 anggota circle lari, membandingkan harga dua entitas, dan mengurutkan 3 data menggunakan seleksi kondisi IF bertingkat.",
        "analysis": "Mengkombinasikan array of struct dengan algoritma perbandingan harga berantai dan penukaran variabel sementara (temp) untuk sorting.",
        "simulated": [
            "$ g++ -std=c++17 'Membandingkan Harga Sepatu.cpp' -o program && ./program",
            "============================================================",
            "        KOMPARASI & PENGURUTAN HARGA SEPATU ANGGOTA         ",
            "============================================================",
            "Membandingkan Sepatu Nadia (Rp 1.200.000) vs Dimas (Rp 2.100.000):",
            ">> Sepatu Dimas LEBIH MAHAL daripada sepatu Nadia.",
            "",
            "Hasil Pengurutan 3 Sepatu (Termurah -> Termahal):",
            "1. Nadia - Nike (Rp 1.200.000)",
            "2. Fajri - Adidas (Rp 1.850.000)",
            "3. Dimas - Asics (Rp 2.100.000)"
        ]
    },
    "Data Sepatu Anggota Circle Lari.cpp": {
        "title": "Input & Penayangan Inventaris Sepatu Anggota",
        "topic": "Pengisian Interaktif Array of Struct & Pemilihan Data",
        "concepts": ["Array of Struct", "Input Dinamis", "Pencarian Indeks", "Seleksi Kondisi"],
        "description": "Membaca data sepatu anggota baru secara interaktif ke dalam array of struct dan menayangkan informasi spesifik berdasarkan indeks pilihan.",
        "analysis": "Mengelola database sederhana dalam memori untuk inventaris sepatu pelari dan menyediakan navigasi pilihan anggota.",
        "simulated": [
            "$ g++ -std=c++17 'Data Sepatu Anggota Circle Lari.cpp' -o program && ./program",
            "Pilih Anggota Circle Lari (1-5): 2",
            "--------------------------------------------------",
            "Nama Pemilik : Fajri Setyawan",
            "Merk Sepatu  : Nike Invincible Run 3",
            "Warna / Seri : Obsidian Blue (#102)",
            "Ukuran       : 42",
            "Harga        : Rp 2.399.000"
        ]
    },
    "Mencari Nilai Terbesar Dari 5 Data Sepatu.cpp": {
        "title": "Pencarian Ukuran Sepatu Terbesar (5 Data)",
        "topic": "Algoritma Pencarian Maksimum (Linear Max Search) pada Array of Struct",
        "concepts": ["Linear Search", "Pencarian Nilai Maksimum", "Array of Struct", "Penelusuran Iteratif"],
        "description": "Menentukan ukuran sepatu paling besar di antara 5 anggota circle lari dan menampilkan pemilik beserta detail lengkapnya.",
        "analysis": "Inisialisasi variabel max dengan elemen pertama sepatu[0], kemudian loop membandingkan sepatu[i].ukuran > max.ukuran.",
        "simulated": [
            "$ g++ -std=c++17 'Mencari Nilai Terbesar Dari 5 Data Sepatu.cpp' -o program && ./program",
            "============================================================",
            "             PENCARIAN UKURAN SEPATU TERBESAR               ",
            "============================================================",
            "Ukuran Terbesar : Size 44 (Milik: Dimas)",
            "Merk            : Asics Novablast",
            "Warna           : Neon Lime",
            "Harga           : Rp 2.100.000"
        ]
    },
    "Modifikasi Pengaturan Dari Besar ke Kecil.cpp": {
        "title": "Pengurutan Sepatu Descending (Besar ke Kecil)",
        "topic": "Algoritma Pengurutan Descending Berdasarkan Kriteria Ukuran/Harga",
        "concepts": ["Sorting Descending", "Array of Struct", "Swap Algorithm", "Manipulasi Array"],
        "description": "Menyusun dan mengurutkan seluruh 5 data sepatu anggota circle lari secara terbalik (descending) dari nilai terbesar menuju nilai terkecil.",
        "analysis": "Mengimplementasikan pengurutan terbalik dengan membalik relasi komparasi perbandingan nilai pada bubble sort.",
        "simulated": [
            "$ g++ -std=c++17 'Modifikasi Pengaturan Dari Besar ke Kecil.cpp' -o program && ./program",
            "--- URUTAN SEPATU DARI UKURAN TERBESAR KE TERKECIL ---",
            "1. Dimas  - Ukuran: 44 (Asics)",
            "2. Budi   - Ukuran: 43 (Puma)",
            "3. Fajri  - Ukuran: 42 (Nike)",
            "4. Sarah  - Ukuran: 39 (New Balance)",
            "5. Nadia  - Ukuran: 38 (Nike Air)"
        ]
    },
    "Analisis Klasifikasi Karakteristik Bilangan Bulat.cpp": {
        "title": "Klasifikasi Karakteristik Bilangan Bulat",
        "topic": "Pohon Keputusan Multi-Kriteria (Positif/Negatif/Nol & Ganjil/Genap)",
        "concepts": ["Nested If-Else", "Operator Modulo (%)", "Klasifikasi Angka", "Kondisi Bertingkat"],
        "description": "Menentukan apakah suatu bilangan bertanda positif, negatif, atau nol, serta mengidentifikasi apakah bilangan tersebut tergolong ganjil atau genap.",
        "analysis": "Struktur seleksi dua tingkat: tingkat pertama mengecek sign (x > 0, x < 0, x == 0), dan tingkat kedua mengecek paritas (x % 2 != 0).",
        "simulated": [
            "$ g++ -std=c++17 'Analisis Klasifikasi Karakteristik Bilangan Bulat.cpp' -o program && ./program",
            "Masukkan sebuah bilangan bulat: -15",
            "-----------------------------------------------",
            "Hasil Analisis Karakteristik:",
            "- Tanda Bilangan : Negatif",
            "- Paritas        : Ganjil (Bilangan Bulat Negatif Ganjil)"
        ]
    },
    "Pengurutan Tiga Bilangan Bulat Dari Nilai Terbesar Menuju terkecil.cpp": {
        "title": "Pengurutan Tiga Bilangan Bulat (Descending)",
        "topic": "Logika Seleksi Kondisi Lengkap (6 Kasus Permutasi)",
        "concepts": ["Permutasi Logika", "Seleksi If-Else", "Pengurutan 3 Bilangan", "Logika Boolean"],
        "description": "Mengurutkan tiga buah bilangan bulat dari nilai terbesar menuju terkecil menggunakan struktur kendali pemilihan if-else komparatif.",
        "analysis": "Menguji seluruh kombinasi pasangan relasi (a>=b dan b>=c, dll.) untuk menjamin penataan urutan 3 nilai dengan benar.",
        "simulated": [
            "$ g++ -std=c++17 'Pengurutan Tiga Bilangan Bulat Dari Nilai Terbesar Menuju terkecil.cpp' -o program && ./program",
            "Masukkan Bilangan A: 27",
            "Masukkan Bilangan B: 84",
            "Masukkan Bilangan C: 15",
            "---------------------------------------",
            "Urutan Terbesar ke Terkecil: 84 >= 27 >= 15"
        ]
    },
    "Translasi Bilangan Bulat Rentang 1 - 100 Menjadi String.cpp": {
        "title": "Translasi Bilangan 1 - 100 Menjadi String Teks",
        "topic": "Parsing Tata Bahasa Bilangan (Belasan, Puluhan, Ratusan)",
        "concepts": ["String Synthesizer", "Logika Pembagian & Modulo", "Switch-Case / If-Else", "Pemetaan Bahasa"],
        "description": "Mengubah inputan numerik bulat dari rentang 1 sampai 100 menjadi representasi teks ejaan bahasa Indonesia yang baku.",
        "analysis": "Menangani kasus khusus: 1-11 (satuan & belasan), 12-19 (satuan + belas), 20-99 (puluhan + satuan), dan 100 (seratus).",
        "simulated": [
            "$ g++ -std=c++17 'Translasi Bilangan Bulat Rentang 1 - 100 Menjadi String.cpp' -o program && ./program",
            "Masukkan bilangan bulat (1 - 100): 42",
            "Hasil Translasi Kata: 'empat puluh dua'"
        ]
    },
    "Translasi Kode Angka Menjadi Teks Representasif Menggunakan Struktur Pemilihan Bertingkat.cpp": {
        "title": "Translasi Kode Angka Pemilihan Bertingkat (Switch-Case)",
        "topic": "Struktur Kontrol Seleksi Menu Berbasis Kode Angka",
        "concepts": ["Switch-Case", "Default Case", "Menu Interaktif", "Struktur Pemilihan"],
        "description": "Mengonversi masukan kode numerik menjadi representasi teks deskriptif melalui penggunaan struktur kendali switch-case atau if bertingkat.",
        "analysis": "Menerapkan struktur switch-case untuk menangani dispatching opsi menu berdasarkan integer code dengan penanganan default error handling.",
        "simulated": [
            "$ g++ -std=c++17 'Translasi Kode Angka Menjadi Teks.cpp' -o program && ./program",
            "Pilih Kode Status Layanan (1-4): 3",
            ">> Kode 3: Status 'Pesanan Dalam Pengiriman Kurir'"
        ]
    },
    "komparasi massa dua semangka untuk penentuan bobot terbesar.cpp": {
        "title": "Komparasi Massa Dua Semangka",
        "topic": "Seleksi Kondisi Relasional & Penentuan Nilai Maksimum Dua Objek",
        "concepts": ["Relasi Logika (> < ==)", "Floating Point Comparison", "Seleksi Kondisi", "Aritmatika"],
        "description": "Membandingkan massa dua buah semangka (Semangka A dan Semangka B) untuk menentukan semangka mana yang berbobot lebih berat atau memiliki berat sama.",
        "analysis": "Menggunakan percabangan if (beratA > beratB) ... else if (beratB > beratA) ... else ... untuk menangani ketiga kemungkinan hasil komparasi.",
        "simulated": [
            "$ g++ -std=c++17 'komparasi massa dua semangka.cpp' -o program && ./program",
            "Masukkan Massa Semangka A (kg): 4.85",
            "Masukkan Massa Semangka B (kg): 3.90",
            "---------------------------------------",
            ">> HASIL: Semangka A LEBIH BERAT daripada Semangka B dengan selisih 0.95 kg."
        ]
    }
}

def scan_repository():
    tasks = []
    ignored_dirs = {'.git', '.github', 'scripts', '.vscode', '__pycache__', 'build', '.idea', 'assets'}
    
    candidate_dirs = [
        d for d in ROOT_DIR.iterdir()
        if d.is_dir() and d.name not in ignored_dirs and not d.name.startswith('.')
    ]
    
    task_dirs = []
    for d in candidate_dirs:
        has_cpp = any(d.rglob("*.cpp"))
        if d.name.lower().startswith("tugas") or has_cpp:
            task_dirs.append(d)
            
    task_dirs.sort(key=lambda p: natural_sort_key(p.name))
    
    assignment_items = []
    item_counter = 1
    
    total_loc = 0
    total_cpp = 0
    total_pdf = 0
    
    all_modules = []

    for task_dir in task_dirs:
        rel_dir = task_dir.name
        meta_file = task_dir / "info.json"
        custom_meta = {}
        if meta_file.exists():
            try:
                with open(meta_file, "r", encoding="utf-8") as f:
                    custom_meta = json.load(f)
            except Exception:
                pass
                
        module_title = custom_meta.get("title", rel_dir)
        module_topic = custom_meta.get("topic", "C++ Algorithm & Implementation")
        
        module_data = {
            "id": f"mod-{len(all_modules) + 1}",
            "dirName": rel_dir,
            "title": module_title,
            "topic": module_topic,
            "cppCount": 0,
            "pdfCount": 0,
            "loc": 0
        }
        
        # Temukan semua file cpp dalam modul ini
        cpp_files = sorted(list(task_dir.rglob("*.cpp")), key=lambda p: (
            str(p.parent).lower(),
            natural_sort_key(p.name)
        ))
        
        for cpp in cpp_files:
            rel_cpp = cpp.relative_to(ROOT_DIR).as_posix()
            cpp_parent = cpp.parent
            subfolder_rel = cpp_parent.relative_to(task_dir).as_posix()
            
            # Cari file PDF di folder yang sama
            matching_pdfs = list(cpp_parent.glob("*.pdf"))
            pdf_info = None
            if matching_pdfs:
                p_file = matching_pdfs[0]
                pdf_info = {
                    "name": p_file.name,
                    "path": p_file.relative_to(ROOT_DIR).as_posix(),
                    "size": format_file_size(p_file.stat().st_size)
                }
                total_pdf += 1
                module_data["pdfCount"] += 1
                
            # Cek jika ada file .docx di subfolder atau modul
            docx_info = None
            matching_docx = list(cpp_parent.glob("*.docx"))
            if not matching_docx:
                matching_docx = list(task_dir.glob("*.docx"))
            if matching_docx:
                d_file = matching_docx[0]
                docx_info = {
                    "name": d_file.name,
                    "path": d_file.relative_to(ROOT_DIR).as_posix(),
                    "size": format_file_size(d_file.stat().st_size)
                }

            # Cek file header .h terkait
            header_info = None
            matching_h = list(cpp_parent.glob("*.h"))
            if matching_h:
                h_file = matching_h[0]
                header_info = {
                    "name": h_file.name,
                    "path": h_file.relative_to(ROOT_DIR).as_posix(),
                    "code": h_file.read_text(encoding="utf-8", errors="ignore")
                }

            # Baca kode C++
            code_text = cpp.read_text(encoding="utf-8", errors="ignore")
            loc = count_lines_of_code(code_text)
            file_size = format_file_size(cpp.stat().st_size)
            
            total_loc += loc
            total_cpp += 1
            module_data["cppCount"] += 1
            module_data["loc"] += loc
            
            # Cari metadata dari KB
            kb_entry = KNOWLEDGE_BASE.get(cpp.name, {})
            title = kb_entry.get("title", cpp.stem)
            topic = kb_entry.get("topic", "Implementasi Logika C++")
            concepts = kb_entry.get("concepts", ["C++17", "Algoritma Dasar"])
            description = kb_entry.get("description", f"Implementasi program C++ untuk {cpp.stem}")
            analysis = kb_entry.get("analysis", "Program C++ terstruktur yang memproses masukan data, menerapkan kalkulasi algoritmik, dan menyajikan luaran terformat.")
            simulated = kb_entry.get("simulated", [
                f"$ g++ -std=c++17 '{cpp.name}' -o program && ./program",
                f">> Program {cpp.name} berhasil dieksekusi dengan normal."
            ])
            
            # Deteksi nomor kasus
            kasus_match = re.search(r'kasus\s*(\d+)', subfolder_rel, re.IGNORECASE)
            if not kasus_match:
                kasus_match = re.search(r'kasus\s*(\d+)', cpp.name, re.IGNORECASE)
            case_num = int(kasus_match.group(1)) if kasus_match else item_counter

            assignment_items.append({
                "id": f"task-{item_counter:02d}",
                "counter": item_counter,
                "module": rel_dir,
                "moduleTitle": module_title,
                "subfolder": subfolder_rel if subfolder_rel != "." else "",
                "caseNum": case_num,
                "caseLabel": f"Kasus {case_num}" if case_num else "Praktikum",
                "title": title,
                "topic": topic,
                "concepts": concepts,
                "description": description,
                "analysis": analysis,
                "simulatedTerminal": "\n".join(simulated),
                "cppName": cpp.name,
                "cppPath": rel_cpp,
                "cppSize": file_size,
                "loc": loc,
                "code": code_text,
                "header": header_info,
                "pdf": pdf_info,
                "docx": docx_info,
                "githubBlob": f"https://github.com/{PROFILE['github_user']}/{PROFILE['repo_name']}/blob/main/{urllib.parse.quote(rel_cpp)}"
            })
            item_counter += 1

        all_modules.append(module_data)

    # Kumpulkan semua berkas PDF secara menyeluruh untuk katalog PDF
    all_pdfs = []
    for pdf_p in sorted(list(ROOT_DIR.rglob("*.pdf")), key=lambda p: (str(p.parent).lower(), natural_sort_key(p.name))):
        if any(ign in pdf_p.parts for ign in ['.git', '.github', 'scripts', 'assets']):
            continue
        rel_pdf = pdf_p.relative_to(ROOT_DIR).as_posix()
        module_name = pdf_p.parts[0]
        size = format_file_size(pdf_p.stat().st_size)
        
        # Tentukan tipe dokumen
        fn_low = pdf_p.name.lower()
        if 'notasi' in fn_low:
            doc_type = "Notasi Algoritmik"
        elif 'analisis' in fn_low:
            doc_type = "Dokumen Analisis"
        else:
            doc_type = "Laporan & Uji Kasus"
            
        all_pdfs.append({
            "name": pdf_p.name,
            "path": rel_pdf,
            "module": module_name,
            "size": size,
            "docType": doc_type,
            "githubUrl": f"https://github.com/{PROFILE['github_user']}/{PROFILE['repo_name']}/blob/main/{urllib.parse.quote(rel_pdf)}"
        })

    # Summary Stats
    stats = {
        "totalModules": len(all_modules),
        "totalCpp": total_cpp,
        "totalPdf": len(all_pdfs),
        "totalLoc": total_loc,
        "completionRate": 100,
        "lastUpdated": datetime.now().strftime("%d %B %Y, %H:%M WIB"),
        "profile": PROFILE,
        "modules": all_modules
    }

    return assignment_items, all_pdfs, stats

def main():
    print("🔍 Menghasilkan data assignments.js untuk Web Portal...")
    assignments, pdfs, stats = scan_repository()
    
    js_content = f"""/**
 * DASPRO ASSIGNMENTS REPOSITORY DATA
 * Otomatis dihasilkan oleh scripts/generate_web_data.py
 * Tanggal Sinkronisasi: {stats['lastUpdated']}
 */

window.DASPRO_STATS = {json.dumps(stats, indent=2, ensure_ascii=False)};

window.DASPRO_PDFS = {json.dumps(pdfs, indent=2, ensure_ascii=False)};

window.DASPRO_ASSIGNMENTS = {json.dumps(assignments, indent=2, ensure_ascii=False)};
"""
    
    output_path = ROOT_DIR / "assets" / "js" / "assignments.js"
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(js_content)
        
    print(f"✅ Data web berhasil diperbarui di: {output_path}")
    print(f"📊 Statistik: {len(assignments)} Berkas C++, {len(pdfs)} PDF, {stats['totalLoc']} Total LOC.")

if __name__ == "__main__":
    main()
