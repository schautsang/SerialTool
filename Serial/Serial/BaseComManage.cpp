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
** ��������: ����ί��
************************************************************/
void CBaseComManage::SetDelegate(DelegateComManage* p)
{
	m_pDelegate = p;
}
