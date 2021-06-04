#ifndef NETMODULE_H
#define NETMODULE_H

#include <vector>
using namespace std;

#ifdef NETMODULE_EXPORTS
#define H264_DVR_API  extern "C" __declspec(dllexport)
#else
#define H264_DVR_API  extern "C" __declspec(dllimport)   //VC ��
#endif

typedef enum SDK_RET_CODE
{	
	H264_DVR_NOERROR					= 0,					//û�д���
	H264_DVR_SUCCESS					= 1,					//���سɹ�
	H264_DVR_SDK_NOTVALID			= -10000,				//�Ƿ�����
	H264_DVR_NO_INIT					= -10001,				//SDKδ����ʼ��
	H264_DVR_ILLEGAL_PARAM			= -10002,			//�û��������Ϸ�
	H264_DVR_INVALID_HANDLE			= -10003,			//�����Ч
	H264_DVR_SDK_UNINIT_ERROR		= -10004,			//SDK�������
	H264_DVR_SDK_TIMEOUT				= -10005,			//�ȴ���ʱ
	H264_DVR_SDK_MEMORY_ERROR		= -10006,			//�ڴ���󣬴����ڴ�ʧ��
	H264_DVR_SDK_NET_ERROR			= -10007,			//�������
	H264_DVR_SDK_OPEN_FILE_ERROR		= -10008,			//���ļ�ʧ��
	H264_DVR_SDK_UNKNOWNERROR		= -10009,			//δ֪����
	H264_DVR_DEV_VER_NOMATCH			= -11000,			//�յ����ݲ���ȷ�����ܰ汾��ƥ��
	H264_DVR_SDK_NOTSUPPORT			= -11001,			//�汾��֧��

	H264_DVR_OPEN_CHANNEL_ERROR		= -11200,			//��ͨ��ʧ��
	H264_DVR_CLOSE_CHANNEL_ERROR		= -11201,			//�ر�ͨ��ʧ��
	H264_DVR_SUB_CONNECT_ERROR		= -11202,			//����ý��������ʧ��
	H264_DVR_SUB_CONNECT_SEND_ERROR	= -11203,			//ý��������ͨѶʧ��

	

	/// �û������ִ�����
	H264_DVR_NOPOWER					= -11300,			//��Ȩ��
	H264_DVR_PASSWORD_NOT_VALID		= -11301,			// �˺����벻��
	H264_DVR_LOGIN_USER_NOEXIST		= -11302,			//�û�������
	H264_DVR_USER_LOCKED				= -11303,			// ���û�������
	H264_DVR_USER_IN_BLACKLIST		= -11304,			// ���û����������(�ں�������)
	H264_DVR_USER_HAS_USED			= -11305,			// ���û��Ե�½
	H264_DVR_USER_NOT_LOGIN			= -11306,			// ���û�û�е�½
	H264_DVR_CONNECT_DEVICE_ERROR    = -11307,			//�����豸������
	H264_DVR_ACCOUNT_INPUT_NOT_VALID = -11308,			//�û��������벻�Ϸ�
	H264_DVR_ACCOUNT_OVERLAP			= -11309,			//�����ظ�
	H264_DVR_ACCOUNT_OBJECT_NONE		= -11310,			//�����ڶ���, ���ڲ�ѯʱ
	H264_DVR_ACCOUNT_OBJECT_NOT_VALID= -11311,			//�����ڶ���
	H264_DVR_ACCOUNT_OBJECT_IN_USE	= -11312,			//��������ʹ��
	H264_DVR_ACCOUNT_SUBSET_OVERLAP	= -11313,			//�Ӽ�����Χ (�����Ȩ�޳���Ȩ�ޱ��û�Ȩ�޳������Ȩ�޷�Χ�ȵ�)
	H264_DVR_ACCOUNT_PWD_NOT_VALID	= -11314,			//���벻��ȷ
	H264_DVR_ACCOUNT_PWD_NOT_MATCH	= -11315,			//���벻ƥ��
	H264_DVR_ACCOUNT_RESERVED		= -11316,			//�����ʺ�


	/// ���ù�����ش�����
	
	H264_DVR_OPT_RESTART				= -11400,			// �������ú���Ҫ����Ӧ�ó���
	H264_DVR_OPT_REBOOT				= -11401,			// ��Ҫ����ϵͳ
	H264_DVR_OPT_FILE_ERROR			= -11402,			// д�ļ�����
	H264_DVR_OPT_CAPS_ERROR			= -11403,			// �������Բ�֧��
	H264_DVR_OPT_VALIDATE_ERROR		= -11404,			// ����У��ʧ��
	H264_DVR_OPT_CONFIG_NOT_EXIST	= -11405,			// ����������õ����ò�����
	
	/// 

	H264_DVR_CTRL_PAUSE_ERROR		= -11500,			//��ͣʧ��
	H264_DVR_SDK_NOTFOUND			= -11501,			//����ʧ�ܣ�û���ҵ���Ӧ�ļ�
};


//��̨��������
typedef enum PTZ_ControlType
{
	TILT_UP = 0,			//��̨��
	TILT_DOWN,				//��
	PAN_LEFT,				//��
	PAN_RIGHT,				//��
	PAN_LEFTTOP,			//����
	PAN_LEFTDOWN,			//����
	PAN_RIGTHTOP,			//����
	PAN_RIGTHDOWN,			//����
	ZOOM_OUT,				//�䱶С
	ZOOM_IN,				//�䱶��
	FOCUS_FAR,				//������
	FOCUS_NEAR,				//����ǰ��
	IRIS_OPEN,				//��Ȧ����
	IRIS_CLOSE,				//��Ȧ��С

	EXTPTZ_OPERATION_ALARM,			///< �������� 
	EXTPTZ_LAMP_ON,					///< �ƹ⿪
	EXTPTZ_LAMP_OFF,				//�ƹ��
	EXTPTZ_POINT_SET_CONTROL,			//����Ԥ�õ� 
	EXTPTZ_POINT_DEL_CONTROL,			//���Ԥ�õ� 
	EXTPTZ_POINT_MOVE_CONTROL,			//תԤ�õ�
	EXTPTZ_STARTPANCRUISE,			//��ʼˮƽ��ת			
	EXTPTZ_STOPPANCRUISE,			//ֹͣˮƽ��ת	
	EXTPTZ_SETLEFTBORDER,			//������߽�		
	EXTPTZ_SETRIGHTBORDER,			//�����ұ߽�	
	EXTPTZ_STARTLINESCAN,			//�Զ�ɨ�迪ʼ 
	EXTPTZ_CLOSELINESCAN,			//�Զ�ɨ�迪ֹͣ 
	EXTPTZ_ADDTOLOOP,				//����Ԥ�õ㵽Ѳ��	p1Ѳ����·	p2Ԥ�õ�ֵ	
	EXTPTZ_DELFROMLOOP,				//ɾ��Ѳ����Ԥ�õ�	p1Ѳ����·	p2Ԥ�õ�ֵ	
	EXTPTZ_POINT_LOOP_CONTROL,			//��ʼѲ��
	EXTPTZ_POINT_STOP_LOOP_CONTROL,	//ֹͣѲ��
	EXTPTZ_CLOSELOOP,				//���Ѳ��	p1Ѳ����·		
	EXTPTZ_FASTGOTO,				//���ٶ�λ	
	EXTPTZ_AUXIOPEN,				//�������أ��ر�����������
	EXTPTZ_OPERATION_MENU,				//����˵����������а��������أ�ȷ���ȵ�
	EXTPTZ_REVERSECOMM,				//��ͷ��ת
	EXTPTZ_OPERATION_RESET,			///< ��̨��λ

	EXTPTZ_TOTAL,
};


#define PAN_AUTO		29	/* ��̨��SS���ٶ������Զ�ɨ�� */
#define EXTPTZ_FASTGOTO	30	//��ά��λ


#define NET_MAX_CHANNUM 			32			//���ͨ������
#define NET_DECORDR_CH              16          //������ͨ������
#define NET_MAX_USER_NUM			60			//����û���
#define NET_MAX_RIGTH_NUM			128			//���Ȩ����
#define NET_MAX_GROUP_NUM			50			//�������
#define NET_MAX_USER_LENGTH			32			//�û���������󳤶�
#define NET_MAX_COMBINE_NUM			2			//�����ϱ���ͨ����
#define NET_MAX_DECORDR_CH          16          //������ͨ������

#define NET_MAX_DDNS_TYPE			5			//֧�ֵ�DDNS����
#define NET_MAX_ARSP_TYPE			5
#define NET_MAX_ALARMSERVER_TYPE    5           //֧�ֱ�����������
#define NET_MAX_SYSFUNC				20			//���ϵͳ���ܸ���
#define NET_MAX_PTZ_PROTOCOL_LENGTH 32			//��̨Э��������󳤶�
#define NET_N_WEEKS					7			//������
#define	NET_N_TSECT					6			//ʱ�����
#define NET_MD_REGION_ROW			32			//��̬�����������
#define NET_COVERNUM				8			 //����������
#define NET_MAX_FILTERIP_NUM		64			//IP��ַ��������
#define NET_NAME_PASSWORD_LEN		64			//�û���������󳤶�
#define NET_MAX_PATH_LENGTH	        260			//·������
#define NET_N_MIN_TSECT				2
#define NET_MAX_RETURNED_LOGLIST	128			//�����־����
#define NET_MAX_MAC_LEN             32          //MAC��ַ�ַ���󳤶�
#define NET_IW_ENCODING_TOKEN_MAX   128
#define NET_MAX_AP_NUMBER           10
#define NET_MAX_INFO_LEN		    128

//ʵʱԤ����չ�ӿ����ӵĲ�����Ԥ������
typedef enum _H264_DVR_RealPlayType
{
	NET_RType_Realplay = 0,	//ʵʱԤ��
	NET_RType_Main_Realplay2,	//ʵʱ����-����������ͬ��NET_RType_Realplay
	NET_RType_Main_Realplay3,
	NET_RType_Sub_Realplay_1,	//ʵʱ����-������1
	NET_RType_Sub_Realplay_2,	//ʵʱ����-������2
	NET_RType_Sub_Realplay_3,	//ʵʱ����-������3

	NET_RType_Multiplay_1,	//�໭��Ԥ����1����
	NET_RType_Multiplay_4,	//�໭��Ԥ����4����
	NET_RType_Multiplay_6,	//�໭��Ԥ����6����
	NET_RType_Multiplay_8,	//�໭��Ԥ����8����
	NET_RType_Multiplay_9,	//�໭��Ԥ����9����
	NET_RType_Multiplay_12,	//�໭��Ԥ����12����
	NET_RType_Multiplay_16,	//�໭��Ԥ����16����
} NET_RealPlayType;

