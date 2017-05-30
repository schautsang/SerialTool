#pragma once

#include "BaseCom.h"

class XCom : public CBaseCom
{
public:
	XCom(void);
	~XCom(void);

	//获取状态
	virtual BOOL GetComState();

	//打开串口
	virtual BOOL OpenCom(HWND pPortOwner, CString szComName, DWORD nBaudRate, 
		BYTE cParity, BYTE nByteSize, BYTE cStopsBits);

	//关闭串口
	virtual void CloseCom();

	//发送串口数据
	virtual BOOL SendData(const char* pData, const int nLen);

	//获取串口名称
	virtual CString GetComName();

public:

	//串口线程函数
	static UINT ComThread(LPVOID pParam);

	//接收字符
	BOOL ReceiveChar(DWORD dwLen);

private:

	//打开串口
	BOOL OpenCom(CString szComName);

	//设置DCB
	BOOL SetDCB(DWORD nBaudRate, BYTE cParity, BYTE nByteSize, 
		BYTE cStopsBits);

	//开始监控
	void StartMonitoring();

	//停止监控
	void StopMonitoring();

public:

	//串口句柄
	HANDLE m_hComm;

	//线程结束事件句柄
	HANDLE m_hThreadEndEvent; 

	//窗口句柄
	HWND m_Owner;

	//互斥锁
	CRITICAL_SECTION m_csCommunicationSync;   

private:

	//状态
	BOOL m_bSate;

	//串口DCB
	DCB	m_dcb;

	//串口名称
	CString m_szComName;
};

