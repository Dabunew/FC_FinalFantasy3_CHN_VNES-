//
// ネットプレイダイアログクラス
//
#ifndef	__CNETPLAYDLG_INCLUDED__
#define	__CNETPLAYDLG_INCLUDED__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#include <string>
using namespace std;

#include "Wnd.h"

class	CNetPlayDlg : public CWnd
{
public:
	// Override from CWnd
	INT	DoModal( HWND hWndParent );

protected:
	void	SetStatusMessage( UINT uID );

	// Message map
	DLG_MESSAGE_MAP()
	DLGMSG		OnInitDialog( DLGMSGPARAM );
	DLGMSG		OnNetworkAccept( DLGMSGPARAM );
	DLGMSG		OnNetworkConnect( DLGMSGPARAM );
	DLGMSG		OnNetworkClose( DLGMSGPARAM );
	DLGMSG		OnNetworkError( DLGMSGPARAM );

	DLGCMD		OnServer( DLGCMDPARAM );
	DLGCMD		OnClient( DLGCMDPARAM );

	DLGCMD		OnConnect( DLGCMDPARAM );
	DLGCMD		OnCancel( DLGCMDPARAM );
	//

	HWND	m_hWndParent;
private:
};

#endif	// !__CNETPLAYDLG_INCLUDED__