/// ��ϱ���ģʽ
enum NetCombinType
{
	NET_COMBIN_NONE,
	NET_COMBIN_1,
	NET_COMBIN_2,
	NET_COMBIN_3,
	NET_COMBIN_4,
	NET_COMBIN_5,
	NET_COMBIN_6,
	NET_COMBIN_7,
	NET_COMBIN_8,
	NET_COMBIN_9,
	NET_COMBIN_10,
	NET_COMBIN_11,
	NET_COMBIN_12,
	NET_COMBIN_13,
	NET_COMBIN_14,
	NET_COMBIN_15,
	NET_COMBIN_16,
	NET_COMBIN_1_4,
	NET_COMBIN_5_8,
	NET_COMBIN_9_12,
	NET_COMBIN_13_16,
	NET_COMBIN_1_8,
	NET_COMBIN_9_16,
	NET_COMBIN_1_9,
	NET_COMBIN_8_16,
	NET_COMBIN_1_16
};

//��Щ�ṹ���ö�����ṩ���ⲿʹ�ã����п��ܻ���豸�Ǳ߶�����2��,���Զ���ǰ�����SDK_
enum SDK_CAPTURE_SIZE_t {
	SDK_CAPTURE_SIZE_D1,		///< 720*576(PAL)	720*480(NTSC)
	SDK_CAPTURE_SIZE_HD1,		///< 352*576(PAL)	352*480(NTSC)
	SDK_CAPTURE_SIZE_BCIF,		///< 720*288(PAL)	720*240(NTSC)
	SDK_CAPTURE_SIZE_CIF,		///< 352*288(PAL)	352*240(NTSC)
	SDK_CAPTURE_SIZE_QCIF,		///< 176*144(PAL)	176*120(NTSC)
	SDK_CAPTURE_SIZE_VGA,		///< 640*480(PAL)	640*480(NTSC)
	SDK_CAPTURE_SIZE_QVGA,		///< 320*240(PAL)	320*240(NTSC)
	SDK_CAPTURE_SIZE_SVCD,		///< 480*480(PAL)	480*480(NTSC)
	SDK_CAPTURE_SIZE_QQVGA,		///< 160*128(PAL)	160*128(NTSC)
	SDK_CAPTURE_SIZE_NR			///< ö�ٵ�ͼ�δ�С�������Ŀ��
};

/// ������������ģʽ����
enum SDK_capture_brc_t {
	SDK_CAPTURE_BRC_CBR,			///< �̶�������
	SDK_CAPTURE_BRC_VBR,			///< �ɱ�������
	SDK_CAPTURE_BRC_MBR,			///< ���������
	SDK_CAPTURE_BRC_NR				///< ö�ٵ���������ģʽ��Ŀ��
};

/// ����ѹ����ʽ����
enum SDK_CAPTURE_COMP_t {
	SDK_CAPTURE_COMP_DIVX_MPEG4,	///< DIVX MPEG4��
	SDK_CAPTURE_COMP_MS_MPEG4,		///< MS MPEG4��
	SDK_CAPTURE_COMP_MPEG2,			///< MPEG2��
	SDK_CAPTURE_COMP_MPEG1,			///< MPEG1��
	SDK_CAPTURE_COMP_H263,			///< H.263
	SDK_CAPTURE_COMP_MJPG,			///< MJPG
	SDK_CAPTURE_COMP_FCC_MPEG4,		///< FCC MPEG4
	SDK_CAPTURE_COMP_H264,			///< H.264
	SDK_CAPTURE_COMP_NR				///< ö�ٵ�ѹ����׼��Ŀ��
};

/// ����ͨ������
enum SDK_CAPTURE_CHANNEL_t {
	SDK_CHL_MAIN_T = 0,		///< ��ͨ��	��	������1 
	SDK_CHL_2END_T = 1,		///< ��ͨ��	��	��������2 
	SDK_CHL_3IRD_T = 2,		///< ��ͨ��	��	��������3 
	SDK_CHL_4RTH_T = 3,		///< ��ͨ��	��	��������4 
	SDK_CHL_JPEG_T = 4,		///< ��ͨ��	��	��JPEGץͼ 
	SDK_CHL_FUNCTION_NUM
};
/// ��Ƶ��������
enum SDK_AudioEncodeTypes
{
	SDK_AUDIO_ENCODE_NONE = 0,
	SDK_AUDIO_ENCODE_G729_8KBIT,
	SDK_AUDIO_ENCODE_G726_16KBIT,
	SDK_AUDIO_ENCODE_G726_24KBIT,
	SDK_AUDIO_ENCODE_G726_32KBIT,
	SDK_AUDIO_ENCODE_G726_40KBIT,
	SDK_AUDIO_ENCODE_PCM_8TO16BIT,
	SDK_AUDIO_ENCODE_PCM_ALAW,
	SDK_AUDIO_ENCODE_PCM_ULAW,
	SDK_AUDIO_ENCODE_ADPCM8K16BIT,
	SDK_AUDIO_ENCODE_ADPCM16K16BIT,
	SDK_AUDIO_ENCODE_G711_ALAW,
	SDK_AUDIO_ENCODE_MPEG2_LAYER1,
	SDK_AUDIO_ENCODE_AMR8K16BIT,
	SDK_AUDIO_ENCODE_G711_ULAW,
	SDK_AUDIO_ENCODE_IMA_ADPCM_8K16BIT,
	SDK_AUDIO_ENCODE_TYPES_NR,
};



//��������
typedef enum _SDK_CONFIG_TYPE
{
	E_SDK_CONFIG_NOTHING = 0,		//
	E_SDK_CONFIG_USER,			//�û���Ϣ��������Ȩ���б��û��б�����б�
	E_SDK_CONFIG_ADD_USER,		//�����û�
	E_SDK_CONFIG_MODIFY_USER,		//�޸��û�
	E_SDK_CONFIG_DELETE_USER,
	E_SDK_CONFIG_ADD_GROUP,		//������
	E_SDK_CONFIG_MODIFY_GROUP,	//�޸���
	E_SDK_COFIG_DELETE_GROUP,
	E_SDK_CONFIG_MODIFY_PSW,		//�޸�����


	E_SDK_CONFIG_ABILITY_SYSFUNC = 9,//֧�ֵ����繦��
	E_SDK_CONFIG_ABILTY_ENCODE,	//���Ȼ�ñ�������
	E_SDK_CONFIG_ABILITY_PTZPRO,	//��̨Э��
	E_SDK_COMFIG_ABILITY_COMMPRO,	//����Э��
	E_SDK_CONFIG_ABILITY_MOTION_FUNC,	//��̬����
	E_SDK_CONFIG_ABILITY_BLIND_FUNC,	//��Ƶ�ڵ���
	E_SDK_CONFIG_ABILITY_DDNS_SERVER,	//DDNS����֧������
	E_SDK_CONFIG_ABILITY_TALK,		//�Խ���������


	E_SDK_CONFIG_SYSINFO = 17,		//ϵͳ��Ϣ
	E_SDK_CONFIG_SYSNORMAL,	//��ͨ����
	E_SDK_CONFIG_SYSENCODE,	//��������
	E_SDK_CONFIG_SYSNET,		//��������
	E_SDK_CONFIG_PTZ,			//��̨ҳ��
	E_SDK_CONFIG_COMM,		//����ҳ��
	E_SDK_CONFIG_RECORD,		//¼�����ý���
	E_SDK_CONFIG_MOTION,		//��̬���ҳ��
	E_SDK_CONFIG_SHELTER,		//��Ƶ�ڵ�
	E_SDK_CONFIG_VIDEO_LOSS,  //��Ƶ��ʧ,
	E_SDK_CONFIG_ALARM_IN,	//��������
	E_SDK_CONFIG_ALARM_OUT,	//�������
	E_SDK_CONFIG_DISK_MANAGER,//Ӳ�̹������
	E_SDK_CONFIG_OUT_MODE,	//���ģʽ����
	E_SDK_CONFIG_CHANNEL_NAME,//ͨ������
	E_SDK_CONFIG_AUTO,		//�Զ�ά����������
	E_SDK_CONFIG_DEFAULT,     //�ָ�Ĭ�Ͻ�������
	E_SDK_CONFIG_DISK_INFO,	//Ӳ����Ϣ
	E_SDK_CONFIG_LOG_INFO,	//��ѯ��־
	E_SDK_CONFIG_NET_IPFILTER,
	E_SDK_CONFIG_NET_DHCP,
	E_SDK_CONFIG_NET_DDNS,
	E_SDK_CONFIG_NET_EMAIL,
	E_SDK_CONFIG_NET_MULTICAST,
	E_SDK_CONFIG_NET_NTP,
	E_SDK_CONFIG_NET_PPPOE,
	E_SDK_CONFIG_NET_DNS,
	E_SDK_CONFIG_NET_FTPSERVER,
	
	E_SDK_CONFIG_SYS_TIME,	//ϵͳʱ��
	E_SDK_CONFIG_CLEAR_LOG,	//�����־
	E_SDK_REBOOT_DEV,		//���������豸
	E_SDK_CONFIG_ABILITY_LANG,	//֧������
	E_SDK_CONFIG_VIDEO_FORMAT,
	E_SDK_CONFIG_COMBINEENCODE,	//��ϱ���
	E_SDK_CONFIG_EXPORT,	//���õ���
	E_SDK_CONFIG_IMPORT,	//���õ���
	E_SDK_LOG_EXPORT,		//��־����
	E_SDK_CONFIG_COMBINEENCODEMODE, //��ϱ���ģʽ
	E_SDK_WORK_STATE,	//����״̬
	E_SDK_ABILITY_LANGLIST, //ʵ��֧�ֵ����Լ�
	E_SDK_CONFIG_NET_ARSP,
	E_SDK_CONFIG_SNAP_STORAGE,
	E_SDK_CONFIG_NET_3G, //3G����
	E_SDK_CONFIG_NET_MOBILE, //�ֻ����
	E_SDK_CONFIG_UPGRADEINFO, //��ȡ������Ϣ
	E_SDK_CONFIG_NET_DECODER,
	E_SDK_ABILITY_VSTD, //ʵ��֧�ֵ���Ƶ��ʽ
	E_SDK_CONFIG_ABILITY_VSTD,	//֧����Ƶ��ʽ
	E_SDK_CONFIG_NET_UPNP, //UPUN����
	E_SDK_CONFIG_NET_WIFI,
	E_SDK_CONFIG_NET_WIFI_AP_LIST,
	E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, //�򻯵ı�������
	E_SDK_CONFIG_ALARM_CENTER,  //�澯����
	E_SDK_CONFIG_NET_ALARM,
}SDK_CONFIG_TYPE;



