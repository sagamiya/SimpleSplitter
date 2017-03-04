/*
MIT License

Copyright(c) 2002, 2005, 2017 sagamiya

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// SimpleSplitter.cpp : DLL �p�̏����������̒�`���s���܂��B
//

#include "stdafx.h"
#include "direct.h"
#include "SimpleSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	����!
//
//		���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ
//		�ǂ̊֐����֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE 
//		�}�N�����܂�ł��Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂�
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC 
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

/////////////////////////////////////////////////////////////////////////////
// CSimpleSplitterApp

BEGIN_MESSAGE_MAP(CSimpleSplitterApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpleSplitterApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleSplitterApp �̍\�z

CSimpleSplitterApp::CSimpleSplitterApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance �̒��̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSimpleSplitterApp �I�u�W�F�N�g

CSimpleSplitterApp theApp;

CString CSimpleSplitterApp::pluginName = CString("�ȈՕ�������");

CString CSimpleSplitterApp::internalPluginName = CString("�ȈՕ�������");

/* �ȍ~���v���O�C����SPI�̎����ł� */
#include <string.h>
#include "mpplugin.h"
#include "resource.h"
#include "xdw_api.h"
#include "xdwapian.h"
#include "aboutdlg.h"

#undef	XDW_COLOR_FUSEN_BLUE
#define	XDW_COLOR_FUSEN_BLUE	0xFFBF9D
#undef	XDW_COLOR_FUSEN_YELLOW
#define	XDW_COLOR_FUSEN_YELLOW	0x64FFFF
#undef	XDW_COLOR_FUSEN_LIME
#define XDW_COLOR_FUSEN_LIME	0xC2FF9D

class MyData {
public:
	DWORD	flags;
	DWORD	ixToStart;
	DWORD	nDigits;
	DWORD	ixCurrent;
	static const DWORD flagRemoveOriginal;
	static const DWORD flagAtSameFolder;
	static const DWORD flagSharpAsSN;
	static const DWORD flagHoldLastCount;
public:
	MyData() { flags = 0; ixToStart=1; nDigits=3; };
	bool SetMyData(CString instanceName);
	bool GetMyData(CString instanceName);
	void DeleteMyData(CString instanceName);

	bool GetHoldLastCount() {
		return (flags & flagHoldLastCount) != 0;
	}
	void SetHoldLastCount(BOOL atSameFolder) {
		if (atSameFolder) {
			flags |= flagHoldLastCount;
		} else {
			flags &= ~flagHoldLastCount;
		}
	}
	bool GetAtSameFolder() {
		return (flags & flagAtSameFolder) != 0;
	}
	void SetAtSameFolder(BOOL atSameFolder) {
		if (atSameFolder) {
			flags |= flagAtSameFolder;
		} else {
			flags &= ~flagAtSameFolder;
		}
	}
	DWORD GetIxToStart() {
		return ixToStart;
	}
	void SetIxToStart(DWORD dword) {
		ixToStart = dword;
	}
	DWORD GetNDigits() {
		return nDigits;
	}
	void SetNDigits(DWORD dword) {
		nDigits = dword;
	}
	void ResetSN() {
		ixCurrent = ixToStart;
	}
	CString GetSN() {
		CString s;
		CString format;
		if (nDigits==0) {
			format = "%d";
		} else {
			format.Format("%%0%dd",nDigits);
		}
		s.Format(format, ixCurrent);
		ixCurrent++;
		if (GetHoldLastCount()) {
			ixToStart = ixCurrent;
		}
		return s;
	}

	bool GetRemoveOriginal() {
		return (flags & flagRemoveOriginal) != 0;
	}
	void SetRemoveOriginal(BOOL remove) {
		if (remove) {
			flags |= flagRemoveOriginal;
		} else {
			flags &= ~flagRemoveOriginal;
		}
	}
	bool GetSharpAsSN() {
		return (flags & flagSharpAsSN) != 0;
	}
	void SetSharpAsSN(BOOL sharpAsSN) {
		if (sharpAsSN) {
			flags |= flagSharpAsSN;
		} else {
			flags &= ~flagSharpAsSN;
		}
	}
};

