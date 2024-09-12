@echo off
IF -%1==- GOTO NoDir
cls
rem Вывод меню на экран
ECHO 1 - На экран
ECHO 2 - В файл C:\Users\def\proba\catalog.txt
rem Вывод подсказки для ввода
CHOICE /C 12
rem Определение сделанного выбора
IF ERRORLEVEL 2 GOTO DirToFile
IF ERRORLEVEL 1 GOTO DirToCon
ECHO Выбор не был сделан.
GOTO End
:DirToCon
DIR %1 | MORE
GOTO End
:DirToFile
DIR %1 > C:\Users\def\proba\catalog.txt
GOTO End
:NoDir
ECHO He указан каталог для сканирования!
PAUSE
:End
