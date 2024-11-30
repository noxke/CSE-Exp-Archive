@echo off

echo build %1
ml /c /coff /Cp %1.asm  && link /subsystem:windows /section:.text,rwe %1.obj
del %1.obj
