
// SerialDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Serial.h"
#include "SerialDlg.h"
#include "afxdialogex.h"
#include "mscomm1.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSerialDlg �Ի���



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


// CSerialDlg ��Ϣ�������

BOOL CSerialDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialDlg::OnPaint()
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
HCURSOR CSerialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSerialDlg::OnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

	m_mscomm.put_CommPort(comPort2Int(comPort));				// ѡ��COM
	m_mscomm.put_InBufferSize(1024);		                    // ���ջ�����  
	m_mscomm.put_OutBufferSize(1024);		                    // ���ͻ�����  
	m_mscomm.put_InputLen(0);									// ���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ  
	m_mscomm.put_InputMode(1);									// �Զ����Ʒ�ʽ��д����  
	m_mscomm.put_RThreshold(1);									// ���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm  
	//m_mscomm.put_Settings(L"115200,n,8,1");					// ������9600�޼���λ��8������λ��1��ֹͣλ 

	//MessageBox(comBaudRate + "," + comParity2CString(comParity) + "," + comDataWidth + "," + comStopBits);

	m_mscomm.put_Settings(comBaudRate + "," + comParity2CString(comParity) + "," + comDataWidth + "," + comStopBits);

	if (!m_mscomm.get_PortOpen())								// �������û�д���� 
	{
		m_mscomm.put_PortOpen(TRUE);							// �򿪴���  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_mscomm.put_PortOpen(FALSE);          // �رմ���  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);							   // ��ȡ�༭������  

	if (m_enHex)
	{
		CByteArray hexdata;

		m_sendNumber += CString2Hex(m_editSend, hexdata);

		m_mscomm.put_Output(COleVariant(hexdata));  // �������� 
	}
	else
	{
		m_sendNumber += m_editSend.GetLength();

		m_mscomm.put_Output(COleVariant(m_editSend));  // ��������  
	}

	//m_editSend.Empty();                            // ���ͺ���������  
	UpdateData(FALSE);		                       // ���±༭������ 
}


BEGIN_EVENTSINK_MAP(CSerialDlg, CDialogEx)
	ON_EVENT(CSerialDlg, IDC_MSCOMM1, 1, CSerialDlg::OnOncommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CSerialDlg::OnOncommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������

	VARIANT variant_In;
	COleSafeArray array_In;
	long len, k;
	BYTE rxdata[1024];                                      // ���� BYTE ����  
	CString strtemp;

	if (m_mscomm.get_CommEvent() == 2)                      // ֵΪ 2 ��ʾ���ջ����������ַ�  
	{
		variant_In = m_mscomm.get_Input();                  // ����������Ϣ  
		array_In = variant_In;                              // ����ת��  
		len = array_In.GetOneDimSize();                     // �õ���Ч�����ݳ��� 

		for (k = 0; k < len; k++)
		{
			array_In.GetElement(&k, rxdata + k);
		}

		UpdateData(TRUE);
        for (k = 0; k<len; k++)                             // ������ת��Ϊ CString �ͱ���  
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
	UpdateData(FALSE);                                      // ���±༭������  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_editSend.Empty();
	m_sendNumber = 0;
	UpdateData(FALSE);
}


void CSerialDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_editReceive.Empty();
	m_receiveNumber = 0;
	UpdateData(FALSE);
}
