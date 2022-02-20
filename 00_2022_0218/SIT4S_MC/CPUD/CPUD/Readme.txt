-------- PROJECT GENERATOR --------
PROJECT NAME :	CPUB
PROJECT DIRECTORY :	D:\SIT4S_MC\CPUB\CPUB
CPU SERIES :	SH3-DSP
CPU TYPE :	SH7727
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.4.1.0
GENERATION FILES :
    D:\SIT4S_MC\CPUB\CPUB\dbsct.c
        Setting of B,R Section
    D:\SIT4S_MC\CPUB\CPUB\typedefine.h
        Aliases of Integer Type
    D:\SIT4S_MC\CPUB\CPUB\sbrk.c
        Program of sbrk
    D:\SIT4S_MC\CPUB\CPUB\iodefine.h
        Definition of I/O Register
    D:\SIT4S_MC\CPUB\CPUB\intprg.src
        Interrupt Program
    D:\SIT4S_MC\CPUB\CPUB\vecttbl.src
        Initialize of Vector Table
    D:\SIT4S_MC\CPUB\CPUB\vect.inc
        Definition of Vector
    D:\SIT4S_MC\CPUB\CPUB\env.inc
        Define Interruput Event Register
    D:\SIT4S_MC\CPUB\CPUB\vhandler.src
        Reset/Interrupt Handler
    D:\SIT4S_MC\CPUB\CPUB\resetprg.c
        Reset Program
    D:\SIT4S_MC\CPUB\CPUB\hwsetup.src
        Hardware Setup file
    D:\SIT4S_MC\CPUB\CPUB\CPUB.c
        Main Program
    D:\SIT4S_MC\CPUB\CPUB\sbrk.h
        Header file of sbrk file
    D:\SIT4S_MC\CPUB\CPUB\stacksct.h
        Setting of Stack area
LIBRARY NAME :	sh3dspnb.lib
START ADDRESS OF SECTION :
 H'000000800	INTHandler,VECTTBL,INTTBL,IntPRG
 H'000001000	PResetPRG
 H'000002000	P,C,C$BSEC,C$DSEC,D
 H'005007000	B,R
 H'005018BF0	S
 H'0A0000000	RSTHandler

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start H'2000.
* RAM start H'05007000.

DATE & TIME : 2013/11/22 14:36:24
