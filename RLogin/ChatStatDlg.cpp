// ChatStatDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "RLogin.h"
#include "ChatStatDlg.h"


// CChatStatDlg �_�C�A���O

IMPLEMENT_DYNAMIC(CChatStatDlg, CDialogExt)

CChatStatDlg::CChatStatDlg(CWnd* pParent /*=NULL*/)
	: CDialogExt(CChatStatDlg::IDD, pParent)
{
	m_Counter = 0;
}

CChatStatDlg::~CChatStatDlg()
{
}

void CChatStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogExt::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_TIMEPROG, m_TimeProg);
	DDX_Control(pDX, IDC_TITLE, m_Title);
}


BEGIN_MESSAGE_MAP(CChatStatDlg, CDialogExt)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChatStatDlg ���b�Z�[�W �n���h��

BOOL CChatStatDlg::OnInitDialog()
{
	CDialogExt::OnInitDialog();

	int x, y;
	CRect rect, box;

	GetParent()->GetClientRect(box);
	GetWindowRect(rect);
	x = (box.Width() - rect.Width()) / 2;
	y = (box.Height() - rect.Height()) / 2;
	rect.left   += x;
	rect.right  += x;
	rect.top    += y;
	rect.bottom += y;
	MoveWindow(rect);

	m_TimeProg.SetRange(0, 180);
	SetTimer(1028, 1000, NULL);
	m_Counter = 0;

	return TRUE;
}

void CChatStatDlg::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == 1028 ) {
		m_TimeProg.SetPos(++m_Counter);
		if ( m_Counter >= 180 )
			OnOK();
	}
	CDialogExt::OnTimer(nIDEvent);
}

void CChatStatDlg::OnOK()
{
	CWnd *pWnd = GetParent();
	if ( pWnd != NULL )
		pWnd->PostMessage(WM_COMMAND, ID_CHARSCRIPT_END);
	CDialogExt::OnOK();
}

void CChatStatDlg::SetStaus(LPCTSTR str)
{
	m_Status.SetWindowText(str);
}
