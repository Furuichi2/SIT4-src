
/* �O���Q�ƕϐ���` -------------------------------------------------- */
/*==========================================================================*/
/*		�e�X�g�p�̉���`													*/
/*==========================================================================*/
//extern	UNs		OP_STATUS_DT;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H

/*==========================================================================*/
/*		�V���[�N�̈��`�iSit-S�j											*/
/*==========================================================================*/
extern	UNi		SVPV_LCD_FLG;					//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
extern	UNs		SV_DANSUU_SRV_BAK;				//�H���� �Z�[�u
//extern	UNs		SV_TAIKIKAKU_SRV_BAK;			//�ҋ@�p�̊i�[
//extern	UNl		SV_TAIKIPOS_SRV_BAK;			//�ҋ@�ʒu�̊i�[
#if (mot100_test == 1)
extern	UNs		SV_MOT_PAGE;				//
#endif

extern	UNl		SV_TAIKIPOS_SRV;            /* �ҋ@�ʒu */
extern	UNs		SV_KAITEN_SRV;              /* ��]���� */
extern	UNs		SV_DANSUU_SRV;              /* �i�� */
extern	UNs		SV_TAIKIKAKU_SRV;           /* �ҋ@�p */
extern	UNs		SV_TAIKSPD_SRV;             /* ����x */
extern	UNl		SV_DAIHAITO_SRV;            /* �_�C�n�C�g */
extern	UNs		SV_HOASEI_SRV;              /* �␳�f�[�^ */
extern	UNs		SV_TAIKTIM_SRV;             /* �ҋ@���� */
extern	UNs		SV_1DANDEG_SRV;             /* 1�i�ږڕW�p�x */
extern	UNs		SV_2DANDEG_SRV;             /* 2�i�ږڕW�p�x */
extern	UNs		SV_3DANDEG_SRV;             /* 3�i�ږڕW�p�x */
extern	UNs		SV_4DANDEG_SRV;             /* 4�i�ږڕW�p�x */
extern	UNs		SV_5DANDEG_SRV;             /* 5�i�ږڕW�p�x */
extern	UNs		SV_6DANDEG_SRV;             /* 6�i�ږڕW�p�x */
extern	UNs		SV_7DANDEG_SRV;             /* 7�i�ږڕW�p�x */
extern	UNs		SV_8DANDEG_SRV;             /* 8�i�ږڕW�p�x */
extern	UNs		SV_9DANDEG_SRV;             /* 9�i�ږڕW�p�x */
extern	UNs		SV_10DANDEG_SRV;            /* 10�i�ږڕW�p�x */
#if (mot100_test == 1)
extern	UNs		SV_11DANDEG_SRV;            /* 11�i�ږڕW�p�x */
extern	UNs		SV_12DANDEG_SRV;            /* 12�i�ږڕW�p�x */
extern	UNs		SV_13DANDEG_SRV;            /* 13�i�ږڕW�p�x */
extern	UNs		SV_14DANDEG_SRV;            /* 14�i�ږڕW�p�x */
extern	UNs		SV_15DANDEG_SRV;            /* 15�i�ږڕW�p�x */
extern	UNs		SV_16DANDEG_SRV;            /* 16�i�ږڕW�p�x */
extern	UNs		SV_17DANDEG_SRV;            /* 17�i�ږڕW�p�x */
extern	UNs		SV_18DANDEG_SRV;            /* 18�i�ږڕW�p�x */
extern	UNs		SV_19DANDEG_SRV;            /* 19�i�ږڕW�p�x */
extern	UNs		SV_20DANDEG_SRV;            /* 20�i�ږڕW�p�x */
extern	UNs		SV_21DANDEG_SRV;            /* 21�i�ږڕW�p�x */
extern	UNs		SV_22DANDEG_SRV;            /* 22�i�ږڕW�p�x */
extern	UNs		SV_23DANDEG_SRV;            /* 23�i�ږڕW�p�x */
extern	UNs		SV_24DANDEG_SRV;            /* 24�i�ږڕW�p�x */
extern	UNs		SV_25DANDEG_SRV;            /* 25�i�ږڕW�p�x */
extern	UNs		SV_26DANDEG_SRV;            /* 26�i�ږڕW�p�x */
extern	UNs		SV_27DANDEG_SRV;            /* 27�i�ږڕW�p�x */
extern	UNs		SV_28DANDEG_SRV;            /* 28�i�ږڕW�p�x */
extern	UNs		SV_29DANDEG_SRV;            /* 29�i�ږڕW�p�x */
extern	UNs		SV_30DANDEG_SRV;            /* 30�i�ږڕW�p�x */
extern	UNs		SV_31DANDEG_SRV;            /* 31�i�ږڕW�p�x */
extern	UNs		SV_32DANDEG_SRV;            /* 32�i�ږڕW�p�x */
extern	UNs		SV_33DANDEG_SRV;            /* 33�i�ږڕW�p�x */
extern	UNs		SV_34DANDEG_SRV;            /* 34�i�ږڕW�p�x */
extern	UNs		SV_35DANDEG_SRV;            /* 35�i�ږڕW�p�x */
extern	UNs		SV_36DANDEG_SRV;            /* 36�i�ږڕW�p�x */
extern	UNs		SV_37DANDEG_SRV;            /* 37�i�ږڕW�p�x */
extern	UNs		SV_38DANDEG_SRV;            /* 38�i�ږڕW�p�x */
extern	UNs		SV_39DANDEG_SRV;            /* 39�i�ږڕW�p�x */
extern	UNs		SV_40DANDEG_SRV;            /* 40�i�ږڕW�p�x */
extern	UNs		SV_41DANDEG_SRV;            /* 41�i�ږڕW�p�x */
extern	UNs		SV_42DANDEG_SRV;            /* 42�i�ږڕW�p�x */
extern	UNs		SV_43DANDEG_SRV;            /* 43�i�ږڕW�p�x */
extern	UNs		SV_44DANDEG_SRV;            /* 44�i�ږڕW�p�x */
extern	UNs		SV_45DANDEG_SRV;            /* 45�i�ږڕW�p�x */
extern	UNs		SV_46DANDEG_SRV;            /* 46�i�ږڕW�p�x */
extern	UNs		SV_47DANDEG_SRV;            /* 47�i�ږڕW�p�x */
extern	UNs		SV_48DANDEG_SRV;            /* 48�i�ږڕW�p�x */
extern	UNs		SV_49DANDEG_SRV;            /* 49�i�ږڕW�p�x */
extern	UNs		SV_50DANDEG_SRV;            /* 50�i�ږڕW�p�x */
extern	UNs		SV_51DANDEG_SRV;            /* 51�i�ږڕW�p�x */
extern	UNs		SV_52DANDEG_SRV;            /* 52�i�ږڕW�p�x */
extern	UNs		SV_53DANDEG_SRV;            /* 53�i�ږڕW�p�x */
extern	UNs		SV_54DANDEG_SRV;            /* 54�i�ږڕW�p�x */
extern	UNs		SV_55DANDEG_SRV;            /* 55�i�ږڕW�p�x */
extern	UNs		SV_56DANDEG_SRV;            /* 56�i�ږڕW�p�x */
extern	UNs		SV_57DANDEG_SRV;            /* 57�i�ږڕW�p�x */
extern	UNs		SV_58DANDEG_SRV;            /* 58�i�ږڕW�p�x */
extern	UNs		SV_59DANDEG_SRV;            /* 59�i�ږڕW�p�x */
extern	UNs		SV_60DANDEG_SRV;            /* 60�i�ږڕW�p�x */
extern	UNs		SV_61DANDEG_SRV;            /* 61�i�ږڕW�p�x */
extern	UNs		SV_62DANDEG_SRV;            /* 62�i�ږڕW�p�x */
extern	UNs		SV_63DANDEG_SRV;            /* 63�i�ږڕW�p�x */
extern	UNs		SV_64DANDEG_SRV;            /* 64�i�ږڕW�p�x */
extern	UNs		SV_65DANDEG_SRV;            /* 65�i�ږڕW�p�x */
extern	UNs		SV_66DANDEG_SRV;            /* 66�i�ږڕW�p�x */
extern	UNs		SV_67DANDEG_SRV;            /* 67�i�ږڕW�p�x */
extern	UNs		SV_68DANDEG_SRV;            /* 68�i�ږڕW�p�x */
extern	UNs		SV_69DANDEG_SRV;            /* 69�i�ږڕW�p�x */
extern	UNs		SV_70DANDEG_SRV;            /* 70�i�ږڕW�p�x */
extern	UNs		SV_71DANDEG_SRV;            /* 71�i�ږڕW�p�x */
extern	UNs		SV_72DANDEG_SRV;            /* 72�i�ږڕW�p�x */
extern	UNs		SV_73DANDEG_SRV;            /* 73�i�ږڕW�p�x */
extern	UNs		SV_74DANDEG_SRV;            /* 74�i�ږڕW�p�x */
extern	UNs		SV_75DANDEG_SRV;            /* 75�i�ږڕW�p�x */
extern	UNs		SV_76DANDEG_SRV;            /* 76�i�ږڕW�p�x */
extern	UNs		SV_77DANDEG_SRV;            /* 77�i�ږڕW�p�x */
extern	UNs		SV_78DANDEG_SRV;            /* 78�i�ږڕW�p�x */
extern	UNs		SV_79DANDEG_SRV;            /* 79�i�ږڕW�p�x */
extern	UNs		SV_80DANDEG_SRV;            /* 80�i�ږڕW�p�x */
extern	UNs		SV_81DANDEG_SRV;            /* 81�i�ږڕW�p�x */
extern	UNs		SV_82DANDEG_SRV;            /* 82�i�ږڕW�p�x */
extern	UNs		SV_83DANDEG_SRV;            /* 83�i�ږڕW�p�x */
extern	UNs		SV_84DANDEG_SRV;            /* 84�i�ږڕW�p�x */
extern	UNs		SV_85DANDEG_SRV;            /* 85�i�ږڕW�p�x */
extern	UNs		SV_86DANDEG_SRV;            /* 86�i�ږڕW�p�x */
extern	UNs		SV_87DANDEG_SRV;            /* 87�i�ږڕW�p�x */
extern	UNs		SV_88DANDEG_SRV;            /* 88�i�ږڕW�p�x */
extern	UNs		SV_89DANDEG_SRV;            /* 89�i�ږڕW�p�x */
extern	UNs		SV_90DANDEG_SRV;            /* 90�i�ږڕW�p�x */
extern	UNs		SV_91DANDEG_SRV;            /* 91�i�ږڕW�p�x */
extern	UNs		SV_92DANDEG_SRV;            /* 92�i�ږڕW�p�x */
extern	UNs		SV_93DANDEG_SRV;            /* 93�i�ږڕW�p�x */
extern	UNs		SV_94DANDEG_SRV;            /* 94�i�ږڕW�p�x */
extern	UNs		SV_95DANDEG_SRV;            /* 95�i�ږڕW�p�x */
extern	UNs		SV_96DANDEG_SRV;            /* 96�i�ږڕW�p�x */
extern	UNs		SV_97DANDEG_SRV;            /* 97�i�ږڕW�p�x */
extern	UNs		SV_98DANDEG_SRV;            /* 98�i�ږڕW�p�x */
extern	UNs		SV_99DANDEG_SRV;            /* 99�i�ږڕW�p�x */
extern	UNs		SV_100DANDEG_SRV;           /* 100�i�ږڕW�p�x */
#endif
extern	UNl		SV_1DANPOS_SRV;             /* 1�i�ږڕW�ʒu */
extern	UNl		SV_2DANPOS_SRV;             /* 2�i�ږڕW�ʒu */
extern	UNl		SV_3DANPOS_SRV;             /* 3�i�ږڕW�ʒu */
extern	UNl		SV_4DANPOS_SRV;             /* 4�i�ږڕW�ʒu */
extern	UNl		SV_5DANPOS_SRV;             /* 5�i�ږڕW�ʒu */
extern	UNl		SV_6DANPOS_SRV;             /* 6�i�ږڕW�ʒu */
extern	UNl		SV_7DANPOS_SRV;             /* 7�i�ږڕW�ʒu */
extern	UNl		SV_8DANPOS_SRV;             /* 8�i�ږڕW�ʒu */
extern	UNl		SV_9DANPOS_SRV;             /* 9�i�ږڕW�ʒu */
extern	UNl		SV_10DANPOS_SRV;            /* 10�i�ږڕW�ʒu */
#if (mot100_test == 1)
extern	UNl		SV_11DANPOS_SRV;            /* 11�i�ږڕW�ʒu */
extern	UNl		SV_12DANPOS_SRV;            /* 12�i�ږڕW�ʒu */
extern	UNl		SV_13DANPOS_SRV;            /* 13�i�ږڕW�ʒu */
extern	UNl		SV_14DANPOS_SRV;            /* 14�i�ږڕW�ʒu */
extern	UNl		SV_15DANPOS_SRV;            /* 15�i�ږڕW�ʒu */
extern	UNl		SV_16DANPOS_SRV;            /* 16�i�ږڕW�ʒu */
extern	UNl		SV_17DANPOS_SRV;            /* 17�i�ږڕW�ʒu */
extern	UNl		SV_18DANPOS_SRV;            /* 18�i�ږڕW�ʒu */
extern	UNl		SV_19DANPOS_SRV;            /* 19�i�ږڕW�ʒu */
extern	UNl		SV_20DANPOS_SRV;            /* 20�i�ږڕW�ʒu */
extern	UNl		SV_21DANPOS_SRV;            /* 21�i�ږڕW�ʒu */
extern	UNl		SV_22DANPOS_SRV;            /* 22�i�ږڕW�ʒu */
extern	UNl		SV_23DANPOS_SRV;            /* 23�i�ږڕW�ʒu */
extern	UNl		SV_24DANPOS_SRV;            /* 24�i�ږڕW�ʒu */
extern	UNl		SV_25DANPOS_SRV;            /* 25�i�ږڕW�ʒu */
extern	UNl		SV_26DANPOS_SRV;            /* 26�i�ږڕW�ʒu */
extern	UNl		SV_27DANPOS_SRV;            /* 27�i�ږڕW�ʒu */
extern	UNl		SV_28DANPOS_SRV;            /* 28�i�ږڕW�ʒu */
extern	UNl		SV_29DANPOS_SRV;            /* 29�i�ږڕW�ʒu */
extern	UNl		SV_30DANPOS_SRV;            /* 30�i�ږڕW�ʒu */
extern	UNl		SV_31DANPOS_SRV;            /* 31�i�ږڕW�ʒu */
extern	UNl		SV_32DANPOS_SRV;            /* 32�i�ږڕW�ʒu */
extern	UNl		SV_33DANPOS_SRV;            /* 33�i�ږڕW�ʒu */
extern	UNl		SV_34DANPOS_SRV;            /* 34�i�ږڕW�ʒu */
extern	UNl		SV_35DANPOS_SRV;            /* 35�i�ږڕW�ʒu */
extern	UNl		SV_36DANPOS_SRV;            /* 36�i�ږڕW�ʒu */
extern	UNl		SV_37DANPOS_SRV;            /* 37�i�ږڕW�ʒu */
extern	UNl		SV_38DANPOS_SRV;            /* 38�i�ږڕW�ʒu */
extern	UNl		SV_39DANPOS_SRV;            /* 39�i�ږڕW�ʒu */
extern	UNl		SV_40DANPOS_SRV;            /* 40�i�ږڕW�ʒu */
extern	UNl		SV_41DANPOS_SRV;            /* 41�i�ږڕW�ʒu */
extern	UNl		SV_42DANPOS_SRV;            /* 42�i�ږڕW�ʒu */
extern	UNl		SV_43DANPOS_SRV;            /* 43�i�ږڕW�ʒu */
extern	UNl		SV_44DANPOS_SRV;            /* 44�i�ږڕW�ʒu */
extern	UNl		SV_45DANPOS_SRV;            /* 45�i�ږڕW�ʒu */
extern	UNl		SV_46DANPOS_SRV;            /* 46�i�ږڕW�ʒu */
extern	UNl		SV_47DANPOS_SRV;            /* 47�i�ږڕW�ʒu */
extern	UNl		SV_48DANPOS_SRV;            /* 48�i�ږڕW�ʒu */
extern	UNl		SV_49DANPOS_SRV;            /* 49�i�ږڕW�ʒu */
extern	UNl		SV_50DANPOS_SRV;            /* 50�i�ږڕW�ʒu */
extern	UNl		SV_51DANPOS_SRV;            /* 51�i�ږڕW�ʒu */
extern	UNl		SV_52DANPOS_SRV;            /* 52�i�ږڕW�ʒu */
extern	UNl		SV_53DANPOS_SRV;            /* 53�i�ږڕW�ʒu */
extern	UNl		SV_54DANPOS_SRV;            /* 54�i�ږڕW�ʒu */
extern	UNl		SV_55DANPOS_SRV;            /* 55�i�ږڕW�ʒu */
extern	UNl		SV_56DANPOS_SRV;            /* 56�i�ږڕW�ʒu */
extern	UNl		SV_57DANPOS_SRV;            /* 57�i�ږڕW�ʒu */
extern	UNl		SV_58DANPOS_SRV;            /* 58�i�ږڕW�ʒu */
extern	UNl		SV_59DANPOS_SRV;            /* 59�i�ږڕW�ʒu */
extern	UNl		SV_60DANPOS_SRV;            /* 60�i�ږڕW�ʒu */
extern	UNl		SV_61DANPOS_SRV;            /* 61�i�ږڕW�ʒu */
extern	UNl		SV_62DANPOS_SRV;            /* 62�i�ږڕW�ʒu */
extern	UNl		SV_63DANPOS_SRV;            /* 63�i�ږڕW�ʒu */
extern	UNl		SV_64DANPOS_SRV;            /* 64�i�ږڕW�ʒu */
extern	UNl		SV_65DANPOS_SRV;            /* 65�i�ږڕW�ʒu */
extern	UNl		SV_66DANPOS_SRV;            /* 66�i�ږڕW�ʒu */
extern	UNl		SV_67DANPOS_SRV;            /* 67�i�ږڕW�ʒu */
extern	UNl		SV_68DANPOS_SRV;            /* 68�i�ږڕW�ʒu */
extern	UNl		SV_69DANPOS_SRV;            /* 69�i�ږڕW�ʒu */
extern	UNl		SV_70DANPOS_SRV;            /* 70�i�ږڕW�ʒu */
extern	UNl		SV_71DANPOS_SRV;            /* 71�i�ږڕW�ʒu */
extern	UNl		SV_72DANPOS_SRV;            /* 72�i�ږڕW�ʒu */
extern	UNl		SV_73DANPOS_SRV;            /* 73�i�ږڕW�ʒu */
extern	UNl		SV_74DANPOS_SRV;            /* 74�i�ږڕW�ʒu */
extern	UNl		SV_75DANPOS_SRV;            /* 75�i�ږڕW�ʒu */
extern	UNl		SV_76DANPOS_SRV;            /* 76�i�ږڕW�ʒu */
extern	UNl		SV_77DANPOS_SRV;            /* 77�i�ږڕW�ʒu */
extern	UNl		SV_78DANPOS_SRV;            /* 78�i�ږڕW�ʒu */
extern	UNl		SV_79DANPOS_SRV;            /* 79�i�ږڕW�ʒu */
extern	UNl		SV_80DANPOS_SRV;            /* 80�i�ږڕW�ʒu */
extern	UNl		SV_81DANPOS_SRV;            /* 81�i�ږڕW�ʒu */
extern	UNl		SV_82DANPOS_SRV;            /* 82�i�ږڕW�ʒu */
extern	UNl		SV_83DANPOS_SRV;            /* 83�i�ږڕW�ʒu */
extern	UNl		SV_84DANPOS_SRV;            /* 84�i�ږڕW�ʒu */
extern	UNl		SV_85DANPOS_SRV;            /* 85�i�ږڕW�ʒu */
extern	UNl		SV_86DANPOS_SRV;            /* 86�i�ږڕW�ʒu */
extern	UNl		SV_87DANPOS_SRV;            /* 87�i�ږڕW�ʒu */
extern	UNl		SV_88DANPOS_SRV;            /* 88�i�ږڕW�ʒu */
extern	UNl		SV_89DANPOS_SRV;            /* 89�i�ږڕW�ʒu */
extern	UNl		SV_90DANPOS_SRV;            /* 90�i�ږڕW�ʒu */
extern	UNl		SV_91DANPOS_SRV;            /* 91�i�ږڕW�ʒu */
extern	UNl		SV_92DANPOS_SRV;            /* 92�i�ږڕW�ʒu */
extern	UNl		SV_93DANPOS_SRV;            /* 93�i�ږڕW�ʒu */
extern	UNl		SV_94DANPOS_SRV;            /* 94�i�ږڕW�ʒu */
extern	UNl		SV_95DANPOS_SRV;            /* 95�i�ږڕW�ʒu */
extern	UNl		SV_96DANPOS_SRV;            /* 96�i�ږڕW�ʒu */
extern	UNl		SV_97DANPOS_SRV;            /* 97�i�ږڕW�ʒu */
extern	UNl		SV_98DANPOS_SRV;            /* 98�i�ږڕW�ʒu */
extern	UNl		SV_99DANPOS_SRV;            /* 99�i�ږڕW�ʒu */
extern	UNl		SV_100DANPOS_SRV;           /* 100�i�ږڕW�ʒu */
#endif
extern	UNs		SV_1DANSPD_SRV;             /* 1�i�ڈړ����x */
extern	UNs		SV_2DANSPD_SRV;             /* 2�i�ڈړ����x */
extern	UNs		SV_3DANSPD_SRV;             /* 3�i�ڈړ����x */
extern	UNs		SV_4DANSPD_SRV;             /* 4�i�ڈړ����x */
extern	UNs		SV_5DANSPD_SRV;             /* 5�i�ڈړ����x */
extern	UNs		SV_6DANSPD_SRV;             /* 6�i�ڈړ����x */
extern	UNs		SV_7DANSPD_SRV;             /* 7�i�ڈړ����x */
extern	UNs		SV_8DANSPD_SRV;             /* 8�i�ڈړ����x */
extern	UNs		SV_9DANSPD_SRV;             /* 9�i�ڈړ����x */
extern	UNs		SV_10DANSPD_SRV;            /* 10�i�ڈړ����x */
#if (mot100_test == 1)
extern	UNs		SV_11DANSPD_SRV;            /* 11�i�ڈړ����x */
extern	UNs		SV_12DANSPD_SRV;            /* 12�i�ڈړ����x */
extern	UNs		SV_13DANSPD_SRV;            /* 13�i�ڈړ����x */
extern	UNs		SV_14DANSPD_SRV;            /* 14�i�ڈړ����x */
extern	UNs		SV_15DANSPD_SRV;            /* 15�i�ڈړ����x */
extern	UNs		SV_16DANSPD_SRV;            /* 16�i�ڈړ����x */
extern	UNs		SV_17DANSPD_SRV;            /* 17�i�ڈړ����x */
extern	UNs		SV_18DANSPD_SRV;            /* 18�i�ڈړ����x */
extern	UNs		SV_19DANSPD_SRV;            /* 19�i�ڈړ����x */
extern	UNs		SV_20DANSPD_SRV;            /* 20�i�ڈړ����x */
extern	UNs		SV_21DANSPD_SRV;            /* 21�i�ڈړ����x */
extern	UNs		SV_22DANSPD_SRV;            /* 22�i�ڈړ����x */
extern	UNs		SV_23DANSPD_SRV;            /* 23�i�ڈړ����x */
extern	UNs		SV_24DANSPD_SRV;            /* 24�i�ڈړ����x */
extern	UNs		SV_25DANSPD_SRV;            /* 25�i�ڈړ����x */
extern	UNs		SV_26DANSPD_SRV;            /* 26�i�ڈړ����x */
extern	UNs		SV_27DANSPD_SRV;            /* 27�i�ڈړ����x */
extern	UNs		SV_28DANSPD_SRV;            /* 28�i�ڈړ����x */
extern	UNs		SV_29DANSPD_SRV;            /* 29�i�ڈړ����x */
extern	UNs		SV_30DANSPD_SRV;            /* 30�i�ڈړ����x */
extern	UNs		SV_31DANSPD_SRV;            /* 31�i�ڈړ����x */
extern	UNs		SV_32DANSPD_SRV;            /* 32�i�ڈړ����x */
extern	UNs		SV_33DANSPD_SRV;            /* 33�i�ڈړ����x */
extern	UNs		SV_34DANSPD_SRV;            /* 34�i�ڈړ����x */
extern	UNs		SV_35DANSPD_SRV;            /* 35�i�ڈړ����x */
extern	UNs		SV_36DANSPD_SRV;            /* 36�i�ڈړ����x */
extern	UNs		SV_37DANSPD_SRV;            /* 37�i�ڈړ����x */
extern	UNs		SV_38DANSPD_SRV;            /* 38�i�ڈړ����x */
extern	UNs		SV_39DANSPD_SRV;            /* 39�i�ڈړ����x */
extern	UNs		SV_40DANSPD_SRV;            /* 40�i�ڈړ����x */
extern	UNs		SV_41DANSPD_SRV;            /* 41�i�ڈړ����x */
extern	UNs		SV_42DANSPD_SRV;            /* 42�i�ڈړ����x */
extern	UNs		SV_43DANSPD_SRV;            /* 43�i�ڈړ����x */
extern	UNs		SV_44DANSPD_SRV;            /* 44�i�ڈړ����x */
extern	UNs		SV_45DANSPD_SRV;            /* 45�i�ڈړ����x */
extern	UNs		SV_46DANSPD_SRV;            /* 46�i�ڈړ����x */
extern	UNs		SV_47DANSPD_SRV;            /* 47�i�ڈړ����x */
extern	UNs		SV_48DANSPD_SRV;            /* 48�i�ڈړ����x */
extern	UNs		SV_49DANSPD_SRV;            /* 49�i�ڈړ����x */
extern	UNs		SV_50DANSPD_SRV;            /* 50�i�ڈړ����x */
extern	UNs		SV_51DANSPD_SRV;            /* 51�i�ڈړ����x */
extern	UNs		SV_52DANSPD_SRV;            /* 52�i�ڈړ����x */
extern	UNs		SV_53DANSPD_SRV;            /* 53�i�ڈړ����x */
extern	UNs		SV_54DANSPD_SRV;            /* 54�i�ڈړ����x */
extern	UNs		SV_55DANSPD_SRV;            /* 55�i�ڈړ����x */
extern	UNs		SV_56DANSPD_SRV;            /* 56�i�ڈړ����x */
extern	UNs		SV_57DANSPD_SRV;            /* 57�i�ڈړ����x */
extern	UNs		SV_58DANSPD_SRV;            /* 58�i�ڈړ����x */
extern	UNs		SV_59DANSPD_SRV;            /* 59�i�ڈړ����x */
extern	UNs		SV_60DANSPD_SRV;            /* 60�i�ڈړ����x */
extern	UNs		SV_61DANSPD_SRV;            /* 61�i�ڈړ����x */
extern	UNs		SV_62DANSPD_SRV;            /* 62�i�ڈړ����x */
extern	UNs		SV_63DANSPD_SRV;            /* 63�i�ڈړ����x */
extern	UNs		SV_64DANSPD_SRV;            /* 64�i�ڈړ����x */
extern	UNs		SV_65DANSPD_SRV;            /* 65�i�ڈړ����x */
extern	UNs		SV_66DANSPD_SRV;            /* 66�i�ڈړ����x */
extern	UNs		SV_67DANSPD_SRV;            /* 67�i�ڈړ����x */
extern	UNs		SV_68DANSPD_SRV;            /* 68�i�ڈړ����x */
extern	UNs		SV_69DANSPD_SRV;            /* 69�i�ڈړ����x */
extern	UNs		SV_70DANSPD_SRV;            /* 70�i�ڈړ����x */
extern	UNs		SV_71DANSPD_SRV;            /* 71�i�ڈړ����x */
extern	UNs		SV_72DANSPD_SRV;            /* 72�i�ڈړ����x */
extern	UNs		SV_73DANSPD_SRV;            /* 73�i�ڈړ����x */
extern	UNs		SV_74DANSPD_SRV;            /* 74�i�ڈړ����x */
extern	UNs		SV_75DANSPD_SRV;            /* 75�i�ڈړ����x */
extern	UNs		SV_76DANSPD_SRV;            /* 76�i�ڈړ����x */
extern	UNs		SV_77DANSPD_SRV;            /* 77�i�ڈړ����x */
extern	UNs		SV_78DANSPD_SRV;            /* 78�i�ڈړ����x */
extern	UNs		SV_79DANSPD_SRV;            /* 79�i�ڈړ����x */
extern	UNs		SV_80DANSPD_SRV;            /* 80�i�ڈړ����x */
extern	UNs		SV_81DANSPD_SRV;            /* 81�i�ڈړ����x */
extern	UNs		SV_82DANSPD_SRV;            /* 82�i�ڈړ����x */
extern	UNs		SV_83DANSPD_SRV;            /* 83�i�ڈړ����x */
extern	UNs		SV_84DANSPD_SRV;            /* 84�i�ڈړ����x */
extern	UNs		SV_85DANSPD_SRV;            /* 85�i�ڈړ����x */
extern	UNs		SV_86DANSPD_SRV;            /* 86�i�ڈړ����x */
extern	UNs		SV_87DANSPD_SRV;            /* 87�i�ڈړ����x */
extern	UNs		SV_88DANSPD_SRV;            /* 88�i�ڈړ����x */
extern	UNs		SV_89DANSPD_SRV;            /* 89�i�ڈړ����x */
extern	UNs		SV_90DANSPD_SRV;            /* 90�i�ڈړ����x */
extern	UNs		SV_91DANSPD_SRV;            /* 91�i�ڈړ����x */
extern	UNs		SV_92DANSPD_SRV;            /* 92�i�ڈړ����x */
extern	UNs		SV_93DANSPD_SRV;            /* 93�i�ڈړ����x */
extern	UNs		SV_94DANSPD_SRV;            /* 94�i�ڈړ����x */
extern	UNs		SV_95DANSPD_SRV;            /* 95�i�ڈړ����x */
extern	UNs		SV_96DANSPD_SRV;            /* 96�i�ڈړ����x */
extern	UNs		SV_97DANSPD_SRV;            /* 97�i�ڈړ����x */
extern	UNs		SV_98DANSPD_SRV;            /* 98�i�ڈړ����x */
extern	UNs		SV_99DANSPD_SRV;            /* 99�i�ڈړ����x */
extern	UNs		SV_100DANSPD_SRV;           /* 100�i�ڈړ����x */
#endif
extern	UNs		SV_1DANTIM_SRV;             /* 1�i�ڒ�~���� */
extern	UNs		SV_2DANTIM_SRV;             /* 2�i�ڒ�~���� */
extern	UNs		SV_3DANTIM_SRV;             /* 3�i�ڒ�~���� */
extern	UNs		SV_4DANTIM_SRV;             /* 4�i�ڒ�~���� */
extern	UNs		SV_5DANTIM_SRV;             /* 5�i�ڒ�~���� */
extern	UNs		SV_6DANTIM_SRV;             /* 6�i�ڒ�~���� */
extern	UNs		SV_7DANTIM_SRV;             /* 7�i�ڒ�~���� */
extern	UNs		SV_8DANTIM_SRV;             /* 8�i�ڒ�~���� */
extern	UNs		SV_9DANTIM_SRV;             /* 9�i�ڒ�~���� */
extern	UNs		SV_10DANTIM_SRV;            /* 10�i�ڒ�~���� */
#if (mot100_test == 1)
extern	UNs		SV_11DANTIM_SRV;            /* 11�i�ڒ�~���� */
extern	UNs		SV_12DANTIM_SRV;            /* 12�i�ڒ�~���� */
extern	UNs		SV_13DANTIM_SRV;            /* 13�i�ڒ�~���� */
extern	UNs		SV_14DANTIM_SRV;            /* 14�i�ڒ�~���� */
extern	UNs		SV_15DANTIM_SRV;            /* 15�i�ڒ�~���� */
extern	UNs		SV_16DANTIM_SRV;            /* 16�i�ڒ�~���� */
extern	UNs		SV_17DANTIM_SRV;            /* 17�i�ڒ�~���� */
extern	UNs		SV_18DANTIM_SRV;            /* 18�i�ڒ�~���� */
extern	UNs		SV_19DANTIM_SRV;            /* 19�i�ڒ�~���� */
extern	UNs		SV_20DANTIM_SRV;            /* 20�i�ڒ�~���� */
extern	UNs		SV_21DANTIM_SRV;            /* 21�i�ڒ�~���� */
extern	UNs		SV_22DANTIM_SRV;            /* 22�i�ڒ�~���� */
extern	UNs		SV_23DANTIM_SRV;            /* 23�i�ڒ�~���� */
extern	UNs		SV_24DANTIM_SRV;            /* 24�i�ڒ�~���� */
extern	UNs		SV_25DANTIM_SRV;            /* 25�i�ڒ�~���� */
extern	UNs		SV_26DANTIM_SRV;            /* 26�i�ڒ�~���� */
extern	UNs		SV_27DANTIM_SRV;            /* 27�i�ڒ�~���� */
extern	UNs		SV_28DANTIM_SRV;            /* 28�i�ڒ�~���� */
extern	UNs		SV_29DANTIM_SRV;            /* 29�i�ڒ�~���� */
extern	UNs		SV_30DANTIM_SRV;            /* 30�i�ڒ�~���� */
extern	UNs		SV_31DANTIM_SRV;            /* 31�i�ڒ�~���� */
extern	UNs		SV_32DANTIM_SRV;            /* 32�i�ڒ�~���� */
extern	UNs		SV_33DANTIM_SRV;            /* 33�i�ڒ�~���� */
extern	UNs		SV_34DANTIM_SRV;            /* 34�i�ڒ�~���� */
extern	UNs		SV_35DANTIM_SRV;            /* 35�i�ڒ�~���� */
extern	UNs		SV_36DANTIM_SRV;            /* 36�i�ڒ�~���� */
extern	UNs		SV_37DANTIM_SRV;            /* 37�i�ڒ�~���� */
extern	UNs		SV_38DANTIM_SRV;            /* 38�i�ڒ�~���� */
extern	UNs		SV_39DANTIM_SRV;            /* 39�i�ڒ�~���� */
extern	UNs		SV_40DANTIM_SRV;            /* 40�i�ڒ�~���� */
extern	UNs		SV_41DANTIM_SRV;            /* 41�i�ڒ�~���� */
extern	UNs		SV_42DANTIM_SRV;            /* 42�i�ڒ�~���� */
extern	UNs		SV_43DANTIM_SRV;            /* 43�i�ڒ�~���� */
extern	UNs		SV_44DANTIM_SRV;            /* 44�i�ڒ�~���� */
extern	UNs		SV_45DANTIM_SRV;            /* 45�i�ڒ�~���� */
extern	UNs		SV_46DANTIM_SRV;            /* 46�i�ڒ�~���� */
extern	UNs		SV_47DANTIM_SRV;            /* 47�i�ڒ�~���� */
extern	UNs		SV_48DANTIM_SRV;            /* 48�i�ڒ�~���� */
extern	UNs		SV_49DANTIM_SRV;            /* 49�i�ڒ�~���� */
extern	UNs		SV_50DANTIM_SRV;            /* 50�i�ڒ�~���� */
extern	UNs		SV_51DANTIM_SRV;            /* 51�i�ڒ�~���� */
extern	UNs		SV_52DANTIM_SRV;            /* 52�i�ڒ�~���� */
extern	UNs		SV_53DANTIM_SRV;            /* 53�i�ڒ�~���� */
extern	UNs		SV_54DANTIM_SRV;            /* 54�i�ڒ�~���� */
extern	UNs		SV_55DANTIM_SRV;            /* 55�i�ڒ�~���� */
extern	UNs		SV_56DANTIM_SRV;            /* 56�i�ڒ�~���� */
extern	UNs		SV_57DANTIM_SRV;            /* 57�i�ڒ�~���� */
extern	UNs		SV_58DANTIM_SRV;            /* 58�i�ڒ�~���� */
extern	UNs		SV_59DANTIM_SRV;            /* 59�i�ڒ�~���� */
extern	UNs		SV_60DANTIM_SRV;            /* 60�i�ڒ�~���� */
extern	UNs		SV_61DANTIM_SRV;            /* 61�i�ڒ�~���� */
extern	UNs		SV_62DANTIM_SRV;            /* 62�i�ڒ�~���� */
extern	UNs		SV_63DANTIM_SRV;            /* 63�i�ڒ�~���� */
extern	UNs		SV_64DANTIM_SRV;            /* 64�i�ڒ�~���� */
extern	UNs		SV_65DANTIM_SRV;            /* 65�i�ڒ�~���� */
extern	UNs		SV_66DANTIM_SRV;            /* 66�i�ڒ�~���� */
extern	UNs		SV_67DANTIM_SRV;            /* 67�i�ڒ�~���� */
extern	UNs		SV_68DANTIM_SRV;            /* 68�i�ڒ�~���� */
extern	UNs		SV_69DANTIM_SRV;            /* 69�i�ڒ�~���� */
extern	UNs		SV_70DANTIM_SRV;            /* 70�i�ڒ�~���� */
extern	UNs		SV_71DANTIM_SRV;            /* 71�i�ڒ�~���� */
extern	UNs		SV_72DANTIM_SRV;            /* 72�i�ڒ�~���� */
extern	UNs		SV_73DANTIM_SRV;            /* 73�i�ڒ�~���� */
extern	UNs		SV_74DANTIM_SRV;            /* 74�i�ڒ�~���� */
extern	UNs		SV_75DANTIM_SRV;            /* 75�i�ڒ�~���� */
extern	UNs		SV_76DANTIM_SRV;            /* 76�i�ڒ�~���� */
extern	UNs		SV_77DANTIM_SRV;            /* 77�i�ڒ�~���� */
extern	UNs		SV_78DANTIM_SRV;            /* 78�i�ڒ�~���� */
extern	UNs		SV_79DANTIM_SRV;            /* 79�i�ڒ�~���� */
extern	UNs		SV_80DANTIM_SRV;            /* 80�i�ڒ�~���� */
extern	UNs		SV_81DANTIM_SRV;            /* 81�i�ڒ�~���� */
extern	UNs		SV_82DANTIM_SRV;            /* 82�i�ڒ�~���� */
extern	UNs		SV_83DANTIM_SRV;            /* 83�i�ڒ�~���� */
extern	UNs		SV_84DANTIM_SRV;            /* 84�i�ڒ�~���� */
extern	UNs		SV_85DANTIM_SRV;            /* 85�i�ڒ�~���� */
extern	UNs		SV_86DANTIM_SRV;            /* 86�i�ڒ�~���� */
extern	UNs		SV_87DANTIM_SRV;            /* 87�i�ڒ�~���� */
extern	UNs		SV_88DANTIM_SRV;            /* 88�i�ڒ�~���� */
extern	UNs		SV_89DANTIM_SRV;            /* 89�i�ڒ�~���� */
extern	UNs		SV_90DANTIM_SRV;            /* 90�i�ڒ�~���� */
extern	UNs		SV_91DANTIM_SRV;            /* 91�i�ڒ�~���� */
extern	UNs		SV_92DANTIM_SRV;            /* 92�i�ڒ�~���� */
extern	UNs		SV_93DANTIM_SRV;            /* 93�i�ڒ�~���� */
extern	UNs		SV_94DANTIM_SRV;            /* 94�i�ڒ�~���� */
extern	UNs		SV_95DANTIM_SRV;            /* 95�i�ڒ�~���� */
extern	UNs		SV_96DANTIM_SRV;            /* 96�i�ڒ�~���� */
extern	UNs		SV_97DANTIM_SRV;            /* 97�i�ڒ�~���� */
extern	UNs		SV_98DANTIM_SRV;            /* 98�i�ڒ�~���� */
extern	UNs		SV_99DANTIM_SRV;            /* 99�i�ڒ�~���� */
extern	UNs		SV_100DANTIM_SRV;           /* 100�i�ڒ�~���� */
#endif
//extern	UNs		SV_CYCTIM_SRV;              /* �T�C�N���^�C�� */
//extern	UNs		SV_TAIKAN_SRV;              /* �ҋ@�����͈� */
extern	UNs		SV_MOKKAN_SRV;              /* �ڕW�����͈� */
extern	UNs		SV_KAJYUU_PRS;				/* �׏d�␳ V01m*/
extern	UNs		SV_KAJYUU_OBJP;				/* �׏d�ڕW V01m*/

extern	UNs		disp_stg, disp_stg_sel;
extern	UNl		language_chg;

extern	UNs		PV_STPTIM_B2;					/* ssc_tbl.c �ɂĎg�p		*/

//extern	UNs		PV_KOUTEI1_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI2_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI3_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI4_NO;					/*                      	*/
//extern	UNs		PV_KOUTEI5_NO;					/*                      	*/

extern	UNs		PV_CAMNA1_C1;					/*                      	*/

extern	UNs		PV_STPTM_OLD;					/*                      	*/
extern	UNs		PV_MLNO01_C15;					/*                      	*/
extern	UNs		PV_MLNO02_C15;					/*                      	*/
extern	UNs		PV_MLNO03_C15;					/*                      	*/
extern	UNs		PV_MLNO04_C15;					/*                      	*/
extern	UNs		PV_MLNO05_C15;					/*                      	*/
extern	UNs		PV_MLNO06_C15;					/*                      	*/
extern	UNs		PV_MLNO07_C15;					/*                      	*/
extern	UNs		PV_MLNO08_C15;					/*                      	*/
extern	UNs		PV_MLNO09_C15;					/*                      	*/
extern	UNs		PV_MLNO10_C15;					/*                      	*/

extern	UNs		PV_MLDNO2_F11[8];		//DB 16 DUP(?)	;	/* V01j */

