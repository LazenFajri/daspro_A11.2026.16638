#!/usr/bin/env python3
"""
DASPRO README Generator
Otomatis memindai folder tugas (Tugas*), menghitung statistik,
dan membuat README.md berdesain modern dan profesional.
"""

import os
import sys
import re
import json
from pathlib import Path
from datetime import datetime

# Pastikan UTF-8 di Windows terminal
if sys.platform == "win32":
    try:
        sys.stdout.reconfigure(encoding="utf-8")
    except Exception:
        pass

# Konfigurasi Profil Mahasiswa & Matkul
PROFILE = {
    "name": "Muhammad Fajri Setyawan",
    "nim": "A11.2026.16638",
    "course": "Dasar Pemrograman (DASPRO)",
    "prodi": "Teknik Informatika",
    "univ": "Universitas Dian Nuswantoro (UDINUS)",
    "language": "C++17",
    "github_user": "LazenFajri",
    "repo_name": "daspro_A11.2026.16638"
}

ROOT_DIR = Path(__file__).resolve().parent.parent

def natural_sort_key(s):
    """Kunci pengurutan natural (misal: Tugas1, Tugas2, Tugas10)."""
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', str(s))]

def format_folder_name(name):
    """Format nama folder menjadi judul yang rapi."""
    # Misal: Tugas1FunRun -> Tugas 1: Fun Run
    match = re.match(r'Tugas(\d+)(.*)', name, re.IGNORECASE)
    if match:
        num = match.group(1)
        rest = match.group(2)
        # Pisahkan camelCase
        spaced = re.sub(r'([a-z])([A-Z])', r'\1 \2', rest).strip()
        if spaced:
            return f"Tugas {num} — {spaced}"
        return f"Tugas {num}"
    return name

def extract_file_description(file_path, file_name=""):
    """Ekstrak judul / deskripsi dari header komentar C++ jika ada."""
    desc = ""
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            content = f.read(2048) # Baca 2KB pertama
            
            # 1. Cek format 'judul : ...'
            match = re.search(r'judul\s*:\s*([^\n\r]+)', content, re.IGNORECASE)
            if match:
                desc = match.group(1).strip()
                return desc[0].upper() + desc[1:] if desc else ""
                
            # 2. Cek format '// Kasus X:' atau '// 1. ...'
            match_kasus = re.search(r'//\s*([0-9]+\.\s*[^;\n\r]+)', content)
            if match_kasus:
                return match_kasus.group(1).strip()

            # 3. Cek komentar deskriptif pertama setelah include
            lines = content.splitlines()
            for line in lines:
                s = line.strip()
                if s.startswith("//") and not s.startswith("///") and len(s) > 4:
                    cleaned = s.lstrip("/").strip()
                    if not any(skip in cleaned.lower() for skip in ["include", "using namespace", "int main", "typedef"]):
                        return cleaned[0].upper() + cleaned[1:]
    except Exception:
        pass
        
    # Fallback berbasis nama file jika ada pola Kasus
    kasus_match = re.search(r'kasus(\d+)', file_name, re.IGNORECASE)
    if kasus_match:
        k_num = kasus_match.group(1)
        fallback_kasus = {
            "1": "Perhitungan Aljabar, Statistik Bilangan & Konversi Suhu",
            "2": "Kalkulasi Upah Kerja & Persentase Lembur",
            "3": "Relasi Logika Dua Bilangan & Deret Angka",
            "4": "Pemrosesan Array 1D (Min, Max, Sum, & Rata-rata)",
            "5": "Definisi Tipe Bentukan Struct Sederhana",
            "6": "Struktur Data Titik Koordinat (ADT Point)",
            "7": "Konsep Alamat Memori & Manipulasi Variabel Pointer"
        }
        if k_num in fallback_kasus:
            return fallback_kasus[k_num]
        return f"Praktikum Pemrograman — Kasus {k_num}"
        
    return ""

def format_file_size(size_bytes):
    """Format ukuran file ke KB / B."""
    if size_bytes < 1024:
        return f"{size_bytes} B"
    return f"{size_bytes / 1024:.1f} KB"

def count_lines_of_code(file_path):
    """Hitung baris kode (LOC) dari file teks."""
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            return sum(1 for line in f if line.strip())
    except Exception:
        return 0

