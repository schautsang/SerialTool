#include "stdafx.h"
#include "HandleCode.h"

/***********************************************************
** ��������: ���ֽ�תUnicode�ַ���

** �������: CString& szData		����Unicode�ַ���
					char* pData				���ֽ�����ָ��
************************************************************/
BOOL HandleCode::ConvertAsciitoUnicode(CString& szData, const char* pData)
{
	int nConvertLen = MultiByteToWideChar(CP_ACP, 0, pData, -1, NULL, 0);  

	if (0 == nConvertLen)
	{
		return FALSE;
	}

	BOOL bResult = FALSE;

	LPWSTR pTemp = nullptr;

	pTemp = new WCHAR[nConvertLen];  

	nConvertLen = MultiByteToWideChar(CP_ACP, 0, pData, -1, pTemp, nConvertLen);  

	if (0 != nConvertLen)
	{
		szData.Format(_T("%s"), pTemp);

		bResult = TRUE;
	}
	
	if (nullptr != pTemp)
	{
		delete[] pTemp;

		pTemp = nullptr;
	}

	return bResult;
}

/***********************************************************
** ��������: Unicode�ַ���ת���ֽ�

** �������: const CString &szData		Unicode�ַ���
				   char*& pData					����ת���Ķ��ֽ��ַ���
				   int& nDataLen					����ת���Ķ��ֽ��ַ������ȡ�ע��:���Ȱ���������
************************************************************/
BOOL HandleCode::ConvertUnicodeToAscii(const CString &szData, char*& pData, int& nDataLen)
{
	int nConvertLen;

	nConvertLen = WideCharToMultiByte(CP_ACP, 0, szData, -1 ,NULL, 0, NULL, FALSE);

	if (0 == nConvertLen)
	{
		return FALSE;
	}

	pData = new char[nConvertLen];

	nConvertLen = WideCharToMultiByte(CP_ACP, 0, szData, -1, pData, nConvertLen, NULL, 0);     

	if (0 == nConvertLen)
	{
		return FALSE;
	}

	nDataLen =  nConvertLen;

	return TRUE;
}