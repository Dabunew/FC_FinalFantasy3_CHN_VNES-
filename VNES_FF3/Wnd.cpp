//
// �ؤʤ��礳Window Class
//
#include "Wnd.h"

// Instance
CWndList	WndList;

list<CWnd*>	CWndList::m_WndPtrList;

// �������
CWndList::CWndList()
{
//	m_WndPtrList.clear();
}

CWndList::~CWndList()
{
//	if( !m_WndPtrList.empty() )
//		m_WndPtrList.clear();
}

void	CWndList::Add( CWnd* pWnd )
{
	m_WndPtrList.push_back( pWnd );
}

void	CWndList::Del( CWnd* pWnd )
{
	for( list<CWnd*>::iterator it=m_WndPtrList.begin(); it!=m_WndPtrList.end(); ) {
		if( *it == pWnd ) {
			m_WndPtrList.erase(it);
			break;
		} else {
			++it;
		}
	}
}

BOOL	CWndList::IsDialogMessage( LPMSG msg )
{
	if( m_WndPtrList.empty() )
		return	FALSE;

	list<CWnd*>::iterator it=m_WndPtrList.begin();
	while( it != m_WndPtrList.end() ) {
		if( ::IsDialogMessage( (*it)->m_hWnd, msg ) )
			return	TRUE;
		++it;
	}

	return	FALSE;
}

CWnd::CWnd()
{
	m_hWnd = NULL;
	m_hMenu = NULL;
}

CWnd::~CWnd()
{
}

void	CWnd::SetThis()
{
	// Dispatch������褦��CWnd*������z��
	if( m_hWnd ) {
		::SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );
	}
}

LRESULT	CALLBACK CWnd::g_WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// Window���_��ǰ�ˤ��ä���I����
	if( msg == WM_CREATE ) {
		LPCREATESTRUCT	lpcs = (LPCREATESTRUCT)lParam;
		CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );
		if( !pWnd ) {
			// CWnd* this������z��
			::SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpcs->lpCreateParams );
			// �Է֤�Window Handle
			pWnd = (CWnd*)lpcs->lpCreateParams;
			pWnd->m_hWnd = hWnd;
		}
	}
	// CWnd* this������z��Ǥ���
	CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );

	if( pWnd ) {
		return	pWnd->DispatchWnd( hWnd, msg, wParam, lParam );
	} else {
		return	::DefWindowProc(  hWnd, msg, wParam, lParam );
	}
}

BOOL	CALLBACK CWnd::g_DlgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// Dispatchǰ�ˤ��ä���I����
	if( msg == WM_INITDIALOG ) {
		// Dispatch������褦��CWnd*������z��(Model�ϱؤ�DialogBoxParam�����Ӥ�����)
		// CWnd* this������z��Ǥ��뤬��Model�Ǥ���äƤ��ʤ�
		CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );

		if( !pWnd ) {
			::SetWindowLong( hWnd, GWL_USERDATA, (LONG)lParam );
			pWnd = (CWnd*)lParam;
		}
		// �Է֤�Window Handle
		pWnd->m_hWnd = hWnd;

		// Dialog��������ƄӤ���:)
		HWND hWndParent = ::GetParent( hWnd );
		if( hWndParent ) {
			RECT	rcParent, rc;
			::GetWindowRect( hWndParent, &rcParent );
			::GetWindowRect( hWnd, &rc );
			INT x = rcParent.left+(rcParent.right-rcParent.left)/2-(rc.right-rc.left)/2;
			INT y = rcParent.top +(rcParent.bottom-rcParent.top)/2-(rc.bottom-rc.top)/2;
			::SetWindowPos( hWnd, NULL, x, y, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
		}
	}

	// CWnd* this������z��Ǥ���
	CWnd* pWnd = (CWnd*)::GetWindowLong( hWnd, GWL_USERDATA );

	if( pWnd ) {
		return	pWnd->DispatchDlg( hWnd, msg, wParam, lParam );
	} else {
		return	FALSE;
	}
}

