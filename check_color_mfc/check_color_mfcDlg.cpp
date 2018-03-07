
// check_color_mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "check_color_mfc.h"
#include "check_color_mfcDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <direct.h>
#include "user_define.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string file_head="";



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Ccheck_color_mfcDlg 对话框
Ccheck_color_mfcDlg::Ccheck_color_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ccheck_color_mfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccheck_color_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ccheck_color_mfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ccheck_color_mfcDlg::OnBnClickedButton1)
//	ON_EN_CHANGE(IDC_EDIT2, &Ccheck_color_mfcDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &Ccheck_color_mfcDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Ccheck_color_mfcDlg 消息处理程序

BOOL Ccheck_color_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ccheck_color_mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ccheck_color_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ccheck_color_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ccheck_color_mfcDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         strFolderPath = TEXT("");

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择处理结果存储路径");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框    
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名    
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}



	USES_CONVERSION;
	std::string str1(W2A(strFolderPath));

	file_head = str1+"\\";

	GetDlgItem(1001)->SetWindowTextW(strFolderPath);


	std::cout << "here" << std::endl;
}


void Ccheck_color_mfcDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

	CString cam_no;
	GetDlgItem(IDC_EDIT3)->GetWindowText(cam_no);
	std::string file_no1(CW2A(cam_no.GetString()));
	int cam_init_no = std::atoi(file_no1.c_str());

	cv::VideoCapture capture(cam_init_no);

	if (!capture.isOpened())
	{
		std::cout << "Cam if failed!" << std::endl;
	}
	cv::Mat Frame;
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	bool stop = false;
// 获取全局的参考值
	cv::Mat ref_value_meanblock = cv::Mat::zeros(12, 1, CV_32FC1);

	while (!stop)
	{
		capture >> Frame;
		cv::Mat img_show = Frame.clone();
		cv::Mat img_cal  = Frame.clone();

		cv::Mat img_rotate(img_show.size(), CV_8UC3), value_meanblock;
		get_color_imshow(img_show, ref_value_meanblock, img_rotate, value_meanblock);

		cv::namedWindow("Cam_View", 0);
		cv::imshow("Cam_View", img_rotate);

		cv::namedWindow("Cam_ori", 0);
		cv::imshow("Cam_ori", img_show);

		int key_no = cv::waitKey(30);
		if (key_no == 27)
		{
			stop = true;
		}

		// get the ref_img
		else if (key_no == 13)
		{
			std::cout << "reference-photos--- " << std::endl;
			cv::Mat ref_img_rotate;

#ifndef IS_GETDATA0301
//			get_color_noout(img_cal, ref_img_rotate, ref_value_meanblock);
#endif
#ifdef IS_GETDATA0301
			cv::Mat img_ref = cv::imread("D:\\codes\\vc\\test\\test_opencv\\photos1\\20180302\\ref\\cam_old_ref.jpg", 1);
			get_color_noout(img_ref, ref_img_rotate, ref_value_meanblock);
#endif
#ifdef IS_GETJHCAMDATA
			cv::Mat img_ref = cv::imread("D:\\photots\\QQSJ8808\\CAM01\\img_n_bottom.jpg", 1);
			get_color_noout(img_ref, ref_img_rotate, ref_value_meanblock);
#endif

			std::cout << "completed!" << std::endl;

		}

		// get the cur_img
		else if (key_no == 8)
		{
			std::cout << "current-photos cal---" << std::endl;
			cv::Mat cur_img_rotate, cur_value_meanblock;
#ifndef IS_GETJHCAMDATA
			get_color_noout(img_cal, cur_img_rotate, cur_value_meanblock);
#endif
#ifdef IS_GETJHCAMDATA
			cv::Mat img_in = cv::imread("D:\\photots\\QQSJ8808\\CAM01\\img_n_bottom.jpg",1);
			get_color_noout(img_in, cur_img_rotate, cur_value_meanblock);
#endif
			
			std::string filename = file_head+"test.txt";

			for (int i = 0; i < 12; i++)
			{
				mattotxt(cur_value_meanblock, filename, i);
			}

			for (int i = 0; i < 12; i++)
			{
				mattotxt(cur_value_meanblock - ref_value_meanblock, filename, i);
			}

			CString file_no;
			GetDlgItem(IDC_EDIT2)->GetWindowText(file_no);

			std::string file_no1(CW2A(file_no.GetString()));
			std::string file_end = ".jpg";
			std::string file_end_rotate = "_rotate.jpg";
			std::string dir_name = file_head + file_no1;
			_mkdir(dir_name.c_str());

			std::string file_head1 = dir_name + "\\img";

			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			char char_phno[64];
			sprintf_s(char_phno, "%d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);


			std::string file_name = file_head1 + char_phno + file_end;
			cv::imwrite(file_head1 + char_phno + file_end, Frame);
			cv::imwrite(file_head1 + char_phno + file_end_rotate, cur_img_rotate);



			std::cout << "completed!" << std::endl;
		}

	}
}
