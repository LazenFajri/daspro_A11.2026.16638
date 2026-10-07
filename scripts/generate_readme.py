#!/usr/bin/env python3
"""
DASPRO README Generator
Otomatis memindai folder tugas (Tugas*), sub-folder (Kasus*, modul, dll.),
menghitung statistik secara rekursif, dan membuat README.md berdesain modern & profesional.
"""

import os
import sys
import re
import json
import urllib.parse
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
    """Kunci pengurutan natural (misal: Tugas1, Tugas2, Tugas10, Kasus 1, Kasus 2)."""
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', str(s))]

def slugify(text):
    """Buat slug URL anchor ramah GitHub Markdown tanpa spasi bermasalah."""
    s = re.sub(r'[^\w\s-]', '', str(text)).strip().lower()
    return re.sub(r'[-\s]+', '-', s)

def format_folder_name(name):
    """Format nama folder menjadi judul yang rapi."""
    match = re.match(r'Tugas(\d+)(.*)', name, re.IGNORECASE)
    if match:
        num = match.group(1)
        rest = match.group(2).strip()
        spaced = re.sub(r'([a-z])([A-Z])', r'\1 \2', rest).strip()
        if spaced:
            return f"Tugas {num} — {spaced}"
        return f"Tugas {num}"
    return name

def format_file_size(size_bytes):
    """Format ukuran file ke KB / MB / B."""
    if size_bytes < 1024:
        return f"{size_bytes} B"
    elif size_bytes < 1024 * 1024:
        return f"{size_bytes / 1024:.1f} KB"
    else:
        return f"{size_bytes / (1024 * 1024):.1f} MB"

def count_lines_of_code(file_path):
    """Hitung baris kode (LOC non-empty) dari file teks."""
    try:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            return sum(1 for line in f if line.strip())
    except Exception:
        return 0

