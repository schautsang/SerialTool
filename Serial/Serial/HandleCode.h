#pragma once

//����ת����
class HandleCode
{
public:

	//���ֽ�תUnicode�ַ���
	static BOOL ConvertAsciitoUnicode(CString& szData, const char* pData);

	//Unicode�ַ���ת���ֽ�
	static BOOL ConvertUnicodeToAscii(const CString& szData, char*& pData, 
		int& nDataLen);
};