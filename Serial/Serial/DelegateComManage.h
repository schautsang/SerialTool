#pragma once

class DelegateComManage
{
public:
	DelegateComManage(void);
	~DelegateComManage(void);

	//��ȡ���ھ��
	virtual HWND GetHWND() = 0;
};

