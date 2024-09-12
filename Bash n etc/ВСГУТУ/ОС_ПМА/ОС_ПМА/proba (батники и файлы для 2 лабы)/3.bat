@echo off
rem Проверка наличия параметра командной строки
IF -%1==- GOTO NoDir
rem Вызов в цикле файла 3_l.bat для копирования нужного файла
FOR %%f IN (*.txt) DO IF NOT -%%f==-%2 CALL 3_l.bat %%f %1
GOTO End
:NoDir
ECHO He указан каталог для копирования!
PAUSE
:End
