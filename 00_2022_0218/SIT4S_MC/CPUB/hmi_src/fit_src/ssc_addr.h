/****************************************************************************/
/*																			*/
/*	�R�}�c�Y�@���a����	�r�h�s�|�r�R���g���[��								*/
/*																			*/
/*						�A�h���X��`�t�@�C��								*/
/*																			*/
/*						2002.06.30				FIT			mizukawa		*/
/*																			*/
/****************************************************************************/
//#define	Ver_005
#define	Ver_100


#ifdef	Ver_005

#define	E_GAMEN_BASE	0x00060000						/* �̈�擪���ڽ	*/

//#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x00004000)		/* 320�ޯ�����ݓo�^	*/
#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x0001c000)		/* 320�ޯ�����ݓo�^	*/
#define	E_GAMEN_TOP		(E_GAMEN_BASE + 0x00008000)		/* ��{�����ڽ	*/
#define	E_WINDOW_TOP	(E_GAMEN_BASE + 0x00013180)		/* ����޳�����ڽ	*/
#define	E_CHAR_TOP		(E_GAMEN_BASE + 0x00015E80)		/* ���Y�������ڽ	*/
#define	E_INTROCK_TOP	(E_GAMEN_BASE + 0x00018B08)		/* ����ۯ��������ڽ	*/
#define	E_GAMEN_TOP2	E_GAMEN_TOP						/* ���J���� ��{�����ڽ	*/

#else

#if ( SIT_TYPE_SEL == TYPE_SIT3 )
#define	E_GAMEN_BASE	0x00500000						/* �̈�擪���ڽ	*/
#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x00004000)		/* 320�ޯ�����ݓo�^	*/
#define	E_INTROCK_CHAR	(E_GAMEN_BASE + 0x00006000)		/* ����ۯ��o�͕���	*/		//2009/07/14
#define	E_GAMEN_TOP		(E_GAMEN_BASE + 0x00010000)		/* ��{�����ڽ	*/
#define	E_WINDOW_TOP	(E_GAMEN_BASE + 0x0001B180)		/* ����޳�����ڽ	*/
#define	E_CHAR_TOP		(E_GAMEN_BASE + 0x0001DE80)		/* ���Y�������ڽ	*/
#define	E_INTROCK_TOP	(E_GAMEN_BASE + 0x00020B08)		/* ����ۯ��������ڽ	*/
#define	E_GAMEN_TOP2	(E_GAMEN_BASE + 0x00028000)		/* ���J���� ��{�����ڽ	*/
#define	E_GAIZI_TOP		(E_GAMEN_BASE + 0x000A0000)		/* �O�������ڽ	*/				//V01l
#define	E_FROM_INI_TOP	(E_GAMEN_BASE + 0x00008000)		/* �ݒ�l�����ް����ڽ	*/
#define	E_FROM_INI_TOP2	(E_FROM_INI_TOP + 0x1606)		/* �ݒ�l�����ް��^���̱��ڽ	*/
#define	E_2language 	(E_GAMEN_TOP2 - E_GAMEN_TOP)/2	//���J����
#else
#define	E_GAMEN_BASE	0xB9000000						/* �̈�擪���ڽ	*/
#define	E_INTROCK_PAT	(E_GAMEN_BASE + 0x00004000)		/* 320�ޯ�����ݓo�^	*/
#define	E_INTROCK_CHAR	(E_GAMEN_BASE + 0x00006000)		/* ����ۯ��o�͕���	*/		//2009/07/14
#define	E_GAMEN_TOP		(E_GAMEN_BASE + 0x00010000)		/* ��{�����ڽ	*/
#define	E_WINDOW_TOP	(E_GAMEN_BASE + 0x0001B180)		/* ����޳�����ڽ	*/
#define	E_CHAR_TOP		(E_GAMEN_BASE + 0x0001DE80)		/* ���Y�������ڽ	*/
#define	E_INTROCK_TOP	(E_GAMEN_BASE + 0x00020B08)		/* ����ۯ��������ڽ	*/
//V06m	#define	E_GAMEN_TOP2	(E_GAMEN_BASE + 0x0001C000)		/* ���J���� ��{�����ڽ	*/
#define	E_GAMEN_TOP2	(E_GAMEN_BASE + 0x00020000)		/* ���J���� ��{�����ڽ	*/
#define	E_GAIZI_TOP		(E_GAMEN_BASE + 0x000A0000)		/* �O�������ڽ	*/				//V01l
#define	E_FROM_INI_TOP	(E_GAMEN_BASE + 0x00008000)		/* �ݒ�l�����ް����ڽ	*/
#define	E_FROM_INI_TOP2	(E_FROM_INI_TOP + 0x1606)		/* �ݒ�l�����ް��^���̱��ڽ	*/
#define	E_FROM_INI_TOP3	(E_FROM_INI_TOP + 0x3000)		/* �ݒ�l�����ް��^���̱��ڽ	*/	//V06n
#define	E_2language 	(E_GAMEN_TOP2 - E_GAMEN_TOP)	//���J����
#endif

#endif



/****************************************************************************/
