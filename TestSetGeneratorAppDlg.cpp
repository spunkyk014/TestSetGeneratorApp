
// TestSetGeneratorAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestSetGeneratorApp.h"
#include "TestSetGeneratorAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestSetGeneratorAppDlg dialog



CTestSetGeneratorAppDlg::CTestSetGeneratorAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTSETGENERATORAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSetGeneratorAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_cb_shape);
	DDX_Control(pDX, IDC_LIST1, m_lb_side_lengths);
	DDX_Control(pDX, IDC_EDIT1, m_eb_side_length);
	DDX_Control(pDX, IDC_COMBO1, m_cb_quad_options);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_generate);
	DDX_Control(pDX, IDC_EDIT2, m_edit_pixel_width);
	DDX_Control(pDX, IDC_EDIT3, m_edit_pixel_height);
	DDX_Control(pDX, IDC_EDIT4, m_edit_rotation_range);
	DDX_Control(pDX, IDC_EDIT5, m_edit_rotation_increment);
	DDX_Control(pDX, IDC_LIST2, m_lb_side_thickness);
	DDX_Control(pDX, IDC_EDIT6, m_eb_side_thickness);
	DDX_Control(pDX, IDC_STATIC10, m_lbl_progress);
	DDX_Control(pDX, IDC_COMBO2, m_cb_tri_options);
}

BEGIN_MESSAGE_MAP(CTestSetGeneratorAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTestSetGeneratorAppDlg::OnLvnItemchangedList1)
	ON_EN_CHANGE(IDC_EDIT1, &CTestSetGeneratorAppDlg::OnEnChangeEdit1)
//	ON_EN_KILLFOCUS(IDC_EDIT1, &CTestSetGeneratorAppDlg::OnEnKillfocusEdit1)
//ON_WM_KILLFOCUS()
ON_CBN_SELCHANGE(IDC_COMBO, &CTestSetGeneratorAppDlg::OnCbnSelchangeCombo)
//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CTestSetGeneratorAppDlg::OnLvnColumnclickList1)
ON_CBN_SELCHANGE(IDC_COMBO1, &CTestSetGeneratorAppDlg::OnCbnSelchangeCombo1)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CTestSetGeneratorAppDlg::OnLvnItemchangedList2)
ON_EN_CHANGE(IDC_EDIT6, &CTestSetGeneratorAppDlg::OnEnChangeEdit6)
ON_BN_CLICKED(IDC_BUTTON1, &CTestSetGeneratorAppDlg::OnBnClickedButton1)
ON_CBN_SELCHANGE(IDC_COMBO2, &CTestSetGeneratorAppDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CTestSetGeneratorAppDlg message handlers

BOOL CTestSetGeneratorAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_cur_shape_select = -1;

	// TODO: Add extra initialization here
	InitSideListViews();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestSetGeneratorAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSetGeneratorAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSetGeneratorAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestSetGeneratorAppDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int row = pNMLV->iItem;

	if (row != m_cur_length_row_select)
	{
		m_cur_length_row_select = row;
		int cur_col_select = m_lb_side_lengths.GetSelectedColumn();

		CRect lv_rect;
		m_lb_side_lengths.GetWindowRect(lv_rect);
		ScreenToClient(lv_rect);
		CRect rect;
		m_lb_side_lengths.GetItemRect(row, &rect, LVIR_BOUNDS);
		int left = lv_rect.left + rect.left + 76;
		int top = lv_rect.top + rect.top;
		int height = rect.bottom - rect.top;

		CString	text;
		m_lb_side_lengths.SetSelectionMark(row);
		text = m_lb_side_lengths.GetItemText(row, 1);
		m_eb_side_length.MoveWindow(left, top, 50, height);

		m_eb_side_length.ShowWindow(SW_SHOW);
		m_eb_side_length.BringWindowToTop();
		m_eb_side_length.SetWindowTextW(text);
		m_eb_side_length.SetFocus();
	}
	*pResult = 0;
}


void CTestSetGeneratorAppDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int row = pNMLV->iItem;

	if (row != m_cur_thick_row_select)
	{
		m_cur_thick_row_select = row;
		int cur_col_select = m_lb_side_thickness.GetSelectedColumn();

		CRect lv_rect;
		m_lb_side_thickness.GetWindowRect(lv_rect);
		ScreenToClient(lv_rect);
		CRect rect;
		m_lb_side_thickness.GetItemRect(row, &rect, LVIR_BOUNDS);
		int left = lv_rect.left + rect.left + 76;
		int top = lv_rect.top + rect.top;
		int height = rect.bottom - rect.top;

		CString	text;
		m_lb_side_thickness.SetSelectionMark(row);
		text = m_lb_side_thickness.GetItemText(row, 1);
		m_eb_side_thickness.MoveWindow(left, top, 50, height);

		m_eb_side_thickness.ShowWindow(SW_SHOW);
		m_eb_side_thickness.BringWindowToTop();
		m_eb_side_thickness.SetWindowTextW(text);
		m_eb_side_thickness.SetFocus();
	}
	*pResult = 0;
}

