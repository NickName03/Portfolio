@echo off
rem ����஢���� 䠩��
XCOPY %1 %2 /D /C > NUL
rem �஢�ઠ �ᯥ譮�� ����஢����
IF ERRORLEVEL 0 GOTO Success
rem ������ � 䠩� ���� ���ଠ樨 �� �訡�� �� ����஢����
ECHO �訡��: %1 >> logcopy.log
GOTO End
:Success
rem ������ � 䠩� ���� ���ଠ樨 �� �ᯥ譮� ����஢����
ECHO �ᯥ譮: %1 >> logcopy.log
:End