const DWORD MyData::flagRemoveOriginal = 1;
const DWORD MyData::flagAtSameFolder = 2;
const DWORD MyData::flagSharpAsSN = 4;
const DWORD MyData::flagHoldLastCount = 8;

MyData mydata;

void print_error(int code)
{
	switch (code) {
	case XDW_E_NOT_INSTALLED:
		AfxMessageBox("DocuWorks���C���X�g�[������Ă��܂���B");
		break;
	case XDW_E_FILE_NOT_FOUND:
		AfxMessageBox("�w�肳�ꂽ�t�@�C����������܂���B");
		break;
	case XDW_E_FILE_EXISTS:
		AfxMessageBox("�w�肳�ꂽ�t�@�C���͂��łɑ��݂��܂��B");
		break;
	case XDW_E_ACCESSDENIED:
	case XDW_E_INVALID_NAME:
	case XDW_E_BAD_NETPATH:
		AfxMessageBox("�w�肳�ꂽ�t�@�C�����J�����Ƃ��ł��܂���B");
		break;
	case XDW_E_BAD_FORMAT:
		AfxMessageBox("�w�肳�ꂽ�t�@�C���͐������t�H�[�}�b�g�ł͂���܂���B");
		break;
	case XDW_E_INVALID_ACCESS:
		AfxMessageBox("�w�肳�ꂽ��������錠��������܂���B");
		break;
	default:
		AfxMessageBox("�G���[���������܂����B");
		break;
	}
}


bool RemoveLimeFusen(XDW_DOCUMENT_HANDLE fascicle) {
	bool ok = false;
	int		j;
	XDW_PAGE_INFO	pageInfo;
	pageInfo.nSize = sizeof XDW_PAGE_INFO;
	int api_result = XDW_GetPageInformation( fascicle, 1, &pageInfo);
	if (api_result < 0 ) {
		print_error(api_result);
		goto exit_all;
	}
	for (j=1; j<= pageInfo.nAnnotations; j++) {
		XDW_ANNOTATION_INFO annotationInfo;
		annotationInfo.nSize = sizeof annotationInfo;
		api_result = XDW_GetAnnotationInformation(fascicle, 1, NULL, j, &annotationInfo, NULL);
		if (api_result < 0 ) {
			print_error(api_result);
			goto exit_all;
		}
		if (annotationInfo.nAnnotationType == XDW_AID_FUSEN) {
			const int sizeOfValue = sizeof ( int );
			int		value;
			api_result = XDW_GetAnnotationAttribute(annotationInfo.handle, XDW_ATN_FillColor, (char *)(&value), sizeOfValue, NULL);
			if (value == XDW_COLOR_FUSEN_LIME) {
				api_result = XDW_RemoveAnnotation(fascicle, annotationInfo.handle, NULL);
				if (api_result < 0) {
					goto exit_all;
				}
				ok = true;
				break;
			}
		}
	}
exit_all:
	return ok;
}

char * TmpFileName(const char *folder) {
//	return CString( tmpnam((char *)folder) );
	return _tempnam(folder,"tmp");
}

CString trim(CString s) {
	s.TrimLeft();
	s.TrimRight(); // �O��̉��s��󔒂��폜
	s.Replace('\t',' ');
	s.Remove('\r');
	s.Remove('\n');
	return s;
}

