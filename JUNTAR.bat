@echo off
rem Junta os arquivos partidos (name.part001 ...) de volta; confere o tamanho e o SHA-256 (PARTES.json).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0juntar.ps1"
exit /b %ERRORLEVEL%
