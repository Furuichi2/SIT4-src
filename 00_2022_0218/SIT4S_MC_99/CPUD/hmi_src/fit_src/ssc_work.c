
#include "ssc_ver1.h"							//�e��̋��ʒ�`
#include "ssc_def.h"							//�e��̋��ʒ�`


#pragma section	wkram1	// 2010-09-21 wdt-up�΍� �����=����Bwkram1

/*==========================================================================*/
/*		�e�X�g�p�̉���`													*/
/*==========================================================================*/
//UNs		OP_STATUS_DT;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H

/*==========================================================================*/
/*		�V���[�N�̈��`�iSit-S�j											*/
/*==========================================================================*/
UNi		SVPV_LCD_FLG;							//�ݒ�l�������l��LCD�\���׸�(00���\���^00����\��)
UNs		SV_DANSUU_SRV_BAK;						//�H���� �Z�[�u
//UNs		SV_TAIKIKAKU_SRV_BAK;					//�ҋ@�p�̊i�[
//UNl		SV_TAIKIPOS_SRV_BAK;					//�ҋ@�ʒu�̊i�[
#if (mot100_test == 1)
UNs		SV_MOT_PAGE;				//
#endif

UNl		SV_TAIKIPOS_SRV;            /* �ҋ@�ʒu */
UNs		SV_KAITEN_SRV;              /* ��]���� */
UNs		SV_DANSUU_SRV;              /* �i�� */
UNs		SV_TAIKIKAKU_SRV;           /* �ҋ@�p */
UNs		SV_TAIKSPD_SRV;             /* ����x */
UNl		SV_DAIHAITO_SRV;            /* �_�C�n�C�g */
UNs		SV_HOASEI_SRV;              /* �␳�f�[�^ */
UNs		SV_TAIKTIM_SRV;             /* �ҋ@���� */
UNs		SV_1DANDEG_SRV;             /* 1�i�ږڕW�p�x */
UNs		SV_2DANDEG_SRV;             /* 2�i�ږڕW�p�x */
UNs		SV_3DANDEG_SRV;             /* 3�i�ږڕW�p�x */
UNs		SV_4DANDEG_SRV;             /* 4�i�ږڕW�p�x */
UNs		SV_5DANDEG_SRV;             /* 5�i�ږڕW�p�x */
UNs		SV_6DANDEG_SRV;             /* 6�i�ږڕW�p�x */
UNs		SV_7DANDEG_SRV;             /* 7�i�ږڕW�p�x */
UNs		SV_8DANDEG_SRV;             /* 8�i�ږڕW�p�x */
UNs		SV_9DANDEG_SRV;             /* 9�i�ږڕW�p�x */
UNs		SV_10DANDEG_SRV;            /* 10�i�ږڕW�p�x */
#if (mot100_test == 1)
UNs		SV_11DANDEG_SRV;            /* 11�i�ږڕW�p�x */
UNs		SV_12DANDEG_SRV;            /* 12�i�ږڕW�p�x */
UNs		SV_13DANDEG_SRV;            /* 13�i�ږڕW�p�x */
UNs		SV_14DANDEG_SRV;            /* 14�i�ږڕW�p�x */
UNs		SV_15DANDEG_SRV;            /* 15�i�ږڕW�p�x */
UNs		SV_16DANDEG_SRV;            /* 16�i�ږڕW�p�x */
UNs		SV_17DANDEG_SRV;            /* 17�i�ږڕW�p�x */
UNs		SV_18DANDEG_SRV;            /* 18�i�ږڕW�p�x */
UNs		SV_19DANDEG_SRV;            /* 19�i�ږڕW�p�x */
UNs		SV_20DANDEG_SRV;            /* 20�i�ږڕW�p�x */
UNs		SV_21DANDEG_SRV;            /* 21�i�ږڕW�p�x */
UNs		SV_22DANDEG_SRV;            /* 22�i�ږڕW�p�x */
UNs		SV_23DANDEG_SRV;            /* 23�i�ږڕW�p�x */
UNs		SV_24DANDEG_SRV;            /* 24�i�ږڕW�p�x */
UNs		SV_25DANDEG_SRV;            /* 25�i�ږڕW�p�x */
UNs		SV_26DANDEG_SRV;            /* 26�i�ږڕW�p�x */
UNs		SV_27DANDEG_SRV;            /* 27�i�ږڕW�p�x */
UNs		SV_28DANDEG_SRV;            /* 28�i�ږڕW�p�x */
UNs		SV_29DANDEG_SRV;            /* 29�i�ږڕW�p�x */
UNs		SV_30DANDEG_SRV;            /* 30�i�ږڕW�p�x */
UNs		SV_31DANDEG_SRV;            /* 31�i�ږڕW�p�x */
UNs		SV_32DANDEG_SRV;            /* 32�i�ږڕW�p�x */
UNs		SV_33DANDEG_SRV;            /* 33�i�ږڕW�p�x */
UNs		SV_34DANDEG_SRV;            /* 34�i�ږڕW�p�x */
UNs		SV_35DANDEG_SRV;            /* 35�i�ږڕW�p�x */
UNs		SV_36DANDEG_SRV;            /* 36�i�ږڕW�p�x */
UNs		SV_37DANDEG_SRV;            /* 37�i�ږڕW�p�x */
UNs		SV_38DANDEG_SRV;            /* 38�i�ږڕW�p�x */
UNs		SV_39DANDEG_SRV;            /* 39�i�ږڕW�p�x */
UNs		SV_40DANDEG_SRV;            /* 40�i�ږڕW�p�x */
UNs		SV_41DANDEG_SRV;            /* 41�i�ږڕW�p�x */
UNs		SV_42DANDEG_SRV;            /* 42�i�ږڕW�p�x */
UNs		SV_43DANDEG_SRV;            /* 43�i�ږڕW�p�x */
UNs		SV_44DANDEG_SRV;            /* 44�i�ږڕW�p�x */
UNs		SV_45DANDEG_SRV;            /* 45�i�ږڕW�p�x */
UNs		SV_46DANDEG_SRV;            /* 46�i�ږڕW�p�x */
UNs		SV_47DANDEG_SRV;            /* 47�i�ږڕW�p�x */
UNs		SV_48DANDEG_SRV;            /* 48�i�ږڕW�p�x */
UNs		SV_49DANDEG_SRV;            /* 49�i�ږڕW�p�x */
UNs		SV_50DANDEG_SRV;            /* 50�i�ږڕW�p�x */
UNs		SV_51DANDEG_SRV;            /* 51�i�ږڕW�p�x */
UNs		SV_52DANDEG_SRV;            /* 52�i�ږڕW�p�x */
UNs		SV_53DANDEG_SRV;            /* 53�i�ږڕW�p�x */
UNs		SV_54DANDEG_SRV;            /* 54�i�ږڕW�p�x */
UNs		SV_55DANDEG_SRV;            /* 55�i�ږڕW�p�x */
UNs		SV_56DANDEG_SRV;            /* 56�i�ږڕW�p�x */
UNs		SV_57DANDEG_SRV;            /* 57�i�ږڕW�p�x */
UNs		SV_58DANDEG_SRV;            /* 58�i�ږڕW�p�x */
UNs		SV_59DANDEG_SRV;            /* 59�i�ږڕW�p�x */
UNs		SV_60DANDEG_SRV;            /* 60�i�ږڕW�p�x */
UNs		SV_61DANDEG_SRV;            /* 61�i�ږڕW�p�x */
UNs		SV_62DANDEG_SRV;            /* 62�i�ږڕW�p�x */
UNs		SV_63DANDEG_SRV;            /* 63�i�ږڕW�p�x */
UNs		SV_64DANDEG_SRV;            /* 64�i�ږڕW�p�x */
UNs		SV_65DANDEG_SRV;            /* 65�i�ږڕW�p�x */
UNs		SV_66DANDEG_SRV;            /* 66�i�ږڕW�p�x */
UNs		SV_67DANDEG_SRV;            /* 67�i�ږڕW�p�x */
UNs		SV_68DANDEG_SRV;            /* 68�i�ږڕW�p�x */
UNs		SV_69DANDEG_SRV;            /* 69�i�ږڕW�p�x */
UNs		SV_70DANDEG_SRV;            /* 70�i�ږڕW�p�x */
UNs		SV_71DANDEG_SRV;            /* 71�i�ږڕW�p�x */
UNs		SV_72DANDEG_SRV;            /* 72�i�ږڕW�p�x */
UNs		SV_73DANDEG_SRV;            /* 73�i�ږڕW�p�x */
UNs		SV_74DANDEG_SRV;            /* 74�i�ږڕW�p�x */
UNs		SV_75DANDEG_SRV;            /* 75�i�ږڕW�p�x */
UNs		SV_76DANDEG_SRV;            /* 76�i�ږڕW�p�x */
UNs		SV_77DANDEG_SRV;            /* 77�i�ږڕW�p�x */
UNs		SV_78DANDEG_SRV;            /* 78�i�ږڕW�p�x */
UNs		SV_79DANDEG_SRV;            /* 79�i�ږڕW�p�x */
UNs		SV_80DANDEG_SRV;            /* 80�i�ږڕW�p�x */
UNs		SV_81DANDEG_SRV;            /* 81�i�ږڕW�p�x */
UNs		SV_82DANDEG_SRV;            /* 82�i�ږڕW�p�x */
UNs		SV_83DANDEG_SRV;            /* 83�i�ږڕW�p�x */
UNs		SV_84DANDEG_SRV;            /* 84�i�ږڕW�p�x */
UNs		SV_85DANDEG_SRV;            /* 85�i�ږڕW�p�x */
UNs		SV_86DANDEG_SRV;            /* 86�i�ږڕW�p�x */
UNs		SV_87DANDEG_SRV;            /* 87�i�ږڕW�p�x */
UNs		SV_88DANDEG_SRV;            /* 88�i�ږڕW�p�x */
UNs		SV_89DANDEG_SRV;            /* 89�i�ږڕW�p�x */
UNs		SV_90DANDEG_SRV;            /* 90�i�ږڕW�p�x */
UNs		SV_91DANDEG_SRV;            /* 91�i�ږڕW�p�x */
UNs		SV_92DANDEG_SRV;            /* 92�i�ږڕW�p�x */
UNs		SV_93DANDEG_SRV;            /* 93�i�ږڕW�p�x */
UNs		SV_94DANDEG_SRV;            /* 94�i�ږڕW�p�x */
UNs		SV_95DANDEG_SRV;            /* 95�i�ږڕW�p�x */
UNs		SV_96DANDEG_SRV;            /* 96�i�ږڕW�p�x */
UNs		SV_97DANDEG_SRV;            /* 97�i�ږڕW�p�x */
UNs		SV_98DANDEG_SRV;            /* 98�i�ږڕW�p�x */
UNs		SV_99DANDEG_SRV;            /* 99�i�ږڕW�p�x */
UNs		SV_100DANDEG_SRV;           /* 100�i�ږڕW�p�x */
#endif
UNl		SV_1DANPOS_SRV;             /* 1�i�ږڕW�ʒu */
UNl		SV_2DANPOS_SRV;             /* 2�i�ږڕW�ʒu */
UNl		SV_3DANPOS_SRV;             /* 3�i�ږڕW�ʒu */
UNl		SV_4DANPOS_SRV;             /* 4�i�ږڕW�ʒu */
UNl		SV_5DANPOS_SRV;             /* 5�i�ږڕW�ʒu */
UNl		SV_6DANPOS_SRV;             /* 6�i�ږڕW�ʒu */
UNl		SV_7DANPOS_SRV;             /* 7�i�ږڕW�ʒu */
UNl		SV_8DANPOS_SRV;             /* 8�i�ږڕW�ʒu */
UNl		SV_9DANPOS_SRV;             /* 9�i�ږڕW�ʒu */
UNl		SV_10DANPOS_SRV;            /* 10�i�ږڕW�ʒu */
#if (mot100_test == 1)
UNl		SV_11DANPOS_SRV;            /* 11�i�ږڕW�ʒu */
UNl		SV_12DANPOS_SRV;            /* 12�i�ږڕW�ʒu */
UNl		SV_13DANPOS_SRV;            /* 13�i�ږڕW�ʒu */
UNl		SV_14DANPOS_SRV;            /* 14�i�ږڕW�ʒu */
UNl		SV_15DANPOS_SRV;            /* 15�i�ږڕW�ʒu */
UNl		SV_16DANPOS_SRV;            /* 16�i�ږڕW�ʒu */
UNl		SV_17DANPOS_SRV;            /* 17�i�ږڕW�ʒu */
UNl		SV_18DANPOS_SRV;            /* 18�i�ږڕW�ʒu */
UNl		SV_19DANPOS_SRV;            /* 19�i�ږڕW�ʒu */
UNl		SV_20DANPOS_SRV;            /* 20�i�ږڕW�ʒu */
UNl		SV_21DANPOS_SRV;            /* 21�i�ږڕW�ʒu */
UNl		SV_22DANPOS_SRV;            /* 22�i�ږڕW�ʒu */
UNl		SV_23DANPOS_SRV;            /* 23�i�ږڕW�ʒu */
UNl		SV_24DANPOS_SRV;            /* 24�i�ږڕW�ʒu */
UNl		SV_25DANPOS_SRV;            /* 25�i�ږڕW�ʒu */
UNl		SV_26DANPOS_SRV;            /* 26�i�ږڕW�ʒu */
UNl		SV_27DANPOS_SRV;            /* 27�i�ږڕW�ʒu */
UNl		SV_28DANPOS_SRV;            /* 28�i�ږڕW�ʒu */
UNl		SV_29DANPOS_SRV;            /* 29�i�ږڕW�ʒu */
UNl		SV_30DANPOS_SRV;            /* 30�i�ږڕW�ʒu */
UNl		SV_31DANPOS_SRV;            /* 31�i�ږڕW�ʒu */
UNl		SV_32DANPOS_SRV;            /* 32�i�ږڕW�ʒu */
UNl		SV_33DANPOS_SRV;            /* 33�i�ږڕW�ʒu */
UNl		SV_34DANPOS_SRV;            /* 34�i�ږڕW�ʒu */
UNl		SV_35DANPOS_SRV;            /* 35�i�ږڕW�ʒu */
UNl		SV_36DANPOS_SRV;            /* 36�i�ږڕW�ʒu */
UNl		SV_37DANPOS_SRV;            /* 37�i�ږڕW�ʒu */
UNl		SV_38DANPOS_SRV;            /* 38�i�ږڕW�ʒu */
UNl		SV_39DANPOS_SRV;            /* 39�i�ږڕW�ʒu */
UNl		SV_40DANPOS_SRV;            /* 40�i�ږڕW�ʒu */
UNl		SV_41DANPOS_SRV;            /* 41�i�ږڕW�ʒu */
UNl		SV_42DANPOS_SRV;            /* 42�i�ږڕW�ʒu */
UNl		SV_43DANPOS_SRV;            /* 43�i�ږڕW�ʒu */
UNl		SV_44DANPOS_SRV;            /* 44�i�ږڕW�ʒu */
UNl		SV_45DANPOS_SRV;            /* 45�i�ږڕW�ʒu */
UNl		SV_46DANPOS_SRV;            /* 46�i�ږڕW�ʒu */
UNl		SV_47DANPOS_SRV;            /* 47�i�ږڕW�ʒu */
UNl		SV_48DANPOS_SRV;            /* 48�i�ږڕW�ʒu */
UNl		SV_49DANPOS_SRV;            /* 49�i�ږڕW�ʒu */
UNl		SV_50DANPOS_SRV;            /* 50�i�ږڕW�ʒu */
UNl		SV_51DANPOS_SRV;            /* 51�i�ږڕW�ʒu */
UNl		SV_52DANPOS_SRV;            /* 52�i�ږڕW�ʒu */
UNl		SV_53DANPOS_SRV;            /* 53�i�ږڕW�ʒu */
UNl		SV_54DANPOS_SRV;            /* 54�i�ږڕW�ʒu */
UNl		SV_55DANPOS_SRV;            /* 55�i�ږڕW�ʒu */
UNl		SV_56DANPOS_SRV;            /* 56�i�ږڕW�ʒu */
UNl		SV_57DANPOS_SRV;            /* 57�i�ږڕW�ʒu */
UNl		SV_58DANPOS_SRV;            /* 58�i�ږڕW�ʒu */
UNl		SV_59DANPOS_SRV;            /* 59�i�ږڕW�ʒu */
UNl		SV_60DANPOS_SRV;            /* 60�i�ږڕW�ʒu */
UNl		SV_61DANPOS_SRV;            /* 61�i�ږڕW�ʒu */
UNl		SV_62DANPOS_SRV;            /* 62�i�ږڕW�ʒu */
UNl		SV_63DANPOS_SRV;            /* 63�i�ږڕW�ʒu */
UNl		SV_64DANPOS_SRV;            /* 64�i�ږڕW�ʒu */
UNl		SV_65DANPOS_SRV;            /* 65�i�ږڕW�ʒu */
UNl		SV_66DANPOS_SRV;            /* 66�i�ږڕW�ʒu */
UNl		SV_67DANPOS_SRV;            /* 67�i�ږڕW�ʒu */
UNl		SV_68DANPOS_SRV;            /* 68�i�ږڕW�ʒu */
UNl		SV_69DANPOS_SRV;            /* 69�i�ږڕW�ʒu */
UNl		SV_70DANPOS_SRV;            /* 70�i�ږڕW�ʒu */
UNl		SV_71DANPOS_SRV;            /* 71�i�ږڕW�ʒu */
UNl		SV_72DANPOS_SRV;            /* 72�i�ږڕW�ʒu */
UNl		SV_73DANPOS_SRV;            /* 73�i�ږڕW�ʒu */
UNl		SV_74DANPOS_SRV;            /* 74�i�ږڕW�ʒu */
UNl		SV_75DANPOS_SRV;            /* 75�i�ږڕW�ʒu */
UNl		SV_76DANPOS_SRV;            /* 76�i�ږڕW�ʒu */
UNl		SV_77DANPOS_SRV;            /* 77�i�ږڕW�ʒu */
UNl		SV_78DANPOS_SRV;            /* 78�i�ږڕW�ʒu */
UNl		SV_79DANPOS_SRV;            /* 79�i�ږڕW�ʒu */
UNl		SV_80DANPOS_SRV;            /* 80�i�ږڕW�ʒu */
UNl		SV_81DANPOS_SRV;            /* 81�i�ږڕW�ʒu */
UNl		SV_82DANPOS_SRV;            /* 82�i�ږڕW�ʒu */
UNl		SV_83DANPOS_SRV;            /* 83�i�ږڕW�ʒu */
UNl		SV_84DANPOS_SRV;            /* 84�i�ږڕW�ʒu */
UNl		SV_85DANPOS_SRV;            /* 85�i�ږڕW�ʒu */
UNl		SV_86DANPOS_SRV;            /* 86�i�ږڕW�ʒu */
UNl		SV_87DANPOS_SRV;            /* 87�i�ږڕW�ʒu */
UNl		SV_88DANPOS_SRV;            /* 88�i�ږڕW�ʒu */
UNl		SV_89DANPOS_SRV;            /* 89�i�ږڕW�ʒu */
UNl		SV_90DANPOS_SRV;            /* 90�i�ږڕW�ʒu */
UNl		SV_91DANPOS_SRV;            /* 91�i�ږڕW�ʒu */
UNl		SV_92DANPOS_SRV;            /* 92�i�ږڕW�ʒu */
UNl		SV_93DANPOS_SRV;            /* 93�i�ږڕW�ʒu */
UNl		SV_94DANPOS_SRV;            /* 94�i�ږڕW�ʒu */
UNl		SV_95DANPOS_SRV;            /* 95�i�ږڕW�ʒu */
UNl		SV_96DANPOS_SRV;            /* 96�i�ږڕW�ʒu */
UNl		SV_97DANPOS_SRV;            /* 97�i�ږڕW�ʒu */
UNl		SV_98DANPOS_SRV;            /* 98�i�ږڕW�ʒu */
UNl		SV_99DANPOS_SRV;            /* 99�i�ږڕW�ʒu */
UNl		SV_100DANPOS_SRV;           /* 100�i�ږڕW�ʒu */
#endif
UNs		SV_1DANSPD_SRV;             /* 1�i�ڈړ����x */
UNs		SV_2DANSPD_SRV;             /* 2�i�ڈړ����x */
UNs		SV_3DANSPD_SRV;             /* 3�i�ڈړ����x */
UNs		SV_4DANSPD_SRV;             /* 4�i�ڈړ����x */
UNs		SV_5DANSPD_SRV;             /* 5�i�ڈړ����x */
UNs		SV_6DANSPD_SRV;             /* 6�i�ڈړ����x */
UNs		SV_7DANSPD_SRV;             /* 7�i�ڈړ����x */
UNs		SV_8DANSPD_SRV;             /* 8�i�ڈړ����x */
UNs		SV_9DANSPD_SRV;             /* 9�i�ڈړ����x */
UNs		SV_10DANSPD_SRV;            /* 10�i�ڈړ����x */
#if (mot100_test == 1)
UNs		SV_11DANSPD_SRV;            /* 11�i�ڈړ����x */
UNs		SV_12DANSPD_SRV;            /* 12�i�ڈړ����x */
UNs		SV_13DANSPD_SRV;            /* 13�i�ڈړ����x */
UNs		SV_14DANSPD_SRV;            /* 14�i�ڈړ����x */
UNs		SV_15DANSPD_SRV;            /* 15�i�ڈړ����x */
UNs		SV_16DANSPD_SRV;            /* 16�i�ڈړ����x */
UNs		SV_17DANSPD_SRV;            /* 17�i�ڈړ����x */
UNs		SV_18DANSPD_SRV;            /* 18�i�ڈړ����x */
UNs		SV_19DANSPD_SRV;            /* 19�i�ڈړ����x */
UNs		SV_20DANSPD_SRV;            /* 20�i�ڈړ����x */
UNs		SV_21DANSPD_SRV;            /* 21�i�ڈړ����x */
UNs		SV_22DANSPD_SRV;            /* 22�i�ڈړ����x */
UNs		SV_23DANSPD_SRV;            /* 23�i�ڈړ����x */
UNs		SV_24DANSPD_SRV;            /* 24�i�ڈړ����x */
UNs		SV_25DANSPD_SRV;            /* 25�i�ڈړ����x */
UNs		SV_26DANSPD_SRV;            /* 26�i�ڈړ����x */
UNs		SV_27DANSPD_SRV;            /* 27�i�ڈړ����x */
UNs		SV_28DANSPD_SRV;            /* 28�i�ڈړ����x */
UNs		SV_29DANSPD_SRV;            /* 29�i�ڈړ����x */
UNs		SV_30DANSPD_SRV;            /* 30�i�ڈړ����x */
UNs		SV_31DANSPD_SRV;            /* 31�i�ڈړ����x */
UNs		SV_32DANSPD_SRV;            /* 32�i�ڈړ����x */
UNs		SV_33DANSPD_SRV;            /* 33�i�ڈړ����x */
UNs		SV_34DANSPD_SRV;            /* 34�i�ڈړ����x */
UNs		SV_35DANSPD_SRV;            /* 35�i�ڈړ����x */
UNs		SV_36DANSPD_SRV;            /* 36�i�ڈړ����x */
UNs		SV_37DANSPD_SRV;            /* 37�i�ڈړ����x */
UNs		SV_38DANSPD_SRV;            /* 38�i�ڈړ����x */
UNs		SV_39DANSPD_SRV;            /* 39�i�ڈړ����x */
UNs		SV_40DANSPD_SRV;            /* 40�i�ڈړ����x */
UNs		SV_41DANSPD_SRV;            /* 41�i�ڈړ����x */
UNs		SV_42DANSPD_SRV;            /* 42�i�ڈړ����x */
UNs		SV_43DANSPD_SRV;            /* 43�i�ڈړ����x */
UNs		SV_44DANSPD_SRV;            /* 44�i�ڈړ����x */
UNs		SV_45DANSPD_SRV;            /* 45�i�ڈړ����x */
UNs		SV_46DANSPD_SRV;            /* 46�i�ڈړ����x */
UNs		SV_47DANSPD_SRV;            /* 47�i�ڈړ����x */
UNs		SV_48DANSPD_SRV;            /* 48�i�ڈړ����x */
UNs		SV_49DANSPD_SRV;            /* 49�i�ڈړ����x */
UNs		SV_50DANSPD_SRV;            /* 50�i�ڈړ����x */
UNs		SV_51DANSPD_SRV;            /* 51�i�ڈړ����x */
UNs		SV_52DANSPD_SRV;            /* 52�i�ڈړ����x */
UNs		SV_53DANSPD_SRV;            /* 53�i�ڈړ����x */
UNs		SV_54DANSPD_SRV;            /* 54�i�ڈړ����x */
UNs		SV_55DANSPD_SRV;            /* 55�i�ڈړ����x */
UNs		SV_56DANSPD_SRV;            /* 56�i�ڈړ����x */
UNs		SV_57DANSPD_SRV;            /* 57�i�ڈړ����x */
UNs		SV_58DANSPD_SRV;            /* 58�i�ڈړ����x */
UNs		SV_59DANSPD_SRV;            /* 59�i�ڈړ����x */
UNs		SV_60DANSPD_SRV;            /* 60�i�ڈړ����x */
UNs		SV_61DANSPD_SRV;            /* 61�i�ڈړ����x */
UNs		SV_62DANSPD_SRV;            /* 62�i�ڈړ����x */
UNs		SV_63DANSPD_SRV;            /* 63�i�ڈړ����x */
UNs		SV_64DANSPD_SRV;            /* 64�i�ڈړ����x */
UNs		SV_65DANSPD_SRV;            /* 65�i�ڈړ����x */
UNs		SV_66DANSPD_SRV;            /* 66�i�ڈړ����x */
UNs		SV_67DANSPD_SRV;            /* 67�i�ڈړ����x */
UNs		SV_68DANSPD_SRV;            /* 68�i�ڈړ����x */
UNs		SV_69DANSPD_SRV;            /* 69�i�ڈړ����x */
UNs		SV_70DANSPD_SRV;            /* 70�i�ڈړ����x */
UNs		SV_71DANSPD_SRV;            /* 71�i�ڈړ����x */
UNs		SV_72DANSPD_SRV;            /* 72�i�ڈړ����x */
UNs		SV_73DANSPD_SRV;            /* 73�i�ڈړ����x */
UNs		SV_74DANSPD_SRV;            /* 74�i�ڈړ����x */
UNs		SV_75DANSPD_SRV;            /* 75�i�ڈړ����x */
UNs		SV_76DANSPD_SRV;            /* 76�i�ڈړ����x */
UNs		SV_77DANSPD_SRV;            /* 77�i�ڈړ����x */
UNs		SV_78DANSPD_SRV;            /* 78�i�ڈړ����x */
UNs		SV_79DANSPD_SRV;            /* 79�i�ڈړ����x */
UNs		SV_80DANSPD_SRV;            /* 80�i�ڈړ����x */
UNs		SV_81DANSPD_SRV;            /* 81�i�ڈړ����x */
UNs		SV_82DANSPD_SRV;            /* 82�i�ڈړ����x */
UNs		SV_83DANSPD_SRV;            /* 83�i�ڈړ����x */
UNs		SV_84DANSPD_SRV;            /* 84�i�ڈړ����x */
UNs		SV_85DANSPD_SRV;            /* 85�i�ڈړ����x */
UNs		SV_86DANSPD_SRV;            /* 86�i�ڈړ����x */
UNs		SV_87DANSPD_SRV;            /* 87�i�ڈړ����x */
UNs		SV_88DANSPD_SRV;            /* 88�i�ڈړ����x */
UNs		SV_89DANSPD_SRV;            /* 89�i�ڈړ����x */
UNs		SV_90DANSPD_SRV;            /* 90�i�ڈړ����x */
UNs		SV_91DANSPD_SRV;            /* 91�i�ڈړ����x */
UNs		SV_92DANSPD_SRV;            /* 92�i�ڈړ����x */
UNs		SV_93DANSPD_SRV;            /* 93�i�ڈړ����x */
UNs		SV_94DANSPD_SRV;            /* 94�i�ڈړ����x */
UNs		SV_95DANSPD_SRV;            /* 95�i�ڈړ����x */
UNs		SV_96DANSPD_SRV;            /* 96�i�ڈړ����x */
UNs		SV_97DANSPD_SRV;            /* 97�i�ڈړ����x */
UNs		SV_98DANSPD_SRV;            /* 98�i�ڈړ����x */
UNs		SV_99DANSPD_SRV;            /* 99�i�ڈړ����x */
UNs		SV_100DANSPD_SRV;           /* 100�i�ڈړ����x */
#endif
UNs		SV_1DANTIM_SRV;             /* 1�i�ڒ�~���� */
UNs		SV_2DANTIM_SRV;             /* 2�i�ڒ�~���� */
UNs		SV_3DANTIM_SRV;             /* 3�i�ڒ�~���� */
UNs		SV_4DANTIM_SRV;             /* 4�i�ڒ�~���� */
UNs		SV_5DANTIM_SRV;             /* 5�i�ڒ�~���� */
UNs		SV_6DANTIM_SRV;             /* 6�i�ڒ�~���� */
UNs		SV_7DANTIM_SRV;             /* 7�i�ڒ�~���� */
UNs		SV_8DANTIM_SRV;             /* 8�i�ڒ�~���� */
UNs		SV_9DANTIM_SRV;             /* 9�i�ڒ�~���� */
UNs		SV_10DANTIM_SRV;            /* 10�i�ڒ�~���� */
#if (mot100_test == 1)
UNs		SV_11DANTIM_SRV;            /* 11�i�ڒ�~���� */
UNs		SV_12DANTIM_SRV;            /* 12�i�ڒ�~���� */
UNs		SV_13DANTIM_SRV;            /* 13�i�ڒ�~���� */
UNs		SV_14DANTIM_SRV;            /* 14�i�ڒ�~���� */
UNs		SV_15DANTIM_SRV;            /* 15�i�ڒ�~���� */
UNs		SV_16DANTIM_SRV;            /* 16�i�ڒ�~���� */
UNs		SV_17DANTIM_SRV;            /* 17�i�ڒ�~���� */
UNs		SV_18DANTIM_SRV;            /* 18�i�ڒ�~���� */
UNs		SV_19DANTIM_SRV;            /* 19�i�ڒ�~���� */
UNs		SV_20DANTIM_SRV;            /* 20�i�ڒ�~���� */
UNs		SV_21DANTIM_SRV;            /* 21�i�ڒ�~���� */
UNs		SV_22DANTIM_SRV;            /* 22�i�ڒ�~���� */
UNs		SV_23DANTIM_SRV;            /* 23�i�ڒ�~���� */
UNs		SV_24DANTIM_SRV;            /* 24�i�ڒ�~���� */
UNs		SV_25DANTIM_SRV;            /* 25�i�ڒ�~���� */
UNs		SV_26DANTIM_SRV;            /* 26�i�ڒ�~���� */
UNs		SV_27DANTIM_SRV;            /* 27�i�ڒ�~���� */
UNs		SV_28DANTIM_SRV;            /* 28�i�ڒ�~���� */
UNs		SV_29DANTIM_SRV;            /* 29�i�ڒ�~���� */
UNs		SV_30DANTIM_SRV;            /* 30�i�ڒ�~���� */
UNs		SV_31DANTIM_SRV;            /* 31�i�ڒ�~���� */
UNs		SV_32DANTIM_SRV;            /* 32�i�ڒ�~���� */
UNs		SV_33DANTIM_SRV;            /* 33�i�ڒ�~���� */
UNs		SV_34DANTIM_SRV;            /* 34�i�ڒ�~���� */
UNs		SV_35DANTIM_SRV;            /* 35�i�ڒ�~���� */
UNs		SV_36DANTIM_SRV;            /* 36�i�ڒ�~���� */
UNs		SV_37DANTIM_SRV;            /* 37�i�ڒ�~���� */
UNs		SV_38DANTIM_SRV;            /* 38�i�ڒ�~���� */
UNs		SV_39DANTIM_SRV;            /* 39�i�ڒ�~���� */
UNs		SV_40DANTIM_SRV;            /* 40�i�ڒ�~���� */
UNs		SV_41DANTIM_SRV;            /* 41�i�ڒ�~���� */
UNs		SV_42DANTIM_SRV;            /* 42�i�ڒ�~���� */
UNs		SV_43DANTIM_SRV;            /* 43�i�ڒ�~���� */
UNs		SV_44DANTIM_SRV;            /* 44�i�ڒ�~���� */
UNs		SV_45DANTIM_SRV;            /* 45�i�ڒ�~���� */
UNs		SV_46DANTIM_SRV;            /* 46�i�ڒ�~���� */
UNs		SV_47DANTIM_SRV;            /* 47�i�ڒ�~���� */
UNs		SV_48DANTIM_SRV;            /* 48�i�ڒ�~���� */
UNs		SV_49DANTIM_SRV;            /* 49�i�ڒ�~���� */
UNs		SV_50DANTIM_SRV;            /* 50�i�ڒ�~���� */
UNs		SV_51DANTIM_SRV;            /* 51�i�ڒ�~���� */
UNs		SV_52DANTIM_SRV;            /* 52�i�ڒ�~���� */
UNs		SV_53DANTIM_SRV;            /* 53�i�ڒ�~���� */
UNs		SV_54DANTIM_SRV;            /* 54�i�ڒ�~���� */
UNs		SV_55DANTIM_SRV;            /* 55�i�ڒ�~���� */
UNs		SV_56DANTIM_SRV;            /* 56�i�ڒ�~���� */
UNs		SV_57DANTIM_SRV;            /* 57�i�ڒ�~���� */
UNs		SV_58DANTIM_SRV;            /* 58�i�ڒ�~���� */
UNs		SV_59DANTIM_SRV;            /* 59�i�ڒ�~���� */
UNs		SV_60DANTIM_SRV;            /* 60�i�ڒ�~���� */
UNs		SV_61DANTIM_SRV;            /* 61�i�ڒ�~���� */
UNs		SV_62DANTIM_SRV;            /* 62�i�ڒ�~���� */
UNs		SV_63DANTIM_SRV;            /* 63�i�ڒ�~���� */
UNs		SV_64DANTIM_SRV;            /* 64�i�ڒ�~���� */
UNs		SV_65DANTIM_SRV;            /* 65�i�ڒ�~���� */
UNs		SV_66DANTIM_SRV;            /* 66�i�ڒ�~���� */
UNs		SV_67DANTIM_SRV;            /* 67�i�ڒ�~���� */
UNs		SV_68DANTIM_SRV;            /* 68�i�ڒ�~���� */
UNs		SV_69DANTIM_SRV;            /* 69�i�ڒ�~���� */
UNs		SV_70DANTIM_SRV;            /* 70�i�ڒ�~���� */
UNs		SV_71DANTIM_SRV;            /* 71�i�ڒ�~���� */
UNs		SV_72DANTIM_SRV;            /* 72�i�ڒ�~���� */
UNs		SV_73DANTIM_SRV;            /* 73�i�ڒ�~���� */
UNs		SV_74DANTIM_SRV;            /* 74�i�ڒ�~���� */
UNs		SV_75DANTIM_SRV;            /* 75�i�ڒ�~���� */
UNs		SV_76DANTIM_SRV;            /* 76�i�ڒ�~���� */
UNs		SV_77DANTIM_SRV;            /* 77�i�ڒ�~���� */
UNs		SV_78DANTIM_SRV;            /* 78�i�ڒ�~���� */
UNs		SV_79DANTIM_SRV;            /* 79�i�ڒ�~���� */
UNs		SV_80DANTIM_SRV;            /* 80�i�ڒ�~���� */
UNs		SV_81DANTIM_SRV;            /* 81�i�ڒ�~���� */
UNs		SV_82DANTIM_SRV;            /* 82�i�ڒ�~���� */
UNs		SV_83DANTIM_SRV;            /* 83�i�ڒ�~���� */
UNs		SV_84DANTIM_SRV;            /* 84�i�ڒ�~���� */
UNs		SV_85DANTIM_SRV;            /* 85�i�ڒ�~���� */
UNs		SV_86DANTIM_SRV;            /* 86�i�ڒ�~���� */
UNs		SV_87DANTIM_SRV;            /* 87�i�ڒ�~���� */
UNs		SV_88DANTIM_SRV;            /* 88�i�ڒ�~���� */
UNs		SV_89DANTIM_SRV;            /* 89�i�ڒ�~���� */
UNs		SV_90DANTIM_SRV;            /* 90�i�ڒ�~���� */
UNs		SV_91DANTIM_SRV;            /* 91�i�ڒ�~���� */
UNs		SV_92DANTIM_SRV;            /* 92�i�ڒ�~���� */
UNs		SV_93DANTIM_SRV;            /* 93�i�ڒ�~���� */
UNs		SV_94DANTIM_SRV;            /* 94�i�ڒ�~���� */
UNs		SV_95DANTIM_SRV;            /* 95�i�ڒ�~���� */
UNs		SV_96DANTIM_SRV;            /* 96�i�ڒ�~���� */
UNs		SV_97DANTIM_SRV;            /* 97�i�ڒ�~���� */
UNs		SV_98DANTIM_SRV;            /* 98�i�ڒ�~���� */
UNs		SV_99DANTIM_SRV;            /* 99�i�ڒ�~���� */
UNs		SV_100DANTIM_SRV;           /* 100�i�ڒ�~���� */
#endif
//UNs		SV_CYCTIM_SRV;              /* �T�C�N���^�C�� */
//UNs		SV_TAIKAN_SRV;              /* �ҋ@�����͈� */
UNs		SV_MOKKAN_SRV;              /* �ڕW�����͈� */
UNs		SV_KAJYUU_PRS;				/* �׏d�␳ V01m*/
UNs		SV_KAJYUU_OBJP;				/* �׏d�ڕW V01m*/

