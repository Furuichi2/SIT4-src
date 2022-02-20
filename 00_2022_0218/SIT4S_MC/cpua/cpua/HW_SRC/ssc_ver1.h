//;	***********************************
//;	***								***
//;	***	SIT3/4ÇÃ ∞ƒﬁä÷åWø∞Ωêÿï™		***
//;	***								***
//;	***********************************
#define		TYPE_SIT3		0
#define		TYPE_SIT4		1
#define		SIT_TYPE_SEL		TYPE_SIT4
//;;#define		SIT_TYPE_SEL		TYPE_SIT3

//;	***********************************
//;	***								***
//;	***	C/BÇÃ ∞ƒﬁä÷åWø∞Ωêÿï™		***
//;	***								***
//;	***********************************
#define		CB_CPUA		0
#define		CB_CPUB		1
#define		CB_CPU_SEL		CB_CPUA
//;;#define		CB_CPU_SEL		CB_CPUB

#if 1
	#if (SIT_TYPE_SEL == TYPE_SIT3)

		#if (CB_CPU_SEL == CB_CPUA)

			#define	SIT_CPU_SEL	SIT3_CPUA

		#else

			#define	SIT_CPU_SEL	SIT3_CPUB

		#endif
	#else
		#if (CB_CPU_SEL == CB_CPUA)

			#define	SIT_CPU_SEL	SIT4_CPUA

		#else

			#define	SIT_CPU_SEL	SIT4_CPUB

		#endif
	#endif
#endif



