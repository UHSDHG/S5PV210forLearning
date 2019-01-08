#include "main.h"
#include "stdio.h"

#define TSADCCON0  0xE1700000
#define TSDATX0    0xE170000C
#define TSDATY0    0xE1700010
//#define CLRINTADC0 0xE1700018
#define ADCMUX     0xE170001C

#define rTSADCCON0 (*(volatile unsigned int *)TSADCCON0)
#define rTSDATX0 (*(volatile unsigned int *)TSDATX0)
#define rTSDATY0 (*(volatile unsigned int *)TSDATY0)
#define rCLRINTADC0 (*(volatile unsigned int *)CLRINTADC0)
#define rADCMUX (*(volatile unsigned int *)ADCMUX)

// 注意：第一，延时要确实能延时；
         //第二，延时时间要合适；
static void delay(void)
{
	volatile unsigned int i,j;
	for(i = 0; i < 2000; i++)
	{
		for(j = 0; j < 3000; j++)
		{
			
		}
	}
}


// 初始化ADC控制器的函数
static void adc_init(void)
{
	//printf("---wdt interrupt test---");
	//TSADCCON0	
		// resolution set REG 16 bit 设置分辨率为 12bit
		rTSADCCON0 |= (1<<16);   // 12bit
		//  是否转换完成标志寄存器 bit 15 
		
		//  PRSCEN A/D converter prescaler enable bit 14
		rTSADCCON0 |= (1<<14);  //enable
		//  [13:6] A/D converter prescaler value
		rTSADCCON0 &= ~(0xff<<6);
		rTSADCCON0 |= (65<<6);   //convertor clock = 66/66=1MHz
		//[2]Standby mode select  #休眠模式选择
		rTSADCCON0 &= ~(1<<2);
		//[1] READ_START A/D conversion start by read
		   //读操作开始
		rTSADCCON0 &= ~(1<<1); //disable start by read mode
		//[0] A/D conversion starts by enable
		//rTSADCCON0 = (1<<0);
		这一条代码写错了  rTSADCCON0 |= (1<<0)
	//rTSDATX0	
		//[15]Up or Down state of stylus pen at Waiting for Interrupt Mode.
	//rTSDATX0	
	
	//CLRINTADC0
	
	//ADCMUX
	rADCMUX &= ~(0x0f<<0);  //根据接线ADCIN0,ADCMUX选择ADCIN0设置为0000;
	
}

// 测试ADC，完成的功能就是循环检测ADC并得到ADC转换数字值打印出来
void adc_test(void)
{
	unsigned int val;

	adc_init();
		
	while(1)
	{
		
		//第一步：开启ADC转换(手工开启)
		rTSADCCON0 |= (1<<0);
		//第二步：等待ADC转换完毕
		while((rTSADCCON0 & (1<<15)));
		printf("\n 5---wdt interrupt test---\n");
		//第三步：读取ADC的数字值
		//第四步：处理/显示数字值
		val = rTSDATX0;
		printf("X: bit14 = %d.\n",(val & (1<<14)));
		printf("X: adc value = %d.\n",(val & (0xfff<<0)));
		
		val = rTSDATY0;
		printf("Y: bit14 = %d.\n",(val & (1<<14)));
		printf("Y: adc value = %d.\n",(val & (0xfff<<0)));
		
		
		
		// 第五步：延时一段
		delay();
	}
	
}