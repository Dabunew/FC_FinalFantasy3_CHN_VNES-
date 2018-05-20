//
// バージョンダイアログクラス
//
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <string>
using namespace std;

#include "VirtuaNESres.h"
//#include "DebugOut.h"
#include "App.h"
#include "Pathlib.h"

#include "Wnd.h"
#include "NetPlayDlg.h"

#include "NetPlay.h"

DLG_MESSAGE_BEGIN(CNetPlayDlg)
DLG_ON_MESSAGE( WM_INITDIALOG,	OnInitDialog )
DLG_ON_MESSAGE( WM_NETPLAY_ACCEPT, OnNetworkAccept )
DLG_ON_MESSAGE( WM_NETPLAY_CONNECT, OnNetworkConnect )
DLG_ON_MESSAGE( WM_NETPLAY_CLOSE, OnNetworkClose )
DLG_ON_MESSAGE( WM_NETPLAY_ERROR, OnNetworkError )

DLG_COMMAND_BEGIN()
DLG_ON_COMMAND( IDC_NET_CONNECT, OnConnect )
DLG_ON_COMMAND( IDC_NET_SERVER, OnServer )
DLG_ON_COMMAND( IDC_NET_CLIENT, OnClient )
DLG_ON_COMMAND( IDCANCEL, OnCancel )
DLG_COMMAND_END()
DLG_MESSAGE_END()

INT	CNetPlayDlg::DoModal( HWND hWndParent )
{
	m_hWndParent = hWndParent;

	return	::DialogBoxParam( CApp::GetPlugin(), MAKEINTRESOURCE(IDD_NETPLAY),
				hWndParent, g_DlgProc, (LPARAM)this );
}

void	CNetPlayDlg::SetStatusMessage( UINT uID )
{
	CHAR	szTemp[256];
	CApp::LoadString( uID, szTemp, sizeof(szTemp) );
	::SetDlgItemText( m_hWnd, IDC_NET_STATUS, szTemp );
}

DLGMSG	CNetPlayDlg::OnInitDialog( DLGMSGPARAM )
{
//	DEBUGOUT( "CNetPlayDlg::OnInitDialog\n" );

	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), FALSE );
	::SetDlgItemText( m_hWnd, IDC_NET_IP, "127.0.0.1" );
	::SetDlgItemText( m_hWnd, IDC_NET_PORT, "10000" );
	::SetDlgItemText( m_hWnd, IDC_NET_LATENCY, "0" );

	::CheckRadioButton( m_hWnd, IDC_NET_SERVER, IDC_NET_CLIENT, IDC_NET_SERVER );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), IsBTNCHECK(IDC_NET_SERVER)?TRUE:FALSE );

	SetStatusMessage( IDS_NET_NOCONNECT );

	return	TRUE;
}

