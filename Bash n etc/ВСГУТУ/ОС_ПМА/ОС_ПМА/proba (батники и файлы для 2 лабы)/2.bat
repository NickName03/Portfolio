@echo off
rem �஢�ઠ ������ ��ࠬ��� ��������� ��ப�
IF -%1==- GOTO NoDir
rem ����஢���� �㦭�� 䠩���
FOR %%f IN (*.txt) DO IF NOT -%%f==-%2 COPY %%f %1
GOTO End
:NoDir
ECHO He 㪠��� ��⠫�� ��� ����஢����!
PAUSE
:End
