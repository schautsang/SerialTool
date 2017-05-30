#include "StdAfx.h"
#include "Constant.h"

//常量
const CString COM_DEF_BAUDRATE = _T("9600");
const CString COM_DEF_BYTESIZE = _T("8");
const CString COM_DEF_STOPBIT = _T("1");
const CString COM_DEF_PARITY = _T("NO");

//消息
const int MSG_COM_ERROR = WM_USER + 1;//串口出现异常
const int MSG_COM_RECEIVEDATA = WM_USER + 2;//串口接收数据