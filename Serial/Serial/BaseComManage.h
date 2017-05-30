#pragma once

class DelegateComManage;

class CBaseComManage
{
public:
	CBaseComManage(void);
	virtual ~CBaseComManage(void);

	//初始化
	virtual void Init() = 0;

	//获取串口状态
	virtual BOOL GetComState() = 0;

	//打开串口
	virtual BOOL OpenCom(CString szComName, CString szBaudRate, 
		CString szByteSize, CString szParity, CString szStopBits) = 0;

	//关闭串口
	virtual void CloseCom() = 0;

	//发送串口数据
	virtual BOOL SendData(const char* pData, const int nLen) = 0;

	//添加串口名称到ComboBox
	virtual void AddComNameToComboBox(CComboBox* pComBox) = 0;

	//添加波特率到ComboBox
	virtual void AddBaudRateToComboBox(CComboBox* pComBox) = 0;

	//添加数据位到ComboBox
	virtual void AddByteSizeToComboBox(CComboBox* pComBox) = 0;

	//添加停止位到ComboBox
	virtual void AddStopBitToComboBox(CComboBox* pComBox) = 0;

	//添加检验位到ComboBox
	virtual void AddParityToComboBox(CComboBox* pComBox) = 0;

public:

	//设置委托
	void SetDelegate(DelegateComManage* p);

protected:

	//委托
	DelegateComManage* m_pDelegate;
};