void CTestSetGeneratorAppDlg::OnEnChangeEdit1()
{
	int item = m_lb_side_lengths.GetSelectionMark();
	CString text;
	int cur_col_select = m_lb_side_lengths.GetSelectedColumn();
	if (item != -1)
	{
		GetDlgItemText(IDC_EDIT1, text);
		m_lb_side_lengths.SetItemText(item, 1, text);
	}
}

void CTestSetGeneratorAppDlg::OnEnChangeEdit6()
{
	int item = m_lb_side_thickness.GetSelectionMark();
	CString text;
	int cur_col_select = m_lb_side_thickness.GetSelectedColumn();
	if (item != -1)
	{
		GetDlgItemText(IDC_EDIT6, text);
		m_lb_side_thickness.SetItemText(item, 1, text);
	}
}

void CTestSetGeneratorAppDlg::OnCbnSelchangeCombo()
{
	if (m_cur_shape_select != m_cb_shape.GetCurSel())
	{
		m_cur_shape_select = m_cb_shape.GetCurSel();

		if (m_cur_shape_select == SL_TRIANGLE)
		{
			SetNumSideRows(3);
			SetNumSideThicknessRows(3);
			m_cb_quad_options.ShowWindow(SW_HIDE);
			m_cb_tri_options.ShowWindow(SW_SHOW);
		}
		else if (m_cur_shape_select == SL_QUADRILATERAL)
		{
			SetNumSideRows(4);
			SetNumSideThicknessRows(4);
			m_cb_quad_options.ShowWindow(SW_SHOW);
			m_cb_tri_options.ShowWindow(SW_HIDE);
		}
		m_eb_side_thickness.SetWindowTextW(L"0");
		m_eb_side_length.SetWindowTextW(L"0");
	}
}

void CTestSetGeneratorAppDlg::OnCbnSelchangeCombo1()
{
	int cur_select = m_cb_quad_options.GetCurSel();
	switch (cur_select)
	{
		case Quadrilateral::QT_SQUARE:
				SetNumSideRows(1);
				break;
		case Quadrilateral::QT_RECTANGLE:
				SetNumSideRows(2);
				break;
		case Quadrilateral::QT_RHOMBUS:
				SetNumSideRows(1);
				break;
		case Quadrilateral::QT_PARALLELOGRAM:
				SetNumSideRows(2);
				break;
		case Quadrilateral::QT_TRAPEZOID:
				SetNumSideRows(4);
				break;
		case Quadrilateral::QT_KITE:
				SetNumSideRows(4);
						 //add edit boxes later for angles
				break;

		default:
			SetNumSideRows(4);
	}
}

void CTestSetGeneratorAppDlg::OnCbnSelchangeCombo2()
{
	int cur_select = m_cb_tri_options.GetCurSel();
	switch (cur_select)
	{
		case Triangle::TRT_EQUILATERAL:
			SetNumSideRows(1);
			break;
		case Triangle::TRT_ISOCELES:
			SetNumSideRows(2);
			break;
		case Triangle::TRT_RIGHT:
			SetNumSideRows(3);
			break;
		case Triangle::TRT_RIGHT_ISOCELES:
			SetNumSideRows(2);
			break;
		case Triangle::TRT_ACUTE:
			SetNumSideRows(3);
			break;
		case Triangle::TRT_OBTUSE:
			SetNumSideRows(3);
			break;
		case Triangle::TRT_SCALENE:
			SetNumSideRows(3);
			//add edit boxes later for angles
			break;

		default:
			SetNumSideRows(3);
	}
}

