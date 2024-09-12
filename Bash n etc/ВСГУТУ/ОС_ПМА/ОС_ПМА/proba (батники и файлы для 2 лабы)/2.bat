@echo off
rem Проверка наличия параметра командной строки
IF -%1==- GOTO NoDir
rem Копирование нужных файлов
FOR %%f IN (*.txt) DO IF NOT -%%f==-%2 COPY %%f %1
GOTO End
:NoDir
ECHO He указан каталог для копирования!
PAUSE
:End
