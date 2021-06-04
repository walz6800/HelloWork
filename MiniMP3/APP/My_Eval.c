#include  <stm32f10x_conf.h>
//#include  <stm32f10x_lib.h>
#include  <stm32f10x.h>
//#include "stm32f10x.h"
//#include "stm32f10x_lib.h"
#include "..\GUIinc\GUI.h"

#include "my_eval.h"
#include "ili9320.h"
//#include "usb_lib.h"
//#include "hw_config.h"
//#include "stm32f10x_it.h"
//#include "stm32f10x_nvic.h"
//#include "GUIDEMO.h"
#include "stm32f10x.h"
#include "sdio_sdcard.h"
#include "integer.h"
#include "ff.h"
#include "ffconf.h"
#include "diskio.h"

#include "usb_regs.h"

#include "bmp.h"
//#include "bmp1.h"
#include "bmp2.h"
#include "bmp3.h"
//#include "bmp4.h"
#include "dazhen.h"
#include "ili9320.h"

extern unsigned short *pDataBuff;

#define ECG_BUFF_SIZE	320

#define M	900							//SD���洢900����

u8 SD_BUFF[M];							//SD���洢����

extern unsigned short temp[220];
extern unsigned short ECG_Buff[ECG_BUFF_SIZE];

//unsigned char buffer[512];     // �ļ����ݻ�����
    
FATFS		fs;					 // �߼��������ı�־
FRESULT		res;				 // FatFs ���ܺ������ؽ������
UINT 		br;					 // �ļ���/д������
FIL 		file;				 // �ļ���־

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
SD_Error Status = SD_OK;
SD_CardInfo SDCardInfo;

int TouchX,TouchY;
u8 i=0,j=0,k=0,l=0;
u8 index=0;
	
void SD_TEST(void)
{
	Status = SD_Init();
    Status = SD_GetCardInfo(&SDCardInfo);
    Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
    Status = SD_SetDeviceMode(SD_DMA_MODE);  
// 	if (Status == SD_OK)
//  	{
//        // �ӵ�ַ0��ʼ��ȡ512�ֽ�  
//    	Status = SD_ReadBlock(Buffer_Block_Rx, 0x00,  512); 
//  	}
  	if(Status == SD_OK)
    {	 
       // ���سɹ��Ļ����������SD�����Գɹ���Ϣ 
	   // USART_OUT(USART1,"\r\nSD �ܶ�STM32������ SDIO-4bitģʽ ����TF���ɹ��� \n ");
//	   POINT_COLOR=BLUE;
//	   TFT_ShowString(10,10,"SDIO-4bit Mode TF Card test OK!");
	   ili9320_PutChar(20,50,'o',0xffff,0x0000);
    } 
}
void USB_SendString(u8 *str)
{
	UserToPMABufferCopy(str, GetEPTxAddr(ENDP1), 64);
	SetEPTxCount(ENDP1, 64);
	/* enable endpoint for transmission */
	SetEPTxValid(ENDP1);
}

void GPIO_Configuration1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
//	STM_EVAL_LEDInit(LED1);

	//PA0/1/2/3 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USB_DISCONNECT used as USB pull-up */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

//	STM_EVAL_LEDInit(LED1);
//	STM_EVAL_LEDInit(LED2);
}
//ϵͳ�жϹ���
void NVIC_Configuration1(void)
{  
	NVIC_InitTypeDef NVIC_InitStructure;

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//�������ȼ����飺��ռ���ȼ�0λ,�����ȼ�4λ
	
	//�����������λ�ú�ƫ��
	#ifdef  VECT_TAB_RAM  
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 		//������λ��RAM
	#else  /* VECT_TAB_FLASH  */
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   //������λ��FLASH
	#endif

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = 0x1d;  //TIM3_IRQn=29  TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	/* ���ȼ���1 */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  
//	
//	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;			     //SDIO�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		 //�������ȼ�0  ��Χ��0��1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			 //�����ȼ�0	��Χ��0-7
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}
void MY_ADC_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_DeInit(ADC1);  		//������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;		//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);			//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

	ADC_Cmd(ADC1, ENABLE);						//ʹ��ָ����ADC1		
	ADC_ResetCalibration(ADC1);					//����ָ����ADC1��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
	
	ADC_StartCalibration(ADC1);					//��ʼָ��ADC1��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	

}
void TIM3_Configuration(u16 timerval)
{
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
	/* ---------------------------------------------------------------
	TIM3CLK ��PCLK1=36MHz
	TIM3CLK = 36 MHz, Prescaler = 7200, TIM3 counter clock = 5K,���ı�һ��Ϊ5K,���ھ�Ϊ10K
	--------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = timerval; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	��������5000���Ǽ�����5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Enables the Update event for TIM3 */
	//TIM_UpdateDisableConfig(TIM3,ENABLE); 	//ʹ�� TIM3 �����¼� 
	
	/* TIM IT enable */
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
}
//����ϵͳʱ��,ʹ�ܸ�����ʱ��
void RCC_Configuration1(void)
{
	SystemInit();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP |
                           RCC_APB1Periph_TIM2, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIO_DISCONNECT |
//		       RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOB, ENABLE); 

			 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC 
  						| RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOE , ENABLE);

}
//���ADCֵ//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ1,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			//ʹ��ָ����ADC1�����ת����������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));	//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);			//�������һ��ADC1�������ת�����
}
/**********************************************************************
**�������ܣ���һ����׼ECG�ο����Σ��õײ��LCD���ߺ������ģ����˵㣬
**			��Ϊ��GUI�����������Ի����Ҳ����ȥ��ԭ���ˣ�
**������������      
**�������أ���
***********************************************************************/
void ECG_Wave(void)
{
//--------------------------------------------------------------//
//	POINT_COLOR = 0x001F;
	GUI_Line(164, 45, 190, 45,0x001F);  //����ʼ�У���ʼ�У������У������У�ֱ��
	GUI_Line(190, 45, 195, 50,0x001F);	 //P��
	GUI_Line(197, 52, 202, 24,0x001F);	 //QRS��1����ߣ�
	GUI_Line(202, 24, 206, 58,0x001F);	 //QRS��2���ұߣ�
	GUI_Line(206, 58, 212, 45,0x001F);	 //ST��1
	GUI_Line(212, 45, 215, 40,0x001F);	 //ST��2
	
	GUI_Line(215, 40, 218, 38,0x001F);	 //T��1
	GUI_Line(218, 38, 221, 37,0x001F);	 //T��2
	GUI_Line(221, 37, 224, 37,0x001F);	 //T��3
	
	GUI_Line(224, 37, 228, 39,0x001F);	 //U��1
	GUI_Line(228, 39, 232, 41,0x001F);	 //U��2
	GUI_Line(232, 41, 236, 43,0x001F);	 //U��3
	GUI_Line(236, 43, 240, 45,0x001F);	 //U��4
	
	//----------------�������������Ʋ���------------------------------------------------//
	GUI_Line(164+76, 45, 190+66, 45,0x001F);  //������ʼ�У���ʼ�У������У������У�ֱ��
	GUI_Line(190+66, 45, 195+66, 50,0x001F);	 //P��
	GUI_Line(197+66, 52, 202+66, 24,0x001F);	 //QRS��1����ߣ�
	GUI_Line(202+66, 24, 206+66, 58,0x001F);	 //QRS��2���ұߣ�
	GUI_Line(206+66, 58, 212+66, 45,0x001F);	 //ST��1
	GUI_Line(212+66, 45, 215+66, 40,0x001F);	 //ST��2
	
	GUI_Line(215+66, 40, 218+66, 38,0x001F);	 //T��1
	GUI_Line(218+66, 38, 221+66, 37,0x001F);	 //T��2
	GUI_Line(221+66, 37, 224+66, 37,0x001F);	 //T��3
	
	GUI_Line(224+66, 37, 228+66, 39,0x001F);	 //U��1
	GUI_Line(228+66, 39, 232+66, 41,0x001F);	 //U��2
	GUI_Line(232+66, 41, 236+66, 43,0x001F);	 //U��3
	GUI_Line(236+66, 43, 240+66, 45,0x001F);	 //U��4
	GUI_Line(240+66, 45, 250+66, 45,0x001F);

//-----------------------------------------------------------------------------------//
}
/**********************************************************************
**��������	ECG_Samp_Inf��void������Ի����Լ����ģ�
**�������ܣ���һ���Ի��������в���ֵ����ѹת��ֵ������
**������������      
**�������أ���
***********************************************************************/
void ECG_Samp_Inf(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_SetBkColor(GUI_WHITE);
	GUI_DrawRect(18, 0, 155, 76);							//��һ�������(��ʼ�У���ʼ�У������У�������)	
	GUI_ClearRect(21, 3, 152, 73);			 				//�����������Ϊ������ɫ
	GUI_SetBkColor(GUI_DARKGRAY);
	GUI_ClearRect(21, 3, 152, 12);			 				//�����������Ϊ������ɫ
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font8_ASCII);			 				//��������
	GUI_DispStringAt("ECG Sampling Information", 22, 4);   	//("�ַ�"���У���)
	GUI_DrawRect(19, 1, 154, 75);							//�����м��
	GUI_SetColor(GUI_GRAY);									//������ɫ
	GUI_DrawRect(20, 2, 153, 74);							//���� ���ڿ�
	GUI_SetColor(GUI_BLACK);
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font13B_ASCII);
	GUI_DispStringAt("SAM_VAL:", 22, 15);   				//("�ַ�"���У���)
	GUI_DispStringAt("ADC_VAL:     .        V", 22, 30);	//��ʾת���õĵ�ѹֵ
	GUI_DispStringAt("Heart Rate:          p/min", 22, 45);	//��ʾ����

	GUI_DispStringAt("Wave num:",22, 60);					//��ʾ���θ���
}
void Load_Sys_ICO(void)	  		//����ϵͳͼ��
{
	GUI_SetColor(GUI_BLUE);		 		//���ñʻ���ɫ
	GUI_SetBkColor(GUI_WHITE);	 		//���ñ�����ɫ
	GUI_Clear();
	Show_BMP(40,10,100,100,gImage_dd); 		//����ʼ�У���ʼ�У�ͼƬ�Ŀ�ͼƬ�ĸߣ�
	Show_BMP(180,10,100,100,gImage_cc);
	Show_BMP(40,130,100,100,gImage_dazhen);
	Show_BMP(180,130,100,100,gImage_bb);

	GUI_DrawRect(39, 9, 140, 110);		//��һ�������(��ʼ�У���ʼ�У������У�������)	
	GUI_DrawRect(38, 8, 141, 111);
	GUI_DrawRect(37, 7, 142, 112);
	GUI_DrawRect(36, 6, 143, 113);
}
void Show_ICO(void)
{
	GUI_SetColor(GUI_BLUE);		 		//���ñʻ���ɫ
	GUI_SetBkColor(GUI_WHITE);	 		//���ñ�����ɫ
	GUI_Clear();
	Show_BMP(40,10,100,100,gImage_dd); 		//����ʼ�У���ʼ�У�ͼƬ�Ŀ�ͼƬ�ĸߣ�
	Show_BMP(180,10,100,100,gImage_cc);
	Show_BMP(40,130,100,100,gImage_dazhen);
	Show_BMP(180,130,100,100,gImage_bb);
}
void Select_Menu(void)		   //ѡ������ͼ��
{
	GUI_SetFont(&GUI_Font13B_ASCII);
	TouchX=GUI_TOUCH_X_MeasureX();
	TouchY=GUI_TOUCH_X_MeasureY();
//	GUI_DispDecAt(TouchX,92,50,5);
//	GUI_DispDecAt(TouchY,92,70,5);
	if(TouchX>2300&&TouchX<3670&&TouchY<1870&&TouchY>830)
	{
		GUI_DrawRect(39, 9, 140, 110);		//��һ�������(��ʼ�У���ʼ�У������У�������)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		GUI_SetColor(GUI_BLUE);
		TouchX=4000;TouchY=4000;
		{++i;j=0;k=0;l=0;}
		if(i==2) {index=1;i=0;}
		GUI_Delay(300);		
	}
	if(TouchX>2300&&TouchX<3670&&TouchY<3430&&TouchY>2370)
	{
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(39, 9, 140, 110);		//��һ�������(��ʼ�У���ʼ�У������У�������)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		GUI_SetColor(GUI_BLUE);
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		TouchX=4000;TouchY=4000;
		{i=0;j+=1;k=0;l=0;}
		if(j==2) {index=2;j=0;}
		GUI_Delay(300);
	}
	if(TouchX>450&&TouchX<1860&&TouchY<1870&&TouchY>830)
	{
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(39, 9, 140, 110);		//��һ�������(��ʼ�У���ʼ�У������У�������)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		GUI_SetColor(GUI_BLUE);		
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		TouchX=4000;TouchY=4000;
		{i=0;j=0;k+=1;l=0;}
		if(k==2) {index=3;k=0;}
		GUI_Delay(300);
	}
	if(TouchX>450&&TouchX<1860&&TouchY<3430&&TouchY>2370)
	{
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(39, 9, 140, 110);		//��һ�������(��ʼ�У���ʼ�У������У�������)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		GUI_SetColor(GUI_BLUE);		
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		TouchX=4000;TouchY=4000;
		{i=0;j=0;k=0;l+=1;}
		if(l==2) {index=4;l=0;}
		GUI_Delay(300);	
	}
	GUI_DispDecAt(index,310,50,1);
	GUI_DispDecAt(i,310,62,1);
	GUI_DispDecAt(j,310,74,1);
	GUI_DispDecAt(k,310,86,1);
	GUI_DispDecAt(l,310,98,1);
	switch(index)
	{
		case 1://��ѹʽ�������
			Draw_ECG_Wave();
			Load_Sys_ICO();//���¼���ϵͳ�˵�
			index=0; 				   
			break;
		case 2://�Զ����Ʋ���	 
			Draw_Any_Graph();
//			LCD_Fill(0,0,239,319,WHITE);//����
			Load_Sys_ICO();//���¼���ϵͳ�˵�
			index=0;
			break;
		case 3://�Զ���������	 
//			Pen_Viewer();
//			LCD_Fill(0,0,239,319,WHITE);//����
//			Load_Sys_ICO();//���¼���ϵͳ�˵�
			index=0;
			break; 
		case 4://ʱ��ģʽ	 
//			ECG_Viewer();
//			LCD_Fill(0,0,239,319,WHITE);//����
//			Load_Sys_ICO();//���¼���ϵͳ�˵�
			index=0;
			break;
		case 5://	 

			break;
		default:break;

	}	
}
void Draw_ECG_Wave(void)
{

	unsigned int i,j,r=1;
	signed int SAM_VAL;
	unsigned short max1=0,max2=0;
	unsigned short c1=0,c2=0;
	u8 USB_BUFF[6];
	float temp1;
	
	pDataBuff = &ECG_Buff[0];
	GUI_SetColor(GUI_WHITE);
	GUIDEMO_Graph();						//��ʼ������ǰ�Ļ���
	FrameWin();								//��һ��GUI�Ի���
	ECG_Wave();								//��һ����׼��ECG�ο�����
	My_Return_Bottom();
	ECG_Samp_Inf();
//---------��ʼ���ļ�ϵͳ-------------------------------------------//									  
	f_mount(0, &fs);			
	res=f_open(&file,"ECG_FILE1.TXT", FA_OPEN_ALWAYS|FA_WRITE ); 	//�Զ�д��ʽ�򿪲���������
	f_close(&file);			 										//�ر��ļ�
	f_open(&file,"ECG_FILE1.TXT", FA_OPEN_ALWAYS|FA_WRITE ); 	   	//�Զ�д��ʽ�򿪲���������
	f_lseek(&file,file.fsize); 										//�ƶ�ָ��
	f_write(&file,"JDSLJFDJLJLSJFAL",10,&br);				   	//ÿ��rest��ָ��ļ�
	f_printf(&file,"\n");
	f_close(&file);			 //�ر��ļ�
//------------------------------------------------------------------//		USB_BUFF[0]='_';
	USB_BUFF[5]='\0'; 
	while(1) 
	{	
		j=0;
		max1=1000,max2=1000,c1=1000,c2=1000;
//-----------���ļ���ʼд������------------------------//
		f_open(&file,"ECG_FILE1.TXT", FA_OPEN_ALWAYS|FA_WRITE );	//�Զ�д��ʽ�򿪲���������
		f_lseek(&file,file.fsize); 								//�ƶ�ָ��
		f_write(&file,__TIME__,9,&br); 							//���GUIʱ�䲢д��SD��txt�ļ���
		f_write(&file," ",1,&br);  								//д�ո�
		f_printf(&file,"%d",r);	  								//дһ��ECG�������
		f_printf(&file,"\n");	 								//����

		GUI_SetColor(GUI_BLUE);		 		//���ñʻ���ɫ
		GUI_SetBkColor(GUI_WHITE);	 		//���ñ�����ɫ
		GUI_DispDecAt(r,92,60,5);			//�ڣ�115�У�15�У����ݳ���Ϊ5Ϊ����ʾ���θ���
		for(i=0;i<ECG_BUFF_SIZE;i++) 		//ECG_BUFF_SIZE=320
		{
//			iir_reset();					//�˲�����λ
			SAM_VAL=Get_Adc(ADC_Channel_0);	//��ȡADC����ֵ
			GUI_DispDecAt(SAM_VAL,82,15,4);	//�ڣ�82�У�15�У����ݳ���Ϊ4Ϊ����ʾ����ֵ
			ECG_Buff[i]=SAM_VAL;			//�Ѳ���ֵװ��������
//			adcv=ECG_Buff[i];				//�˲�
//			ECG_Buff[i]=iir_filter(adcv);	//iir�˲���
			USB_BUFF[1]=(ECG_Buff[i]-ECG_Buff[i]%1000)/1000+48;
			USB_BUFF[2]=(ECG_Buff[i]%1000-ECG_Buff[i]%1000%100)/100+48;
			USB_BUFF[3]=(ECG_Buff[i]%1000%100-ECG_Buff[i]%1000%100%10)/10+48;
			USB_BUFF[4]=ECG_Buff[i]%1000%100%10+48;
			USB_SendString(USB_BUFF);
//-----------��ADC�ɼ���������д��SD��------------------------//
			temp1=(float)SAM_VAL*(3.3/4096);
			SAM_VAL=temp1;
			GUI_DispDecAt(SAM_VAL,80,30,1);	  //(�У��У����ݶ���λ)
			SD_BUFF[j]=(u8)(SAM_VAL)+48;
			temp1-=SAM_VAL;
			temp1*=1000;
			GUI_DispDecAt(temp1,96,30,3);
			SD_BUFF[j+1]=(u8)(temp1/100)+48;
			SD_BUFF[j+2]=' ';
			j=j+3;
			if(j>M) j=0;
			//delay_us(100);
			//delay_ms(1);
			GUI_Delay(4);
			TouchX=GUI_TOUCH_X_MeasureX();
			TouchY=GUI_TOUCH_X_MeasureY();
			if(TouchX<450&&TouchY>3500) 
			{
				Delete_Window();
				return;
			}
			else;
		}
//-----------��ADC�ɼ���������д��SD��------------------------//
		f_write(&file,SD_BUFF,M,&br);				   			//ÿ��rest��ָ��ļ�
		f_printf(&file,"\n");					//10�����ݾͻ���һ��
		f_printf(&file,"\n");	 //����
		f_printf(&file,"\n");	 //����
		f_close(&file);			 //�ر��ļ�
//------------�����������ֵ------------------------//
		for(i=0;i<ECG_BUFF_SIZE;i++)
		{
		  if(ECG_Buff[i]>max1) {max1=ECG_Buff[i];c1=i;}		  
		}
//------------�������еڶ���ֵ-----------------------//
		for(i=0;i<ECG_BUFF_SIZE;i++)
		{
		  if(max1>ECG_Buff[i]&&ECG_Buff[i]>max2) {max2=ECG_Buff[i];c2=i;}		  
		}
		c1=(60000000/((abs(c1-c2))*4650));			 //����=����QRS�����ڵĵ��� ����=60��/��QRS_1-QRS-2)��
		if(50<c1&&c1<100)
			GUI_DispDecAt(c1,93,45,3);				 //��������ʾ����

		if(pDataBuff)
		{
//			Filter(pDataBuff, DATA_BUFF_SIZE); //�����ԭ��Ϊ����,�����˲�
			ECG_Draw();
			//pDataBuff = 0;
			//GUI_Delay(10);
		}
		r++;			//һ��ECG���ε���ż�1
					

	}
}
void Draw_Any_Graph(void)
{
	GUI_SetColor(GUI_WHITE);		 		//���ñʻ���ɫ
	My_Return_Bottom();
	My_GUIDEMO_Graph();						//��ʼ������

	while(1)
	{
		TouchX=GUI_TOUCH_X_MeasureX();
		TouchY=GUI_TOUCH_X_MeasureY();
		if(TouchX<450&&TouchY>3500) 
		{
			Delete_Window();
			return;
		}
		else;
	}
}
