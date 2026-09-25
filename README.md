<div align="center">

# DASPRO ACTIVITY RECORDER
**Engine Agregasi Metrik Lari & Analisis Waktu (ADT Struct)**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-black?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Topic](https://img.shields.io/badge/Architecture-ADT_Struct-111111?style=for-the-badge)](https://github.com/)
[![Status](https://img.shields.io/badge/Build-Passing-222222?style=for-the-badge)](https://github.com/)

</div>

---

### Identitas Mahasiswa

> **Nama Lengkap** : Muhammad Fajri Setyawan  
> **NIM** : `A11.2026.16638`  
> **Mata Kuliah** : Dasar Pemrograman  
> **Komponen** : `struct`, `std::string::substr`, `std::stoi`, Time Converter

---

### Dashboard Metrik Utama

<div align="center">

<img src="https://img.shields.io/badge/TOTAL_WAKTU-01:27:30-black?style=for-the-badge&labelColor=1a1a1a" height="40" alt="Total Waktu" />
<img src="https://img.shields.io/badge/RATA--RATA_DURASI-29:10-black?style=for-the-badge&labelColor=1a1a1a" height="40" alt="Rata-rata Durasi" />
<img src="https://img.shields.io/badge/VOLUME_LATIHAN-7.60_KM-black?style=for-the-badge&labelColor=1a1a1a" height="40" alt="Volume Latihan" />

</div>

<br/>

> [!NOTE]
> **Ringkasan Telemetri:** Data lari 3 sesi (Nadia) berhasil dikalkulasi melalui pemotongan indeks string `HH:MM:SS` menjadi total 5.250 detik dengan rata-rata 1.750 detik per sesi latihan.

---

### Log Sesi Running Nadia

| HARI | BERANGKAT | FINISH | DURASI (MM:SS) | JARAK | STATUS LOG |
| :--- | :---: | :---: | :---: | :---: | :--- |
| `Senin` | `07:10:00` | `07:38:20` | **`28:20`** | `2.5 km` | Cuaca cerah |
| `Rabu` | `07:12:00` | `07:41:10` | **`29:10`** | `2.6 km` | Sedikit ramai |
| `Jumat` | `07:15:30` | `07:45:30` | **`30:00`** | `2.5 km` | Lancar |
| **RATA-RATA** | — | — | **`29:10`** | **`2.53 km`** | **Optimal** |

---

### Analisis KM Splits Half-Marathon (21.4 KM)

<div align="center">

<img src="https://img.shields.io/badge/PACE_RATA--RATA-06:06_/KM-black?style=for-the-badge&labelColor=1a1a1a" height="38" alt="Pace" />
<img src="https://img.shields.io/badge/TOTAL_WAKTU_RACE-02:10:41-black?style=for-the-badge&labelColor=1a1a1a" height="38" alt="Total Race" />

</div>

<details>
<summary><b>Buka Detail Log Split Per Kilometer (KM 1 — 21)</b></summary>

<br/>

| KM | Split Pace | Evaluasi Ritme |
| :---: | :---: | :--- |
| `01` | `06:05` | Target awal tercapai |
| `02` | `06:01` | Peningkatan laju |
| `03` | `05:57` | Ritme puncak awal |
| `04` | `06:05` | Penyesuaian ritme |
| `05` | `05:58` | Stabilisasi |
| `06` | `06:04` | Stabil |
| `07` | `05:58` | Stabil |
| `08` | `05:57` | Zona efisiensi |
| `09` | `06:05` | Ritme tengah rute |
| `10` | `06:01` | Pengendalian stamina |
| `11` | `06:02` | Stabil |
| `12` | `06:08` | Penurunan ringan |
| `13` | `06:09` | Ambang lelah |
| `14` | `05:58` | Rebound |
| `15` | `06:20` | Ritme melambat |
| `16` | `06:13` | Penyesuaian energi |
| `17` | `06:20` | Mempertahankan batas |
| `18` | `06:17` | Konsisten |
| `19` | `06:26` | Beban muskular |
| `20` | `06:47` | Fase terberat |
| `21` | `06:11` | Akselerasi akhir |

</details>

---

### Implementasi Sumber Kode

```cpp
struct KegiatanLari {
    string nama;
    string hari;
    string waktuBerangkat;
    string waktuFinish;
    double jarak;
    string catatan;
};