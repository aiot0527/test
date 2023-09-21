// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "mfctestCircle.h"
#include "CDlgImage.h"
#include "afxdialogex.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

#include "mfctestCircleDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int n = 100;
	CmfctestCircleDlg* pDlg = (CmfctestCircleDlg*)m_pParent;
	pDlg->callFunc(n++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 480);


	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
	
	drawData(&dc);

}

void CDlgImage::drawData(CDC* pDC)
{
	int nWidth = 640;
	int nHeight = 480;

	CRect rect;
	CPen pen;	// 펜 생성
	CBrush brush;

	m_ptData.x = rand() % nWidth;
	m_ptData.y = rand() % nHeight;

	brush.CreateSolidBrush(RGB(255, 255, 255));	// 브러시 생성
	pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW);	//직선, 두께, 색상 //Ctrl + Shift + U : 소문자->대문자
	CPen* pOldPen = pDC->SelectObject(&pen);	//현재 펜 저장
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	rect.SetRect(m_ptData, m_ptData);
	rect.InflateRect(m_pNum, m_pNum);	// 원 크기
	pDC->Ellipse(rect); // 네모 안에 원 그리기

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	 // 원의 중심에 십자가 모양 그리기 (빨간색)
	CPen redpen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldredPen = pDC->SelectObject(&redpen);	//현재 펜 저장




	// 수평선
	pDC->MoveTo(m_ptData.x - (m_pNum/6), m_ptData.y);
	pDC->LineTo(m_ptData.x + (m_pNum/6), m_ptData.y);

	// 수직선
	pDC->MoveTo(m_ptData.x, m_ptData.y - (m_pNum/6));
	pDC->LineTo(m_ptData.x, m_ptData.y + (m_pNum/6));


	
	
	pDC->SelectObject(pOldredPen);

	// pen, brush 객체 소멸 (필요에 따라 소멸)
	pen.DeleteObject();
	redpen.DeleteObject();
	brush.DeleteObject();
	//pDC->SelectObject(pOldPen);	//펜 가져오기
}

void CDlgImage::InitImage()
{
	int nWidth = 640;	//640
	int nHeight = 480;	//480
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}
	
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, nWidth * nHeight);
}


