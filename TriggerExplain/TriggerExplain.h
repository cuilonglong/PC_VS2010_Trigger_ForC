
// TriggerExplain.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTriggerExplainApp:
// �йش����ʵ�֣������ TriggerExplain.cpp
//

class CTriggerExplainApp : public CWinApp
{
public:
	CTriggerExplainApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTriggerExplainApp theApp;