UNs		disp_stg, disp_stg_sel;
UNl		language_chg;

UNs		PV_STPTIM_B2;							/* ssc_tbl.c �ɂĎg�p		*/

//UNs		PV_KOUTEI1_NO;							/*                      	*/
//UNs		PV_KOUTEI2_NO;							/*                      	*/
//UNs		PV_KOUTEI3_NO;							/*                      	*/
//UNs		PV_KOUTEI4_NO;							/*                      	*/
//UNs		PV_KOUTEI5_NO;							/*                      	*/

UNs		PV_STPTM_OLD;							/*                      	*/
UNs		PV_MLNO01_C15;							/*                      	*/
UNs		PV_MLNO02_C15;							/*                      	*/
UNs		PV_MLNO03_C15;							/*                      	*/
UNs		PV_MLNO04_C15;							/*                      	*/
UNs		PV_MLNO05_C15;							/*                      	*/
UNs		PV_MLNO06_C15;							/*                      	*/
UNs		PV_MLNO07_C15;							/*                      	*/
UNs		PV_MLNO08_C15;							/*                      	*/
UNs		PV_MLNO09_C15;							/*                      	*/
UNs		PV_MLNO10_C15;							/*                      	*/

UNs		PV_MLDNO2_F11[8];		//DB 16 DUP(?)	;	/* V01j */

