
// check_color_mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ccheck_color_mfcApp: 
// �йش����ʵ�֣������ check_color_mfc.cpp
//

class Ccheck_color_mfcApp : public CWinApp
{
public:
	Ccheck_color_mfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ccheck_color_mfcApp theApp;