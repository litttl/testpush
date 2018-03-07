
// check_color_mfcDlg.h : 头文件
//

#pragma once


// Ccheck_color_mfcDlg 对话框
class Ccheck_color_mfcDlg : public CDialogEx
{
// 构造
public:
	Ccheck_color_mfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHECK_COLOR_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton2();
};
