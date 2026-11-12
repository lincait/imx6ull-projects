/**************************************************************
描述 : I.MX6U 开发板裸机 C 语言点灯
**************************************************************/
#include "main.h"

/*
* @description : 使能 I.MX6U 所有外设时钟
* @param : 无
* @return : 无
*/
void clk_enable(void)
{
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;
 }

/*
* @description : 初始化 LED 对应的 GPIO
* @param : 无
* @return : 无
*/
void led_init(void)
{
    /* 1、初始化 IO 复用, 复用为 GPIO1_IO03 */
    SW_MUX_GPIO1_IO03 = 0x5; 

    /* 2、配置 GPIO1_IO03 的 IO 属性 
    *bit 16:0 HYS 关闭
    *bit [15:14]: 00 默认下拉
    *bit [13]: 0 kepper 功能
    *bit [12]: 1 pull/keeper 使能
    *bit [11]: 0 关闭开路输出
    *bit [7:6]: 10 速度 100Mhz
    *bit [5:3]: 110 R0/6 驱动能力
    *bit [0]: 0 低转换率
    */
    SW_PAD_GPIO1_IO03 = 0X10B0; 

    /* 3、初始化 GPIO, GPIO1_IO03 设置为输出 */
    GPIO1_GDIR = 0X0000008;

    /* 4、设置 GPIO1_IO03 输出低电平，打开 LED0 */
    GPIO1_DR = 0X0;
}

/*
* @description : 打开 LED 灯
* @param : 无
* @return : 无
*/
void led_on(void)
{
    /* 
    * 将 GPIO1_DR 的 bit3 清零 
    */
    GPIO1_DR &= ~(1<<3);
}

/*
* @description : 关闭 LED 灯
* @param : 无
* @return : 无
*/
void led_off(void)
{
    /* 
    * 将 GPIO1_DR 的 bit3 置 1
    */
    GPIO1_DR |= (1<<3);
}

/*
* @description : 短时间延时函数
* @param - n : 要延时循环次数(空操作循环次数，模式延时)
* @return : 无
*/
void delay_short(volatile unsigned int n)
{
    while(n--){}
}

/*
* @description : 延时函数,在 396Mhz 的主频下延时时间大约为 1ms
* @param - n : 要延时的 ms 数
* @return : 无
*/
void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

/*
* @description : main 函数
* @param : 无
* @return : 无
*/
int main(void)
{
    clk_enable(); /* 使能所有的时钟 */
    led_init(); /* 初始化 led */
    while(1) /* 死循环 */
    { 
        led_off(); /* 关闭 LED */
        delay(500); /* 延时大约 500ms */
        led_on(); /* 打开 LED */
        delay(500); /* 延时大约 500ms */
    }
    return 0;
}