void CTestSetGeneratorAppDlg::OnBnClickedButton1()
{
	SBX::Polygon * poly = new SBX::Polygon;
	bool is_polygon_gen_success(false);
	if (m_cb_shape.GetCurSel() == SL_QUADRILATERAL)
	{
		is_polygon_gen_success = GenerateQuadrilateral(poly);
	}
	if (m_cb_shape.GetCurSel() == SL_TRIANGLE)
	{
		is_polygon_gen_success = GenerateTriangle(poly);
	}

	/*DEBUGGING*/
/*	is_polygon_gen_success = true;*/
	/*DEBUGGING*/
	
	if (is_polygon_gen_success)
	{	
		m_lbl_progress.SetWindowTextW(L"Generating Polygons!");
	
		/*DEBUGGING*/
		/*Triangle tri;
		tri.InitializeEquilateral(400);
		tri.SetSideThickness(Triangle::SL_AB, 100);
		tri.SetSideThickness(Triangle::SL_BC, 1);
		tri.SetSideThickness(Triangle::SL_CA, 1);
		*poly = *(tri.ReturnSelfAsPolygon());		
		Quadrilateral quad;
		quad.InitializeSquare(300);
		quad.SetSideThickness(Quadrilateral::SL_AB, 10);
		quad.SetSideThickness(Quadrilateral::SL_BC, 75);
		quad.SetSideThickness(Quadrilateral::SL_CD, 50);
		quad.SetSideThickness(Quadrilateral::SL_DA, 150);
		*poly = *(quad.ReturnSelfAsPolygon());*/
		/*m_generator.SetNumXPixels(600);
		m_generator.SetNumYPixels(600);
		m_generator.SetRotationRange(360);
		m_generator.SetRotationIncrement(1);*/
		/*DEBUGGING*/

		m_generator.SetNumXPixels(GetPixelWidth());
		m_generator.SetNumYPixels(GetPixelHeight());
		m_generator.SetRotationRange(GetRotationRange());
		m_generator.SetRotationIncrement(GetRotationIncrement());
		m_generator.SetPolygon(*poly);
		m_generator.GenerateTestSet();
	}

	delete poly;
	m_lbl_progress.SetWindowTextW(L"Polygons Generated!");
}

//...................................................................................
/////////////////////////////////////////////////////////////////////////////////////
//User defined functions
/////////////////////////////////////////////////////////////////////////////////////
//...................................................................................
void CTestSetGeneratorAppDlg::InitSideListViews(void)
{
	LVCOLUMN lv_length_col;

	lv_length_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv_length_col.fmt = LVCFMT_LEFT;
	lv_length_col.cx = 75;
	lv_length_col.pszText = L"Side Num";
	m_lb_side_lengths.InsertColumn(0, &lv_length_col);

	lv_length_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv_length_col.fmt = LVCFMT_LEFT;
	lv_length_col.cx = 50;
	lv_length_col.pszText = L"Length";
	m_lb_side_lengths.InsertColumn(1, &lv_length_col);

	LVCOLUMN lv_thickness_col;

	lv_thickness_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv_thickness_col.fmt = LVCFMT_LEFT;
	lv_thickness_col.cx = 75;
	lv_thickness_col.pszText = L"Side Num";
	m_lb_side_thickness.InsertColumn(0, &lv_thickness_col);

	lv_thickness_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv_thickness_col.fmt = LVCFMT_LEFT;
	lv_thickness_col.cx = 50;
	lv_thickness_col.pszText = L"Thickness";
	m_lb_side_thickness.InsertColumn(1, &lv_thickness_col);

	m_cur_length_row_select = -1;
	m_cur_thick_row_select = -1;
}

//...................................................................................
void CTestSetGeneratorAppDlg::SetNumSideRows(int num_rows)
{
	m_lb_side_lengths.DeleteAllItems();
	for (int i = 0; i < num_rows; i++)
	{
		LVITEM lv_item_length;
		std::wstring item_text = L"Side " + to_wstring(i + 1);

		lv_item_length.mask = LVIF_TEXT;
		lv_item_length.iItem = i;
		lv_item_length.iSubItem = 0;
		lv_item_length.pszText = (LPWSTR)(item_text.c_str());
		int item = m_lb_side_lengths.InsertItem(&lv_item_length);
		m_lb_side_lengths.SetItemText(item, 1, L"0");
	}
}

//...................................................................................
void CTestSetGeneratorAppDlg::SetNumSideThicknessRows(int num_rows)
{
	m_lb_side_thickness.DeleteAllItems();
	for (int i = 0; i < num_rows; i++)
	{
		LVITEM lv_item_thickness;
		std::wstring item_text = L"Side " + to_wstring(i + 1);

		lv_item_thickness.mask = LVIF_TEXT;
		lv_item_thickness.iItem = i;
		lv_item_thickness.iSubItem = 0;
		lv_item_thickness.pszText = (LPWSTR)(item_text.c_str());
		int item = m_lb_side_thickness.InsertItem(&lv_item_thickness);
		m_lb_side_thickness.SetItemText(item, 1, L"1");
	}
}

