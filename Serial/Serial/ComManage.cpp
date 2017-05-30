#include "StdAfx.h"
#include "ComManage.h"
#include "DelegateComManage.h"
#include "XCom.h"

CComManage::CComManage(void)
{
	m_pCom = nullptr;
}


CComManage::~CComManage(void)
{
	if (nullptr != m_pCom)
	{
		delete m_pCom;

		m_pCom = nullptr;
	}
}

/***********************************************************
** ��������: ��ʼ��
************************************************************/
void CComManage::Init()
{
	m_pCom = new XCom;
}

/***********************************************************
** ��������: ��ȡ����״̬
************************************************************/
BOOL CComManage::GetComState()
{
	return m_pCom->GetComState();
}

/***********************************************************
** ��������: �򿪴���
************************************************************/
BOOL CComManage::OpenCom(CString szComName, CString szBaudRate, 
	CString szByteSize, CString szParity, CString szStopBits)
{
	return m_pCom->OpenCom(m_pDelegate->GetHWND(), GetComName(szComName), 
		GetBaudRate(szBaudRate), GetParity(szParity), GetByteSize(szByteSize), GetStopBit(szStopBits));
}

/***********************************************************
** ��������: �رմ���
************************************************************/
void CComManage::CloseCom()
{
	m_pCom->CloseCom();
}

/***********************************************************
** ��������: ���ʹ�������
************************************************************/
BOOL CComManage::SendData(const char* pData, const int nLen)
{
	return m_pCom->SendData(pData, nLen);
}

/***********************************************************
** ��������: ��Ӵ������Ƶ�ComboBox
************************************************************/
void CComManage::AddComNameToComboBox(CComboBox* pComBox)
{
	if (nullptr != pComBox)
	{
		pComBox->ResetContent();

		HKEY hKey;  

		//�򿪴���ע���
		LONG nResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), 
			NULL, KEY_READ, &hKey);

		if (ERROR_SUCCESS == nResult)     
		{
			DWORD dwPortName = MAX_PATH;
			DWORD dwComName = MAX_PATH;

			TCHAR cPortName[MAX_PATH];
			TCHAR cComName[MAX_PATH];  

			DWORD dwIndex = 0;

			CString szTemp = _T("");

			while(1)   
			{
				ZeroMemory(cPortName, MAX_PATH);
				ZeroMemory(cComName, MAX_PATH);

				dwPortName = MAX_PATH;
				dwComName = MAX_PATH;

				if (::RegEnumValue(hKey, dwIndex, cPortName, &dwPortName, NULL, NULL, (LPBYTE)cComName, 
					&dwComName) == ERROR_NO_MORE_ITEMS)
				{
					break;
				}

				szTemp.Format(_T("%s"), cComName);

				pComBox->AddString(cComName);

				dwIndex++;
			}

			RegCloseKey(hKey);
		}
	}
}

/***********************************************************
** ��������: ��Ӳ����ʵ�ComboBox
************************************************************/
void CComManage::AddBaudRateToComboBox(CComboBox* pComBox)
{
	if (nullptr != pComBox)
	{
		pComBox->ResetContent();

		pComBox->AddString(_T("2400"));
		pComBox->AddString(_T("4800"));
		pComBox->AddString(_T("9600"));
		pComBox->AddString(_T("14400"));
		pComBox->AddString(_T("19200"));
		pComBox->AddString(_T("38400"));
		pComBox->AddString(_T("57600"));
		pComBox->AddString(_T("115200"));
		pComBox->AddString(_T("128000"));
		pComBox->AddString(_T("256000"));
	}
}

/***********************************************************
** ��������: �������λ��ComboBox
************************************************************/
void CComManage::AddByteSizeToComboBox(CComboBox* pComBox)
{
	if (nullptr != pComBox)
	{
		pComBox->ResetContent();

		pComBox->AddString(_T("4"));
		pComBox->AddString(_T("5"));
		pComBox->AddString(_T("6"));
		pComBox->AddString(_T("7"));
		pComBox->AddString(_T("8"));
	}
}

/***********************************************************
** ��������: ���ֹͣλ��ComboBox
************************************************************/
void CComManage::AddStopBitToComboBox(CComboBox* pComBox)
{
	if (nullptr != pComBox)
	{
		pComBox->ResetContent();

		pComBox->AddString(_T("1"));
		pComBox->AddString(_T("1.5"));
		pComBox->AddString(_T("2"));
	}
}

/***********************************************************
** ��������: ��Ӽ���λ��ComboBox
************************************************************/
void CComManage::AddParityToComboBox(CComboBox* pComBox)
{
	if (nullptr != pComBox)
	{
		pComBox->ResetContent();

		pComBox->AddString(_T("NO"));
		pComBox->AddString(_T("ODD"));
		pComBox->AddString(_T("EVEN"));
		pComBox->AddString(_T("MARK"));
	}
}

/***********************************************************
** ��������: ��ȡ����λ
************************************************************/
BYTE CComManage::GetParity(CString szData)
{
	BYTE cData = 0;

	if (szData ==  _T("EVEN"))
	{
		cData = EVENPARITY;
	}
	else if (szData == _T("ODD"))
	{
		cData = ODDPARITY;
	}
	else if (szData == _T("NO"))
	{
		cData = NOPARITY;
	}
	else if (szData == _T("MARK"))
	{
		cData = MARKPARITY;
	}

	return cData;
}

/***********************************************************
** ��������: ��ȡֹͣλ
************************************************************/
BYTE CComManage::GetStopBit(CString szData)
{
	BYTE cData = 0;

	if (szData ==  _T("1"))
	{
		cData = ONESTOPBIT;
	}
	else if (szData == _T("1.5"))
	{
		cData = ONE5STOPBITS;
	}
	else if (szData == _T("2"))
	{
		cData = TWOSTOPBITS;
	}
	
	return cData;
}

/***********************************************************
** ��������: ��ȡ����λ
************************************************************/
BYTE CComManage::GetByteSize(CString szData)
{
	return (BYTE)_ttoi(szData);
}

/***********************************************************
** ��������: ��ȡ������
************************************************************/
DWORD CComManage::GetBaudRate(CString szData)
{
	return (DWORD)_ttoi(szData);
}

/***********************************************************
** ��������: ��ȡ��������
************************************************************/
CString CComManage::GetComName(CString szComName)
{
	return _T("\\\\.\\") + szComName;
}