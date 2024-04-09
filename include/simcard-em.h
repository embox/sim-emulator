#ifdef __SIMCARD_EM_H__
#define __SIMCARD_EM_H__

#define SIM_FS_MF       0x3f00

/* MF level*/
#define DF_GSM          0x7f20
#define DF_TELECOM      0x7f10
#define EF_ICCID        0x2fe2

/* DFgsm level*/
#define EF_GSM_LP       0x6f05
#define EF_GSM_IMSI     0x6f07
#define EF_KC           0x6f20

/* DF telecom level*/
#define EF_TELECOM_SMS  0x6f3c

#endif   /*#ifdef __SIMCARD_EM_H__*/