bool DoSplit (const char *path, const char *folder, MyData * mydata) {
	int api_result = 0;
	bool ok = false;

	XDW_DOCUMENT_HANDLE fascicle = NULL;
	int		fascicleLastPage = 0;

	//char * tmpFileName = "C:\\temp\\tmp.xdw";
	char * tmpFileName = TmpFileName(folder);

	XDW_DOCUMENT_HANDLE h = NULL;
	XDW_OPEN_MODE_EX mode = {
		sizeof(XDW_OPEN_MODE_EX), XDW_OPEN_READONLY, XDW_AUTH_NODIALOGUE };
	api_result = XDW_OpenDocumentHandle(path, &h, (XDW_OPEN_MODE*)&mode);
	if (api_result < 0) {
		print_error(api_result);
		AfxMessageBox("Unexpected error: �I�����ꂽ�������J���܂���ł����B");
		return false;
	}

	// XDW_GetDocumentInformation��p���đ��y�[�W���𓾂�
	XDW_DOCUMENT_INFO info = { sizeof(XDW_DOCUMENT_INFO), 0, 0, 0 };
	XDW_GetDocumentInformation(h, &info);
	int last_page = info.nPages;
	XDW_PAGE_INFO	pageInfo;
	pageInfo.nSize = sizeof XDW_PAGE_INFO;

	for (int page=1; page <= last_page; page++) {
		bool	splitHere = false;
		CString	fname;

		api_result = XDW_GetPageInformation( h, page, &pageInfo);
		if (api_result < 0 ) {
			print_error(api_result);
			goto exit_all;
		}
		for (int j=1; j<= pageInfo.nAnnotations; j++) {
			XDW_ANNOTATION_INFO annotationInfo;
			annotationInfo.nSize = sizeof annotationInfo;
			api_result = XDW_GetAnnotationInformation(h, page, NULL, j, &annotationInfo, NULL);
			if (api_result < 0 ) {
				print_error(api_result);
				goto exit_all;
			}
			if (annotationInfo.nAnnotationType == XDW_AID_FUSEN) {
				const int sizeOfValue = sizeof ( int );
				int		value;
				api_result = XDW_GetAnnotationAttribute(annotationInfo.handle, XDW_ATN_FillColor, (char *)(&value), sizeOfValue, NULL);
				if (value == XDW_COLOR_FUSEN_LIME) {
					if (annotationInfo.nChildAnnotations > 0) {
						XDW_ANNOTATION_INFO yaAnnotationInfo;
						yaAnnotationInfo.nSize = sizeof annotationInfo;
						api_result = XDW_GetAnnotationInformation(h, page, annotationInfo.handle, 1, &yaAnnotationInfo, NULL);
						if (api_result < 0 ) {
							print_error(api_result);
							goto exit_all;
						}
						int sizeNeeded;
						char	buff[1024];
						sizeNeeded = XDW_GetAnnotationAttribute(yaAnnotationInfo.handle, XDW_ATN_Text, buff, 1024, NULL);
						fname = CString(buff);
						fname = trim(fname);
						if (mydata->GetSharpAsSN()) {
							CString sn = mydata->GetSN();
							int ixSharp = fname.Find('#');
							if (ixSharp>=0) {
								fname = fname.Left(ixSharp) + sn + fname.Right(fname.GetLength()-ixSharp-1);
							}
						}
					} else {
						fname.Empty();
					}
					splitHere = true;
					break;
				}
				/*
				CString msg;
				msg.Format("nChildAttribute = %d", annotationInfo.nChildAnnotations);
				AfxMessageBox(msg);
				*/
			}
		}
		if (splitHere) {
			if (fascicle!= NULL) {
				api_result =  XDW_SaveDocument (fascicle, NULL); 
				if (api_result < 0 ) {
					print_error(api_result);
					goto exit_all;
				}
				XDW_CloseDocumentHandle(fascicle, NULL);
				fascicle = NULL;
				fascicleLastPage = 0;
			}
			if (!fname.IsEmpty()){
				api_result =  XDW_GetPage(h, page, (LPCSTR)(CString(folder)+"\\"+fname+".xdw"), NULL);
				if (api_result < 0 ) {
					print_error(api_result);
					AfxMessageBox(CString("Unexpected error: �tⳂ̕t�����y�[�W���A")+CString(folder)+"\\"+fname+".xdw"+"�Ƃ������O�Ŏ��o���̂Ɏ��s.");
					goto exit_all;
				}
				XDW_OPEN_MODE_EX updateMode = {
					sizeof(XDW_OPEN_MODE_EX), XDW_OPEN_UPDATE, XDW_AUTH_NODIALOGUE };
				api_result = XDW_OpenDocumentHandle((LPCSTR)(CString(folder)+"\\"+fname+".xdw"), &fascicle, (XDW_OPEN_MODE*)&updateMode);
				if (api_result < 0 ) {
					print_error(api_result);
					AfxMessageBox("Unexpected error: �tⳂ̕t�����y�[�W�����o�����t�@�C�����J���̂Ɏ��s�B");
					goto exit_all;
				}
				fascicleLastPage = 1;
				if (!RemoveLimeFusen(fascicle)) {
					AfxMessageBox("Unexpected error: �tⳂ̍폜�Ɏ��s");
					goto exit_all;
				};
			} else {
				// �ǂݎ̂ĊJ�n
			}
			splitHere = false;
		} else {
			if (fascicle!= NULL) {
				api_result =  XDW_GetPage(h, page, CString(tmpFileName)+".xdw", NULL);
				if (api_result < 0 ) {
					AfxMessageBox("Unexpected error: failed to get page.");
					print_error(api_result);
					goto exit_all;
				}
				api_result =  XDW_InsertDocument(fascicle, fascicleLastPage+1, CString(tmpFileName)+".xdw", NULL);
				if (api_result < 0 ) {
					AfxMessageBox("Unexpected error: failed to insert document.");
					print_error(api_result);
					goto exit_all;
				}
				fascicleLastPage++;
				CFile::Remove(CString(tmpFileName)+".xdw");
			}
		}
	}
	ok = true; // �����܂ŗ���Έꉞ�����B
exit_all:
	if (fascicle!= NULL) {
		api_result =  XDW_SaveDocument (fascicle, NULL); 
		if (api_result < 0 ) {
			print_error(api_result);
			ok = false;  // �ł��A�Ō��fascicle�����Ȃ���Ύ��s.
		}
		XDW_CloseDocumentHandle(fascicle, NULL);
	}
	XDW_CloseDocumentHandle(h, NULL);
	free(tmpFileName);
	return ok;
}

