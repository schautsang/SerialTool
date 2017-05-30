#pragma once

//编码转换类
class HandleCode
{
public:

	//多字节转Unicode字符串
	static BOOL ConvertAsciitoUnicode(CString& szData, const char* pData);

	//Unicode字符串转多字节
	static BOOL ConvertUnicodeToAscii(const CString& szData, char*& pData, 
		int& nDataLen);
};