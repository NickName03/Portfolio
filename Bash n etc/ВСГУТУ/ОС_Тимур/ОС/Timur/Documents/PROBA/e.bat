
@echo off
rem �஢�ઠ ��ࠬ��஢ ��������� ��ப�
if "%1"=="" goto Spravka
if "%1"=="/?" goto Spravka
rem ���������� ⥪�騩 ��⠫��
pushd .
rem � �ᯨᠭ�� �ᥣ� ���� 6 ���ᮢ, ���쬥� �� �᫮ �� ����筮�
rem ����� ��।����� ��ࠬ��஢ ������ ���� �� ����� 6
for %%G in (%1 %2 %3 %4 %5 %6) do (
rem ���室�� � ��⠫�� �� ��।������ ��ࠬ����
cd C:\Users\Timur\Documents\PROBA\Students\%%G
echo ����⪠ 㤠����� ���㦭�� 䠩��� � Stud\%%G
for /R %%f in (*.BAK *.TMP) do  ( 
echo 㤠����� %%f
del %%f )
)
echo �������� ���㦭�� 䠩��� ����祭�. �����饭�� � ���� ��⠫��
popd
echo �஢�ઠ ࠡ��ᯮᮡ����
tree /F C:\Users\Timur\Documents\PROBA\Students
goto End

:Spravka
echo ��� 䠩� �।�����祭 ��� ४��ᨢ���� 㤠����� *.BAK � *.TMP 䠩���
echo � ��⥬� ��㤥��᪨� ��⠫����. � ����⢥ ��ࠬ��� ��।����� �����
echo ������ ������ �����, ��㯯� ��762.
goto End

:End