def extract_file_description(file_path, file_name="", subfolder=""):
    """
    Ekstrak judul / deskripsi file secara cerdas:
    1. Membaca header komentar C++ (Judul:, Deskripsi:, dll)
    2. Mendeteksi pola penamaan Kasus (dari nama file atau subfolder)
    3. Mendeteksi jenis dokumen PDF (Notasi Algoritmik, Analisis, Laporan)
    4. Fallback yang informatif
    """
    ext = file_path.suffix.lower()

    # 1. Cek explicit Judul / Deskripsi dari header komentar
    if ext in {'.cpp', '.c', '.cxx', '.h', '.hpp'}:
        try:
            with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read(2048) # 2KB pertama
                
                # Cek 'Judul : ...'
                match = re.search(r'judul\s*:\s*([^\n\r]+)', content, re.IGNORECASE)
                if match:
                    desc = match.group(1).strip()
                    return desc[0].upper() + desc[1:] if desc else ""
        except Exception:
            pass

    # 2. Pola Kasus terstruktur (cek dari nama file dan nama subfolder)
    # 2a. Cek nama kasus eksplisit dari subfolder (misal: "Kasus 1 Autentikasi Login Bertingkat")
    m_sub = re.search(r'kasus\s*(\d+)[\s—\-_:]+(.+)', subfolder, re.IGNORECASE)
    if m_sub:
        k_num = m_sub.group(1)
        k_title = m_sub.group(2).strip()
        if ext in {'.cpp', '.c', '.cxx', '.h', '.hpp'}:
            return f"Kasus {k_num} — {k_title}"
        elif ext == '.pdf':
            return f"Dokumen Laporan & Analisis — Kasus {k_num} ({k_title})"

    # 2b. Cek nama kasus eksplisit dari nama file (misal: "Kasus 1 Data Sepatu Sederhana.cpp")
    m_fn = re.search(r'kasus\s*(\d+)[\s—\-_:]+(.+)', file_name, re.IGNORECASE)
    if m_fn:
        k_num = m_fn.group(1)
        k_title = Path(m_fn.group(2)).stem.strip()
        if ext in {'.cpp', '.c', '.cxx', '.h', '.hpp'}:
            return f"Kasus {k_num} — {k_title}"
        elif ext == '.pdf':
            return f"Dokumen Laporan & Analisis — Kasus {k_num} ({k_title})"

    # 2c. Pola kasus umum
    combined_name = f"{subfolder}_{file_name}"
    kasus_match = re.search(r'kasus\s*(\d+)', combined_name, re.IGNORECASE)
    if kasus_match:
        k_num = kasus_match.group(1)
        stem_raw = Path(file_name).stem.replace('_', ' ').replace('-', ' ').strip()
        if not re.match(r'^pas\s*kasus', stem_raw, re.IGNORECASE) and not re.match(r'^kasus\s*\d+$', stem_raw, re.IGNORECASE):
            stem_spaced = re.sub(r'([a-z])([A-Z])', r'\1 \2', stem_raw)
            topic = f"Kasus {k_num} — {stem_spaced}"
        else:
            fallback_kasus = {
                "1": "Perhitungan Aljabar, Statistik Bilangan & Konversi Suhu",
                "2": "Kalkulasi Upah Kerja & Persentase Lembur",
                "3": "Relasi Logika Dua Bilangan & Deret Angka",
                "4": "Pemrosesan Array 1D (Min, Max, Sum, & Rata-rata)",
                "5": "Definisi Tipe Bentukan Struct Sederhana",
                "6": "Struktur Data Titik Koordinat (ADT Point)",
                "7": "Konsep Alamat Memori & Manipulasi Variabel Pointer"
            }
            topic = f"Kasus {k_num} — {fallback_kasus.get(k_num, f'Praktikum Pemrograman — Kasus {k_num}')}"

        if ext == '.pdf':
            fn_low = file_name.lower()
            if 'notasi' in fn_low or 'algoritmik' in fn_low:
                return f"Dokumen Notasi Algoritmik — Kasus {k_num}"
            elif 'analisis' in fn_low:
                return f"Dokumen Analisis — Kasus {k_num}"
            return f"Dokumen Laporan & Analisis — Kasus {k_num}"
        elif ext in {'.h', '.hpp'}:
            return f"Header Specification & ADT Definition — Kasus {k_num}"
        else:
            return topic


    # 3. Komentar umum untuk file non-kasus
    if ext in {'.cpp', '.c', '.cxx', '.h', '.hpp'}:
        try:
            with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read(2048)
                match_kasus = re.search(r'//\s*([0-9]+\.\s*[^;\n\r]+)', content)
                if match_kasus:
                    return match_kasus.group(1).strip()
                lines = content.splitlines()
                for line in lines:
                    s = line.strip()
                    if s.startswith("//") and not s.startswith("///") and len(s) > 4:
                        cleaned = s.lstrip("/").strip()
                        if not any(skip in cleaned.lower() for skip in ["include", "using namespace", "int main", "typedef"]):
                            return cleaned[0].upper() + cleaned[1:]
        except Exception:
            pass

    # 3. Analisis untuk PDF umum
    if ext == '.pdf':
        fn_low = file_name.lower()
        if 'halfmarathon' in fn_low:
            return "Dokumen Analisis & Evaluasi Split Half-Marathon"
        elif 'laporan' in fn_low:
            return "Dokumen Laporan Praktikum & Pengujian Program"
        return "Dokumen Analisis / Notasi Algoritmik / Laporan"

    # 4. Header umum
    if ext in {'.h', '.hpp'}:
        return "Header Specification & ADT Definition"

    # 5. Default C++
    if ext in {'.cpp', '.c', '.cxx'}:
        return "Implementasi Program C++"

    return f"Berkas {ext.replace('.', '').upper()}"

