#include "StdAfx.h"
#include "Constant.h"

//����
const CString COM_DEF_BAUDRATE = _T("9600");
const CString COM_DEF_BYTESIZE = _T("8");
const CString COM_DEF_STOPBIT = _T("1");
const CString COM_DEF_PARITY = _T("NO");

//��Ϣ
const int MSG_COM_ERROR = WM_USER + 1;//���ڳ����쳣
const int MSG_COM_RECEIVEDATA = WM_USER + 2;//���ڽ�������