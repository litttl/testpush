
// Get_Image.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGet_ImageApp: 
// �йش����ʵ�֣������ Get_Image.cpp
//

class CGet_ImageApp : public CWinApp
{
public:
	CGet_ImageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGet_ImageApp theApp;