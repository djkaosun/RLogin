#pragma once

#include "afxwin.h"
#include "DialogExt.h"

// CAnyPastDlg �_�C�A���O

class CAnyPastDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CAnyPastDlg)

public:
	CAnyPastDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CAnyPastDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ANYPASTDIG };

public:
	CStatic m_IconBox;
	CEdit m_EditWnd;
	int m_CtrlCode[3];
	BOOL m_bUpdateText;
	BOOL m_bDelayPast;
	BOOL m_NoCheck;
	BOOL m_bCtrlView;
	CString m_ConvStr;

	CString m_EditText;
	BOOL m_bUpdateEnable;
	class CMainFrame *m_pMain;
	int m_DocSeqNumber;
	BOOL m_bDiffViewEnable;

public:
	void CtrlCount();
	LPCTSTR CtrlStr(LPCTSTR str, BOOL bCtrl);
	BOOL SendBracketedPaste(LPCTSTR str);
	BOOL UpdateTextData(BOOL bOk);
	void SetEditText(LPCTSTR str, int DocSeqNumber);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateEdit();
	afx_msg void OnCtrlConv(UINT nID);
	afx_msg void OnShellesc();
	afx_msg void OnOneLine();
	afx_msg void OnCtrlView();
	afx_msg void OnClose();
};