//extern	UNl		PVB_RNAORG_PLS1;				/*							*/
//extern	UNl		SV_GENITI_CHK;

extern	UNs		PV_CAMNA1_C1;					/*                      	*/
extern	UNs		PV_MLDMES_C1;					/*							*/
extern	UNs		PV_OFFSET_A1;					/*                      	*/
extern	UNs		PV_DATINI_A1;					/*                      	*/
extern	UNs		PV_KAJYUU_A1;					/*                      	*/
extern	UNs		PV_GAIBU_A1;					/*                      	*/
extern	UNs		PV_BACKDA_A1;					/*                      	*/

extern	UNs		TAIKI_ZEN_MOD;					/* ���[���b�g�O��`�����	*/
extern	UNs		TAIKITEN_DIRECT;				/* �ҋ@�_�f�[�^�i�N���b�`�j	*/

extern	UNs		SEISAN_DISP_FLG;				// ���Y�s���\��	 (00:�Ȃ��^FF:����)
extern	UNs		INTROCK_DISP_FLG;				// �K�C�_���X�\��(00:�Ȃ��^FF:����)

extern	UNs		IROCK_NO	 [];				/* ����ۯ��\���ԍ���		*/
extern	UNs		IROCK_NO_LAST[];				/* ����ۯ��\���ԍ���O��l	*/

/*==========================================================================*/
/*		�L�[���͗p�̃��[�N�̈��`											*/
/*==========================================================================*/
//extern	UNs		KEY_DATA_FLG;				/* �j�����f�[�^����t���O */
//extern	UNs		KEY_DATA_NO[4];				/* �j�����f�[�^�m���D�t���O */
extern	UNs		KEY_DATA_CODE, KEY_DATA_MODE;
extern	UNs		Key_up[4],Key_dn[4],Key_last[4];

/*==========================================================================*/
/*		�����[�N�̈��`(Sit-2���)											*/
/*==========================================================================*/
/***	�\���p�̃��[�N�̈��`		***/
extern	UNs		GAMEN_NO;					//DW ?	;/* ��ʃR�[�h */
extern	UNs		GAMEN_CODE;					//DB ?	;/* ��ʃR�[�h */
extern	UNs		WINDOW_NO;					//DW ?	;/* ��ʃR�[�h */
extern	UNs		CSR_FLG;					//DB ?	;/* �J�[�\���L���ʃt���O */

extern	UNs		CSR_CNT;					/* �J�[�\���J�E���^ */
extern	UNs		CSR_CNT1;					/* �J�[�\���J�E���^ */
extern	UNs		SV_CNT;						/* �ݒ�l�J�E���^ */
extern	UNs		PV_CNT;						/* �����l�J�E���^ */
extern	UNs		SW_CNT;						/* �r�v�f�[�^�J�E���^ */
extern	UNs		SW_CNT1;					/* �r�v�f�[�^�J�E���^ */