/// �����¼���
enum SDK_EventCodeTypes
{
	SDK_EVENT_CODE_INIT = 0,
	SDK_EVENT_CODE_LOCAL_ALARM = 1,	//���ر���
	SDK_EVENT_CODE_NET_ALARM,		//���籨��
	SDK_EVENT_CODE_MANUAL_ALARM,	//�ֶ�����
	SDK_EVENT_CODE_VIDEO_MOTION,	//��̬���
	SDK_EVENT_CODE_VIDEO_LOSS,		//��Ƶ��ʧ
	SDK_EVENT_CODE_VIDEO_BLIND,		//��Ƶ�ڵ�
	SDK_EVENT_CODE_VIDEO_TITLE,		
	SDK_EVENT_CODE_VIDEO_SPLIT,
	SDK_EVENT_CODE_VIDEO_TOUR,
	SDK_EVENT_CODE_STORAGE_NOT_EXIST,
	SDK_EVENT_CODE_STORAGE_FAILURE,
	SDK_EVENT_CODE_LOW_SPACE,
	SDK_EVENT_CODE_NET_ABORT,
	SDK_EVENT_CODE_COMM,
	SDK_EVENT_CODE_STORAGE_READ_ERROR,
	SDK_EVENT_CODE_STORAGE_WRITE_ERROR,
	SDK_EVENT_CODE_NET_IPCONFLICT,
	SDK_EVENT_CODE_ALARM_EMERGENCY,
	SDK_EVENT_CODE_DEC_CONNECT,
	SDK_EVENT_CODE_NR,
};
//! �������õ�����
enum SDK_ENCODE_TYPE_BY_RECORD
{
	SDK_ENCODE_TYPE_TIM = 0,
	SDK_ENCODE_TYPE_MTD = 1,
	SDK_ENCODE_TYPE_ALM = 2,
	SDK_ENCODE_TYPE_NUM = 3,
	SDK_ENCODE_TYPE_SNAP_TIMER = 0,
	SDK_ENCODE_TYPE_SNAP_TRIGGER = 1,
};
#define SDK_EXTRATYPES 3 //����������

//���紫�����
enum SDK_TransferPolicy
{
	SDK_TRANSFER_POLICY_AUTO,		///< ����Ӧ
	SDK_TRANSFER_POLICY_QUALITY,	///< ��������
	SDK_TRANSFER_POLICY_FLUENCY,	///< ��������
	SDK_TRANSFER_POLICY_NR,
};



typedef struct {
	int left;
	int top;
	int right;
	int bottom;
}sdkRect;

/// ��Ƶ�����ʽ�������Խ���
struct SDK_AudioInFormatConfig
{
	int iBitRate;	   ///< ������С��kbpsΪ��λ������192kbps��128kbps
	int iSampleRate;   ///< �����ʣ�HzΪ��λ������44100Hz
	int iSampleBit;    ///< ������λ��
	int iEncodeType;   ///< ���뷽ʽ������AudioEncodeTypes����
};

//�����Խ���ʽ
typedef enum __TALK_CODING_TYPE
{
	TALK_DEFAULT = 0,
	TALK_PCM = 1,					//PCM
	TALK_G711a,						//G711a
	TALK_AMR,						//AMR
	TALK_G711u,						//G711u
	TALK_G726,						//G726
}TALK_CODING_TYPE;
//�����Խ�
typedef struct  
{
	TALK_CODING_TYPE		encodeType;		//��������
	int						nAudioBit;		//��ʵ�ʵ�ֵ��ʾ����8λ ����ֵΪ8
	unsigned int			dwSampleRate;	//�����ʣ���16k ����ֵΪ16000
	char					reserved[64];
}H264_DVR_TALKDECODE_INFO;


/// ϵͳʱ��ṹ
typedef struct SDK_SYSTEM_TIME{
	int  year;///< �ꡣ   
	int  month;///< �£�January = 1, February = 2, and so on.   
	int  day;///< �ա�   
	int  wday;///< ���ڣ�Sunday = 0, Monday = 1, and so on   
	int  hour;///< ʱ��   
	int  minute;///< �֡�   
	int  second;///< �롣   
	int  isdst;///< ����ʱ��ʶ��   
}SDK_SYSTEM_TIME;

//¼��������ؽṹ��
typedef struct tagSDK_TIMESECTION
{
	//!ʹ��
	int enable;
	//!��ʼʱ��:Сʱ
	int startHour;
	//!��ʼʱ��:����
	int	startMinute;
	//!��ʼʱ��:����
	int	startSecond;
	//!����ʱ��:Сʱ
	int	endHour;
	//!����ʱ��:����
	int	endMinute;
	//!����ʱ��:����
	int	endSecond;
}SDK_TIMESECTION;	

typedef struct{
	int dwYear;		//��
	int dwMonth;	//��
	int dwDay;		//��
	int dwHour;		//ʱ
	int dwMinute;	//��
	int dwSecond;	//��
}H264_DVR_TIME,*LPH264_DVR_TIME;

//ʱ��ṹ
typedef struct _NEW_NET_TIME								
{
	unsigned int second			:6;					//	��	1-60		
	unsigned int minute			:6;					//	��	1-60		
	unsigned int hour			:5;					//	ʱ	1-24		
	unsigned int day			:5;					//	��	1-31		
	unsigned int month			:4;					//	��	1-12		
	unsigned int year			:6;					//	��	2000-2063	
}NEW_NET_TIME, *LPNET_TIME;
///< ����ʱ�ṹ
struct DSTPoint
{
	int	iYear;
	int	iMonth;
	int	iWeek;		///<��1:first  to2 3 4 -1:last one   0:��ʾʹ�ð��ռ���ķ���[-1,4]
	int	iWeekDay;	///<weekday from sunday=0	[0, 6]
	int Hour;
	int Minute;
};

struct SDK_VIDEO_FORMAT
{
	int		iCompression;			//  ѹ��ģʽ 	
	int		iResolution;			//  �ֱ��� ����ö��capture_size_t 	
	int		iBitRateControl;		//  �������� ����ö��capture_brc_t
	int		iQuality;				//  �����Ļ��� ����1-6		
	int		nFPS;					//  ֡��ֵ��NTSC/PAL������,������ʾ����һ֡		
	int		nBitRate;				//  0-4096k,���б���Ҫ�ɿͻ��˱��棬�豸ֻ����ʵ�ʵ�����ֵ�������±ꡣ
	int		iGOP;					//  ��������I֮֡��ļ��ʱ�䣬2-12 
} ;
struct  SDK_AUDIO_FORMAT
{
	int		nBitRate;				//  ����kbps	
	int		nFrequency;				//  ����Ƶ��	
	int		nMaxVolume;				//  ���������ֵ
} ;
// ý���ʽ
struct SDK_MEDIA_FORMAT
{
	SDK_VIDEO_FORMAT vfFormat;			//  ��Ƶ��ʽ���� 			
	SDK_AUDIO_FORMAT afFormat;			//  ��Ƶ��ʽ���� 
	bool	bVideoEnable;				//  ������Ƶ���� 
	bool	bAudioEnable;				//  ������Ƶ���� 	
} ;

typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int 	l;
}CONFIG_IPAddress;








///////////////////�û��ʺŹ�����ؽṹ��/////////////////////////////////
typedef struct _OPR_RIGHT
{
	char name[NET_MAX_USER_LENGTH];
}OPR_RIGHT;

typedef struct _USER_INFO
{
	int			rigthNum;
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];
	char		Groupname[NET_MAX_USER_LENGTH];
	char		memo[NET_MAX_USER_LENGTH];
	char		name[NET_MAX_USER_LENGTH];
	char		passWord[NET_MAX_USER_LENGTH];
	bool		reserved;		//�Ƿ���
	bool		shareable;		//���û��Ƿ������� 1-���ã�0-������
}USER_INFO;

typedef struct _USER_GROUP_INFO
{
	int			rigthNum;
	char		memo[NET_MAX_USER_LENGTH]; 
	char		name[NET_MAX_USER_LENGTH];
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];	//Ȩ���б�
}USER_GROUP_INFO;

//�û���Ϣ���ýṹ
typedef struct _USER_MANAGE_INFO
{
	int					rigthNum;
	OPR_RIGHT			rightList[NET_MAX_RIGTH_NUM];
	int					groupNum;
	USER_GROUP_INFO		groupList[NET_MAX_GROUP_NUM];
	int					userNum;
	USER_INFO			userList[NET_MAX_USER_NUM];
}USER_MANAGE_INFO;

//�޸��û�
typedef struct _CONF_MODIFYUSER
{
	char UserName[NET_MAX_USER_LENGTH];
	USER_INFO User;
}CONF_MODIFYUSER;

//�޸���
typedef struct _CONF_MODIFYGROUP
{
	char GroupName[NET_MAX_USER_LENGTH];
	USER_GROUP_INFO Group;
}CONF_MODIFYGROUP;


/// �޸��û���������
struct _CONF_MODIFY_PSW
{
	char sUserName[NET_MAX_USER_LENGTH];
	char Password[NET_MAX_USER_LENGTH];
	char NewPassword[NET_MAX_USER_LENGTH];
};

