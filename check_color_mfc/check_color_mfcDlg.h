
// check_color_mfcDlg.h : ͷ�ļ�
//

#pragma once


// Ccheck_color_mfcDlg �Ի���
class Ccheck_color_mfcDlg : public CDialogEx
{
// ����
public:
	Ccheck_color_mfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHECK_COLOR_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
