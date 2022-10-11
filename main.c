
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000
#define GPIOA_BASE 0x40010800

#define RCC_APB2ENR (*(unsigned int *)0x40021018)

#define GPIOB_CRH (*(unsigned int *)0x40010C04)
#define GPIOC_CRH (*(unsigned int *)0x40011004)
#define GPIOA_CRL (*(unsigned int *)0x40010800)

#define GPIOB_ODR (*(unsigned int *)0x40010C0C)
#define GPIOC_ODR (*(unsigned int *)0x4001100C)
#define GPIOA_ODR (*(unsigned int *)0x4001080C)
	


void SystemInit(void);
void Delay_ms(volatile  unsigned  int);
void A_LED_LIGHT(void);
void B_LED_LIGHT(void);
void C_LED_LIGHT(void);
void Delay_ms( volatile  unsigned  int  t)
{
     unsigned  int  i;
     while(t--)
         for (i=0;i<800;i++);
}

void A_LED_LIGHT(){
	GPIOA_ODR=0x0<<5;		//PA5低电平
	GPIOB_ODR=0x1<<9;		//PB9高电平
	GPIOC_ODR=0x1<<14;		//PC14高电平
}
void B_LED_LIGHT(){
	GPIOA_ODR=0x1<<5;		//PA5高电平
	GPIOB_ODR=0x0<<9;		//PB9低电平
	GPIOC_ODR=0x1<<14;		//PC14高电平
}
void C_LED_LIGHT(){
	GPIOA_ODR=0x1<<5;		//PA5高电平
	GPIOB_ODR=0x1<<9;		//PB9高电平
	GPIOC_ODR=0x0<<14;		//PC14低电平	
}

int main(){
	int j=100;
	// 开启时钟
	RCC_APB2ENR |= (1<<3); // 开启 GPIOB 时钟
	RCC_APB2ENR |= (1<<4); // 开启 GPIOC 时钟
	RCC_APB2ENR |= (1<<2); // 开启 GPIOA 时钟
	
	
	// 设置 GPIO 为推挽输出
	GPIOB_CRH&= 0xffffff0f;	//设置位 清零		
	GPIOB_CRH|=0x00000020;  //PB9推挽输出

	GPIOC_CRH &= 0x0fffffff; //设置位 清零		
	GPIOC_CRH|=0x22200000;  //PC14推挽输出


	GPIOA_CRL &= 0xFF0FFFFF; //设置位 清零		
	GPIOA_CRL|=0x00200000; //PA5推挽输出

	// 3个LED初始化为不亮（即高点位）
	GPIOB_ODR |= (1<<9); 
	GPIOC_ODR |= (1<<14); 
	GPIOA_ODR |= (1<<5);  
	
	while(j){
		
		B_LED_LIGHT();
		Delay_ms(1000000);

		C_LED_LIGHT();
		Delay_ms(1000000);

		A_LED_LIGHT();
		Delay_ms(1000000);
	}
	
}


void SystemInit(){
	
}