void RemoveOriginal(const char *fullpath) {
	char * pFrom = new char[strlen(fullpath)+2];
	strcpy(pFrom, fullpath);
	pFrom[strlen(fullpath)+1]=0; // pFrom �́AC������̘A���Ȃ̂ŁA00�Ń^�[�~�l�[�g����B

	// SHFILEOPSTRUCT �\���̃����o�̒l��ݒ�
	SHFILEOPSTRUCT FileOp;
	FileOp.hwnd = NULL; //hDlg;
	FileOp.wFunc = FO_DELETE;
	FileOp.pFrom = pFrom;
	FileOp.pTo = NULL; // pTo is ignored.
	FileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	FileOp.fAnyOperationsAborted = FALSE;
	FileOp.hNameMappings = NULL;
	FileOp.lpszProgressTitle = NULL;

	// �t�@�C�����폜
	SHFileOperation( &FileOp );
}

bool DoIt (const char *fullpath, MyData *mydata) {
	bool atSameFolder = mydata->GetAtSameFolder();
	int api_result = 0;
	bool ok;

    char ext[MAX_PATH];
    char fname[MAX_PATH];
    _splitpath(fullpath, NULL, NULL, fname, ext);
    
	CString foldername;
	if (!atSameFolder) {
		foldername = CString(fullpath).Left( CString(fullpath).GetLength() - CString(ext).GetLength() );

		if (_mkdir(foldername)<0) {
				AfxMessageBox(CString(fname)+"�Ƃ������O�̃t�H���_�̍쐬�Ɏ��s�����̂ŃX�L�b�v���܂��B���ɓ������O�̃t�H���_�����݂��Ă��܂��񂩁B");
			return false;
		}
	} else {
		foldername = CString(fullpath).Left( CString(fullpath).GetLength() - CString(fname).GetLength()- CString(ext).GetLength() );
	}
	if (!mydata->GetHoldLastCount()) {
		mydata->ResetSN();
	}
	ok = DoSplit(fullpath, foldername, mydata);
	if (ok && mydata->GetRemoveOriginal()) {
		RemoveOriginal(fullpath);
	}
	return ok;
}


