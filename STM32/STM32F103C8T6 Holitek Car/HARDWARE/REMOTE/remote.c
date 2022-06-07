#include "remote.h"

void Remote_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef Tim_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(IR_GPIOx_LCK, ENABLE);             //使能端口x时钟
    RCC_APBxPeriphClockCmd(TIMx_LCK, ENABLE);                 //使能TIMx时钟

    GPIO_InitStructure.GPIO_Pin = IR_IO;                        //输入IO口 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IR_GPIOx, &GPIO_InitStructure);                 //初始化I0口

/*--------------------时基结构体初始化-----------------------------*/
    Tim_TimeBaseStructure.TIM_Period = 10000;                           //设定计数器自动重装值 最大10ms溢出  
    Tim_TimeBaseStructure.TIM_Prescaler = 72;                           //预分频器,1M的计数频率,1us加1.   
    Tim_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             //设置时钟分频系数
    Tim_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //TIM向上计数模式
    //Tim_TimeBaseStructure.TIM_RepetitionCounter = 0;                  //重复计数设置,高级计时器才有
    TIM_TimeBaseInit(IR_TIME, &Tim_TimeBaseStructure);                //初始化 TIMx定时器

/*--------------------输入捕获结构体初始化--------------------------*/
    TIM_ICStructure.TIM_Channel = TIM_Channel_x;                        //配置输入捕获的通道，根据具体的 GPIO 来配置
    TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;             //上升沿捕获
    TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;         //捕获输入通道选择
    TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                   //不分频，每个变化沿都捕获 
    TIM_ICStructure.TIM_ICFilter = 0;                                   //被捕获的信号的滤波系数                                   
    TIM_ICInit(IR_TIME, &TIM_ICStructure);                            //初始化 定时器输入捕获

