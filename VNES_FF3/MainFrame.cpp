//
// Main Window Class
//
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include <imm.h>
#include <mbstring.h>
#include <string>
using namespace std;

#include "VirtuaNESres.h"
#include "App.h"
#include "Pathlib.h"

#include "Wnd.h"
#include "WndHook.h"
#include "MainFrame.h"
#include "Config.h"

#include "NetPlay.h"

#include "AboutDlg.h"
#include "EmulatorDlg.h"
#include "GraphicsDlg.h"
#include "SoundDlg.h"
#include "ControllerDlg.h"
#include "ShortcutDlg.h"
#include "MovieDlg.h"
#include "GameOptionDlg.h"
#include "NetPlayDlg.h"
#include "MovieInfoDlg.h"

#include "DirectDraw.h"
#include "DirectSound.h"
#include "DirectInput.h"

#include "nes.h"
#include "rom.h"
#include "pad.h"

// Message Map
WND_MESSAGE_BEGIN(CMainFrame)
// Message
WND_ON_MESSAGE( WM_CREATE,	OnCreate )
WND_ON_MESSAGE( WM_CLOSE,	OnClose )
WND_ON_MESSAGE( WM_DESTROY,	OnDestroy )
WND_ON_MESSAGE( WM_GETMINMAXINFO, OnGetMinMaxInfo )
WND_ON_MESSAGE( WM_ACTIVATE,	OnActivate )
WND_ON_MESSAGE( WM_ACTIVATEAPP,	OnActivateApp )
WND_ON_MESSAGE( WM_VNS_SHORTCUTENABLE, OnShortCutEnable )
WND_ON_MESSAGE( WM_ENABLE,	OnEnable )
WND_ON_MESSAGE( WM_ENTERMENULOOP, OnEnterMenuLoop )
WND_ON_MESSAGE( WM_EXITMENULOOP, OnExitMenuLoop )
WND_ON_MESSAGE( WM_SETFOCUS,	OnSetFocus )
WND_ON_MESSAGE( WM_KILLFOCUS,	OnKillFocus )
WND_ON_MESSAGE( WM_INITMENU,	OnInitMenu )
WND_ON_MESSAGE( WM_INITMENUPOPUP, OnInitMenuPopup )
WND_ON_MESSAGE( WM_PAINT,	OnPaint )
WND_ON_MESSAGE( WM_DISPLAYCHANGE, OnDisplayChange )
WND_ON_MESSAGE( WM_PALETTECHANGED, OnPaletteChanged )
WND_ON_MESSAGE( WM_QUERYNEWPALETTE, OnQueryNewPalette )
WND_ON_MESSAGE( WM_MENUCHAR,	OnMenuChar )
WND_ON_MESSAGE( WM_KEYDOWN,	OnKeyDown )
WND_ON_MESSAGE( WM_SIZE,	OnSize )
WND_ON_MESSAGE( WM_SYSCOMMAND,	OnSysCommand )
WND_ON_MESSAGE( WM_EXITSIZEMOVE, OnExitSizeMove )

WND_ON_MESSAGE( WM_SETCURSOR,	OnSetCursor )
WND_ON_MESSAGE( WM_TIMER,	OnTimer )

WND_ON_MESSAGE( WM_COPYDATA, OnCopyData )

WND_ON_MESSAGE( WM_VNS_ERRORMSG, OnErrorMessage )

WND_ON_MESSAGE( WM_VNS_COMMANDLINE, OnCommandLine )

WND_ON_MESSAGE( WM_NETPLAY, OnNetPlay )
WND_ON_MESSAGE( WM_NETPLAY_CLOSE, OnNetPlayClose )
WND_ON_MESSAGE( WM_NETPLAY_ERROR, OnNetPlayError )

// Command
WND_COMMAND_BEGIN()
WND_ON_COMMAND( ID_HTMLHELP, OnHelp )
WND_ON_COMMAND( ID_ABOUT, OnAbout )

WND_ON_COMMAND( ID_NETPLAY_CONNECT, OnNetPlayConnect )
WND_ON_COMMAND( ID_NETPLAY_DISCONNECT, OnNetPlayDisconnect )

WND_ON_COMMAND( ID_CFG_EMULATOR, OnEmulatorCfg )
WND_ON_COMMAND( ID_CFG_GRAPHICS, OnGraphicsCfg )
WND_ON_COMMAND( ID_CFG_SOUND, OnSoundCfg )
WND_ON_COMMAND( ID_CFG_CONTROLLER, OnControllerCfg )
WND_ON_COMMAND( ID_CFG_SHORTCUT, OnShortcutCfg )
WND_ON_COMMAND( ID_CFG_MOVIE, OnMovieCfg )
WND_ON_COMMAND( ID_CFG_GAMEOPTION, OnGameOptionCfg )

WND_ON_COMMAND( ID_SEARCH, OnSearch )
WND_ON_COMMAND( ID_CHEAT, OnCheat )
WND_ON_COMMAND_RANGE( ID_CHEAT_ENABLE, ID_CHEAT_DISABLE, OnCheatCommand )
WND_ON_COMMAND( ID_GENIE, OnGenie )

WND_ON_COMMAND( ID_FULLSCREEN, OnFullScreen )
WND_ON_COMMAND( ID_ONTOP, OnOnTop )
WND_ON_COMMAND_RANGE( ID_ZOOMx1, ID_ZOOMx4, OnZoom )
WND_ON_COMMAND( ID_HWRESET, OnEmuCommand )
WND_ON_COMMAND( ID_SWRESET, OnEmuCommand )
WND_ON_COMMAND( ID_PAUSE, OnEmuCommand )
WND_ON_COMMAND( ID_THROTTLE, OnEmuCommand )
WND_ON_COMMAND( ID_STATE_UP, OnEmuCommand )
WND_ON_COMMAND( ID_STATE_DOWN, OnEmuCommand )
WND_ON_COMMAND( ID_FPSDISP, OnEmuCommand )
WND_ON_COMMAND( ID_TVASPECT, OnEmuCommand )
WND_ON_COMMAND( ID_TVFRAME, OnEmuCommand )
WND_ON_COMMAND( ID_SCANLINE, OnEmuCommand )
WND_ON_COMMAND( ID_ALLLINE, OnEmuCommand )
WND_ON_COMMAND( ID_ALLSPRITE, OnEmuCommand )
WND_ON_COMMAND( ID_SYNCDRAW, OnEmuCommand )
WND_ON_COMMAND( ID_FITSCREEN, OnEmuCommand )
WND_ON_COMMAND( ID_SNAPSHOT, OnEmuCommand )

WND_ON_COMMAND( ID_LEFTCLIP, OnEmuCommand )
WND_ON_COMMAND( ID_ONEFRAME, OnEmuCommand )

WND_ON_COMMAND( ID_STATE_LOAD, OnStateCommand )
WND_ON_COMMAND( ID_STATE_SAVE, OnStateCommand )

WND_ON_COMMAND( ID_MOVIE_PLAY, OnMovieCommand )
WND_ON_COMMAND( ID_MOVIE_REC, OnMovieCommand )
WND_ON_COMMAND( ID_MOVIE_REC_APPEND, OnMovieCommand )
WND_ON_COMMAND( ID_MOVIE_STOP, OnMovieCommand )
WND_ON_COMMAND( ID_MOVIE_INFO, OnMovieInfo )

WND_ON_COMMAND( ID_FRAMESKIP_AUTO, OnEmuCommand )
WND_ON_COMMAND( ID_FRAMESKIP_UP, OnEmuCommand )
WND_ON_COMMAND( ID_FRAMESKIP_DOWN, OnEmuCommand )


//
WND_ON_COMMAND_RANGE( ID_STATE_SLOT0, ID_STATE_SLOT9, OnEmuCommand )
WND_ON_COMMAND_RANGE( ID_MUTE_0, ID_MUTE_F, OnEmuCommand )
WND_COMMAND_END()
WND_MESSAGE_END()

BOOL	CMainFrame::Create( HWND hWndParent )
{

	// NES Object
	Nes = NULL;

	// Member変数
	m_hMenu = NULL;

	WNDCLASSEX	wcl;
	ZeroMemory( &wcl, sizeof(wcl) );
	wcl.cbSize		= sizeof(wcl);
	wcl.lpszClassName	= "VirtuaNESwndclass";
	wcl.lpfnWndProc		= g_WndProc;
	wcl.style		= CS_DBLCLKS;
	wcl.cbClsExtra		= wcl.cbWndExtra = 0;
	wcl.hInstance		= CApp::GetInstance();
	wcl.lpszMenuName	= NULL;
	wcl.hIcon		=
	wcl.hIconSm		= ::LoadIcon( CApp::GetInstance(), MAKEINTRESOURCE(IDI_ICON) );
	wcl.hCursor		= ::LoadCursor( NULL, IDC_ARROW );
	wcl.hbrBackground	= 0;

	if( !RegisterClassEx( &wcl ) ) {
		return	FALSE;
	}

	HWND hWnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			VIRTUANES_WNDCLASS,
			CApp::GetErrorString(10),
			WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			hWndParent,
			NULL,
			CApp::GetInstance(),
			(LPVOID)this		// This を埋め込む為
		);
	if( !hWnd ) {
		return	FALSE;
	}

	// Main Windowとして登録
	CApp::SetHWnd( hWnd );

	// State Slot
	m_nStateSlot = 0;

	return	TRUE;
}