PLUGGEDIN_EXPORT( long ) PLG_ExecuteCommand(PLUGGEDIN_STRUCT *ps)
{
    /* ���̃R�}���h���s�̓r���A�����Ƃ��ēn�����DW�t�@�C���͊J������Ă��܂��B
       �ǂݏ����\�ŃA�N�Z�X�ł��܂��B
    */
    /* MFC���g�p����ꍇ�AAFX_MANAGE_STATE( AfxGetStaticModuleState() );��
       �K���R�[�����Ă��������B����ɂ��A����DLL�̃��\�[�X���g����悤�ɂȂ�܂��B
    */
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

//	if (strcmp(ps->ps_pszFunction, "�ȈՕ�������"))
//		return 0;

	MyData mydata;
	mydata.GetMyData(ps->ps_pszFunction);

    char *buf=NULL;
    char *tmp1=NULL;
    char *path=NULL;

    buf=new char[32+(MAX_PATH * ps->ps_nFiles)];
    tmp1=new char[MAX_PATH];
    path=new char[MAX_PATH];
    strcpy(buf,"Arg files:");
	if ( ps->ps_nFiles > 0 ) {
		for (int i=0; i<ps->ps_nFiles; i++) {
			DoIt(ps->ps_pszFiles[i], &mydata);
		}
		AfxMessageBox("Done.");
	} else {
		AfxMessageBox("�t�@�C�������������񂾗ΐF�̕tⳂŐ؂�o���ʒu���w�肵��������I�����Ă��������B");
	}
	if (mydata.GetHoldLastCount()) {
		mydata.SetMyData(ps->ps_pszFunction);
	}
    delete buf;
    delete tmp1;
    delete path;
    return 1;
}

/* EnumerateCommands Entry */
PLUGGEDIN_EXPORT( long ) PLG_EnumerateCommands(char* pszEntries, long nBufSize, long* pnRealSize)
{
    // Check buffer size is large enough
    /* *pnRealSize�ɕK�v�ȃo�b�t�@�T�C�Y�����Ă������� */
    *pnRealSize=strlen("�ȈՕ�������")+1;

    if (nBufSize<*pnRealSize)
        return 0;

    /* nBufSize���K�v�ȃo�b�t�@�T�C�Y�𒴂��Ă���ꍇ�̂݁ApszEntries�ɃR�s�[��
       �����������Ƃ����� return 1��Ԃ��Ă�������
    */

    /*
     0�^�[�~�l�[�g�̕�����̃��X�g��Ԃ��Ă��������BDWDesk�̃v���O�C��/�ݒ�̌��ɏo�܂�
    */
   // DoCopy Commands!
    strcpy(pszEntries, "�ȈՕ�������");
	return 1;
}

PLUGGEDIN_EXPORT( long ) PLG_Executable(const char *pszFunction, long nSel)
{
    //�I���t�@�C���̐� nSel�ɉ����Ď��s�\����Ԃ��Ă�������
	if (nSel>0) {
		return 1;
	} else {
		return 0;
	}
}
PLUGGEDIN_EXPORT( long ) PLG_RequireFiles(const char *pszFunction)
{
    // 0��Ԃ��ƁA�t�@�C���I����Ԃɂ�炸�����͓n����܂���
	return 1;
}