def scan_tasks():
    """Pindai semua folder tugas dan kumpulkan informasinya secara rekursif."""
    tasks = []
    ignored_dirs = {'.git', '.github', 'scripts', '.vscode', '__pycache__', 'build', '.idea'}
    
    candidate_dirs = [
        d for d in ROOT_DIR.iterdir()
        if d.is_dir() and d.name not in ignored_dirs and not d.name.startswith('.')
    ]
    
    # Filter folder tugas (awalan 'Tugas' atau memiliki file .cpp di mana saja di dalamnya)
    task_dirs = []
    for d in candidate_dirs:
        has_cpp = any(d.rglob("*.cpp"))
        if d.name.lower().startswith("tugas") or has_cpp:
            task_dirs.append(d)
            
    task_dirs.sort(key=lambda p: natural_sort_key(p.name))
    
    for task_dir in task_dirs:
        rel_dir = task_dir.name
        
        # Cek info.json di root folder tugas
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
        status = custom_meta.get("status", "Selesai")
        
        # Pindai SEMUA file secara rekursif (termasuk sub-folder dan sub-kasus)
        all_raw_files = [p for p in task_dir.rglob("*") if p.is_file()]
        
        files = []
        cpp_count = 0
        pdf_count = 0
        header_count = 0
        task_loc = 0
        subfolder_set = set()
        
        # Ekstensi yang diabaikan (binary / compiled / arsip)
        ignored_extensions = {'.exe', '.o', '.obj', '.out', '.bin', '.rar', '.zip', '.7z', '.tar', '.gz'}
        special_doc_names = {'telemetry.md', 'info.json', 'analysis.md', 'notes.md'}
        
        for item in sorted(all_raw_files, key=lambda p: (
            str(p.relative_to(task_dir).parent).lower(),
            0 if p.suffix.lower() == '.cpp' else (1 if p.suffix.lower() in ['.h', '.hpp'] else 2),
            natural_sort_key(p.name)
        )):
            ext = item.suffix.lower()
            if ext in ignored_extensions:
                continue
            if item.name.lower() in special_doc_names or item.name.startswith('.'):
                continue
                
            rel_to_task = item.relative_to(task_dir)
            subfolder_parts = rel_to_task.parts[:-1]
            subfolder = "/".join(subfolder_parts) if subfolder_parts else ""
            if subfolder:
                subfolder_set.add(subfolder)
                
            rel_path = f"{rel_dir}/{rel_to_task.as_posix()}"
            # URL encode untuk link Markdown aman spasi
            encoded_url = urllib.parse.quote(rel_path)
            
            file_size = format_file_size(item.stat().st_size)
            loc = 0
            file_badge = ""
            
            if ext in {'.cpp', '.c', '.cxx'}:
                cpp_count += 1
                loc = count_lines_of_code(item)
                task_loc += loc
                file_badge = "![C++](https://img.shields.io/badge/-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)"
            elif ext in {'.h', '.hpp'}:
                header_count += 1
                loc = count_lines_of_code(item)
                task_loc += loc
                file_badge = "![Header](https://img.shields.io/badge/-Header-gray?style=flat-square)"
            elif ext == '.pdf':
                pdf_count += 1
                file_badge = "![PDF](https://img.shields.io/badge/-PDF-red?style=flat-square&logo=adobeacrobatreader&logoColor=white)"
            elif ext == '.md':
                file_badge = "![Doc](https://img.shields.io/badge/-Docs-blue?style=flat-square)"
            else:
                ext_name = ext.replace('.', '').upper()
                file_badge = f"![File](https://img.shields.io/badge/-{ext_name}-lightgrey?style=flat-square)"
                
            description = extract_file_description(item, item.name, subfolder)
            
            files.append({
                "name": item.name,
                "subfolder": subfolder,
                "rel_path": rel_path,
                "encoded_url": encoded_url,
                "badge": file_badge,
                "size": file_size,
                "loc": loc,
                "description": description,
                "ext": ext
            })
            
        # Kumpulkan konten kustom (telemetry.md / analysis.md)
        custom_content_blocks = []
        for doc_name in ['telemetry.md', 'analysis.md', 'notes.md']:
            cfile = task_dir / doc_name
            if cfile.exists():
                try:
                    with open(cfile, "r", encoding="utf-8") as cf:
                        content = cf.read().strip()
                        if content:
                            custom_content_blocks.append(content)
                except Exception:
                    pass
                    
        # Cek jika ada telemetry/analysis di subfolder
        for sub in sorted(list(subfolder_set)):
            for doc_name in ['telemetry.md', 'analysis.md', 'notes.md']:
                sub_cfile = task_dir / sub / doc_name
                if sub_cfile.exists():
                    try:
                        with open(sub_cfile, "r", encoding="utf-8") as cf:
                            content = cf.read().strip()
                            if content:
                                custom_content_blocks.append(content)
                    except Exception:
                        pass

        subfolders_sorted = sorted(list(subfolder_set), key=natural_sort_key)
        
        tasks.append({
            "folder": rel_dir,
            "title": title,
            "topic": topic,
            "status": status,
            "files": files,
            "subfolders": subfolders_sorted,
            "cpp_count": cpp_count,
            "pdf_count": pdf_count,
            "header_count": header_count,
            "loc": task_loc,
            "custom_content": "\n\n".join(custom_content_blocks)
        })
        
    return tasks