void	CMainFrame::Destroy()
{
	if( m_hWnd && IsWindow(m_hWnd) ) {
		::DestroyWindow( m_hWnd );
		m_hWnd = NULL;
	}
}

BOOL	CMainFrame::PreTranslateMessage( MSG* pMsg )
{
	if( pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST ) {
//		return	TRUE;
	}
	return	FALSE;
}

WNDMSG	CMainFrame::OnCreate( WNDMSGPARAM )
{
	DirectDraw.SetSystemMemory( Config.graphics.bSystemMemory );
	DirectDraw.SetUseHEL      ( Config.graphics.bUseHEL );

	if( !DirectDraw.InitialDDraw( m_hWnd ) ) {
		hResult = -1L;
		return	TRUE;
	}
	if( !DirectSound.InitialDSound( m_hWnd ) ) {
		hResult = -1L;
		return	TRUE;
	}
	if( !DirectInput.InitialDInput( m_hWnd, CApp::GetInstance() ) ) {
		hResult = -1L;
		return	TRUE;
	}
	// DirectDraw Optionの設定
	DirectDraw.SetFlipMode     ( Config.graphics.bSyncDraw );
	DirectDraw.SetAspectMode   ( Config.graphics.bAspect );
	DirectDraw.SetAllLineMode  ( Config.graphics.bAllLine );
	DirectDraw.SetMaxZoom      ( Config.graphics.bFitZoom );
	DirectDraw.SetTVFrameMode  ( Config.graphics.bTVFrame );
	DirectDraw.SetScanlineMode ( Config.graphics.bScanline );
	DirectDraw.SetScanlineColor( Config.graphics.nScanlineColor );

	DirectDraw.SetWindowVSyncMode( Config.graphics.bWindowVSync );

	DirectDraw.SetDoubleSize  ( Config.graphics.bDoubleSize );

	// DirectDraw Srufaceの構築
	if( !DirectDraw.InitialSurface( FALSE ) ) {
		hResult = -1L;
		return	TRUE;
	}

	// Palettee Fileのロード
	if( Config.graphics.bPaletteFile ) {
		DirectDraw.SetPaletteFile( Config.graphics.szPaletteFile );
	}

	// DirectSound Optionの設定
	DirectSound.SetSamplingRate( Config.sound.nRate, Config.sound.nBits );
	DirectSound.SetBufferSize( Config.sound.nBufferSize );

	// DirectSound Bufferの構築
	if( !DirectSound.InitialBuffer() ) {
		hResult = -1L;
		return	TRUE;
	}

	// Palette Tableの計算
	DirectDraw.CalcPaletteTable();

	// Net Play
	NetPlay.Initialize( m_hWnd );

	// MenuのLoad
	m_hMenu = CApp::LoadMenu( IDR_MENU );
	CApp::SetMenu( m_hMenu );
	::SetMenu( m_hWnd, m_hMenu );
	m_bMenu = TRUE;		// Menu表示中Flag

	// MenuにAccelerator Key名の追加
	OnRebuildMenu();

	// Window位置の設定
	RECT	rc = Config.general.rcWindowPos;
	if( !((rc.right-rc.left) <= 0 || (rc.bottom-rc.top) <= 0) ) {
		if( (m_bZoomed = Config.general.bWindowZoom) ) {
			CApp::SetCmdShow( SW_SHOWMAXIMIZED );
		}
		// 保存されていたWindow Sizeにする
		m_WindowRect = rc;
		::SetWindowPos( m_hWnd, HWND_NOTOPMOST, rc.left, rc.top,
				rc.right-rc.left, rc.bottom-rc.top, 0 );
	} else {
		m_bZoomed = FALSE;
		// Default Sizeを調整する
		OnSetWindowSize();
	}

	// Window Styleの保存
	m_StyleBackup   = ::GetWindowLong( m_hWnd, GWL_STYLE );
	m_ExStyleBackup = ::GetWindowLong( m_hWnd, GWL_EXSTYLE );

	// IME使用禁止:D
	::ImmAssociateContext( m_hWnd, NULL );

	OnEmulationStart(NULL, FALSE);
	Emu.Event( CEmuThread::EV_THROTTLE );

	//是否放在最顶^_^:P
	m_OnTop = Config.general.bOnTop;
	if(m_OnTop == 1)
		SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	else
	{
		CheckMenuItem(GetMenu(m_hWnd), 60000, MF_BYCOMMAND|MF_UNCHECKED);
	}

	// Flag類
	m_bActivate = TRUE;
	m_bActivateApp = TRUE;
	m_bForcus = TRUE;
	m_bCursor = TRUE;
	m_bKeyEnable = TRUE;
	m_bKeyChecking = FALSE;
	m_LastMovedTime = 0;

	m_uTimerID = ::SetTimer( m_hWnd, 0x0001, 1000, NULL );
	m_uKeyTimerID = ::SetTimer( m_hWnd, 0x0100, 30, NULL );	// 30ms

	::ZeroMemory( m_KeyBuf, sizeof(m_KeyBuf) );
	::ZeroMemory( m_KeyCnt, sizeof(m_KeyCnt) );

	return	FALSE;
}

WNDMSG	CMainFrame::OnClose( WNDMSGPARAM )
{
	// Net Play
	NetPlay.Release();

	// Emulation終了
	Emu.Stop();
	DELETEPTR( Nes );

	// Timerの終了
	::KillTimer( m_hWnd, m_uTimerID );
	::KillTimer( m_hWnd, m_uKeyTimerID );
	m_uTimerID = 0;
	m_uKeyTimerID = 0;

	// Window破棄
	::DestroyWindow( m_hWnd );

	// Search Dialog終了
	m_SearchDlg.Destroy();


	// Window位置の保存
	Config.general.bWindowZoom = m_bZoomed;
	Config.general.rcWindowPos = m_WindowRect;

	Config.general.bOnTop = m_OnTop;

	::DragAcceptFiles( m_hWnd, FALSE );

	return	FALSE;
}

WNDMSG	CMainFrame::OnDestroy( WNDMSGPARAM )
{
	::PostQuitMessage( 0 );
	return	FALSE;
}

WNDMSG	CMainFrame::OnGetMinMaxInfo( WNDMSGPARAM )
{
	MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;

	// 最小Sizeだけ
	lpMMI->ptMinTrackSize.x = 128;
	lpMMI->ptMinTrackSize.y = 128;

	return	TRUE;
}

WNDMSG	CMainFrame::OnActivate( WNDMSGPARAM )
{
	if( LOWORD(wParam) == WA_INACTIVE ) {
		m_bActivate = FALSE;
	} else {
		m_bActivate = TRUE;
	}
	return	FALSE;
}

WNDMSG	CMainFrame::OnActivateApp( WNDMSGPARAM )
{
	if( (BOOL)wParam ) {
		m_bActivateApp = TRUE;
		if( !Config.emulator.bBackground ) {
			Emu.Resume();
		}
		DirectInput.Acquire();
	} else {
		if( m_bActivateApp ) {
			m_bActivateApp = FALSE;
			if( !Config.emulator.bBackground ) {
				Emu.Pause();
			}
		}
		DirectInput.Unacquire();
	}
	return	FALSE;
}

WNDMSG	CMainFrame::OnShortCutEnable( WNDMSGPARAM )
{
	m_bKeyEnable = (BOOL)wParam;

	return	FALSE;
}

WNDMSG	CMainFrame::OnEnable( WNDMSGPARAM )
{
	if( (BOOL)wParam )
		Emu.Resume();
	else
		Emu.Pause();

	m_bKeyEnable = (BOOL)wParam;

	return	FALSE;
}

WNDMSG	CMainFrame::OnEnterMenuLoop( WNDMSGPARAM )
{
	m_bKeyEnable = FALSE;
	Emu.Pause();
	return	FALSE;
}

WNDMSG	CMainFrame::OnExitMenuLoop( WNDMSGPARAM )
{
	m_bKeyEnable = TRUE;
	Emu.Resume();
	return	FALSE;
}

WNDMSG	CMainFrame::OnSetFocus( WNDMSGPARAM )
{
	m_bForcus = TRUE;
	if( Config.general.bScreenMode ) {
		if( Emu.IsRunning() ) {
			if( !m_bMenu ) {
				Emu.EventParam( CEmuThread::EV_FULLSCREEN_GDI, FALSE );
			}
		}
	}
	return	FALSE;
}