extern	CSR_TBL_TDEF	CSR_buff[110];		/* �J�[�\�����e�[�u����`�̈�	*/
extern	SV_TBL_TDEF		SV_buff[100];		/* �ݒ�l���e�[�u����`�̈�	*/
extern	PV_TBL_TDEF		PV_buff[40];		/* �����l���e�[�u����`�̈�	*/
extern	SW_TBL_TDEF		SW_buff[70];		/* �r�v�f�[�^���e�[�u����`�̈�	*/

extern	UNs		PV_DISP_CNT;				/* �\�������l�J�E���^ */
extern	UNs		SW_DISP_CNT;				//����\���r�v�f�[�^�J�E���^

extern	UNs		LCD_WORK1[15][16][40];		/* �\��ܰ��̈�LCD1[���s���ޯĖډ�������] */
extern	UNs		LCD_WORK2[15][16][40];		/* �\��ܰ��̈�LCD2[���s���ޯĖډ�������] */
extern	UNs		LCD_WORK3[15][16][40];		/* �\��ܰ��̈�LCD3[���s���ޯĖډ�������] */ /* V01  */

extern	UNs		CSR_FLG_CNT;				//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
extern	UNs		SV_FLG_CNT;					//DW ?	;/* �����l�Z�b�g */
extern	UNs		SW_FLG_CNT;					//DW ?	;/* �����l�Z�b�g */

extern	UNs		CSR_POS;					//DW ?	;/* �J�[�\���|�W�V�����f�[�^�Ǎ� */
extern	UNs		CSR_POS_LAST;				//DW ?	;/* �O��J�[�\���|�W�V�����f�[�^�Ǎ� */
extern	UNs		CSR_ON_FLG;					//DB ?	;/* �J�[�\���\���t���O�n�m */

extern	UNs		SWDATA_DISP_CNT;			//DW ?	;/* �r�v�f�[�^�\���p���[�v�J�E���g */
extern	UNs		SVSW_CHG_FLG;				//DB ?	;/* �f�[�^�`�F���W�t���O�Z�b�g */

extern	UNl		SV_DISP_BUFF;				//DB 20 DUP(?)	;/* �ݒ�l���ԃo�b�t�@�i�`�r�b�h�h�j */
extern	UNs		SV_DATA_CHG;				//DB ?	;//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
extern	UNs		CSR_TBL_POS_NOW;			//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
extern	UNs		SV_TBL_POS_NOW;				//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
extern	UNs		SW_TBL_POS_NOW;				//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
extern	UNs		DISP_CHG_FLG;				//DB ?	;/* �\�����]�t���O�Z�b�g */

extern	UNs		SV_DISP_CNT;				//DB ?	;/* �ݒ�l�\���������͏����� */
extern	UNs		SV_ENT_CNT;					//DB ?
extern	UNs		TENKEY_CNT;					//DB ?	;/* ���̓I�[�o�[�H */
extern	UNs		NO_SUPRESU;					//DB ?
extern	UNs		INTER_ROCK_FLG;				//DB ?	;/* �C���^�[���b�N�L��H */
extern	UNs		PATH_WORD_CNT;				//DB ?		;

