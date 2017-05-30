#pragma once

#include "BaseComManage.h"

class CBaseCom;

class CComManage : public CBaseComManage
{
public:
	CComManage(void);
	~CComManage(void);

	//初始化
	virtual void Init();

	//获取串口状态
	virtual BOOL GetComState();

	//打开串口
	virtual BOOL OpenCom(CString szComName, CString szBaudRate, 
		CString szByteSize, CString szParity, CString szStopBits);

	//关闭串口
	virtual void CloseCom();

	//发送串口数据
	virtual BOOL SendData(const char* pData, const int nLen);

	//添加串口名称到ComboBox
	virtual void AddComNameToComboBox(CComboBox* pComBox);

	//添加波特率到ComboBox
	virtual void AddBaudRateToComboBox(CComboBox* pComBox);

	//添加数据位到ComboBox
	virtual void AddByteSizeToComboBox(CComboBox* pComBox);

	//添加停止位到ComboBox
	virtual void AddStopBitToComboBox(CComboBox* pComBox);

	//添加检验位到ComboBox
	virtual void AddParityToComboBox(CComboBox* pComBox);

private:

	//获取检验位
	BYTE GetParity(CString szData);

	//获取停止位
	BYTE GetStopBit(CString szData);

	//获取数据位
	BYTE GetByteSize(CString szData);

	//获取波特率
	DWORD GetBaudRate(CString szData);

	//获取串口名称
	CString GetComName(CString szComName);

private:

	//串口
	CBaseCom* m_pCom;
};

