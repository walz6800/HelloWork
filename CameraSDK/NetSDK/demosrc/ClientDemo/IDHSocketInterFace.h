// IDHSocketInterFace.h: interface for the IDHSocketInterFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDHSOCKETINTERFACE_H__8E1F686D_E4D7_475A_A228_E5D7FCB4CF86__INCLUDED_)
#define AFX_IDHSOCKETINTERFACE_H__8E1F686D_E4D7_475A_A228_E5D7FCB4CF86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

//�������紫�͵���Ƶ���ݻص�
typedef int (__stdcall * CallbackFuncRealData )( long lRealHandle, 
												long dwDataType, unsigned char *pBuffer,
												long lbufsize,long dwUser);

//�����Խ��ص�
typedef void (CALLBACK *callbackFuncTalkData)(LONG lTalkHandle, char *pDataBuf, long dwBufSize, char byAudioFlag, long dwUser);

//�豸�Ͽ��ص�
typedef void (__stdcall *fDevDisconnectCallback)(int nSvrType, long lLoginID, long lDevID, DWORD dwUser);

//¼���ѯ���ݻص�
typedef void (__stdcall *fRecordQueryCallback)(H264_DVR_FILE_DATA* pRecFileInfo, int nNum, DWORD dwUser);

//֪ͨӦ�ò�( display )�豸������Ϣ
typedef void( CALLBACK* CallbackAlarmInfo )( long lDevcID , unsigned char* pBuf , DWORD dwLen , DWORD dwUser );


class IDHSocketInterFace  
{
public:

	IDHSocketInterFace();
	virtual ~IDHSocketInterFace();
	static IDHSocketInterFace* CreateObject(VENDOR_TYPE nMode);
	static void DeleteObject(VENDOR_TYPE nMode);


//���½ӿں���	

