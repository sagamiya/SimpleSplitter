#if !defined(AFX_ABOUTDLG_H__63CA7D4F_09C0_40D0_AA18_A9E53E7FD7A6__INCLUDED_)
#define AFX_ABOUTDLG_H__63CA7D4F_09C0_40D0_AA18_A9E53E7FD7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// AboutDlg �_�C�A���O

class AboutDlg : public CDialog
{
// �R���X�g���N�V����
public:
	AboutDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(AboutDlg)
	enum { IDD = IDD_DIALOG1 };
	BOOL	m_sameFolder;
	BOOL	m_deleteOriginal;
	BOOL	m_sharpAsSN;
	int		m_nDigits;
	int		m_ixToStart;
	BOOL	m_HoldLastCount;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(AboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(AboutDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ABOUTDLG_H__63CA7D4F_09C0_40D0_AA18_A9E53E7FD7A6__INCLUDED_)
