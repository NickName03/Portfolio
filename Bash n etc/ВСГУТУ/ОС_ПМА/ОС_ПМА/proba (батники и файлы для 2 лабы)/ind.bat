@echo off
rem проверка параметров
if "%1" == "" goto NoExe
if "%1" == "/?" goto NoExe
if not "%1" == "MpCmdRun.exe" goto WrongExe
rem Меню
echo 1 - Диск С
echo 2 - Диск D
choice /C 12
if ERRORLEVEL 2 goto ScanD
if ERRORLEVEL 1 goto ScanC
echo Выбор не был сделан.
goto End
:ScanC
echo Быстрое сканирование диска C
rem запуск защитника Windows на быструю проверку (ScanType1) в каталоге (можно установить любую папку после -File)
"%ProgramFiles%\Windows Defender\MpCmdRun.exe" -Scan -ScanType 1 -File C:\
goto End
:ScanD
echo Быстрое сканирование диска D
"%ProgramFiles%\Windows Defender\MpCmdRun.exe" -Scan -ScanType 1 -File D:\
goto End
:WrongExe
echo Нет такого антивируса.
goto End
:NoExe
echo ind.bat, файл для проверки каталогов на вирусы, область выбранный в меню диск, автор Перевозникова Мария
goto End
:End