PLUGGEDIN_EXPORT( HICON ) PLG_GetCommandIcon(const char *pszFunction, long bNormal)
{
    /* ��ɑ傫��(32x32 or 24x24)�A�C�R���ł����܂��܂��� */

	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	HICON hIcon=NULL;
	unsigned resID=0;
	if (CString(pszFunction).Left(theApp.internalPluginName.GetLength()) == theApp.internalPluginName) {
		resID= IDI_APPICON1;
	} else return 0;

	HINSTANCE myInst = (HINSTANCE) AfxGetInstanceHandle();
	if (bNormal)
		hIcon=LoadIcon(myInst,MAKEINTRESOURCE(resID));
	else
		hIcon=(HICON)LoadImage(myInst,MAKEINTRESOURCE(resID),IMAGE_ICON,16,16,0);
	return hIcon;
}

/* Followin SPI s  are NO-op */

PLUGGEDIN_EXPORT( long ) PLG_Initialize(const char* cmd)
{
    /* �K�� 1��Ԃ��Ă�������. 0��Ԃ��ƃv���O�C�������[�h����܂���*/
	return 1;
}

PLUGGEDIN_EXPORT( long ) PLG_Finalize(const char*  cmd)
{
	return 1;
}

PLUGGEDIN_EXPORT( long ) PLG_CanFinalize(const char*  cmd)
{
	return 1;
}

/*
    IsCloningCommand/CanSetProfile�� 0�ȊO��Ԃ��ƁA
    GetNewClone / SetProfile���R�[������܂�

*/

PLUGGEDIN_EXPORT( long ) PLG_IsParallel(const char *pszFunction)
{
    /* v2.0�ł͂���SPI�͖�������܂� */
	return 0;
}


PLUGGEDIN_EXPORT( long ) PLG_CanSetProfile(const char *pszFunction)
{
    /* SetProfile��L���ɂ���ꍇ�A������1��Ԃ��Ă������� */
	return 1;
}

PLUGGEDIN_EXPORT( long ) PLG_SetProfile(const char *pszFunction)
{
    /* ������GUI���o���Ď��g�̐ݒ���s���Ă������� */
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	MyData mydata;
	mydata.GetMyData(pszFunction);
	AboutDlg dlg;

	dlg.m_deleteOriginal = mydata.GetRemoveOriginal();
	dlg.m_sameFolder = mydata.GetAtSameFolder();
	dlg.m_sharpAsSN = mydata.GetSharpAsSN();
	dlg.m_HoldLastCount = mydata.GetHoldLastCount();
	mydata.ResetSN();
	dlg.m_ixToStart = mydata.GetIxToStart();
	dlg.m_nDigits = mydata.GetNDigits();
	dlg.DoModal();

	mydata.SetRemoveOriginal(dlg.m_deleteOriginal);
	mydata.SetAtSameFolder(dlg.m_sameFolder);
	mydata.SetSharpAsSN(dlg.m_sharpAsSN);
	mydata.SetHoldLastCount(dlg.m_HoldLastCount);
	mydata.SetIxToStart(dlg.m_ixToStart);
	mydata.SetNDigits(dlg.m_nDigits);
	
	mydata.SetMyData(pszFunction);
	return 1;
}


/* IsCloning Entry*/
PLUGGEDIN_EXPORT( long ) PLG_IsCloningCommand(const char *pszFunction)
{
    /* ����@�\�ŕ����̐ݒ��ۑ����ē��삳�������ꍇ�Ȃǂ́A����
       SPI�� 1 ��Ԃ��Ă�������
     */
    return 1;
}

/* GetNewClone Entry*/
PLUGGEDIN_EXPORT( long ) PLG_GetNewClone(char* pszNewClone, long bufsize)
{
    /* pszNewClone�Ƃ͈قȂ�����������쐬���ApszNewClone�����������ĕԂ��Ă������� */
    /* �Ⴆ�� "�v���O�C���@�\" -> "�v���O�C���@�\01","�v���O�C���@�\02"�Ȃ�
       �ȍ~�̃Z�b�V�����ł́A�N���[�����ꂽ�����񂪈���pszCommand�Ƃ��ēn����܂�
       �N���[�����Ƃɐݒ��ۑ����Ă��������B
       PLUGGEDIN_REGKEY\ �ȉ��̃��W�X�g���ɕۑ����ꂽ�f�[�^�́A
       Desk�̃v���O�C��/�ݒ�_�C�A���O�� OK ��������Ȃ�����A�ꊇ�L�����Z������܂�
     */  
	int i;
	MyData mydata;
	for (i=0; i<10; i++) {
		CString number, name;
		number.Format("%02d",i);
		name = theApp.internalPluginName+number;
		if (!mydata.GetMyData(name)) {
			if (mydata.SetMyData(name)) {
				::strcpy(pszNewClone, (LPCSTR)name);
				return 1;
			};
		}
	}
    return 0;
}