//UNl		PVB_RNAORG_PLS1;						/*							*/
//UNl		SV_GENITI_CHK;							/*							*/

UNs		PV_CAMNA1_C1;							/*                      	*/
UNs		PV_MLDMES_C1;							/*							*/
UNs		PV_OFFSET_A1;							/*							*/
UNs		PV_DATINI_A1;							/*							*/
UNs		PV_KAJYUU_A1;							/*							*/
UNs		PV_GAIBU_A1;							/*							*/
UNs		PV_BACKDA_A1;							/*							*/

//2002-08-08
//UNs		deg_OLD	[ 3 ];							/* �p�x�O��l				*/
UNs		deg_OLD	[ 4 ];							/* �p�x�O��l				*/
UNs		rbit_OLD[ 3 ];							/* ؾ��   �w���ޯđO��l	*/
UNs		cbit_OLD[ 3 ];							/* ����UP �w���ޯđO��l	*/

UNs		TAIKI_ZEN_MOD;							/* ���[���b�g�O��`�����	*/
UNs		TAIKITEN_DIRECT;						/* �ҋ@�_�f�[�^�i�N���b�`�j	*/

UNs		SEISAN_DISP_FLG;						// ���Y�s���\��	 (00:�Ȃ��^FF:����)
UNs		INTROCK_DISP_FLG;						// �K�C�_���X�\��(00:�Ȃ��^FF:����)

UNs		IROCK_NO	 [ INTROCK_MAX ];			/* ����ۯ��\���ԍ���		*/
UNs		IROCK_NO_LAST[ INTROCK_MAX ];			/* ����ۯ��\���ԍ���O��l	*/

/*==========================================================================*/
/*		�L�[���͗p�̃��[�N�̈��`											*/
/*==========================================================================*/
UNs		KEY_DATA_CODE, KEY_DATA_MODE;

UNs		Key_up[4],Key_dn[4],Key_last[4];

/*==========================================================================*/
/*		�����[�N�̈��`(Sit-2���)											*/
/*==========================================================================*/
/***	�\���p�̃��[�N�̈��`		***/
UNs		GAMEN_NO;					//DW ?	;/* ��ʃR�[�h */
UNs		GAMEN_CODE;					//DB ?	;/* ��ʃR�[�h */
UNs		WINDOW_NO;					//DW ?	;/* ��ʃR�[�h */
UNs		CSR_FLG;					//DB ?	;/* �J�[�\���L���ʃt���O */

UNs		CSR_CNT;					/* �J�[�\���J�E���^ */
UNs		CSR_CNT1;					/* �J�[�\���J�E���^ */
UNs		SV_CNT;						/* �ݒ�l�J�E���^ */
UNs		PV_CNT;						/* �����l�J�E���^ */
UNs		SW_CNT;						/* �r�v�f�[�^�J�E���^ */
UNs		SW_CNT1;					/* �r�v�f�[�^�J�E���^ */

//UNs		CSR_CNT2;				/* �J�[�\���J�E���^ */
//UNs		SV_CNT2;				/* �ݒ�l�J�E���^ */
//UNs		PV_CNT2;				/* �����l�J�E���^ */
//UNs		SW_CNT2;				/* �r�v�f�[�^�J�E���^ */

CSR_TBL_TDEF	CSR_buff[110];		/* �J�[�\�����e�[�u����`�̈�	*/
//2016/11/15
////SV_TBL_TDEF		SV_buff[80];		/* �ݒ�l���e�[�u����`�̈�	*/
SV_TBL_TDEF		SV_buff[100];		/* �ݒ�l���e�[�u����`�̈�	*/
PV_TBL_TDEF		PV_buff[40];		/* �����l���e�[�u����`�̈�	*/
SW_TBL_TDEF		SW_buff[70];		/* �r�v�f�[�^���e�[�u����`�̈�	*/

