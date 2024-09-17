
// MFC_lab2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_lab2.h"
#include "MFC_lab2Dlg.h"
#include "afxdialogex.h"
#include <cmath>

# define M_PI           3.14159265358979323846

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFClab2Dlg dialog



CMFClab2Dlg::CMFClab2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MFC_LAB2_DIALOG, pParent)
	, m_start(0.31)
	, m_end(1.93)
	, m_result(_T(""))
	, m_n(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFClab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_start);
	DDX_Text(pDX, IDC_EDIT2, m_end);
	DDX_Text(pDX, IDC_EDIT3, m_result);
	DDX_Text(pDX, IDC_EDIT4, m_n);
}

BEGIN_MESSAGE_MAP(CMFClab2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFClab2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFClab2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFClab2Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFClab2Dlg message handlers

BOOL CMFClab2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFClab2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFClab2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFClab2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double f(double x) {
	return M_PI / std::sqrt(1 + std::pow(x, 4));
}

//безпроцентные подсчёты

double leftRectangleIntegral(double a, double b, int n) {
	if (n <= 0) {
		return 0.0;
	}

	double width = (b - a) / n;
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		double x = a + i * width;
		sum += f(x) * width;
	}

	return sum;
}

double rightRectangleIntegral(double a, double b, int n) {
	if (n <= 0) {
		return 0.0;
	}

	double width = (b - a) / n; 
	double sum = 0.0;

	for (int i = 1; i <= n; ++i) {
		double x = a + i * width;
		sum += f(x) * width;
	}

	return sum;
}

double centralRectangleIntegral(double a, double b, int n) {
	if (n <= 0) {
		return 0.0;
	}

	double width = (b - a) / n; 
	double sum = 0.0;

	for (int i = 0; i < n; ++i) {
		double x = a + (i + 0.5) * width;
		sum += f(x) * width;
	}

	return sum;
}


double CMFClab2Dlg::calculateIntegralWithAccuracyLeft(double a, double b, double accuracy) {
	int n = static_cast<int>(m_n);
	double currentIntegral = leftRectangleIntegral(a, b, n);
	double previousIntegral;

	do {
		previousIntegral = currentIntegral;
		n += 2;
		currentIntegral = leftRectangleIntegral(a, b, n);
	} while (std::abs((currentIntegral - previousIntegral) / currentIntegral) > accuracy);

	m_n = n - 2;

	return previousIntegral;
}

double CMFClab2Dlg::calculateIntegralWithAccuracyRight(double a, double b, double accuracy) {
	int n = static_cast<int>(m_n);
	double currentIntegral = rightRectangleIntegral(a, b, n);
	double previousIntegral;

	do {
		previousIntegral = currentIntegral;
		n += 2; 
		currentIntegral = rightRectangleIntegral(a, b, n);

	} while (std::abs((currentIntegral - previousIntegral) / currentIntegral) > accuracy);

	m_n = n-2;

	return previousIntegral;
}

double CMFClab2Dlg::calculateIntegralWithAccuracyCentral(double a, double b, double accuracy) {
	int n = static_cast<int>(m_n);
	double currentIntegral = centralRectangleIntegral(a, b, n);
	double previousIntegral;

	do {
		previousIntegral = currentIntegral;
		n += 1000; // Увеличиваем количество разбиений на фиксированное количество
		currentIntegral = centralRectangleIntegral(a, b, n);

	} while (std::abs((currentIntegral - previousIntegral) / currentIntegral) > accuracy);

	m_n = n - 2;

	return previousIntegral;
}

void CMFClab2Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	double a = static_cast<double>(m_start);
	double b = static_cast<double>(m_end);

	double result = calculateIntegralWithAccuracyLeft(a, b, 0.01);

	m_result.Format(_T("%.8f"), result);

	UpdateData(FALSE);
}


void CMFClab2Dlg::OnBnClickedButton3()
{
	UpdateData(TRUE);

	double a = static_cast<double>(m_start);
	double b = static_cast<double>(m_end);

	double result = calculateIntegralWithAccuracyRight(a, b, 0.01);

	m_result.Format(_T("%.8f"), result);

	UpdateData(FALSE);
}


void CMFClab2Dlg::OnBnClickedButton2()
{
	UpdateData(TRUE);

	double a = static_cast<double>(m_start);
	double b = static_cast<double>(m_end);

	double result = calculateIntegralWithAccuracyCentral(a, b, 0.01);

	m_result.Format(_T("%.8f"), result);

	UpdateData(FALSE);
}