//��ͨ����ҳ�ṹ��
typedef struct _SDK_CONFIG_NORMAL
{	
	SDK_SYSTEM_TIME sysTime;		//ϵͳʱ��

	int iLocalNo;			/*!< �������:[0, 998] */
	int iOverWrite;			/*!< Ӳ����ʱ���� "OverWrite", "StopRecord" */		
	int iSnapInterval;			///< ��ʱץͼ��ʱ����������Ϊ��λ 
	char sMachineName[64];	///< ������
	int iVideoStartOutPut;	/*!< ���ģʽ */
	int iAutoLogout;			///< ���ز˵��Զ�ע��(����)	[0, 120]

	int iVideoFormat;		/*!< ��Ƶ��ʽ:��PAL��, ��NTSC��, ��SECAM�� */
	int iLanguage;			/*!< ����ѡ��:��English��, ��SimpChinese��, ��TradChinese��, ��Italian��, ��Spanish��, ��Japanese��, ��Russian��, ��French��, ��German�� */	
	int iDateFormat;		/*!< ���ڸ�ʽ:��YYMMDD��, ��MMDDYY��, ��DDMMYY�� */
	int iDateSeparator;		/*!< ���ڷָ��:��.��, ��-��, ��/�� */
	int iTimeFormat;		/*!< ʱ���ʽ:��12��, ��24�� */
	int iDSTRule;			///< ����ʱ���� 
	int iWorkDay;			///< ������
	DSTPoint dDSTStart;
	DSTPoint dDSTEnd;
}SDK_CONFIG_NORMAL;


//���±����������
// ��������
struct SDK_CONFIG_ENCODE
{
	SDK_MEDIA_FORMAT dstMainFmt[SDK_ENCODE_TYPE_NUM];		//  ��������ʽ 	
	SDK_MEDIA_FORMAT dstExtraFmt[SDK_EXTRATYPES];	//  ��������ʽ 
	SDK_MEDIA_FORMAT dstSnapFmt[SDK_ENCODE_TYPE_NUM];		//  ץͼ��ʽ 
};
struct  SDK_EncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_CHANNUM];
};


// �򻯰汾��������
/// ý���ʽ
struct SDK_MEDIA_FORMAT_SIMPLIIFY
{
	SDK_VIDEO_FORMAT vfFormat;			//  ��Ƶ��ʽ���� 			
	bool	bVideoEnable;			//  ������Ƶ���� 
	bool	bAudioEnable;			//  ������Ƶ���� 	
};

/// ��������
struct SDK_CONFIG_ENCODE_SIMPLIIFY
{
	SDK_MEDIA_FORMAT dstMainFmt;		//  ��������ʽ 	
	SDK_MEDIA_FORMAT dstExtraFmt;	//  ��������ʽ 
};

/// ȫͨ����������
struct SDK_EncodeConfigAll_SIMPLIIFY
{
	SDK_CONFIG_ENCODE_SIMPLIIFY vEncodeConfigAll[NET_MAX_CHANNUM];
};


struct  SDK_CombineEncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_COMBINE_NUM];
};

/// ��ϱ���ģʽ
struct SDK_CombEncodeParam
{
	int iEncodeMode;	 //��CombineEncodeMode
};

struct SDK_CombEncodeModeAll
{
	SDK_CombEncodeParam vEncodeParam[NET_MAX_COMBINE_NUM];
};

//!��Ƶ����ṹ
struct  SDK_VIDEO_WIDGET
{
	unsigned int rgbaFrontground;		///< �����ǰ��MakeRGB����͸����	
	unsigned int rgbaBackground;		///< ����ĺ�MakeRGB����͸����	
	sdkRect	rcRelativePos;			///< ����߾��������ı���*8191
	bool	bPreviewBlend;			///< Ԥ������	
	bool	bEncodeBlend;			///< �������
};

//!��Ƶ�������
struct SDK_CONFIG_VIDEOWIDGET
{
	SDK_VIDEO_WIDGET	dstCovers[NET_COVERNUM];
	SDK_VIDEO_WIDGET	ChannelTitle;
	SDK_VIDEO_WIDGET	TimeTitle;
	struct 
	{
		char strName[NET_NAME_PASSWORD_LEN];
		__int64 iSerialNo;	
	}ChannelName;					/// ͨ������
	int				iCoverNum;		/*!< ��ǰ��ͨ���м������ӵ����� */
};

/// ��Ƶ���(���ģʽ�Ի���)
struct SDK_VideoWidgetConfigAll
{
	SDK_CONFIG_VIDEOWIDGET vVideoWidegetConfigAll[NET_MAX_CHANNUM];
};

/// ����ͨ�����Ʊ���
struct SDK_ChannelNameConfigAll
{
	char channelTitle[NET_MAX_CHANNUM][NET_NAME_PASSWORD_LEN];
};


////!��ͨ��������
struct SDK_CONFIG_NET_COMMON
{
	//!������
	char HostName[NET_NAME_PASSWORD_LEN];
	//!����IP
	CONFIG_IPAddress HostIP;
	//!��������
	CONFIG_IPAddress Submask;
	//!����IP
	CONFIG_IPAddress Gateway;
	//!HTTP����˿�
	int HttpPort;
	//!TCP�����˿�
	int TCPPort;	
	//!SSL�����˿�
	int SSLPort;
	//!UDP�����˿�
	int UDPPort;
	//!���������
	int MaxConn;
	//!����Э�� {"TCP","UDP","MCAST",��}
	int MonMode;
	//!�޶�����ֵ
	int MaxBps;
	//!�������
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!�Ƿ����ø���¼�����ز���
	bool bUseHSDownLoad;

	//!MAC��ַ
	char sMac[NET_MAX_MAC_LEN];
};

//DHCP
struct SDK_NetDHCPConfig
{
	bool bEnable;
	char ifName[32];
};
/// ����������DHCP����
struct SDK_NetDHCPConfigAll
{
	SDK_NetDHCPConfig vNetDHCPConfig[2];
};

///< DNS����
struct SDK_NetDNSConfig
{
	CONFIG_IPAddress		PrimaryDNS;
	CONFIG_IPAddress		SecondaryDNS;
};
///< �������ṹ����
struct SDK_RemoteServerConfig
{
	char ServerName[NET_NAME_PASSWORD_LEN];	///< ������
	CONFIG_IPAddress ip;						///< IP��ַ
	int Port;							///< �˿ں�
	char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
	char Password[NET_NAME_PASSWORD_LEN];		///< ����	
	bool Anonymity;							///< �Ƿ�������¼
};
///< IPȨ������
struct SDK_NetIPFilterConfig
{
	bool Enable;		///< �Ƿ���
	CONFIG_IPAddress BannedList[NET_MAX_FILTERIP_NUM];		///< �������б�
	CONFIG_IPAddress TrustList[NET_MAX_FILTERIP_NUM];		///< �������б�
};

///< �鲥����
struct SDK_NetMultiCastConfig
{
	bool Enable;		///< �Ƿ���
	SDK_RemoteServerConfig Server;		///< �鲥������
};

///< pppoe����
struct SDK_NetPPPoEConfig
{
	bool Enable;	///< �Ƿ���
	SDK_RemoteServerConfig Server;		///< PPPOE������
	CONFIG_IPAddress addr;		///< ���ź��õ�IP��ַ
};

