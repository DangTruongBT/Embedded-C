#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void delay(__IO uint32_t timedelay){ 
	for(int i=0; i<timedelay; i++){}
}

void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
}
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	
	
}
int main()
{
	RCC_Config();
	GPIO_Config();
	
	while(1){
		//trang thai mac dinh cua nut nhat la 0
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) ) //read status of PA0
			{
				  GPIO_ResetBits(GPIOC, GPIO_Pin_13);} 
				else{
					GPIO_SetBits(GPIOC, GPIO_Pin_13); //neu no dang tat thi sang 
				}
			
		}
	return 0;
	}
	