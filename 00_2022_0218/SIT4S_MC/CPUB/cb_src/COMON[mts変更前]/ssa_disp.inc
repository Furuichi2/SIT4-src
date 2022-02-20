;	*******************************************
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	***					***
;	*******************************************
;	debug-monitor
;	***********************************
;	***	表示機能		***
;	***********************************
	.EXPORT	_MONI_CNT_NOW_INFO_DISP		;17
	.EXPORT	_MONI_CNT_HIST_INFO_DISP	;18
;	***********************************
;	***	現在値モニタ		***
;	***********************************
;	***********************************
;	***	NO.17			***
;	***********************************

;	Inout R2 S02 (頁)
;	Input R3 S03 (詳細)
;
_MONI_CNT_NOW_INFO_DISP
	SUB_START
;;;;;;;;;;;;;;;;;;;	MOV	R3,R0				;
;;;;;;;;;;;;;;;;;;;	CMP/EQ	#00,R0				;
;;;;;;;;;;;;;;;;;;;	BF	MONI_CNT_NOW_INFO_DSP_010	;
;;;;;;;;;;;;;;;;;;;	FAR_JSR	#_MONI_CNT_NOW_INFO_DSP1,R0	;17-00
;;;;;;;;;;;;;;;;;;;	M_BRA	MONI_CNT_NOW_INFO_DSP_EXT	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;MONI_CNT_NOW_INFO_DSP_010			;
;;;;;;;;;;;;;;;;;;;	CMP/EQ	#01,R0				;
;;;;;;;;;;;;;;;;;;;	BF	MONI_CNT_NOW_INFO_DSP_020	
;;;;;;;;;;;;;;;;;;;	FAR_JSR	#_MONI_CNT_NOW_INFO_DSP2,R0	;17-1
;;;;;;;;;;;;;;;;;;;	M_BRA	MONI_CNT_NOW_INFO_DSP_EXT	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;MONI_CNT_NOW_INFO_DSP_020			;
;;;;;;;;;;;;;;;;;;;	CMP/EQ	#02,R0				;
;;;;;;;;;;;;;;;;;;;	BF	MONI_CNT_NOW_INFO_DSP_030	
;;;;;;;;;;;;;;;;;;;	FAR_JSR	#_MONI_CNT_NOW_INFO_DSP3,R0	;17-2
;;;;;;;;;;;;;;;;;;;	M_BRA	MONI_CNT_NOW_INFO_DSP_EXT	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;MONI_CNT_NOW_INFO_DSP_030	
;;;;;;;;;;;;;;;;;;;	FAR_JSR	#_MONI_CNT_NOW_INFO_DSP4,R0	;17-3
;;;;;;;;;;;;;;;;;;;MONI_CNT_NOW_INFO_DSP_EXT			;

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	現在値モニタ		***
;	***	17-0-0-1/2		***
;	***				***
;	***********************************
;	====== 17-0 =====
_MONI_CNT_NOW_INFO_DSP1
	SUB_START
;;;;;;;;;;;;;;;;;;;;;	DATA_STD_SHN_MOV	SRC=_PV_POWER_ON_CNT,L1=W,DST=_PVP_MONALM_P01,L2=W
;;;;;;;;;;;;;;;;;;;;;	DATA_STD_SHN_MOV	SRC=_PV_CB_STS_POINT,L1=W,DST=_PVP_MONALM_P02,L2=W
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;	=========== A01~A08(同じことを確認) =======
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP1_FRQ		,W	,_PVP_MONALM_A01,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP2_FRQ		,W	,_PVP_MONALM_A02,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP3_FRQ		,W	,_PVP_MONALM_A03,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP4_FRQ		,W	,_PVP_MONALM_A04,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP1_FRQ		,W	,_PVP_MONALM_A05,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP2_FRQ		,W	,_PVP_MONALM_A06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP3_FRQ		,W	,_PVP_MONALM_A07,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP4_FRQ		,W	,_PVP_MONALM_A08,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP1_TIM		,W	,_PVP_MONALM_B01,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP2_TIM		,W	,_PVP_MONALM_B02,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP3_TIM		,W	,_PVP_MONALM_B03,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP4_TIM		,W	,_PVP_MONALM_B04,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP1_TIM		,W	,_PVP_MONALM_B05,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP2_TIM		,W	,_PVP_MONALM_B06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP3_TIM		,W	,_PVP_MONALM_B07,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP4_TIM		,W	,_PVP_MONALM_B08,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP1_PV_PLS	,L	,_PVP_MONALM_C01,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP2_PV_PLS	,L	,_PVP_MONALM_C02,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP3_PV_PLS	,L	,_PVP_MONALM_C03,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP4_PV_PLS	,L	,_PVP_MONALM_C04,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP1_PV_PLS	,L	,_PVP_MONALM_C05,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP2_PV_PLS	,L	,_PVP_MONALM_C06,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP3_PV_PLS	,L	,_PVP_MONALM_C07,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP4_PV_PLS	,L	,_PVP_MONALM_C08,L,R1,R2,R3,H'3FFFFFF;


	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	現在値モニタ		***
