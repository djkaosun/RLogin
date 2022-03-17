// SockOptPage.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "RLogin.h"
#include "RLoginDoc.h"
#include "RLoginView.h"
#include "TextRam.h"
#include "Data.h"
#include "OptDlg.h"
#include "SockOptPage.h"

// CSockOptPage �_�C�A���O

IMPLEMENT_DYNAMIC(CSockOptPage, CTreePage)

#define	CHECKOPTMAX		15
#define	IDC_CHECKFAST	IDC_OPTCHECK1
static const int CheckOptTab[] = {
	TO_RLDELAY,		TO_RLBPLUS,		TO_RLDSECHO,	TO_RLPOFF,		TO_RLKEEPAL, 
	TO_SLEEPTIMER,	TO_RLGROUPCAST,	TO_RLNTBCRECV,	TO_RLNTBCSEND,	TO_RLNOTCLOSE, 
	TO_RLREOPEN,	TO_RLTRSLIMIT,	TO_RLNODELAY,	TO_RLDELAYRV,	TO_RLDELAYCR
};

CSockOptPage::CSockOptPage() : CTreePage(CSockOptPage::IDD)
{
	m_DelayUsecChar = DELAY_CHAR_USEC / 1000.0;
	m_DelayMsecLine = DELAY_LINE_MSEC;
	m_DelayMsecRecv = DELAY_RECV_MSEC;
	m_DelayMsecCrLf = 0;
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = FALSE;
	m_SelIPver = 0;
	m_SleepTime = 10;
	m_TransmitLimit = 1000;
	m_UrlOpt = _T("#TRSOPT");
}

CSockOptPage::~CSockOptPage()
{
}

void CSockOptPage::DoDataExchange(CDataExchange* pDX)
{
	CTreePage::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_DELAYCHAR, m_DelayUsecChar);
	DDX_Text(pDX, IDC_DELAYLINE, m_DelayMsecLine);
	DDX_Text(pDX, IDC_DELAYRECV, m_DelayMsecRecv);
	DDX_Text(pDX, IDC_DELAYCRLF, m_DelayMsecCrLf);
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		DDX_Check(pDX, IDC_CHECKFAST + n, m_Check[n]);
	DDX_Radio(pDX, IDC_RADIO1, m_SelIPver);
	DDX_Text(pDX, IDC_SLEEPTIME, m_SleepTime);
	DDX_Text(pDX, IDC_GROUPCAST, m_GroupCast);
	DDX_Text(pDX, IDC_TRANSMITLIMIT, m_TransmitLimit);
}


BEGIN_MESSAGE_MAP(CSockOptPage, CTreePage)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECKFAST, IDC_CHECKFAST + CHECKOPTMAX - 1, OnUpdateCheck)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO3, OnUpdateCheck)
	ON_EN_CHANGE(IDC_DELAYCHAR, OnUpdateEdit)
	ON_EN_CHANGE(IDC_DELAYLINE, OnUpdateEdit)
	ON_EN_CHANGE(IDC_DELAYRECV, OnUpdateEdit)
	ON_EN_CHANGE(IDC_DELAYCRLF, OnUpdateEdit)
	ON_EN_CHANGE(IDC_SLEEPTIME, OnUpdateEdit)
	ON_EN_CHANGE(IDC_GROUPCAST, OnUpdateEdit)
	ON_EN_CHANGE(IDC_TRANSMITLIMIT, OnUpdateEdit)
END_MESSAGE_MAP()


// CSockOptPage ���b�Z�[�W �n���h���[

void CSockOptPage::DoInit()
{
	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		m_Check[n] = (m_pSheet->m_pTextRam->IsOptEnable(CheckOptTab[n]) ? TRUE : FALSE);

	m_DelayUsecChar = m_pSheet->m_pTextRam->m_DelayUSecChar / 1000.0;
	m_DelayMsecLine = m_pSheet->m_pTextRam->m_DelayMSecLine;
	m_DelayMsecRecv = m_pSheet->m_pTextRam->m_DelayMSecRecv;
	m_DelayMsecCrLf = m_pSheet->m_pTextRam->m_DelayMSecCrLf;
	m_SelIPver      = m_pSheet->m_pParamTab->m_SelIPver;
	m_SleepTime     = m_pSheet->m_pTextRam->m_SleepMax / 6;
	m_GroupCast     = m_pSheet->m_pTextRam->m_GroupCast;
	m_TransmitLimit = m_pSheet->m_pParamTab->m_TransmitLimit;

	UpdateData(FALSE);
}
BOOL CSockOptPage::OnInitDialog()
{
	ASSERT(m_pSheet != NULL && m_pSheet->m_pTextRam != NULL && m_pSheet->m_pParamTab != NULL);

	CTreePage::OnInitDialog();

	DoInit();

	return TRUE;
}
BOOL CSockOptPage::OnApply()
{
	ASSERT(m_pSheet != NULL && m_pSheet->m_pTextRam != NULL && m_pSheet->m_pParamTab != NULL);

	UpdateData(TRUE);

	if ( m_SleepTime <= 0 )
		m_SleepTime = 1;

	for ( int n = 0 ; n < CHECKOPTMAX ; n++ )
		m_pSheet->m_pTextRam->SetOption(CheckOptTab[n], m_Check[n]);

	m_pSheet->m_pTextRam->m_DelayUSecChar = (int)(m_DelayUsecChar * 1000.0);
	m_pSheet->m_pTextRam->m_DelayMSecLine = m_DelayMsecLine;
	m_pSheet->m_pTextRam->m_DelayMSecRecv = m_DelayMsecRecv;
	m_pSheet->m_pTextRam->m_DelayMSecCrLf = m_DelayMsecCrLf;
	m_pSheet->m_pParamTab->m_SelIPver   = m_SelIPver;
	m_pSheet->m_pTextRam->m_SleepMax    = m_SleepTime * 6;
	m_pSheet->m_pTextRam->m_GroupCast   = m_GroupCast;
	m_pSheet->m_pParamTab->m_TransmitLimit = m_TransmitLimit;

	return TRUE;
}
void CSockOptPage::OnReset()
{
	ASSERT(m_pSheet != NULL && m_pSheet->m_pTextRam != NULL && m_pSheet->m_pParamTab != NULL);

	DoInit();
	SetModified(FALSE);
}

void CSockOptPage::OnUpdateEdit() 
{
	SetModified(TRUE);
	m_pSheet->m_ModFlag |= (UMOD_TEXTRAM | UMOD_PARAMTAB);
}
void CSockOptPage::OnUpdateCheck(UINT nID) 
{
	int n = nID - IDC_CHECKFAST;

	SetModified(TRUE);
	m_pSheet->m_ModFlag |= (UMOD_TEXTRAM | UMOD_PARAMTAB);

	if ( n >= 0 && n < CHECKOPTMAX && CheckOptTab[n] < 1000 )
		m_pSheet->m_ModFlag |= UMOD_ANSIOPT;
}