WNDMSG	CMainFrame::OnKillFocus( WNDMSGPARAM )
{
	m_bForcus = FALSE;
	return	FALSE;
}

WNDMSG	CMainFrame::OnInitMenu( WNDMSGPARAM )
{
	DrawMenuBar( m_hWnd );
	return	FALSE;
}

WNDMSG	CMainFrame::OnInitMenuPopup( WNDMSGPARAM )
{
	// System menu
	if( (BOOL)HIWORD(lParam) )
		return	FALSE;

	HMENU	hMenu = (HMENU)wParam;

	INT	MenuCount = ::GetMenuItemCount( hMenu );
	for( INT i = 0; i < MenuCount; i++ ) {
		OnUpdateMenu( hMenu, ::GetMenuItemID( hMenu, i ) );
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnPaint( WNDMSGPARAM )
{
	HDC	hDC;
	PAINTSTRUCT	ps;
	hDC = ::BeginPaint( m_hWnd, &ps );
	if( !Emu.IsRunning() ) {
		RECT	rc;
		::GetClientRect( m_hWnd, &rc );
		::SetBkColor( hDC, 0x00000000 );
		::ExtTextOut( hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL );
	} else if( Emu.IsPausing() ) {
		DirectDraw.OnScreenDraw();
	}
	::EndPaint( m_hWnd, &ps );

	return	TRUE;
}

WNDMSG	CMainFrame::OnDisplayChange( WNDMSGPARAM )
{
	// Full Screenならば自分でChange中もしくはALT+TAB切り替え中
	if( !Config.general.bScreenMode ) {
		// 危険なのでThreadをPause
		Emu.Pause();
		DirectDraw.OnChangeDisplayMode();

		// 再描画
		::InvalidateRect( m_hWnd, NULL, TRUE );

		// ThreadをResume
		Emu.Resume();
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnPaletteChanged( WNDMSGPARAM )
{
	if( (HWND)wParam == m_hWnd )
		return	FALSE;

	DirectDraw.RealizePalette();
	return	FALSE;
}

WNDMSG	CMainFrame::OnQueryNewPalette( WNDMSGPARAM )
{
	DirectDraw.RealizePalette();
	return	TRUE;
}

WNDMSG	CMainFrame::OnMenuChar( WNDMSGPARAM )
{
	// キンキンうるさいから閉じる…と嘘をつく//吵闹得不得了 所以就关上了...
	hResult = MAKELONG(0,MNC_CLOSE);
	return	TRUE;
}

WNDMSG	CMainFrame::OnKeyDown( WNDMSGPARAM )
{
	if( Config.general.bScreenMode ) {
		if( wParam == VK_ESCAPE && (lParam & (1<<30)) == 0 ) {
			OnChangeMenu( !m_bMenu );
			return	TRUE;
		}
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnSize( WNDMSGPARAM )
{
	// 最大化表示等
	// WM_SYSCOMMANDでも良いのだが，CaptionをDouble Clickしたときに来ないので...
	switch( wParam ) {
		case	SIZE_MAXIMIZED:
			m_bZoomed = TRUE;
			{
			WINDOWPLACEMENT wpl;
			::GetWindowPlacement( m_hWnd, &wpl );
			m_WindowRect = wpl.rcNormalPosition;	// 元の位置をCopy
			}
			break;
		case	SIZE_RESTORED:
			m_bZoomed = FALSE;
			break;
		default:
			break;
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnSysCommand( WNDMSGPARAM )
{
	// Emulation中のみ
	if( Emu.IsRunning() ) {
		// Screen Saverの起動の抑止
		if( wParam == SC_SCREENSAVE ) {
			hResult = 1L;
			return	TRUE;
		}
		// Display電源Offの抑止
		if( wParam == SC_MONITORPOWER ) {
			hResult = 1L;
			return	TRUE;
		}
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnExitSizeMove( WNDMSGPARAM )
{
	if( !Config.general.bScreenMode ) {
		::GetWindowRect( m_hWnd, &m_WindowRect );
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnSetCursor( WNDMSGPARAM )
{
	if( LOWORD(lParam) == HTCLIENT ) {
		if( Emu.IsRunning() ) {
			if( !Emu.IsPausing() ) {
				if( DirectDraw.GetZapperMode() ) {
					m_bCursor = TRUE;
					::SetCursor( NULL );
					hResult = 1L;
					return	TRUE;
				} else {
					m_bCursor = FALSE;
					m_LastMovedTime = ::timeGetTime();
				}
			} else {
				m_bCursor = TRUE;
			}
		} else {
			m_bCursor = TRUE;
		}
	} else {
		m_bCursor = TRUE;
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnTimer( WNDMSGPARAM )
{
	if( wParam == 0x0001 ) {
	// Mouse Cursor用Timer
		RECT	rc;
		POINT	pt;
		::GetWindowRect( m_hWnd, &rc );
		::GetCursorPos( &pt );

		if( !m_bCursor && m_bForcus && pt.x >= rc.left && pt.x <= rc.right && pt.y >= rc.top && pt.y <= rc.bottom ) {
			if( Emu.IsRunning() && !Emu.IsPausing() ) {
				if( (::timeGetTime()-m_LastMovedTime) > 1500 ) {
					::SetCursor( NULL );
				}
			}
		}
	} else if( wParam == 0x0100 ) {
	// Key Check用Timer
		// Active Windowでない時やDialog等が出ている時はCancel
		if( m_bKeyEnable )
			OnKeyControl();
	}

	return	FALSE;
}

WNDMSG	CMainFrame::OnCopyData( WNDMSGPARAM )
{
	COPYDATASTRUCT* pcds = (COPYDATASTRUCT*)lParam;

	OnEmulationStart( (LPSTR)pcds->lpData, FALSE );

	return	TRUE;
}

WNDMSG	CMainFrame::OnErrorMessage( WNDMSGPARAM )
{
	// Search Dialog終了
	m_SearchDlg.Destroy();

	// NetPlay切断
	NetPlay.Disconnect();

	// Emulation終了
	Emu.Stop();
	DELETEPTR( Nes );

	::MessageBox( m_hWnd, (LPCTSTR)lParam, "ERROR", MB_ICONERROR|MB_OK );

	::InvalidateRect( m_hWnd, NULL, TRUE );

	return	TRUE;
}


WNDCMD	CMainFrame::OnHelp( WNDCMDPARAM )
{
	string	sHelp = CPathlib::MakePath( CApp::GetModulePath(), "virtuanes.chm" );

	// 面倒なんでShellExecuteで代用
	::ShellExecute( HWND_DESKTOP, "open", sHelp.c_str(), NULL, NULL, SW_SHOWNORMAL );
}

WNDCMD	CMainFrame::OnAbout( WNDCMDPARAM )
{
	CAboutDlg dlg;
	dlg.DoModal( m_hWnd );
}


WNDMSG	CMainFrame::OnCommandLine( WNDMSGPARAM )
{
	OnEmulationStart( (LPSTR)lParam, FALSE );

	return	TRUE;
}


WNDMSG	CMainFrame::OnNetPlay( WNDMSGPARAM )
{
	hResult = NetPlay.WndProc( hWnd, wParam, lParam );
	return	TRUE;
}

WNDMSG	CMainFrame::OnNetPlayClose( WNDMSGPARAM )
{
	NetPlay.SetMsgWnd( NULL );
	NetPlay.Disconnect();

	LPCSTR	szErrStr = CApp::GetErrorString( IDS_ERROR_NETWORKDISCONNECT );
	::PostMessage( m_hWnd, WM_VNS_ERRORMSG, 0, (LPARAM)szErrStr );
	return	TRUE;
}

WNDMSG	CMainFrame::OnNetPlayError( WNDMSGPARAM )
{
	NetPlay.SetMsgWnd( NULL );
	NetPlay.Disconnect();

	LPCSTR	szErrStr = CApp::GetErrorString( IDS_ERROR_NETWORKERROR );
	::PostMessage( m_hWnd, WM_VNS_ERRORMSG, 0, (LPARAM)szErrStr );
	return	TRUE;
}



void	CMainFrame::OnEmulationStart( LPCSTR szFile, BOOL bChecked )
{
	// Search Dialog終了
	m_SearchDlg.Destroy();

		// Emulation終了
		Emu.Stop();
		DELETEPTR( Nes );

		if( (Nes = new NES(szFile)) )
		{

			if( Config.general.bScreenMode )
			{
				DirectDraw.SetFullScreenGDI( FALSE );
			}
			else
			{
				if( Config.emulator.bLoadFullscreen )
				{
					::PostMessage( m_hWnd, WM_COMMAND, (WPARAM)ID_FULLSCREEN, (LPARAM)0 );
				}
			}

			// Emulation Thread Start
			Emu.Start( m_hWnd, Nes );
		}
		else
		{
			// xxx Fileを開けません
			LPCSTR	szErrStr = CApp::GetErrorString( IDS_ERROR_OPEN );
			sprintf( szErrorString, szErrStr, szFile );
			throw	szErrorString;
		}
}




WNDCMD	CMainFrame::OnNetPlayConnect( WNDCMDPARAM )
{
	if( !Emu.IsRunning() || !Nes )
		return;
	if( Nes->IsMoviePlay() || Nes->IsMovieRec() )
		return;
	if( NetPlay.IsConnect() )
		return;

	Emu.Pause();

	if( !m_bMenu )
		OnFullScreenGDI( TRUE );

	CNetPlayDlg	dlg;
	if( dlg.DoModal( m_hWnd ) == IDOK ) {
		Emu.Event( CEmuThread::EV_NETPLAY_START );
	}

	if( !m_bMenu )
		OnFullScreenGDI( FALSE );

	Emu.Resume();
}

WNDCMD	CMainFrame::OnNetPlayDisconnect( WNDCMDPARAM )
{
	if( !NetPlay.IsConnect() )
		return;

	Emu.Pause();
	NetPlay.Disconnect();
	Emu.Resume();
}

WNDCMD	CMainFrame::OnSearch( WNDCMDPARAM )
{
	if( !Emu.IsRunning() || !Nes )
		return;

	if( !m_SearchDlg.m_hWnd ) {
		m_SearchDlg.Create( NULL );
	}

	if( Config.general.bScreenMode ) {
		if( Emu.IsRunning() ) {
			Emu.EventParam( CEmuThread::EV_FULLSCREEN_GDI, TRUE );
		} else {
			DirectDraw.SetFullScreenGDI( TRUE );
		}
		// Dialogを中央に移動する:)
		RECT	rcParent, rc;
		::GetWindowRect( m_hWnd, &rcParent );
		::GetWindowRect( m_SearchDlg.m_hWnd, &rc );
		INT x = rcParent.left+(rcParent.right-rcParent.left)/2-(rc.right-rc.left)/2;
		INT y = rcParent.top +(rcParent.bottom-rcParent.top)/2-(rc.bottom-rc.top)/2;
		::SetWindowPos( m_SearchDlg.m_hWnd, NULL, x, y, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );

		::SetWindowPos( m_SearchDlg.m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
	} else {
		::SetWindowPos( m_SearchDlg.m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
	}

	::ShowWindow( m_SearchDlg.m_hWnd, SW_SHOW );
}

WNDCMD	CMainFrame::OnCheat( WNDCMDPARAM )
{
	if( !Emu.IsRunning() || !Nes )
		return;

	if( !m_bMenu )
		OnFullScreenGDI( TRUE );

	CCheatCodeDlg	dlg;

	dlg.DoModal( m_hWnd );

	if( !m_bMenu )
		OnFullScreenGDI( FALSE );
}

WNDCMD	CMainFrame::OnGenie( WNDCMDPARAM )
{
	if( !Emu.IsRunning() || !Nes )
		return;

	Emu.Pause();

	string	tempstr;
	if( Config.path.bCheatPath ) {
		CreateDirectory( Config.path.szCheatPath, NULL );
		tempstr = CPathlib::MakePathExt( Config.path.szCheatPath, Emu.GetNES()->rom->GetRomName(), "gen" );
	} else {
		tempstr = CPathlib::MakePathExt( Emu.GetNES()->rom->GetRomPath(), Emu.GetNES()->rom->GetRomName(), "gen" );
	}

	OPENFILENAME	ofn;
	CHAR	szFile[_MAX_PATH];

	::strcpy( szFile, tempstr.c_str() );
	::ZeroMemory( &ofn, sizeof(ofn) );

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);

	ofn.lpstrFilter = "GameGeine Files(*.gen)\0*.gen\0All Files(*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_EXPLORER|OFN_PATHMUSTEXIST;

	if( Config.path.bCheatPath ) {
		ofn.lpstrInitialDir = Config.path.szCheatPath;
	} else {
		ofn.lpstrInitialDir = CApp::GetModulePath();
	}

	CHAR	szTitle[256];
	CApp::LoadString( IDS_UI_LOADGENIECODE, szTitle, sizeof(szTitle) );
	ofn.lpstrTitle = szTitle;
	if( ::GetOpenFileName( &ofn ) ) {
		Nes->GenieLoad( szFile );
	}

	Emu.Resume();
}

WNDCMD	CMainFrame::OnCheatCommand( WNDCMDPARAM )
{
	if( !Emu.IsRunning() || !Nes )
		return;

	if( uID == ID_CHEAT_ENABLE ) {
		Nes->SetCheatCodeAllFlag( TRUE, TRUE );
	} else
	if( uID == ID_CHEAT_DISABLE ) {
		Nes->SetCheatCodeAllFlag( FALSE, TRUE );
	}
}

WNDCMD	CMainFrame::OnEmulatorCfg( WNDCMDPARAM )
{
	CEmulatorDlg dlg;
	if( dlg.DoModal( m_hWnd ) == IDOK ) {
		Emu.SetPriority( Config.emulator.nPriority );
	}
}

WNDCMD	CMainFrame::OnGraphicsCfg( WNDCMDPARAM )
{
	CGraphicsDlg dlg;
	if( dlg.DoModal( m_hWnd ) == IDOK ) {
		Emu.Pause();

		// Surfaceをリビルドする必要があるかのCheck
		BOOL	bRebuildDirectDraw = FALSE;
		BOOL	bRebuildSurface = FALSE;

		if( DirectDraw.GetUseHEL() != Config.graphics.bUseHEL )
			bRebuildDirectDraw = TRUE;
		if( DirectDraw.GetSystemMemory() != Config.graphics.bSystemMemory )
			bRebuildSurface = TRUE;

		// DirectDraw Optionの設定
		DirectDraw.SetFlipMode     ( Config.graphics.bSyncDraw );
		DirectDraw.SetAspectMode   ( Config.graphics.bAspect );
		DirectDraw.SetAllLineMode  ( Config.graphics.bAllLine );
		DirectDraw.SetMaxZoom      ( Config.graphics.bFitZoom );
		DirectDraw.SetTVFrameMode  ( Config.graphics.bTVFrame );
		DirectDraw.SetScanlineMode ( Config.graphics.bScanline );
		DirectDraw.SetScanlineColor( Config.graphics.nScanlineColor );

		DirectDraw.SetUseHEL      ( Config.graphics.bUseHEL );
		DirectDraw.SetDoubleSize  ( Config.graphics.bDoubleSize );
		DirectDraw.SetSystemMemory( Config.graphics.bSystemMemory );

		DirectDraw.SetWindowVSyncMode( Config.graphics.bWindowVSync );

		if( Config.general.bScreenMode ) {
			// Screen Modeの変更があった場合
			if( DirectDraw.m_dwDisplayWidth  != Config.graphics.dwDisplayWidth
			 || DirectDraw.m_dwDisplayHeight != Config.graphics.dwDisplayHeight
			 || DirectDraw.m_dwDisplayDepth  != Config.graphics.dwDisplayDepth
			 || DirectDraw.m_dwDisplayRate   != Config.graphics.dwDisplayRate ) {
				if( !bRebuildDirectDraw )
					DirectDraw.BeginDisplayChange();

				// Screen Modeの設定
				DirectDraw.m_dwDisplayWidth  = Config.graphics.dwDisplayWidth;
				DirectDraw.m_dwDisplayHeight = Config.graphics.dwDisplayHeight;
				DirectDraw.m_dwDisplayDepth  = Config.graphics.dwDisplayDepth;
				DirectDraw.m_dwDisplayRate   = Config.graphics.dwDisplayRate;

				DirectDraw.SetScreenMode( Config.general.bScreenMode );
				if( !bRebuildDirectDraw )
					DirectDraw.EndDisplayChange();

				::SetWindowPos( m_hWnd, HWND_NOTOPMOST, 0, 0, ::GetSystemMetrics(SM_CXSCREEN),
						::GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW );

				// Palette
				::PostMessage( m_hWnd, WM_QUERYNEWPALETTE, 0, 0 );

				// Surfaceは再構築されたので二度は行わない
				bRebuildSurface = FALSE;
			}
		} else {
			OnSetWindowSize();
		}
		if( bRebuildDirectDraw ) {
			DirectDraw.ReleaseDDraw();
			DirectDraw.InitialDDraw( m_hWnd );
			DirectDraw.InitialSurface( Config.general.bScreenMode );
		} else
		if( bRebuildSurface ) {
			DirectDraw.ReleaseSurface();
			DirectDraw.InitialSurface( Config.general.bScreenMode );
		}

		Emu.Resume();
	}
}

WNDCMD	CMainFrame::OnSoundCfg( WNDCMDPARAM )
{
	CSoundDlg dlg;

	DWORD	rate, bits;
	DirectSound.GetSamplingRate( rate, bits );
	BOOL	bSoundOn = DirectSound.IsStreamPlay();

	if( dlg.DoModal( m_hWnd ) == IDOK ) {
		if( Config.sound.nRate != (INT)rate
		 || Config.sound.nBits != (INT)bits
		 || Config.sound.nBufferSize != DirectSound.GetBufferSize() ) {
			Emu.Pause();
			if( bSoundOn ) {
				DirectSound.StreamStop();
			}

			DirectSound.ReleaseBuffer();

			DirectSound.SetSamplingRate( Config.sound.nRate, Config.sound.nBits );
			DirectSound.SetBufferSize( Config.sound.nBufferSize );

			if( DirectSound.InitialBuffer() ) {
				if( Nes ) {
					Nes->SoundSetup();
				}
				if( bSoundOn ) {
					DirectSound.StreamPlay();
					DirectSound.StreamPause();
				}
			}
			Emu.Resume();
		}
	}
}

WNDCMD	CMainFrame::OnControllerCfg( WNDCMDPARAM )
{
	CControllerDlg dlg;

	CWndHook::SetFiltering( TRUE );
	dlg.DoModal( m_hWnd );
	CWndHook::SetFiltering( FALSE );
}

WNDCMD	CMainFrame::OnShortcutCfg( WNDCMDPARAM )
{
	CShortcutDlg dlg;

	CWndHook::SetFiltering( TRUE );

	if( dlg.DoModal( m_hWnd ) == IDOK ) {
		::SetMenu( m_hWnd, NULL );
		::DestroyMenu( m_hMenu );
		// Menuの再Load
		m_hMenu = CApp::LoadMenu( IDR_MENU );
		CApp::SetMenu( m_hMenu );
		::SetMenu( m_hWnd, m_hMenu );
		OnRebuildMenu();
	}

	CWndHook::SetFiltering( FALSE );
}

WNDCMD	CMainFrame::OnMovieCfg( WNDCMDPARAM )
{
	CMovieDlg dlg;
	dlg.DoModal( m_hWnd );
}

WNDCMD	CMainFrame::OnGameOptionCfg( WNDCMDPARAM )
{
	CGameOptionDlg dlg;
	dlg.DoModal( m_hWnd );
}

WNDCMD	CMainFrame::OnFullScreen( WNDCMDPARAM )
{
	// 危険なので...
	Emu.Pause();

	Config.general.bScreenMode = !Config.general.bScreenMode;
//	OnChangeMenu( FALSE );

	if( !Config.general.bScreenMode ) {
	// FullScreen to Window mode
		DirectDraw.BeginDisplayChange();

		// 位置の復帰
		::SetWindowLong( m_hWnd, GWL_STYLE, m_StyleBackup );
		::SetWindowLong( m_hWnd, GWL_EXSTYLE, m_ExStyleBackup );
		::SetWindowPlacement( m_hWnd, &m_WindowPlacement );
	} else {
	// Window to FullScreen mode
		// 位置の保存
		m_WindowPlacement.length = sizeof(m_WindowPlacement);
		::GetWindowPlacement( m_hWnd, &m_WindowPlacement );

		m_StyleBackup   = ::GetWindowLong( m_hWnd, GWL_STYLE );
		m_ExStyleBackup = ::GetWindowLong( m_hWnd, GWL_EXSTYLE );
		::SetWindowLong( m_hWnd, GWL_STYLE, WS_POPUP );
		::SetWindowLong( m_hWnd, GWL_EXSTYLE, 0 );

		// Screen Modeの設定
		DirectDraw.m_dwDisplayWidth  = Config.graphics.dwDisplayWidth;
		DirectDraw.m_dwDisplayHeight = Config.graphics.dwDisplayHeight;
		DirectDraw.m_dwDisplayDepth  = Config.graphics.dwDisplayDepth;
		DirectDraw.m_dwDisplayRate   = Config.graphics.dwDisplayRate;

		DirectDraw.BeginDisplayChange();
	}

	DirectDraw.SetScreenMode( Config.general.bScreenMode );
	DirectDraw.EndDisplayChange();

	if( !Config.general.bScreenMode )
	{
		OnChangeMenu( TRUE );
		::SetForegroundWindow( m_hWnd );
		::RedrawWindow( m_hWnd, NULL, NULL, RDW_FRAME|RDW_INVALIDATE );
	} else {
		if( Emu.IsRunning() ) {
			OnChangeMenu( FALSE );
		} else {
			OnChangeMenu( TRUE );
		}
		::SetWindowPos( m_hWnd, HWND_NOTOPMOST, 0, 0, ::GetSystemMetrics(SM_CXSCREEN),
				::GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW );
	}

	// 危険なので...
	Emu.Resume();
}

WNDCMD	CMainFrame::OnZoom( WNDCMDPARAM )
{
	// Full Screen時は無視
	if( Config.general.bScreenMode )
		return;

	Config.general.nScreenZoom = (INT)(uID-ID_ZOOMx1);
	OnSetWindowSize();

	CHAR	szStr[64];
	::wsprintf( szStr, "Screen Zoom *%d", uID-ID_ZOOMx1+1 );
	Emu.EventParam( CEmuThread::EV_MESSAGE_OUT, (LONG)szStr );
}


WNDCMD	CMainFrame::OnEmuCommand( WNDCMDPARAM )
{
	switch( uID ) {
		case	ID_HWRESET:
			Emu.Event( CEmuThread::EV_HWRESET );
			break;
		case	ID_SWRESET:
			Emu.Event( CEmuThread::EV_SWRESET );
			break;
		case	ID_PAUSE:
			Emu.Event( CEmuThread::EV_EMUPAUSE );
			break;

		case	ID_ONEFRAME:
			Emu.Event( CEmuThread::EV_ONEFRAME );
			break;

		case	ID_THROTTLE:
			Emu.Event( CEmuThread::EV_THROTTLE );
			break;
		case	ID_FRAMESKIP_UP:
			Emu.Event( CEmuThread::EV_FRAMESKIP_UP );
			break;
		case	ID_FRAMESKIP_DOWN:
			Emu.Event( CEmuThread::EV_FRAMESKIP_DOWN );
			break;
		case	ID_FRAMESKIP_AUTO:
			Emu.Event( CEmuThread::EV_FRAMESKIP_AUTO );
			break;

		case	ID_STATE_UP:
			{
			CHAR	szStr[64];
			if( ++m_nStateSlot > 10-1 ) {
				m_nStateSlot = 0;
			}
			::wsprintf( szStr, "State Slot #%d", m_nStateSlot );
			Emu.EventParam( CEmuThread::EV_MESSAGE_OUT, (LONG)szStr );
			}
			break;
		case	ID_STATE_DOWN:
			{
			CHAR	szStr[64];
			if( --m_nStateSlot < 0 ) {
				m_nStateSlot = 10-1;
			}
			::wsprintf( szStr, "State Slot #%d", m_nStateSlot );
			Emu.EventParam( CEmuThread::EV_MESSAGE_OUT, (LONG)szStr );
			}
			break;

		case	ID_STATE_SLOT0:	case	ID_STATE_SLOT1:
		case	ID_STATE_SLOT2:	case	ID_STATE_SLOT3:
		case	ID_STATE_SLOT4:	case	ID_STATE_SLOT5:
		case	ID_STATE_SLOT6:	case	ID_STATE_SLOT7:
		case	ID_STATE_SLOT8:	case	ID_STATE_SLOT9:
			m_nStateSlot = (INT)(uID-ID_STATE_SLOT0);
			{
			CHAR	szStr[64];
			::wsprintf( szStr, "State Slot #%d", m_nStateSlot );
			Emu.EventParam( CEmuThread::EV_MESSAGE_OUT, (LONG)szStr );
			}
			break;

		case	ID_MUTE_0: case	ID_MUTE_1: case	ID_MUTE_2: case	ID_MUTE_3:
		case	ID_MUTE_4: case	ID_MUTE_5: case	ID_MUTE_6: case	ID_MUTE_7:
		case	ID_MUTE_8: case	ID_MUTE_9: case	ID_MUTE_A: case	ID_MUTE_B:
		case	ID_MUTE_C: case	ID_MUTE_D: case	ID_MUTE_E: case	ID_MUTE_F:
			Emu.EventParam( CEmuThread::EV_SOUND_MUTE, (LONG)(uID-ID_MUTE_0) );
			break;

		case	ID_SNAPSHOT:
			Emu.Event( CEmuThread::EV_SNAPSHOT );
			break;

		case	ID_TVASPECT:
			Config.graphics.bAspect = !Config.graphics.bAspect;
			Emu.Pause();
			DirectDraw.SetAspectMode( Config.graphics.bAspect );
			if( !Config.general.bScreenMode )
				OnSetWindowSize();
			Emu.Resume();
			break;
		case	ID_SCANLINE:
			Config.graphics.bScanline = !Config.graphics.bScanline;
			Emu.Pause();
			DirectDraw.SetScanlineMode( Config.graphics.bScanline );
			Emu.Resume();
			break;
		case	ID_ALLLINE:
			Config.graphics.bAllLine = !Config.graphics.bAllLine;
			Emu.Pause();
			DirectDraw.SetAllLineMode( Config.graphics.bAllLine );
			if( !Config.general.bScreenMode )
				OnSetWindowSize();
			Emu.Resume();
			break;
		case	ID_ALLSPRITE:
			Config.graphics.bAllSprite = !Config.graphics.bAllSprite;
			break;
		case	ID_SYNCDRAW:
			Config.graphics.bSyncDraw = !Config.graphics.bSyncDraw;
			Emu.Pause();
			DirectDraw.SetFlipMode( Config.graphics.bSyncDraw );
			Emu.Resume();
			break;
		case	ID_FITSCREEN:
			Config.graphics.bFitZoom = !Config.graphics.bFitZoom;
			Emu.Pause();
			DirectDraw.SetMaxZoom( Config.graphics.bFitZoom );
			Emu.Resume();
			break;

		case	ID_TVFRAME:
			Config.graphics.bTVFrame = !Config.graphics.bTVFrame;
			Emu.Pause();
			DirectDraw.SetTVFrameMode( Config.graphics.bTVFrame );
			Emu.Resume();
			break;
		case	ID_FPSDISP:
			Config.graphics.bFPSDisp = !Config.graphics.bFPSDisp;
			break;

		case	ID_LEFTCLIP:
			Config.graphics.bLeftClip = !Config.graphics.bLeftClip;
			break;

		default:
			break;
	}
}

WNDCMD	CMainFrame::OnStateCommand( WNDCMDPARAM )
{
	if( !Emu.IsRunning() )
		return;

	CHAR	st[16];
	::wsprintf( st, "st%1X", m_nStateSlot );

	string	tempstr;
	if( Config.path.bStatePath ) {
		::CreateDirectory( Config.path.szStatePath, NULL );
		tempstr = CPathlib::MakePathExt( Config.path.szStatePath, Nes->rom->GetRomName(), st );
	} else {
		tempstr = CPathlib::MakePathExt( Nes->rom->GetRomPath(), Nes->rom->GetRomName(), st );
	}

	if( uID == ID_STATE_LOAD ) {
		INT	ret;
		if( (ret = NES::IsStateFile( tempstr.c_str(), Nes->rom )) >= 0 ) {
			if( ret == IDS_ERROR_ILLEGALSTATECRC ) {
				if( Config.emulator.bCrcCheck ) {
					if( ::MessageBox( m_hWnd, CApp::GetErrorString(ret), "VirtuaNES", MB_ICONWARNING|MB_YESNO ) != IDYES )
						return;
				}
			}
		}
		Emu.EventParam2( CEmuThread::EV_STATE_LOAD, (INT)tempstr.c_str(), m_nStateSlot );
	}
	if( uID == ID_STATE_SAVE ) {
		Emu.EventParam2( CEmuThread::EV_STATE_SAVE, (INT)tempstr.c_str(), m_nStateSlot );
	}
}

WNDCMD	CMainFrame::OnMovieCommand( WNDCMDPARAM )
{
	if( !Emu.IsRunning() )
		return;

	if( uID == ID_MOVIE_STOP ) {
		Emu.Event( CEmuThread::EV_MOVIE_STOP );
		return;
	}

	Emu.Pause();

	if( Config.general.bScreenMode && !m_bMenu ) {
		OnFullScreenGDI( TRUE );
	}

	string	tempstr;
	if( Config.path.bMoviePath ) {
		CreateDirectory( Config.path.szMoviePath, NULL );
		tempstr = CPathlib::MakePathExt( Config.path.szMoviePath, Nes->rom->GetRomName(), "vmv" );
	} else {
		tempstr = CPathlib::MakePathExt( Nes->rom->GetRomPath(), Nes->rom->GetRomName(), "vmv" );
	}

	OPENFILENAME	ofn;
	CHAR	szFile[_MAX_PATH];

	::strcpy( szFile, tempstr.c_str() );
	::ZeroMemory( &ofn, sizeof(ofn) );

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);

	ofn.lpstrFilter = "Movie Files(*.vmv)\0*.vmv\0All Files(*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_EXPLORER|OFN_PATHMUSTEXIST;

	if( Config.path.bMoviePath ) {
		ofn.lpstrInitialDir = Config.path.szMoviePath;
	} else {
		ofn.lpstrInitialDir = CApp::GetModulePath();
	}

	CHAR	szTitle[256];

	if( uID == ID_MOVIE_PLAY ) {
		CApp::LoadString( IDS_UI_PLAYMOVIE, szTitle, sizeof(szTitle) );
		ofn.lpstrTitle = szTitle;
		if( ::GetOpenFileName( &ofn ) ) {
			INT	ret;
			if( (ret = NES::IsMovieFile( szFile, Nes->rom )) >= 0 ) {
				if( ret == IDS_ERROR_ILLEGALMOVIEOLD ) {
					::MessageBox( m_hWnd, CApp::GetErrorString(ret), "VirtuaNES", MB_ICONHAND|MB_OK );
					goto	_Movie_Play_Failed;
				} else
				if( ret == IDS_ERROR_ILLEGALMOVIEVER ) {
					if( Config.emulator.bCrcCheck ) {
						if( ::MessageBox( m_hWnd, CApp::GetErrorString(ret), "VirtuaNES", MB_ICONWARNING|MB_YESNO ) != IDYES )
							goto	_Movie_Play_Failed;
					}
				} else
				if( ret == IDS_ERROR_ILLEGALMOVIECRC ) {
					if( Config.emulator.bCrcCheck ) {
						if( ::MessageBox( m_hWnd, CApp::GetErrorString(ret), "VirtuaNES", MB_ICONWARNING|MB_YESNO ) != IDYES )
							goto	_Movie_Play_Failed;
					}
				}

				Emu.EventParam( CEmuThread::EV_MOVIE_PLAY, (INT)szFile );
			}
_Movie_Play_Failed:;
		}
	}
	if( uID == ID_MOVIE_REC ) {
		ofn.Flags |= OFN_OVERWRITEPROMPT;
		CApp::LoadString( IDS_UI_RECMOVIE, szTitle, sizeof(szTitle) );
		ofn.lpstrTitle = szTitle;
		if( ::GetSaveFileName( &ofn ) ) {
			Emu.EventParam( CEmuThread::EV_MOVIE_REC, (INT)szFile );
		}
	}
	if( uID == ID_MOVIE_REC_APPEND ) {
		CApp::LoadString( IDS_UI_APPENDMOVIE, szTitle, sizeof(szTitle) );
		ofn.lpstrTitle = szTitle;
		if( ::GetOpenFileName( &ofn ) ) {
			INT	ret;
			if( (ret = NES::IsMovieFile( szFile, Nes->rom )) >= 0 ) {
				if( ret == IDS_ERROR_ILLEGALMOVIEOLD ) {
					::MessageBox( m_hWnd, CApp::GetErrorString(IDS_ERROR_ILLEGALMOVIEOLD_A), "VirtuaNES", MB_ICONHAND|MB_OK );
					goto	_Movie_Append_Failed;
				} else
				if( ret == IDS_ERROR_ILLEGALMOVIEVER ) {
					if( Config.emulator.bCrcCheck ) {
						if( ::MessageBox( m_hWnd, CApp::GetErrorString(IDS_ERROR_ILLEGALMOVIEVER_A), "VirtuaNES", MB_ICONWARNING|MB_YESNO ) != IDYES )
							goto	_Movie_Append_Failed;
					}
				} else
				if( ret == IDS_ERROR_ILLEGALMOVIECRC ) {
					if( Config.emulator.bCrcCheck ) {
						if( ::MessageBox( m_hWnd, CApp::GetErrorString(IDS_ERROR_ILLEGALMOVIECRC_A), "VirtuaNES", MB_ICONWARNING|MB_YESNO ) != IDYES )
							goto	_Movie_Append_Failed;
					}
				}

				Emu.EventParam( CEmuThread::EV_MOVIE_RECAPPEND, (INT)szFile );
			} else {
				// 新規作成と同じ
				Emu.EventParam( CEmuThread::EV_MOVIE_REC, (INT)szFile );
			}
		}
_Movie_Append_Failed:;
	}

	if( Config.general.bScreenMode && !m_bMenu ) {
		OnFullScreenGDI( FALSE );
	}

	Emu.Resume();
}

void	CMainFrame::OnMovieInfo( WNDCMDPARAM )
{
	if( !Emu.IsRunning() || !Nes )
		return;

	if( !(Nes->IsMoviePlay() || Nes->IsMovieRec()) )
		return;

	CMovieInfoDlg dlg;

	// Memberの設定
	Nes->GetMovieInfo( dlg.m_wRecVersion, dlg.m_wVersion, dlg.m_dwFrames, dlg.m_dwRerecordTimes );

	if( !m_bMenu )
		OnFullScreenGDI( TRUE );
	dlg.DoModal( m_hWnd );
	if( !m_bMenu )
		OnFullScreenGDI( FALSE );
}

void	CMainFrame::OnFullScreenGDI( BOOL bFlag )
{
	if( Config.general.bScreenMode ) {
		if( Emu.IsRunning() ) {
			Emu.EventParam( CEmuThread::EV_FULLSCREEN_GDI, (INT)bFlag );
		}
	}
}

void	CMainFrame::OnShowCursor( BOOL bFlag )
{
	if( !bFlag ) {
		if( m_bCursor ) {
			while( ::ShowCursor( FALSE ) >= 0 );
			m_bCursor = FALSE;
		}
	} else {
		if( !m_bCursor ) {
			while( ::ShowCursor( TRUE ) < 0 );
			m_bCursor = TRUE;
		}
	}
}

void	CMainFrame::OnChangeMenu( BOOL bFlag )
{
	if( Config.general.bScreenMode ) {
		if( Emu.IsRunning() ) {
			Emu.EventParam( CEmuThread::EV_FULLSCREEN_GDI, (INT)bFlag );
		} else {
			DirectDraw.SetFullScreenGDI( bFlag );
		}
	}

	if( m_bMenu ) {
		if( !bFlag ) {
			::SetMenu( m_hWnd, NULL );
			m_bMenu = FALSE;
		}
	} else {
		if( bFlag ) {
			::SetMenu( m_hWnd, m_hMenu );
			m_bMenu = TRUE;
			::DrawMenuBar( m_hWnd );
		}
	}
}

void	CMainFrame::OnSetWindowSize()
{
	// Window Modeの時だけ
	if( Config.general.bScreenMode )
		return;

	LONG	width, height;

	if( !Config.graphics.bAspect )  width  = CDirectDraw::SCREEN_WIDTH;
	else				width  = (LONG)((CDirectDraw::SCREEN_WIDTH)*1.25);
	if( !Config.graphics.bAllLine ) height = CDirectDraw::SCREEN_HEIGHT-16;
	else				height = CDirectDraw::SCREEN_HEIGHT;

	width  *= Config.general.nScreenZoom+1;
	height *= Config.general.nScreenZoom+1;

	RECT	rcW, rcC;
	::GetWindowRect( m_hWnd, &rcW );
	::GetClientRect( m_hWnd, &rcC );

	rcW.right  += width -(rcC.right-rcC.left);
	rcW.bottom += height-(rcC.bottom-rcC.top);
	::SetWindowPos( m_hWnd, HWND_NOTOPMOST, rcW.left, rcW.top,
			rcW.right-rcW.left, rcW.bottom-rcW.top, SWP_NOZORDER );

	// Menuが折り返されると縦が小さくなる事があるので再修正
	::GetClientRect( m_hWnd, &rcC );
	if( (rcC.bottom-rcC.top) != height ) {
		::GetWindowRect( m_hWnd, &rcW );
		::GetClientRect( m_hWnd, &rcC );

		rcW.right  += width -(rcC.right-rcC.left);
		rcW.bottom += height-(rcC.bottom-rcC.top);
		::SetWindowPos( m_hWnd, HWND_NOTOPMOST, rcW.left, rcW.top,
				rcW.right-rcW.left, rcW.bottom-rcW.top, SWP_NOZORDER );
	}


	// 最大表示時にSizeを変更した場合の最大表示の解除及びボタンの再描画
	LONG	style = ::GetWindowLong( m_hWnd, GWL_STYLE );
	style &= ~WS_MAXIMIZE;
	::SetWindowLong( m_hWnd, GWL_STYLE, style );
	::RedrawWindow( m_hWnd, NULL, NULL, RDW_FRAME|RDW_INVALIDATE );

	// 位置保存しなおし
	m_bZoomed = FALSE;
	::GetWindowRect( m_hWnd, &m_WindowRect );
}

void	CMainFrame::OnRebuildMenu()
{
	CHAR	szMenuString[256];
	string	str;
	for( INT i = 0; CConfig::ShortcutKeyID[i*3+0]; i++ ) {
		::GetMenuString( m_hMenu, CConfig::ShortcutKeyID[i*3+0], szMenuString, 256, MF_BYCOMMAND );

		INT	id, code;
		id = CConfig::ShortcutKeyID[i*3+2];
		code = Config.shortcut.nShortCut[id];
		if( code != 0 ) {
			string	temp = szMenuString;
			temp = temp + "\t";
			temp = temp + Config.ShortcutToKeyName( code );

			::ModifyMenu( m_hMenu, CConfig::ShortcutKeyID[i*3+0], MF_BYCOMMAND|MF_STRING,
					CConfig::ShortcutKeyID[i*3+0], temp.c_str() );
		}
	}
}

void	CMainFrame::OnUpdateMenu( HMENU hMenu, UINT uID )
{
	BOOL	bEnable, bCheck;
	BOOL	bEmu = Emu.IsRunning();
	BOOL	bScn = Config.general.bScreenMode;

	switch( uID ) {

		case	ID_NETPLAY_CONNECT:
			if( bEmu )
				bEnable = !(Nes->IsMoviePlay() || Nes->IsMovieRec() || Nes->rom->IsNSF());
			else
				bEnable = FALSE;
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|((bEnable&&bEmu&&NetPlay.IsNetPlay()&&!NetPlay.IsConnect())?MF_ENABLED:MF_GRAYED) );
			break;
		case	ID_NETPLAY_DISCONNECT:
			if( bEmu )
				bEnable = !(Nes->IsMoviePlay() || Nes->IsMovieRec() || Nes->rom->IsNSF());
			else
				bEnable = FALSE;
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|((bEnable&&bEmu&&NetPlay.IsNetPlay()&&NetPlay.IsConnect())?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_HWRESET:
		case	ID_SWRESET:
		case	ID_PAUSE:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;
		case	ID_STATE_LOAD:
		case	ID_STATE_SAVE:
			if( Nes ) {
				bEnable = bEmu && !Nes->rom->IsNSF();
			} else {
				bEnable = bEmu;
			}
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEnable?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_STATE_SLOT0:	case	ID_STATE_SLOT1:
		case	ID_STATE_SLOT2:	case	ID_STATE_SLOT3:
		case	ID_STATE_SLOT4:	case	ID_STATE_SLOT5:
		case	ID_STATE_SLOT6:	case	ID_STATE_SLOT7:
		case	ID_STATE_SLOT8:	case	ID_STATE_SLOT9:
			// 日時表示(結構面倒ｗ)
			{
			CHAR	szMenuString[256];
			CHAR*	pToken;
			const UCHAR seps[] = " \t\0";	// Splite

			// ID番号からIndexを探す
			for( INT i = 0; CConfig::ShortcutKeyID[i*3+0] != uID; i++ );

			::GetMenuString( m_hMenu, CConfig::ShortcutKeyID[i*3+0], szMenuString, 256, MF_BYCOMMAND );

			if( (pToken = (CHAR*)_mbstok( (UCHAR*)szMenuString, seps )) ) {
				string	str = pToken;

				if( Emu.IsRunning() && Nes ) {
					CHAR	temp[256];
					::wsprintf( temp, "st%1X", CConfig::ShortcutKeyID[i*3+0]-ID_STATE_SLOT0 );

					string	tempstr;
					if( Config.path.bStatePath ) {
						::CreateDirectory( Config.path.szStatePath, NULL );
						tempstr = CPathlib::MakePathExt( Config.path.szStatePath, Nes->rom->GetRomName(), temp );
					} else {
						tempstr = CPathlib::MakePathExt( Nes->rom->GetRomPath(), Nes->rom->GetRomName(), temp );
					}

					HANDLE	hFile = ::CreateFile( tempstr.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
					if( hFile != INVALID_HANDLE_VALUE ) {
						BY_HANDLE_FILE_INFORMATION fi;
						FILETIME	filetime;
						SYSTEMTIME	systime;
						::GetFileInformationByHandle( hFile, &fi );
						::FileTimeToLocalFileTime( &fi.ftLastWriteTime, &filetime );
						::FileTimeToSystemTime( &filetime, &systime );
						::wsprintf( temp,"%04d/%02d/%02d %02d:%02d:%02d", systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond );
						::CloseHandle( hFile );

						str = str + " ";
						str = str + temp;
					} else {
						str = str + " not exist";
					}
				}

				INT	code = Config.shortcut.nShortCut[CConfig::ShortcutKeyID[i*3+2]];
				if( code ) {
					str = str + "\t";
					str = str + Config.ShortcutToKeyName( code );
				}

				::ModifyMenu( m_hMenu, CConfig::ShortcutKeyID[i*3+0], MF_BYCOMMAND|MF_STRING,
						CConfig::ShortcutKeyID[i*3+0], str.c_str() );
			}

			::CheckMenuItem( hMenu, uID, MF_BYCOMMAND|(m_nStateSlot==(INT)(uID-ID_STATE_SLOT0)?MF_CHECKED:MF_UNCHECKED) );
			}
			break;

		case	ID_ZOOMx1: case	ID_ZOOMx2:
		case	ID_ZOOMx3: case	ID_ZOOMx4:
			if( bScn ) ::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|MF_GRAYED );
			else	   ::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|MF_ENABLED );
			::CheckMenuItem( hMenu, uID, MF_BYCOMMAND|(Config.general.nScreenZoom==(uID-ID_ZOOMx1)?MF_CHECKED:MF_UNCHECKED) );
			break;

		case	ID_DISK_EJECT:
		case	ID_DISK_0A: case	ID_DISK_0B:
		case	ID_DISK_1A: case	ID_DISK_1B:
			if( Nes ) {
				INT no = Nes->GetDiskNo();
				bEnable = bEmu && !(Nes->rom->GetMapperNo() != 20 || Nes->rom->IsNSF() || (!no || (uID-ID_DISK_EJECT)>no));
			} else {
				bEnable = bEmu;
			}
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEnable?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_MOVIE_PLAY:
		case	ID_MOVIE_REC:
		case	ID_MOVIE_REC_APPEND:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|((bEmu&&!NetPlay.IsConnect())?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_MOVIE_STOP:
		case	ID_MOVIE_INFO:
			if( Nes ) {
				bEnable = Nes->IsMoviePlay() || Nes->IsMovieRec();
			} else {
				bEnable = bEmu;
			}
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEnable?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_SNAPSHOT:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_EXCTR_NONE:
		case	ID_EXCTR_PADDLE:
		case	ID_EXCTR_HYPERSHOT:
		case	ID_EXCTR_ZAPPER:
		case	ID_EXCTR_KEYBOARD:
		case	ID_EXCTR_CRAZYCLIMBER:
		case	ID_EXCTR_TOPRIDER:
		case	ID_EXCTR_SPACESHADOWGUN:
			if( Nes ) {
				if( Nes->pad->GetExController() == (uID-ID_EXCTR_NONE) )
					bCheck = TRUE;
				else
					bCheck = FALSE;
			} else {
				if( uID == ID_EXCTR_NONE )
					bCheck = TRUE;
				else
					bCheck = FALSE;
			}
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			::CheckMenuItem( hMenu, uID, MF_BYCOMMAND|(bCheck?MF_CHECKED:MF_UNCHECKED) );
			break;

		case	ID_FULLSCREEN:
			::CheckMenuItem( hMenu, uID, MF_BYCOMMAND|(bScn?MF_CHECKED:MF_UNCHECKED) );
			break;
		case	ID_FPSDISP:
			::CheckMenuItem( hMenu, uID, MF_BYCOMMAND|(Config.graphics.bFPSDisp?MF_CHECKED:MF_UNCHECKED) );
			break;
		case	ID_TVFRAME:
			::CheckMenuItem( hMenu, uID, MF_BYCOMMAND|(Config.graphics.bTVFrame?MF_CHECKED:MF_UNCHECKED) );
			break;

		case	ID_CFG_GAMEOPTION:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_SEARCH:
		case	ID_CHEAT:
		case	ID_CHEAT_ENABLE:
		case	ID_CHEAT_DISABLE:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;
		case	ID_GENIE:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_VIEW_PATTERN:
		case	ID_VIEW_NAMETABLE:
		case	ID_VIEW_PALETTE:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;

		case	ID_VIEW_MEMORY:
		case	ID_VIEW_WATCH:
			::EnableMenuItem( hMenu, uID, MF_BYCOMMAND|(bEmu?MF_ENABLED:MF_GRAYED) );
			break;

		default:
			break;
	}
}

void	CMainFrame::OnKeyControl()
{
BYTE	KeyBuf[256+64*8];

	// Timerイベントが重なる事があるのかどうかわからんがとりあえず
	if( m_bKeyChecking )
		return;

	m_bKeyChecking = TRUE;

	// Keyの取得
	if( !Emu.IsRunning() ) {
		// Emulation中以外はPollingする
		DirectInput.Poll();
	}

	// トリガ＆リピート生成
	BYTE*	pSw  = (BYTE*)DirectInput.m_Sw;
	BYTE*	pOld = (BYTE*)m_KeyBuf;
	BYTE*	pCnt = (BYTE*)m_KeyCnt;
	BYTE*	pKey = (BYTE*)KeyBuf;

	for( INT i = 0; i < 256+64*8; i++ ) {
		pKey[i] = (pSw[i]&0x80) & ~(pOld[i]&0x80);
		if( pKey[i] ) {
			pCnt[i] = 14;
		} else if( pCnt[i] != 0 && (pSw[i]&0x80) ) {
			if( --pCnt[i] == 0 ) {
				pKey[i] = pSw[i]&0x80;
				pCnt[i] = 5;
			} else {
				pKey[i] = 0;
			}
		}
	}
	::memcpy( m_KeyBuf, DirectInput.m_Sw, sizeof(m_KeyBuf) );

	// イベント発信
	BOOL	bAltOnly = FALSE;
	if( Emu.IsRunning() ) {
		// ファミリーベーシックKeyBoardの時
		if( Emu.GetExController() == PAD::EXCONTROLLER_KEYBOARD )
			bAltOnly = TRUE;
		if( Emu.IsPausing() )
			bAltOnly = FALSE;
	}

	WORD	keyex = 0;
	if( DirectInput.m_Sw[DIK_LMENU] || DirectInput.m_Sw[DIK_RMENU] )
		keyex = CCfgShortCut::K_ALT;
	if( DirectInput.m_Sw[DIK_LCONTROL] || DirectInput.m_Sw[DIK_RCONTROL] )
		keyex = CCfgShortCut::K_CTRL;
	if( DirectInput.m_Sw[DIK_LSHIFT] || DirectInput.m_Sw[DIK_RSHIFT] )
		keyex = CCfgShortCut::K_SHIFT;

	WORD*	pShortCutKey = Config.shortcut.nShortCut;
	INT*	pShortCutKeyID = Config.ShortcutKeyID;

	if( bAltOnly ) {
		INT	no;
		WORD	key, key2;
		for( INT i = 0; pShortCutKeyID[i*3+0]; i++ ) {
			no = pShortCutKeyID[i*3+2];
			key = pShortCutKey[no];
			key2 = pShortCutKey[no+128];

			if( (key & 0xF000) == CCfgShortCut::K_ALT && keyex == CCfgShortCut::K_ALT && KeyBuf[key&0x0FFF] && (key&0x0FFF) ) {
				::PostMessage( m_hWnd, WM_COMMAND, (WPARAM)pShortCutKeyID[i*3+0], (LPARAM)0 );
			}
			if( (key2 & 0xF000) == CCfgShortCut::K_ALT && keyex == CCfgShortCut::K_ALT && KeyBuf[key2&0x0FFF] && (key2&0x0FFF) ) {
				::PostMessage( m_hWnd, WM_COMMAND, (WPARAM)pShortCutKeyID[i*3+0], (LPARAM)0 );
			}
		}
	} else {
		INT	no;
		WORD	key, key2;
		for( INT i = 0; pShortCutKeyID[i*3+0]; i++ ) {
			no = pShortCutKeyID[i*3+2];
			key = pShortCutKey[no];
			key2 = pShortCutKey[no+128];
			if( (key & 0xF000) == keyex && KeyBuf[key&0x0FFF] && (key&0x0FFF) ) {
				::PostMessage( m_hWnd, WM_COMMAND, (WPARAM)pShortCutKeyID[i*3+0], (LPARAM)0 );
			}
			if( (key2 & 0xF000) == keyex && KeyBuf[key2&0x0FFF] && (key2&0x0FFF) ) {
				::PostMessage( m_hWnd, WM_COMMAND, (WPARAM)pShortCutKeyID[i*3+0], (LPARAM)0 );
			}
		}
	}

	m_bKeyChecking = FALSE;
}

WNDCMD	CMainFrame::OnOnTop( WNDCMDPARAM )
{
	HMENU m_menu = GetMenu(m_hWnd);
	UINT state = GetMenuState(m_menu, 60000, MF_BYCOMMAND);
	if(state == MF_CHECKED)
	{
		m_OnTop = 0;
		SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		CheckMenuItem(m_menu, 60000, MF_BYCOMMAND|MF_UNCHECKED);
	}
	else if(state == MF_UNCHECKED)
	{
		m_OnTop = 1;
		SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		CheckMenuItem(m_menu, 60000, MF_BYCOMMAND|MF_CHECKED);
	}
}

