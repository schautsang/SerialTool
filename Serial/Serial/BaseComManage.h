#pragma once

class DelegateComManage;

class CBaseComManage
{
public:
	CBaseComManage(void);
	virtual ~CBaseComManage(void);

	//��ʼ��
	virtual void Init() = 0;

	//��ȡ����״̬
	virtual BOOL GetComState() = 0;

	//�򿪴���
	virtual BOOL OpenCom(CString szComName, CString szBaudRate, 
		CString szByteSize, CString szParity, CString szStopBits) = 0;

	//�رմ���
	virtual void CloseCom() = 0;

	//���ʹ�������
	virtual BOOL SendData(const char* pData, const int nLen) = 0;

	//��Ӵ������Ƶ�ComboBox
	virtual void AddComNameToComboBox(CComboBox* pComBox) = 0;

	//��Ӳ����ʵ�ComboBox
	virtual void AddBaudRateToComboBox(CComboBox* pComBox) = 0;

	//�������λ��ComboBox
	virtual void AddByteSizeToComboBox(CComboBox* pComBox) = 0;

	//���ֹͣλ��ComboBox
	virtual void AddStopBitToComboBox(CComboBox* pComBox) = 0;

	//��Ӽ���λ��ComboBox
	virtual void AddParityToComboBox(CComboBox* pComBox) = 0;

public:

	//����ί��
	void SetDelegate(DelegateComManage* p);

protected:

	//ί��
	DelegateComManage* m_pDelegate;
};