UNs		PV_DISP_CNT;				/* �\�������l�J�E���^ */
UNs		SW_DISP_CNT;				//����\���r�v�f�[�^�J�E���^

UNs		LCD_WORK1[15][16][40];		/* �\��ܰ��̈�LCD1[���s���ޯĖډ�������] */
UNs		LCD_WORK2[15][16][40];		/* �\��ܰ��̈�LCD2[���s���ޯĖډ�������] */
UNs		LCD_WORK3[15][16][40];		/* �\��ܰ��̈�LCD3[���s���ޯĖډ�������] */ /* V01  */
//UNs		LCD_WIN1[9][16][40];	/* �\��ܰ��̈�LCD1[���s���ޯĖډ�������] */
//UNs		LCD_WIN2[9][16][40];	/* �\��ܰ��̈�LCD2[���s���ޯĖډ�������] */

UNs		CSR_FLG_CNT;				//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
UNs		SV_FLG_CNT;					//DW ?	;/* �����l�Z�b�g */
UNs		SW_FLG_CNT;					//DW ?	;/* �����l�Z�b�g */

UNs		CSR_POS;					//DW ?	;/* �J�[�\���|�W�V�����f�[�^�Ǎ� */
UNs		CSR_POS_LAST;				//DW ?	;/* �O��J�[�\���|�W�V�����f�[�^�Ǎ� */
UNs		CSR_ON_FLG;					//DB ?	;/* �J�[�\���\���t���O�n�m */

UNs		SWDATA_DISP_CNT;			//DW ?	;/* �r�v�f�[�^�\���p���[�v�J�E���g */
UNs		SVSW_CHG_FLG;				//DB ?	;/* �f�[�^�`�F���W�t���O�Z�b�g */

//UNs		SV_DISP_BUFF[20];			//DB 20 DUP(?)	;/* �ݒ�l���ԃo�b�t�@�i�`�r�b�h�h�j */
UNl		SV_DISP_BUFF;				//DB 20 DUP(?)	;/* �ݒ�l���ԃo�b�t�@�i�`�r�b�h�h�j */

UNs		SV_DATA_CHG;				//DB ?	;//�ݒ��ް��ύX�׸�(0:�Ȃ�/55:�����_����/ff:��������)
UNs		CSR_TBL_POS_NOW;			//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
UNs		SV_TBL_POS_NOW;				//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
UNs		SW_TBL_POS_NOW;				//DW ?	;/* �J�[�\�����݈ʒu�A�h���X */
UNs		DISP_CHG_FLG;				//DB ?	;/* �\�����]�t���O�Z�b�g */

UNs		SV_DISP_CNT;				//DB ?	;/* �ݒ�l�\���������͏����� */
UNs		SV_ENT_CNT;					//DB ?
UNs		TENKEY_CNT;					//DB ?	;/* ���̓I�[�o�[�H */
UNs		NO_SUPRESU;					//DB ?
UNs		INTER_ROCK_FLG;				//DB ?	;/* �C���^�[���b�N�L��H */
UNs		PATH_WORD_CNT;				//DB ?		;