def scan_tasks():
    """Pindai semua folder tugas dan kumpulkan informasinya."""
    tasks = []
    
    # Folder yang diabaikan
    ignored_dirs = {'.git', '.github', 'scripts', '.vscode', '__pycache__', 'build'}
    
    candidate_dirs = [
        d for d in ROOT_DIR.iterdir()
        if d.is_dir() and d.name not in ignored_dirs and not d.name.startswith('.')
    ]
    
    # Filter folder yang berawalan Tugas atau memiliki file .cpp
    task_dirs = []
    for d in candidate_dirs:
        has_cpp = any(d.glob("*.cpp"))
        if d.name.lower().startswith("tugas") or has_cpp:
            task_dirs.append(d)
            
    task_dirs.sort(key=lambda p: natural_sort_key(p.name))
    
    for task_dir in task_dirs:
        rel_dir = task_dir.name
        
        # Cek apakah ada info.json kustom
        meta_file = task_dir / "info.json"
        custom_meta = {}
        if meta_file.exists():
            try:
                with open(meta_file, "r", encoding="utf-8") as f:
                    custom_meta = json.load(f)
            except Exception:
                pass
                
        title = custom_meta.get("title", format_folder_name(rel_dir))
        topic = custom_meta.get("topic", "C++ Algorithm & Implementation")
        status = custom_meta.get("status", "Completed")
        
        # Pindai file di dalam folder
        files = []
        cpp_count = 0
        pdf_count = 0
        task_loc = 0
        
        for item in sorted(task_dir.iterdir(), key=lambda p: natural_sort_key(p.name)):
            if item.is_file():
                ext = item.suffix.lower()
                # Skip binary dan file pendukung
                if ext in {'.exe', '.o', '.obj', '.out'}:
                    continue
                if item.name in {'telemetry.md', 'info.json', 'analysis.md', 'notes.md'}:
                    continue
                    
                file_size = format_file_size(item.stat().st_size)
                description = ""
                file_badge = ""
                
                if ext == '.cpp':
                    cpp_count += 1
                    loc = count_lines_of_code(item)
                    task_loc += loc
                    description = extract_file_description(item, item.name)
                    if not description:
                        description = f"Implementasi C++ ({loc} baris kode)"
                    file_badge = "![C++](https://img.shields.io/badge/-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)"
                elif ext in {'.h', '.hpp'}:
                    loc = count_lines_of_code(item)
                    task_loc += loc
                    description = "Header Specification & ADT Definition"
                    file_badge = "![Header](https://img.shields.io/badge/-Header-gray?style=flat-square)"
                elif ext == '.pdf':
                    pdf_count += 1
                    description = "Dokumen Analisis / Notasi Algoritmik / Laporan"
                    file_badge = "![PDF](https://img.shields.io/badge/-PDF-red?style=flat-square&logo=adobeacrobatreader&logoColor=white)"
                elif ext == '.md':
                    description = "Dokumentasi Tambahan Modul"
                    file_badge = "![Doc](https://img.shields.io/badge/-Docs-blue?style=flat-square)"
                else:
                    description = f"File {ext.replace('.', '').upper()}"
                    file_badge = f"![File](https://img.shields.io/badge/-{ext.replace('.', '').upper()}-lightgrey?style=flat-square)"
                    
                files.append({
                    "name": item.name,
                    "rel_path": f"{rel_dir}/{item.name}",
                    "badge": file_badge,
                    "size": file_size,
                    "description": description,
                    "ext": ext
                })
                
        # Cek file konten kustom (telemetry.md / analysis.md)
        custom_content = ""
        for custom_name in ['telemetry.md', 'analysis.md', 'notes.md']:
            cfile = task_dir / custom_name
            if cfile.exists():
                try:
                    with open(cfile, "r", encoding="utf-8") as cf:
                        custom_content = cf.read().strip()
                    break
                except Exception:
                    pass

        tasks.append({
            "folder": rel_dir,
            "title": title,
            "topic": topic,
            "status": status,
            "files": files,
            "cpp_count": cpp_count,
            "pdf_count": pdf_count,
            "loc": task_loc,
            "custom_content": custom_content
        })
        
    return tasks

