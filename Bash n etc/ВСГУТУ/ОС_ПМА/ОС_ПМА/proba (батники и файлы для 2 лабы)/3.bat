@echo off
rem �஢�ઠ ������ ��ࠬ��� ��������� ��ப�
IF -%1==- GOTO NoDir
rem �맮� � 横�� 䠩�� 3_l.bat ��� ����஢���� �㦭��� 䠩��
FOR %%f IN (*.txt) DO IF NOT -%%f==-%2 CALL 3_l.bat %%f %1
GOTO End
:NoDir
ECHO He 㪠��� ��⠫�� ��� ����஢����!
PAUSE
:End