;	***	17-0-1-1/2		***
;	***				***
;	***********************************
;	====== 17-1 =====
_MONI_CNT_NOW_INFO_DSP2
	SUB_START
;;;;;;;;;;;;;;;;;;;;	=========== A01~A08 =======
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP1_SV_PLS+0	,W	,_PVP_MONALM_A01,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP1_SV_PLS+2	,W	,_PVP_MONALM_A02,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP4_SV_PLS+0	,W	,_PVP_MONALM_A03,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_STEP4_SV_PLS+2	,W	,_PVP_MONALM_A04,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP1_SV_PLS+0	,W	,_PVP_MONALM_A05,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP1_SV_PLS+2	,W	,_PVP_MONALM_A06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP4_SV_PLS+0	,W	,_PVP_MONALM_A07,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_STEP4_SV_PLS+2	,W	,_PVP_MONALM_A08,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_PVP_A_LOT_CNT3		,W	,_PVP_MONALM_B01,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_PVP_B_LOT_CNT3		,W	,_PVP_MONALM_B02,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_FLAG	,W	,_PVP_MONALM_B03,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_CHK_CNT1	,W	,_PVP_MONALM_B04,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_CHK_CNT2	,W	,_PVP_MONALM_B05,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_DAT1	,L	,_PVP_MONALM_B06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_SH2_CNT_REST_PLS	,L	,_PVP_MONALM_B07,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_SH4_CNT_REST_PLS	,L	,_PVP_MONALM_B08,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;	===========================<<<偏差>>>===========
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_HENSA_OVER_MOVE_CNT		,L	,_PVP_MONALM_C01,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_POSLSI_OUTPUT_TOTAL_PLS+4	,L	,_PVP_MONALM_C02,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_POSLSI_HENSA_LATCH+4		,L	,_PVP_MONALM_C03,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_SV_CONST_SUB_PV		,L	,_PVP_MONALM_C04,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_SV_REAL_SUB_PV			,L	,_PVP_MONALM_C05,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_SV_REAL_PLS			,L	,_PVP_MONALM_C06,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_LINK_SV_OBJ_ABSPLS+4		,L	,_PVP_MONALM_C07,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_LINK_PV_ABSPLS+4	,L	,_PVP_MONALM_C08,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
	SUB_END
	M_RTS


;	***********************************
;	***				***
;	***	現在値モニタ		***
;	***	17-0-2-1/2		***
;	***				***
;	***********************************
;	====== 17-2 =====
_MONI_CNT_NOW_INFO_DSP3
	SUB_START
;;;;;;;;;;;;;;;;;;;;	=========== A01~A08 =======
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHi_NOW_STEP		,W	,_PVP_MONALM_A01,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_eSHy_NOW_STEP		,W	,_PVP_MONALM_A02,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_INT_POS_CTL_STEP	,W	,_PVP_MONALM_A03,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_SV_POS_CTL_STEP	,W	,_PVP_MONALM_A04,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_PLSOUT_STOP_CNT	,W	,_PVP_MONALM_A05,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_CNT1	,W	,_PVP_MONALM_A06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	
;;;;;;;;;;;;;;;;;;;	XOR	R0,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A07	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A08	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;	======================================
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_PVP_A_LOT_CNT3		,W	,_PVP_MONALM_B01,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_PVP_B_LOT_CNT3		,W	,_PVP_MONALM_B02,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_CHK_CNT1	,W	,_PVP_MONALM_B03,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_CHK_CNT2	,W	,_PVP_MONALM_B04,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_DAT1	,L	,_PVP_MONALM_B05,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_DAT2	,L	,_PVP_MONALM_B06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_SH2_CNT_REST_PLS	,L	,_PVP_MONALM_B07,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_SH4_CNT_REST_PLS	,L	,_PVP_MONALM_B08,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP1_REST_P	,L	,_PVP_MONALM_C01,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP2_REST_P	,L	,_PVP_MONALM_C02,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP3_REST_P	,L	,_PVP_MONALM_C03,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHi_STEP4_REST_P	,L	,_PVP_MONALM_C04,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP1_REST_P	,L	,_PVP_MONALM_C05,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP2_REST_P	,L	,_PVP_MONALM_C06,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP3_REST_P	,L	,_PVP_MONALM_C07,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM_ALMT	_eSHy_STEP4_REST_P	,L	,_PVP_MONALM_C08,L,R1,R2,R3,H'3FFFFFF;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;

	SUB_END
	M_RTS

