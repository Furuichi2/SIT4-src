

DEL *.TAG

ASM38 SEQ_ROM.ASM > SEQ_ROM.tag /list -debug

DIR *.TAG
pause

H8LNK	/DEBUG/SUBCOMMAND= seq_lnk.cmd

pause

H8ICEMB seq.abs

H8CNVS	seq.abs	seq.mot