//...................................................................................
void CTestSetGeneratorAppDlg::SetOptionsForQuadrilateral(int type)
{
	switch (type)
	{
		case Quadrilateral::QT_SQUARE:
			//no more options needed
			break;
		case Quadrilateral::QT_RECTANGLE:
			//no more options needed
			break;
		case Quadrilateral::QT_RHOMBUS:
			//add edit boxes later for angles
			break;
		case Quadrilateral::QT_PARALLELOGRAM:
			//add edit boxes later for angles
			break;
		case Quadrilateral::QT_TRAPEZOID:
			//add edit boxes later for angles
			break;
		case Quadrilateral::QT_KITE:
					 //add edit boxes later for angles
			break;

		default:
			;
			//add edit boxes later for angles
	}
}

//...................................................................................
bool CTestSetGeneratorAppDlg::ValidateSideLengths(void)
{
	bool sides_valid(true);

	for (int i = 0; i < m_lb_side_lengths.GetItemCount(); i++)
	{
		CString text = m_lb_side_lengths.GetItemText(i, 1);
		if (StrToInt(text) < 1)
		{
			sides_valid = false;
			break;
		}
	}

	return sides_valid;
}

//...................................................................................
bool CTestSetGeneratorAppDlg::ValidateSideThickness(void)
{
	bool thickness_valid(true);

	for (int i = 0; i < m_lb_side_thickness.GetItemCount(); i++)
	{
		CString text = m_lb_side_thickness.GetItemText(i, 1);
		if (StrToInt(text) < 1)
		{
			thickness_valid = false;
			break;
		}
	}

	return thickness_valid;
}

//...................................................................................
int CTestSetGeneratorAppDlg::GetSideLength(int side_label)
{
	int length = 0;

	if (side_label < m_lb_side_lengths.GetItemCount())
	{
		length = StrToInt(m_lb_side_lengths.GetItemText(side_label, 1));
	}

	return length;
}

//...................................................................................
int CTestSetGeneratorAppDlg::GetSideThickness(int side_label)
{
	int thickness = 1;

	if (side_label < m_lb_side_thickness.GetItemCount())
	{
		thickness = StrToInt(m_lb_side_thickness.GetItemText(side_label, 1));
		if (thickness < 1)
		{
			thickness = 1;
		}
	}

	return thickness;
}

//...................................................................................
int CTestSetGeneratorAppDlg::GetPixelWidth(void)
{
	int pixel_width(1);

	CString text;
	GetDlgItemText(IDC_EDIT2, text);
	pixel_width = StrToInt(text);

	if (pixel_width < 1)
	{
		pixel_width = 1;
	}

	return pixel_width;
}

//...................................................................................
int CTestSetGeneratorAppDlg::GetPixelHeight(void)
{
	int pixel_height(1);

	CString text;
	GetDlgItemText(IDC_EDIT3, text);
	pixel_height = StrToInt(text);

	if (pixel_height < 1)
	{
		pixel_height = 1;
	}

	return pixel_height;
}

//...................................................................................
int CTestSetGeneratorAppDlg::GetRotationRange(void)
{
	int rotation_range(0);

	CString text;
	GetDlgItemText(IDC_EDIT4, text);
	rotation_range = StrToInt(text);

	if (rotation_range < 1)
	{
		rotation_range = 0;
	}

	return rotation_range;
}

//...................................................................................
int CTestSetGeneratorAppDlg::GetRotationIncrement(void)
{
	int rotation_increment(0);

	CString text;
	GetDlgItemText(IDC_EDIT5, text);
	rotation_increment = StrToInt(text);

	if (rotation_increment < 1)
	{
		rotation_increment = 0;
	}

	return rotation_increment;
}

