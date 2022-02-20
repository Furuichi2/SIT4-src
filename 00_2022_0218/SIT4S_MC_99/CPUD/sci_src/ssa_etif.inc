;	*************************************************************************************
;	*****										*****
;	*****	�d�s�P��ʒʐM�C���^�[�t�F�[�X						*****
;	*****										*****
;	*****										*****
;	*************************************************************************************

;//2012/10/02	.SECTION	P,CODE,ALIGN=4
	.SECTION	PvupsciROM,CODE,ALIGN=4

	.IMPORT		_ET_LDCMND_AREA		;LdCmnd set area
	.IMPORT		_ET_LDCMND_REQ		;LdCmnd Request Flag
	.IMPORT		_ET_LDCMND_RES		;LdCmnd Response Flag
	.IMPORT		_MEM_ARI		;
	.IMPORT		_ET1_INITAL_FLG		;

_ET_DP		.EQU	H'00			; DP���α��ڽ
_ET_SP		.EQU	H'01			; SP���α��ڽ
_ET_TRAN	.EQU	H'02			; �g�����U�N�V�������α��ڽ
_ET_STS		.EQU	H'04			; �����ð����α��ڽ
_ET_IDL		.EQU	H'06			; �ڑ�ID���α��ڽ
_ET_BYTENL	.EQU	H'12			; �ް����޲Đ�(L)���α��ڽ
_ET_ADRL	.EQU	H'15			; 
_ET_ADRM	.EQU	H'16			; 
_ET_ADRH	.EQU	H'17			; 



	.EXPORT		_ET1_LDCMD_IF;
_ET1_LDCMD_IF:
	SUB_START

;--------------------------------------------------------------------------------------------------
	MOV.L	#_ET1_INITAL_FLG,R1		; V05h(INS)
	MOV.W	@R1,R0				;
	TST	#BIT6,R0			;
	TST_BIT_ON _ET1_LDCMD_IF_STR00		;
	M_BRA	_ET1_LDCMDIF_EXT		;
;--------------------------------------------------------------------------------------------------

_ET1_LDCMD_IF_STR00:
;;;;;	MOV.L	#_MEM_ARI,R1			;
;;;;;	MOV.B	@R1,R0				;
;;;;	EXTU.B	R0,R0				;
	MOV.L	#_OPTION_ET1_ARI,R1		;[MC]005A CPUB-->CPUD
	MOV.W	@R1,R0				;[MC]

	MOV.W	#H'00A5,R1			;
	CMP/EQ	R1,R0				;
	BT	_ET1_LDCMD_IF_START		;�ڑ�
	M_BRA	_ET1_LDCMDIF_EXT		;���ڑ�

_ET1_LDCMD_IF_START:
	MOV.L	#_sci0_wkram+ET1_LDCMND_REQ,R1
	MOV.W	@R1,R0
	CMP/EQ	#1,R0				; ���Ɏ�M�ςݗL��H
	BF	_ET1_LDCMDIF_000		; ������
	M_BRA	_ET1_LDCMDIF_300		; �͂�

;	==============================================================================

_ET1_LDCMDIF_000:
	MOV.L	#_ET_LDCMND_REQ+0,R1
;//SIT-MC	MOV.B	@R1,R0
;////////	CMP/EQ	#H'01,R0			; LdCmnd Request Flag�L��H
	MOV.W	@R1,R0
	SWAP.B	R0,R0
	CMP/EQ	#H'01,R0			; LdCmnd Request Flag�L��H
	BT	_ET1_LDCMDIF_100
	M_BRA	_ET1_LDCMDIF_EXT

_ET1_LDCMDIF_100:
;	----- SIT4-MC --------------------------
	MOV.L	#(512/2),R4			; SIT4-MC�͒���ET1�Ɛڑ��ł͖���CPUB�Ɛڑ��ɂȂ������߁B
	MOV.L	#_ET_LDCMND_AREA,R8		; CPUB�Ƃ�ܰ��ܸ�������o���Ȃ������U��M�ް���ܰ��ցB
	MOV.L	#_ET_LDCMND_WORK,R9
	NOP
_ET1_LDCMDIF_105:
	TST	R4,R4
	BT	_ET1_LDCMDIF_106
	MOV.W	@R8,R0
	MOV.W	R0,@R9
	ADD	#2,R8
	ADD	#2,R9
	ADD	#-1,R4
	M_BRA	_ET1_LDCMDIF_105
_ET1_LDCMDIF_106:
;	----------------------------------------

	MOV.L	#_sci0_rxd_buf+_STR_CODE,R8
	XOR	R9,R9				; BCC�쐬�p
	MOV.W	#H'0FF,R10

;	--- ���ڽ�ϊ� ܰ�ޱ��ڽ���޲ı��ڽ ---
;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_ADRL,R3
;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_ADRM,R4
;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_ADRH,R5
	MOV.L	#_ET_LDCMND_WORK+_ET_ADRL,R3
	MOV.L	#_ET_LDCMND_WORK+_ET_ADRM,R4
	MOV.L	#_ET_LDCMND_WORK+_ET_ADRH,R5
	MOV.B	@R3,R0
	AND	R10,R0				; ADR L
	MOV.B	@R4,R1
	AND	R10,R1				; ADR M
	SHLL8	R1
	MOV.B	@R5,R2
	AND	R10,R2				; ADR H
	SHLL16	R2
	OR	R1,R0
	OR	R2,R0
	SHLL	R0				; ܰ�ޱ��ڽ���޲ı��ڽ
	MOV.B	R0,@R3				; ADR L
	MOV	R0,R1
	SHLR8	R1
	MOV.B	R1,@R4				; ADR M
	MOV	R0,R2
	SHLR16	R2
	MOV.B	R2,@R5				; ADR H

;	--- �`��ͯ�ޕ��]�� ---
	MOV.B	#H'5A,R0
	MOV.B	R0,@R8				; ���ĺ���
	ADD	#1,R8

;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_BYTENL,R7
	MOV.L	#_ET_LDCMND_WORK+_ET_BYTENL,R7
	MOV.B	@R7+,R0
	AND	R10,R0
	MOV.B	@R7+,R1
	SHLL8	R1
	OR	R1,R0				; �f�[�^���o�C�g��

;--------------------------------------------------------------------------------------------------
;;;���߁@2007-12-06 MOV	#512-3-16-1,R11			; 512-3-16-1=492���o�C�g���ő�l	V05h(INS)
	MOV.W	#(512-3-16-1),R11			; 512-3-16-1=492���o�C�g���ő�l	V05h(INS)
	CMP/HI	R11,R0				; 492���傫���H
	BF	_ET1_LDCMDIF_110		; ������
	MOV	R11,R0				; ���~�b�g
_ET1_LDCMDIF_110:
;--------------------------------------------------------------------------------------------------

	MOV	R0,R11				; �f�[�^���o�C�g��KEEP
	MOV.W	#16,R2
	ADD	R2,R0				; �{�R�}���h�w�b�_�o�C�g��
	MOV.W	#1,R2
	ADD	R2,R0				; �{�a�b�b�o�C�g��

	MOV	R0,R1
	AND	R10,R0
	MOV.B	R0,@R8				; �f�[�^���J�E���^(L)
	ADD	#1,R8
	ADD	R0,R9				; +BCC

	MOV	R1,R0
	SHLR8	R0
	AND	R10,R0
	MOV.B	R0,@R8				; �f�[�^���J�E���^(H)
	ADD	#1,R8
	ADD	R0,R9				; +BCC

;	--- �����ͯ�ޕ��]�� ---
;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_STS,R7
	MOV.L	#_ET_LDCMND_WORK+_ET_STS,R7
	MOV.W	#16,R4				; �R�}���h�w�b�_�o�C�g��
_ET1_LDCMDIF_120:
	TST	R4,R4
	BT	_ET1_LDCMDIF_140
	MOV.B	@R7+,R0
	AND	R10,R0
	MOV.B	R0,@R8
	ADD	#1,R8
	ADD	R0,R9				; +BCC
	ADD	#-1,R4
	M_BRA	_ET1_LDCMDIF_120

;	--- �ް����]�� ---
_ET1_LDCMDIF_140:
	MOV	R11,R4				; �f�[�^���o�C�g��
_ET1_LDCMDIF_160:
	TST	R4,R4
	BT	_ET1_LDCMDIF_180
	MOV.B	@R7+,R0
	AND	R10,R0
	MOV.B	R0,@R8
	ADD	#1,R8
	ADD	R0,R9				; +BCC
	ADD	#-1,R4
	M_BRA	_ET1_LDCMDIF_160

;	--- BCC���]�� ---
_ET1_LDCMDIF_180:
	NEG	R9,R9
	MOV.B	R9,@R8				; BCC

	MOV.L	#_ET_LDCMND_REQ+0,R1
;//SIT4-MC	MOV.B	#0,R0
;/////////	MOV.B	R0,@R1				; LdCmnd Request Flag�N���A
	MOV.W	#0,R0
	MOV.W	R0,@R1				; LdCmnd Request Flag�N���A

	MOV.L	#_sci0_wkram+ET1_LDCMND_REQ,R1
	MOV.W	#1,R0
	MOV.W	R0,@R1				; ����LdCmnd Request Flag�n�m

	MOV.L	#_sci0_wkram+RX_END,R1
	MOV.W	#1,R0
	MOV.W	R0,@R1				; �����I�Ɏ�M����Flag�n�m

	M_BRA	_ET1_LDCMDIF_EXT

;	==============================================================================

_ET1_LDCMDIF_300:
	MOV.L	#_sci0_wkram+ET1_LDCMND_RES,R1
	MOV.W	@R1,R0
	CMP/EQ	#1,R0				; ���X�|���X�L��H
	BT	_ET1_LDCMDIF_320		; �͂�
	M_BRA	_ET1_LDCMDIF_EXT		; ������

_ET1_LDCMDIF_320:
	MOV.W	#0,R0
	MOV.L	#_sci0_wkram+ET1_LDCMND_REQ,R1
	MOV.W	R0,@R1				; ����LdCmnd Request Flag�N���A
	MOV.L	#_sci0_wkram+ET1_LDCMND_RES,R1
	MOV.W	R0,@R1				; ����LdCmnd Response Flag�N���A

	MOV.W	#H'0FF,R10

;	--- ���ڽ�ϊ� �޲ı��ڽ��ܰ�ޱ��ڽ ---
	MOV.L	#_sci0_txd_buf+_ADRL,R3
	MOV.L	#_sci0_txd_buf+_ADRM,R4
	MOV.L	#_sci0_txd_buf+_ADRH,R5
	MOV.B	@R3,R0
	AND	R10,R0				; ADR L
	MOV.B	@R4,R1
	AND	R10,R1				; ADR M
	SHLL8	R1
	MOV.B	@R5,R2
	AND	R10,R2				; ADR H
	SHLL16	R2
	OR	R1,R0
	OR	R2,R0
	SHLR	R0				; �޲ı��ڽ��ܰ�ޱ��ڽ
	MOV.B	R0,@R3				; ADR L
	MOV	R0,R1
	SHLR8	R1
	MOV.B	R1,@R4				; ADR M
	MOV	R0,R2
	SHLR16	R2
	MOV.B	R2,@R5				; ADR H

;	--- ���ĺ�ͯ�ޕ��]�� ---
;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_DP,R8
	MOV.L	#_ET_LDCMND_WORK+_ET_DP,R8
	MOV.B	#H'80,R0
	MOV.B	R0,@R8				; DP
	ADD	#1,R8

	MOV.B	#H'FB,R0
	MOV.B	R0,@R8				; SP
	ADD	#1,R8

	MOV.B	#H'C0,R0
	MOV.B	R0,@R8				; ��ݻ޸���
	ADD	#1,R8

	MOV.B	#H'0,R0
	MOV.B	R0,@R8				; �`���ð��
	ADD	#1,R8

;	--- �����ͯ�ޕ��]�� ---
	MOV.L	#_sci0_txd_buf+_SYORI_STS,R7
	MOV.W	#16,R4				; �R�}���h�w�b�_�o�C�g��
_ET1_LDCMDIF_340:
	TST	R4,R4
	BT	_ET1_LDCMDIF_360
	MOV.B	@R7+,R0
	MOV.B	R0,@R8
	ADD	#1,R8
	ADD	#-1,R4
	M_BRA	_ET1_LDCMDIF_340

;	--- �ް����]�� ---
_ET1_LDCMDIF_360:
	MOV.L	#_sci0_txd_buf+_BYTENL,R2
	MOV.B	@R2+,R0
	AND	R10,R0
	MOV.B	@R2+,R1
	SHLL8	R1
	OR	R1,R0				; �f�[�^���o�C�g��
	MOV	R0,R4
_ET1_LDCMDIF_380:
	TST	R4,R4
	BT	_ET1_LDCMDIF_400
	MOV.B	@R7+,R0
	MOV.B	R0,@R8
	ADD	#1,R8
	ADD	#-1,R4
	M_BRA	_ET1_LDCMDIF_380

;	--- �ڑ�ID������ ---
_ET1_LDCMDIF_400:
;//SIT4-MC	MOV.L	#_ET_LDCMND_AREA+_ET_IDL,R8
	MOV.L	#_ET_LDCMND_WORK+_ET_IDL,R8
	MOV.B	#H'A5,R0
	MOV.B	R0,@R8

;	----- SIT4-MC --------------------------
	MOV.L	#(512/2),R4			; SIT4-MC�͒���ET1�Ɛڑ��ł͖���CPUB�Ɛڑ��ɂȂ������߁B
	MOV.L	#_ET_LDCMND_WORK,R8
	MOV.L	#_ET_LDCMND_AREA,R9
	NOP
_ET1_LDCMDIF_420:
	TST	R4,R4
	BT	_ET1_LDCMDIF_440
	MOV.W	@R8,R0
	MOV.W	R0,@R9
	ADD	#2,R8
	ADD	#2,R9
	ADD	#-1,R4
	M_BRA	_ET1_LDCMDIF_420
_ET1_LDCMDIF_440:
;	----------------------------------------

	MOV.L	#_ET_LDCMND_RES+0,R1
;//SIT4-MC	MOV.B	#1,R0
;/////////	MOV.B	R0,@R1				; LdCmnd Response Flag�Z�b�g
	MOV.W	#1,R0
	SWAP.B	R0,R0
	MOV.W	R0,@R1				; LdCmnd Response Flag�Z�b�g

	M_BRA	_ET1_LDCMDIF_EXT

_ET1_LDCMDIF_EXT:
	SUB_END
	M_RTS


;**************************************************
;***						***
;***	�d���������AIP�A�h���X��ET1�֋�����	***	V05j
;***						***
;**************************************************
	.IMPORT		_ET1_VER
	.IMPORT		_SV_IPS_ADR0
	.IMPORT		_ET1_IPS_ADR0
	.IMPORT		_ET1_IPS_ENT
	.IMPORT		_ET1_IPM_ADR0
	.IMPORT		_PV0_IPM_ADR0
	.EXPORT		_ASM_ET1_IP_BACK
_ASM_ET1_IP_BACK:
	SUB_START
	PUSH_ALL

;;//////	MOV.L	#_ET1_VER,R1		;
;;//////	MOV.W	@R1,R0				;
;;//////	MOV.W	#H'4554,R2			; "ET"
;;//////	CMP/EQ	R2,R0				; �o�[�W�����u�d�s�v�������H
;;//////	BT	_ASM_ET1IP_BK_000		; �͂�
;;//////	M_BRA	_ASM_ET1IP_BK_EXT		; ������

	MOV.L	#_MEM_ARI,R1			;
	MOV.B	@R1,R0				;
	EXTU.B	R0,R0				;
	MOV.W	#H'00A5,R1			;
	CMP/EQ	R1,R0				;
	BT	_ASM_ET1IP_BK_000		; �͂�
	M_BRA	_ASM_ET1IP_BK_EXT		; ������

_ASM_ET1IP_BK_000:
	MOV.L	#_SV_IPS_ADR0,R1
	MOV.L	#_ET1_IPS_ADR0,R2
	MOV.W	#4*3,R4					; IP���ڽ�A���ȯ�Ͻ��A��̫�Ĺްĳ��
_ASM_ET1IP_BK_100:
	TST	R4,R4
	BT	_ASM_ET1IP_BK_150
	MOV.W	@R1+,R0
	MOV.W	R0,@R2
	ADD	#2,R2
	ADD	#-1,R4
	M_BRA	_ASM_ET1IP_BK_100

_ASM_ET1IP_BK_150:
	MOV.W	#H'5AA5,R0
	MOV.L	#_ET1_IPS_ENT,R1			;IP���ڽ�m��
	MOV.W	R0,@R1

	MOV.L	#_ET1_IPM_ADR0,R1
	MOV.L	#_PV0_IPM_ADR0,R2
	MOV.W	#4*1,R4					; ����pIP���ڽ
_ASM_ET1IP_BK_200:
	TST	R4,R4
	BT	_ASM_ET1IP_BK_250
	MOV.W	@R1+,R0
	MOV.W	R0,@R2
	ADD	#2,R2
	ADD	#-1,R4
	M_BRA	_ASM_ET1IP_BK_200

_ASM_ET1IP_BK_250:

_ASM_ET1IP_BK_EXT:
	POP_ALL
	SUB_END
	M_RTS

