// SyncSock.h: CSyncSock �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCSOCK_H__929658C6_9B4A_4686_B274_6CE4582CA208__INCLUDED_)
#define AFX_SYNCSOCK_H__929658C6_9B4A_4686_B274_6CE4582CA208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include "ProgDlg.h"
#include "IConv.h"

#define	THCMD_START				0
#define	THCMD_ENDOF				1
#define	THCMD_DLGOPEN			2
#define	THCMD_DLGCLOSE			3
#define	THCMD_DLGMESSAGE		4
#define	THCMD_DLGRANGE			5
#define	THCMD_DLGPOS			6
#define	THCMD_SENDBUF			7
#define	THCMD_CHECKPATH			8
#define	THCMD_YESNO				9
#define	THCMD_XONXOFF			10
#define	THCMD_SENDSTR			11
#define	THCMD_SENDSCRIPT		12
#define	THCMD_SENDSYNC			13
#define	TGCMD_MESSAGE			14
#define	TGCMD_NOWAITMESSAGE		15
#define	THCMD_ECHOBUFFER		16

#define	CHKFILENAME_SAVE		000
#define	CHKFILENAME_OPEN		001
#define	CHKFILENAME_MULTI		002

extern const unsigned short crc16tab[];
extern const unsigned long  crc32tab[];

class CSyncSock : public CObject  
{
public:
	CWnd *m_pWnd;
	class CRLoginDoc *m_pDoc;
	CWnd *m_pView;
	LPCTSTR m_ProtoName;

	BOOL m_ThreadFlag;
	BOOL m_DoAbortFlag;
	int m_ThreadMode;
	CEvent *m_pThreadEvent;

	CBuffer m_RecvBuf;
	CBuffer m_SendBuf, m_EchoBuf, m_SwapBuf;
	CSemaphore m_SendSema;
	BOOL m_EchoPostReq;
	BOOL m_bInitDone;

	class CProgDlg m_ProgDlg;
	BOOL m_ResvDoit;
	BOOL m_MultiFile;
	CStringList m_ResvPath;
	CString m_PathName;
	CStringA m_FileName;
	CStringA m_Message;
	DWORD m_Param;
	LONGLONG m_Size;
	LONGLONG m_RemSize;
	CEvent *m_pParamEvent;
	clock_t m_LastUpdate;
	CBuffer m_LogBuffer;

	int m_ExtFileDlgMode;

#ifdef	USE_DEBUGLOG
	void DebugMsg(LPCSTR fmt, ...);
	void DebugDump(LPBYTE buf, int len);
#else
	#define	DebugMsg(...)
	#define DebugDump(...)
#endif

	void Bufferd_Send(int c);
	void Bufferd_SendBuf(char *buf, int len);
	void Bufferd_Flush();
	void Bufferd_Clear();
	void Bufferd_Sync();
	int Bufferd_Receive(int sec, int msec = 0);
	BOOL Bufferd_ReceiveBuf(char *buf, int len, int sec, int msec = 0);
	void Bufferd_ReceiveBack(char *buf, int len);
	int Bufferd_ReceiveSize();
	void SetXonXoff(int sw);

	BOOL CheckFileName(int mode, LPCSTR file);
	int YesOrNo(LPCSTR msg);
	int AbortCheck();
	void SendEcho(int ch);
	void SendEchoBuffer(char *buf, int len);
	void SendString(LPCWSTR str);
	void SendScript(LPCWSTR str);
	void Message(LPCSTR msg);
	void NoWaitMessage(LPCSTR msg);

	BOOL m_IsAscii;
	CString m_HostCode;
	CIConv m_IConv;
	CBuffer m_InBuf;
	CBuffer m_OutBuf;
	BOOL m_bUseWrite;

	inline void SetFileType(BOOL ascii) { m_IsAscii = ascii; }
	FILE *FileOpen(LPCTSTR filename, LPCSTR mode, BOOL ascii);
	void FileClose(FILE *fp);
	int ReadCharToHost(FILE *fp);
	int ReadFileToHost(char *buf, int len, FILE *fp);
	int WriteFileFromHost(char *buf, int len, FILE *fp);

	void UpDownOpen(LPCSTR msg);
	void UpDownClose();
	void UpDownMessage(LPCSTR msg);
	void UpDownInit(LONGLONG size, LONGLONG rems = 0L);
	void UpDownStat(LONGLONG size);

	void ThreadCommand(int cmd);
	void DoAbort();
	void StatusMsg(int ids);

	virtual void DoProc(int cmd);
	virtual void OnProc(int cmd);

	CSyncSock(class CRLoginDoc *pDoc, CWnd *pWnd);
	virtual ~CSyncSock();
};

#endif // !defined(AFX_SYNCSOCK_H__929658C6_9B4A_4686_B274_6CE4582CA208__INCLUDED_)
