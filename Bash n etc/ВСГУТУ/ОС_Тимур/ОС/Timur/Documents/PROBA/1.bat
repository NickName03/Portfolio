@echo off
rem �஢�ઠ ������ ��ࠬ��஢ ��������� ��ப�
IF -%1==- GOTO NoParam
IF -%2==- GOTO NoParam
rem �뤥����� �㦭�� ��ப �� 䠩�� protokol.txt
FIND "%1.%2" protokol.txt | SORT /+26 > %1%2.txt
GOTO End
:NoParam
ECHO He ������ ����室��� ��ࠬ���� ��������� ��ப�!
PAUSE
:End
