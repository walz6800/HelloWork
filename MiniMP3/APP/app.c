#define GLOBALS
#include "includes.h"
#include "demo.h"

#include "my_eval.h"
//#include "usb_lib.h"
//#include "hw_config.h"
//#include "stm32f10x_it.h"

//#include "GUIDEMO.h"

#include "sdio_sdcard.h"
#include "integer.h"
#include "ff.h"
#include "ffconf.h"
#include "diskio.h"



extern void GUIDEMO_main(void);		

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
static  OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void App_TaskCreate(void);

static  void App_TaskStart(void* p_arg);
static  void  AppTaskUserIF (void *p_arg);

static  void AppTaskKbd(void* p_arg);

void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);


/****************************************************************************
* ��    �ƣ�int main(void)
* ��    �ܣ����������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
int main(void)
{
   CPU_INT08U os_err; 
   /* ��ֹ�����ж� */
   CPU_IntDis();
   
   /* ucosII ��ʼ�� */
   OSInit();                                                  

   /* Ӳ��ƽ̨��ʼ�� */
   BSP_Init();                               
   
   //���������� ���ȼ����  ���������������һ����;��Ϊ���Ժ�ʹ��ͳ������
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,               		    //ָ����������ָ��
                          (void *) 0,												//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
               		     (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],	//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
                         (INT8U) APP_TASK_START_PRIO);								//�������������ȼ�
             
   OSTimeSet(0);			 //ucosII�Ľ��ļ�������0    ���ļ�������0-4294967295  
   OSStart();                //����ucosII�ں�   
   return (0);
}




/****************************************************************************
* ��    �ƣ�static  void App_TaskStart(void* p_arg)
* ��    �ܣ���ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
static  void App_TaskStart(void* p_arg)
{
 
  (void) p_arg;
   //��ʼ��ucosIIʱ�ӽ���
   OS_CPU_SysTickInit();
                               
   //ʹ��ucos ��ͳ������
#if (OS_TASK_STAT_EN > 0)
   
   OSStatInit();                //----ͳ�������ʼ������                                 
#endif

   App_TaskCreate();			//��������������

   while (1)
   {  
      LED_LED1_ON();		      	  
	  OSTimeDlyHMSM(0, 0, 0, 100);

	  LED_LED1_OFF();
	  OSTimeDlyHMSM(0, 0, 0, 100);
   }
}

/****************************************************************************
* ��    �ƣ�static  void App_TaskCreate(void)
* ��    �ܣ�������������ĺ���
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
static  void App_TaskCreate(void)
{
  
   NMEA_MBOX=OSSemCreate(1);		                                           //����NMEAָ��������ź���
   /*  �����û��������� */
   OSTaskCreateExt(AppTaskUserIF,											   //ָ����������ָ��
   					(void *)0,												   //����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
   					(OS_STK *)&AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE-1],  //���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
					APP_TASK_USER_IF_PRIO,									   //�������������ȼ�
					APP_TASK_USER_IF_PRIO,									   //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
					(OS_STK *)&AppTaskUserIFStk[0],							   //ָ�������ջջ�׵�ָ�룬���ڶ�ջ�ļ���
                    APP_TASK_USER_IF_STK_SIZE,									//ָ����ջ�����������ڶ�ջ�ļ���
                    (void *)0,													//ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);					//ѡ�ָ���Ƿ������ջ���飬�Ƿ񽫶�ջ��0,�����Ƿ�Ҫ
					                                                            //���и�������ȵȡ�
                    
   /*   ���������������� */
   OSTaskCreateExt(AppTaskKbd,
   					(void *)0,
					(OS_STK *)&AppTaskKbdStk[APP_TASK_KBD_STK_SIZE-1],
					APP_TASK_KBD_PRIO,
					APP_TASK_KBD_PRIO,
					(OS_STK *)&AppTaskKbdStk[0],
                    APP_TASK_KBD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	
}

/****************************************************************************
* ��    �ƣ�static  void  AppTaskUserIF (void *p_arg)
* ��    �ܣ��û���������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
static  void  AppTaskUserIF (void *p_arg)
{											   
 	(void)p_arg;
								    
	RCC_Configuration1();					//ϵͳʱ������
	NVIC_Configuration1();					//�ж�����
//	TIM3_Configuration(5000);
	GPIO_Configuration1();					//I/O������
	SD_TEST();               				//SD�����Ժ���
//----------USBӲ����ʼ��------------------// Ӳ����ʼ��һ��Ҫ����ǰ�棬��Ȼ�ͳ�ʱ�������޷�ʶ��
	USB_Interrupts_Config();
	Set_USBClock();    
	USB_Init();
//-------------------------------------------//
//	delay_init(72);							//ϵͳ���ĳ�ʼ��
	MY_ADC_Init();							//ADC���ó�ʼ��
  	GUI_Init();	                			//ucgui��ʼ�� 
//	GUIDEMO_main();	   						//��ʼ��ʾGUI����
	GUIDEMO_Intro();	   					//��ʾ��һ�����棬GUI��Ϣ
	GUIDEMO_DemoProgBar();					//������
	
		

	Load_Sys_ICO();
	while(1) 
	{	

		Select_Menu();
		GUI_CURSOR_Show();						   //��ʾ���
	}
}
/****************************************************************************
* ��    �ƣ�static  void  AppTaskKbd (void *p_arg)
* ��    �ܣ������������ȡ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
static  void  AppTaskKbd (void *p_arg)
{
  (void)p_arg;   
   while(1) 
   { 
   	  /* ��ʱ10ms���ȡһ�δ�������	*/
      OSTimeDlyHMSM(0,0,0,10); 	               
	  GUI_TOUCH_Exec();    
   }
}


#if (OS_APP_HOOKS_EN > 0)
/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument : ptcb   is a pointer to the task control block of the task being created.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument : none.
*
* Note     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument : none.
*********************************************************************************************************
*/

void App_TaskStatHook(void)
{
}

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument : none.
*
* Note     : 1 Interrupts are disabled during this call.
*
*            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument : ptcb    is a pointer to the TCB of the task being created.
*
* Note     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif

