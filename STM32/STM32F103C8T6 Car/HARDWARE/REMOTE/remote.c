#include "remote.h"

void Remote_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef Tim_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(IR_GPIOx_LCK, ENABLE);             //ʹ�ܶ˿�xʱ��
    RCC_APBxPeriphClockCmd(TIMx_LCK, ENABLE);                 //ʹ��TIMxʱ��

    GPIO_InitStructure.GPIO_Pin = IR_IO;                        //����IO�� 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//�������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IR_GPIOx, &GPIO_InitStructure);                 //��ʼ��I0��

/*--------------------ʱ���ṹ���ʼ��-----------------------------*/
    Tim_TimeBaseStructure.TIM_Period = 10000;                           //�趨�������Զ���װֵ ���10ms���  
    Tim_TimeBaseStructure.TIM_Prescaler = 72;                           //Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.   
    Tim_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             //����ʱ�ӷ�Ƶϵ��
    Tim_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
    //Tim_TimeBaseStructure.TIM_RepetitionCounter = 0;                  //�ظ���������,�߼���ʱ������
    TIM_TimeBaseInit(IR_TIME, &Tim_TimeBaseStructure);                //��ʼ�� TIMx��ʱ��

/*--------------------���벶��ṹ���ʼ��--------------------------*/
    TIM_ICStructure.TIM_Channel = TIM_Channel_x;                        //�������벶���ͨ�������ݾ���� GPIO ������
    TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;             //�����ز���
    TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;         //��������ͨ��ѡ��
    TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                   //����Ƶ��ÿ���仯�ض����� 
    TIM_ICStructure.TIM_ICFilter = 0;                                   //��������źŵ��˲�ϵ��                                   
    TIM_ICInit(IR_TIME, &TIM_ICStructure);                            //��ʼ�� ��ʱ�����벶��

/*--------------------�ж����ȼ�����--------------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);                   //�����ж���Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;                     //���ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;           //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                  //�����ȼ�1��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //ʹ��IRQͨ��
    NVIC_Init(&NVIC_InitStructure);                                   //��ʼ��NVIC�Ĵ���

    TIM_ClearFlag(IR_TIME, TIM_IT_Update | TIM_IT_CCx);                 // ������ºͲ����жϱ�־λ
    TIM_Cmd(IR_TIME, ENABLE);                                         //ʹ�ܶ�ʱ��x
    TIM_ITConfig(IR_TIME, TIM_IT_Update | TIM_IT_CCx, ENABLE);          // �������ºͲ����ж�    

}

u8  IRdatas = 0;                //���յ����ݴ���
u8  IRval = 0;                 //���յ��İ���ֵ           
u8  RmtCnt = 0;                 //�����ظ����µĴ���
u8  Remote = 0;                 //ң�ذ�������ֵ��ȫ�ֱ���
TIM_ValueTypeDef TIM_Values;    //��ʼ���ṹ�� 

void TIMx_IRQHandler(void)                              //��ʱ��x�жϷ������
{
    if (TIM_GetITStatus(IR_TIME, TIM_IT_Update) != RESET)
    {
        if (TIM_Values.DataFlag == 1)                 //�Ƿ���յ���������
        {
            if (TIM_Values.Period > 3)                 //���4������жϣ�40ms��û�յ����ݣ���Ҫô��ʼ���ظ��룬Ҫô����������
            {
                if (RmtCnt == 0 || TIM_Values.Period > 9)                          //����յ����쵼�룬����4������м�û���յ��ظ��룬���ж��������ݣ���0��־�˳�                                                       
                    TIM_Values.DataFlag = 0;                                                //�����յ��ظ��룬���м�90msû�ٴ����жϣ����ж��������ݣ���0�˳�
            }
            TIM_Values.Period++;
        }
    }
    if (TIM_GetITStatus(IR_TIME, TIM_IT_CCx) != RESET)                              //�����������ػ����½����¼�?
    {
        if (TIM_Values.StartFlag == 0)                            //��һ�������ز���
        {
            TIM_SetCounter(IR_TIME, 0);                               //��0������
            TIM_OCxPolarityConfig(IR_TIME, TIM_ICPolarity_Falling);       //����Ϊ�½��ز���
            TIM_Values.CrrValue = 0;                //����ֵ��0             
            TIM_Values.StartFlag = 1;               //��ʼ�½��ز���
            TIM_Values.Period = 0;              //�Զ���װ�ؼĴ�����0
        }
        else                //�ڶ��β����½��ز���
        {
            TIM_Values.CrrValue = TIM_GetCapturex(IR_TIME);           //��ȡͨ��4 ����Ĵ�����ֵ
            TIM_OCxPolarityConfig(IR_TIME, TIM_ICPolarity_Rising);                        //����Ϊ�����ز���
            TIM_Values.StartFlag = 0;                                   //��ʼ��־��0�������жϲ���������
            TIM_Values.FinishFlag = 1;                                  //������1�β�������

            if (TIM_Values.FinishFlag == 1)                           //�ж��Ƿ����һ�β�������
            {
                if (TIM_Values.DataFlag == 1)                                     //�Ƿ���յ���������
                {
                    if (TIM_Values.CrrValue > 300 && TIM_Values.CrrValue < 800)           //560Ϊ��׼ֵ,560us
                    {
                        TIM_Values.Data <<= 1;                  //����һλ
                        TIM_Values.Data |= 0;                   //���յ�0
                        IRdatas++;                      //���յ������ݴ�����1.
                    }
                    else if (TIM_Values.CrrValue > 1400 && TIM_Values.CrrValue < 1800)    //1680Ϊ��׼ֵ,1680us
                    {
                        TIM_Values.Data <<= 1;                  //����һλ
                        TIM_Values.Data |= 1;                   //���յ�1
                        IRdatas++;              //���յ������ݴ�����1
                    }

                    /*���� NEC ��涨��110ms������(�� 9ms �͵�ƽ+2.5m �ߵ�ƽ+0.56ms �͵�ƽ
                    +97.94ms �ߵ�ƽ���)�������һ֡���ݷ������֮�󣬰�����Ȼû�зſ��������ظ��룬
                    �������룬����ͨ��ͳ��������Ĵ�������ǰ������µĳ���/������������ ��0.56ms �ߵ�ƽ*/

                    else if (TIM_Values.CrrValue > 2100 && TIM_Values.CrrValue < 2500)    //�õ�������ֵ���ӵ���Ϣ 2250Ϊ��׼ֵ2.25ms
                    {
                        if (RmtCnt > 3)            //��ֹ�ɿ��������յ��ظ��룬������ǰ3���յ����ظ��� 
                            IRdatas++;              //���յ������ݴ�����1
                        RmtCnt++;                   //������������1��  
                    }
                }
                else if (TIM_Values.CrrValue > 4200 && TIM_Values.CrrValue < 4700)        //4500Ϊ��׼ֵ4.5ms
                {
                    TIM_Values.DataFlag = 1;            //�ɹ����յ���������,���ݿ�ʼ��־Ϊ1
                    IRdatas = 0;                        //����1ʱ�յ�������
                    RmtCnt = 0;                         //�����������������

                }
            }

            /*---------------------------------------�������ݴ���---------------------------------------*/

            switch (IRdatas)
            {
                //              case 8:     //������������
                //                  if( TIM_Values.Data != IR_ID )                      //������յ����������ʹ��ң��������ͬ,������ȫ����0����
                //                  {
                //                      IRdatas = 0;                    //�������ݴ�����0
                //                      TIM_Values.DataFlag = 0;        //��ʼ�������ݱ�־��λΪ0  
                //                  }
                //                  TIM_Values.Data = 0;                //���յ���������0��ֻ��Ҫ������
                //                  break;

            case 16:    //��������������
                //if ( (u8)~TIM_Values.Data != IR_ID )                  //���֪��ң��ID����ֻ���ض�ң�������ƣ��������������һ��
                if ((u8)(TIM_Values.Data >> 8) != (u8)~(TIM_Values.Data & 0xff))      //�����������յ����������룬�ȽϷ��ֲ�ͬ��������ȫ����0����
                {
                    IRdatas = 0;                    //�������ݴ�����0
                    TIM_Values.DataFlag = 0;        //��ʼ�������ݱ�־��λΪ0
                }
                TIM_Values.Data = 0;                //���յ���������0
                break;

            case 24:    //������������
                IRval = TIM_Values.Data;        //��������浽IRval
                TIM_Values.Data = 0;            //���յ���������0��׼���������ݷ���
                break;

            case 32:    //���������ݷ���
                if (IRval != (u8)~TIM_Values.Data)        //���������ͽ��յ������ݷ��벻ͬ������������0,���¿�ʼ
                {
                    IRdatas = 0;                    //�������ݴ�����0
                    IRval = 0;
                }
                TIM_Values.Data = 0;            //���յ���������0��׼��������һ���ж�����
                Remote = IRval;          //���յ��İ���ֵ��ֵ��ȫ�ֱ��� Remote
                IRdatas = 33;            //��ֵΪ33��ֹ�ڽ�����ʱ�ٽ����жϣ�����32���жϣ�����������0
                break;

            case 34:    //�ظ���,�����x���ظ������յ�1���ظ��������Ͱ�34��x                  
                Remote = IRval;
                IRdatas = 33;            //���¸�ֵ��33����ֹ�ظ���������̫�࣬������ֵ������Ҳ���Ҫд�����switchѡ��
                break;
            }
        }
    }
    TIM_ClearITPendingBit(IR_TIME, TIM_IT_Update | TIM_IT_CCx);       //����жϱ�־λ
}

//��ֲʱ���ݲ�ͬ��ң�ذ���ֵ������case
void Remote_Scan(u8 str)              //ң�ذ�������
{
    Remote = 0;
    switch (str)
    {
    case 0X16:
        //
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
        break;
    case 0X68:
        //
        break;
    case 0X30:
        //LCD_ShowString( 25, 55,"I MISS YOU" );  // ��ʾ�ַ���
        break;
    case 0X18:
        //LCD_ShowString( 30, 70,"I SEE YOU" );  // ��ʾ�ַ���
        break;
    case 0x7A:
        //LCD_Image( 0, 0, 240, 135, imageLoge );
        break;
    case 0x10:
        //LCD_Image( 100, 140, 60, 58, imageLoge2 );
        break;
    case 0x38:
        //LCD_ShowNum( 100, 55, time, sizeof(time)-1 );
        //time++;
        break;
    case 0x5A:
        //LED_TOGGLE( 2 );
        break;
    case 0x42:
        //LED_GPIO_Confing();
        //time = 0;
        //LCD_ShowNum( 100, 55, time, sizeof(time)-1 );
        break;
    }
}