DLGMSG	CNetPlayDlg::OnNetworkAccept( DLGMSGPARAM )
{
BYTE	databuf;
DWORD	dwStartTime, dwEndTime;
INT	nServerLatency;
INT	nClientLatency;
INT	nLatency;
BOOL	bRet = FALSE;

	// 通信レイテンシの計測
	CHAR	str[256];
	::wsprintf( str, "VirtuaNES version %01d.%01d%01d",
		    (VIRTUANES_VERSION&0xF00)>>8,
		    (VIRTUANES_VERSION&0x0F0)>>4,
		    (VIRTUANES_VERSION&0x00F) );

	dwStartTime = ::timeGetTime();
	for( INT i = 0; i < ::strlen(str); i++ ) {
		if( NetPlay.Send( (unsigned char*)&str[i], sizeof(char) ) ) {
			goto	_accept_error;
		}
		if( NetPlay.RecvTime( (unsigned char*)&databuf, sizeof(databuf), 10*1000 ) < 0 ) {
			goto	_accept_error;
		} else {
			if( databuf != (BYTE)str[i] ) {
				goto	_accept_error;
			}
		}
	}
	dwEndTime = ::timeGetTime()-dwStartTime;

//	DEBUGOUT( "Server: Transfer Bytes: %d byte / Time: %d ms / Latency: %d frames\n", ::strlen(str), dwEndTime, (dwEndTime*60/(::strlen(str)*500))+1 );

	// レイテンシ設定あり？
	nLatency = ::GetDlgItemInt( m_hWnd, IDC_NET_LATENCY, &bRet, FALSE );

	if( nLatency ) {
		nServerLatency = nLatency;
	} else {
		nServerLatency = (dwEndTime*60/(::strlen(str)*500))+1;
	}

	// Send Latency
	if( NetPlay.Send( (unsigned char*)&nServerLatency, sizeof(nServerLatency) ) ) {
		goto	_accept_error;
	}

	// Recv Latency dummy
	if( NetPlay.RecvTime( (unsigned char*)&nClientLatency, sizeof(nClientLatency), 10*1000 ) < 0 ) {
		goto	_accept_error;
	}

	nLatency = nServerLatency;
//	DEBUGOUT( "Server: Network Latency:%d frames\n", nLatency );

	// Sync send
	databuf = 0;
	if( NetPlay.Send( (unsigned char*)&databuf, sizeof(databuf) ) ) {
		goto	_accept_error;
	}

	// Sync recv
	if( NetPlay.RecvTime( (unsigned char*)&databuf, sizeof(databuf), 10*1000 ) < 0 ) {
		goto	_accept_error;
	} else {
		if( databuf != 0 ) {
			goto	_accept_error;
		}
	}

	NetPlay.SetLatency( nLatency );
	NetPlay.SetMsgWnd( m_hWndParent );

	::EndDialog( m_hWnd, IDOK );
	return	TRUE;
_accept_error:
	NetPlay.Disconnect();
	::SetDlgItemText( m_hWnd, IDC_NET_STATUS, CApp::GetErrorString( IDS_ERROR_NETWORKERROR ) );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CONNECT ), TRUE );
	return	TRUE;
}

DLGMSG	CNetPlayDlg::OnNetworkConnect( DLGMSGPARAM )
{
BYTE	databuf;
DWORD	dwStartTime, dwEndTime;
INT	nServerLatency;
INT	nClientLatency;
INT	nLatency;

	// 通信レイテンシの計測
	CHAR	str[256];
	::wsprintf( str, "VirtuaNES version %01d.%01d%01d",
		    (VIRTUANES_VERSION&0xF00)>>8,
		    (VIRTUANES_VERSION&0x0F0)>>4,
		    (VIRTUANES_VERSION&0x00F) );

	dwStartTime = ::timeGetTime();
	for( INT i = 0; i < ::strlen(str); i++ ) {
		if( NetPlay.Send( (unsigned char*)&str[i], sizeof(char) ) ) {
			goto	_connect_error;
		}
		if( NetPlay.RecvTime( (unsigned char*)&databuf, sizeof(databuf), 10*1000 ) < 0 ) {
			goto	_connect_error;
		} else {
			if( databuf != str[i] ) {
				goto	_connect_error;
			}
		}
	}
	dwEndTime = ::timeGetTime()-dwStartTime;

//	DEBUGOUT( "Client: Transfer Bytes: %d byte / Time: %d ms / Latency: %d frames\n", ::strlen(str), dwEndTime, (dwEndTime*60/(::strlen(str)*500))+1 );

	nClientLatency = (dwEndTime*60/(::strlen(str)*500))+1;

	// Send Latency dummy
	if( NetPlay.Send( (unsigned char*)&nClientLatency, sizeof(nClientLatency) ) ) {
		goto	_connect_error;
	}
	// Recv Latency
	if( NetPlay.RecvTime( (unsigned char*)&nServerLatency, sizeof(nServerLatency), 10*1000 ) < 0 ) {
		goto	_connect_error;
	}

	nLatency = nServerLatency;
//	DEBUGOUT( "Client: Network Latency:%d frames\n", nLatency );

	// Sync send
	databuf = 0;
	if( NetPlay.Send( (unsigned char*)&databuf, sizeof(databuf) ) ) {
		goto	_connect_error;
	}

	// Sync recv
	if( NetPlay.RecvTime( (unsigned char*)&databuf, sizeof(databuf), 10*1000 ) < 0 ) {
		goto	_connect_error;
	} else {
		if( databuf != 0 ) {
			goto	_connect_error;
		}
	}

	NetPlay.SetLatency( nLatency );
	NetPlay.SetMsgWnd( m_hWndParent );

	::EndDialog( m_hWnd, IDOK );
	return	TRUE;
_connect_error:
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), IsBTNCHECK(IDC_NET_SERVER)?FALSE:TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_PORT ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_SERVER ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CLIENT ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), IsBTNCHECK(IDC_NET_SERVER)?TRUE:FALSE );

	NetPlay.Disconnect();
	::SetDlgItemText( m_hWnd, IDC_NET_STATUS, CApp::GetErrorString( IDS_ERROR_NETWORKERROR ) );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CONNECT ), TRUE );
	return	TRUE;
}

