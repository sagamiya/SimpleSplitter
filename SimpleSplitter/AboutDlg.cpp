// AboutDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SimpleSplitter.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AboutDlg ダイアログ


AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AboutDlg)
	m_sameFolder = FALSE;
	m_deleteOriginal = FALSE;
	m_sharpAsSN = FALSE;
	m_nDigits = 0;
	m_ixToStart = 0;
	m_HoldLastCount = FALSE;
	//}}AFX_DATA_INIT
}


void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AboutDlg)
	DDX_Check(pDX, IDC_CHECK1, m_sameFolder);
	DDX_Check(pDX, IDC_CHECK2, m_deleteOriginal);
	DDX_Check(pDX, IDC_CHECK3, m_sharpAsSN);
	DDX_Text(pDX, IDC_EDIT2, m_nDigits);
	DDV_MinMaxInt(pDX, m_nDigits, 0, 10);
	DDX_Text(pDX, IDC_EDIT1, m_ixToStart);
	DDX_Check(pDX, IDC_CHECK4, m_HoldLastCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
	//{{AFX_MSG_MAP(AboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AboutDlg メッセージ ハンドラ

void AboutDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CDialog::OnOK();
}

