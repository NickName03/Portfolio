@echo off
rem Копирование файла
XCOPY %1 %2 /D /C > NUL
rem Проверка успешности копирования
IF ERRORLEVEL 0 GOTO Success
rem Запись в файл отчета информации об ошибке при копировании
ECHO Ошибка: %1 >> logcopy.log
GOTO End
:Success
rem Запись в файл отчета информации об успешном копировании
ECHO Успешно: %1 >> logcopy.log
:End
