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
** 功能描述: 初始化
************************************************************/
void CComManage::Init()
{
	m_pCom = new XCom;
}

/***********************************************************
** 功能描述: 获取串口状态
************************************************************/
BOOL CComManage::GetComState()
{
	return m_pCom->GetComState();
}

/***********************************************************
** 功能描述: 打开串口
************************************************************/
BOOL CComManage::OpenCom(CString szComName, CString szBaudRate, 
	CString szByteSize, CString szParity, CString szStopBits)
{
	return m_pCom->OpenCom(m_pDelegate->GetHWND(), GetComName(szComName), 
		GetBaudRate(szBaudRate), GetParity(szParity), GetByteSize(szByteSize), GetStopBit(szStopBits));
}

/***********************************************************
** 功能描述: 关闭串口
************************************************************/
void CComManage::CloseCom()
{
	m_pCom->CloseCom();
}

/***********************************************************
** 功能描述: 发送串口数据
************************************************************/
BOOL CComManage::SendData(const char* pData, const int nLen)
{
	return m_pCom->SendData(pData, nLen);
}

/***********************************************************
** 功能描述: 添加串口名称到ComboBox
************************************************************/
void CComManage::AddComNameToComboBox(CComboBox* pComBox)
{
	if (nullptr != pComBox)
	{
		pComBox->ResetContent();

		HKEY hKey;  

		//打开串口注册表
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
** 功能描述: 添加波特率到ComboBox
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
** 功能描述: 添加数据位到ComboBox
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
** 功能描述: 添加停止位到ComboBox
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
** 功能描述: 添加检验位到ComboBox
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
** 功能描述: 获取检验位
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
** 功能描述: 获取停止位
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
** 功能描述: 获取数据位
************************************************************/
BYTE CComManage::GetByteSize(CString szData)
{
	return (BYTE)_ttoi(szData);
}

/***********************************************************
** 功能描述: 获取波特率
************************************************************/
DWORD CComManage::GetBaudRate(CString szData)
{
	return (DWORD)_ttoi(szData);
}

/***********************************************************
** 功能描述: 获取串口名称
************************************************************/
CString CComManage::GetComName(CString szComName)
{
	return _T("\\\\.\\") + szComName;
}