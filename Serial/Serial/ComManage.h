#pragma once

#include "BaseComManage.h"

class CBaseCom;

class CComManage : public CBaseComManage
{
public:
	CComManage(void);
	~CComManage(void);

	//��ʼ��
	virtual void Init();

	//��ȡ����״̬
	virtual BOOL GetComState();

	//�򿪴���
	virtual BOOL OpenCom(CString szComName, CString szBaudRate, 
		CString szByteSize, CString szParity, CString szStopBits);

	//�رմ���
	virtual void CloseCom();

	//���ʹ�������
	virtual BOOL SendData(const char* pData, const int nLen);

	//��Ӵ������Ƶ�ComboBox
	virtual void AddComNameToComboBox(CComboBox* pComBox);

	//��Ӳ����ʵ�ComboBox
	virtual void AddBaudRateToComboBox(CComboBox* pComBox);

	//�������λ��ComboBox
	virtual void AddByteSizeToComboBox(CComboBox* pComBox);

	//���ֹͣλ��ComboBox
	virtual void AddStopBitToComboBox(CComboBox* pComBox);

	//��Ӽ���λ��ComboBox
	virtual void AddParityToComboBox(CComboBox* pComBox);

private:

	//��ȡ����λ
	BYTE GetParity(CString szData);

	//��ȡֹͣλ
	BYTE GetStopBit(CString szData);

	//��ȡ����λ
	BYTE GetByteSize(CString szData);

	//��ȡ������
	DWORD GetBaudRate(CString szData);

	//��ȡ��������
	CString GetComName(CString szComName);

private:

	//����
	CBaseCom* m_pCom;
};

