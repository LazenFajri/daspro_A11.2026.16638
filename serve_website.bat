@echo off
echo ========================================================
echo   DASPRO Web Portal - Menjalankan Local Web Server...
echo   Mahasiswa: Muhammad Fajri Setyawan (A11.2026.16638)
echo ========================================================
echo.
echo Membuka website di peramban: http://localhost:8000
echo Tekan Ctrl+C di terminal ini untuk menghentikan server.
echo.

start http://localhost:8000
python -m http.server 8000
