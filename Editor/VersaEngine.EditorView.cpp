
// VersaEngine.EditorView.cpp : implementation of the CVersaEngineEditorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VersaEngine.Editor.h"
#endif

#include "VersaEngine.EditorDoc.h"
#include "VersaEngine.EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVersaEngineEditorView

IMPLEMENT_DYNCREATE(CVersaEngineEditorView, CView)

BEGIN_MESSAGE_MAP(CVersaEngineEditorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVersaEngineEditorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CVersaEngineEditorView construction/destruction

CVersaEngineEditorView::CVersaEngineEditorView() noexcept
{
	// TODO: add construction code here

}

CVersaEngineEditorView::~CVersaEngineEditorView()
{
}

BOOL CVersaEngineEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVersaEngineEditorView drawing

void CVersaEngineEditorView::OnDraw(CDC* /*pDC*/)
{
	CVersaEngineEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CVersaEngineEditorView printing


void CVersaEngineEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVersaEngineEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVersaEngineEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVersaEngineEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVersaEngineEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVersaEngineEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVersaEngineEditorView diagnostics

#ifdef _DEBUG
void CVersaEngineEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CVersaEngineEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVersaEngineEditorDoc* CVersaEngineEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVersaEngineEditorDoc)));
	return (CVersaEngineEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CVersaEngineEditorView message handlers
