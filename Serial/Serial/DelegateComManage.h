#pragma once

class DelegateComManage
{
public:
	DelegateComManage(void);
	~DelegateComManage(void);

	//»ñÈ¡´°¿Ú¾ä±ú
	virtual HWND GetHWND() = 0;
};