	/*	$Function		:	ConnectServer
	==  ===============================================================
	==	Description		:	���ӷ�����
	==	Argument		:	szIP		��ַ
	==					:	nPort		�˿�
						:   szUserName	�û���
						:	szPassword	����
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int ConnectServer(char *szIP, int nPort, const char* szUserName , const char* szPassword) = 0;

	/*	$Function		:	DisconnectServer
	==  ===============================================================
	==	Description		:	�Ͽ�����������
	==	Argument		
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual BOOL DisconnectServer() = 0;
	

	/*	$Function		:	ReuestDataFromCenter
	==  ===============================================================
	==	Description		:	�ӷ�������ȡ��Ϣ
	==	Argument		:
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int RequestDataFromServer(XM_DataType nType = XM_Data_NULL) = 0;
		
	//���ԭ���Ƿ��������Խ�״̬,���鹦��ʹ��
	//PC�����������Խ��ͻ��鹦��ֻ����һ����ʹ��
	virtual bool IsTalkingWithDevice() = 0;


	/*	$Function		:	SynchroDevice
	==  ===============================================================
	==	Description		:	�豸ʱ��ͬ��
	==	Argument		:	lTSID	(������ҵ�汾,������ý���ַ, ����ֱ���汾,����SDK���豸���)
						:	lDevcID (�豸ID, ����ֱ���汾��Ч)
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int SynchroDevice( long lTSID , long lDevcID ) = 0;


	/*	$Function		:	ConnectDevice
	==  ===============================================================
	==	Description		:	�����豸
	==	Argument		:	devcInfo		��½���豸��Ϣ
						:	pOutDevcInfo	��½�󷵻ص��豸��Ϣ
	== 	Return			:	������ҵ�汾,������ý����, ֱ���汾�����豸��½���
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int ConnectDevice( DEVICE_INFO devcInfo , DEVICE_INFO* const pOutDevcInfo ) = 0; 


	/*	$Function		:	DisconnectDevice
	==  ===============================================================
	==	Description		:	�Ͽ��豸����
	==	Argument		:	lTSID		(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	lDevcID		�豸ID,ֱ���汾��Ч
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int DisconnectDevice( long lTSID ,long lDevcID ) = 0;


	/*	$Function		:	ConnectChanel
	==  ===============================================================
	==	Description		:	����ͨ��
	==	Argument		:	lTSID		(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	pDevc		���ӵ��豸��Ϣ
						:	lChannelNO	ͨ����
						:	type		��������(��������,Ԥ����)
	== 	Return			:	ֱ���豸���ز��ž��, ��ҵ�汾�����豸��ID��, �ڹر�ʱ��ʹ��
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int ConnectChanel( long lTSID , DEVICE_INFO* pDevc , LPH264_DVR_CLIENTINFO pInfo, CallbackFuncRealData func , DWORD dwUserParm ) = 0;
	//�Ͽ�ͨ��
	//lDevcID ��ֱ���汾�о��ǲ��ž��
	virtual long DisconnectChannel(long lLoginID, long lDevcID, CallbackFuncRealData func , DWORD dwUserParm) = 0;


	/*	$Function		:	StartTalking
	==  ===============================================================
	==	Description		:	��ʼ�����Խ�
	==	Argument		:	lLoginID		(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	nTalkFlag		�Խ���Ƶ��������
	== 	Return			:	��ҵ�汾�����豸ID, ֱ���汾���ضԽ����,���رպͷ�������ʱ��ʹ��
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long StartTalking(long lLoginID , int nTalkFlag, callbackFuncTalkData pCallback, DWORD dwUserData) = 0;


	/*	$Function		:	SendTalkData
	==  ===============================================================
	==	Description		:	���������Խ�����
	==	Argument		:	lTSID		(��ҵ�汾:��ý����, ֱ���汾��Ч)
						:	lTalkhandle	(��ҵ�汾:�豸ID, ֱ���汾SDK��½���)
						:	pDataBuffer		�Խ�����
						:	dwDataLength	��Ƶ����
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int SendTalkData(long lTSID, long lTalkhandle, LPBYTE pDataBuffer,DWORD dwDataLength) =0 ;
	

	/*	$Function		:	StopTalking
	==  ===============================================================
	==	Description		:	ֹͣ�����Խ�
	==	Argument		:	lTSID		(��ҵ�汾:��ý����, ֱ���汾��Ч)
						:	lDevcID		��ҵ�汾�豸ID,ֱ���汾�Խ����
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int StopTalking( long lTSID , long lDevcID ) = 0;


	/*	$Function		:	QueryPower
	==  ===============================================================
	==	Description		:	��ѯ�Ƿ���Ȩ��, �����������ֱ������Ч
	==	Argument		:	lTSID		(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	type		Ȩ������
						:	lDevcID
						:	lChannel
						:	PreviewType
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	//�豸id��ͨ����ͬʱ��0ʱ,��ʾ��Ȩ��ֻ���û��ҹ�,���豸ͨ���޹�
	//virtual int QueryPower( POWER_TYPE type , long lDevcID , long lChannel , NET_RealPlayType PreviewType = NET_RType_Realplay ) = 0; 
	

	/*	$Function		:	PTZControl
	==  ===============================================================
	==	Description		:	��̨����
	==	Argument		:	lLoginID	(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	lDevcID
						:	lChannel
						:	dwPTZCommand
						:	lParam1
						:	lParam2
						:	lParam3
						:	dwStop		0 ��ʼ , 1 ֹͣ
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int PTZControl( LONG lLoginID , long lDevcID , int nChannelID, DWORD dwPTZCommand, 
		long lParam1, long lParam2, long lParam3, BOOL dwStop ) = 0;


	/*	$Function		:	QueryDevSystemInfo
	==  ===============================================================
	==	Description		:	��ѯ�豸��������Ϣ,������
	==	Argument		:	lLoginID		(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	lDevcID
						:	lConfigType		��ѯ��������
						:	nChannelNO		ͨ����(������豸������,ͨ����Ϊ-1, )
						:	pConfigBuf		��ѯ�������
						:	dwBufSize		���صĽ������
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int QueryDevSystemInfo(long lLonginID , long lDevID , long lConfigType , int nChannelNO, char* pConfigBuf, DWORD dwBufSize, DWORD *lpRet = NULL) = 0;
	//��������,����ͬQueryDevSystemInfo
	virtual int SaveIOControlState( long lLonginID , long lDevID , long lConfigType , int nChannelNO, char* pConfigBuf, DWORD dwBufSize) = 0;
	

	/*	$Function		:	RebootDevice
	==  ===============================================================
	==	Description		:	����DVR
	==	Argument		:	lTSID			(��ҵ�汾:��ý����, ֱ���汾SDK��½���)
						:	lDevcID			�豸ID��,ֱ���汾����Ч
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int RebootDevice( long lTSID , long lDevcID) = 0;


	/*	$Function		:	RequestUserIsLogin
	==  ===============================================================
	==	Description		:	ɾ���û�ʱ��,��֤��ǰ�û��Ƿ��Ѿ���½,����Ѿ���½���޷�ɾ��
	==	Argument		:	szUserName		�û���
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long RequestUserIsLogin(char *szUserName) = 0;
	


	/*	$Function		:	QueryRecordFile
	==  ===============================================================
	==	Description		:	��ѯ¼���¼
	==	Argument		:	lLoginID		��ҵ�汾������ý�����,���������豸��½���
						:	pRecQueryParam	��ѯ¼������
						:	nWaitTime		��ѯ�ȴ�ʱ��
						:	pRecQueryCallback	��ѯ��¼�ص�
						:	dwUser			�ص�����
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int QueryRecordFile( long lLoginID,
								RECORD_QUERY_PARAM* pRecQueryParam, 
								int nWaitTime /* = 5000  */,
								void* pRecQueryCallback /*= NULL*/, 
								DWORD dwUser /*= 0*/) = 0;

	/*	$Function		:	PlayBackByRecordFile
	==  ===============================================================
	==	Description		:	�ط�¼���¼
	==	Argument		:	lLoginID		��ҵ�汾������ý�����,���������豸��½���
						:	lDevID			�豸ID,ֱ���汾��Ч
						:	pRecFile		�طŵ��ļ���Ϣ
						:	pDownloadPosCallback	���Ȼص�
						:	dwPosUser				���Ȼص�����
						:	pNetDataCallback		���ݻص�
						:	dwDataUser				���ݻص�����
	== 	Return			:	��ҵ�汾��ý�����,ֱ���汾�طž��
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long PlayBackByRecordFile( long lLoginID, long lDevID, 
		void *pRecFile, 
		void *pDownloadPosCallback, DWORD dwPosUser, 
		void *pNetDataCallback, DWORD dwDataUser ) = 0;

	/*	$Function		:	PlayBackByTime
	==  ===============================================================
	==	Description		:	��ʱ��ط�¼��
	==	Argument		:	lLoginID		��ҵ�汾������ý�����,���������豸��½���
						:	lDevID			�豸ID,ֱ���汾��Ч
						:	nChannelNO		ͨ����
						:	pTmStart		��ʼʱ��
						:	pTmEnd			����ʱ��
						:	pDownloadPosCallback	���Ȼص�
						:	dwPosUser				���Ȼص�����
						:	pNetDataCallback		���ݻص�
						:	dwDataUser				���ݻص�����
	== 	Return			:	��ҵ�汾��ý�����,ֱ���汾�طž��
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long PlayBackByTime( long lLoginID, long lDevID, int nChannelNO, 
		LPH264_DVR_TIME pTmStart, LPH264_DVR_TIME pTmEnd, 
		void *pDownloadPosCallback, DWORD dwPosUser, 
		void *pNetDataCallback, DWORD dwDataUser ) = 0;	



	/*	$Function		:	StopPlayBack  PausePlayBack SeekPlayBack
	==  ===============================================================
	==	Description		:	¼�����
	==	Argument		:	lLoginID		�豸��½���(��ҵ�汾:��ý���ַ,  ֱ���汾: ��½���)
						:	lPlayHandle		PLAY����ֵ(��ҵ�汾:�豸ID, ֱ���汾: �طž��)
						:	nChannelNO		ͨ����,ֱ���汾��Ч
						:	offsetTime		ʱ��ƫ��
						:	offsetByte		λ��ƫ��
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	//ֹͣ����ط�
	virtual BOOL StopPlayBack( long lLoginID, long lPlayHandle, int nChannelNO ) = 0;	
	//��ͣ����ط�
	virtual BOOL PausePlayBack( long lLoginID, long lPlayHandle, int nChannelNO, BOOL bPause ) = 0;	
	//���ò���λ��
	virtual BOOL SeekPlayBack( long lLoginID, long lPlayHandle, int nChannelNO, 
		unsigned int offsetTime, unsigned int offsetByte ) = 0;



	/*	$Function		:	DownloadByRecordFile
	==  ===============================================================
	==	Description		:	¼������
	==	Argument		:	lLoginID		�豸��½���(��ҵ�汾:��ý���ַ,  ֱ���汾: ��½���)
						:	lDevID			�豸ID��(ֱ���汾��Ч)
						:	pRecFile		�ļ���Ϣ
						:	szFileName		������ļ���
						:	pDownloadPosCallback		���Ȼص�
						:	dwPosUser				
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long DownloadByRecordFile( long lLoginID, long lDevID, 
		H264_DVR_FILE_DATA* pRecFile, 
		char* szFileName,
		void *pDownloadPosCallback, 
		DWORD dwPosUser ) = 0;
	
	virtual long DownloadByTime( LONG lLoginID, 
						long lDevID,
						int nChannelNo, 
						int nRecordFileType, 
						LPNET_TIME tmStart, 
						LPNET_TIME tmEnd, 
						char *sSavedFileName, 
						void * cbTimeDownLoadPos, 
						DWORD dwUserData ) = 0;


	/*	$Function		:	StopDownload
	==  ===============================================================
	==	Description		:	ֹͣ¼������
	==	Argument		:	lLoginID		�豸��½���(��ҵ�汾:��ý���ַ,  ֱ���汾: ��½���)
						:	lPlayHandle		DownloadByRecordFile�ķ���ֵ(��ҵ�汾:�豸ID�� ֱ���汾:���ؾ��)
						:	nChannelNO		ͨ����(ֱ���汾��Ч)	
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual BOOL StopDownload( long lLoginID, long lPlayHandle, int nChannelNO ) = 0;


	//�ص�ע�ắ��
	virtual void RegisterAllCallback(CALLBACK_TYPE nCallbacjType, void* pCallback, DWORD dwUserData) = 0;
	
	//���汨���������ݵ�����
	virtual int SaveAlarmPlanToServer(int nType = 0) = 0; 
	virtual int ReuestLogFile( int nYear,int nMonth ,int nDay ,int nPage , const char* szFindData ) = 0; //szFindDataΪ��ѯ����

	//����������
	virtual BOOL SendHeartbeet() = 0;
	virtual BOOL PostHeartbeetData() = 0;
	virtual int CheckHearbeet() = 0;
	virtual void RecvHeartbeetData(unsigned char* pbuf , DWORD dwlen) = 0;
	//��ѯ�洢�����¼��
	//�ɹ�����¼��������ʧ�ܷ���<0
	virtual int QueryRecordFileFromServer( H264_DVR_FILE_DATA* pRecFileInfo,
		RECORD_QUERY_PARAM* pRecQueryParam, 
		char* szIP, int nPort, long& lConnID,
		int nWaitTime /*= 5000*/,
		void* pRecQueryCallback /*= NULL*/, DWORD dwUser /*= 0*/) = 0;
	//��ѯ�洢�����б�
	virtual BOOL QuerySSvrList( void* pCallbackFunc, DWORD dwUser ) = 0;
	virtual BOOL FinishToSendConfig() = 0;
	virtual int SendConfigToServer( XM_DataType type, CString strFileName ) = 0;
	virtual BOOL NotifyLocalCenter() = 0;
	virtual DWORD GetRecNetplayBufferSize(long lPlayHandle, long lDevID, int nChannelNO) = 0;
	virtual int SetupAlarmChan(long lLoginID) = 0;
	virtual LONG GetLastError() = 0;
	//��ʼ¼��
	virtual BOOL StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType) = 0;
	//�ر�¼��
	virtual BOOL StopDVRRecord(long lLoginID, int nChannelNo) = 0;

	//232��485��д
	virtual BOOL SerialWrite(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen) = 0;
	virtual BOOL SerialRead(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen) = 0;

};

#endif // !defined(AFX_IDHSOCKETINTERFACE_H__8E1F686D_E4D7_475A_A228_E5D7FCB4CF86__INCLUDED_)
