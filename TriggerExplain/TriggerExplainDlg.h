
// TriggerExplainDlg.h : ͷ�ļ�
//

#pragma once


// CTriggerExplainDlg �Ի���
class CTriggerExplainDlg : public CDialogEx
{
// ����
public:
	CTriggerExplainDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRIGGEREXPLAIN_DIALOG };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int GetCStringHex(CString string,int stringlen,unsigned char *data);
	int ExplainTriggerInfo(CString data,CString &info);
	afx_msg void OnBnClickedOk();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnChangeCipherEdit();
};