//...................................................................................
bool CTestSetGeneratorAppDlg::GenerateQuadrilateral(SBX::Polygon * poly)
{
	bool is_success(false);

	Quadrilateral quad;
	if (ValidateSideLengths())
	{
		if (m_cb_quad_options.GetCurSel() == Quadrilateral::QT_SQUARE)
		{
			quad.InitializeSquare(GetSideLength(Quadrilateral::SL_AB));
		}
		if (m_cb_quad_options.GetCurSel() == Quadrilateral::QT_RECTANGLE)
		{
			quad.InitializeRectange(GetSideLength(Quadrilateral::SL_AB), GetSideLength(Quadrilateral::SL_BC));
		}
		if (m_cb_quad_options.GetCurSel() == Quadrilateral::QT_RHOMBUS)
		{
			//quad.InitializeRhombus(GetSideLength(Quadrilateral::SL_AB));
		}
		if (m_cb_quad_options.GetCurSel() == Quadrilateral::QT_PARALLELOGRAM)
		{
			//quad.InitializeParallelogram(GetSideLength(Quadrilateral::SL_AB), GetSideLength(Quadrilateral::SL_BC));
		}
		if (m_cb_quad_options.GetCurSel() == Quadrilateral::QT_TRAPEZOID)
		{
			/*quad.InitializeTrapezoid(
																	GetSideLength(Quadrilateral::SL_AB), GetSideLength(Quadrilateral::SL_BC)
																	GetSideLength(Quadrilateral::SL_CD), GetSideLength(Quadrilateral::SL_DA)
																);*/
		}
		if (m_cb_quad_options.GetCurSel() == Quadrilateral::QT_KITE)
		{
			//quad.InitializeKite(GetSideLength(Quadrilateral::SL_AB), GetSideLength(Quadrilateral::SL_BC));
		}
		else
		{
			/*quad.SetSideLength(Quadrilateral::SL_AB, GetSideLength(Quadrilateral::SL_AB));
			quad.SetSideLength(Quadrilateral::SL_BC, GetSideLength(Quadrilateral::SL_BC));
			quad.SetSideLength(Quadrilateral::SL_CD, GetSideLength(Quadrilateral::SL_CD));
			quad.SetSideLength(Quadrilateral::SL_DA, GetSideLength(Quadrilateral::SL_DA));*/
		}

		//
		quad.SetSideThickness(Quadrilateral::SL_AB, GetSideThickness(Quadrilateral::SL_AB));
		quad.SetSideThickness(Quadrilateral::SL_BC, GetSideThickness(Quadrilateral::SL_BC));
		quad.SetSideThickness(Quadrilateral::SL_CD, GetSideThickness(Quadrilateral::SL_CD));
		quad.SetSideThickness(Quadrilateral::SL_DA, GetSideThickness(Quadrilateral::SL_DA));

		*poly = quad;
		is_success = true;
	}

	return is_success;
}

//...................................................................................
bool CTestSetGeneratorAppDlg::GenerateTriangle(SBX::Polygon * poly)
{
	bool is_success(false);

	Triangle tri;
	if (ValidateSideLengths())
	{
		if (m_cb_tri_options.GetCurSel() == Triangle::TRT_EQUILATERAL)
		{
			tri.InitializeEquilateral(GetSideLength(Quadrilateral::SL_AB));
		}
		if (m_cb_tri_options.GetCurSel() == Triangle::TRT_ISOCELES)
		{
			//tri.InitializeIsoceles(GetSideLength(Triangle::SL_AB), GetSideLength(Triangle::SL_BC));
		}
		if (m_cb_tri_options.GetCurSel() == Triangle::TRT_RIGHT)
		{
			//tri.InitializeRight(GetSideLength(Triangle::SL_AB), GetSideLength(Triangle::SL_BC), GetSideLength(Triangle::SL_CA));
		}
		if (m_cb_tri_options.GetCurSel() == Triangle::TRT_RIGHT_ISOCELES)
		{
			//tri.InitializeRightIsoceles(GetSideLength(Triangle::SL_AB), GetSideLength(Triangle::SL_BC));
		}
		if (m_cb_tri_options.GetCurSel() == Triangle::TRT_ACUTE)
		{
			//tri.InitializeAcute(GetSideLength(Triangle::SL_AB), GetSideLength(Triangle::SL_BC), GetSideLength(Triangle::SL_CA));
		}
		if (m_cb_tri_options.GetCurSel() == Triangle::TRT_OBTUSE)
		{
			//tri.InitializeObtuse(GetSideLength(Triangle::SL_AB), GetSideLength(Triangle::SL_BC), GetSideLength(Triangle::SL_CA));
		}
		else
		{
			//tri.InitializeScalene(GetSideLength(Triangle::SL_AB), GetSideLength(Triangle::SL_BC), GetSideLength(Triangle::SL_CA));
		}

		//
		tri.SetSideThickness(Triangle::SL_AB, GetSideThickness(Triangle::SL_AB));
		tri.SetSideThickness(Triangle::SL_BC, GetSideThickness(Triangle::SL_BC));
		tri.SetSideThickness(Triangle::SL_CA, GetSideThickness(Triangle::SL_CA));

		*poly = tri;
		is_success = true;
	}

	return is_success;
}