/* ReleaseClone Entry*/
PLUGGEDIN_EXPORT( long ) PLG_ReleaseClone(const char* pszClone)
{
    /* pszClone�Ŏw�肳�ꂽ�R�}���h���g�p���Ă����̈���J�����Ă������� */
	MyData mydata;
	mydata.DeleteMyData(CString(pszClone));
    return 1;
}

// MyData�̎���

bool MyData::SetMyData(CString instanceName) {
	HKEY subKey;
	LONG result;
	DWORD type = REG_DWORD;
	DWORD cbData= sizeof DWORD;
	result = RegCreateKeyEx(HKEY_CURRENT_USER,
				CString( PLUGGEDIN_REGKEY )+"\\"+theApp.internalPluginName+"\\"+instanceName,
				0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &subKey, NULL);
	if (result == ERROR_SUCCESS) {
		result = RegSetValueEx(subKey, "flags", NULL, type, (unsigned char *)&flags, cbData);
		if (result == ERROR_SUCCESS) {
			if (result == ERROR_SUCCESS) {
				result = RegSetValueEx(subKey, "ixToStart", NULL, type, (unsigned char *)&ixToStart, cbData);
				if (result == ERROR_SUCCESS) {
					result = RegSetValueEx(subKey, "nDigits", NULL, type, (unsigned char *)&nDigits, cbData);
				}
			}
		}
	}
	RegCloseKey(subKey);   
	return (result==ERROR_SUCCESS);
}

bool MyData::GetMyData(CString instanceName) {
	HKEY subKey;
	LONG result;
	DWORD type = REG_DWORD;
	DWORD cbData = sizeof DWORD;
	result = RegOpenKeyEx(HKEY_CURRENT_USER,
				CString( PLUGGEDIN_REGKEY )+"\\"+theApp.internalPluginName+"\\"+instanceName,
				0, KEY_READ, &subKey);
	if (result == ERROR_SUCCESS) {
		result = RegQueryValueEx(subKey,"flags", NULL, &type, (unsigned char *)&flags, &cbData);
		if (result == ERROR_SUCCESS) {
			result = RegQueryValueEx(subKey,"ixToStart", NULL, &type, (unsigned char *)&ixToStart, &cbData);
			if (result == ERROR_SUCCESS) {
				result = RegQueryValueEx(subKey,"nDigits", NULL, &type, (unsigned char *)&nDigits, &cbData);
			}
		}
	}
	RegCloseKey(subKey);
	ixCurrent = ixToStart;
	return (result==ERROR_SUCCESS);
}

void MyData::DeleteMyData(CString instanceName) {
	HKEY subKey;
	LONG result;
	DWORD cbData=0;
	result = RegOpenKeyEx(HKEY_CURRENT_USER,
				CString( PLUGGEDIN_REGKEY )+"\\"+theApp.internalPluginName+"\\"+instanceName,
				0, KEY_READ, &subKey);
	if (result == ERROR_SUCCESS) {
		result = RegDeleteValue(subKey, "flags");
		result = RegDeleteValue(subKey, "ixToStart");
		result = RegDeleteValue(subKey, "nDigits");
		RegCloseKey(subKey);
		result = RegDeleteKey(HKEY_CURRENT_USER, CString( PLUGGEDIN_REGKEY )+"\\"+theApp.internalPluginName+"\\"+instanceName);
	}
   
}