DLGMSG	CNetPlayDlg::OnNetworkClose( DLGMSGPARAM )
{
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), IsBTNCHECK(IDC_NET_SERVER)?FALSE:TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_PORT ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_SERVER ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CLIENT ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), IsBTNCHECK(IDC_NET_SERVER)?TRUE:FALSE );

	::SetDlgItemText( m_hWnd, IDC_NET_STATUS, CApp::GetErrorString( IDS_ERROR_NETWORKDISCONNECT ) );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CONNECT ), TRUE );
	NetPlay.SetMsgWnd( NULL );
	return	TRUE;
}

DLGMSG	CNetPlayDlg::OnNetworkError( DLGMSGPARAM )
{
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), IsBTNCHECK(IDC_NET_SERVER)?FALSE:TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_PORT ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_SERVER ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CLIENT ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), IsBTNCHECK(IDC_NET_SERVER)?TRUE:FALSE );

	::SetDlgItemText( m_hWnd, IDC_NET_STATUS, CApp::GetErrorString( IDS_ERROR_NETWORKERROR ) );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CONNECT ), TRUE );
	NetPlay.SetMsgWnd( NULL );
	return	TRUE;
}

DLGCMD	CNetPlayDlg::OnServer( DLGCMDPARAM )
{
//	DEBUGOUT( "CNetPlayDlg::OnServer\n" );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), FALSE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), TRUE );
}

DLGCMD	CNetPlayDlg::OnClient( DLGCMDPARAM )
{
//	DEBUGOUT( "CNetPlayDlg::OnClient\n" );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), TRUE );
	::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), FALSE );
}

DLGCMD	CNetPlayDlg::OnConnect( DLGCMDPARAM )
{
//	DEBUGOUT( "CNetPlayDlg::OnConnect\n" );

	CHAR	szIP[256];
	UINT	Port;
	BOOL	bRet;

	::GetDlgItemText( m_hWnd, IDC_NET_IP, szIP, 256 );
	Port = ::GetDlgItemInt( m_hWnd, IDC_NET_PORT, &bRet, FALSE );

	// 危険～
	if( Port < 1024 )
		return;

	if( !bRet ) {
		::SetDlgItemText( m_hWnd, IDC_NET_STATUS, CApp::GetErrorString( IDS_ERROR_NETWORKERROR ) );
		return;
	}

	// エラーとかその他もろもろをこのウインドウで受け取る為
	NetPlay.SetMsgWnd( m_hWnd );

	if( NetPlay.Connect( IsBTNCHECK(IDC_NET_SERVER), szIP, Port ) ) {
		if( IsBTNCHECK(IDC_NET_SERVER) )
			SetStatusMessage( IDS_NET_ACCEPTING );
		else
			SetStatusMessage( IDS_NET_CONNECTING );
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CONNECT ), FALSE );

		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_IP ), FALSE );
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_PORT ), FALSE );
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_SERVER ), FALSE );
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_CLIENT ), FALSE );
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NET_LATENCY ), FALSE );
	} else {
		::SetDlgItemText( m_hWnd, IDC_NET_STATUS, CApp::GetErrorString( IDS_ERROR_NETWORKERROR ) );
//		DEBUGOUT( "CNetPlayDlg::OnConnect error.\n" );
	}
//	::EndDialog( m_hWnd, IDOK );
}

DLGCMD	CNetPlayDlg::OnCancel( DLGCMDPARAM )
{
//	DEBUGOUT( "CNetPlayDlg::OnCancel\n" );

	NetPlay.Disconnect();

	::EndDialog( m_hWnd, IDCANCEL );
}

