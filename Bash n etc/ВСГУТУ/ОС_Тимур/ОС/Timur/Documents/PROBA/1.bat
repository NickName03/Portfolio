@echo off
rem Проверка наличия параметров командной строки
IF -%1==- GOTO NoParam
IF -%2==- GOTO NoParam
rem Выделение нужных строк из файла protokol.txt
FIND "%1.%2" protokol.txt | SORT /+26 > %1%2.txt
GOTO End
:NoParam
ECHO He заданы необходимые параметры командной строки!
PAUSE
:End
