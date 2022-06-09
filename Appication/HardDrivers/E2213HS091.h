/*
 * E2213HS091.h
 *
 * Created: 2022-06-09 오후 8:26:21
 *  Author: YS
 */ 


#ifndef E2213HS091_H_
#define E2213HS091_H_


#include "../../main.h"

// extern SPI_HandleTypeDef hspi1;
/*引脚定义*************************************************************************/
/* SPI号 */
#define E2213HS091_SPI					(SPI1)
/* CS */
#define E2213HS091_CS_ENABLE() \
setPin_CS(0)	// HAL_GPIO_WritePin(DO_SCREEN_CS_GPIO_Port, DO_SCREEN_CS_Pin ,GPIO_PIN_RESET)
#define E2213HS091_CS_DISABLE() \
setPin_CS(1)	// HAL_GPIO_WritePin(DO_SCREEN_CS_GPIO_Port, DO_SCREEN_CS_Pin ,GPIO_PIN_SET)
/* DC */
#define E2213HS091_DC_DATA() \
setPin_DC(1)	// HAL_GPIO_WritePin(DO_SCREEN_DC_GPIO_Port, DO_SCREEN_DC_Pin,GPIO_PIN_SET)
#define E2213HS091_DC_CMD() \
setPin_DC(0)	// HAL_GPIO_WritePin(DO_SCREEN_DC_GPIO_Port, DO_SCREEN_DC_Pin,GPIO_PIN_RESET)
/* RST */
#define E2213HS091_RST_ENABLE() \
setPin_RST(1)	// HAL_GPIO_WritePin(DO_SCREEN_RST_GPIO_Port, DO_SCREEN_RST_Pin,GPIO_PIN_SET)
#define E2213HS091_RST_DISABLE() \
setPin_RST(0)	// HAL_GPIO_WritePin(DO_SCREEN_RST_GPIO_Port, DO_SCREEN_RST_Pin,GPIO_PIN_RESET)
/* BUSY */
#define E2213HS091_BUSY_READ() \
readPin_BUSY()	// HAL_GPIO_ReadPin(DI_SCREEN_BUSY_GPIO_Port,DI_SCREEN_BUSY_Pin)
/*枚举*****************************************************************************/
/* 方向：水平/垂直 */
enum ENUM_ORIENTATION
{
	HORIZONTAL,
	VERTICAL
};
/* 填充：实心/空心 */
enum ENUM_FILL
{
	SOLID,
	HOLLOW
};
/*屏幕参数*************************************************************************/
/* X轴坐标0~103；Y轴坐标0~211 */
#define E2213HS091_W 104
#define E2213HS091_H 212
#define E2213HS091_XPOS_MAX 103
#define E2213HS091_YPOS_MAX 211
#define E2213HS091_BUFFER_SIZE (E2213HS091_W * E2213HS091_H / 8)
#define E2213HS091_BUFFER_WIDTH_SIZE (E2213HS091_W / 8)
#define E2213HS091_BUFFER_HEIGHT_SIZE (E2213HS091_H)
/*颜色*****************************************************************************/
enum ENUM_COLOR
{
	WHITE,
	BLACK,
	GREY
};
/* 01红，00白，10黑 */
#define RED_BUFFER1             0X00
// #define RED_BUFFER2             0XFF
#define WHITE_BUFFER1           0x00
// #define WHITE_BUFFER2           0x00
#define BLACK_BUFFER1           0xFF
// #define BLACK_BUFFER2           0x00
/* 红白相间=浅红色，红黑相间=深红色，黑白相间=灰色 */
#define GREY_BUFFER1_SINGLE     0xAA
#define GREY_BUFFER1_DOUBLE     0x55
// #define GREY_BUFFER2            0x00
/*字库*****************************************************************************/
#define FONT_1608		    (0)
#define FONT_1608_WIDTH		(8)
#define FONT_1608_HEIGHT	(16)
/*指令*****************************************************************************/
#define SOFT_RESET_CMD          0x00
#define SOFT_RESET_DATA         0x0E
#define SET_TEMP_CMD            0xE5
#define SET_TEMP_25_DATA        0x19
#define ACTIVE_TEMP_CMD         0xE0
#define ACTIVE_TEMP_25_DATA     0x02
//#define PANEL_SET_CMD         0x00
//#define PANEL_SET_DATA_1      0xCF
//#define PANEL_SET_DATA_2      0x89
#define FIRST_FRAME_CMD         0x10
#define SECOND_FRAME_CMD        0x13
#define TURN_ON_DCDC_CMD        0x04
#define TURN_OFF_DCDC_CMD       0x02
#define DISPLAY_REFRESH_CMD     0x12
/*位操作***************************************************************************/
/* 指定的某一位数置1 */
#define SetBit(x, y)   (x |= (1<<y))
/* 指定的某一位数置0 */
#define ClearBit(x, y) (x &= ~(1<<y))
/* 指定的某一位数取反 */
#define ReverseBit(x,y) (x^=(1<<y))
/* 获取的某一位的值 */
#define GetBit(x, y)   ((x>>y) & 1)
/* 指定的某一位数置为指定的0或1 */
#define WriteBit(data, position, flag)   (flag ? SetBit(data, position) : ClearBit(data, position))
/*函数*******************************************************************************/
void E2213HS091_Init(void);
void E2213HS091_SendImageData(void);
void E2213HS091_ClearFullScreen(enum ENUM_COLOR color);
void E2213HS091_SendUpdateCmd(void);
void E2213HS091_TurnOffDCDC(void);
void E2213HS091_DrawPoint(uint8_t xPos, uint8_t yPos, enum ENUM_COLOR color);
void E2213HS091_DrawLine(uint8_t xStart, uint8_t yStart, uint8_t length,
enum ENUM_ORIENTATION orientation, enum ENUM_COLOR color);
void E2213HS091_DrawRectangle(uint8_t xStart, uint8_t yStart, uint8_t width,
uint8_t height, enum ENUM_FILL fill, enum ENUM_COLOR borderColor,
enum ENUM_COLOR fillColor);
uint8_t E2213HS091_ShowChar(uint8_t xStart, uint8_t yStart, char chr,
uint8_t font, enum ENUM_COLOR fontColor, enum ENUM_COLOR backgroundColor);
uint8_t E2213HS091_ShowCharStr(uint8_t xStart, uint8_t yStart, char* str,
uint8_t font, enum ENUM_COLOR fontColor, enum ENUM_COLOR backgroundColor);
void E2213HS091_DrawBmp(uint8_t xStart, uint8_t yStart, uint8_t bmpWidth,
uint8_t bmpHeight, enum ENUM_COLOR fontColor, enum ENUM_COLOR backgroundColor,
const unsigned char* pic);
// void E2213HS091_DrawImage(uint8_t xStart, uint8_t yStart, uint8_t imageWidth,
// uint8_t imageHeight, const unsigned char* pic);


#endif /* E2213HS091_H_ */