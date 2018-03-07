
// Get_ImageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Get_Image.h"
#include "Get_ImageDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <direct.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//std::string file_head="";

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGet_ImageDlg �Ի���



CGet_ImageDlg::CGet_ImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGet_ImageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGet_ImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGet_ImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGet_ImageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGet_ImageDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CGet_ImageDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CGet_ImageDlg::OnEnChangeMfceditbrowse1)
END_MESSAGE_MAP()


// CGet_ImageDlg ��Ϣ�������

BOOL CGet_ImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGet_ImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGet_ImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGet_ImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGet_ImageDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString cam_no;
	GetDlgItem(IDC_EDIT2)->GetWindowText(cam_no);
	std::string file_no1(CW2A(cam_no.GetString()));
	int cam_int_no = std::atoi(file_no1.c_str());

	cv::VideoCapture capture(cam_int_no);
	
	if (!capture.isOpened())
	{
		std::cout << "Cam is failed!" << std::endl;
	}
	cv::Mat Frame;


	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	//capture.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	//capture.set(CV_CAP_PROP_FRAME_HEIGHT,1080);

	int rows_roi = 1090;
	int cols_roi = 270;

	cv::Point left_top = cv::Point(640-rows_roi/2, 360-cols_roi/2);
	cv::Point left_bottom = cv::Point(640-rows_roi/2, 360+cols_roi/2);
	cv::Point right_top = cv::Point(640+rows_roi/2, 360-cols_roi/2);
	cv::Point right_bottom = cv::Point(640+rows_roi/2, 360+cols_roi/2);


	bool stop = false;
	while (!stop)
	{
		capture >> Frame;
		
//		cv::imwrite("D:\\codes\\vc\\test\\test_opencv\\photos\\photos_test.jpg",Frame);

		cv::Mat img_show = Frame.clone();

		cv::line(img_show, left_top, left_bottom, cv::Scalar(0, 255, 0), 4);
		cv::line(img_show, left_top, right_top, cv::Scalar(0, 255, 0), 4);
		cv::line(img_show, left_bottom, right_bottom, cv::Scalar(0, 255, 0), 4);
		cv::line(img_show, right_bottom, right_top, cv::Scalar(0, 255, 0), 4);
		 
		cv::namedWindow("Cam_View", 0);
		cv::imshow("Cam_View", img_show);

		int key_no = cv::waitKey(30);
		if (key_no == 27)
		{
			stop = true;
		}
		else if (key_no == 8)
		{

			CString file_no;
			GetDlgItem(IDC_EDIT1)->GetWindowText(file_no);

			//		std::string file_no1 = file_no.GetBuffer();
			std::string file_no1(CW2A(file_no.GetString()));

			std::string file_head = "D:\\codes\\vc\\test\\test_opencv\\photos1\\20180307\\";

			std::string file_end = ".jpg";
			std::string dir_name = file_head + file_no1;
			_mkdir(dir_name.c_str());

			std::string file_head1 = dir_name + "\\img";

			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			char char_phno[64];
			sprintf_s(char_phno, "%d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);


			std::string file_name = file_head1 + char_phno + file_end;
			cv::imwrite(file_head1 + char_phno + file_end, Frame);
			std::cout << "here!" << std::endl;
		}
	}
}


void CGet_ImageDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	cv::VideoCapture capture(0);

	if (!capture.isOpened())
	{
		std::cout << "Cam is failed!" << std::endl;
	}
	cv::Mat Frame;


	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	bool stop = false;
	while (!stop)
	{
		capture >> Frame;
		cv::waitKey(30);
		//		cv::namedWindow("Cam_View",0);
		cv::imshow("Cam_View1", Frame);

	}
}

void CGet_ImageDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CGet_ImageDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//file_head = "";
	//std::cout << "here!" << std::endl;
	char szdir[MAX_PATH];
	BROWSEINFO bi;
//	bi.hwndOwner = (HWND)hwnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;

	char* pt_title = "Select file:";
	CString title = CString(pt_title);
	USES_CONVERSION;
	bi.lpszTitle = A2CW(W2A(title));
	bi.iImage = 0;

	std::cout << "here!" << std::endl;
}