///< DDNS����
struct SDK_NetDDNSConfig
{
	bool Enable;	///< �Ƿ���
	char DDNSKey[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
	char HostName[NET_NAME_PASSWORD_LEN];	///< ������
	SDK_RemoteServerConfig Server;			///< DDNS������
};

///< DDNS����
struct SDK_NetDDNSConfigALL
{
	SDK_NetDDNSConfig ddnsConfig[NET_MAX_DDNS_TYPE];
};

///< FTP����
struct SDK_FtpServerConfig{
	bool bEnable;        ///< ������ʹ��     
	SDK_RemoteServerConfig Server;	///< FTP������
	char cRemoteDir[NET_MAX_PATH_LENGTH];	///< Զ��Ŀ¼
	int iMaxFileLen;	///< �ļ���󳤶�
};

///< NTP����
struct SDK_NetNTPConfig
{
	///< �Ƿ���
	bool Enable;
	///< PPPOE������
	SDK_RemoteServerConfig Server;
	///< ��������
	int UpdatePeriod;
	///< ʱ��
	int TimeZone;
};
#define  NET_MAX_EMAIL_TITLE_LEN 64
#define  NET_MAX_EMAIL_RECIEVERS  5
#define  NET_EMAIL_ADDR_LEN  32

///< EMAIL����
struct SDK_NetEmailConfig
{
	///< �Ƿ���
	bool Enable;
	///< smtp ��������ַʹ���ַ�����ʽ���
	///< ������ip,Ҳ����������
	SDK_RemoteServerConfig Server;
	bool bUseSSL;
	///< ���͵�ַ
	char SendAddr[NET_EMAIL_ADDR_LEN];
	///< �����˵�ַ
	char Recievers[NET_MAX_EMAIL_RECIEVERS][NET_EMAIL_ADDR_LEN];
	///< �ʼ�����
	char Title[NET_MAX_EMAIL_TITLE_LEN];
	///< email��Чʱ��
	SDK_TIMESECTION Schedule[NET_N_MIN_TSECT];
};

///< ARSP(����ע�������)����
struct SDK_NetARSPConfig
{
	bool bEnable;	///< �Ƿ���
	char sARSPKey[NET_NAME_PASSWORD_LEN];	///< DNS��������
	int iInterval;	///< ������ʱ��
	char sURL[NET_NAME_PASSWORD_LEN];    ///< ��������
	SDK_RemoteServerConfig Server;		///< DDNS������
};

struct SDK_NetARSPConfigAll
{
	SDK_NetARSPConfig vNetARSPConfigAll[NET_MAX_ARSP_TYPE];
};

///< ��������ַ����
struct SDK_NetDecorderConfig
{
	bool Enable;						///< �Ƿ���
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< ������
	char Address[NET_NAME_PASSWORD_LEN];
	int Protocol;
	int Port;							///< ���������Ӷ˿�
	int Channel;						///< ����������ͨ����
};

/// ��������ַ����
struct SDK_NetDecorderConfigAll
{
	SDK_NetDecorderConfig vNetDecorderConfig[NET_MAX_DECORDR_CH];
};

///< 3G��������
struct SDK_Net3GConfig
{
	bool bEnable;			  ///< ����ģ��ʹ�ܱ�־
	int iNetType;			  ///< ������������
	char sAPN[NET_NAME_PASSWORD_LEN];		///< ���������
	char sDialNum[NET_NAME_PASSWORD_LEN];   ///< ���ź���
	char sUserName[NET_NAME_PASSWORD_LEN];  ///< �����û���
	char sPassword[NET_NAME_PASSWORD_LEN];  ///< ��������
	CONFIG_IPAddress addr;			  ///< ���ź��õ�IP��ַ
};

///< �ֻ�������ð���
struct SDK_NetMoblieConfig
{
	bool bEnable;	///< �Ƿ���
	SDK_RemoteServerConfig Server;		///< ������
};

///< UPNP����
struct SDK_NetUPNPConfig
{
	bool bEnable;			  ///< ʹ�ܱ�־
	bool bState;              ///< ״̬, 1: OK 0: NOK
	int iHTTPPort;			  ///< HTTP����ӳ���Ķ˿�
	int iMediaPort;			  ///< ý������ӳ���Ķ˿�
	int iMobliePort;		  ///< �ֻ����ӳ���Ķ˿�
};

///< WIFI����
struct SDK_NetWifiConfig
{
	bool bEnable;
	char sSSID[36];            //SSID Number
	int nChannel;                   //channel
	char sNetType[32];         //Infra, Adhoc
	char sEncrypType[32];      //NONE, WEP, TKIP, AES
	char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
	int  nKeyType;                  //0:Hex 1:ASCII
	char sKeys[NET_IW_ENCODING_TOKEN_MAX];
	CONFIG_IPAddress HostIP;		///< host ip
	CONFIG_IPAddress Submask;		///< netmask
	CONFIG_IPAddress Gateway;		///< gateway
};

enum SDK_RSSI_SINGNAL
{
	SDK_RSSI_NO_SIGNAL,   //<= -90db
	SDK_RSSI_VERY_LOW,     //<= -81db
	SDK_RSSI_LOW,          //<= -71db
	SDK_RSSI_GOOD,         //<= -67db
	SDK_RSSI_VERY_GOOD,    //<= -57db
	SDK_RSSI_EXCELLENT     //>-57db
};

struct SDK_NetWifiDevice
{
	char sSSID[36];            //SSID Number
	int nRSSI;                 //SEE SDK_RSSI_SINGNAL
	int nChannel;
	char sNetType[32];         //Infra, Adhoc
	char sEncrypType[32];      //NONE, WEP, TKIP, AES
	char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
};

struct SDK_NetWifiDeviceAll
{
	int nDevNumber;
	SDK_NetWifiDevice vNetWifiDeviceAll[NET_MAX_AP_NUMBER];
};

///< ������������
struct SDK_NetAlarmCenterConfig
{
	bool bEnable;		///< �Ƿ���
	char sAlarmServerKey[NET_NAME_PASSWORD_LEN];	///< ��������Э����������, 
	///< �������ķ�����
	SDK_RemoteServerConfig Server;	
	bool bAlarm;
	bool bLog;
};

struct SDK_NetAlarmServerConfigAll
{
	SDK_NetAlarmCenterConfig vAlarmServerConfigAll[NET_MAX_ALARMSERVER_TYPE];
};

// ����������Ϣ����
enum SDK_AlarmCenterMsgType
{
	SDK_ALARMCENTER_ALARM,
	SDK_ALARMCENTER_LOG,
};

// ����������Ϣ����
enum SDK_AlarmCenterStatus
{
	SDK_AC_START,
	SDK_AC_STOP,
};

// �澯������Ϣ����
struct SDK_NetAlarmCenterMsg
{
	CONFIG_IPAddress HostIP;		///< �豸IP
	int nChannel;                   ///< ͨ��
	int nType;                      ///< ���� ��AlarmCenterMsgType
	int nStatus;                    ///< ״̬ ��AlarmCenterStatus
	SDK_SYSTEM_TIME Time;           ///< ����ʱ��
	char sEvent[NET_MAX_INFO_LEN];  ///< �¼�
	char sSerialID[NET_MAX_MAC_LEN]; ///< �豸���к�
	char sDescrip[NET_MAX_INFO_LEN];  ///< ����
};

/// ������Ϣ
struct SDK_EncodeInfo
{
	bool bEnable;			///< ʹ����
	int iStreamType;		///< �������ͣ�capture_channel_t
	bool bHaveAudio;		///< �Ƿ�֧����Ƶ
	unsigned int uiCompression;		///< capture_comp_t������
	unsigned int uiResolution;		///< capture_size_t������
};

/// ��������
struct CONFIG_EncodeAbility
{
	unsigned int iMaxEncodePower;		///< ֧�ֵ�����������
	int iChannelMaxSetSync;		///< ÿ��ͨ���ֱ����Ƿ���Ҫͬ�� 0-��ͬ��, 1 -ͬ��
	unsigned int nMaxPowerPerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵ���߱�������
	unsigned int ImageSizePerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵ�ͼ��ֱ���
	unsigned int ExImageSizePerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
	SDK_EncodeInfo vEncodeInfo[SDK_CHL_FUNCTION_NUM];	///< ������Ϣ,��ʱ����4������
	SDK_EncodeInfo vCombEncInfo[SDK_CHL_FUNCTION_NUM];	///< ��ϱ�����Ϣ,��ʱ����4������
};

// ����Э��
enum SDK_CommProtocol
{
	SDK_CONSOLE = 0,
	SDK_KEYBOARD,
	SDK_COM_TYPES,
};
/// ����Э��
struct SDK_COMMFUNC
{
	//ÿ��Э�������64���ַ����
	int nProNum;
	char vCommProtocol[SDK_COM_TYPES][32];
};

/// ��̨Э��
struct SDK_PTZPROTOCOLFUNC
{
	//ÿ��Э�������64���ַ����
	int nProNum;
	char vPTZProtocol[100][NET_MAX_PTZ_PROTOCOL_LENGTH];
};

/// �����ڵ�������
struct SDK_BlindDetectFunction
{
	int iBlindConverNum;	///< �����ڵ�����
};

/// ��������������
struct SDK_MotionDetectFunction
{
	int iGridRow;
	int iGridColumn;
};

/// ֧�ֵ�DDNS����
struct SDK_DDNSServiceFunction
{
	int  nTypeNum;
	char vDDNSType[NET_MAX_DDNS_TYPE][64];
};

/// ֧������
struct SDK_MultiLangFunction
{
	//ÿ��Э�������64���ַ����
	int nLangNum;
	char vLanguageName[128][64];
};

/// ֧�ֵ���Ƶ��ʽ
struct SDK_MultiVstd
{
	//ÿ��Э�������3���ַ����
	int nVstdNum;
	char vVstdName[3][64];
};

/// ���빦��
enum SDK_EncodeFunctionTypes
{
	SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM,		///< ˫��������
	SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM,	///< ��ϱ��빦��
	SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM,		///< ץͼ����
	SDK_ENCODE_FUNCTION_TYPE_NR,
};

/// ��������
enum SDK_AlarmFucntionTypes
{
	SDK_ALARM_FUNCTION_TYPE_MOTION_DETECT,	///< ��̬���
	SDK_ALARM_FUNCTION_TYPE_BLIND_DETECT,	///< �����ڵ�
	SDK_ALARM_FUNCTION_TYPE_LOSS_DETECT,	///< ������ʧ
	SDK_ALARM_FUNCTION_TYPE_LOCAL_ALARM,	///< ���ر���
	SDK_ALARM_FUNCTION_TYPE_NET_ALARM,		///< ���籨��
	SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT,	///< IP��ַ��ͻ
	SDK_ALARM_FUNCTION_TYPE_NET_ABORT,		///< �����쳣
	SDK_ALARM_FUNCTION_TYPE_STORAGE_NOTEXIST,	///< �洢�豸������
	SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE,	///< �洢�豸��������
	SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE,	///< �洢�豸����ʧ��
	SDK_ALARM_FUNCTION_TYPE_NR
};

/// ���������
enum SDK_NetServerTypes
{
	SDK_NET_SERVER_TYPES_IPFILTER,		///< �׺�����
	SDK_NET_SERVER_TYPES_DHCP,			///< DHCP����
	SDK_NET_SERVER_TYPES_DDNS,			///< DDNS����
	SDK_NET_SERVER_TYPES_EMAIL,			///< Email����
	SDK_NET_SERVER_TYPES_MULTICAST,		///< �ಥ����
	SDK_NET_SERVER_TYPES_NTP,			///< NTP����
	SDK_NET_SERVER_TYPES_PPPOE,
	SDK_NET_SERVER_TYPES_DNS,
	SDK_NET_SERVER_TYPES_ARSP,			///< ����ע�����
	SDK_NET_SERVER_TYPES_3G,            ///< 3G����
	SDK_NET_SERVER_TYPES_MOBILE,        ///< �ֻ����
	SDK_NET_SERVER_TYPES_UPNP,			    ///< UPNP
	SDK_NET_SERVER_TYPES_FTP,			    ///< FTP
	SDK_NET_SERVER_TYPES_WIFI,          ///<WIFI
	SDK_NET_SERVER_TYPES_ALARM_CENTER,  ///< �澯����
	SDK_NET_SERVER_TYPES_NR,
};

/// Ԥ������
enum SDK_PreviewTypes
{
	SDK_PREVIEW_TYPES_TOUR,		///< ��Ѳ
	SDK_PREVIEW_TYPES_TALK,		///< GUI��������
	SDK_PREVIEW_TYPES_NR
};
///֧�ֵ�ϵͳ����
struct SDK_SystemFunction
{
	bool vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_NR];	///< ���빦��EncodeFunctionTypes
	bool vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_NR];		///< ��������AlarmFucntionTypes
	bool vNetServerFunction[SDK_NET_SERVER_TYPES_NR];	///< ���������NetServerTypes
	bool vPreviewFunction[SDK_PREVIEW_TYPES_NR];		///< Ԥ������PreviewTypes
};

struct SDK_COMMATTRI
{
	int	iDataBits;	// ����λȡֵΪ5,6,7,8 
	int	iStopBits;	// ֹͣλ
	int	iParity;	// У��λ
	int	iBaudRate;	// ʵ�ʲ�����
};

