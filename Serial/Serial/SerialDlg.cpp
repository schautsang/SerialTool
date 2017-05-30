
// SerialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Serial.h"
#include "SerialDlg.h"
#include "afxdialogex.h"
#include "mscomm1.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSerialDlg 对话框



CSerialDlg::CSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIAL_DIALOG, pParent)
	, m_pComManage(NULL)
	, m_editSend(_T(""))
	, m_editReceive(_T(""))
	, m_enHex(FALSE)
	, m_sendNumber(0)
	, m_receiveNumber(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}


CSerialDlg::~CSerialDlg()
{
	if (NULL != m_pComManage)
	{
		delete m_pComManage;

		m_pComManage = NULL;
	}
}


void CSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Control(pDX, IDC_COMBO10, m_ComboBox_ComName);
	DDX_Control(pDX, IDC_COMBO11, m_ComboBox_BaudRate);
	DDX_Control(pDX, IDC_COMBO12, m_ComboBox_ByteSize);
	DDX_Control(pDX, IDC_COMBO13, m_ComboBox_StopBit);
	DDX_Control(pDX, IDC_COMBO14, m_ComboBox_Parity);
	DDX_Text(pDX, IDC_EDIT1, m_editSend);
	DDX_Text(pDX, IDC_EDIT2, m_editReceive);
	DDX_Check(pDX, IDC_CHECK1, m_enHex);
	DDX_Text(pDX, IDC_EDIT3, m_sendNumber);
	DDX_Text(pDX, IDC_EDIT4, m_receiveNumber);
}

BEGIN_MESSAGE_MAP(CSerialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON1, &CSerialDlg::OnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CSerialDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CSerialDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &CSerialDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CSerialDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &CSerialDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CSerialDlg 消息处理程序

BOOL CSerialDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	m_pComManage = new CComManage;
	m_pComManage->Init();

	m_pComManage->AddComNameToComboBox(&m_ComboBox_ComName);
	m_ComboBox_ComName.SetCurSel(0);

	m_pComManage->AddBaudRateToComboBox(&m_ComboBox_BaudRate);
	m_ComboBox_BaudRate.SetCurSel(m_ComboBox_BaudRate.FindStringExact(0, COM_DEF_BAUDRATE));

	m_pComManage->AddByteSizeToComboBox(&m_ComboBox_ByteSize);
	m_ComboBox_ByteSize.SetCurSel(m_ComboBox_ByteSize.FindStringExact(0, COM_DEF_BYTESIZE));

	m_pComManage->AddStopBitToComboBox(&m_ComboBox_StopBit);
	m_ComboBox_StopBit.SetCurSel(m_ComboBox_StopBit.FindStringExact(0, COM_DEF_STOPBIT));

	m_pComManage->AddParityToComboBox(&m_ComboBox_Parity);
	m_ComboBox_Parity.SetCurSel(m_ComboBox_Parity.FindStringExact(0, COM_DEF_PARITY));

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO10)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO11)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO12)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO13)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO14)->EnableWindow(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSerialDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSerialDlg::OnPaint()
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
HCURSOR CSerialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSerialDlg::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString comPort, comBaudRate, comDataWidth, comStopBits, comParity;

	GetDlgItemText(IDC_COMBO10, comPort);
	GetDlgItemText(IDC_COMBO11, comBaudRate);
	GetDlgItemText(IDC_COMBO12, comDataWidth);
	GetDlgItemText(IDC_COMBO13, comStopBits);
	GetDlgItemText(IDC_COMBO14, comParity);

	//MessageBox(comPort + comBaudRate + comDataWidth + comStopBits + comParity);

	if (comPort == _T(""))
	{
		MessageBox(_T("Error: Please select serial!"), _T("Prompt"), MB_ICONERROR);
		return;
	}

	if (m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(FALSE);
	}

	m_mscomm.put_CommPort(comPort2Int(comPort));				// 选择COM
	m_mscomm.put_InBufferSize(1024);		                    // 接收缓冲区  
	m_mscomm.put_OutBufferSize(1024);		                    // 发送缓冲区  
	m_mscomm.put_InputLen(0);									// 设置当前接收区数据长度为0,表示全部读取  
	m_mscomm.put_InputMode(1);									// 以二进制方式读写数据  
	m_mscomm.put_RThreshold(1);									// 接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm  
	//m_mscomm.put_Settings(L"115200,n,8,1");					// 波特率9600无检验位，8个数据位，1个停止位 

	//MessageBox(comBaudRate + "," + comParity2CString(comParity) + "," + comDataWidth + "," + comStopBits);

	m_mscomm.put_Settings(comBaudRate + "," + comParity2CString(comParity) + "," + comDataWidth + "," + comStopBits);

	if (!m_mscomm.get_PortOpen())								// 如果串口没有打开则打开 
	{
		m_mscomm.put_PortOpen(TRUE);							// 打开串口  
		MessageBox(L"Serial Open OK!");

		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO12)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO13)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO14)->EnableWindow(FALSE);
	}
	else
	{
		m_mscomm.put_OutBufferCount(0);
		MessageBox(L"Serial Open Fail!");

		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO12)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO13)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO14)->EnableWindow(TRUE);
	}
}


void CSerialDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	m_mscomm.put_PortOpen(FALSE);          // 关闭串口  
	MessageBox(L"Serial Port Closed!");

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO10)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO11)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO12)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO13)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO14)->EnableWindow(TRUE);
}


void CSerialDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);							   // 读取编辑框内容  

	if (m_enHex)
	{
		CByteArray hexdata;

		m_sendNumber += CString2Hex(m_editSend, hexdata);

		m_mscomm.put_Output(COleVariant(hexdata));  // 发送数据 
	}
	else
	{
		m_sendNumber += m_editSend.GetLength();

		m_mscomm.put_Output(COleVariant(m_editSend));  // 发送数据  
	}

	//m_editSend.Empty();                            // 发送后清空输入框  
	UpdateData(FALSE);		                       // 更新编辑框内容 
}


BEGIN_EVENTSINK_MAP(CSerialDlg, CDialogEx)
	ON_EVENT(CSerialDlg, IDC_MSCOMM1, 1, CSerialDlg::OnOncommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CSerialDlg::OnOncommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码

	VARIANT variant_In;
	COleSafeArray array_In;
	long len, k;
	BYTE rxdata[1024];                                      // 设置 BYTE 数组  
	CString strtemp;

	if (m_mscomm.get_CommEvent() == 2)                      // 值为 2 表示接收缓冲区内有字符  
	{
		variant_In = m_mscomm.get_Input();                  // 读缓冲区消息  
		array_In = variant_In;                              // 变量转换  
		len = array_In.GetOneDimSize();                     // 得到有效的数据长度 

		for (k = 0; k < len; k++)
		{
			array_In.GetElement(&k, rxdata + k);
		}

		UpdateData(TRUE);
        for (k = 0; k<len; k++)                             // 将数组转换为 CString 型变量  
        {
			if (m_enHex)
			{
				strtemp.Format(L"%02X", *(rxdata + k));
			}
			else
			{
				strtemp.Format(L"%C", *(rxdata + k));
			}
            m_editReceive += strtemp;
		}
		m_receiveNumber += len;
    }
	UpdateData(FALSE);                                      // 更新编辑框内容  
}


short CSerialDlg::comPort2Int(CString cString)
{
	return _ttoi(cString.Mid(3));
}


CString CSerialDlg::comParity2CString(CString cString)
{
	return cString.Left(1);
}


void CSerialDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	m_pComManage->AddComNameToComboBox(&m_ComboBox_ComName);
	m_ComboBox_ComName.SetCurSel(0);

	UpdateData(TRUE);
	m_editReceive.Empty();
	m_receiveNumber = 0;
	m_editSend.Empty();
	m_sendNumber = 0;
	UpdateData(FALSE);

}


int CSerialDlg::CString2Hex(CString cString, CByteArray &cByteArray)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = cString.GetLength();

	cByteArray.SetSize(len / 2);

	for (int i = 0; i<len;)
	{
		char lstr, hstr = (char)cString[i];

		if (hstr == ' ')
		{
			i++;
			continue;
		}

		i++;

		if (i >= len)
			break;

		lstr = (char)cString[i];

		hexdata = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);

		if ((hexdata == 16) || (lowhexdata == 16))
		{
			return 0;
		}
		else
		{
			hexdata = hexdata * 16 + lowhexdata;
		}

		i++;

		cByteArray[hexdatalen] = (char)hexdata;

		hexdatalen++;
	}

	cByteArray.SetSize(hexdatalen);

	return hexdatalen;
}


char CSerialDlg::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - '0';
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else
	{	
		MessageBox(_T("Error: Illegal hexadecimal character!"), _T("Prompt"), MB_ICONERROR);

		return 16;
	}
}


void CSerialDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_editSend.Empty();
	m_sendNumber = 0;
	UpdateData(FALSE);
}


void CSerialDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_editReceive.Empty();
	m_receiveNumber = 0;
	UpdateData(FALSE);
}
