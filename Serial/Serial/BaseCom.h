#pragma once

class CBaseCom
{
public:
	CBaseCom(void);
	virtual ~CBaseCom(void);

	//打开串口
	virtual BOOL OpenCom(HWND pPortOwner, CString szComName, 
		DWORD nBaudRate, BYTE cParity, BYTE nByteSize, BYTE cStopsBits) = 0;

	//获取串口状态
	virtual BOOL GetComState() = 0;

	//关闭串口
	virtual void CloseCom() = 0;

	//发送串口数据
	virtual BOOL SendData(const char* pData, const int nLen) = 0;
};

