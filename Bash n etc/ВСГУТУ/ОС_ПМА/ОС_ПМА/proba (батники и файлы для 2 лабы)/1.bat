@echo off
IF -%1==- GOTO NoParam
IF -%2==- GOTO NoParam
FIND "%1.%2" protokol.txt | SORT /+26 > %1%2.txt
GOTO End
:NoParam
ECHO He заданы необходимые параметры командной строки!
PAUSE
:End
