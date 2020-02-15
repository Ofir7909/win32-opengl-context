@echo off
cl main.c libs\glad\src\glad.c /Ilibs\glad\include /Fegame.exe /Zi /D "UNICODE" /D "_UNICODE" /nologo user32.lib gdi32.lib opengl32.lib 