// ��������
struct SDK_CONFIG_COMM_X
{
	char iProtocolName[32];	// ����Э��:��Console�� 
	int iPortNo;		// �˿ں� 
	SDK_COMMATTRI aCommAttri;		// �������� 
};

struct SDK_CommConfigAll
{
	SDK_CONFIG_COMM_X vCommConfig[SDK_COM_TYPES];
};


// ��̨����
struct SDK_STR_CONFIG_PTZ
{
	char sProtocolName[NET_MAX_PTZ_PROTOCOL_LENGTH];	// Э������ 	
	int	ideviceNo;				// ��̨�豸��ַ��� 	
	int	iNumberInMatrixs;		// �ھ����е�ͳһ���	
	int iPortNo;				// ���ڶ˿ں�	[1, 4] 	
	SDK_COMMATTRI dstComm;			// �������� 	
};

//����ͨ����̨Э��
struct SDK_STR_PTZCONFIG_ALL
{
	SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
};

struct SDK_CONFIG_WORKSHEET
{	
	SDK_TIMESECTION	tsSchedule[NET_N_WEEKS][NET_N_TSECT];	/*!< ʱ��� */
};

/// ¼��ģʽ����
enum SDK_RecordModeTypes
{
	SDK_RECORD_MODE_CLOSED,		///< �ر�¼��
	SDK_RECORD_MODE_MANUAL,		///< �ֶ�¼��
	SDK_RECORD_MODE_CONFIG,		///< ������¼��
	SDK_RECORD_MODE_NR,		
};

///< ¼������
struct SDK_RECORDCONFIG
{
	int iPreRecord;			///< Ԥ¼ʱ�䣬Ϊ��ʱ��ʾ�ر�	
	bool bRedundancy;		///< ���࿪��
	bool bSnapShot;			///< ���տ���	
	int iPacketLength;		///< ¼�������ȣ����ӣ�[1, 255]
	int iRecordMode;		///< ¼��ģʽ��0 �رգ�1 ��ֹ 2 ����
	SDK_CONFIG_WORKSHEET wcWorkSheet;			///< ¼��ʱ���	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];		///< ¼����������
};

//¼�����ýṹ��
struct SDK_RECORDCONFIG_ALL
{
	SDK_RECORDCONFIG vRecordConfigAll[NET_MAX_CHANNUM];
};

///< ͼƬ����
struct SDK_SnapshotConfig
{
	int iPreSnap;			///< ԤץͼƬ��
	bool bRedundancy;		///< ���࿪��
	int iSnapMode;		///< ¼��ģʽ����RecordModeTypes
	SDK_CONFIG_WORKSHEET wcWorkSheet;				///< ¼��ʱ���	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];	///< ¼���������룬��enum RecordTypes
};

struct SDK_SnapshotConfigAll
{
	SDK_SnapshotConfig vSnapshotConfigAll[NET_MAX_CHANNUM];
};


//������ؽṹ��
//  ��̨�����ṹ
struct SDK_PtzLinkConfig
{
	int iType;		// ���������� 
	int iValue;		// ���������Ͷ�Ӧ��ֵ 
};

struct SDK_EventHandler
{
	unsigned int	dwRecord;				// ¼������ 
	unsigned int	iRecordLatch;			// ¼����ʱ��10��300 sec  	
	unsigned int	dwTour;					// ��Ѳ���� 	
	unsigned int	dwSnapShot;				// ץͼ���� 
	unsigned int	dwAlarmOut;				// �������ͨ������ 
	unsigned int	dwMatrix;				// �������� 
	int		iEventLatch;			// ������ʼ��ʱʱ�䣬sΪ��λ 
	int		iAOLatch;				// ���������ʱ��10��300 sec  
	SDK_PtzLinkConfig PtzLink[NET_MAX_CHANNUM];		// ��̨������ 
	SDK_CONFIG_WORKSHEET schedule;		// ¼��ʱ���

	bool	bRecordEn;				// ¼��ʹ�� 
	bool	bTourEn;				// ��Ѳʹ�� 
	bool	bSnapEn;				// ץͼʹ�� 	
	bool	bAlarmOutEn;			// ����ʹ�� 
	bool	bPtzEn;					// ��̨����ʹ�� 
	bool	bTip;					// ��Ļ��ʾʹ�� 	
	bool	bMail;					// �����ʼ� 	
	bool	bMessage;				// ������Ϣ���������� 	
	bool	bBeep;					// ���� 	
	bool	bVoice;					// ������ʾ 		
	bool	bFTP;					// ����FTP���� 
	bool	bMatrixEn;				// ����ʹ�� 
	bool	bLog;					// ��־ʹ�ܣ�Ŀǰֻ����WTN��̬�����ʹ�� 
	bool	bMessagetoNet;			// ��Ϣ�ϴ�������ʹ�� 
};


///< ��̬�������
struct SDK_MOTIONCONFIG
{
	bool bEnable;							// ��̬��⿪�� 
	int iLevel;								// ������ 
	unsigned int mRegion[NET_MD_REGION_ROW];			// ����ÿһ��ʹ��һ�������ƴ� 	
	SDK_EventHandler hEvent;					// ��̬������� 
};

/// ȫͨ����̬�������
struct SDK_MOTIONCONFIG_ALL
{
	SDK_MOTIONCONFIG vMotionDetectAll[NET_MAX_CHANNUM];
};

///< �ڵ��������
struct SDK_BLINDDETECTCONFIG
{
	bool	bEnable;		///< �ڵ���⿪��
	int		iLevel;			///< �����ȣ�1��6
	SDK_EventHandler hEvent;	///< �ڵ��������
};

/// ȫͨ���ڵ��������
struct SDK_BLINDDETECTCONFIG_ALL
{
	SDK_BLINDDETECTCONFIG vBlindDetectAll[NET_MAX_CHANNUM];
};

///< �����¼��ṹ
struct SDK_VIDEOLOSSCONFIG
{
	bool bEnable;			///< ʹ��
	SDK_EventHandler hEvent;	///< �������
};

/// ����ͨ���Ļ���ʱ��ṹ
struct SDK_VIDEOLOSSCONFIG_ALL
{
	SDK_VIDEOLOSSCONFIG vGenericEventConfig[NET_MAX_CHANNUM];
};

///< ������������
struct SDK_ALARM_INPUTCONFIG
{
	bool	bEnable;		///< �������뿪��
	int		iSensorType;	///< ���������ͳ��� or ����
	SDK_EventHandler hEvent;	///< ��������
};

///< ����ͨ���ı�����������
struct SDK_ALARM_INPUTCONFIG_ALL
{
	SDK_ALARM_INPUTCONFIG vAlarmConfigAll[NET_MAX_CHANNUM];
};

///< ��·����
struct SDK_NETALARMCONFIG
{
	bool bEnable;			///< ʹ��
	SDK_EventHandler hEvent;	///< �������
};

/// ����ͨ������·�����ṹ
struct SDK_NETALARMCONFIG_ALL
{
	SDK_NETALARMCONFIG vNetAlarmConfig[NET_MAX_CHANNUM];
};

///< ���ر����������
struct SDK_AlarmOutConfig
{
	int nAlarmOutType;		///< �����������: ����,�ֶ�,�ر�
	int nAlarmOutStatus;    ///< ����״̬: 0:�� 1;�պ�
};

///< ����ͨ���ı����������
struct SDK_AlarmOutConfigAll
{
	SDK_AlarmOutConfig vAlarmOutConfigAll[NET_MAX_CHANNUM];
};

///< ��������Ϣ�ṹ
struct SDK_DriverInformation 
{
	int		iDriverType;		///< ����������
	bool	bIsCurrent;			///< �Ƿ�Ϊ��ǰ������
	unsigned int	uiTotalSpace;		///< ��������MBΪ��λ
	unsigned int	uiRemainSpace;		///< ʣ��������MBΪ��λ
	int		iStatus;			///< �����־���ļ�ϵͳ��ʼ��ʱ������
	int		iLogicSerialNo;				///< �߼����
	SDK_SYSTEM_TIME  tmStartTimeNew;		///< ��¼��ʱ��εĿ�ʼʱ��
	SDK_SYSTEM_TIME	 tmEndTimeNew;			///< ��¼��ʱ��εĽ���ʱ��
	SDK_SYSTEM_TIME	 tmStartTimeOld;		///< ��¼��ʱ��εĿ�ʼʱ��
	SDK_SYSTEM_TIME	 tmEndTimeOld;			///< ��¼��ʱ��εĽ���ʱ��
};
enum 
{
	SDK_MAX_DRIVER_PER_DISK = 2,	///< ÿ���������ķ�����
	SDK_MAX_DISK_PER_MACHINE = 8,	///< ���֧��8��Ӳ��
};
//Ӳ�̹���
struct SDK_STORAGEDISK
{
	int		iPhysicalNo;
	int		iPartNumber;		// ������
	SDK_DriverInformation diPartitions[SDK_MAX_DRIVER_PER_DISK];
};

struct SDK_StorageDeviceInformationAll
{
	int iDiskNumber;
	SDK_STORAGEDISK vStorageDeviceInfoAll[SDK_MAX_DISK_PER_MACHINE];
};

/// �洢�豸��������
enum SDK_StorageDeviceControlTypes
{
	SDK_STORAGE_DEVICE_CONTROL_SETTYPE,		///< ��������
	SDK_STORAGE_DEVICE_CONTROL_RECOVER,		///< �ָ�����
	SDK_STORAGE_DEVICE_CONTROL_PARTITIONS,	///< ��������
	SDK_STORAGE_DEVICE_CONTROL_CLEAR,		///< �������
	SDK_STORAGE_DEVICE_CONTROL_NR,
};

/// ���������������
enum SDK_StorageDeviceClearTypes
{
	SDK_STORAGE_DEVICE_CLEAR_DATA,			///< ���¼������
	SDK_STORAGE_DEVICE_CLEAR_PARTITIONS,	///< �������
	SDK_STORAGE_DEVICE_CLEAR_NR,
};

/// ����������
enum SDK_FileSystemDriverTypes
{
	SDK_DRIVER_READ_WRITE	= 0,	///< ��д������
	SDK_DRIVER_READ_ONLY	= 1,	///< ֻ��������
	SDK_DRIVER_EVENTS		= 2,	///< �¼�������
	SDK_DRIVER_REDUNDANT	= 3,	///< ����������
	SDK_DRIVER_SNAPSHOT		= 4,	///< ����������
	SDK_DRIVER_TYPE_NR		= 5,	///< ���������͸���
	SDK_DRIVER_UNUSED		= 0xff,	///< û��ʹ�õ��������ṹ
};