def generate_markdown(tasks):
    """Buat konten README.md dengan estetika visual modern, presisi, dan informatif."""
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
    md.append(f'[![Status](https://img.shields.io/badge/Status-Active_Semester-222222?style=for-the-badge)](https://github.com/{PROFILE["github_user"]}/{PROFILE["repo_name"]})\n')
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
    md.append('| No | Modul Tugas | Topik / Fokus Materi | Sub-Modul | File C++ | Dokumen | Status | Navigasi |')
    md.append('| :-: | :--- | :--- | :---: | :---: | :---: | :---: | :---: |')
    
    for i, t in enumerate(tasks, 1):
        anchor = slugify(t["folder"])
        
        # Ringkasan sub-modul
        sub_count = len(t["subfolders"])
        if sub_count > 0:
            if all('kasus' in s.lower() for s in t["subfolders"]):
                sub_label = f"`{sub_count} Kasus`"
            else:
                sub_label = f"`{sub_count} Sub-Folder`"
        else:
            sub_label = "—"
            
        md.append(f'| `{i:02d}` | **{t["title"]}** | `{t["topic"]}` | {sub_label} | `{t["cpp_count"]}` | `{t["pdf_count"]}` | <span style="color:#4CAF50">●</span> {t["status"]} | [Buka Detail](#{anchor}) |')
    
    md.append('\n---\n')
    
    # 5. Detail Showcase Tiap Tugas
    md.append('### 📑 Showcase & Arsip Modul\n')
    
    for i, t in enumerate(tasks, 1):
        anchor = slugify(t["folder"])
        folder_encoded = urllib.parse.quote(t["folder"])
        
        md.append(f'<a id="{anchor}"></a>\n')
        md.append(f'#### {t["title"]}\n')
        md.append(f'> 📂 **Folder**: [`{t["folder"]}`](./{folder_encoded})  ')
        md.append(f'> 🎯 **Topik**: {t["topic"]}  ')
        
        stat_line = f'> 📈 **Statistik**: `{t["cpp_count"]} File C++`'
        if t["header_count"] > 0:
            stat_line += f' | `{t["header_count"]} Header`'
        stat_line += f' | `{t["pdf_count"]} Dokumen PDF` | `{t["loc"]} Baris Kode`'
        md.append(stat_line)
        
        if t["subfolders"]:
            sub_badges = " • ".join(f"`{s}`" for s in t["subfolders"])
            md.append(f'> 🗂️ **Struktur Sub-Folder**: {sub_badges}\n')
        else:
            md.append('')
            
        # Tabel File dalam Tugas (otomatis mendeteksi file dalam sub-folder)
        if t["files"]:
            has_subfolders = bool(t["subfolders"])
            
            if has_subfolders:
                md.append('| Sub-Folder / Modul | Berkas | Format | Ukuran | Baris | Deskripsi & Topik Pembahasan |')
                md.append('| :--- | :--- | :---: | :---: | :---: | :--- |')
                for f in t["files"]:
                    file_link = f'[`{f["name"]}`](./{f["encoded_url"]})'
                    sub_label = f'📁 `{f["subfolder"]}`' if f["subfolder"] else '—'
                    loc_label = f'`{f["loc"]}`' if f["ext"] in ['.cpp', '.c', '.cxx', '.h', '.hpp'] else '—'
                    md.append(f'| {sub_label} | {file_link} | {f["badge"]} | `{f["size"]}` | {loc_label} | {f["description"]} |')
            else:
                md.append('| Berkas | Format | Ukuran | Baris | Deskripsi & Topik Pembahasan |')
                md.append('| :--- | :---: | :---: | :---: | :--- |')
                for f in t["files"]:
                    file_link = f'[`{f["name"]}`](./{f["encoded_url"]})'
                    loc_label = f'`{f["loc"]}`' if f["ext"] in ['.cpp', '.c', '.cxx', '.h', '.hpp'] else '—'
                    md.append(f'| {file_link} | {f["badge"]} | `{f["size"]}` | {loc_label} | {f["description"]} |')
                    
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

