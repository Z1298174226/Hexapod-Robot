/*********************************************************************
*                SEGGER MICROCONTROLLER GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2003-2012     SEGGER Microcontroller GmbH & Co KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "glcd.h"


//
// 设置LCD的物理显示大小
//
#define XSIZE_PHYS  320
#define YSIZE_PHYS  240

//
// 定义所使用的演示转换模式
//
#define COLOR_CONVERSION  GUICC_565

//
// 定义显示驱动的类型
//
#define DISPLAY_DRIVER  GUIDRV_FLEXCOLOR


/*********************************************************************
*
*       检测是否正确配置
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

/*********************************************************************
*
* 定义和配置
*
**********************************************************************
*/

//
//定义LCD的基地址
//
#define LCD_REG_16   *(vu16*)((u32)0x60000000)
#define LCD_DATA_16  *(vu16*)((u32)0x60020000)

/*********************************************************************
*
* 静态数据
*
**********************************************************************
*/

/*********************************************************************
*
*  本地函数
*
**********************************************************************
*/

/**************************************************************************************************************
 * 函数名：_LcdSetReg()
 * 输入  ：U16 Data   16bit寄存器地址
 * 输出  ：void
 * 描述  ：设置LCD寄存器函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _LcdSetReg(U16 Data) {
  LCD_REG_16 = Data;
}

/**************************************************************************************************************
 * 函数名：_LcdWriteData()
 * 输入  ：U16 Data   16bit数据
 * 输出  ：void
 * 描述  ：LCD写数据函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _LcdWriteData(U16 Data) {
  LCD_DATA_16 = Data;
}
/**************************************************************************************************************
 * 函数名：_LcdWriteDataMultiple()
 * 输入  ：U16 Data   16bit数据   int NumItems  要写的数据长度
 * 输出  ：void
 * 描述  ：LCD写多个数据数据函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _LcdWriteDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    LCD_DATA_16 = *pData++;
  }
}

/**************************************************************************************************************
 * 函数名：_LcdReadDataMultiple()
 * 输入  ：U16 Data   16bit数据   int NumItems  要读的数据长度
 * 输出  ：void
 * 描述  ：LCD读多个数据数据函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _LcdReadDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    *pData++ = LCD_DATA_16;
  }
}

/**************************************************************************************************************
 * 函数名：__WriteReg()
 * 输入  ：U16 Reg要写的寄存器地址，U16 Data   16bit数据
 * 输出  ：void
 * 描述  ：LCD写寄存器函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _WriteReg(U16 Reg, U16 Data) {
  _LcdSetReg   (Reg);
  _LcdWriteData(Data);
}

/**************************************************************************************************************
 * 函数名：_InitLcdController()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD初始化函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _InitLcdController(void) {
 GLCD_Init();
}

/**************************************************************************************************************
 * 函数名：_Init()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：GUI硬件初始化函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void _Init(void) {
  _InitLcdController();
  //
  // Start joystick timer
  //
  //OS_CREATETIMER(&_JoystickTimer, _ExecJoystick, JOYSTICK_TIMER_INTERVAL);
}

/*********************************************************************
*
*       公共函数
*
**********************************************************************
*/
/**************************************************************************************************************
 * 函数名：LCD_X_Config()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD硬件显示配置函数
 * 调用  ：内部调用        
 *****************************************************************************************************************/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // 设置显示驱动及颜色转换类型
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // 配置显示的大小分辨率
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // 显示方向的配置
  //
  Config.Orientation =  GUI_SWAP_XY |GUI_MIRROR_Y;// GUI_MIRROR_X;//
  //Config.RegEntryMode=8;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // 设置屏幕显示的底层API
  //
  PortAPI.pfWrite16_A0  = _LcdSetReg;
  PortAPI.pfWrite16_A1  = _LcdWriteData;
  PortAPI.pfWriteM16_A1 = _LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = _LcdReadDataMultiple;
  /*设置显示控制器*/
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
    _Init();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

