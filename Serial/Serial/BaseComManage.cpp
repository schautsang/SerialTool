#include "StdAfx.h"
#include "BaseComManage.h"


CBaseComManage::CBaseComManage(void)
{
	m_pDelegate = nullptr;
}


CBaseComManage::~CBaseComManage(void)
{
}

/***********************************************************
** 功能描述: 设置委托
************************************************************/
void CBaseComManage::SetDelegate(DelegateComManage* p)
{
	m_pDelegate = p;
}