def update_task_tracker(tasks):
    """Otomatis sinkronkan task-tracker/index.html dengan modul dan sub-tugas terbaru."""
    tracker_path = ROOT_DIR / "task-tracker" / "index.html"
    if not tracker_path.exists():
        return
        
    content = tracker_path.read_text(encoding="utf-8")
    
    total_tasks = len(tasks)
    total_cpp = sum(t["cpp_count"] for t in tasks)
    total_pdf = sum(t["pdf_count"] for t in tasks)
    total_loc = sum(t["loc"] for t in tasks)
    
    # 1. Update data-target stats in stats-section
    content = re.sub(
        r'(<div class="stat-card stat-total">.*?<span class="stat-number"\s+data-target=")\d+(")',
        rf'\g<1>{total_tasks}\g<2>',
        content, flags=re.DOTALL
    )
    content = re.sub(
        r'(<div class="stat-card stat-files">.*?<span class="stat-number"\s+data-target=")\d+(")',
        rf'\g<1>{total_cpp}\g<2>',
        content, flags=re.DOTALL
    )
    content = re.sub(
        r'(<div class="stat-card stat-docs">.*?<span class="stat-number"\s+data-target=")\d+(")',
        rf'\g<1>{total_pdf}\g<2>',
        content, flags=re.DOTALL
    )
    content = re.sub(
        r'(<div class="stat-card stat-loc">.*?<span class="stat-number"\s+data-target=")\d+(")',
        rf'\g<1>{total_loc}\g<2>',
        content, flags=re.DOTALL
    )
    
    # 2. Generate task cards HTML
    cards_html = []
    status_icons = {
        "done": '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><polyline points="20 6 9 17 4 12"/></svg>',
        "progress": '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="10"/><polyline points="12 6 12 12 16 14"/></svg>',
        "pending": '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="10"/><line x1="8" y1="12" x2="16" y2="12"/></svg>'
    }
    
    for i, t in enumerate(tasks, 1):
        status_raw = t.get("status", "Selesai").strip()
        status_key = status_raw.lower()
        if "proses" in status_key or "progress" in status_key:
            data_status = "proses"
            status_class = "progress"
            status_label = "Dalam Proses"
            pct = 50
        elif "belum" in status_key or "pending" in status_key:
            data_status = "belum"
            status_class = "pending"
            status_label = "Belum Mulai"
            pct = 0
        else:
            data_status = "selesai"
            status_class = "done"
            status_label = "Selesai"
            pct = 100

        badge_class = f"modul-{((i - 1) % 6) + 1}"
        icon_svg = status_icons[status_class]
        
        # Sub-stats
        sub_count = len(t["subfolders"]) if t["subfolders"] else len([f for f in t["files"] if f["ext"] in {'.cpp', '.c', '.cxx', '.h', '.hpp'}])
        sub_label = "Sub-Folder" if t["subfolders"] else "Kasus"
        
        # Subtasks
        subtasks_html = []
        code_files = [f for f in t["files"] if f["ext"] in {'.cpp', '.c', '.cxx', '.h', '.hpp'}]
        display_files = code_files if code_files else t["files"]
        
        for f in display_files:
            item_status_class = "done" if status_class == "done" else status_class
            desc = f.get("description", f["name"])
            loc_or_size = f"{f['loc']} LOC" if f['loc'] > 0 else f['size']
            meta = f"{loc_or_size} • {f['name']}"
            check_svg = '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3"><polyline points="20 6 9 17 4 12"/></svg>'
            
            subtasks_html.append(f"""                            <div class="detail-item {item_status_class}" data-sub="{desc}">
                                <div class="check-circle">{check_svg}</div>
                                <div class="detail-info">
                                    <span class="detail-title">{desc}</span>
                                    <span class="detail-meta">{meta}</span>
                                </div>
                            </div>""")

        subtasks_block = "\n".join(subtasks_html)
        
        card = f"""                <!-- Modul {i}: {t['title']} -->
                <div class="task-card" data-status="{data_status}" data-module="{i}">
                    <div class="card-header">
                        <div class="card-badge {badge_class}">Modul {i:02d}</div>
                        <div class="card-status {status_class}">
                            {icon_svg}
                            {status_label}
                        </div>
                    </div>
                    <h3 class="card-title">{t['title']}</h3>
                    <p class="card-topic">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="10"/><path d="M12 16v-4M12 8h.01"/></svg>
                        {t['topic']}
                    </p>
                    <div class="card-stats">
                        <div class="mini-stat">
                            <span class="mini-num">{t['cpp_count']}</span>
                            <span class="mini-label">File C++</span>
                        </div>
                        <div class="mini-stat">
                            <span class="mini-num">{t['pdf_count']}</span>
                            <span class="mini-label">Dokumen</span>
                        </div>
                        <div class="mini-stat">
                            <span class="mini-num">{t['loc']}</span>
                            <span class="mini-label">LOC</span>
                        </div>
                        <div class="mini-stat">
                            <span class="mini-num">{sub_count}</span>
                            <span class="mini-label">{sub_label}</span>
                        </div>
                    </div>
                    <div class="card-progress">
                        <div class="card-progress-bar" style="--progress: {pct}%"></div>
                    </div>
                    <button class="card-expand" aria-label="Lihat Detail" onclick="toggleExpand(this)">
                        <span>Lihat Detail</span>
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><polyline points="6 9 12 15 18 9"/></svg>
                    </button>
                    <div class="card-details">
                        <div class="details-grid">
{subtasks_block}
                        </div>
                    </div>
                </div>"""
        cards_html.append(card)

    all_cards_block = "\n\n".join(cards_html)
    
    # 3. Replace section #tasks
    content = re.sub(
        r'(<section class="tasks-section" id="tasks">).*?(</section>)',
        f'\\1\n\n{all_cards_block}\n            \\2',
        content, flags=re.DOTALL
    )
    
    # 4. Generate Timeline
    timeline_html = []
    for i, t in enumerate(tasks, 1):
        status_raw = t.get("status", "Selesai").strip().lower()
        t_dot = "done" if "selesai" in status_raw else ("progress" if "proses" in status_raw else "pending")
        k_count = len(t["subfolders"]) if t["subfolders"] else t["cpp_count"]
        t_head = t['title']
        if len(t_head) > 40 and " — " in t_head:
            parts = t_head.split(" — ")
            t_head = f"{parts[0]} — {parts[1][:30]}..." if len(parts[1]) > 32 else t_head

        timeline_html.append(f"""                    <div class="timeline-item">
                        <div class="timeline-dot {t_dot}"></div>
                        <div class="timeline-content">
                            <span class="timeline-date">Modul {i:02d}</span>
                            <h4>{t_head} — {k_count} Kasus Selesai</h4>
                            <p>{t['topic']}</p>
                        </div>
                    </div>""")

    timeline_block = "\n".join(timeline_html)
    content = re.sub(
        r'(<div class="timeline">).*?(</div>\s*</section>)',
        f'\\1\n{timeline_block}\n                \\2',
        content, flags=re.DOTALL
    )

    # 5. Update sync timestamp in footer
    months = ["Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"]
    now = datetime.now()
    month_name = months[now.month - 1]
    time_str = f"{now.day} {month_name} {now.year}, {now.strftime('%H:%M')} WIB"
    content = re.sub(
        r'<p class="footer-sync">Terakhir disinkronkan:.*?</p>',
        f'<p class="footer-sync">Terakhir disinkronkan: {time_str}</p>',
        content
    )
    
    tracker_path.write_text(content, encoding="utf-8")
    print(f"✅ task-tracker/index.html berhasil disinkronkan ({total_tasks} modul, {total_cpp} C++, {total_loc} LOC).")

