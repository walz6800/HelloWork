#ifndef _DEFINE_H
#define _DEFINE_H



#define		MAXWNDNUM		16		//��󴰿���

#define WM_MYCOMMAND		(WM_USER+1)
#define ID_ADD_DEVICE		(WM_USER+100)
#define ID_DELETE_DEVICE	(WM_USER+101)
#define ID_MODIFY_DEVICE	(WM_USER+4)
#define ID_CONNNECT			(WM_USER+5)
#define ID_DISCONNECT		(WM_USER+6)
#define ID_START_TALK		(WM_USER+7)
//�豸��Ϣ
typedef struct _DEV_INFO 
{
	long lLoginID;			//��½���
	long lID;				//Ψһ��־��
	char szDevName[60];		//�豸��
	char szIpaddress[15];		//�豸��
	char szUserName[8];		//�û���
	char szPsw[8];			//����
	int nPort;				//�˿�
	int nTotalChannel;		//ͨ����
}DEV_INFO;


struct ModuleFileInfomations
{
	CString		strFullPath;
	CString		strPath;
	CString		strDrive;
	CString		strDir;
	CString		strName;
	CString		strExt;
};






#endif