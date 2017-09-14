//--------------------------------------------------------------------//
//                ���ߣ�������                                        //
//                �鼮�������簲ȫ��̼�����ʵ����                    //
//--------------------------------------------------------------------// 
// ParameterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocolanalysis.h"
#include "ParameterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CParameterDlg dialog
extern bool gSaveDumpFile;
extern bool gShowPacketData;
CParameterDlg::CParameterDlg(CWnd* pParent /*=NULL*/)
: CDialog(CParameterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameterDlg)
	m_bSaveDumpFile = FALSE;
	m_bShowPacketData = TRUE;
	//}}AFX_DATA_INIT
}
void CParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterDlg)
	DDX_Check(pDX, IDC_CHECK_SAVE_DUMP_FILE, m_bSaveDumpFile);
	DDX_Check(pDX, IDC_CHECK_SHOW_PACKET_DATA, m_bShowPacketData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameterDlg, CDialog)
//{{AFX_MSG_MAP(CParameterDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterDlg message handlers

void CParameterDlg::OnOK() 
{
	UpdateData(TRUE);
	gSaveDumpFile=m_bSaveDumpFile;
	gShowPacketData=m_bShowPacketData;
	if((gSaveDumpFile==false)&&(gShowPacketData==false))
	{
		MessageBox("��ѡ������һ������ʽ��","����Э�����ϵͳ�����簲ȫ��̼�����ʵ���������ߣ������Σ�");
		return ;
	}
	CDialog::OnOK();
}


