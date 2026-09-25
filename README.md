<div align="center">

# DASPRO ACTIVITY RECORDER
### Implementasi ADT Struct C++ & Analisis Metrik Waktu

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Standard-C%2B%2B17-blue?style=flat-square" alt="C++17" />
  <img src="https://img.shields.io/badge/IDE-VS_Code_/_Antigravity-007ACC?style=flat-square&logo=visualstudiocode&logoColor=white" alt="VS Code" />
  <img src="https://img.shields.io/badge/Compiler-GCC_MinGW-4B0082?style=flat-square" alt="GCC" />
</p>

</div>

---

### Informasi Mahasiswa

<table>
  <tr>
    <td width="160"><b>Nama Lengkap</b></td>
    <td>Muhammad Fajri Setyawan</td>
  </tr>
  <tr>
    <td><b>NIM</b></td>
    <td><code>A11.2026.16638</code></td>
  </tr>
  <tr>
    <td><b>Mata Kuliah</b></td>
    <td>Dasar Pemrograman (DASPRO)</td>
  </tr>
  <tr>
    <td><b>Topik Bahasan</b></td>
    <td>Abstract Data Type (ADT) — <code>struct</code> & Operasi String</td>
  </tr>
</table>

---

### Arsitektur Struktur Data

```cpp
struct KegiatanLari {
    std::string nama;
    std::string hari;
    std::string waktuBerangkat;
    std::string waktuFinish;
    double      jarak;
    std::string catatan;
};