extern	UNs		SEI_INF_BUFF[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
extern	UNs		SEI_INF_BUFF1[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
extern	UNs		SEI_INF_BUFF2[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
extern	UNs		SEI_WRT_POS;				//DW ?	;/* �\���ʒu */
extern	UNs		SEI_WRT_CNT;				//DW ?		;/* �\�������� */
extern	UNs		SEI_WRT_ADR;				//DW ?		;/* �\�������� */
extern	UNs		IROCK_BUFF[40];				//DW 40 DUP(?)	;
extern	UNs		IROCK_BUFF01[320/2];		//DB 320 DUP(?)	;
extern	UNs		SEI_INF_FLG;				//DB ?
extern	UNs		SEI_INF_FLG_LAST;			//DB ?		;

extern	UNs		GAMEN_WRITE_CNT;			//DB ?		;
extern	UNs		SEQ_044_WORK[30/2];				//DB 30 DUP(?)	;

extern	UNs		IROC_CHG_FLG;				//DW ?	;
extern	UNs		IROC_CHG_FLG1;				//DW ?	;
extern	UNs		IL_DISP_LAST;				//DB ?
extern	UNs		GAMEN_NO_IROCK;				//DW ?
extern	UNs		SEISAN_FLG;					//DB ?	;
extern	UNs		SEISAN_FLG_LAST;			//DB ?	;
extern	UNs		IROCK_SHR_LAST;				//DB ?
extern	UNs		SVPV_DATA_FLG;				//DB ?
extern	UNs		SOUSA_LEFT_FLG;				//DB ?
extern	UNs		ERR_MONI_LAST1;				//DW ?
extern	UNs		ERR_MONI_LAST2;				//DW ?
extern	UNs		ERR_MONI_LAST3;				//DW ?
extern	UNs		DAN_SOUSA_DAT;				//DW ?
extern	UNs		RULET_DIG_TBL_ADR;			//DW ?
extern	UNs		SEI_COUNT_LAST1;			//DB ?;
extern	UNs		SEI_COUNT_LAST2;			//DB ?;
extern	UNs		SEI_COUNT_LAST3;			//DB ?;
extern	UNs		SEI_COUNT_LAST4;			//DB ?;

extern	UNs		GAMEN_ON_FLG;				//DB ?
extern	UNs		IL_DISP_FLG;				//DB ?		;/* �h�k�\���t���O���Z�b�g */
extern	UNs		INI_FLG	;					//DB ?
extern	UNs		SEQ_018_SV_BUFF;			//DB ?
extern	UNs		BASE_CLS_CNT;				//DW ?
extern	UNs		SEI_INF_SPATH_CNT;			//DW ?
extern	UNs		SUM_CHK_ERR;				//DB ?
extern	UNs		DAN_NON_GAMEN;				//DB ?
extern	UNs		SV_CHK_ERR;					//DB ?
extern	UNs		SV_CMP_ERR;					//DB ?
extern	UNs		SV_SUM1_ERR;				//DB ?
extern	UNs		SV_SUM2_ERR;				//DB ?
extern	UNs		SV_DPRAM_ERR;				//DB ?

extern	UNs		INCH_DATA_FLG;				//DB ?	;/* INCH�����t���O */

extern	UNs		OP_MESS_DISP_LAST1;			//DB ?	;
extern	UNs		OP_MESS_DISP_LAST2;			//DB ?	;
extern	UNs		OP_MESS_DISP_LAST3;			//DB ?	;

extern	UNs		OFF_SET_MNG_LAST;			//DB ?	;
extern	UNs		OFF_SET_MNG_LAST1;			//DB ?	;
extern	UNs		KOUSEI_MNG_LAST;			//DB ?	;
extern	UNs		KOUSEI_MNG_LAST1;			//DB ?	;
extern	UNs		SURA_AUTO_MNG_LAST;			//DB ?	;
extern	UNs		SURA_AUTO_MNG_LAST1;		//DB ?	;
extern	UNs		SURA_AUTO_MNG_LAST2;		//DB ?	;

extern	UNs		SEIGAMEN_CNT;				//DB ?	;
extern	UNs		SEGAMEN_ADR;				//DW ?	;

extern	UNs		OFF_SET_MNG_LAST2;			//DB ?	;
extern	UNs		OFF_SET_MNG_LAST3;			//DB ?	;
extern	UNs		OFF_SET_MNG_LASTX;			//DB ?	;
extern	UNs		KOUSEI_MNG_LAST2;			//DB ?	;
extern	UNs		YOUBI_LAST;					//DB ?

extern	UNs		PODATA_SET_FLG;				//DB ?	;

extern	UNs		ONOFF_FLG;					//DB ?	;
extern	UNs		ONOFF_LAST1;				//DB ?	;
extern	UNs		ONOFF_LAST2;				//DB ?	;
extern	UNs		ONOFF_LAST3;				//DB ?	;
extern	UNs		ONOFF_LAST4;				//DB ?	;
extern	UNs		ONOFF_LAST5;				//DB ?	;
extern	UNs		ONOFF_LAST6;				//DB ?	;
//extern	UNs		ONOFF_LAST7;				//DB ?	;
//extern	UNs		ONOFF_LAST8;				//DB ?	;
//extern	UNs		ONOFF_LAST9;				//DB ?	;
//extern	UNs		ONOFF_LAST10;				//DB ?	;

extern	UNs		GAMEN_B6_NON_FLG;			//DB ?	;

extern	UNs		INI_POS_ERR_FLG;			//DB ?	;

extern	UNs		PV_ADBAKD_A14;				//DW ?	;

extern	UNs		ENCO_DATA_BCD;				//DW ?	;
extern	UNs		ENCO_DATA_HEX;				//DW ?	;

extern	UNs		OFFSET_END_FLG;				//DB ?	;/* �I�t�Z�b�g���������H */

extern	UNs		MCN_SEQ_LAST1;				//DB ?		;
extern	UNs		MCN_SEQ_LAST2;				//DB ?		;
extern	UNs		MCN_SEQ_LAST3;				//DB ?		;
extern	UNs		MCN_SEQ_LAST4;				//DB ?		;
extern	UNs		MCN_SEQ_LAST5;				//DB ?		;

extern	UNs		MCN_DATA_NO1;				//DB ?		;
extern	UNs		MCN_DATA_NO2;				//DB ?		;
extern	UNs		MCN_DATA_NO3;				//DB ?		;
extern	UNs		MCN_DATA_NO4;				//DB ?		;
extern	UNs		MCN_DATA_NO5;				//DB ?		;

extern	UNs		MCN_REC_FLG;				//DB ?		;

//extern	UNs		GAMEN_DISP_FLG;				//DB ?	;
extern	UNs		GGAMEN_DISP_FLG;			//DB ?	;

extern	UNs		CARA_CHG_FLG;				//DB ?	;
extern	UNs		YOKOBAI_CNT;				//DW ?	;/* ���{�J�E���^ */
extern	UNs		YOKOBAI_ADR;				//DW ?	;/* ���{�A�h���X */
extern	UNs		YOKO_BAI_WORK[32*16];		//DB 32*16 DUP(?)	;/* �f�[�^�����[�N�̈�֓]�� */

extern	UNs		KAN_BANK_NO;				//DB ?		;V05

extern	UNs		GENGO_CHG_LAST;				//DB ?		;
//extern	UNs		GENGO_CHG_LAST1;			//DB ?		;
extern	UNs		WORK_BUFF_NAME[20];			//DW 20 DUP(?);

extern	UNs		BASE_WORK;					//DW ?		;

extern	UNs		KT_DUMMY_01;				//DW ?	;
extern	UNs		KT_DUMMY_02;				//DB ?	;

extern	UNs		DAI_SVDATA_FLG;				//DB ?	;/* �_�C�n�C�g�����L���H */
extern	UNs		SEQ_023_WK;					//DB ?	;

extern	UNs		AUTO_SEQ_LST;				//DB ?	;

extern	UNs		SV_0401_FLG;				//DB 	?	;
extern	UNs		SV_1101_FLG;				//DB ?	;
extern	UNs		SW_1101_FLG;				//DB ?	;
extern	UNs		SW_1102_FLG;				//DB ?	;
extern	UNs		SW_1103_FLG;				//DB ?	;

extern	UNs		CSR_MLD_WORK[32/2];			//DB 32 DUP(?)	;/* �J�[�\�����ړ�����ƕ����� */

extern	UNs		SIT_MOLD3_RCV_BUFF[50];		//DW	50	DUP(?)	;

extern	UNs		TAIKITEN_DAT;				//DW ?	;/* �ҋ@�_�������烋�[���b�g���ĕ\�� */	EXTRN	TAIKITEN_DAT		: WORD	;/* �ҋ@�_�������烋�[���b�g���ĕ\�� */
extern	UNs		RULET_NOW_LST;				//DW ?	;
extern	UNs		DEG_DISP_LST;				//DW ?	;/* �p�x�ް��ω�����H */
extern	UNl		DEG_DISP_DATA[2];			//DD	?	;
									//DD	?	;

extern	UNs		DEG_LCD_BUFF[32*12];		//DB 32*12 DUP(?)	;/* �p�x�\����p�o�b�t�@ */

extern	UNs		STOPTIME_DISP_LST;			//DW ?	;/* �p�x�ް��ω�����H */
extern	UNl		STOPTIME_DISP_DATA[2];		//DD	?	;
									//DD	?	;

extern	UNs		STOPTIME_LCD_BUFF[32*12];	//DB 32*12 DUP(?)	;/* �p�x�\����p�o�b�t�@ */

extern	UNs		PFOUT_DATA_BAK;				//DB ?	;

extern	UNs		DAT_LCD_KAN_BAK;			//DB ?	;

extern	UNs		DEG_DISP_FLG;				//DB ?	;
//extern	UNs		STOP_DISP_FLG;				//DB ?	;
extern	UNs		RULET_DISP_FLG;				//DB ?	;/* ���[���b�g�\���n�j */
//extern	UNs		RULET_NON_FLG;				//DB ?	;
extern	UNs		CSR_MOVE_OK_FLG;			//DB ?	;/* �J�[�\���ړ��֎~ */

extern	UNs		SW14_ON_FLG;				//DB ?	;
extern	UNs		SW14_ON_CNT;				//DB ?	;
extern	UNs		SET_KEY_LST;				//DB ?	;

extern	UNs		KIDO_FLG_FLG;				//DB 2 DUP(?)	;/* �P�x�f�[�^�Ǎ����i�[ */
extern	UNs		KIDO_FLG_PV;				//DB ?		;/* �P�x�f�[�^�Ǎ����i�[ */

extern	UNs		GAIBU_RST_LAST;				//DB ?	;
//extern	UNs		GAIBU_RST_LAST1;			//DB ?	;
extern	UNs		GAIBU_RST_LAST2;			//DB ?	;
extern	UNs		GAIBU_RST_LAST3;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST4;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST5;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST6;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST7;			//DB ?	;
//extern	UNs		GAIBU_RST_LAST8;			//DB ?	;

//extern	UNs		GAIBU_CHG_FLG;				//DB ?	;

extern	UNs		TAIKITEN_FLG;				//DB ?	;
extern	UNs		TAIKITEN_LAST;				//DB ?
extern	UNs		TAIKITEN_DATA;				//DW ?
extern	UNs		TAIKI_NOW_POS;				//DW ?	;
extern	UNs		TAIKI_ZEN_POS;				//DW ?	;

extern	UNs		COUNT_HOSEI_ADR;			//DW ?	;/* ���]�A�h���X�f�[�^�Ҕ� */
extern	UNs		SURA_HOSEI_ADR;				//DW ?	;/* ���]�A�h���X�f�[�^�Ҕ� */

extern	UNs		SWCHG_DISP_ON_FLG;			//DB ?	;
extern	UNs		SEISAN_SW56_FLG;			//DB ?	;
extern	UNs		SEISAN_SW56_TIM;			//DW ?	;
extern	UNs		OPBAK_UP_LST;				//DB ?	;
extern	UNs		OPBAK_UP_LST1;				//DB ?	;

extern	UNs		SW14_ON1_FLG;				//DB ?	;
extern	UNs		SW14_ON6_FLG;				//DB ?	;
extern	UNs		SW14_ON1_FLG_BAK2;			//DB ?	;
extern	UNs		SW14_ON1_FLG_BAK3;			//DB ?	;
extern	UNs		SW14_ON1_FLG_BAK;			//DB ?	;
extern	UNs		SW14_ON6_FLG_BAK;			//DB ?	;
extern	UNs		SW14_ON6_FLG_BACK;			//DB ?	;

extern	UNs		TAIKI_LST;					//DW ?	;

extern	UNs		CAMNAME_INP_CNT;			//DB ?	;
extern	UNs		NAME_CHG_FLG;				//DB ?	;/* ���̕ύX���H */
extern	UNs		CAM_NAME_NO;				//DB ?	;/* �ύX�J�����̔ԍ��Ǎ� */
extern	UNs		SUOERTH_BUFF[3];			//DW 3 DUP(?)	;

extern	UNs		CSR_FLG_CNT_BAK;			//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
extern	UNs		CSR_FLG_CNT_BAK3;			//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
extern	UNs		SV_FLG_CNT_BAK;				//DW ?	;/* �����l�Z�b�g */
extern	UNs		SW_FLG_CNT_BAK;				//DW ?	;/* �����l�Z�b�g */

extern	UNs		CAMOUT_MUSK;				//DW ?	;/* �ėp�o�̓}�X�N�r�b�g */
extern	UNs		CAMOUT_BIT;					//DW ?	;/* �ėp�o�̓r�b�g */

extern	UNs		GAMEN_NO_CAM;				//DW ?	;
extern	UNs		DAN_WIN_FLG;				//DB ?	;	V01j(ins)
extern	UNs		DAN_CSR_LST;				//DB ?	;

//extern	UNs		SW14_DISP7_NON;				//DB ?	;

extern	UNs		SET_SPM_LST;				//DB ?	;
extern	UNs		KATNAME_INP_CNT;			//DB ?	;/* ���̓J�E���^�[�P */

//extern	UNs		PV_MLDNO1_F0[16];			//DB 16 DUP(?)	;
extern	UNs		PV_MLDNO1_F0;				//DB 16 DUP(?)	;
extern	UNs		PV_MLDNO2_F0[16];			//DB 16 DUP(?)	;

extern	UNs		SINCAM_LST;					//DB ?	;	
extern	UNs		TAIKITEN_FLG_FLG;			//DB ?	;/* ���łɃt���O�𗧂ĂĂ������� */

extern	UNs		CSR_CLS_FLG;				//DB ?	;
extern	UNs		PVCNT_DISP_CNT;				//DB ?	;
extern	UNs		PVALL_FLG;					//DB ?	;
extern	UNs		PVGENNITI_FLG;				//DB ?	;

extern	UNs		CSR_FLG_BUF;				//DW ?	;/*  */
extern	UNs		SV_FLG_BUF;					//DW ?	;/*  */

extern	UNs		ENCO_DATA_HEX1;				//DW ?	;

extern	UNs		RULET_GAKU_FLG;				//DW ?	;
extern	UNs		RULET_GAKU_LST;				//DB ?	;

extern	UNs		SEI_ON6_LST1;				//DB ?	;
extern	UNs		SEI_ON6_LST2;				//DB ?	;
extern	UNs		SEI_ON6_LST3;				//DB ?	;
extern	UNs		SEI_ON6_LST4;				//DB ?	;
extern	UNs		SEI_ON1_LST;				//DB ?	;

extern	UNs		DAN_GAMEN_NON;				//DB ?	;
extern	UNs		SEL_GAMEN_NON;				//DB ?	;
extern	UNs		CAM_GAMEN_NON;				//DB ?	;
extern	UNs		EJE_GAMEN_NON;				//DB ?	;
extern	UNs		MIS_GAMEN_NON;				//DB ?	;
extern	UNs		ROT_GAMEN_NON;				//DB ?	;

extern	UNs		ROT1_GAMEN_NON;				//DB ?	;
extern	UNs		ROT2_GAMEN_NON;				//DB ?	;
extern	UNs		ROT3_GAMEN_NON;				//DB ?	;

extern	UNs		CSR_FLG_CNT_LST;			//DW ?	;/* �J�[�\���ԍ��Z�b�g */

extern	UNs		POWRE_OK_FLG;				//DW ?	;

extern	UNs		PVDATA_NON;					//DB ?	;

extern	UNs		CAR_ROM_SEG;				//DW ?	;

extern	UNs		PV_SUM_CHK;					//DW ?	;
extern	UNs		EE_SUM_CHK;					//DW ?	;

extern	UNs		POWER_DOWN_FLG;				//DB ?	;

extern	UNs		SW56_UPTOP_FLG;				//DB ?	;'98-08-05

//V01u	extern	UNs		KAT_DATCHG_FLG;				//DB ?	;
extern	UNs		KAT_DATCHG_FLG_DUMMY;				//DB ?	;
extern	UNs		KAT_CNTCHG_FLG;				//DB ?	;

extern	UNs		SW14_DISP7_DANNON;			//DB ?	;'98-08-31/*�X���C�h�ȊO�Ȃ��Ƃ��̓W�����v  */
//extern	UNs		OP_NON_FLG;					//DB ?	;

extern	UNs		SYS_HIGHSPM_B1;				//DW ?	;V01a
extern	UNs		SYS_LOWSPM_B1;				//DW ?	;V01a
extern	UNs		RULET_HIGH_FLG;				//DB ?	;/* �������[���b�g�`��t���O�Z�b�g */
extern	UNs		RULET_HIGH_LST;				//DB ?	;
extern	UNs		CB1_SPMDAT_PVV;				//DW ?	;/* �ǂݍ��� */

extern	UNs		PV_TLINKSMP_DAT;			//DW ?	;V03j

extern	UNs		ENC_SPD_CNT;				//DW ?		;
extern	UNl		ENCSPD_ADD;					//DD	?		;
extern	UNs		ENCSPD_BF[20];				//DW	10	DUP (?)	;
									//DW	10	DUP (?)	;

extern	UNs		CSR_DAN_CSR_LST;			//DW ?		;V01a/* �i�����SW56���ݽ��ݾٗp */

extern	UNs		SW56_MUSK_FLG;				//DW ?		;V01b

extern	UNs		MLD_100_GNO;				//DW ?		;MLD100/* �^�Ǘ���ʔԍ������� */
//extern	UNs		MLD_100_NO;					//DW ?		;MLD100/* �^�Ǘ���ʔԍ������� */
extern	UNs		MLD_100_FLG;				//DB ?		;MLD100/* �^�Ǘ��t���O������ */
//extern	UNs		MLD_100_CARD_FLG;			//DB ?		;MLD100/*  */

extern	UNs		MEM_ADR;					//DW ?	;
extern	UNs		MEM_BNK;					//DW ?	;
extern	UNs		MLD_WRITE_BNK;				//DB ?	;

extern	UNs		CSR_POS_G15;				//DB ?	;/*  */

extern	UNs		CSR_MOVE_NON;				//DB ?	;/* �J�[�\���͓����Ȃ��H */

extern	UNs		MLD100_INI_FLG;				//DB ?	;

extern	UNs		DAN_DAN_FLG;				//DB ?	;

extern	UNs		CSR_FLG_CNT_BACK;			//DW ?		;
extern	UNs		WINDOW_NO_BACK;				//DW ? 		;

extern	UNs		DAN_KEY_FLG;				//DB ?		;

extern	UNs		G07_WIN_FLG;				//DB ?		;

extern	UNs		FILCK_CNT;					//DW ?			;
extern	UNs		FILCK_STEP1_FLG;			//DB ?			;
extern	UNs		FILCK_STEP2_FLG;			//DB ?			;
extern	UNs		FILCK_STEP3_FLG;			//DB ?			;

extern	UNs		NEXT_READ_NO;				//DW ?	;/* ���^�ԍ��ݒ�l */

extern	UNs		KEY_DOWN14_FLG;				//DB ?	;/* �j�d�x����������t���O���Z�b�g */
extern	UNs		SW14_MUSK_FLG;				//DW ?	;

extern	UNs		SW14_MUSK_FLG_SW2;			//DW ?	;

extern	UNs		CSR_G07_NO1;				//DW ?	;/* �J�[�\���擪�ʒu�Ɠ����H */
extern	UNs		CSR_G07_NO2;				//DW ?	;/* �J�[�\���擪�ʒu�Ɠ����H */

extern	UNs		SYS_SPMPM_B1P;				//DW ?	;
extern	UNs		SYS_SPMPM_B1M;				//DW ?	;

extern	UNs		SEQ_019_FLG;				//DB ?	;

extern	UNs		SYS_MISSEL_SV;				//DB ?		;

extern	UNs		SURA_SEL_LST;				//DB ?	;

extern	UNs		DAN_CLS_CNT;				//DW ?		;2000-07-04/* �\���������J�E���^ */

extern	UNs		SEI_GAI_LST;				//DB ?
extern	UNs		GENG_SEQ_LST;				//DB ?
extern	UNs		NEXT_MLDSEQ_FLG;			//DB ?		;2001-08-07 /*�V�[�P���X�p���^�f�[�^�ǂݍ��݃t���O�n�m*/

extern	UNs		PV_CAMSW1_C1[4];		//DB 8 DUP(?)	;BIT_1
extern	UNs		PV_CAMSW2_C1[4];		//DB 8 DUP(?)	;BIT_2
extern	UNs		PV_CAMSW3_C1[4];		//DB 8 DUP(?)	;BIT_3
extern	UNs		PV_CAMSW4_C1[4];		//DB 8 DUP(?)	;BIT_4
extern	UNs		PV_CAMSW5_C1[4];		//DB 8 DUP(?)	;BIT_5
extern	UNs		PV_CAMSW6_C1[4];		//DB 8 DUP(?)	;BIT_6
extern	UNs		PV_CAMSW7_C1[4];		//DB 8 DUP(?)	;BIT_7
extern	UNs		PV_CAMSW8_C1[4];		//DB 8 DUP(?)	;BIT_8
extern	UNs		PV_CAMSW9_C1[4];		//DB 8 DUP(?)	;BIT_9
extern	UNs		PV_CAMSWA_C1[4];		//DB 8 DUP(?)	;BIT_A
extern	UNs		PV_CAMSWB_C1[4];		//DB 8 DUP(?)	;BIT_B
extern	UNs		PV_CAMSWC_C1[4];		//DB 8 DUP(?)	;BIT_C
extern	UNs		PV_CAMSWD_C1[4];		//DB 8 DUP(?)	;BIT_D
extern	UNs		PV_CAMSWE_C1[4];		//DB 8 DUP(?)	;BIT_E
extern	UNs		PV_CAMSWF_C1[4];		//DB 8 DUP(?)	;BIT_F

extern	UNs		PV_CAMNA01_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P���� */
extern	UNs		PV_CAMNA02_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���Q���� */
extern	UNs		PV_CAMNA03_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���R���� */
extern	UNs		PV_CAMNA04_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���S���� */
extern	UNs		PV_CAMNA05_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���T���� */
extern	UNs		PV_CAMNA06_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���U���� */
extern	UNs		PV_CAMNA07_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���V���� */
extern	UNs		PV_CAMNA08_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���W���� */
extern	UNs		PV_CAMNA09_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���X���� */
extern	UNs		PV_CAMNA10_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�O���� */
extern	UNs		PV_CAMNA11_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�P���� */
extern	UNs		PV_CAMNA12_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�Q���� */
extern	UNs		PV_CAMNA13_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�R���� */
extern	UNs		PV_CAMNA14_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�S���� */
extern	UNs		PV_CAMNA15_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�T���� */
extern	UNs		PV_CAMNA16_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�U���� */
extern	UNs		PV_CAMNA17_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�V���� */
extern	UNs		PV_CAMNA18_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�W���� */
extern	UNs		PV_CAMNA19_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�X���� */
extern	UNs		PV_CAMNA20_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���Q�O���� */

extern	UNs		PV_KOUMOKU1_NAME[8];	//DB 16 DUP(?)	;
extern	UNs		PV_KOUMOKU2_NAME[8];	//DB 16 DUP(?)	;
extern	UNs		PV_KOUMOKU3_NAME[8];	//DB 16 DUP(?)	;
extern	UNs		PV_KOUMOKU4_NAME[8];	//DB 16 DUP(?)	;

extern	UNs		PV_KINOU01_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU02_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU03_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU04_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU05_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU06_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU07_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU08_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU09_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU10_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU11_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU12_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU13_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU14_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU15_NAE[8];		//DB 16 DUP(?)	;
extern	UNs		PV_KINOU16_NAE[8];		//DB 16 DUP(?)	;

extern	UNs		SEQ_PAR_101_BAK;		/* V00p */
extern	UNs		disp_stg_sel_bak;		/* V00p */
extern	UNs		WINDOW_NO_bak;			/* V00p */
extern	UNs		PV0_PAR_A_CHAR;         /* V00p */    /* ���Ұ��ް�ޮ� ������׸� ASCII */
extern	UNs		PV0_PAR_B_CHAR;         /* V00p */    /* ���Ұ��ް�ޮ� ������׸� ASCII */
extern	UNs		PV0_TBL_A_CHAR;         /* V00p */    /* �ݻ��ð��ٔԍ� ASCII */
extern	UNs		PV0_TBL_B_CHAR;         /* V00p */    /* �ݻ��ð��ٔԍ� ASCII */
extern	UNs		PV0_INTER_VER2;			/* V00p */    /* ����ۯ��ް�ޮ� ������׸� ASCII */
extern	UNs		PV0_DEFULT_VER2;		/* V00p */    /* �����l�ް��ް�ޮ� ������׸� ASCII */
extern	UNs		PV0_SEQ_VER2;			/* V00p */    /* ���ݽ�ް�ޮ� ������׸� ASCII */
extern	UNl		PV0_NOW_POSI000;		/* V00q */    /* �����㍂��PV */
extern	UNl		PV0_DYHITO_POS;			/* V00q */    /* �����ʒuPV */
extern	UNl		PV0_SLIDE_POS;			/* V01  */    /* ���Y����PV */
extern	UNl		PV0_NOWPOSI_SLIDE;		/* V01  */    /* ���Y����or�����㍂PV */

extern	UNs		GAIBU_RST_BAK;			/* V00t */

extern	UNs		PV0_MONALM_P01;
extern	UNs		PV0_MONALM_P02;
extern	UNs		PV0_MONALM_P03;
extern	UNs		PV0_MONALM_P04;
extern	UNs		PV0_MONALM_A01;
extern	UNs		PV0_MONALM_A02;
extern	UNs		PV0_MONALM_A03;
extern	UNs		PV0_MONALM_A04;
extern	UNs		PV0_MONALM_A05;
extern	UNs		PV0_MONALM_A06;
extern	UNs		PV0_MONALM_A07;
extern	UNs		PV0_MONALM_A08;
extern	UNs		PV0_MONALM_B01;
extern	UNs		PV0_MONALM_B02;
extern	UNs		PV0_MONALM_B03;
extern	UNs		PV0_MONALM_B04;
extern	UNs		PV0_MONALM_B05;
extern	UNs		PV0_MONALM_B06;
extern	UNs		PV0_MONALM_B07;
extern	UNs		PV0_MONALM_B08;
extern	UNl		PV0_MONALM_C01;
extern	UNl		PV0_MONALM_C02;
extern	UNl		PV0_MONALM_C03;
extern	UNl		PV0_MONALM_C04;
extern	UNl		PV0_MONALM_C05;
extern	UNl		PV0_MONALM_C06;
extern	UNl		PV0_MONALM_C07;
extern	UNl		PV0_MONALM_C08;
extern	UNs		PV0_MONALM_B01_SIGN;
extern	UNs		PV0_MONALM_B02_SIGN;
extern	UNs		PV0_MONALM_B03_SIGN;
extern	UNs		PV0_MONALM_B04_SIGN;
extern	UNs		PV0_MONALM_B05_SIGN;
extern	UNs		PV0_MONALM_B06_SIGN;
extern	UNs		PV0_MONALM_B07_SIGN;
extern	UNs		PV0_MONALM_B08_SIGN;
extern	UNs		PV0_MONALM_C01_SIGN;
extern	UNs		PV0_MONALM_C02_SIGN;
extern	UNs		PV0_MONALM_C03_SIGN;
extern	UNs		PV0_MONALM_C04_SIGN;
extern	UNs		PV0_MONALM_C05_SIGN;
extern	UNs		PV0_MONALM_C06_SIGN;
extern	UNs		PV0_MONALM_C07_SIGN;
extern	UNs		PV0_MONALM_C08_SIGN;

extern	UNs		MOTION_SV_CHG_CANCEL;			/* V01d */

extern	UNs		TAIKIKAKU_CHG_FLG;				/* V01i */
extern	UNs		GAMNE_REDISP_COD;				/* V01i */

extern	UNs		SEQ_PAR_107_BAK;				/* V01j */
extern	UNs		SEQ_PAR_427_CHG;				/* V01j */
extern	UNs		SEQ_PAR_427_ONE;				/* V01j */
extern	UNs		SEQ_PAR_427_OFE;				/* V01j */
extern	UNs		SEQ_PAR_427_BAK;				/* V01j */
extern	UNs		autokana_sw56_bak;				/* V01j */
extern	UNs		ADC_DISP_FLG;					/* V01j */
extern	UNs		ADC_CHG_LST;					/* V01j */
extern	UNs		ADC_CHG_LST1;					/* V01j */
extern	UNs		ADC_CHG_LST2;					/* V01j */
extern	UNs		ADC_CHG_LST3;					/* V01j */
extern	UNs		ADC_CHG_LST4;					/* V01j */
extern	UNs		ADC_CHG_LST5;					/* V01j */
extern	UNs		ADC_CHG_LST2_2;					/* V01j */
extern	UNs		ADC_MODE_FLG;					/* V01j */
extern	UNs		ADC_STEP_FLG;					/* V01j */
extern	UNs		ADC_STPCHG_FLG;					/* V01j */
extern	UNs		ADC_FILCK_LST;					/* V01j */
extern	UNs		ADC_SW2_FLG;					/* V01j */
extern	UNs		ADC_SW34_FLG;					/* V01j */
extern	UNs		ADC_SW5_FLG;					/* V01j */
extern	UNs		ADC_SW6_FLG;					/* V01j */
extern	UNs		SW14_DISP7_NON;					/* V01j */
extern	UNs		ADC_STEP_NO[4];					/* V01j */
extern	UNs		ADC_STEP_NO_LAST[4];			/* V01j */
extern	UNs		step_flick_flg;					/* V01j */
extern	UNs		step_flick_flg_bak;				/* V01j */
extern	UNs		step_flick_cnt;					/* V01j */

extern	UNl		CAR_LNG_KAJ_AREA;				/* V01k */
extern	UNs		SYO_LNG_KAJ_CNT;				/* V01k */

extern	UNl		PV0_KAGEN_POSITIONER;			/* V01l_b */

extern	UNs		SYO_LNG_SUR_CNT;				/* V01m */

extern	UNs		DEB_WORD_FLG1;					/* V01n_b */
extern	UNs		DEB_WORD_FLG2;					/* V01n_b */
extern	UNs		DEB_WORD_FLG3;					/* V01n_b */
extern	UNs		DEB_WORD_FLG4;					/* V01n_b */
extern	UNs		DEB_WORD_FLG5;					/* V01n_b */
extern	UNs		DEB_WORD_FLG6;					/* V01n_b */
extern	UNs		DEB_WORD_FLG7;					/* V01n_b */
extern	UNs		DEB_WORD_FLG8;					/* V01n_b */
extern	UNs		DEB_WORD_FLG9;					/* V01n_b */
extern	UNs		DEB_WORD_FLG10;					/* V01n_b */
extern	UNs		DEB_WORD_FLG11;					/* V01n_b */
extern	UNs		DEB_WORD_FLG12;					/* V01n_b */
extern	UNs		DEB_WORD_FLG13;					/* V01n_b */
extern	UNs		DEB_WORD_FLG14;					/* V01n_b */
extern	UNs		DEB_WORD_FLG15;					/* V01n_b */
extern	UNs		DEB_WORD_FLG16;					/* V01n_b */

//��������������	�ȉ��A�r�h�s�|�S�Œǉ�		��������������
extern	UNl		DEBUG_CNT;

extern	UNs		CSR_BAK_M_LEN;	
extern	UNs		CSR_BAK_X_POS;	
extern	UNs		CSR_BAK_Y_POS;	
extern	UNs		CSR_BAK_C_COL;	
extern	UNs		CSR_BAK_B_COL;	
extern	UNs		CSR_BAK_SIZE;	
extern	UNs		*CSR_BAK_G_P;	

extern	GAMENn_HEAD_st	GAMENn_HEAD;
extern	DISP_INFO_st	DISP_INFO;

extern	UNl		CHR_TABLE_ADR;			// �L�����N�^�e�[�u���̕�����L�����N�^�擪�A�h���X
extern	UNl		CSR_TABLE_ADR;			// �L�����N�^�e�[�u���̃J�[�\���L�����N�^�擪�A�h���X
extern	UNl		SWL_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^�擪�A�h���X
extern	UNl		S56_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^�擪�A�h���X
extern	UNl		MES_TABLE_ADR;			// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^�擪�A�h���X
extern	UNl		S56U_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�T�E�U��i�L�����N�^�擪�A�h���X
extern	UNl		SPE_TABLE_ADR;			// �L�����N�^�e�[�u���̓��ʃL�����N�^�擪�A�h���X

extern	UNl		GAMENN_MOJ_INF_ADR;		// ��ʂ��̕�������̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
extern	UNl		GAMENN_CSR_INF_ADR;		// ��ʂ��̃J�[�\�����̐擪�A�h���X		�i��ʂ���\������Ƃ��ɎZ�o�j
extern	UNl		GAMENN_SVP_INF_ADR;		// ��ʂ��̐ݒ�l���̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
extern	UNl		GAMENN_PVP_INF_ADR;		// ��ʂ��̎����l���̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
extern	UNl		GAMENN_SWL_INF_ADR;		// ��ʂ��̂r�v�|�k�`�l�o�̐擪�A�h���X		�i��ʂ���\������Ƃ��ɎZ�o�j
extern	UNl		GAMENN_GRP_INF_ADR;		// ��ʂ��̃O���t�B�b�N���̐擪�A�h���X	�i��ʂ���\������Ƃ��ɎZ�o�j

extern	UNs		CHRTBL_CHR_CNT;			// �L�����N�^�e�[�u���̕�����L�����N�^��
extern	UNs		CHRTBL_CSR_CNT;			// �L�����N�^�e�[�u���̃J�[�\���L�����N�^��
extern	UNs		CHRTBL_SWL_CNT;			// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^��
extern	UNs		CHRTBL_S56_CNT;			// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^��
extern	UNs		CHRTBL_MES_CNT;			// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^��
extern	UNs		CHRTBL_S56U_CNT;		// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^��
extern	UNs		CHRTBL_SPE_CNT;			// �L�����N�^�e�[�u���̓��ʃL�����N�^��

extern	UNs		GAMENn_SCR_COL;			//��ʂ̽�ذݐF�iWindow��\�����ĕς��Ȃ����Ɓj

extern	UNs		PVW_ZURE_PLS_SIN;		//���Խ�ڎ�������
extern	UNs		PVW_ZURE_RNA_SIN;		//���Խ���Ʊ����
extern	UNs		PVW_ZURE_PLS;			//���Խ�ڎ���
extern	UNs		PVW_ZURE_RNA;			//���Խ���Ʊ
extern	UNs		PVW_BAKORG_SIN1;		//�ޯ����ߎ�������
extern	UNs		PVW_BAKORG_SIN2;		//�ޯ����ߎ�������
extern	UNl		SVBW_BAKORG_PLS1;		//�Ʊ��ʒu��ٽ	COP2
extern	UNl		SVBW_BAKORG_PLS2;		//�Ʊ��ʒu��ٽ	COP2

extern	UNs		GAM_CHG_WIN_NO_BAK;		/* V04a */

extern	UNb		OP_STATUS;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H			//V01e
extern	UNb		OP_STATUS_DUM;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H		//V01e

extern	UNb		MEM_ARI;				//DB	?		; OP��:A5H		//V05h

extern	UNs		PV0_CB_C_VER[6];		//ASCII�ް� (1WORD�ŷ�׸����� 6char) SH4-->
extern	UNs		PV0_PAR_C_CHAR;			//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
extern	UNs		PV0_TBL_C_CHAR;			//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)

//;	******** 2007/12/12 ***********
extern	UNs		PV0_IPM_ADR0;			//IP���ڽ(���)
extern	UNs		PV0_IPM_ADR1;			//IP���ڽ(���)
extern	UNs		PV0_IPM_ADR2;			//IP���ڽ(���)
extern	UNs		PV0_IPM_ADR3;			//IP���ڽ(���)

//;	******** 2009/07/14 ***********
extern	UNs		IROCK_OUT_NO[8];			/* ����ۯ������ԍ�		*/
extern	UNb		IROCK_CHAR[8][8];			/* ����ۯ������ԍ��ɑ΂��鷬׸�����		*/

//;	******** 2009/08/-- *********** V05o(INS)	�����g�`�\���p
extern	UNs		WAVE_SAMP_DTP[2];					//���������ݸޔg�`�`��ʒu�߲��		+0:�ŐV  +1:�O��l
extern	UNs		WAVE_TRND_DTP[2];					//��������ޔg�`�`��ʒu�߲��		+0:�ŐV  +1:�O��l
extern	WAVE_SAMP_DATA_ST	WAVE_SAMP_DATA[501];	//���������ݸޔg�`�p�ް�
extern	WAVE_TRND_DATA_ST	WAVE_TRND_DATA[5001];	//��������ޔg�`�p�ް�
extern	WAVE_SAMP_DOT_ST	WAVE_SAMP_DOT[501];		//���������ݸޔg�`�p�ް�
extern	WAVE_TRND_DOT_ST	WAVE_TRND_DOT[5001];	//��������ޔg�`�p�ް�
extern	UNs		CSR_PVSAMP[2];						//���������ݸޔg�`��ʂ̶��وʒu	+0:�ŐV  +1:�O��l
extern	UNs		CSR_PVTRND[2];						//��������ޔg�`��ʂ̶��وʒu		+0:�ŐV  +1:�O��l
extern	UNs		PW_Key_up[4];						//�����g�`��ʗp�������ω�	(5ms�����݂ŊĎ�)
extern	UNs		PW_Key_dn[4];						//�����g�`��ʗp��������ω�	(5ms�����݂ŊĎ�)
extern	UNs		PW_Key_last[4];						//�����g�`��ʗp���O��l		(5ms�����݂ŊĎ�)
extern	UNs		PW_Key_tim02[4];					//�����g�`��ʗp������������	(5ms�����݂ŊĎ�)
extern	UNs		PW_Key_tim30[4];					//�����g�`��ʗp������������	(5ms�����݂ŊĎ�)
extern	UNs		PV0_SMPCSR_KJT;						//���وʒu�̍��v�׏d
extern	UNs		PV0_SMPCSR_KJL;						//���وʒu�̍��׏d
extern	UNs		PV0_SMPCSR_KJR;						//���وʒu�̉E�׏d
extern	UNs		PV0_SMPCSR_AGL;						//���وʒu�̊p�x
extern	UNl		PV0_SMPCSR_RNA1;					//���وʒu�̽ײ�ވʒu
extern	UNl		PV0_SMPCSR_RNA2;					//���وʒu�̽ײ�ވʒu
extern	UNs		PV0_SMPCSR_SEQ0;					//���وʒu�̼��ݽ
extern	UNs		PV0_SMPCSR_SEQ1;					//���وʒu�̼��ݽ
extern	UNs		PV0_SMPCSR_TIM;						//���وʒu�̎���
extern	UNs		PV0_SMPCSR_POS;						//���وʒu���߲��
extern	UNl		PV0_TRDCSR_RNAU;					//�ײ�ޏ�����o�ʒu
extern	UNl		PV0_TRDCSR_RNAD;					//�ײ�މ������o�ʒu
extern	UNs		PV0_TRDCSR_KJT;						//���وʒu�̍��v�׏d
extern	UNs		PV0_TRDCSR_KJL;						//���وʒu�̍��׏d
extern	UNs		PV0_TRDCSR_KJR;						//���وʒu�̉E�׏d
extern	UNl		PV0_TRDCSR_RNA1;					//���وʒu�̽ײ�ވʒu
extern	UNl		PV0_TRDCSR_RNA2;					//���وʒu�̽ײ�ވʒu
extern	UNs		PV0_TRDCSR_TIM;						//���وʒu�̎���
extern	UNs		PV0_TRDCSR_POS;						//���وʒu���߲��
extern	UNs		PV0_TRDCSR_POSL;					//�-�͈ٔ�
extern	UNs		PV0_TRDCSR_POSR;					//�-�͈ٔ�

//;	******** 2010/08/10~ *********** V05r(INS)
extern	UNs		SEIDOU_SEQ_LST;						//
extern	UNs		sys_1min_cnt;						//1min����
//extern	UNs		PVTIM_seidouseinou_inter;			//�������\��������������(1min�޸�������)
//extern	UNs		PVTIM_seidouseinou_yokok;			//�������\�����\�����(1min�޸�������)
extern	UNs		SYO_HOS_KAJ_CNT;
extern	UNs		PV0_INTER_TIM;						//�������\��������������(1h�޸�������)

//;	******** 2010/08/31~ *********** V06 (INS)
extern	UNl		INTR_DAT_OFS;
extern	UNl		INIT_DAT_OFS;
extern	UNl		ALL_CHR_TBL_OFS;
extern	UNl		GAM_INF_TBL_OFS;
extern	UNs		EcoMeter_bit;
extern	UNs		PV0_EPMCSR_HOR;
extern	UNs		PV0_EPMCSR_MIN;
extern	UNl		PV0_EPMCSR_UEP;
extern	UNl		PV0_EPMCSR_KEP;
extern	UNl		PV0_EPMCSR_TEP;
extern	UNl		PV0_EPML_SCRH;
extern	UNl		PV0_EPML_SCRM;
extern	UNl		PV0_EPML_SCRL;
extern	UNl		PV0_EPMR_SCRH;
extern	UNl		PV0_EPMR_SCRM;
extern	UNl		PV0_EPMR_SCRL;
extern	UNl		PV0_EPM_KWH[20][3];					//�d�̓��j�^�p�O���t�f�[�^
extern	UNs		EPM_CSR[2];							//�d�̓��j�^�p�J�[�\���ʒu
extern	UNs		EPM_TIM_BAK;						//�P�ʎ���
extern	UNl		EPM_GRP_MXL;						//�_�O���t�ő�l�ς�����H
extern	UNl		EPM_GRP_MXR;						//�܂���O���t�ő�l�ς�����H
extern	UNs		sys_1sec_cnt;						//1sec����

//extern	UNl		EPM_SEC_60ADD[2];					//����d�͗� 60sec�ώZ(kWs)
//extern	UNs		EPM_SEC_60CNT;
//extern	UNl		EPM_HOR_BUF[24*60][2];				//����d�͗� 1440��(kWs)
//extern	UNs		EPM_HOR_POI;
extern	UNs		EPM_GAMEN_RIF;						//�d�̓��j�^��ʃ��t���b�V���t���O

extern	UNl		PV0_SMPCSR_EP;						//�����ݸޔg�`��ʶ��وʒu�̏u���d��
extern	int		PV0_SMPCSR_EP_SIN;					//�����ݸޔg�`��ʶ��وʒu�̏u���d��		//V06a
extern	UNl		PV0_TRDCSR_EP;						//����ޔg�`���   ���وʒu�̓d�͗�

extern	UNs		SEIDOU_DSP_LST;

extern	UNs		PV0_INTER_VER1;						/* ����ۯ��ް�ޮ� ���l */
extern	UNs		PV0_DEFULT_VER1;					/* �����l�ް��ް�ޮ� ���l */

extern	UNs		PV0_EPMDAT_SIN;						//�����ݸޔg�`��ʂ̓d�͒l����BIT
extern	UNs		EPM_TOTAL_INF;						//�d�������ʗ݌v�l�ؑւ̕\�����			//V06a
extern	UNs		EPM_TLINF_BAK;						//�d�������ʗ݌v�l�ؑւ̕\�����			//V06a
extern	UNs		EPM_CLR_TIM;						//�d����������ް��ر���						//V06a
extern	UNs		EPM_CLR_FLG;						//�d������ر��t�׸�						//V06a
extern	UNs		EPM_GAMRIF_CNT;						//�d����������گ�����ݸ޶ݳ�				//V06a

extern	UNs		SV0_EP_AVE;


extern	UNl		EPM_SEC_2_MESMIN_ADD[2];
extern	UNs		EPM_SEC_MESMIN_CNT;

extern	UNl		EPM_05MIN_BUF[5/5][2] ;
extern	UNl		EPM_10MIN_BUF[10/5][2];
extern	UNl		EPM_15MIN_BUF[15/5][2];
extern	UNl		EPM_20MIN_BUF[20/5][2];
extern	UNl		EPM_25MIN_BUF[25/5][2];
extern	UNl		EPM_30MIN_BUF[30/5][2];
extern	UNl		EPM_35MIN_BUF[35/5][2];
extern	UNl		EPM_40MIN_BUF[40/5][2];
extern	UNl		EPM_45MIN_BUF[45/5][2];
extern	UNl		EPM_50MIN_BUF[50/5][2];
extern	UNl		EPM_55MIN_BUF[55/5][2];
extern	UNl		EPM_60MIN_BUF[60/5][2];

extern	UNs		EPM_05MIN_POI;
extern	UNs		EPM_10MIN_POI;
extern	UNs		EPM_15MIN_POI;
extern	UNs		EPM_20MIN_POI;
extern	UNs		EPM_25MIN_POI;
extern	UNs		EPM_30MIN_POI;
extern	UNs		EPM_35MIN_POI;
extern	UNs		EPM_40MIN_POI;
extern	UNs		EPM_45MIN_POI;
extern	UNs		EPM_50MIN_POI;
extern	UNs		EPM_55MIN_POI;
extern	UNs		EPM_60MIN_POI;

extern	UNl		EPM_05MON_BUF[20][2];
extern	UNl		EPM_10MON_BUF[20][2];
extern	UNl		EPM_15MON_BUF[20][2];
extern	UNl		EPM_20MON_BUF[20][2];
extern	UNl		EPM_25MON_BUF[20][2];
extern	UNl		EPM_30MON_BUF[20][2];
extern	UNl		EPM_35MON_BUF[20][2];
extern	UNl		EPM_40MON_BUF[20][2];
extern	UNl		EPM_45MON_BUF[20][2];
extern	UNl		EPM_50MON_BUF[20][2];
extern	UNl		EPM_55MON_BUF[20][2];
extern	UNl		EPM_60MON_BUF[20][2];

extern	UNs		EPM_05MON_POI;
extern	UNs		EPM_10MON_POI;
extern	UNs		EPM_15MON_POI;
extern	UNs		EPM_20MON_POI;
extern	UNs		EPM_25MON_POI;
extern	UNs		EPM_30MON_POI;
extern	UNs		EPM_35MON_POI;
extern	UNs		EPM_40MON_POI;
extern	UNs		EPM_45MON_POI;
extern	UNs		EPM_50MON_POI;
extern	UNs		EPM_55MON_POI;
extern	UNs		EPM_60MON_POI;

//;	******** 2010/12/06 *********** V06b (INS)
extern	UNs		rulet_taiki_pos1;			//���]�A�U��q���̑ҋ@�_
extern	UNs		rulet_taiki_pos2;			//		�U��q���̑ҋ@�_
extern	UNl		SV0_TAL1_CNT;				//İ�ٶ����C���l
extern	UNl		SV0_LOT1_CNT;				//ۯĶ���1�C���l
extern	UNl		SV0_LOT2_CNT;				//ۯĶ���2�C���l

//;	******** 2011/01/02 *********** V06c (INS)
extern	UNs		SV0_WORKER_COD_BAK	;		//��ƎҺ��ޑޔ�
extern	UNl		SV0_ORDER_COD_BAK	;		//���Ժ��ޑޔ�
extern	UNl		SV0_PLAN_CNT_BAK		;		//�v�搔�ޔ�
extern	UNs		SV0_WORKER_COD		;		//��ƎҺ��ގ擾
extern	UNl		SV0_ORDER_COD		;		//���Ժ��ގ擾
extern	UNl		SV0_PLAN_CNT		;		//�v�搔�擾

extern	UNs		SV0_WORK_STR_FLG		;	//��ƊJ�n�׸ށito C/B�p�j
extern	UNs		SV0SP_WORKER_COD	;		//��ƊJ�n����ƎҺ���
extern	UNl		SV0SP_ORDER_COD		;		//��ƊJ�n�����Ժ���
extern	UNl		SV0SP_PLAN_CNT		;		//��ƊJ�n���v�搔
extern	UNl		SV0SP_BAD_CNT		;		//��ƊJ�n���s�ǐ�
extern	UNs		SV0SP_KATA_NO		;		//��ƊJ�n���^�ԍ�
extern	UNs		SV0SP_KATA_NAME[7]	;		//��ƊJ�n���^����
extern	UNs		SV0SP_KATA_MEMO[7]	;		//��ƊJ�n���^����

extern	UNs		SV0_WORK_STP_FLG		;	//��ƏI���׸ށito C/B�p�j
extern	UNs		SV0SR_WORKER_COD	;		//��ƏI������ƎҺ���
extern	UNl		SV0SR_ORDER_COD		;		//��ƏI�������Ժ���
extern	UNl		SV0SR_PLAN_CNT		;		//��ƏI�����v�搔
extern	UNl		SV0SR_BAD_CNT		;		//��ƏI�����s�ǐ�
extern	UNs		SV0SR_KATA_NO		;		//��ƏI�����^�ԍ�
extern	UNs		SV0SR_KATA_NAME[7]	;		//��ƏI�����^����
extern	UNs		SV0SR_KATA_MEMO[7]	;		//��ƏI�����^����

extern	UNs		KAT_RD_CSR_POS	;			//�^�Ǐo������CSR_TBL_POS_NOW

//;	******** 2012/09/24 *********** V06m (INS)
extern	UNs		DIEH_OFS_FLG;
extern	UNs		FURIKO_FLG;

//;	******** 2012/10/15 *********** V06n (INS)
extern	UNl		SV0_RNAPOS_MAXO;
extern	UNl		SV0_RNAPOS_MINO;
extern	UNs		SV0_DAIHAI_LNG1O;
extern	UNs		SV0_DAIHAI_LNG2O;
extern	UNs		MOT_MODE_BAK;

//;	******** 2013/02/18 *********** V06p (INS)
extern	UNs		PV0_CKSPD_OVBIT;
extern	UNs		PV0_KATRD_BIT;
extern	UNs		TEST_SEQ;
extern	UNs		FURIKO_SEQ_LST;

//;	******** 2013/12/11 *********** SIT4-MC
extern	UNb		*VRAM_Dst8;
extern	UNs		*VRAM_Dst;
extern	UNb		*VRAM_Src;
extern	UNb		*VRAM_End;
extern	UNs		GAM_COPY_FLG;
extern	UNs		GAM_COPY_STS;

//;	******** 2014/02/06 *********** SIT4-MC
extern	UNs		IROCK_COL_CHG_NO;

//;	******** 2014/03/13 *********** SIT4-MC
extern	UNs		SMP_KAJ_MAX_SIN;
extern	UNs		SMP_KAJ_MIN_SIN;
extern	UNs		SMP_EP_MAX_SIN;
extern	UNs		SMP_EP_MIN_SIN;
extern	UNs		TRD_KAJ_MAX_SIN;
extern	UNs		TRD_KAJ_MIN_SIN;
extern	UNs		TRD_EP_MAX_SIN;
extern	UNs		TRD_EP_MIN_SIN;
extern	UNs		OVER_LOAD_SEL;
extern	UNs		LOW_LIMIT_SEL;
extern	UNs		SV0_OVLD_SEL;
extern	UNs		SV0_LWLM_SEL;
extern	UNs		MEM_KAJ_SEL;

//;	******** 2014/04/15 *********** SIT4-MC
extern	UNs		PV0_CKAGL_OVBIT;

//;	******** 2014/06/04 *********** SIT4-MC
extern	UNs		SLDTUN_RNA_SEL ;

//;	******** 2014/08/20 ***********
extern	UNl		CAR_MICRO_KAJ_AREA;

//;	******** 2014/08/26 SIT4-MC ***********
extern	UNl		SV0_RELE_POS	;			//�����[�X����
extern	UNs		SV0_RELE_SNO0	;			//�����[�X�J���I���s��
extern	UNs		SV0_RELE_AGL0	;			//�����[�X�J���I���p�x
extern	UNs		SV0_RELE_SNO1	;			//�����[�X�J���I�t�s��
extern	UNs		SV0_RELE_AGL1	;			//�����[�X�J���I�t�p�x
extern	UNs		SV0_RELE_CAM	;			//�����[�X�J���ݒ�Ώ�
extern	UNl		SV0_SEND_POS	;			//���荂��
extern	UNs		SV0_SEND_SNO0	;			//����J���I���s��
extern	UNs		SV0_SEND_AGL0	;			//����J���I���p�x
extern	UNs		SV0_SEND_SNO1	;			//����J���I�t�s��
extern	UNs		SV0_SEND_AGL1	;			//����J���I�t�p�x
extern	UNs		SV0_SEND_CAM	;			//����J���ݒ�Ώ�
extern	UNs		SV0_TIMING_SNO0	;			//�^�C�~���O�J���I���s��
extern	UNs		SV0_TIMING_AGL0	;			//�^�C�~���O�J���I���p�x
extern	UNs		SV0_TIMING_SNO1	;			//�^�C�~���O�J���I�t�s��
extern	UNs		SV0_TIMING_AGL1	;			//�^�C�~���O�J���I�t�p�x
extern	UNs		SV0_TIMING_CAM	;			//�^�C�~���O�J���ݒ�Ώ�
extern	UNs		PV0_CAMATCAL_MES1;			//�J���������Z�ݒ�s���̃��b�Z�[�W�ԍ�
extern	UNs		PV0_CAMATCAL_MES2;			//�J���������Z�ݒ�s���̃��b�Z�[�W�ԍ�
extern	UNs		PV0_CAMATCAL_MES3;			//�J���������Z�ݒ�s���̃��b�Z�[�W�ԍ�
extern	UNs		PV0_MOTION_INF;				//BIT0�FӰ��݂ɒ�~�s��������B
extern	UNs		PV0_SINKAKU_UPDN1;			//BITn�F۰�ض�n��ON�i�p���������͈͂ɂ���B
extern	UNs		PV0_SINKAKU_UPDN2;			//BITn�F۰�ض�n��OFF�i�p���������͈͂ɂ���B

extern	UNs		SV0_MOT_REP;				//���[�V�����̃��s�[�g���
extern	UNs		SV0_MOT_FIX;				//���[�V�����̈��̈���
extern	UNs		SV0_FIXARA_AGLS;			//���̈�@�J�n�p�x
extern	UNl		SV0_FIXARA_POSS;			//���̈�@�J�n�ʒu
extern	UNs		SV0_FIXARA_SPDB;			//���̈�@�J�n�O���x
extern	UNs		SV0_FIXARA_SPDF;			//���̈�@��葬�x
extern	UNs		SV0_FIXARA_AGLE;			//���̈�@�I���p�x
extern	UNl		SV0_FIXARA_POSE;			//���̈�@�I���ʒu
extern	UNs		PV0_FIXBF_SPD;				//���̈�@�J�n�O���x

extern	UNs		PV0_CAMATCAL_FLG;			//�J���o�͎����ݒ�t���O�N���A			2014/09/12

extern	UNs		SV0_REP_FIX_FLG;			//�J��Ԃ��^���̈�  �L���^�����׸�	2014/09/23
extern	UNs		MOT_FERR_TIM;				//F�}��ERR�M��ON����					2014/09/25

extern	UNs		PV0_FMOTSET_MES1;			//��葬�x�ݒ莞�̃��b�Z�[�W�ԍ�		2014/10/09

//;	******** 2015/01/14 ***********
extern	UNs		SV_1DANPRS_SRV;             /* 1�i�ږڕW�׏d */
extern	UNs		SV_2DANPRS_SRV;             /* 2�i�ږڕW�׏d */
extern	UNs		SV_3DANPRS_SRV;             /* 3�i�ږڕW�׏d */
extern	UNs		SV_4DANPRS_SRV;             /* 4�i�ږڕW�׏d */
extern	UNs		SV_5DANPRS_SRV;             /* 5�i�ږڕW�׏d */
extern	UNs		SV_6DANPRS_SRV;             /* 6�i�ږڕW�׏d */
extern	UNs		SV_7DANPRS_SRV;             /* 7�i�ږڕW�׏d */
extern	UNs		SV_8DANPRS_SRV;             /* 8�i�ږڕW�׏d */
extern	UNs		SV_9DANPRS_SRV;             /* 9�i�ږڕW�׏d */
extern	UNs		SV_10DANPRS_SRV;            /* 10�i�ږڕW�׏d */
#if (mot100_test == 1)
extern	UNs		SV_11DANPRS_SRV;            /* 11�i�ږڕW�׏d */
extern	UNs		SV_12DANPRS_SRV;            /* 12�i�ږڕW�׏d */
extern	UNs		SV_13DANPRS_SRV;            /* 13�i�ږڕW�׏d */
extern	UNs		SV_14DANPRS_SRV;            /* 14�i�ږڕW�׏d */
extern	UNs		SV_15DANPRS_SRV;            /* 15�i�ږڕW�׏d */
extern	UNs		SV_16DANPRS_SRV;            /* 16�i�ږڕW�׏d */
extern	UNs		SV_17DANPRS_SRV;            /* 17�i�ږڕW�׏d */
extern	UNs		SV_18DANPRS_SRV;            /* 18�i�ږڕW�׏d */
extern	UNs		SV_19DANPRS_SRV;            /* 19�i�ږڕW�׏d */
extern	UNs		SV_20DANPRS_SRV;            /* 20�i�ږڕW�׏d */
extern	UNs		SV_21DANPRS_SRV;            /* 21�i�ږڕW�׏d */
extern	UNs		SV_22DANPRS_SRV;            /* 22�i�ږڕW�׏d */
extern	UNs		SV_23DANPRS_SRV;            /* 23�i�ږڕW�׏d */
extern	UNs		SV_24DANPRS_SRV;            /* 24�i�ږڕW�׏d */
extern	UNs		SV_25DANPRS_SRV;            /* 25�i�ږڕW�׏d */
extern	UNs		SV_26DANPRS_SRV;            /* 26�i�ږڕW�׏d */
extern	UNs		SV_27DANPRS_SRV;            /* 27�i�ږڕW�׏d */
extern	UNs		SV_28DANPRS_SRV;            /* 28�i�ږڕW�׏d */
extern	UNs		SV_29DANPRS_SRV;            /* 29�i�ږڕW�׏d */
extern	UNs		SV_30DANPRS_SRV;            /* 30�i�ږڕW�׏d */
extern	UNs		SV_31DANPRS_SRV;            /* 31�i�ږڕW�׏d */
extern	UNs		SV_32DANPRS_SRV;            /* 32�i�ږڕW�׏d */
extern	UNs		SV_33DANPRS_SRV;            /* 33�i�ږڕW�׏d */
extern	UNs		SV_34DANPRS_SRV;            /* 34�i�ږڕW�׏d */
extern	UNs		SV_35DANPRS_SRV;            /* 35�i�ږڕW�׏d */
extern	UNs		SV_36DANPRS_SRV;            /* 36�i�ږڕW�׏d */
extern	UNs		SV_37DANPRS_SRV;            /* 37�i�ږڕW�׏d */
extern	UNs		SV_38DANPRS_SRV;            /* 38�i�ږڕW�׏d */
extern	UNs		SV_39DANPRS_SRV;            /* 39�i�ږڕW�׏d */
extern	UNs		SV_40DANPRS_SRV;            /* 40�i�ږڕW�׏d */
extern	UNs		SV_41DANPRS_SRV;            /* 41�i�ږڕW�׏d */
extern	UNs		SV_42DANPRS_SRV;            /* 42�i�ږڕW�׏d */
extern	UNs		SV_43DANPRS_SRV;            /* 43�i�ږڕW�׏d */
extern	UNs		SV_44DANPRS_SRV;            /* 44�i�ږڕW�׏d */
extern	UNs		SV_45DANPRS_SRV;            /* 45�i�ږڕW�׏d */
extern	UNs		SV_46DANPRS_SRV;            /* 46�i�ږڕW�׏d */
extern	UNs		SV_47DANPRS_SRV;            /* 47�i�ږڕW�׏d */
extern	UNs		SV_48DANPRS_SRV;            /* 48�i�ږڕW�׏d */
extern	UNs		SV_49DANPRS_SRV;            /* 49�i�ږڕW�׏d */
extern	UNs		SV_50DANPRS_SRV;            /* 50�i�ږڕW�׏d */
extern	UNs		SV_51DANPRS_SRV;            /* 51�i�ږڕW�׏d */
extern	UNs		SV_52DANPRS_SRV;            /* 52�i�ږڕW�׏d */
extern	UNs		SV_53DANPRS_SRV;            /* 53�i�ږڕW�׏d */
extern	UNs		SV_54DANPRS_SRV;            /* 54�i�ږڕW�׏d */
extern	UNs		SV_55DANPRS_SRV;            /* 55�i�ږڕW�׏d */
extern	UNs		SV_56DANPRS_SRV;            /* 56�i�ږڕW�׏d */
extern	UNs		SV_57DANPRS_SRV;            /* 57�i�ږڕW�׏d */
extern	UNs		SV_58DANPRS_SRV;            /* 58�i�ږڕW�׏d */
extern	UNs		SV_59DANPRS_SRV;            /* 59�i�ږڕW�׏d */
extern	UNs		SV_60DANPRS_SRV;            /* 60�i�ږڕW�׏d */
extern	UNs		SV_61DANPRS_SRV;            /* 61�i�ږڕW�׏d */
extern	UNs		SV_62DANPRS_SRV;            /* 62�i�ږڕW�׏d */
extern	UNs		SV_63DANPRS_SRV;            /* 63�i�ږڕW�׏d */
extern	UNs		SV_64DANPRS_SRV;            /* 64�i�ږڕW�׏d */
extern	UNs		SV_65DANPRS_SRV;            /* 65�i�ږڕW�׏d */
extern	UNs		SV_66DANPRS_SRV;            /* 66�i�ږڕW�׏d */
extern	UNs		SV_67DANPRS_SRV;            /* 67�i�ږڕW�׏d */
extern	UNs		SV_68DANPRS_SRV;            /* 68�i�ږڕW�׏d */
extern	UNs		SV_69DANPRS_SRV;            /* 69�i�ږڕW�׏d */
extern	UNs		SV_70DANPRS_SRV;            /* 70�i�ږڕW�׏d */
extern	UNs		SV_71DANPRS_SRV;            /* 71�i�ږڕW�׏d */
extern	UNs		SV_72DANPRS_SRV;            /* 72�i�ږڕW�׏d */
extern	UNs		SV_73DANPRS_SRV;            /* 73�i�ږڕW�׏d */
extern	UNs		SV_74DANPRS_SRV;            /* 74�i�ږڕW�׏d */
extern	UNs		SV_75DANPRS_SRV;            /* 75�i�ږڕW�׏d */
extern	UNs		SV_76DANPRS_SRV;            /* 76�i�ږڕW�׏d */
extern	UNs		SV_77DANPRS_SRV;            /* 77�i�ږڕW�׏d */
extern	UNs		SV_78DANPRS_SRV;            /* 78�i�ږڕW�׏d */
extern	UNs		SV_79DANPRS_SRV;            /* 79�i�ږڕW�׏d */
extern	UNs		SV_80DANPRS_SRV;            /* 80�i�ږڕW�׏d */
extern	UNs		SV_81DANPRS_SRV;            /* 81�i�ږڕW�׏d */
extern	UNs		SV_82DANPRS_SRV;            /* 82�i�ږڕW�׏d */
extern	UNs		SV_83DANPRS_SRV;            /* 83�i�ږڕW�׏d */
extern	UNs		SV_84DANPRS_SRV;            /* 84�i�ږڕW�׏d */
extern	UNs		SV_85DANPRS_SRV;            /* 85�i�ږڕW�׏d */
extern	UNs		SV_86DANPRS_SRV;            /* 86�i�ږڕW�׏d */
extern	UNs		SV_87DANPRS_SRV;            /* 87�i�ږڕW�׏d */
extern	UNs		SV_88DANPRS_SRV;            /* 88�i�ږڕW�׏d */
extern	UNs		SV_89DANPRS_SRV;            /* 89�i�ږڕW�׏d */
extern	UNs		SV_90DANPRS_SRV;            /* 90�i�ږڕW�׏d */
extern	UNs		SV_91DANPRS_SRV;            /* 91�i�ږڕW�׏d */
extern	UNs		SV_92DANPRS_SRV;            /* 92�i�ږڕW�׏d */
extern	UNs		SV_93DANPRS_SRV;            /* 93�i�ږڕW�׏d */
extern	UNs		SV_94DANPRS_SRV;            /* 94�i�ږڕW�׏d */
extern	UNs		SV_95DANPRS_SRV;            /* 95�i�ږڕW�׏d */
extern	UNs		SV_96DANPRS_SRV;            /* 96�i�ږڕW�׏d */
extern	UNs		SV_97DANPRS_SRV;            /* 97�i�ږڕW�׏d */
extern	UNs		SV_98DANPRS_SRV;            /* 98�i�ږڕW�׏d */
extern	UNs		SV_99DANPRS_SRV;            /* 99�i�ږڕW�׏d */
extern	UNs		SV_100DANPRS_SRV;           /* 100�i�ږڕW�׏d */
#endif
extern	UNs		SV_KAJOBJ_HAB;				/* �׏d�����͈� */

//;	******** 2015/01/20 ***********
extern	UNs		TANNI_SEQ_LST;

//;	******** 2015/05/19 ***********
extern	UNs		TRND_DTP_FLG;
extern	UNs		chk_kjofs_dat[10];

//;	******** 2015/07/10 ***********
extern	UNs		PV0_CKSPD_LMBIT;

//;	******** ���[�V����100�i�Ή� ***********
#if (mot100_test == 1)
extern	UNs		SV_MOTTGT_INF0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNs		SV_MOTTGT_INF1;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNs		SV_MOTTGT_INF2;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNs		SV_MOTTGT_INF3;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNs		SV_MOTTGT_INF4;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNs		SV_MOTTGT_INF5;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNs		SV_MOTTGT_INF6;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
extern	UNl		CAR_DO_AREA;				//�P��(��)
extern	UNl		CAR_PAR_AREA;				//�P��(%)
extern	UNl		CAR_TIM_AREA;				//�P��(s)
extern	UNs		SV0_DISP_STEP_NO[5];		//���[�V������ʂ̕\������s��No.
extern	UNs		PV0_MOT_ACT_STEP;			//���[�V������ʂŎ��s�s���̃r�b�g���i���\���p�j
extern	UNs		csr_disp_wk[16];

//extern	UNs		PVP_CKAGL_OVBIT1[7];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//extern	UNs		PVP_CKLMT_AGLTOP1[100];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//extern	UNs		PVP_CKSPD_OVBIT1[7];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//extern	UNs		PVP_CKLMT_SPDTOP1[100];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//extern	UNs		PVP_CKSPD_LMBIT1[7];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j

extern	UNs		MOT_CHG_NO[5];
extern	UNs		MOT_SEND_NO;
#endif

//;	******** �@�������ʂ̓��͐����Ή� ***********		2016/02/24
extern	UNs		SV0_RNAORG_ENB1;				//�@�B���_���́i���͋��j
extern	UNs		SV0_ORGCAL_ENB2;				//�@�ԁi���͋��j
extern	UNs		SV0_ORGCAL_ENB1;				//�@��i���͋��j
extern	UNs		SV0_MACINE_ENB1;				//�p�x�l�ؑցi���͋��j
extern	UNs		SV0_OFSET_ENB;					//�̾�Ē����i���͋��j
extern	UNs		SV0_KOUSEI_ENB;					//�׏d�Z���i���͋��j
extern	UNs		SV0_MAXHIZ_ENB;					//�ő�c�i���͋��j
extern	UNs		SV0_MAXKAJ_ENB;					//�ő�׏d�i���͋��j
extern	UNs		SV0_KOUKAJ_ENB;					//�Z���׏d�i���͋��j

//;	******** �t�B�[�_�Ή� ***********		2016/03/18
extern	UNl		PV0_LFEED_POS;					//����̨��ތ��݈ʒu
extern	UNs		SV0_LFEED_SEL;					//����̨��ޗL��
extern	UNs		SV0_LFEED_HSIS;					//����̨��ދ����ʓ�������
extern	UNs		SV0_LFEED_HSOS;					//����̨��ދ����ʏo������
extern	UNb		PV0_LFEED_TYPE[16];				//����̨��ތ^��ASCII
extern	UNs		SYS0_FEED_PAR_BLK[32];			//���݂�����̨��ފ֘A��ROM���

//;	******** Ӱ���10�i��100�i�Ή� ***********		2016/04/01
extern	UNs		kata_mot010_work[0x800/2];
extern	UNs		kata_mot100_work[0x1800/2];

//;	******** Ӱ��݉������Ή� ***********		2016/04/14
extern	UNs		SV0_MOT_UDSEL;					//�������L���^����
extern	UNs		SV0_MOT_BFAF;					//���[�V�����\���y�[�W5�i���̉��������
extern	UNs		SV_MOT_CSUD_INF0;				//���������i1�`16�s���j
extern	UNs		SV_MOT_CSUD_INF1;				//���������i17�`32�s���j
extern	UNs		SV_MOT_CSUD_INF2;				//���������i33�`48�s���j
extern	UNs		SV_MOT_CSUD_INF3;				//���������i49�`64�s���j
extern	UNs		SV_MOT_CSUD_INF4;				//���������i65�`80�s���j
extern	UNs		SV_MOT_CSUD_INF5;				//���������i81�`96�s���j
extern	UNs		SV_MOT_CSUD_INF6;				//���������i97�`100�s���j

//;	******** ���Ӌ@�A���@�\�ǉ��d�l ***********		2016/04/22
extern	UNs		SQ_ORIDE_BAK;
extern	UNs		TLINK_NEXT_LAST;
extern	UNs		TLINK_NEXT_LAST1;
extern	UNs		TLINK_NEXT_NO;
extern	UNs		ADC_SW5_ON_FLG;
extern	UNs		ADC_SW6_ON_FLG;

//;	******** ���i���[�V�����ݒ�d�l ***********		2016/09/17
extern	UNs		PV0_MSSET_MES1;
extern	UNs		PV0_MSSET_STG1;

