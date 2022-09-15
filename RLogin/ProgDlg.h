#pragma once

#include "DialogExt.h"

/////////////////////////////////////////////////////////////////////////////
// CProgDlg �_�C�A���O

class CProgDlg : public CDialogExt
{
	DECLARE_DYNAMIC(CProgDlg)

// �R���X�g���N�V����
public:
	CProgDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProgDlg)
	enum { IDD = IDD_PROGDLG };

public:
	CProgressCtrl	m_FileSize;
	CString	m_EndTime;
	CString	m_TotalSize;
	CString	m_TransRate;
	CString	m_FileName;
	CString m_Message;

public:
	int m_Div;
	LONGLONG m_LastSize;
	LONGLONG m_ResumeSize;
	LONGLONG m_UpdatePos, m_ActivePos;
	clock_t m_StartClock, m_UpdateClock;
	BOOL m_AbortFlag;
	class CExtSocket *m_pSock;

	void SetRange(LONGLONG max, LONGLONG rem);
	void UpdatePos(LONGLONG pos);
	void SetPos(LONGLONG pos);
	void SetFileName(LPCTSTR file);
	void SetMessage(LPCTSTR msg);

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnInitDialog();
	virtual void OnCancel();

// �C���v�������e�[�V����
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
