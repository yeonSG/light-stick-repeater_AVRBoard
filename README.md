# light-stick-repeater_AVRBoard
light-stick-repeater의 AVRBoard 코드

# Atmega128 참고.
 - [atmega128 개발 환경 기본 설정](https://kmg1767.tistory.com/38)
 - [프로그램 메모리 활용](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=jbivanlee&logNo=40119550790)

# EDP 조사 자료.
## EPD(Electronic Paper Display) 개요
 - [홈페이지](https://docs.pervasivedisplays.com/epd-usage/epd-driving-sequence/small-epds)

## 제품 데이터시트
 - [데이터시트 : E2213HS091](https://www.pervasivedisplays.com/wp-content/uploads/2019/06/1P159-00_01_E2213HS091_20171031.pdf)


## 참고용 코드1)
 - [E2213HS091C의 코드](https://github.com/szongen/E2213HS091-drive/blob/main/Application/HardDrivers/E2213JS0C1.h)
 ### 해당 프로젝트에서 "main.c"의 int main(void) 함수 부터 추적.
 - 1. HAL_init();           : 칩 Init
 - 2. SystemClock_Config()  : 
 - 3. MX_GPIO_Init();       : GPIO 핀 설정 
 - 4. MX_SPI1_Init();       : SPI 핀 설정 
 - ------ 초기화 끝 ------
 - 5. E2213JS0C1_Init()     : LCD 칩 초기화.
 - ------ 아래는 LCD 이미지 변경때마다 반복될 동작 ------
 - 6. FrameBuffer드로우           : E2213JS0C1_DrawPoint, E2213JS0C1_ShowCharStr 등등으로 Frame버퍼에 이미지 그림
 - 7. E2213JS0C1_SendImageData() : 이미지 데이터 전송
 - 8. E2213JS0C1_SendUpdateCmd() : Update 커멘드 전송
 - 9. E2213JS0C1_TurnOffDCDC()   : 칩 데이터 종료.

## 참고용코드2)
 [또다른 코드](https://github.com/szongen/ESP32_ePaper)

## 참고용코드3)
 [공식 코드(아두이노 기반)](https://github.com/PervasiveDisplays/EPD_Driver_GU_small)



# EDP 구현 TODO. 
 ## 핀 Out 확인
 - PB3(0x08)   ->  LCD_SI      Display SPI Data Pin (MOSI)
 - PB1(0x02)   ->  LCD_SCLK    Display SPI Clock Pin
 - PB0(0x01)   ->  LCD_SCS      Display SPI Chip select Pin
 - PE4(0x10)   ->  LCD_BS      ??
 - PE5(0x20)   <-  LCD_BUSY_N  Display Busy Pin
 - PE6(0x40)   ->  LCD_REST_N  Display Reset Pin
 - PE7(0x80)   ->  LCD_DC      Display Data/Command Control Pin

 ## 질문사항    
 - BS 핀은 용도가 뭘까?
 - 회로도의 RST_N 회로는 무엇인가?

 ## 코드구현: SPI회로 init함수 구현.
 - https://webnautes.tistory.com/994 참고하여 구현함

 ## 코드구현: 루프문에 들어갈 Frame write 함수 구현. 
 - 받은 메시지에 따라 동작 처리.
