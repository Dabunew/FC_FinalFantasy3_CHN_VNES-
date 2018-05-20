//
// ネットプレイクラス
//
#ifndef	__CNETPLAY_INCLUDED__
#define	__CNETPLAY_INCLUDED__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <winsock.h>

#include <string>
using namespace std;

#define	WM_NETPLAY		(WM_APP+100)

#define	WM_NETPLAY_ACCEPT	(WM_APP+110)
#define	WM_NETPLAY_CONNECT	(WM_APP+111)
#define	WM_NETPLAY_CLOSE	(WM_APP+112)
#define	WM_NETPLAY_ERROR	(WM_APP+113)

class	CNetPlay
{
public:
	CNetPlay();
	~CNetPlay();

	// 初期化/開放
	BOOL	Initialize( HWND hWnd );
	void	Release();

	// ネットプレイ可能？
	BOOL	IsNetPlay() { return m_hWnd?TRUE:FALSE; }
	// 接続中？
	BOOL	IsConnect() { return m_hWnd?m_bConnect:FALSE; }
	// 接続中？
	BOOL	IsServer() { return m_bServer; }

	// 通信レイテンシ
	void	SetLatency( INT nLatency ) { m_nLatency = nLatency; }
	INT	GetLatency() { return m_nLatency; }

	// 非同期処理メッセージ返送ウインドウの設定
	void	SetMsgWnd( HWND hWnd ) { m_hWndMsg = hWnd; }

	// 接続と切断
	BOOL	Connect( BOOL bServer, const char* IP, unsigned short Port );
	void	Disconnect();

	// データ送信 0:受信データ待ち 1以上:受信データあり 0未満:接続切れやエラー
	INT	Send( unsigned char* pBuf, int size );
	// データ受信
	// 0:受信データ待ち 1以上:受信データあり 0未満:接続切れやエラー
	// タイムアウト無し
	INT	Recv( unsigned char* pBuf, int size );
	// タイムアウト有り
	INT	RecvTime( unsigned char* pBuf, int size, unsigned long timeout );

	// Windowsメッセージプロシージャ
	HRESULT	WndProc( HWND hWnd, WPARAM wParam, LPARAM lParam );
protected:
	// メンバ変数
	HWND	m_hWnd;
	HWND	m_hWndMsg;

	BOOL	m_bServer;
	BOOL	m_bConnect;	// 接続中？
	INT	m_nLatency;

	// WINSOCK
	WSADATA	m_WSAdata;
	SOCKET	m_SocketConnect;
	SOCKET	m_SocketData;
private:
};

extern	CNetPlay	NetPlay;

#endif	// !__CNETPLAY_INCLUDED__
