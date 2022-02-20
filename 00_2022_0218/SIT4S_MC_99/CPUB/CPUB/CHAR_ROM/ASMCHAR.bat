
del *.abs
del *.ice
del *.lis
del *.obj

DEL *.TAG
asmsh CHAR_ROM.src >CHAR_ROM.tag /LIST -DEBUG
DIR *.TAG
pause
lnk /SUBCOMMAND= CHARlnk.cmd
CNVS CHAR_ROM.abs CHAR_ROM.mot

