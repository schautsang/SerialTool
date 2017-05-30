#pragma once

#include "BaseCom.h"

class XCom : public CBaseCom
{
public:
	XCom(void);
	~XCom(void);

	//��ȡ״̬
	virtual BOOL GetComState();

	//�򿪴���
	virtual BOOL OpenCom(HWND pPortOwner, CString szComName, DWORD nBaudRate, 
		BYTE cParity, BYTE nByteSize, BYTE cStopsBits);

	//�رմ���
	virtual void CloseCom();

	//���ʹ�������
	virtual BOOL SendData(const char* pData, const int nLen);

	//��ȡ��������
	virtual CString GetComName();

public:

	//�����̺߳���
	static UINT ComThread(LPVOID pParam);

	//�����ַ�
	BOOL ReceiveChar(DWORD dwLen);

private:

	//�򿪴���
	BOOL OpenCom(CString szComName);

	//����DCB
	BOOL SetDCB(DWORD nBaudRate, BYTE cParity, BYTE nByteSize, 
		BYTE cStopsBits);

	//��ʼ���
	void StartMonitoring();

	//ֹͣ���
	void StopMonitoring();

public:

	//���ھ��
	HANDLE m_hComm;

	//�߳̽����¼����
	HANDLE m_hThreadEndEvent; 

	//���ھ��
	HWND m_Owner;

	//������
	CRITICAL_SECTION m_csCommunicationSync;   

private:

	//״̬
	BOOL m_bSate;

	//����DCB
	DCB	m_dcb;

	//��������
	CString m_szComName;
};