UNs		SEI_INF_BUFF[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
UNs		SEI_INF_BUFF1[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
UNs		SEI_INF_BUFF2[280];			//DW 280H DUP(?)	;/* �f�[�^�i�[�A�h���X */
UNs		SEI_WRT_POS;				//DW ?	;/* �\���ʒu */
UNs		SEI_WRT_CNT;				//DW ?		;/* �\�������� */
UNs		SEI_WRT_ADR;				//DW ?		;/* �\�������� */
UNs		IROCK_BUFF[40];				//DW 40 DUP(?)	;
UNs		IROCK_BUFF01[320/2];		//DB 320 DUP(?)	;
UNs		SEI_INF_FLG;				//DB ?
UNs		SEI_INF_FLG_LAST;			//DB ?		;

UNs		GAMEN_WRITE_CNT;			//DB ?		;
//UNs		SEQ_056_WORK[30/2];				//DB 30 DUP(?)	;
UNs		SEQ_044_WORK[30/2];				//DB 30 DUP(?)	;
//UNs		IROCK_NO01;					//DW ?;
//UNs		IROCK_NO02;					//DW ?;
//UNs		IROCK_NO03;					//DW ?;
//UNs		IROCK_NO04;					//DW ?;
//UNs		IROCK_NO05;					//DW ?;
//UNs		IROCK_NO06;					//DW ?;
//UNs		IROCK_NO07;					//DW ?;
//UNs		IROCK_NO08;					//DW ?;
//UNs		IROCK_NO09;					//DW ?;
//UNs		IROCK_NO010;				//DW ?;
//UNs		IROCK_NO011;				//DW ?;
//UNs		IROCK_NO012;				//DW ?;

//UNs		IROCK_NO1_LAST;				//DW ?
//UNs		IROCK_NO01_LAST[30];		//DW 30 DUP(?)	;
UNs		IROC_CHG_FLG;				//DW ?	;
UNs		IROC_CHG_FLG1;				//DW ?	;
UNs		IL_DISP_LAST;				//DB ?
UNs		GAMEN_NO_IROCK;				//DW ?
UNs		SEISAN_FLG;					//DB ?	;
UNs		SEISAN_FLG_LAST;			//DB ?	;
UNs		IROCK_SHR_LAST;				//DB ?
UNs		SVPV_DATA_FLG;				//DB ?
UNs		SOUSA_LEFT_FLG;				//DB ?
UNs		ERR_MONI_LAST1;				//DW ?
UNs		ERR_MONI_LAST2;				//DW ?
UNs		ERR_MONI_LAST3;				//DW ?
UNs		DAN_SOUSA_DAT;				//DW ?
UNs		RULET_DIG_TBL_ADR;			//DW ?
UNs		SEI_COUNT_LAST1;			//DB ?;
UNs		SEI_COUNT_LAST2;			//DB ?;
UNs		SEI_COUNT_LAST3;			//DB ?;
UNs		SEI_COUNT_LAST4;			//DB ?;

//UNs		GAMEN_ON_FLG;				//DB ?
UNs		IL_DISP_FLG;				//DB ?		;/* �h�k�\���t���O���Z�b�g */
UNs		INI_FLG	;					//DB ?
//UNs		SEQ_020_SV_BUFF;			//DB ?
UNs		SEQ_018_SV_BUFF;			//DB ?
UNs		BASE_CLS_CNT;				//DW ?
UNs		SEI_INF_SPATH_CNT;			//DW ?
UNs		SUM_CHK_ERR;				//DB ?
UNs		DAN_NON_GAMEN;				//DB ?
UNs		SV_CHK_ERR;					//DB ?
UNs		SV_CMP_ERR;					//DB ?
UNs		SV_SUM1_ERR;				//DB ?
UNs		SV_SUM2_ERR;				//DB ?
UNs		SV_DPRAM_ERR;				//DB ?

UNs		INCH_DATA_FLG;				//DB ?	;/* INCH�����t���O */

UNs		OP_MESS_DISP_LAST1;			//DB ?	;
UNs		OP_MESS_DISP_LAST2;			//DB ?	;
UNs		OP_MESS_DISP_LAST3;			//DB ?	;

UNs		OFF_SET_MNG_LAST;			//DB ?	;
UNs		OFF_SET_MNG_LAST1;			//DB ?	;
UNs		KOUSEI_MNG_LAST;			//DB ?	;
UNs		KOUSEI_MNG_LAST1;			//DB ?	;
UNs		SURA_AUTO_MNG_LAST;			//DB ?	;
UNs		SURA_AUTO_MNG_LAST1;		//DB ?	;
UNs		SURA_AUTO_MNG_LAST2;		//DB ?	;

UNs		SEIGAMEN_CNT;				//DB ?	;
UNs		SEGAMEN_ADR;				//DW ?	;

UNs		OFF_SET_MNG_LAST2;			//DB ?	;
UNs		OFF_SET_MNG_LAST3;			//DB ?	;
UNs		OFF_SET_MNG_LASTX;			//DB ?	;
UNs		KOUSEI_MNG_LAST2;			//DB ?	;
UNs		YOUBI_LAST;					//DB ?

UNs		PODATA_SET_FLG;				//DB ?	;

UNs		ONOFF_FLG;					//DB ?	;
UNs		ONOFF_LAST1;				//DB ?	;
UNs		ONOFF_LAST2;				//DB ?	;
UNs		ONOFF_LAST3;				//DB ?	;
UNs		ONOFF_LAST4;				//DB ?	;
UNs		ONOFF_LAST5;				//DB ?	;
UNs		ONOFF_LAST6;				//DB ?	;
//UNs		ONOFF_LAST7;				//DB ?	;
//UNs		ONOFF_LAST8;				//DB ?	;
//UNs		ONOFF_LAST9;				//DB ?	;
//UNs		ONOFF_LAST10;				//DB ?	;

UNs		GAMEN_B6_NON_FLG;			//DB ?	;

UNs		INI_POS_ERR_FLG;			//DB ?	;

UNs		PV_ADBAKD_A14;				//DW ?	;

UNs		ENCO_DATA_BCD;				//DW ?	;
UNs		ENCO_DATA_HEX;				//DW ?	;

UNs		OFFSET_END_FLG;				//DB ?	;/* �I�t�Z�b�g���������H */

UNs		MCN_SEQ_LAST1;				//DB ?		;
UNs		MCN_SEQ_LAST2;				//DB ?		;
UNs		MCN_SEQ_LAST3;				//DB ?		;
UNs		MCN_SEQ_LAST4;				//DB ?		;
UNs		MCN_SEQ_LAST5;				//DB ?		;

UNs		MCN_DATA_NO1;				//DB ?		;
UNs		MCN_DATA_NO2;				//DB ?		;
UNs		MCN_DATA_NO3;				//DB ?		;
UNs		MCN_DATA_NO4;				//DB ?		;
UNs		MCN_DATA_NO5;				//DB ?		;

UNs		MCN_REC_FLG;				//DB ?		;

//UNs		GAMEN_DISP_FLG;				//DB ?	;
UNs		GGAMEN_DISP_FLG;			//DB ?	;

UNs		CARA_CHG_FLG;				//DB ?	;
UNs		YOKOBAI_CNT;				//DW ?	;/* ���{�J�E���^ */
UNs		YOKOBAI_ADR;				//DW ?	;/* ���{�A�h���X */
UNs		YOKO_BAI_WORK[32*16];		//DB 32*16 DUP(?)	;/* �f�[�^�����[�N�̈�֓]�� */

UNs		KAN_BANK_NO;				//DB ?		;V05

UNs		GENGO_CHG_LAST;				//DB ?		;
//UNs		GENGO_CHG_LAST1;			//DB ?		;
UNs		WORK_BUFF_NAME[20];			//DW 20 DUP(?);

UNs		BASE_WORK;					//DW ?		;

UNs		KT_DUMMY_01;				//DW ?	;
UNs		KT_DUMMY_02;				//DB ?	;

UNs		DAI_SVDATA_FLG;				//DB ?	;/* �_�C�n�C�g�����L���H */
//UNs		SEQ_030_WK;					//DB ?	;
UNs		SEQ_023_WK;					//DB ?	;

UNs		AUTO_SEQ_LST;				//DB ?	;

UNs		SV_0401_FLG;				//DB 	?	;
UNs		SV_1101_FLG;				//DB ?	;
UNs		SW_1101_FLG;				//DB ?	;
UNs		SW_1102_FLG;				//DB ?	;
UNs		SW_1103_FLG;				//DB ?	;

UNs		CSR_MLD_WORK[32/2];			//DB 32 DUP(?)	;/* �J�[�\�����ړ�����ƕ����� */

UNs		SIT_MOLD3_RCV_BUFF[50];		//DW	50	DUP(?)	;

UNs		TAIKITEN_DAT;				//DW ?	;/* �ҋ@�_�������烋�[���b�g���ĕ\�� */	EXTRN	TAIKITEN_DAT		: WORD	;/* �ҋ@�_�������烋�[���b�g���ĕ\�� */
UNs		RULET_NOW_LST;				//DW ?	;
UNs		DEG_DISP_LST;				//DW ?	;/* �p�x�ް��ω�����H */
UNl		DEG_DISP_DATA[2];			//DD	?	;
									//DD	?	;

UNs		DEG_LCD_BUFF[32*12];		//DB 32*12 DUP(?)	;/* �p�x�\����p�o�b�t�@ */

UNs		STOPTIME_DISP_LST;			//DW ?	;/* �p�x�ް��ω�����H */
UNl		STOPTIME_DISP_DATA[2];		//DD	?	;
									//DD	?	;

UNs		STOPTIME_LCD_BUFF[32*12];	//DB 32*12 DUP(?)	;/* �p�x�\����p�o�b�t�@ */

UNs		PFOUT_DATA_BAK;				//DB ?	;

UNs		DAT_LCD_KAN_BAK;			//DB ?	;

UNs		DEG_DISP_FLG;				//DB ?	;
//UNs		STOP_DISP_FLG;				//DB ?	;
UNs		RULET_DISP_FLG;				//DB ?	;/* ���[���b�g�\���n�j */
//UNs		RULET_NON_FLG;				//DB ?	;
UNs		CSR_MOVE_OK_FLG;			//DB ?	;/* �J�[�\���ړ��֎~ */

UNs		SW14_ON_FLG;				//DB ?	;
UNs		SW14_ON_CNT;				//DB ?	;
UNs		SET_KEY_LST;				//DB ?	;

UNs		KIDO_FLG_FLG;				//DB 2 DUP(?)	;/* �P�x�f�[�^�Ǎ����i�[ */
UNs		KIDO_FLG_PV;				//DB ?		;/* �P�x�f�[�^�Ǎ����i�[ */

UNs		GAIBU_RST_LAST;				//DB ?	;
//UNs		GAIBU_RST_LAST1;			//DB ?	;
UNs		GAIBU_RST_LAST2;			//DB ?	;
UNs		GAIBU_RST_LAST3;			//DB ?	;
//UNs		GAIBU_RST_LAST4;			//DB ?	;
//UNs		GAIBU_RST_LAST5;			//DB ?	;
//UNs		GAIBU_RST_LAST6;			//DB ?	;
//UNs		GAIBU_RST_LAST7;			//DB ?	;
//UNs		GAIBU_RST_LAST8;			//DB ?	;

//UNs		GAIBU_CHG_FLG;				//DB ?	;

UNs		TAIKITEN_FLG;				//DB ?	;
UNs		TAIKITEN_LAST;				//DB ?
UNs		TAIKITEN_DATA;				//DW ?
UNs		TAIKI_NOW_POS;				//DW ?	;
UNs		TAIKI_ZEN_POS;				//DW ?	;

UNs		COUNT_HOSEI_ADR;			//DW ?	;/* ���]�A�h���X�f�[�^�Ҕ� */
UNs		SURA_HOSEI_ADR;				//DW ?	;/* ���]�A�h���X�f�[�^�Ҕ� */

UNs		SWCHG_DISP_ON_FLG;			//DB ?	;
UNs		SEISAN_SW56_FLG;			//DB ?	;
UNs		SEISAN_SW56_TIM;			//DW ?	;
UNs		OPBAK_UP_LST;				//DB ?	;
UNs		OPBAK_UP_LST1;				//DB ?	;

UNs		SW14_ON1_FLG;				//DB ?	;
UNs		SW14_ON6_FLG;				//DB ?	;
UNs		SW14_ON1_FLG_BAK2;			//DB ?	;
UNs		SW14_ON1_FLG_BAK3;			//DB ?	;
UNs		SW14_ON1_FLG_BAK;			//DB ?	;
UNs		SW14_ON6_FLG_BAK;			//DB ?	;
UNs		SW14_ON6_FLG_BACK;			//DB ?	;

UNs		TAIKI_LST;					//DW ?	;

UNs		CAMNAME_INP_CNT;			//DB ?	;
UNs		NAME_CHG_FLG;				//DB ?	;/* ���̕ύX���H */
UNs		CAM_NAME_NO;				//DB ?	;/* �ύX�J�����̔ԍ��Ǎ� */
UNs		SUOERTH_BUFF[3];			//DW 3 DUP(?)	;

UNs		CSR_FLG_CNT_BAK;			//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
UNs		CSR_FLG_CNT_BAK3;			//DW ?	;/* ���݂̃J�[�\���ʒu�J�E���g */
UNs		SV_FLG_CNT_BAK;				//DW ?	;/* �����l�Z�b�g */
UNs		SW_FLG_CNT_BAK;				//DW ?	;/* �����l�Z�b�g */

UNs		CAMOUT_MUSK;				//DW ?	;/* �ėp�o�̓}�X�N�r�b�g */
UNs		CAMOUT_BIT;					//DW ?	;/* �ėp�o�̓r�b�g */

UNs		GAMEN_NO_CAM;				//DW ?	;
UNs		DAN_WIN_FLG;				//DB ?	;	V01j(INS)
UNs		DAN_CSR_LST;				//DB ?	;

//UNs		SW14_DISP7_NON;				//DB ?	;

UNs		SET_SPM_LST;				//DB ?	;
UNs		KATNAME_INP_CNT;			//DB ?	;/* ���̓J�E���^�[�P */

//UNs		PV_MLDNO1_F0[16];			//DB 16 DUP(?)	;
UNs		PV_MLDNO1_F0;				//DB 16 DUP(?)	;
UNs		PV_MLDNO2_F0[16];			//DB 16 DUP(?)	;

UNs		SINCAM_LST;					//DB ?	;	
UNs		TAIKITEN_FLG_FLG;			//DB ?	;/* ���łɃt���O�𗧂ĂĂ������� */

UNs		CSR_CLS_FLG;				//DB ?	;
UNs		PVCNT_DISP_CNT;				//DB ?	;
UNs		PVALL_FLG;					//DB ?	;
UNs		PVGENNITI_FLG;				//DB ?	;

UNs		CSR_FLG_BUF;				//DW ?	;/*  */
UNs		SV_FLG_BUF;					//DW ?	;/*  */

UNs		ENCO_DATA_HEX1;				//DW ?	;

UNs		RULET_GAKU_FLG;				//DW ?	;
UNs		RULET_GAKU_LST;				//DB ?	;

UNs		SEI_ON6_LST1;				//DB ?	;
UNs		SEI_ON6_LST2;				//DB ?	;
UNs		SEI_ON6_LST3;				//DB ?	;
UNs		SEI_ON6_LST4;				//DB ?	;
UNs		SEI_ON1_LST;				//DB ?	;

UNs		DAN_GAMEN_NON;				//DB ?	;
UNs		SEL_GAMEN_NON;				//DB ?	;
UNs		CAM_GAMEN_NON;				//DB ?	;
UNs		EJE_GAMEN_NON;				//DB ?	;
UNs		MIS_GAMEN_NON;				//DB ?	;
UNs		ROT_GAMEN_NON;				//DB ?	;

UNs		ROT1_GAMEN_NON;				//DB ?	;
UNs		ROT2_GAMEN_NON;				//DB ?	;
UNs		ROT3_GAMEN_NON;				//DB ?	;

UNs		CSR_FLG_CNT_LST;			//DW ?	;/* �J�[�\���ԍ��Z�b�g */

UNs		POWRE_OK_FLG;				//DW ?	;

UNs		PVDATA_NON;					//DB ?	;

UNs		CAR_ROM_SEG;				//DW ?	;

UNs		PV_SUM_CHK;					//DW ?	;
UNs		EE_SUM_CHK;					//DW ?	;

UNs		POWER_DOWN_FLG;				//DB ?	;

UNs		SW56_UPTOP_FLG;				//DB ?	;'98-08-05

//V01u	UNs		KAT_DATCHG_FLG;				//DB ?	;
UNs		KAT_DATCHG_FLG_DUMMY;				//DB ?	;
UNs		KAT_CNTCHG_FLG;				//DB ?	;

UNs		SW14_DISP7_DANNON;			//DB ?	;'98-08-31/*�X���C�h�ȊO�Ȃ��Ƃ��̓W�����v  */
//UNs		OP_NON_FLG;					//DB ?	;

UNs		SYS_HIGHSPM_B1;				//DW ?	;V01a
UNs		SYS_LOWSPM_B1;				//DW ?	;V01a
UNs		RULET_HIGH_FLG;				//DB ?	;/* �������[���b�g�`��t���O�Z�b�g */
UNs		RULET_HIGH_LST;				//DB ?	;
UNs		CB1_SPMDAT_PVV;				//DW ?	;/* �ǂݍ��� */

UNs		PV_TLINKSMP_DAT;			//DW ?	;V03j

UNs		ENC_SPD_CNT;				//DW ?		;
UNl		ENCSPD_ADD;					//DD	?		;
UNs		ENCSPD_BF[20];				//DW	10	DUP (?)	;
									//DW	10	DUP (?)	;

UNs		CSR_DAN_CSR_LST;			//DW ?		;V01a/* �i�����SW56���ݽ��ݾٗp */

UNs		SW56_MUSK_FLG;				//DW ?		;V01b

UNs		MLD_100_GNO;				//DW ?		;MLD100/* �^�Ǘ���ʔԍ������� */
//UNs		MLD_100_NO;					//DW ?		;MLD100/* �^�Ǘ���ʔԍ������� */
UNs		MLD_100_FLG;				//DB ?		;MLD100/* �^�Ǘ��t���O������ */
//UNs		MLD_100_CARD_FLG;			//DB ?		;MLD100/*  */

UNs		MEM_ADR;					//DW ?	;
UNs		MEM_BNK;					//DW ?	;
UNs		MLD_WRITE_BNK;				//DB ?	;

UNs		CSR_POS_G15;				//DB ?	;/*  */

UNs		CSR_MOVE_NON;				//DB ?	;/* �J�[�\���͓����Ȃ��H */

UNs		MLD100_INI_FLG;				//DB ?	;

UNs		DAN_DAN_FLG;				//DB ?	;

UNs		CSR_FLG_CNT_BACK;			//DW ?		;
UNs		WINDOW_NO_BACK;				//DW ? 		;

UNs		DAN_KEY_FLG;				//DB ?		;

UNs		G07_WIN_FLG;				//DB ?		;

UNs		FILCK_CNT;					//DW ?			;
UNs		FILCK_STEP1_FLG;			//DB ?			;
UNs		FILCK_STEP2_FLG;			//DB ?			;
UNs		FILCK_STEP3_FLG;			//DB ?			;

UNs		NEXT_READ_NO;				//DW ?	;/* ���^�ԍ��ݒ�l */

UNs		KEY_DOWN14_FLG;				//DB ?	;/* �j�d�x����������t���O���Z�b�g */
UNs		SW14_MUSK_FLG;				//DW ?	;

UNs		SW14_MUSK_FLG_SW2;			//DW ?	;

UNs		CSR_G07_NO1;				//DW ?	;/* �J�[�\���擪�ʒu�Ɠ����H */
UNs		CSR_G07_NO2;				//DW ?	;/* �J�[�\���擪�ʒu�Ɠ����H */

UNs		SYS_SPMPM_B1P;				//DW ?	;
UNs		SYS_SPMPM_B1M;				//DW ?	;

//UNs		SEQ_022_FLG;				//DB ?	;
UNs		SEQ_019_FLG;				//DB ?	;

UNs		SYS_MISSEL_SV;				//DB ?		;

UNs		SURA_SEL_LST;				//DB ?	;

UNs		DAN_CLS_CNT;				//DW ?		;2000-07-04/* �\���������J�E���^ */

UNs		SEI_GAI_LST;				//DB ?
UNs		GENG_SEQ_LST;				//DB ?
UNs		NEXT_MLDSEQ_FLG;			//DB ?		;2001-08-07 /*�V�[�P���X�p���^�f�[�^�ǂݍ��݃t���O�n�m*/

UNs		PV_CAMSW1_C1[4];		//DB 8 DUP(?)	;BIT_1
UNs		PV_CAMSW2_C1[4];		//DB 8 DUP(?)	;BIT_2
UNs		PV_CAMSW3_C1[4];		//DB 8 DUP(?)	;BIT_3
UNs		PV_CAMSW4_C1[4];		//DB 8 DUP(?)	;BIT_4
UNs		PV_CAMSW5_C1[4];		//DB 8 DUP(?)	;BIT_5
UNs		PV_CAMSW6_C1[4];		//DB 8 DUP(?)	;BIT_6
UNs		PV_CAMSW7_C1[4];		//DB 8 DUP(?)	;BIT_7
UNs		PV_CAMSW8_C1[4];		//DB 8 DUP(?)	;BIT_8
UNs		PV_CAMSW9_C1[4];		//DB 8 DUP(?)	;BIT_9
UNs		PV_CAMSWA_C1[4];		//DB 8 DUP(?)	;BIT_A
UNs		PV_CAMSWB_C1[4];		//DB 8 DUP(?)	;BIT_B
UNs		PV_CAMSWC_C1[4];		//DB 8 DUP(?)	;BIT_C
UNs		PV_CAMSWD_C1[4];		//DB 8 DUP(?)	;BIT_D
UNs		PV_CAMSWE_C1[4];		//DB 8 DUP(?)	;BIT_E
UNs		PV_CAMSWF_C1[4];		//DB 8 DUP(?)	;BIT_F

UNs		PV_CAMNA01_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P���� */
UNs		PV_CAMNA02_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���Q���� */
UNs		PV_CAMNA03_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���R���� */
UNs		PV_CAMNA04_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���S���� */
UNs		PV_CAMNA05_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���T���� */
UNs		PV_CAMNA06_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���U���� */
UNs		PV_CAMNA07_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���V���� */
UNs		PV_CAMNA08_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���W���� */
UNs		PV_CAMNA09_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���X���� */
UNs		PV_CAMNA10_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�O���� */
UNs		PV_CAMNA11_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�P���� */
UNs		PV_CAMNA12_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�Q���� */
UNs		PV_CAMNA13_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�R���� */
UNs		PV_CAMNA14_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�S���� */
UNs		PV_CAMNA15_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�T���� */
UNs		PV_CAMNA16_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�U���� */
UNs		PV_CAMNA17_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�V���� */
UNs		PV_CAMNA18_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�W���� */
UNs		PV_CAMNA19_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���P�X���� */
UNs		PV_CAMNA20_C1[4];		//DB 8 DUP(?)	;/* ���[�^���J���Q�O���� */

//UNs		PV_EJECT1_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT2_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT3_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT4_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT5_NAME[4];		//DB 10 DUP(?)   ;
//UNs		PV_EJECT6_NAME[4];		//DB 10 DUP(?)   ;

UNs		PV_KOUMOKU1_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU2_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU3_NAME[8];	//DB 16 DUP(?)	;
UNs		PV_KOUMOKU4_NAME[8];	//DB 16 DUP(?)	;

UNs		PV_KINOU01_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU02_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU03_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU04_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU05_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU06_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU07_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU08_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU09_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU10_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU11_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU12_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU13_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU14_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU15_NAE[8];		//DB 16 DUP(?)	;
UNs		PV_KINOU16_NAE[8];		//DB 16 DUP(?)	;


UNs		SEQ_PAR_101_BAK;		/* V00p */
UNs		disp_stg_sel_bak;		/* V00p */
UNs		WINDOW_NO_bak;			/* V00p */
UNs		PV0_PAR_A_CHAR;			/* V00p */    /* ���Ұ��ް�ޮ� ������׸� ASCII */
UNs		PV0_PAR_B_CHAR;			/* V00p */    /* ���Ұ��ް�ޮ� ������׸� ASCII */
UNs		PV0_TBL_A_CHAR;			/* V00p */    /* �ݻ��ð��ٔԍ� ASCII */
UNs		PV0_TBL_B_CHAR;			/* V00p */    /* �ݻ��ð��ٔԍ� ASCII */
UNs		PV0_INTER_VER2;			/* V00p */    /* ����ۯ��ް�ޮ� ������׸� ASCII */
UNs		PV0_DEFULT_VER2;		/* V00p */    /* �����l�ް��ް�ޮ� ������׸� ASCII */
UNs		PV0_SEQ_VER2;			/* V00p */    /* ���ݽ�ް�ޮ� ������׸� ASCII */
UNl		PV0_NOW_POSI000;		/* V00q */    /* �����㍂��PV */
UNl		PV0_DYHITO_POS;			/* V00q */    /* �����ʒuPV */
UNl		PV0_SLIDE_POS;			/* V01  */    /* ���Y����PV */
UNl		PV0_NOWPOSI_SLIDE;		/* V01  */    /* ���Y����or�����㍂PV */

UNs		GAIBU_RST_BAK;			/* V00t */

UNs		PV0_MONALM_P01;
UNs		PV0_MONALM_P02;
UNs		PV0_MONALM_P03;
UNs		PV0_MONALM_P04;
UNs		PV0_MONALM_A01;
UNs		PV0_MONALM_A02;
UNs		PV0_MONALM_A03;
UNs		PV0_MONALM_A04;
UNs		PV0_MONALM_A05;
UNs		PV0_MONALM_A06;
UNs		PV0_MONALM_A07;
UNs		PV0_MONALM_A08;
UNs		PV0_MONALM_B01;
UNs		PV0_MONALM_B02;
UNs		PV0_MONALM_B03;
UNs		PV0_MONALM_B04;
UNs		PV0_MONALM_B05;
UNs		PV0_MONALM_B06;
UNs		PV0_MONALM_B07;
UNs		PV0_MONALM_B08;
UNl		PV0_MONALM_C01;
UNl		PV0_MONALM_C02;
UNl		PV0_MONALM_C03;
UNl		PV0_MONALM_C04;
UNl		PV0_MONALM_C05;
UNl		PV0_MONALM_C06;
UNl		PV0_MONALM_C07;
UNl		PV0_MONALM_C08;
UNs		PV0_MONALM_B01_SIGN;
UNs		PV0_MONALM_B02_SIGN;
UNs		PV0_MONALM_B03_SIGN;
UNs		PV0_MONALM_B04_SIGN;
UNs		PV0_MONALM_B05_SIGN;
UNs		PV0_MONALM_B06_SIGN;
UNs		PV0_MONALM_B07_SIGN;
UNs		PV0_MONALM_B08_SIGN;
UNs		PV0_MONALM_C01_SIGN;
UNs		PV0_MONALM_C02_SIGN;
UNs		PV0_MONALM_C03_SIGN;
UNs		PV0_MONALM_C04_SIGN;
UNs		PV0_MONALM_C05_SIGN;
UNs		PV0_MONALM_C06_SIGN;
UNs		PV0_MONALM_C07_SIGN;
UNs		PV0_MONALM_C08_SIGN;

UNs		MOTION_SV_CHG_CANCEL;			/* V01d */

UNs		TAIKIKAKU_CHG_FLG;				/* V01i */
UNs		GAMNE_REDISP_COD;				/* V01i */

UNs		SEQ_PAR_107_BAK;				/* V01j */
UNs		SEQ_PAR_427_CHG;				/* V01j */
UNs		SEQ_PAR_427_ONE;				/* V01j */
UNs		SEQ_PAR_427_OFE;				/* V01j */
UNs		SEQ_PAR_427_BAK;				/* V01j */
UNs		autokana_sw56_bak;				/* V01j */
UNs		ADC_DISP_FLG;					/* V01j */
UNs		ADC_CHG_LST;					/* V01j */
UNs		ADC_CHG_LST1;					/* V01j */
UNs		ADC_CHG_LST2;					/* V01j */
UNs		ADC_CHG_LST3;					/* V01j */
UNs		ADC_CHG_LST4;					/* V01j */
UNs		ADC_CHG_LST5;					/* V01j */
UNs		ADC_CHG_LST2_2;					/* V01j */
UNs		ADC_MODE_FLG;					/* V01j */
UNs		ADC_STEP_FLG;					/* V01j */
UNs		ADC_STPCHG_FLG;					/* V01j */
UNs		ADC_FILCK_LST;					/* V01j */
UNs		ADC_SW2_FLG;					/* V01j */
UNs		ADC_SW34_FLG;					/* V01j */
UNs		ADC_SW5_FLG;					/* V01j */
UNs		ADC_SW6_FLG;					/* V01j */
UNs		SW14_DISP7_NON;					/* V01j */
UNs		ADC_STEP_NO[4];					/* V01j */
UNs		ADC_STEP_NO_LAST[4];			/* V01j */
UNs		step_flick_flg;					/* V01j */
UNs		step_flick_flg_bak;				/* V01j */
UNs		step_flick_cnt;					/* V01j */

UNl		CAR_LNG_KAJ_AREA;				/* V01k */
UNs		SYO_LNG_KAJ_CNT;				/* V01k */

UNl		PV0_KAGEN_POSITIONER;				/* V01l_b */

UNs		SYO_LNG_SUR_CNT;				/* V01m */

UNs		DEB_WORD_FLG1;					/* V01n_b */
UNs		DEB_WORD_FLG2;					/* V01n_b */
UNs		DEB_WORD_FLG3;					/* V01n_b */
UNs		DEB_WORD_FLG4;					/* V01n_b */
UNs		DEB_WORD_FLG5;					/* V01n_b */
UNs		DEB_WORD_FLG6;					/* V01n_b */
UNs		DEB_WORD_FLG7;					/* V01n_b */
UNs		DEB_WORD_FLG8;					/* V01n_b */
UNs		DEB_WORD_FLG9;					/* V01n_b */
UNs		DEB_WORD_FLG10;					/* V01n_b */
UNs		DEB_WORD_FLG11;					/* V01n_b */
UNs		DEB_WORD_FLG12;					/* V01n_b */
UNs		DEB_WORD_FLG13;					/* V01n_b */
UNs		DEB_WORD_FLG14;					/* V01n_b */
UNs		DEB_WORD_FLG15;					/* V01n_b */
UNs		DEB_WORD_FLG16;					/* V01n_b */

//��������������	�ȉ��A�r�h�s�|�S�Œǉ�		��������������
UNl		DEBUG_CNT;

UNs		CSR_BAK_M_LEN;	
UNs		CSR_BAK_X_POS;	
UNs		CSR_BAK_Y_POS;	
UNs		CSR_BAK_C_COL;	
UNs		CSR_BAK_B_COL;	
UNs		CSR_BAK_SIZE;	
UNs		*CSR_BAK_G_P;	

GAMENn_HEAD_st	GAMENn_HEAD;
DISP_INFO_st	DISP_INFO;

UNl		CHR_TABLE_ADR;			// �L�����N�^�e�[�u���̕�����L�����N�^�擪�A�h���X
UNl		CSR_TABLE_ADR;			// �L�����N�^�e�[�u���̃J�[�\���L�����N�^�擪�A�h���X
UNl		SWL_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^�擪�A�h���X
UNl		S56_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^�擪�A�h���X
UNl		MES_TABLE_ADR;			// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^�擪�A�h���X
UNl		S56U_TABLE_ADR;			// �L�����N�^�e�[�u���̂r�v�T�E�U��i�L�����N�^�擪�A�h���X
UNl		SPE_TABLE_ADR;			// �L�����N�^�e�[�u���̓��ʃL�����N�^�擪�A�h���X

UNl		GAMENN_MOJ_INF_ADR;		// ��ʂ��̕�������̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_CSR_INF_ADR;		// ��ʂ��̃J�[�\�����̐擪�A�h���X		�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_SVP_INF_ADR;		// ��ʂ��̐ݒ�l���̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_PVP_INF_ADR;		// ��ʂ��̎����l���̐擪�A�h���X			�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_SWL_INF_ADR;		// ��ʂ��̂r�v�|�k�`�l�o�̐擪�A�h���X		�i��ʂ���\������Ƃ��ɎZ�o�j
UNl		GAMENN_GRP_INF_ADR;		// ��ʂ��̃O���t�B�b�N���̐擪�A�h���X	�i��ʂ���\������Ƃ��ɎZ�o�j

UNs		CHRTBL_CHR_CNT;			// �L�����N�^�e�[�u���̕�����L�����N�^��
UNs		CHRTBL_CSR_CNT;			// �L�����N�^�e�[�u���̃J�[�\���L�����N�^��
UNs		CHRTBL_SWL_CNT;			// �L�����N�^�e�[�u���̂r�v�|�k�`�l�o�L�����N�^��
UNs		CHRTBL_S56_CNT;			// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^��
UNs		CHRTBL_MES_CNT;			// �L�����N�^�e�[�u���̃��b�Z�[�W�L�����N�^��
UNs		CHRTBL_S56U_CNT;		// �L�����N�^�e�[�u���̂r�v�T�E�U���i�L�����N�^��
UNs		CHRTBL_SPE_CNT;			// �L�����N�^�e�[�u���̓��ʃL�����N�^��

UNs		GAMENn_SCR_COL;			//��ʂ̽�ذݐF�iWindow��\�����ĕς��Ȃ����Ɓj

UNs		PVW_ZURE_PLS_SIN;		//���Խ�ڎ�������
UNs		PVW_ZURE_RNA_SIN;		//���Խ���Ʊ����
UNs		PVW_ZURE_PLS;			//���Խ�ڎ���
UNs		PVW_ZURE_RNA;			//���Խ���Ʊ
UNs		PVW_BAKORG_SIN1;		//�ޯ����ߎ�������
UNs		PVW_BAKORG_SIN2;		//�ޯ����ߎ�������
UNl		SVBW_BAKORG_PLS1;		//�Ʊ��ʒu��ٽ	COP2
UNl		SVBW_BAKORG_PLS2;		//�Ʊ��ʒu��ٽ	COP2

UNs		GAM_CHG_WIN_NO_BAK;		/* V04a */

UNb		OP_STATUS;				//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H		//V01e
UNb		OP_STATUS_DUM;			//DB	?		; OPż:00H,OP��(OK):55H,OP��(WDTup):54H		//V01e

UNb		MEM_ARI;				//DB	?		; OP��:A5H		//V05h

UNs		PV0_CB_C_VER[6];		//ASCII�ް� (1WORD�ŷ�׸����� 6char) SH4-->
UNs		PV0_PAR_C_CHAR;			//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)
UNs		PV0_TBL_C_CHAR;			//���Ұ��ް�ޮ� ������׸� ASCII(2BYTE)

//;	******** 2007/12/12 ***********
UNs		PV0_IPM_ADR0;			//IP���ڽ(���)
UNs		PV0_IPM_ADR1;			//IP���ڽ(���)
UNs		PV0_IPM_ADR2;			//IP���ڽ(���)
UNs		PV0_IPM_ADR3;			//IP���ڽ(���)

//;	******** 2009/07/14 ***********
UNs		IROCK_OUT_NO[8];			/* ����ۯ������ԍ�		*/
UNb		IROCK_CHAR[8][8];			/* ����ۯ������ԍ��ɑ΂��鷬׸�����		*/

//;	******** 2009/08/-- *********** V05o(INS)	�����g�`�\���p
UNs		WAVE_SAMP_DTP[2];					//���������ݸޔg�`�`��ʒu�߲��		+0:�ŐV  +1:�O��l
UNs		WAVE_TRND_DTP[2];					//��������ޔg�`�`��ʒu�߲��		+0:�ŐV  +1:�O��l
WAVE_SAMP_DATA_ST	WAVE_SAMP_DATA[501];	//���������ݸޔg�`�p�ް�
WAVE_TRND_DATA_ST	WAVE_TRND_DATA[5001];	//��������ޔg�`�p�ް�
WAVE_SAMP_DOT_ST	WAVE_SAMP_DOT[501];		//���������ݸޔg�`�p�ް�
WAVE_TRND_DOT_ST	WAVE_TRND_DOT[5001];	//��������ޔg�`�p�ް�
UNs		CSR_PVSAMP[2];						//���������ݸޔg�`��ʂ̶��وʒu	+0:�ŐV  +1:�O��l
UNs		CSR_PVTRND[2];						//��������ޔg�`��ʂ̶��وʒu		+0:�ŐV  +1:�O��l
UNs		PW_Key_up[4];						//�����g�`��ʗp�������ω�	(5ms�����݂ŊĎ�)
UNs		PW_Key_dn[4];						//�����g�`��ʗp��������ω�	(5ms�����݂ŊĎ�)
UNs		PW_Key_last[4];						//�����g�`��ʗp���O��l		(5ms�����݂ŊĎ�)
UNs		PW_Key_tim02[4];					//�����g�`��ʗp������������	(5ms�����݂ŊĎ�)
UNs		PW_Key_tim30[4];					//�����g�`��ʗp������������	(5ms�����݂ŊĎ�)
UNs		PV0_SMPCSR_KJT;						//���وʒu�̍��v�׏d
UNs		PV0_SMPCSR_KJL;						//���وʒu�̍��׏d
UNs		PV0_SMPCSR_KJR;						//���وʒu�̉E�׏d
UNs		PV0_SMPCSR_AGL;						//���وʒu�̊p�x
UNl		PV0_SMPCSR_RNA1;					//���وʒu�̽ײ�ވʒu
UNl		PV0_SMPCSR_RNA2;					//���وʒu�̽ײ�ވʒu
UNs		PV0_SMPCSR_SEQ0;					//���وʒu�̼��ݽ
UNs		PV0_SMPCSR_SEQ1;					//���وʒu�̼��ݽ
UNs		PV0_SMPCSR_TIM;						//���وʒu�̎���
UNs		PV0_SMPCSR_POS;						//���وʒu���߲��
UNl		PV0_TRDCSR_RNAU;					//�ײ�ޏ�����o�ʒu
UNl		PV0_TRDCSR_RNAD;					//�ײ�މ������o�ʒu
UNs		PV0_TRDCSR_KJT;						//���وʒu�̍��v�׏d
UNs		PV0_TRDCSR_KJL;						//���وʒu�̍��׏d
UNs		PV0_TRDCSR_KJR;						//���وʒu�̉E�׏d
UNl		PV0_TRDCSR_RNA1;					//���وʒu�̽ײ�ވʒu
UNl		PV0_TRDCSR_RNA2;					//���وʒu�̽ײ�ވʒu
UNs		PV0_TRDCSR_TIM;						//���وʒu�̎���
UNs		PV0_TRDCSR_POS;						//���وʒu���߲��
UNs		PV0_TRDCSR_POSL;					//�-�͈ٔ�
UNs		PV0_TRDCSR_POSR;					//�-�͈ٔ�

//;	******** 2010/08/10~ *********** V05r(INS)
UNs		SEIDOU_SEQ_LST;						//
UNs		sys_1min_cnt;						//1min����
//UNs		PVTIM_seidouseinou_inter;			//�������\��������������(1min�޸�������)
//UNs		PVTIM_seidouseinou_yokok;			//�������\�����\�����(1min�޸�������)
UNs		SYO_HOS_KAJ_CNT;
UNs		PV0_INTER_TIM;						//�������\��������������(1h�޸�������)

//;	******** 2010/08/31~ *********** V06 (INS)
UNl		INTR_DAT_OFS;
UNl		INIT_DAT_OFS;
UNl		ALL_CHR_TBL_OFS;
UNl		GAM_INF_TBL_OFS;
UNs		EcoMeter_bit;
UNs		PV0_EPMCSR_HOR;						//�d�̓��j�^�J�[�\���ʒu�̎���
UNs		PV0_EPMCSR_MIN;						//�d�̓��j�^�J�[�\���ʒu�̕�
UNl		PV0_EPMCSR_UEP;						//�d�̓��j�^�J�[�\���ʒu�̏���d�͗�
UNl		PV0_EPMCSR_KEP;						//�d�̓��j�^�J�[�\���ʒu�̉񐶓d�͗�
UNl		PV0_EPMCSR_TEP;						//�d�̓��j�^�J�[�\���ʒu�̗݌v�l
UNl		PV0_EPML_SCRH;						//�d�̓��j�^�O���t���チ����
UNl		PV0_EPML_SCRM;						//�d�̓��j�^�O���t����������
UNl		PV0_EPML_SCRL;						//�d�̓��j�^�O���t����������
UNl		PV0_EPMR_SCRH;						//�d�̓��j�^�O���t�E�チ����
UNl		PV0_EPMR_SCRM;						//�d�̓��j�^�O���t�E��������
UNl		PV0_EPMR_SCRL;						//�d�̓��j�^�O���t�E��������
UNl		PV0_EPM_KWH[20][3];					//�d�̓��j�^�p�O���t�f�[�^
UNs		EPM_CSR[2];							//�d�̓��j�^�p�J�[�\���ʒu
UNs		EPM_TIM_BAK;						//�P�ʎ���
UNl		EPM_GRP_MXL;						//�_�O���t�ő�l�ς�����H
UNl		EPM_GRP_MXR;						//�܂���O���t�ő�l�ς�����H
UNs		sys_1sec_cnt;						//1sec����

//UNl		EPM_SEC_60ADD[2];					//����d�͗� 60sec�ώZ(kWs)
//UNs		EPM_SEC_60CNT;
//UNl		EPM_HOR_BUF[24*60][2];				//����d�͗� 1440��(kWs)
//UNs		EPM_HOR_POI;
UNs		EPM_GAMEN_RIF;						//�d�̓��j�^��ʃ��t���b�V���t���O

UNl		PV0_SMPCSR_EP;						//�����ݸޔg�`��ʶ��وʒu�̏u���d��
int		PV0_SMPCSR_EP_SIN;					//�����ݸޔg�`��ʶ��وʒu�̏u���d��		//V06a
UNl		PV0_TRDCSR_EP;						//����ޔg�`���   ���وʒu�̓d�͗�

UNs		SEIDOU_DSP_LST;

UNs		PV0_INTER_VER1;						/* ����ۯ��ް�ޮ� ���l */
UNs		PV0_DEFULT_VER1;					/* �����l�ް��ް�ޮ� ���l */

UNs		PV0_EPMDAT_SIN;						//�����ݸޔg�`��ʂ̓d�͒l����BIT			//V06a
UNs		EPM_TOTAL_INF;						//�d�������ʗ݌v�l�ؑւ̕\�����			//V06a
UNs		EPM_TLINF_BAK;						//�d�������ʗ݌v�l�ؑւ̕\�����			//V06a
UNs		EPM_CLR_TIM;						//�d����������ް��ر���						//V06a
UNs		EPM_CLR_FLG;						//�d������ر��t�׸�						//V06a
UNs		EPM_GAMRIF_CNT;						//�d����������گ�����ݸ޶ݳ�				//V06a

UNs		SV0_EP_AVE;


UNl		EPM_SEC_2_MESMIN_ADD[2];
UNs		EPM_SEC_MESMIN_CNT;

//V06b	UNl		EPM_05MIN_BUF[5/5][2] ;
//////	UNl		EPM_10MIN_BUF[10/5][2];
//////	UNl		EPM_15MIN_BUF[15/5][2];
//////	UNl		EPM_20MIN_BUF[20/5][2];
//////	UNl		EPM_25MIN_BUF[25/5][2];
//////	UNl		EPM_30MIN_BUF[30/5][2];
//////	UNl		EPM_35MIN_BUF[35/5][2];
//////	UNl		EPM_40MIN_BUF[40/5][2];
//////	UNl		EPM_45MIN_BUF[45/5][2];
//////	UNl		EPM_50MIN_BUF[50/5][2];
//////	UNl		EPM_55MIN_BUF[55/5][2];
//////	UNl		EPM_60MIN_BUF[60/5][2];
UNl		EPM_05MIN_BUF[5][2] ;
UNl		EPM_10MIN_BUF[10][2];
UNl		EPM_15MIN_BUF[15][2];
UNl		EPM_20MIN_BUF[20][2];
UNl		EPM_25MIN_BUF[25][2];
UNl		EPM_30MIN_BUF[30][2];
UNl		EPM_35MIN_BUF[35][2];
UNl		EPM_40MIN_BUF[40][2];
UNl		EPM_45MIN_BUF[45][2];
UNl		EPM_50MIN_BUF[50][2];
UNl		EPM_55MIN_BUF[55][2];
UNl		EPM_60MIN_BUF[60][2];

UNs		EPM_05MIN_POI;
UNs		EPM_10MIN_POI;
UNs		EPM_15MIN_POI;
UNs		EPM_20MIN_POI;
UNs		EPM_25MIN_POI;
UNs		EPM_30MIN_POI;
UNs		EPM_35MIN_POI;
UNs		EPM_40MIN_POI;
UNs		EPM_45MIN_POI;
UNs		EPM_50MIN_POI;
UNs		EPM_55MIN_POI;
UNs		EPM_60MIN_POI;

UNl		EPM_05MON_BUF[20][2];
UNl		EPM_10MON_BUF[20][2];
UNl		EPM_15MON_BUF[20][2];
UNl		EPM_20MON_BUF[20][2];
UNl		EPM_25MON_BUF[20][2];
UNl		EPM_30MON_BUF[20][2];
UNl		EPM_35MON_BUF[20][2];
UNl		EPM_40MON_BUF[20][2];
UNl		EPM_45MON_BUF[20][2];
UNl		EPM_50MON_BUF[20][2];
UNl		EPM_55MON_BUF[20][2];
UNl		EPM_60MON_BUF[20][2];

UNs		EPM_05MON_POI;
UNs		EPM_10MON_POI;
UNs		EPM_15MON_POI;
UNs		EPM_20MON_POI;
UNs		EPM_25MON_POI;
UNs		EPM_30MON_POI;
UNs		EPM_35MON_POI;
UNs		EPM_40MON_POI;
UNs		EPM_45MON_POI;
UNs		EPM_50MON_POI;
UNs		EPM_55MON_POI;
UNs		EPM_60MON_POI;

//;	******** 2010/12/06 *********** V06b (INS)
UNs		rulet_taiki_pos1;			//���]�A�U��q���̑ҋ@�_
UNs		rulet_taiki_pos2;			//		�U��q���̑ҋ@�_
UNl		SV0_TAL1_CNT;				//İ�ٶ����C���l
UNl		SV0_LOT1_CNT;				//ۯĶ���1�C���l
UNl		SV0_LOT2_CNT;				//ۯĶ���2�C���l

//;	******** 2011/01/02 *********** V06c (INS)
UNs		SV0_WORKER_COD_BAK	;		//��ƎҺ��ޑޔ�
UNl		SV0_ORDER_COD_BAK	;		//���Ժ��ޑޔ�
UNl		SV0_PLAN_CNT_BAK	;		//�v�搔�ޔ�
UNs		SV0_WORKER_COD		;		//��ƎҺ���
UNl		SV0_ORDER_COD		;		//���Ժ���
UNl		SV0_PLAN_CNT		;		//�v�搔

UNs		SV0_WORK_STR_FLG		;	//��ƊJ�n�׸ށito C/B�p�j
UNs		SV0SP_WORKER_COD	;		//��ƊJ�n����ƎҺ���
UNl		SV0SP_ORDER_COD		;		//��ƊJ�n�����Ժ���
UNl		SV0SP_PLAN_CNT		;		//��ƊJ�n���v�搔
UNl		SV0SP_BAD_CNT		;		//��ƊJ�n���s�ǐ�
UNs		SV0SP_KATA_NO		;		//��ƊJ�n���^�ԍ�
UNs		SV0SP_KATA_NAME[7]	;		//��ƊJ�n���^����
UNs		SV0SP_KATA_MEMO[7]	;		//��ƊJ�n���^����

UNs		SV0_WORK_STP_FLG		;	//��ƏI���׸ށito C/B�p�j
UNs		SV0SR_WORKER_COD	;		//��ƏI������ƎҺ���
UNl		SV0SR_ORDER_COD		;		//��ƏI�������Ժ���
UNl		SV0SR_PLAN_CNT		;		//��ƏI�����v�搔
UNl		SV0SR_BAD_CNT		;		//��ƏI�����s�ǐ�
UNs		SV0SR_KATA_NO		;		//��ƏI�����^�ԍ�
UNs		SV0SR_KATA_NAME[7]	;		//��ƏI�����^����
UNs		SV0SR_KATA_MEMO[7]	;		//��ƏI�����^����

UNs		KAT_RD_CSR_POS	;			//�^�Ǐo������CSR_TBL_POS_NOW

//;	******** 2012/09/24 *********** V06m (INS)
UNs		DIEH_OFS_FLG;
UNs		FURIKO_FLG;

//;	******** 2012/10/15 *********** V06n (INS)
UNl		SV0_RNAPOS_MAXO;
UNl		SV0_RNAPOS_MINO;
UNs		SV0_DAIHAI_LNG1O;
UNs		SV0_DAIHAI_LNG2O;
UNs		MOT_MODE_BAK;

//;	******** 2013/02/18 *********** V06p (INS)
UNs		PV0_CKSPD_OVBIT;
UNs		PV0_KATRD_BIT;
UNs		TEST_SEQ;
UNs		FURIKO_SEQ_LST;

//;	******** 2013/12/11 *********** SIT4-MC
UNb		*VRAM_Dst8;
UNs		*VRAM_Dst;
UNb		*VRAM_Src;
UNb		*VRAM_End;
UNs		GAM_COPY_FLG;
UNs		GAM_COPY_STS;

//;	******** 2014/02/06 *********** SIT4-MC
UNs		IROCK_COL_CHG_NO;

//;	******** 2014/03/13 *********** SIT4-MC
UNs		SMP_KAJ_MAX_SIN;
UNs		SMP_KAJ_MIN_SIN;
UNs		SMP_EP_MAX_SIN;
UNs		SMP_EP_MIN_SIN;
UNs		TRD_KAJ_MAX_SIN;
UNs		TRD_KAJ_MIN_SIN;
UNs		TRD_EP_MAX_SIN;
UNs		TRD_EP_MIN_SIN;
UNs		OVER_LOAD_SEL;
UNs		LOW_LIMIT_SEL;
UNs		SV0_OVLD_SEL;
UNs		SV0_LWLM_SEL;
UNs		MEM_KAJ_SEL;

//;	******** 2014/04/15 *********** SIT4-MC
UNs		PV0_CKAGL_OVBIT;

//;	******** 2014/06/04 *********** SIT4-MC
UNs		SLDTUN_RNA_SEL ;

//;	******** 2014/08/20 ***********
UNl		CAR_MICRO_KAJ_AREA;

//;	******** 2014/08/26 SIT4-MC ***********
UNl		SV0_RELE_POS	;			//�����[�X����
UNs		SV0_RELE_SNO0	;			//�����[�X�J���I���s��
UNs		SV0_RELE_AGL0	;			//�����[�X�J���I���p�x
UNs		SV0_RELE_SNO1	;			//�����[�X�J���I�t�s��
UNs		SV0_RELE_AGL1	;			//�����[�X�J���I�t�p�x
UNs		SV0_RELE_CAM	;			//�����[�X�J���ݒ�Ώ�
UNl		SV0_SEND_POS	;			//���荂��
UNs		SV0_SEND_SNO0	;			//����J���I���s��
UNs		SV0_SEND_AGL0	;			//����J���I���p�x
UNs		SV0_SEND_SNO1	;			//����J���I�t�s��
UNs		SV0_SEND_AGL1	;			//����J���I�t�p�x
UNs		SV0_SEND_CAM	;			//����J���ݒ�Ώ�
UNs		SV0_TIMING_SNO0	;			//�^�C�~���O�J���I���s��
UNs		SV0_TIMING_AGL0	;			//�^�C�~���O�J���I���p�x
UNs		SV0_TIMING_SNO1	;			//�^�C�~���O�J���I�t�s��
UNs		SV0_TIMING_AGL1	;			//�^�C�~���O�J���I�t�p�x
UNs		SV0_TIMING_CAM	;			//�^�C�~���O�J���ݒ�Ώ�
UNs		PV0_CAMATCAL_MES1;			//�J���������Z�ݒ�s���̃��b�Z�[�W�ԍ�
UNs		PV0_CAMATCAL_MES2;			//�J���������Z�ݒ�s���̃��b�Z�[�W�ԍ�
UNs		PV0_CAMATCAL_MES3;			//�J���������Z�ݒ�s���̃��b�Z�[�W�ԍ�
UNs		PV0_MOTION_INF;				//BIT0�FӰ��݂ɒ�~�s��������B
									//BIT1�FӰ��݂ɋt�]�s��������B
UNs		PV0_SINKAKU_UPDN1;			//BITn�F۰�ض�n��ON�i�p���������͈͂ɂ���B
UNs		PV0_SINKAKU_UPDN2;			//BITn�F۰�ض�n��OFF�i�p���������͈͂ɂ���B

UNs		SV0_MOT_REP;				//���[�V�����̃��s�[�g���
UNs		SV0_MOT_FIX;				//���[�V�����̈��̈���
UNs		SV0_FIXARA_AGLS;			//���̈�@�J�n�p�x
UNl		SV0_FIXARA_POSS;			//���̈�@�J�n�ʒu
UNs		SV0_FIXARA_SPDB;			//���̈�@�J�n�O���x
UNs		SV0_FIXARA_SPDF;			//���̈�@��葬�x
UNs		SV0_FIXARA_AGLE;			//���̈�@�I���p�x
UNl		SV0_FIXARA_POSE;			//���̈�@�I���ʒu
UNs		PV0_FIXBF_SPD;				//���̈�@�J�n�O���x

UNs		PV0_CAMATCAL_FLG;			//�J���o�͎����ݒ�t���O�N���A			2014/09/12

UNs		SV0_REP_FIX_FLG;			//�J��Ԃ��^���̈�  �L���^�����׸�	2014/09/23
UNs		MOT_FERR_TIM;				//F�}��ERR�M��ON����					2014/09/25

UNs		PV0_FMOTSET_MES1;			//��葬�x�ݒ莞�̃��b�Z�[�W�ԍ�		2014/10/09

//;	******** 2015/01/14 ***********
UNs		SV_1DANPRS_SRV;             /* 1�i�ږڕW�׏d */
UNs		SV_2DANPRS_SRV;             /* 2�i�ږڕW�׏d */
UNs		SV_3DANPRS_SRV;             /* 3�i�ږڕW�׏d */
UNs		SV_4DANPRS_SRV;             /* 4�i�ږڕW�׏d */
UNs		SV_5DANPRS_SRV;             /* 5�i�ږڕW�׏d */
UNs		SV_6DANPRS_SRV;             /* 6�i�ږڕW�׏d */
UNs		SV_7DANPRS_SRV;             /* 7�i�ږڕW�׏d */
UNs		SV_8DANPRS_SRV;             /* 8�i�ږڕW�׏d */
UNs		SV_9DANPRS_SRV;             /* 9�i�ږڕW�׏d */
UNs		SV_10DANPRS_SRV;            /* 10�i�ږڕW�׏d */
#if (mot100_test == 1)
UNs		SV_11DANPRS_SRV;            /* 11�i�ږڕW�׏d */
UNs		SV_12DANPRS_SRV;            /* 12�i�ږڕW�׏d */
UNs		SV_13DANPRS_SRV;            /* 13�i�ږڕW�׏d */
UNs		SV_14DANPRS_SRV;            /* 14�i�ږڕW�׏d */
UNs		SV_15DANPRS_SRV;            /* 15�i�ږڕW�׏d */
UNs		SV_16DANPRS_SRV;            /* 16�i�ږڕW�׏d */
UNs		SV_17DANPRS_SRV;            /* 17�i�ږڕW�׏d */
UNs		SV_18DANPRS_SRV;            /* 18�i�ږڕW�׏d */
UNs		SV_19DANPRS_SRV;            /* 19�i�ږڕW�׏d */
UNs		SV_20DANPRS_SRV;            /* 20�i�ږڕW�׏d */
UNs		SV_21DANPRS_SRV;            /* 21�i�ږڕW�׏d */
UNs		SV_22DANPRS_SRV;            /* 22�i�ږڕW�׏d */
UNs		SV_23DANPRS_SRV;            /* 23�i�ږڕW�׏d */
UNs		SV_24DANPRS_SRV;            /* 24�i�ږڕW�׏d */
UNs		SV_25DANPRS_SRV;            /* 25�i�ږڕW�׏d */
UNs		SV_26DANPRS_SRV;            /* 26�i�ږڕW�׏d */
UNs		SV_27DANPRS_SRV;            /* 27�i�ږڕW�׏d */
UNs		SV_28DANPRS_SRV;            /* 28�i�ږڕW�׏d */
UNs		SV_29DANPRS_SRV;            /* 29�i�ږڕW�׏d */
UNs		SV_30DANPRS_SRV;            /* 30�i�ږڕW�׏d */
UNs		SV_31DANPRS_SRV;            /* 31�i�ږڕW�׏d */
UNs		SV_32DANPRS_SRV;            /* 32�i�ږڕW�׏d */
UNs		SV_33DANPRS_SRV;            /* 33�i�ږڕW�׏d */
UNs		SV_34DANPRS_SRV;            /* 34�i�ږڕW�׏d */
UNs		SV_35DANPRS_SRV;            /* 35�i�ږڕW�׏d */
UNs		SV_36DANPRS_SRV;            /* 36�i�ږڕW�׏d */
UNs		SV_37DANPRS_SRV;            /* 37�i�ږڕW�׏d */
UNs		SV_38DANPRS_SRV;            /* 38�i�ږڕW�׏d */
UNs		SV_39DANPRS_SRV;            /* 39�i�ږڕW�׏d */
UNs		SV_40DANPRS_SRV;            /* 40�i�ږڕW�׏d */
UNs		SV_41DANPRS_SRV;            /* 41�i�ږڕW�׏d */
UNs		SV_42DANPRS_SRV;            /* 42�i�ږڕW�׏d */
UNs		SV_43DANPRS_SRV;            /* 43�i�ږڕW�׏d */
UNs		SV_44DANPRS_SRV;            /* 44�i�ږڕW�׏d */
UNs		SV_45DANPRS_SRV;            /* 45�i�ږڕW�׏d */
UNs		SV_46DANPRS_SRV;            /* 46�i�ږڕW�׏d */
UNs		SV_47DANPRS_SRV;            /* 47�i�ږڕW�׏d */
UNs		SV_48DANPRS_SRV;            /* 48�i�ږڕW�׏d */
UNs		SV_49DANPRS_SRV;            /* 49�i�ږڕW�׏d */
UNs		SV_50DANPRS_SRV;            /* 50�i�ږڕW�׏d */
UNs		SV_51DANPRS_SRV;            /* 51�i�ږڕW�׏d */
UNs		SV_52DANPRS_SRV;            /* 52�i�ږڕW�׏d */
UNs		SV_53DANPRS_SRV;            /* 53�i�ږڕW�׏d */
UNs		SV_54DANPRS_SRV;            /* 54�i�ږڕW�׏d */
UNs		SV_55DANPRS_SRV;            /* 55�i�ږڕW�׏d */
UNs		SV_56DANPRS_SRV;            /* 56�i�ږڕW�׏d */
UNs		SV_57DANPRS_SRV;            /* 57�i�ږڕW�׏d */
UNs		SV_58DANPRS_SRV;            /* 58�i�ږڕW�׏d */
UNs		SV_59DANPRS_SRV;            /* 59�i�ږڕW�׏d */
UNs		SV_60DANPRS_SRV;            /* 60�i�ږڕW�׏d */
UNs		SV_61DANPRS_SRV;            /* 61�i�ږڕW�׏d */
UNs		SV_62DANPRS_SRV;            /* 62�i�ږڕW�׏d */
UNs		SV_63DANPRS_SRV;            /* 63�i�ږڕW�׏d */
UNs		SV_64DANPRS_SRV;            /* 64�i�ږڕW�׏d */
UNs		SV_65DANPRS_SRV;            /* 65�i�ږڕW�׏d */
UNs		SV_66DANPRS_SRV;            /* 66�i�ږڕW�׏d */
UNs		SV_67DANPRS_SRV;            /* 67�i�ږڕW�׏d */
UNs		SV_68DANPRS_SRV;            /* 68�i�ږڕW�׏d */
UNs		SV_69DANPRS_SRV;            /* 69�i�ږڕW�׏d */
UNs		SV_70DANPRS_SRV;            /* 70�i�ږڕW�׏d */
UNs		SV_71DANPRS_SRV;            /* 71�i�ږڕW�׏d */
UNs		SV_72DANPRS_SRV;            /* 72�i�ږڕW�׏d */
UNs		SV_73DANPRS_SRV;            /* 73�i�ږڕW�׏d */
UNs		SV_74DANPRS_SRV;            /* 74�i�ږڕW�׏d */
UNs		SV_75DANPRS_SRV;            /* 75�i�ږڕW�׏d */
UNs		SV_76DANPRS_SRV;            /* 76�i�ږڕW�׏d */
UNs		SV_77DANPRS_SRV;            /* 77�i�ږڕW�׏d */
UNs		SV_78DANPRS_SRV;            /* 78�i�ږڕW�׏d */
UNs		SV_79DANPRS_SRV;            /* 79�i�ږڕW�׏d */
UNs		SV_80DANPRS_SRV;            /* 80�i�ږڕW�׏d */
UNs		SV_81DANPRS_SRV;            /* 81�i�ږڕW�׏d */
UNs		SV_82DANPRS_SRV;            /* 82�i�ږڕW�׏d */
UNs		SV_83DANPRS_SRV;            /* 83�i�ږڕW�׏d */
UNs		SV_84DANPRS_SRV;            /* 84�i�ږڕW�׏d */
UNs		SV_85DANPRS_SRV;            /* 85�i�ږڕW�׏d */
UNs		SV_86DANPRS_SRV;            /* 86�i�ږڕW�׏d */
UNs		SV_87DANPRS_SRV;            /* 87�i�ږڕW�׏d */
UNs		SV_88DANPRS_SRV;            /* 88�i�ږڕW�׏d */
UNs		SV_89DANPRS_SRV;            /* 89�i�ږڕW�׏d */
UNs		SV_90DANPRS_SRV;            /* 90�i�ږڕW�׏d */
UNs		SV_91DANPRS_SRV;            /* 91�i�ږڕW�׏d */
UNs		SV_92DANPRS_SRV;            /* 92�i�ږڕW�׏d */
UNs		SV_93DANPRS_SRV;            /* 93�i�ږڕW�׏d */
UNs		SV_94DANPRS_SRV;            /* 94�i�ږڕW�׏d */
UNs		SV_95DANPRS_SRV;            /* 95�i�ږڕW�׏d */
UNs		SV_96DANPRS_SRV;            /* 96�i�ږڕW�׏d */
UNs		SV_97DANPRS_SRV;            /* 97�i�ږڕW�׏d */
UNs		SV_98DANPRS_SRV;            /* 98�i�ږڕW�׏d */
UNs		SV_99DANPRS_SRV;            /* 99�i�ږڕW�׏d */
UNs		SV_100DANPRS_SRV;           /* 100�i�ږڕW�׏d */
#endif
UNs		SV_KAJOBJ_HAB;				/* �׏d�����͈� */

//;	******** 2015/01/20 ***********
UNs		TANNI_SEQ_LST;

//;	******** 2015/05/19 ***********
UNs		TRND_DTP_FLG;
UNs		chk_kjofs_dat[10];

//;	******** 2015/07/10 ***********
UNs		PV0_CKSPD_LMBIT;

//;	******** ���[�V����100�i�Ή� ***********
#if (mot100_test == 1)
UNs		SV_MOTTGT_INF0;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNs		SV_MOTTGT_INF1;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNs		SV_MOTTGT_INF2;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNs		SV_MOTTGT_INF3;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNs		SV_MOTTGT_INF4;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNs		SV_MOTTGT_INF5;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNs		SV_MOTTGT_INF6;				//�ڕW�ʒu�^�׏d�ؑ�BIT���
UNl		CAR_DO_AREA;				//�P��(��)
UNl		CAR_PAR_AREA;				//�P��(%)
UNl		CAR_TIM_AREA;				//�P��(s)
UNs		SV0_DISP_STEP_NO[5];		//���[�V������ʂ̕\������s��No.
UNs		PV0_MOT_ACT_STEP;			//���[�V������ʂŎ��s�s���̃r�b�g���i���\���p�j
UNs		csr_disp_wk[16];

//UNs		PVP_CKAGL_OVBIT1[7];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//UNs		PVP_CKLMT_AGLTOP1[100];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//UNs		PVP_CKSPD_OVBIT1[7];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//UNs		PVP_CKLMT_SPDTOP1[100];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j
//UNs		PVP_CKSPD_LMBIT1[7];		//�{����DPRAM�i��ŏ�������Ƒ��k�A���ڊ��tor�ް��������M�j

UNs		MOT_CHG_NO[5];
UNs		MOT_SEND_NO;
#endif

//;	******** �@�������ʂ̓��͐����Ή� ***********		2016/02/24
UNs		SV0_RNAORG_ENB1;				//�@�B���_���́i���͋��j
UNs		SV0_ORGCAL_ENB2;				//�@�ԁi���͋��j
UNs		SV0_ORGCAL_ENB1;				//�@��i���͋��j
UNs		SV0_MACINE_ENB1;				//�p�x�l�ؑցi���͋��j
UNs		SV0_OFSET_ENB;					//�̾�Ē����i���͋��j
UNs		SV0_KOUSEI_ENB;					//�׏d�Z���i���͋��j
UNs		SV0_MAXHIZ_ENB;					//�ő�c�i���͋��j
UNs		SV0_MAXKAJ_ENB;					//�ő�׏d�i���͋��j
UNs		SV0_KOUKAJ_ENB;					//�Z���׏d�i���͋��j

//;	******** �t�B�[�_�Ή� ***********		2016/03/18
UNl		PV0_LFEED_POS;					//����̨��ތ��݈ʒu
UNs		SV0_LFEED_SEL;					//����̨��ޗL��
UNs		SV0_LFEED_HSIS;					//����̨��ދ����ʓ�������
UNs		SV0_LFEED_HSOS;					//����̨��ދ����ʏo������
UNb		PV0_LFEED_TYPE[16];				//����̨��ތ^��ASCII
UNs		SYS0_FEED_PAR_BLK[32];			//���݂�����̨��ފ֘A��ROM���

//;	******** Ӱ���10�i��100�i�Ή� ***********		2016/04/01
UNs		kata_mot010_work[0x800/2];
UNs		kata_mot100_work[0x1800/2];

//;	******** Ӱ��݉������Ή� ***********		2016/04/15
UNs		SV0_MOT_UDSEL;					//�������L���^����
UNs		SV0_MOT_BFAF;					//���[�V�����\���y�[�W5�i���̉��������
UNs		SV_MOT_CSUD_INF0;				//���������i1�`16�s���j
UNs		SV_MOT_CSUD_INF1;				//���������i17�`32�s���j
UNs		SV_MOT_CSUD_INF2;				//���������i33�`48�s���j
UNs		SV_MOT_CSUD_INF3;				//���������i49�`64�s���j
UNs		SV_MOT_CSUD_INF4;				//���������i65�`80�s���j
UNs		SV_MOT_CSUD_INF5;				//���������i81�`96�s���j
UNs		SV_MOT_CSUD_INF6;				//���������i97�`100�s���j

//;	******** ���Ӌ@�A���@�\�ǉ��d�l ***********		2016/04/22
UNs		SQ_ORIDE_BAK;
UNs		TLINK_NEXT_LAST;
UNs		TLINK_NEXT_LAST1;
UNs		TLINK_NEXT_NO;
UNs		ADC_SW5_ON_FLG;
UNs		ADC_SW6_ON_FLG;

//;	******** ���i���[�V�����ݒ�d�l ***********		2016/09/17
UNs		PV0_MSSET_MES1;
UNs		PV0_MSSET_STG1;





//2019-04-20�̕ύX�͊ԈႢ






/***	END		***/