def update_portal_index(tasks):
    """Otomatis sinkronkan landing page (index.html) dengan modul dan statistik terbaru."""
    index_path = ROOT_DIR / "index.html"
    if not index_path.exists():
        return
        
    content = index_path.read_text(encoding="utf-8")
    
    total_tasks = len(tasks)
    total_cpp = sum(t["cpp_count"] for t in tasks)
    total_loc = sum(t["loc"] for t in tasks)
    
    # Update hero stats
    content = re.sub(
        r'(<div class="hero-stat-num"\s+data-count=")\d+(">\d*</div>\s*<div class="hero-stat-label">Modul Tugas</div>)',
        rf'\g<1>{total_tasks}\g<2>',
        content
    )
    content = re.sub(
        r'(<div class="hero-stat-num"\s+data-count=")\d+(">\d*</div>\s*<div class="hero-stat-label">Source Files</div>)',
        rf'\g<1>{total_cpp}\g<2>',
        content
    )
    content = re.sub(
        r'(<div class="hero-stat-num"\s+data-count=")\d+(">\d*</div>\s*<div class="hero-stat-label">Baris Kode</div>)',
        rf'\g<1>{total_loc}\g<2>',
        content
    )
    
    # Update Modul Chips
    chips_html = []
    for i, t in enumerate(tasks, 1):
        dot_cls = f"c{((i - 1) % 6) + 1}"
        title = t["title"]
        if "Kulino" in title:
            chip_text = "Tugas 1 — Kulino"
        elif "Fun Run" in title:
            chip_text = "Tugas 1 — Fun Run & ADT"
        elif "Daspro Latihan 2" in title:
            chip_text = "Daspro Latihan 2"
        elif "Daspro Latihan" in title:
            chip_text = "Daspro Latihan"
        elif "Tugas 2" in title:
            chip_text = "Tugas 2 — Kondisi & Array"
        elif " — " in title:
            parts = title.split(" — ")
            chip_text = f"{parts[0]} — {parts[1][:20]}..." if len(parts[1]) > 22 else title
        else:
            chip_text = title

        status_text = "✓ Done" if t.get("status", "Selesai").lower() == "selesai" else "⚡ Active"
        chips_html.append(f"""                <div class="modul-chip">
                    <span class="chip-dot {dot_cls}"></span>
                    {chip_text}
                    <span class="chip-status">{status_text}</span>
                </div>""")

    chips_block = "\n".join(chips_html)
    content = re.sub(
        r'(<!-- Modul Chips -->\s*<div class="moduls-row">).*?(</div>\s*</section>)',
        f'\\1\n{chips_block}\n            \\2',
        content, flags=re.DOTALL
    )
    
    index_path.write_text(content, encoding="utf-8")
    print(f"✅ index.html berhasil disinkronkan ({total_tasks} modul chips).")