def generate_markdown(tasks):
    """Buat konten README.md dengan estetika visual modern."""
    total_tasks = len(tasks)
    total_cpp = sum(t["cpp_count"] for t in tasks)
    total_pdf = sum(t["pdf_count"] for t in tasks)
    total_loc = sum(t["loc"] for t in tasks)
    
    md = []
    
    # 1. Header & Hero Section
    md.append('<div align="center">\n')
    md.append('# 🚀 DASPRO ACTIVITY & ASSIGNMENT HUB')
    md.append('### **Repositori Tugas & Portofolio Pemrograman C++**\n')
    md.append(f'[![Language](https://img.shields.io/badge/Language-{PROFILE["language"]}-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)')
    md.append(f'[![NIM](https://img.shields.io/badge/NIM-{PROFILE["nim"]}-black?style=for-the-badge&logo=github&logoColor=white)](https://github.com/{PROFILE["github_user"]})')
    md.append('[![Automated](https://img.shields.io/badge/Auto--Sync-GitHub_Actions-brightgreen?style=for-the-badge&logo=githubactions&logoColor=white)](https://github.com/)')
    md.append(f'[![Status](https://img.shields.io/badge/Status-Active_Semester-222222?style=for-the-badge)](https://github.com/)\n')
    md.append('</div>\n')
    md.append('---\n')
    
    # 2. Identitas Mahasiswa Card
    md.append('### 👤 Identitas Mahasiswa\n')
    md.append(f'> **Nama Lengkap** : **{PROFILE["name"]}**  ')
    md.append(f'> **NIM** : `{PROFILE["nim"]}`  ')
    md.append(f'> **Program Studi** : {PROFILE["prodi"]}  ')
    md.append(f'> **Institusi** : {PROFILE["univ"]}  ')
    md.append(f'> **Mata Kuliah** : {PROFILE["course"]}  \n')
    md.append('---\n')
    
    # 3. Dynamic Stats Dashboard Badges
    md.append('### 📊 Ringkasan Repositori\n')
    md.append('<div align="center">\n')
    md.append(f'<img src="https://img.shields.io/badge/TOTAL_MODUL_TUGAS-{total_tasks}_Modul-black?style=for-the-badge&labelColor=1a1a1a&color=007ACC" height="38" alt="Total Modul" />')
    md.append(f'<img src="https://img.shields.io/badge/SOURCE_FILES-{total_cpp}_Files-black?style=for-the-badge&labelColor=1a1a1a&color=4CAF50" height="38" alt="Source Files" />')
    md.append(f'<img src="https://img.shields.io/badge/DOKUMEN_PDF-{total_pdf}_Berkas-black?style=for-the-badge&labelColor=1a1a1a&color=E91E63" height="38" alt="Dokumen PDF" />')
    md.append(f'<img src="https://img.shields.io/badge/TOTAL_BARIS_KODE-{total_loc}_LOC-black?style=for-the-badge&labelColor=1a1a1a&color=FF9800" height="38" alt="Total LOC" />\n')
    md.append('</div>\n\n<br/>\n')
    
    # 4. Direktori & Index Tugas (Navigasi Cepat)
    md.append('### 📂 Direktori Tugas\n')
    md.append('| No | Modul Tugas | Topik / Fokus Materi | File C++ | Dokumen | Status | Navigasi |')
    md.append('| :-: | :--- | :--- | :-: | :-: | :-: | :-: |')
    
    for i, t in enumerate(tasks, 1):
        anchor = t["folder"].lower()
        md.append(f'| `{i:02d}` | **{t["title"]}** | `{t["topic"]}` | `{t["cpp_count"]}` | `{t["pdf_count"]}` | <span style="color:#4CAF50">●</span> {t["status"]} | [Buka Detail](#{anchor}) |')
    
    md.append('\n---\n')
    
    # 5. Detail Showcase Tiap Tugas
    md.append('### 📑 Showcase & Arsip Modul\n')
    
    for i, t in enumerate(tasks, 1):
        anchor = t["folder"].lower()
        md.append(f'<a id="{anchor}"></a>\n')
        md.append(f'#### {t["title"]}\n')
        md.append(f'> 📂 **Folder**: [`{t["folder"]}`](./{t["folder"]})  ')
        md.append(f'> 🎯 **Topik**: {t["topic"]}  ')
        md.append(f'> 📈 **Statistik**: `{t["cpp_count"]} File C++` | `{t["pdf_count"]} Dokumen PDF` | `{t["loc"]} Baris Kode`\n')
        
        # Tabel File dalam Tugas
        if t["files"]:
            md.append('| Berkas | Format | Ukuran | Deskripsi & Topik Pembahasan |')
            md.append('| :--- | :---: | :---: | :--- |')
            for f in t["files"]:
                file_link = f'[`{f["name"]}`](./{f["rel_path"]})'
                md.append(f'| {file_link} | {f["badge"]} | `{f["size"]}` | {f["description"]} |')
            md.append('')
            
        # Jika ada konten kustom / telemetri
        if t["custom_content"]:
            md.append(t["custom_content"])
            md.append('')
            
    # Format Waktu Indonesia (WIB)
    bulan_indo = {
        1: "Januari", 2: "Februari", 3: "Maret", 4: "April", 5: "Mei", 6: "Juni",
        7: "Juli", 8: "Agustus", 9: "September", 10: "Oktober", 11: "November", 12: "Desember"
    }
    now = datetime.now()
    current_time = f"{now.day} {bulan_indo[now.month]} {now.year}, {now.strftime('%H:%M')} WIB"
    
    # Footer dengan Dynamic GitHub Badge & Waktu Terakhir Sinkronisasi
    md.append('\n---\n\n<div align="center">\n')
    md.append(f'[![Last Commit](https://img.shields.io/github/last-commit/{PROFILE["github_user"]}/{PROFILE["repo_name"]}?style=flat-square&logo=github&label=Terakhir%20Diperbarui&color=007ACC)](https://github.com/{PROFILE["github_user"]}/{PROFILE["repo_name"]}/commits/main)\n')
    md.append(f'<sub>Terakhir disinkronkan otomatis pada: <b>{current_time}</b> • Dikelola oleh GitHub Actions</sub>\n')
    md.append('</div>\n')
    
    return "\n".join(md)

def main():
    print("🔍 Memindai direktori tugas...")
    tasks = scan_tasks()
    print(f"✨ Ditemukan {len(tasks)} modul tugas.")
    for t in tasks:
        print(f"   - {t['folder']}: {t['cpp_count']} file C++, {t['pdf_count']} PDF")
        
    print("📝 Menghasilkan README.md baru...")
    markdown_content = generate_markdown(tasks)
    
    readme_path = ROOT_DIR / "README.md"
    with open(readme_path, "w", encoding="utf-8") as f:
        f.write(markdown_content)
        
    print(f"✅ README.md berhasil diperbarui di: {readme_path}")

if __name__ == "__main__":
    main()
