// SimpleSplitter.h : SIMPLESPLITTER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SIMPLESPLITTER_H__F14AD93D_1C2C_4027_BD7F_2105D9B7F592__INCLUDED_)
#define AFX_SIMPLESPLITTER_H__F14AD93D_1C2C_4027_BD7F_2105D9B7F592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��


/////////////////////////////////////////////////////////////////////////////
// CSimpleSplitterApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� SimpleSplitter.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSimpleSplitterApp : public CWinApp
{
public:
	CSimpleSplitterApp();
	static CString pluginName;
	static CString internalPluginName;
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSimpleSplitterApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSimpleSplitterApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SIMPLESPLITTER_H__F14AD93D_1C2C_4027_BD7F_2105D9B7F592__INCLUDED_)
