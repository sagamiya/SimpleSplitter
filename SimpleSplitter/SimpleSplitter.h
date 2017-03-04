// SimpleSplitter.h : SIMPLESPLITTER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SIMPLESPLITTER_H__F14AD93D_1C2C_4027_BD7F_2105D9B7F592__INCLUDED_)
#define AFX_SIMPLESPLITTER_H__F14AD93D_1C2C_4027_BD7F_2105D9B7F592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル


/////////////////////////////////////////////////////////////////////////////
// CSimpleSplitterApp
// このクラスの動作の定義に関しては SimpleSplitter.cpp ファイルを参照してください。
//

class CSimpleSplitterApp : public CWinApp
{
public:
	CSimpleSplitterApp();
	static CString pluginName;
	static CString internalPluginName;
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSimpleSplitterApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSimpleSplitterApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIMPLESPLITTER_H__F14AD93D_1C2C_4027_BD7F_2105D9B7F592__INCLUDED_)
