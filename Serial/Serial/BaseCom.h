#pragma once

class CBaseCom
{
public:
	CBaseCom(void);
	virtual ~CBaseCom(void);

	//�򿪴���
	virtual BOOL OpenCom(HWND pPortOwner, CString szComName, 
		DWORD nBaudRate, BYTE cParity, BYTE nByteSize, BYTE cStopsBits) = 0;

	//��ȡ����״̬
	virtual BOOL GetComState() = 0;

	//�رմ���
	virtual void CloseCom() = 0;

	//���ʹ�������
	virtual BOOL SendData(const char* pData, const int nLen) = 0;
};

