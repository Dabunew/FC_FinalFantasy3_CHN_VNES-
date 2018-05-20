#define	INITGUID
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <crtdbg.h>

#include <string>
using namespace std;

#include "VirtuaNESres.h"

#include "App.h"
#include "Registry.h"
#include "Pathlib.h"
#include "MMTimer.h"

#include "Wnd.h"
#include "WndHook.h"
#include "MainFrame.h"
#include "Config.h"

#include "DirectDraw.h"
#include "DirectSound.h"
#include "DirectInput.h"

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow )
{
	// Main Frame Window Object
	CMainFrame	MainFrame;

	// Mutex
	HANDLE	hMutex = NULL;

	CApp::LoadErrorString();

	// Application Instance等の設定
	CHAR	szPath[ _MAX_PATH ];
	GetModuleFileName( hInstance, szPath, sizeof(szPath) );
	string	ModulePath = CPathlib::SplitPath( szPath );
	CApp::SetModulePath( ModulePath.c_str() );

	CApp::SetInstance( hInstance );
	CApp::SetPrevInstance( hPrevInstance );
	CApp::SetCmdLine( lpCmdLine );
	CApp::SetCmdShow( nCmdShow );

	CRegistry::SetRegistryKey( CApp::GetErrorString(9) );


	::InitCommonControls();

	// 設定のロード
	CRegistry::SetRegistryKey( CApp::GetErrorString(9) );
	Config.Load();

	// 二重起動の防止
	hMutex = ::CreateMutex( NULL, FALSE, VIRTUANES_MUTEX );
	if( ::GetLastError() == ERROR_ALREADY_EXISTS ) {
		::CloseHandle( hMutex );
		if( Config.general.bDoubleExecute ) {
			HWND	hWnd = ::FindWindow( VIRTUANES_WNDCLASS, VIRTUANES_CAPTION );

			// 起動していた方をForegroundにする
			::SetForegroundWindow( hWnd );

			// Command Line引数があるなら動作中のVirtuaNESのWindowにFile名
			// Messageジを送りつけてそちらで動作させる
			// (当然の様に対応Partionでないとダメ)
			if( ::strlen( lpCmdLine ) > 0 ) {
				LPSTR	pCmd = lpCmdLine;
				if( lpCmdLine[0] == '"' ) {	// Shell execute!!
					lpCmdLine++;
					if( lpCmdLine[::strlen( lpCmdLine )-1] == '"' ) {
						lpCmdLine[::strlen( lpCmdLine )-1] = '\0';
					}
				}

				COPYDATASTRUCT	cds;
				cds.dwData = 0;
				cds.lpData = (void*)lpCmdLine;
				cds.cbData = ::strlen(lpCmdLine)+1; //  終端のNULLも送る
				//  文字列送信
				::SendMessage( hWnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds );
			}

			// 終了
			goto	_DoubleExecute_Exit;
		}
	}

	if( !MainFrame.Create(NULL) )
		goto	_Error_Exit;

	// Main Windowの表示
	::ShowWindow( CApp::GetHWnd(), CApp::GetCmdShow() );
	::UpdateWindow( CApp::GetHWnd() );

	// Hook
	CWndHook::Initialize();

	// Command Line
	if( ::strlen( lpCmdLine ) > 0 ) {
		LPSTR	pCmd = lpCmdLine;
		if( lpCmdLine[0] == '"' ) {	// Shell execute!!
			lpCmdLine++;
			if( lpCmdLine[::strlen( lpCmdLine )-1] == '"' ) {
				lpCmdLine[::strlen( lpCmdLine )-1] = '\0';
			}
		}
	}

	if( ::strlen( lpCmdLine ) > 0 ) {
		::PostMessage( CApp::GetHWnd(), WM_VNS_COMMANDLINE, 0, (LPARAM)lpCmdLine );
	}

	MSG	msg;
	while( ::GetMessage( &msg, NULL, 0, 0 ) ) {
		// Main WindowのMessage Filtering
		if( CApp::GetHWnd() == msg.hwnd ) {
			CWnd* pWnd = (CWnd*)::GetWindowLong( msg.hwnd, GWL_USERDATA );
			if( pWnd ) {
				if( pWnd->PreTranslateMessage( &msg ) )
					continue;
			}
		}
		if( CWndList::IsDialogMessage( &msg ) )
			continue;
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}
	// Hook
	CWndHook::Release();

	// 設定の保存
	CRegistry::SetRegistryKey( CApp::GetErrorString(9) );
	Config.Save();

	// DirectX系破棄
	DirectDraw.ReleaseDDraw();
	DirectSound.ReleaseDSound();
	DirectInput.ReleaseDInput();

	if( hMutex )
		::ReleaseMutex( hMutex );
	CLOSEHANDLE( hMutex );

_DoubleExecute_Exit:
	::FreeLibrary( CApp::GetPlugin() );

	return	msg.wParam;

_Error_Exit:
	// DirectX系破棄
	DirectDraw.ReleaseDDraw();
	DirectSound.ReleaseDSound();
	DirectInput.ReleaseDInput();

	if( CApp::GetPlugin() ) {
		::FreeLibrary( CApp::GetPlugin() );
	}

	return	-1;
}

