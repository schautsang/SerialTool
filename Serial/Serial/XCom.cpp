#include "StdAfx.h"
#include "XCom.h"
#include "Constant.h"

XCom::XCom(void)
{
	m_bSate = FALSE;

	m_Owner = nullptr;

	m_hComm = INVALID_HANDLE_VALUE;

	m_hThreadEndEvent = nullptr;

	m_szComName = _T("");

	InitializeCriticalSection(&m_csCommunicationSync);  
}


XCom::~XCom(void)
{
	CloseCom();
}

BOOL XCom::OpenCom(HWND pPortOwner, CString szComName, DWORD nBaudRate, 
	BYTE cParity, BYTE nByteSize, BYTE cStopsBits)
{
	if (OpenCom(szComName))
	{
		if (SetDCB(nBaudRate, cParity, nByteSize, cStopsBits))
		{
			if (SetCommMask(m_hComm, EV_RXCHAR))
			{
				if(PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT))
				{
					m_Owner = pPortOwner;

					m_bSate  = TRUE;

					m_szComName = szComName;

					StartMonitoring();
				}
			}
		}
	}

	if (!m_bSate)
	{
		CloseCom();
	}

	return m_bSate;
}

BOOL XCom::SetDCB(DWORD nBaudRate, BYTE cParity, BYTE nByteSize, BYTE cStopsBits)
{
	if (!GetCommState(m_hComm, &m_dcb))
	{
		return FALSE;
	}

	m_dcb.BaudRate = nBaudRate; 
	m_dcb.Parity   = cParity;
	m_dcb.ByteSize = nByteSize;
	m_dcb.StopBits = cStopsBits;

	return SetCommState(m_hComm, &m_dcb);
}

BOOL XCom::GetComState()
{
	return m_bSate;
}

CString XCom::GetComName()
{
	return m_szComName;
}

void XCom::CloseCom()
{
	m_bSate  = FALSE;

	m_szComName = _T("");

	if (INVALID_HANDLE_VALUE != m_hComm)
	{
		SetCommMask(m_hComm, NULL);
	}

	StopMonitoring();

	if (INVALID_HANDLE_VALUE != m_hComm)
	{
		CloseHandle(m_hComm);

		m_hComm = INVALID_HANDLE_VALUE;
	}
}

BOOL XCom::OpenCom(CString szComName)
{
	m_hComm = CreateFile(szComName, GENERIC_READ | GENERIC_WRITE, 0, NULL,							
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 0);								

	if (INVALID_HANDLE_VALUE == m_hComm)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void XCom::StartMonitoring()
{
	m_hThreadEndEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	AfxBeginThread(ComThread, this);
}

void XCom::StopMonitoring()
{
	if (nullptr != m_hThreadEndEvent)
	{
		WaitForSingleObject(m_hThreadEndEvent, INFINITE);

		CloseHandle(m_hThreadEndEvent); 

		m_hThreadEndEvent = nullptr;
	}
}

BOOL XCom::SendData(const char* pData, const int nLen)
{
	DWORD nNumberOfBytesWritten;

	OVERLAPPED overlapped = {0};

	BOOL bResult = FALSE;

	EnterCriticalSection(&m_csCommunicationSync);

	BOOL bResultWrite = WriteFile(m_hComm, pData, nLen, &nNumberOfBytesWritten, &overlapped);

	if (bResultWrite)
	{
		bResult = TRUE;
	}
	else
	{
		DWORD dwError = GetLastError();

		if (ERROR_IO_PENDING == dwError)
		{
			bResultWrite = GetOverlappedResult(m_hComm, &overlapped, &nNumberOfBytesWritten, TRUE); 

			if (bResultWrite)
			{
				bResult = TRUE;
			}
		}
	}

	LeaveCriticalSection(&m_csCommunicationSync); 

	return bResult;
}

BOOL XCom::ReceiveChar(DWORD dwLen)
{
	DWORD BytesRead = 0;

	OVERLAPPED overlapped = {0};

	BOOL bResult = FALSE;

	EnterCriticalSection(&m_csCommunicationSync);

	unsigned char* pData = new unsigned char[dwLen];

	BOOL bReadResult = ReadFile(m_hComm, pData, dwLen, &BytesRead, &overlapped);

	if (bReadResult)
	{
		bResult = TRUE;
	}
	else
	{
		DWORD dwError = GetLastError();

		if (ERROR_IO_PENDING == dwError)
		{
			bReadResult = GetOverlappedResult(m_hComm, &overlapped, &BytesRead, TRUE); 

			if (bReadResult)
			{
				bResult = TRUE;
			}
		}
	}

	if (bResult)
	{
		::PostMessage(m_Owner, MSG_COM_RECEIVEDATA, (WPARAM)pData, BytesRead);
	}

	LeaveCriticalSection(&m_csCommunicationSync); 

	return bResult;
}

UINT XCom::ComThread(LPVOID pParam)
{
	//TRACE("XCOM ComThread:Start\n");

	XCom *pCom = (XCom*)pParam;

	DWORD dwEvtMask = 0;

	BOOL bResult = TRUE;

	DWORD dwError = 0;

	COMSTAT comstat;

	BOOL bRunning = TRUE;

	while (bRunning && pCom->m_bSate) 
	{ 
		bResult = WaitCommEvent(pCom->m_hComm, &dwEvtMask, NULL);

		if (!bResult)  
		{
			DWORD dwError = GetLastError();

			switch (dwError) 
			{ 
			case ERROR_IO_PENDING: 	
				{ 
					break;
				}
			case 87:
				{
					break;
				}
			default:
				{
					::PostMessage(pCom->m_Owner, MSG_COM_ERROR, NULL, NULL);

					bRunning = FALSE;

					break;
				}
			}
		} 
		else
		{
			bResult = ClearCommError(pCom->m_hComm, &dwError, &comstat);

			if (0 == comstat.cbInQue)
			{
				continue;
			}

			pCom->ReceiveChar(comstat.cbInQue);
		}
	}

	SetEvent(pCom->m_hThreadEndEvent);

	//TRACE("XCOM ComThread:End\n");

	return 0;
}