;	***********************************
;	***				***
;	***	現在値モニタ		***
;	***	17-0-3-1/2		***
;	***				***
;	***********************************
_SH4_4B		.EQU	0
_SH2_4B		.EQU	4
_SH4_8B		.EQU	0
_SH2_8B		.EQU	8


;	====== 17-3 =====
_MONI_CNT_NOW_INFO_DSP4
	SUB_START

;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_REST_SPD_HOSEI_FLG,W,_PVP_MONALM_A01,W,R1,R2,R3	;
;;;;;;;;;;;;;;;;;;;	XOR	R0,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A02	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A03	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A04	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;	-------------------------- HENSAﾃﾞｰﾀ---------
;;;;;;;;;;;;;;;;;;;	MOV.L	#_MONI_CPUAB_PLSDELT,R1
;;;;;;;;;;;;;;;;;;;	MOV.L	@(0,R1),R5							;
;;;;;;;;;;;;;;;;;;;	MOV.L	@(4,R1),R6							;
;;;;;;;;;;;;;;;;;;;	MOV	R5,R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A05	,L1=W,DT_REG=R0,WKREG1=R1	;H
;;;;;;;;;;;;;;;;;;;	SHLR16	R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A06	,L1=W,DT_REG=R0,WKREG1=R1	;L
;;;;;;;;;;;;;;;;;;;	MOV	R6,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A07	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;	SHLR16	R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_A08	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_LSIFREQ+_SH4_4B,R4					;CPUA
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4+,R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_B01	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_LSIFREQ+_SH2_4B,R4					;CPU
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4+,R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_B02	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_CAL_REST+_SH4_4B,R4					;
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4,R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_B03	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_CAL_REST+_SH2_4B,R4					;
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4,R0								;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_B04	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	XOR	R0,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_B05	,L1=W,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_CHK_CNT2,W,_PVP_MONALM_B06,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_DAT1,L,_PVP_MONALM_B07,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;	MEM_MOV_TO_MEM	_CNT_SYNC_HOS_DAT2,L,_PVP_MONALM_B08,W,R1,R2,R3;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_RL_SPD+_SH4_4B,R4	;OK
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4+,R0				;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C01	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_RL_SPD+_SH2_4B,R4	;OK
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4+,R0				;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C02	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_REST_PLS+_SH4_4B,R4	;
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4+,R0				;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C03	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_REST_PLS+_SH2_4B,R4	;
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4+,R0				;
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C04	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_RL_ABSPLS+_SH4_8B+4,R4		;20060919
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4,R0							;
;;;;;;;;;;;;;;;;;;;	MOV.L	#H'3FFFFFF,R4							;
;;;;;;;;;;;;;;;;;;;	AND	R4,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C05	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_RL_ABSPLS+_SH2_8B+4,R4		;20060919
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4,R0							;
;;;;;;;;;;;;;;;;;;;	MOV.L	#H'3FFFFFF,R4							;
;;;;;;;;;;;;;;;;;;;	AND	R4,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C06	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_PV_ABSPLS+_SH4_8B+4,R4		;
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4,R0							;
;;;;;;;;;;;;;;;;;;;	MOV.L	#H'3FFFFFF,R4							;
;;;;;;;;;;;;;;;;;;;	AND	R4,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C07	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;	MOV.L	#_SH_POSCTL_PV_ABSPLS+_SH2_8B+4,R4		;
;;;;;;;;;;;;;;;;;;;	MOV.L	@R4,R0							;
;;;;;;;;;;;;;;;;;;;	MOV.L	#H'3FFFFFF,R4							;
;;;;;;;;;;;;;;;;;;;	AND	R4,R0
;;;;;;;;;;;;;;;;;;;	REG_MOV_TO_MEM	DST_ADR=_PVP_MONALM_C08	,L1=L,DT_REG=R0,WKREG1=R1	;
;;;;;;;;;;;;;;;;;;;

	SUB_END
	M_RTS



;	=========== C01~C08 =======



;	***********************************
;	***	履歴モニタ		***
;	***				***
;	***	18-(0~199)-0/1-1/2	***
;	***				***
;	***********************************
;	R2 頁
;	R3 詳細 0:自分　1:相手
_MONI_CNT_HIST_INFO_DISP
	SUB_START
	SUB_END
	M_RTS

