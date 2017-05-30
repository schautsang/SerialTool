
// SerialDlg.h : 头文件
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"
#include "BaseComManage.h"
#include "BaseCom.h"
#include "ComManage.h"
#include "Constant.h"
#include "HandleCode.h"

// CSerialDlg 对话框
class CSerialDlg : public CDialogEx
{
// 构造
public:
	CSerialDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CSerialDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_DIALOG };
#endif

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
	CMscomm1 m_mscomm;
	afx_msg void OnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	DECLARE_EVENTSINK_MAP()
	void OnOncommMscomm1();

	CComManage* m_pComManage;
	CComboBox m_ComboBox_ComName;
	CComboBox m_ComboBox_BaudRate;
	CComboBox m_ComboBox_ByteSize;
	CComboBox m_ComboBox_StopBit;
	CComboBox m_ComboBox_Parity;
	short comPort2Int(CString cString);
	CString comParity2CString(CString cString);
	afx_msg void OnBnClickedButton4();
	CString m_editSend;
	CString m_editReceive;
	BOOL m_enHex;
	int CString2Hex(CString cString, CByteArray &cByteArray);
	char ConvertHexChar(char ch);
	UINT m_sendNumber;
	UINT m_receiveNumber;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
