#include "stdafx.h"
#include "HandleCode.h"

/***********************************************************
** 功能描述: 多字节转Unicode字符串

** 输入参数: CString& szData		保存Unicode字符串
					char* pData				多字节数据指针
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
** 功能描述: Unicode字符串转多字节

** 输入参数: const CString &szData		Unicode字符串
				   char*& pData					保存转换的多字节字符串
				   int& nDataLen					保存转换的多字节字符串长度。注意:长度包括结束符
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