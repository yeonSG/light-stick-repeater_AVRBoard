/*
 * avrMCU.c
 *
 * Created: 2022-06-07 오후 10:04:16
 * Author : YS
 */ 

#include "main.h"
#include "util/delay.h"
#include "Appication/HardDrivers/E2213JS0C1.h"
#include "Appication/HardDrivers/image.h"

void HAL_Delay(uint32_t Delay) {
	while (0 < Delay)
	{
		_delay_ms(1);
		--Delay;
	}
    // _delay_ms((double)Delay);
}

 void init_spi_master()
 {
	 SPI_DDR &= ~(1<<MISO); 	 // MISO --> inputs     // 필요없음
	 SPI_DDR |= (1 << SS) | (1 << MOSI) | (1 << SCK); // MOSI, SCK, SS   --> output

	 
	 //16000KHz / 16
	 SPCR |= (1 << SPR0);
	
	 // Enable SPI, Master mode
	 SPCR = (1 << SPE) | (1 << MSTR);
 }


void SPI_master_write(uint8_t data)
{
	SPDR = data;

	while (!(SPSR & (1 << SPIF))) ;     // 전송이 완료될때까지 기다림
}

void example() {
    E2213JS0C1_Init();
    /* 显示图片测试 */
    // E2213JS0C1_DrawImage(0,0,104,212,gImage_1);
    E2213JS0C1_SendImageData();
    E2213JS0C1_SendUpdateCmd();
    E2213JS0C1_TurnOffDCDC();
    HAL_Delay(3000);
    /* 显示点�?�线、矩形�?�字符�?�bpm图片测试 */
    E2213JS0C1_ClearFullScreen(WHITE);
    E2213JS0C1_DrawPoint(0,0,RED);
    E2213JS0C1_DrawLine(0,2,10,HORIZONTAL,BLACK);
    E2213JS0C1_DrawLine(0,4,10,VERTICAL,BLACK);    
    E2213JS0C1_DrawRectangle(0,16,10,10,SOLID,BLACK,RED);   
    E2213JS0C1_DrawRectangle(20,16,10,10,HOLLOW,BLACK,RED);          
    E2213JS0C1_ShowCharStr(0,30,"FONT TEST",FONT_1608,BLACK,WHITE);
    E2213JS0C1_DrawBmp(0,50,104,41,BLACK,WHITE,BmpImage);
    E2213JS0C1_ShowCharStr(0,100,"UID:5572380",FONT_1608,BLACK,WHITE);  
    E2213JS0C1_ShowCharStr(20,116,"Designed",FONT_1608,BLACK,WHITE);
    E2213JS0C1_ShowCharStr(44,132,"By",FONT_1608,BLACK,WHITE);
    E2213JS0C1_ShowCharStr(40,148,"szongen",FONT_1608,BLACK,WHITE);
    E2213JS0C1_SendImageData();
    E2213JS0C1_SendUpdateCmd();
    E2213JS0C1_TurnOffDCDC();
}

int main(void)
{
    /* Replace with your application code */
    init_spi_master();

    while (1) 
    {
    }
}