/*--------------------中断优先级配置--------------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);                   //设置中断组为 0
    NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;                     //设中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;           //抢占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                  //子优先级1级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //使能IRQ通道
    NVIC_Init(&NVIC_InitStructure);                                   //初始化NVIC寄存器

    TIM_ClearFlag(IR_TIME, TIM_IT_Update | TIM_IT_CCx);                 // 清除更新和捕获中断标志位
    TIM_Cmd(IR_TIME, ENABLE);                                         //使能定时器x
    TIM_ITConfig(IR_TIME, TIM_IT_Update | TIM_IT_CCx, ENABLE);          // 开启更新和捕获中断    

}

u8  IRdatas = 0;                //接收到数据次数
u8  IRval = 0;                 //接收到的按键值           
u8  RmtCnt = 0;                 //按键重复按下的次数
u8  Remote = 0;                 //遥控按键处理值，全局变量
TIM_ValueTypeDef TIM_Values;    //初始化结构体 

void TIMx_IRQHandler(void)                              //定时器x中断服务程序
{
    if (TIM_GetITStatus(IR_TIME, TIM_IT_Update) != RESET)
    {
        if (TIM_Values.DataFlag == 1)                 //是否接收到了引导码
        {
            if (TIM_Values.Period > 3)                 //如果4次溢出中断（40ms）没收到数据，则要么开始收重复码，要么数据收完了
            {
                if (RmtCnt == 0 || TIM_Values.Period > 9)                          //如果收到了领导码，且在4次溢出中间没有收到重复码，则判断收完数据，清0标志退出                                                       
                    TIM_Values.DataFlag = 0;                                                //或者收到重复码，且中间90ms没再触发中断，则判断收完数据，清0退出
            }
            TIM_Values.Period++;
        }
    }
    if (TIM_GetITStatus(IR_TIME, TIM_IT_CCx) != RESET)                              //发生了上升沿或者下降沿事件?
    {
        if (TIM_Values.StartFlag == 0)                            //第一次上升沿捕获
        {
            TIM_SetCounter(IR_TIME, 0);                               //清0计数器
            TIM_OCxPolarityConfig(IR_TIME, TIM_ICPolarity_Falling);       //设置为下降沿捕获
            TIM_Values.CrrValue = 0;                //捕获值清0             
            TIM_Values.StartFlag = 1;               //开始下降沿捕获
            TIM_Values.Period = 0;              //自动重装载寄存器清0
        }
        else                //第二次捕获，下降沿捕获
        {
            TIM_Values.CrrValue = TIM_GetCapturex(IR_TIME);           //获取通道4 捕获寄存器的值
            TIM_OCxPolarityConfig(IR_TIME, TIM_ICPolarity_Rising);                        //设置为上升沿捕获
            TIM_Values.StartFlag = 0;                                   //开始标志复0，重新判断捕获上升沿
            TIM_Values.FinishFlag = 1;                                  //标记完成1次捕获流程

            if (TIM_Values.FinishFlag == 1)                           //判断是否完成一次捕获流程
            {
                if (TIM_Values.DataFlag == 1)                                     //是否接收到了引导码
                {
                    if (TIM_Values.CrrValue > 300 && TIM_Values.CrrValue < 800)           //560为标准值,560us
                    {
                        TIM_Values.Data <<= 1;                  //左移一位
                        TIM_Values.Data |= 0;                   //接收到0
                        IRdatas++;                      //接收到的数据次数加1.
                    }
                    else if (TIM_Values.CrrValue > 1400 && TIM_Values.CrrValue < 1800)    //1680为标准值,1680us
                    {
                        TIM_Values.Data <<= 1;                  //左移一位
                        TIM_Values.Data |= 1;                   //接收到1
                        IRdatas++;              //接收到的数据次数加1
                    }

                    /*这是 NEC 码规定的110ms连发码(由 9ms 低电平+2.5m 高电平+0.56ms 低电平
                    +97.94ms 高电平组成)，如果在一帧数据发送完毕之后，按键仍然没有放开，则发射重复码，
                    即连发码，可以通过统计连发码的次数来标记按键按下的长短/次数。结束码 ：0.56ms 高电平*/

                    else if (TIM_Values.CrrValue > 2100 && TIM_Values.CrrValue < 2500)    //得到按键键值增加的信息 2250为标准值2.25ms
                    {
                        if (RmtCnt > 3)            //防止松开慢而误收到重复码，而抛弃前3次收到的重复码 
                            IRdatas++;              //接收到的数据次数加1
                        RmtCnt++;                   //按键次数增加1次  
                    }
                }
                else if (TIM_Values.CrrValue > 4200 && TIM_Values.CrrValue < 4700)        //4500为标准值4.5ms
                {
                    TIM_Values.DataFlag = 1;            //成功接收到了引导码,数据开始标志为1
                    IRdatas = 0;                        //等于1时收到引导码
                    RmtCnt = 0;                         //清除按键次数计数器

                }
            }

            /*---------------------------------------接收数据处理---------------------------------------*/

            switch (IRdatas)
            {
                //              case 8:     //接收完特征码
                //                  if( TIM_Values.Data != IR_ID )                      //如果接收到的特征码和使用遥控器不相同,则数据全部清0重来
                //                  {
                //                      IRdatas = 0;                    //接收数据次数清0
                //                      TIM_Values.DataFlag = 0;        //开始接收数据标志复位为0  
                //                  }
                //                  TIM_Values.Data = 0;                //接收到的数据清0，只需要数据码
                //                  break;

            case 16:    //接收完特征反码
                //if ( (u8)~TIM_Values.Data != IR_ID )                  //如果知道遥控ID，想只能特定遥控器控制，则用这句与上面一句
                if ((u8)(TIM_Values.Data >> 8) != (u8)~(TIM_Values.Data & 0xff))      //如果特征码和收到的特征反码，比较发现不同，则数据全部清0重来
                {
                    IRdatas = 0;                    //接收数据次数清0
                    TIM_Values.DataFlag = 0;        //开始接收数据标志复位为0
                }
                TIM_Values.Data = 0;                //接收到的数据清0
                break;

            case 24:    //接收完数据码
                IRval = TIM_Values.Data;        //把数据码存到IRval
                TIM_Values.Data = 0;            //接收到的数据清0，准备接收数据反码
                break;

            case 32:    //接收完数据反码
                if (IRval != (u8)~TIM_Values.Data)        //如果数据码和接收到的数据反码不同，则数据码清0,重新开始
                {
                    IRdatas = 0;                    //接收数据次数清0
                    IRval = 0;
                }
                TIM_Values.Data = 0;            //接收到的数据清0，准备接收下一次中断数据
                Remote = IRval;          //把收到的按键值赋值给全局变量 Remote
                IRdatas = 33;            //赋值为33防止在结束码时再进入中断，触发32的判断，导致数据清0
                break;

            case 34:    //重复码,如果想x个重复码算收到1次重复按键，就把34＋x                  
                Remote = IRval;
                IRdatas = 33;            //重新赋值回33，防止重复按键次数太多，导致数值溢出，且不需要写后面的switch选择
                break;
            }
        }
    }
    TIM_ClearITPendingBit(IR_TIME, TIM_IT_Update | TIM_IT_CCx);       //清除中断标志位
}

//移植时根据不同的遥控按键值，更改case
void Remote_Scan(u8 str)              //遥控按键处理
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
        //LCD_ShowString( 25, 55,"I MISS YOU" );  // 显示字符串
        break;
    case 0X18:
        //LCD_ShowString( 30, 70,"I SEE YOU" );  // 显示字符串
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