/// �洢�豸����
struct SDK_StorageDeviceControl
{
	int iAction;	///< ��enum SDK_StorageDeviceControlTypes
	int iSerialNo;	///< �������к�
	int iPartNo;    ///< ������
	int iType;		///< enum SDK_StorageDeviceClearTypes����SDK_FileSystemDriverTypes
	int iPartSize[2/*MAX_DRIVER_PER_DISK*/];	///< ���������Ĵ�С
};

/// �豸��Ϣ
typedef struct _H264_DVR_DEVICEINFO
{
	char sSoftWareVersion[64];	///< ����汾��Ϣ
	char sHardWareVersion[64];	///< Ӳ���汾��Ϣ
	char sEncryptVersion[64];	///< ���ܰ汾��Ϣ
	SDK_SYSTEM_TIME tmBuildTime;///< �������ʱ��
	char sSerialNumber[64];			///< �豸���к�
	int byChanNum;				///< ��Ƶ����ͨ����
	int iVideoOutChannel;		///< ��Ƶ���ͨ����
	int byAlarmInPortNum;		///< ��������ͨ����
	int byAlarmOutPortNum;		///< �������ͨ����
	int iTalkInChannel;			///< �Խ�����ͨ����
	int iTalkOutChannel;		///< �Խ����ͨ����
	int iExtraChannel;			///< ��չͨ����	
	int iAudioInChannel;		///< ��Ƶ����ͨ����
	int iCombineSwitch;			///< ��ϱ���ͨ���ָ�ģʽ�Ƿ�֧���л�
}H264_DVR_DEVICEINFO,*LPH264_DVR_DEVICEINFO;

///< �Զ�ά������
struct SDK_AutoMaintainConfig
{
	int iAutoRebootDay;				///< �Զ�������������
	int iAutoRebootHour;			///< ��������ʱ��	[0, 23]	
	int iAutoDeleteFilesDays;		///< �Զ�ɾ���ļ�ʱ��[0, 30]
};

/// Ĭ����������
enum SDK_DefaultConfigKinds
{
	SDK_DEFAULT_CFG_GENERAL,			// ��ͨ����
	SDK_DEFAULT_CFG_ENCODE,				// ��������
	SDK_DEFAULT_CFG_RECORD,				// ¼������
	SDK_DEFAULT_CFG_NET_SERVICE,		// �������
	SDK_DEFAULT_CFG_NET_COMMON,			// ͨ������
	SDK_DEFAULT_CFG_ALARM,				// ����
	SDK_DEFAULT_CFG_PTZCOMM,			// ��̨������
	SDK_DEFAULT_CFG_USERMANAGER,		// �û�����
	SDK_DEFAULT_CFG_PREVIEW,			// Ԥ������
	SDK_DEFAULT_CFG_END,
};

/// �ָ���Ĭ����������
struct SDK_SetDefaultConfigTypes
{
	bool vSetDefaultKinds[SDK_DEFAULT_CFG_END];
}; 


typedef struct{
	int nChannel;	//ͨ����
	int nStream;	//0��ʾ��������Ϊ1��ʾ������
	int nMode;		//0��TCP��ʽ,1��UDP��ʽ,2���ಥ��ʽ,3 - RTP��ʽ��4-����Ƶ�ֿ�(TCP)
	int nComType;	//ֻ����ϱ���ͨ����Ч, ��ϱ���ͨ����ƴͼģʽ
}H264_DVR_CLIENTINFO,*LPH264_DVR_CLIENTINFO;


enum SDK_File_Type
{
	SDK_RECORD_ALL = 0,
	SDK_RECORD_ALARM = 1, //�ⲿ����¼��
	SDK_RECORD_DETECT,	  //��Ƶ���¼��
	SDK_RECORD_REGULAR,	  //��ͨ¼��
	SDK_RECORD_MANUAL,	  //�ֶ�¼��
	SDK_PIC_ALL = 10,
	SDK_PIC_ALARM,		  //�ⲿ����¼��
	SDK_PIC_DETECT,		  //��Ƶ���¼��
	SDK_PIC_REGULAR,      //��ͨ¼��
	SDK_PIC_MANUAL,       //�ֶ�¼��
	SDK_TYPE_NUM
};

//��ѯ¼������
typedef struct 
{
	int nChannelN0;			//ͨ����
	int nFileType;			//�ļ�����, ��SDK_File_Type
	H264_DVR_TIME startTime;	//��ʼʱ��
	H264_DVR_TIME endTime;	//����ʱ��
	char szCard[32];		//����
}H264_DVR_FINDINFO;

//¼���ļ����ؽṹ��
typedef struct 
{
	int ch;						//ͨ����
	int size;					//�ļ���С
	char sFileName[108];		///< �ļ���
	SDK_SYSTEM_TIME stBeginTime;	///< �ļ���ʼʱ��
	SDK_SYSTEM_TIME stEndTime;		///< �ļ�����ʱ��
}H264_DVR_FILE_DATA;

//�طŶ���
enum SEDK_PlayBackAction
{
	SDK_PLAY_BACK_PAUSE,		/*<! ��ͣ�ط� */
	SDK_PLAY_BACK_CONTINUE,		/*<! �����ط� */
	SDK_PLAY_BACK_SEEK,			/*<! �طŶ�λ */
};

//������Ϣ
typedef struct SDK_ALARM_INFO
{
	int nChannel;
	int iEvent;
	int iStatus;
	SDK_SYSTEM_TIME SysTime;
}SDK_AlarmInfo;

/// ��־��ѯ����
struct SDK_LogSearchCondition
{
	int nType;	///< ��־����
	int iLogPosition;			///< ���ϴβ�ѯ�Ľ���ʱ����־ָ��
	SDK_SYSTEM_TIME stBeginTime;	///< ��ѯ��־��ʼʱ��
	SDK_SYSTEM_TIME stEndTime;		///< ��ѯ��־����ʱ��
};


struct SDK_LogItem
{
	char sType[24];	///< ��־����
	char sUser[32];	///< ��־�û�
	char sData[68];	///< ��־����
	SDK_SYSTEM_TIME stLogTime;	///< ��־ʱ��
	int iLogPosition;			///< ���ϴβ�ѯ�Ľ���ʱ����־ָ��
};

//��־������Ϣ
struct SDK_LogList
{
	int iNumLog;
	SDK_LogItem Logs[NET_MAX_RETURNED_LOGLIST];
};

/// �����Խ���ʽ
struct SDK_AudioInFormatConfigAll
{
	SDK_AudioInFormatConfig vAudioInFormatConfig[SDK_AUDIO_ENCODE_TYPES_NR];
};

/// �澯״̬
struct SDK_DVR_ALARMSTATE
{
	int iVideoMotion; ///< �ƶ����״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iVideoBlind; ///< ��Ƶ�ڵ�״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iVideoLoss;	///< ��Ƶ��ʧ״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iAlarmIn;	///< �澯����״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iAlarmOut;	///< �澯���״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
};

// ͨ��״̬
struct SDK_DVR_CHANNELSTATE
{
	bool bRecord; ///< �Ƿ�����¼��
	int iBitrate;	///< ��ǰ����
};

// DVR����״̬
struct SDK_DVR_WORKSTATE
{
	SDK_DVR_CHANNELSTATE vChnState[NET_MAX_CHANNUM];
	SDK_DVR_ALARMSTATE vAlarmState;
};


/// ����ֵ, ����������
enum SDK_NetKeyBoardValue
{
	SDK_NET_KEY_0, SDK_NET_KEY_1, SDK_NET_KEY_2, SDK_NET_KEY_3, SDK_NET_KEY_4, SDK_NET_KEY_5, SDK_NET_KEY_6, SDK_NET_KEY_7, SDK_NET_KEY_8, SDK_NET_KEY_9,
	SDK_NET_KEY_10, SDK_NET_KEY_11, SDK_NET_KEY_12, SDK_NET_KEY_13, SDK_NET_KEY_14, SDK_NET_KEY_15, SDK_NET_KEY_16, SDK_NET_KEY_10PLUS,
	SDK_NET_KEY_UP = 20,     // �ϻ�����̨����
	SDK_NET_KEY_DOWN,        // �»�����̨����
	SDK_NET_KEY_LEFT,        // �������̨����
	SDK_NET_KEY_RIGHT,       // �һ�����̨����
	SDK_NET_KEY_SHIFT, 
	SDK_NET_KEY_PGUP,        // ��һҳ
	SDK_NET_KEY_PGDN,        // ��һҳ
	SDK_NET_KEY_RET,         // ȷ��
	SDK_NET_KEY_ESC,         // ȡ�����˳�
	SDK_NET_KEY_FUNC,        // �л����뷨
	SDK_NET_KEY_PLAY,        // ����/��ͣ
	SDK_NET_KEY_BACK,        // ����
	SDK_NET_KEY_STOP,        // ֹͣ
	SDK_NET_KEY_FAST,        // ���
	SDK_NET_KEY_SLOW,        // ����
	SDK_NET_KEY_NEXT,        // ��һ���ļ�
	SDK_NET_KEY_PREV,        // ��һ���ļ�
	SDK_NET_KEY_REC = 40,    // ¼������
	SDK_NET_KEY_SEARCH,      // ¼���ѯ
	SDK_NET_KEY_INFO,        // ϵͳ��Ϣ
	SDK_NET_KEY_ALARM,       // �澯���
	SDK_NET_KEY_ADDR,        // ң������ַ����
	SDK_NET_KEY_BACKUP,      // ����
	SDK_NET_KEY_SPLIT,       // ����ָ�ģʽ�л���ÿ��һ���л�����һ�����ģʽ
	SDK_NET_KEY_SPLIT1,      // ������
	SDK_NET_KEY_SPLIT4,      // �Ļ���
	SDK_NET_KEY_SPLIT8,      // �˻���
	SDK_NET_KEY_SPLIT9,      // �Ż���
	SDK_NET_KEY_SPLIT16,     // 16����
	SDK_NET_KEY_SHUT,        // �ػ�
	SDK_NET_KEY_MENU,        // �˵�
	SDK_NET_KEY_PTZ = 60,    // ������̨����ģʽ
	SDK_NET_KEY_TELE,        // �䱶��
	SDK_NET_KEY_WIDE,        // �䱶��
	SDK_NET_KEY_IRIS_SMALL,  // ��Ȧ��
	SDK_NET_KEY_IRIS_LARGE,  // ��Ȧ��
	SDK_NET_KEY_FOCUS_NEAR,  // �۽�Զ
	SDK_NET_KEY_FOCUS_FAR,   // �۽���
	SDK_NET_KEY_BRUSH,       // ��ˢ
	SDK_NET_KEY_LIGHT,       // �ƹ�
	SDK_NET_KEY_SPRESET,     // ����Ԥ�õ�
	SDK_NET_KEY_GPRESET,     // ת��Ԥ�õ�
	SDK_NET_KEY_DPRESET,     // ���Ԥ�õ� 
	SDK_NET_KEY_PATTERN,     // ģʽ
	SDK_NET_KEY_AUTOSCAN,    // �Զ�ɨ�迪ʼ����
	SDK_NET_KEY_AUTOTOUR,    // �Զ�Ѳ��
	SDK_NET_KEY_AUTOPAN,     // ��ɨ��ʼ/����
};

