;	***************************************************
;	***						***
;	***						***
;	***						***
;	***	�s���O�ɉ����E��������			***
;	***	�s����ɉ����E��������			***
;	***	�e�s���ł̎w��				***
;	***	2016-04-18				***
;	***						***
;	***						***
;	***						***
;	***************************************************
	.IMPORT		_PAR_ACCDN_MATH		;5 2015-11-18 �������@�����D��[CE2]
;	*******************************************
;	***					***
;	***	�o�b�N�O�����h��CALL		***
;	***	�����쐬			***
;	***					***
;	*******************************************
_ACC_MATHED_SEL_MAIN
	SUB_START
	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACC_MATHED_SEL_MN_100		;

;	-----	�ᑬ�D��	-----
	FAR_JSR	#_ACCLW_DATA_MAIN,R0		;[1��]
	M_BRA	ACC_MATHED_SEL_MN_END		;


ACC_MATHED_SEL_MN_100				;
	CMP/EQ	#2,R0				;
	BF	ACC_MATHED_SEL_MN_END		;

;	-----	�e�i�w��	-----
	FAR_JSR	#_ACCST_DATA_MAIN,R0		;[2��]


ACC_MATHED_SEL_MN_END				;


	SUB_END
	M_RTS



;	***************************************************
;	***						***
;	***	�N����CALL(�^�]�tON,�^�C�}��,1�T�C�N��)	***
;	***						***
;	***************************************************
_API_ACC_MATHED_COM_DRV_START1
	SUB_START

	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACC_MATHED_COM_DRVST1_100	;

;	-----	�ᑬ�D��	-----
	FAR_JSR	#_API_ACCLW_DRV_START1,R0	;

	M_BRA	ACC_MATHED_COM_DRVST1_END	;


ACC_MATHED_COM_DRVST1_100			;
	CMP/EQ	#2,R0				;
	BF	ACC_MATHED_COM_DRVST1_END	;

;	-----	�e�i�w��	-----
	FAR_JSR	#_API_ACCST_DRV_START1,R0	;

ACC_MATHED_COM_DRVST1_END:	;

	SUB_END
	M_RTS





;	*******************************************
;	***					***
;	***	�ʒu���ߒ��f��CALL		***
;	***	�ʒu���ߒ�~�^�C�}��CALL	***
;	***	�ُ펞CALL			***
;	***					***
;	*******************************************
;//BIT0:�N��[API]
;//BIT6:[�����J�n]
;//BIT7:���Z����[��~�s���܂ŉ��Z�s�v�F�����ᑬ�ݒ肪�Ȃ�]:�\��
;//

_API_ACC_MATHED_COM_DRV_STOP
	SUB_START
;	(�����͔��f���Ȃ��Ă������ł��傤)

;	-----	�ᑬ�D��	-----
;	---	�t���O�N���A	---
	FAR_JSR	#_API_ACCLW_DRV_STOP,R0

;	-----	�e�i�w��	-----
;	---	�t���O�N���A	---
	FAR_JSR	#_API_ACCST_DRV_STOP,R0


	SUB_END
	M_RTS



;	*******************************************
;	***					***
;	***	1msec��CALL	���C��		***
;	***					***
;	*******************************************
;	[Input R2]
_ACC_MATHED_SEL_CTRL
	SUB_START

	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACC_MATHED_CTLSEL_100		;

;	-----	�ᑬ�D��	-----
	FAR_JSR	#_ACCLW_CTRL_CALC,R0		;2015-11-17 �����I��

	M_BRA	ACC_MATHED_CTLSEL_END		;


ACC_MATHED_CTLSEL_100				;
	CMP/EQ	#2,R0				;
	BF	ACC_MATHED_CTLSEL_END		;

;	-----	�e�i�w��	-----
	FAR_JSR	#_ACCST_CTRL_CALC,R0		;[2��]

ACC_MATHED_CTLSEL_END				;


	SUB_END
	M_RTS













;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	���W�X�^��R0�ȊO�j�󂵂Ȃ�����
;	R0=0/R0=1(�O����,�O����)-���x�`�F�b�N�P�s�v
_ACCSEL_CHGSPD_LIMIT_INFO_LOAD:
	SUB_START

	PUSH_REG1 R1

	MOV.L	#(_PAR_ACCDN_MATH-_CB_SYS_PARAM000+_W_PARAM_TOP),R1
	MOV.W	@R1,R0				;
	CMP/EQ	#1,R0				;
	BF	ACCCHGSPD_LMT_INF_LD_100	;

;	-----	�ᑬ�D��	-----
	XOR	R0,R0
	M_BRA	ACCCHGSPD_LMT_INF_LD_END	;


ACCCHGSPD_LMT_INF_LD_100:
	CMP/EQ	#2,R0				;
	BF	ACCCHGSPD_LMT_INF_LD_200

;	-----	�e�i�w��	-----
	FAR_JSR	#_ACCST_CHGSPD_LIMIT_INFO_LOAD,R0	;
	M_BRA	ACCCHGSPD_LMT_INF_LD_END		;

ACCCHGSPD_LMT_INF_LD_200				;
	XOR	R0,R0
ACCCHGSPD_LMT_INF_LD_END				;

	POP_REG1 R1

	SUB_END
	M_RTS
	