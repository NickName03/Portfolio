@echo off
rem �஢�ઠ ��ࠬ��஢
if "%1" == "" goto NoExe
if "%1" == "/?" goto NoExe
if not "%1" == "MpCmdRun.exe" goto WrongExe
rem ����
echo 1 - ��� �
echo 2 - ��� D
choice /C 12
if ERRORLEVEL 2 goto ScanD
if ERRORLEVEL 1 goto ScanC
echo �롮� �� �� ᤥ���.
goto End
:ScanC
echo ����஥ ᪠��஢���� ��᪠ C
rem ����� ���⭨�� Windows �� ������� �஢��� (ScanType1) � ��⠫��� (����� ��⠭����� ���� ����� ��᫥ -File)
"%ProgramFiles%\Windows Defender\MpCmdRun.exe" -Scan -ScanType 1 -File C:\
goto End
:ScanD
echo ����஥ ᪠��஢���� ��᪠ D
"%ProgramFiles%\Windows Defender\MpCmdRun.exe" -Scan -ScanType 1 -File D:\
goto End
:WrongExe
echo ��� ⠪��� ��⨢����.
goto End
:NoExe
echo ind.bat, 䠩� ��� �஢�ન ��⠫���� �� ������, ������� ��࠭�� � ���� ���, ���� ��ॢ�������� ����
goto End
:End