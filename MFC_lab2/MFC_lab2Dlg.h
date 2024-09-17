
// MFC_lab2Dlg.h : header file
//

#pragma once


// CMFClab2Dlg dialog
class CMFClab2Dlg : public CDialog
{
// Construction
public:
	CMFClab2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_LAB2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	float m_start;
	float m_end;
	afx_msg void OnBnClickedButton1();
	double calculateIntegralWithAccuracyLeft(double a, double b, double accuracy);
	double calculateIntegralWithAccuracyRight(double a, double b, double accuracy);
	double calculateIntegralWithAccuracyCentral(double a, double b, double accuracy);
	CString m_result;
	int m_n;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