/// ����״̬
enum SDK_NetKeyBoardState
{
	SDK_NET_KEYBOARD_KEYDOWN,	// ��������
	SDK_NET_KEYBOARD_KEYUP,		// �����ɿ�
};

struct SDK_NetKeyBoardData
{
	int iValue;
	int iState;
};

// ������Ϣ��ȡ
struct SDK_UpgradeInfo
{
	char szSerial[64];
	char szHardware[64];
	char szVendor[64];
	unsigned int uiLogoArea[2];
};

/// ���籨��
struct SDK_NetAlarmInfo
{
	int iEvent;  //Ŀǰδʹ��
	int iState;   //ÿbit��ʾһ��ͨ��,bit0:��һͨ��,0-�ޱ��� 1-�б���, ��������
};

//�������Ͽ��ص�ԭ��
typedef void (__stdcall *fDisConnect)(long lLoginID, char *pchDVRIP, long nDVRPort, unsigned long dwUser);

//ԭʼ���ݻص�ԭ��
typedef int(__stdcall *fRealDataCallBack) (long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser);

// �ط�¼����Ȼص�ԭ��
typedef void(__stdcall *fDownLoadPosCallBack) (long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser);

//��Ϣ���������ص�ԭ��
typedef bool (__stdcall *fMessCallBack)(long lLoginID, char *pBuf,
									   unsigned long dwBufLen, long dwUser);

//�����豸����ص�ԭ��
typedef void(__stdcall *fUpgradeCallBack) (long lLoginID, long lUpgradechannel,
										   int nTotalSize, int nSendSize, long dwUser);

// �����Խ�����Ƶ���ݻص�����ԭ��
typedef void (__stdcall *pfAudioDataCallBack)(long lVoiceHandle, char *pDataBuf, 
											 long dwBufSize, char byAudioFlag, long dwUser);


//*** */SDK��ʼ��
H264_DVR_API long H264_DVR_Init(fDisConnect cbDisConnect, unsigned long dwUser);

//*** */SDK�˳�����
H264_DVR_API bool H264_DVR_Cleanup();

//��ȡ������Ϣ
H264_DVR_API long H264_DVR_GetLastError();

//*** */���豸ע��
H264_DVR_API long H264_DVR_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
            							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error);

//���豸ע����չ�ӿ�
//���ӵ�½���� 0==web 1 ==�������� 2 == ��������
H264_DVR_API long H264_DVR_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error);

//*** */���豸ע��
H264_DVR_API long H264_DVR_Logout(long lLoginID);

//���ý���DVR��Ϣ�ص�, ���籨����Ϣ,��ID������
H264_DVR_API bool H264_DVR_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, unsigned long lUser);

//���������ϴ�ͨ��
H264_DVR_API long H264_DVR_SetupAlarmChan(long lLoginID);
H264_DVR_API bool H264_DVR_CloseAlarmChan(long lLoginID);


//Զ�������豸�ӿ� �������ͼ�SDK_CONFIG_TYPE
H264_DVR_API long  H264_DVR_GetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime = 1000);
H264_DVR_API long  H264_DVR_SetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);
//�����������豸���ã�Ŀǰֻ֧�ֶ��������ý�������
H264_DVR_API long H264_DVR_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);

//��־��ѯ
H264_DVR_API bool H264_DVR_FindDVRLog(long lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime = 2000);

//��ʵʱԤ��
H264_DVR_API long H264_DVR_RealPlay(long lLoginID, LPH264_DVR_CLIENTINFO lpClientInfo);
H264_DVR_API bool H264_DVR_StopRealPlay(long lRealHandle);

//���ûص��������û��Լ�����ͻ����յ�������
H264_DVR_API bool H264_DVR_SetRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);
//����ص�����,�ú�����Ҫ��H264_DVR_StopRealPlayǰ����
H264_DVR_API bool H264_DVR_DelRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);

//¼���ѯ
//lLoginID		��½���
//lpFindInfo	��ѯ����
//lpFileData	���ҵ���¼�����ݣ��ⲿ���ڴ�
//lMaxCount		���¼����Ŀ
//findcount		���ҵ���¼����Ŀ
//waittime		��ѯ��ʱʱ��
H264_DVR_API long H264_DVR_FindFile(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);

//¼��ط�
//lLoginID		��½���
//sPlayBackFileName	�طŵ�¼������
//cbDownLoadPos ���Ȼص�		�û�֪ͨ�û��豸�Ƿ��Ѿ������ݷ������
								//�ͻ������ʵʱ��ʾ���ȣ�Ӧ�ô����������ȡʱ��������
								//���粿�ֲ���������������Ե�ǰ�������ݴ�С/�ܴ�С��������ȵĻ����Ǻ�׼��Ӧ���Ե�ǰʱ�䣬���ݿ�ʼʱ��ͽ���ʱ�����������
//fDownLoadDataCallBack ���ݻص�
//dwDataUser	�ص�����
H264_DVR_API long H264_DVR_PlayBackByName(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);

//��ʱ�����¼��ط�
H264_DVR_API long H264_DVR_PlayBackByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);

H264_DVR_API bool H264_DVR_StopPlayBack(long lPlayHandle);

//�طſ��Ʒ�,��ͣ,��λ�ȵ�
H264_DVR_API bool H264_DVR_PlayBackControl(long lPlayHandle, long lControlCode,long lCtrlValue);

//¼������,�û����Բ�ʹ�ûص����Լ�ͨ��H264_DVR_GetDownloadPos��ȡ����
H264_DVR_API long H264_DVR_GetFileByName(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName, 
											fDownLoadPosCallBack cbDownLoadPos = NULL, long dwDataUser = NULL );

H264_DVR_API long H264_DVR_GetFileByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge = false);

H264_DVR_API bool H264_DVR_StopGetFile(long lFileHandle);
//��ȡ���ؽ���
H264_DVR_API int H264_DVR_GetDownloadPos(long lFileHandle);

//����
H264_DVR_API long H264_DVR_Upgrade(long lLoginID, char *sFileName, int nType = 0, fUpgradeCallBack cbUpgrade = NULL, long dwUser = 0);
//����״̬ 1 �ɹ��� 2 �������� 3 ʧ��
H264_DVR_API int H264_DVR_GetUpgradeState(long lUpgradeHandle);
H264_DVR_API long H264_DVR_CloseUpgradeHandle(long lUpgradeHandle);


//��̨���ƣ�Ĭ���ǿ�����̨���ٶ�4���û�Ҳ�������������ٶ�
H264_DVR_API bool H264_DVR_PTZControl(long lLoginID,int nChannelNo, long lPTZCommand, bool bStop = false, long lSpeed = 4);

//��չ��̨���ƣ�����Ԥ�õ����ã�Ѳ��·�ߣ����ٶ�λ�ȵ�
H264_DVR_API bool H264_DVR_PTZControlEx(long lLoginID,int nChannelNo, long lPTZCommand, 
									long lParam1, long lParam2, long lParam3, bool bStop = false);

//�豸���ƣ�����ֵ true �ɹ��� false ʧ��
H264_DVR_API bool H264_DVR_ControlDVR(long lLoginID, int type, int waittime = 2000);


//�����������ڵ��豸
H264_DVR_API bool H264_DVR_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);


//�����Խ����������ݴ����ӿ�
H264_DVR_API long H264_DVR_StartVoiceCom_MR(long lLoginID, pfAudioDataCallBack pVcb, long dwDataUser);
H264_DVR_API bool H264_DVR_VoiceComSendData(long lVoiceHandle, char *pSendBuf, long lBufSize);
H264_DVR_API bool H264_DVR_StopVoiceCom(long lVoiceHandle);

//���öԽ���Ƶ���뷽ʽ���û����Բ����ã�Ĭ��ΪG711A����
H264_DVR_API bool H264_DVR_SetTalkMode(long lLoginID, SDK_AudioInFormatConfig* pTalkMode);

// lRecordType¼��ģʽ, ��SDK_RecordModeTypes
H264_DVR_API bool H264_DVR_StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType);
H264_DVR_API bool H264_DVR_StopDVRRecord(long lLoginID, int nChannelNo);

H264_DVR_API bool H264_DVR_SetSystemDateTime(long lLoginID, SDK_SYSTEM_TIME *pSysTime);
H264_DVR_API bool H264_DVR_GetDVRWorkState(long lLoginID, SDK_DVR_WORKSTATE *pWorkState);

H264_DVR_API bool H264_DVR_ClickKey(long lLoginID, SDK_NetKeyBoardData *pKeyBoardData);

// ���̹���
H264_DVR_API int H264_DVR_StorageManage(long lLoginID, SDK_StorageDeviceControl *pStorageCtl);

H264_DVR_API bool H264_DVR_SendNetAlarmMsg(long lLoginID, SDK_NetAlarmInfo *pAlarmInfo);

H264_DVR_API bool H264_DVR_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, unsigned long dwDataUser);
H264_DVR_API bool H264_DVR_StopAlarmCenterListen();

#endif