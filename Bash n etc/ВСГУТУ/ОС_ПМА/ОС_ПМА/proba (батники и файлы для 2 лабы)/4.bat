@echo off
IF -%1==- GOTO NoDir
cls
rem �뢮� ���� �� �࠭
ECHO 1 - �� �࠭
ECHO 2 - � 䠩� C:\Users\def\proba\catalog.txt
rem �뢮� ���᪠��� ��� �����
CHOICE /C 12
rem ��।������ ᤥ������� �롮�
IF ERRORLEVEL 2 GOTO DirToFile
IF ERRORLEVEL 1 GOTO DirToCon
ECHO �롮� �� �� ᤥ���.
GOTO End
:DirToCon
DIR %1 | MORE
GOTO End
:DirToFile
DIR %1 > C:\Users\def\proba\catalog.txt
GOTO End
:NoDir
ECHO He 㪠��� ��⠫�� ��� ᪠��஢����!
PAUSE
:End
