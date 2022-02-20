-------- PROJECT GENERATOR --------
PROJECT NAME :	cpua
PROJECT DIRECTORY :	d:\sits_he1\cpua\cpua\cpua
CPU SERIES :	SH-4
CPU TYPE :	SH7750
TOOLCHAIN NAME :	Hitachi SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	5.1.0
GENERATION FILES :
    d:\sits_he1\cpua\cpua\cpua\initsct.c
        Initialize of RAM Data
    d:\sits_he1\cpua\cpua\cpua\dbsct.src
        Setting of B,R Section
    d:\sits_he1\cpua\cpua\cpua\sbrk.c
        Program of sbrk
    d:\sits_he1\cpua\cpua\cpua\iodefine.h
        Definition of I/O Register
    d:\sits_he1\cpua\cpua\cpua\intprg.src
        Interrupt Program
    d:\sits_he1\cpua\cpua\cpua\vecttbl.src
        Initialize of Vector Table
    d:\sits_he1\cpua\cpua\cpua\vect.inc
        Definition of Vector
    d:\sits_he1\cpua\cpua\cpua\env.inc
        Define Interruput Event Register
    d:\sits_he1\cpua\cpua\cpua\vhandler.src
        Reset/Interrupt Handler
    d:\sits_he1\cpua\cpua\cpua\resetprg.src
        Reset Program
    d:\sits_he1\cpua\cpua\cpua\hwsetup.src
        Hardware Setup file
    d:\sits_he1\cpua\cpua\cpua\cpua.c
        Main Program
    d:\sits_he1\cpua\cpua\cpua\sbrk.h
        Header file of sbrk file
    d:\sits_he1\cpua\cpua\cpua\stacksct.src
        Setting of Stack area
LIBRARY NAME :	sh4nbmzz.lib
START ADDRESS OF SECTION :
    H'000000000	RSTHandler
    H'000000800	INTHandler,VECTTBL,INTTBL,IntPRG
    H'000001000	ResetPRG
    H'000002000	P,C,D
    H'070000000	B,R
    H'073FFFBF0	Stack

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start H'2000.
* RAM start H'70000000.
