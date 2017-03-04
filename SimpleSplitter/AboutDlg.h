#if !defined(AFX_ABOUTDLG_H__63CA7D4F_09C0_40D0_AA18_A9E53E7FD7A6__INCLUDED_)
#define AFX_ABOUTDLG_H__63CA7D4F_09C0_40D0_AA18_A9E53E7FD7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// AboutDlg ダイアログ

class AboutDlg : public CDialog
{
// コンストラクション
public:
	AboutDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(AboutDlg)
	enum { IDD = IDD_DIALOG1 };
	BOOL	m_sameFolder;
	BOOL	m_deleteOriginal;
	BOOL	m_sharpAsSN;
	int		m_nDigits;
	int		m_ixToStart;
	BOOL	m_HoldLastCount;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(AboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(AboutDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ABOUTDLG_H__63CA7D4F_09C0_40D0_AA18_A9E53E7FD7A6__INCLUDED_)