def setup_git_pre_commit_hook():
    """Pasang git hook pre-commit otomatis jika berada di repositori git."""
    git_hooks_dir = ROOT_DIR / ".git" / "hooks"
    if not git_hooks_dir.exists():
        return
        
    hook_file = git_hooks_dir / "pre-commit"
    hook_content = """#!/bin/sh
# Git Pre-Commit Hook: Otomatis perbarui README, Tracker, dan Portal sebelum commit
echo "[Git Hook] Memperbarui README.md, Task Tracker & Portal..."
python scripts/generate_readme.py
git add README.md index.html task-tracker/index.html
"""
    try:
        # Tulis hook jika belum ada atau berbeda
        if not hook_file.exists() or hook_file.read_text(encoding="utf-8") != hook_content:
            with open(hook_file, "w", encoding="utf-8", newline="\n") as hf:
                hf.write(hook_content)
    except Exception:
        pass

def main():
    print("🔍 Memindai direktori tugas dan sub-folder secara rekursif...")
    tasks = scan_tasks()
    print(f"✨ Ditemukan {len(tasks)} modul tugas.")
    for t in tasks:
        print(f"   📂 {t['folder']} ({len(t['subfolders'])} sub-folder): {t['cpp_count']} file C++, {t['pdf_count']} PDF, {t['loc']} LOC")
        
    print("📝 Menghasilkan README.md baru...")
    markdown_content = generate_markdown(tasks)
    
    readme_path = ROOT_DIR / "README.md"
    with open(readme_path, "w", encoding="utf-8") as f:
        f.write(markdown_content)
    print(f"✅ README.md berhasil diperbarui di: {readme_path}")
    
    print("🚀 Menyinkronkan Dashboard Task Tracker...")
    update_task_tracker(tasks)

    print("🌐 Menyinkronkan Landing Page Portal...")
    update_portal_index(tasks)
        
    # Pasang git pre-commit hook otomatis
    setup_git_pre_commit_hook()

if __name__ == "__main__":
    main()

