//
// バージョンダイアログクラス
//
//
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include <string>
using namespace std;

#include "VirtuaNESres.h"
#include "App.h"
#include "Pathlib.h"

#include "Wnd.h"
#include "AboutDlg.h"
#include "resource.h"

DLG_MESSAGE_BEGIN(CAboutDlg)
DLG_ON_MESSAGE( WM_INITDIALOG,	OnInitDialog )

DLG_COMMAND_BEGIN()
DLG_ON_COMMAND( IDOK, OnOK )
DLG_ON_COMMAND( IDCANCEL, OnCancel )
DLG_ON_COMMAND( IDC_VER_WEBSITE, OnWebsite )
DLG_COMMAND_END()
DLG_MESSAGE_END()

INT	CAboutDlg::DoModal( HWND hWndParent )
{
	return	::DialogBoxParam( CApp::GetPlugin(), MAKEINTRESOURCE(IDD_VERSION),
				hWndParent, g_DlgProc, (LPARAM)this );
}

DLGMSG	CAboutDlg::OnInitDialog( DLGMSGPARAM )
{

	::SendDlgItemMessage( m_hWnd, IDC_VER_ICON, STM_SETICON,
			      (WPARAM)CApp::LoadIcon( IDI_ICON ), 0 );
	::SendDlgItemMessage( m_hWnd, IDC_KF, STM_SETICON,
			      (WPARAM)CApp::LoadIcon( IDI_KF ), 0 );
	::SendDlgItemMessage( m_hWnd, IDC_WOLF, STM_SETICON,
			      (WPARAM)CApp::LoadIcon( IDI_WOLF ), 0 );
	::SendDlgItemMessage( m_hWnd, IDC_PP, STM_SETICON,
			      (WPARAM)CApp::LoadIcon( IDI_P ), 0 );

	TCHAR	str[256];

	::wsprintf( str, "VirtuaNES version %01d.%01d%01d",
		    (VIRTUANES_VERSION&0xF00)>>8,
		    (VIRTUANES_VERSION&0x0F0)>>4,
		    (VIRTUANES_VERSION&0x00F) );
	::SetDlgItemText( m_hWnd, IDC_VER_VERSION, str );

	m_Website.Attach( ::GetDlgItem( m_hWnd, IDC_VER_WEBSITE ), VIRTUANES_WEBSITE );
	m_Email.Attach( ::GetDlgItem( m_hWnd, IDC_VER_EMAIL ), "pinokio@sina.com", "mailto:pinokio@sina.com" );

	return	TRUE;
}

DLGCMD	CAboutDlg::OnOK( DLGCMDPARAM )
{
	::EndDialog( m_hWnd, IDOK );
}

DLGCMD	CAboutDlg::OnCancel( DLGCMDPARAM )
{
	::EndDialog( m_hWnd, IDCANCEL );
}

DLGCMD	CAboutDlg::OnWebsite( DLGCMDPARAM )
{
	::ShellExecute( HWND_DESKTOP, "open", VIRTUANES_WEBSITE, NULL, NULL, SW_SHOWNORMAL );
//	::ShellExecute( m_hWnd, "open", VIRTUANES_WEBSITE, NULL, NULL, SW_SHOWNORMAL );
}

