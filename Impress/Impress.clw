; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFractalDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Impress.h"
LastPage=0

ClassCount=31
Class1=CImpressApp
Class2=CImpressDoc
Class3=CImpressView
Class4=CMainFrame

ResourceCount=29
Resource1=IDR_IMPRESTYPE
Resource2=IDD_FRACTALDIALOG1
Resource3=IDD_TRANSFORMDIALOG (Neutral)
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_BRUSHVIEW_FORM (English (U.S.))
Resource5=IDD_FORMVIEW (English (U.S.))
Resource6=IDR_ENTER_ACCEL (English (U.S.))
Class7=CPreviewWindow
Resource7=IDR_PREVIEWMENU (English (U.S.))
Resource8=IDR_IMPRESTYPE (English (U.S.))
Class8=CRotateAngleDialog
Resource9=IDD_PAGE_BRUSH_FORM (English (U.S.))
Resource10=IDD_NEWDIALOG
Class9=CPropDialog
Resource11=IDD_PAGE_PAINTING_OPTIONS (English (U.S.))
Class10=CCompressDialog
Resource12=IDD_PAGE_BRUSH_SIZE_AND_FORM (English (U.S.))
Class11=CFourierTransformDialog
Resource13=IDD_PAGE_BRUSH_OPACITY (English (U.S.))
Class12=CCustomImageDialog
Resource14=IDD_DIALOGBAR (English (U.S.))
Class13=CBrushDialog
Resource15=IDD_PROPDIALOG
Resource16=IDD_PAGE_BRUSH_COLOR (English (U.S.))
Resource17=IDR_BRUSHVIEW_TMPL (English (U.S.))
Resource18=IDD_FOURIER_TRANSFORM_DIALOG
Resource19=IDD_ABOUTBOX (English (U.S.))
Resource20=IDD_DIALOG2 (English (U.S.))
Class14=CPageColor
Class15=CPageForm
Class16=CPageAlphaBlending
Class17=CBrushSheet
Resource21=IDD_COMPRESS_DIALOG (English (U.S.))
Class18=CBrushView
Class19=CBrushDoc
Class20=CBrushPreviewWindow
Class21=CPageOpacity
Class22=CPageSize
Resource22=IDD_DIALOG2
Class23=CFilterDialog
Class24=CFilterWnd
Resource23=IDD_NEWFILTER (English (U.S.))
Class25=CTraceDialog
Class26=CFilter2DDialog
Class27=CNumberDialog
Class28=NewFilterDialog
Class29=CFilterDialogProperties
Class30=CTransformDialog
Resource24=IDR_MAINFRAME (English (U.S.))
Resource25=IDR_MAINFRAME
Resource26=IDD_FOURIER_TRANSFORM_DIALOG (Russian)
Resource27=IDD_PROPDIALOG (Russian)
Resource28=IDD_ABOUTBOX
Class31=CFractalDialog
Resource29=IDR_ENTER_ACCEL

[CLS:CImpressApp]
Type=0
HeaderFile=Impress.h
ImplementationFile=Impress.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CImpressApp

[CLS:CImpressDoc]
Type=0
HeaderFile=ImpressDoc.h
ImplementationFile=ImpressDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CImpressDoc

[CLS:CImpressView]
Type=0
HeaderFile=ImpressView.h
ImplementationFile=ImpressView.cpp
Filter=C
LastObject=ID_IMAGE_GENERATEFRACTAL
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=Impress.cpp
ImplementationFile=Impress.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308480
Control5=IDC_STATIC,static,1342308480
Control6=IDC_STATIC,static,1342308480
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342181390
Control9=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_IMAGE_SIZE
Command5=ID_IMAGE_TRANSFORM_ROTATE_ROTATENUMERIC
Command6=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CCW
Command7=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CW
Command8=ID_IMAGE_TRANSFORM_OFFSET
Command9=ID_IMAGE_MODE_INVERT
Command10=ID_IMAGE__MONOCHROME
Command11=ID_IMAGE_TRANSFORM_FLIPVERTICAL
Command12=ID_IMAGE_TRANSFORM_FLIPHORIZONTAL
Command13=ID_APP_ABOUT
CommandCount=13

[MNU:IDR_IMPRESTYPE]
Type=1
Class=CImpressView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_IMAGE_DUPLICATE
Command10=ID_IMAGE_TRANSFORM_FLIPVERTICAL
Command11=ID_IMAGE_TRANSFORM_FLIPHORIZONTAL
Command12=ID_IMAGE_TRANSFORM_OFFSET
Command13=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CW
Command14=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CCW
Command15=ID_IMAGE_TRANSFORM_ROTATE_ROTATENUMERIC
Command16=ID_IMAGE_IMAGEINFO
Command17=ID_IMAGE__GRAYSCALE
Command18=ID_IMAGE__MONOCHROME
Command19=ID_IMAGE_MODE_INVERT
Command20=ID_IMAGE_SIZE
Command21=ID_IMAGE_GENERATEFRACTAL
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_WINDOW_NEW
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=ID_APP_ABOUT
CommandCount=28

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_IMPRESTYPE (English (U.S.))]
Type=1
Class=CImpressView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_IMAGE_DUPLICATE
Command10=ID_IMAGE_TRANSFORM_FLIPVERTICAL
Command11=ID_IMAGE_TRANSFORM_FLIPHORIZONTAL
Command12=ID_IMAGE_TRANSFORM_OFFSET
Command13=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CW
Command14=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CCW
Command15=ID_IMAGE_TRANSFORM_ROTATE_ROTATENUMERIC
Command16=ID_IMAGE_IMAGEINFO
Command17=ID_IMAGE__GRAYSCALE
Command18=ID_IMAGE__MONOCHROME
Command19=ID_IMAGE_MODE_INVERT
Command20=ID_IMAGE_SIZE
Command21=ID_VIEW_TOOLBAR
Command22=ID_VIEW_STATUS_BAR
Command23=ID_WINDOW_NEW
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_ARRANGE
Command27=ID_APP_ABOUT
CommandCount=27

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_IMAGE_SIZE
Command5=ID_IMAGE_TRANSFORM_ROTATE_ROTATENUMERIC
Command6=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CCW
Command7=ID_IMAGE_TRANSFORM_ROTATE_ROTATE90CW
Command8=ID_IMAGE_TRANSFORM_OFFSET
Command9=ID_IMAGE_MODE_INVERT
Command10=ID_IMAGE__MONOCHROME
Command11=ID_IMAGE_TRANSFORM_FLIPVERTICAL
Command12=ID_IMAGE_TRANSFORM_FLIPHORIZONTAL
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308480
Control5=IDC_STATIC,static,1342308480
Control6=IDC_STATIC,static,1342308480
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342181390
Control9=IDC_STATIC,static,1342308352

[CLS:CRotateAngleDialog]
Type=0
HeaderFile=RotateAngleDialog.h
ImplementationFile=RotateAngleDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRotateAngleDialog

[MNU:IDR_PREVIEWMENU (English (U.S.))]
Type=1
Class=?
Command1=ID_OPTIONS_UPDATEONMOUSEMOVING
CommandCount=1

[CLS:CPreviewWindow]
Type=0
HeaderFile=PreviewWindow.h
ImplementationFile=PreviewWindow.cpp
BaseClass=CWnd
Filter=T
LastObject=CPreviewWindow
VirtualFilter=fWC

[DLG:IDD_NEWDIALOG]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_A,edit,1350631552
Control4=IDC_B,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_PROPDIALOG]
Type=1
Class=CPropDialog
ControlCount=4
Control1=IDC_A,edit,1350631552
Control2=IDC_B,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CPropDialog]
Type=0
HeaderFile=PropDialog.h
ImplementationFile=PropDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CPropDialog
VirtualFilter=dWC

[CLS:CCompressDialog]
Type=0
HeaderFile=CompressDialog.h
ImplementationFile=CompressDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_THRESHOLD
VirtualFilter=dWC

[DLG:IDD_FOURIER_TRANSFORM_DIALOG]
Type=1
Class=CFourierTransformDialog
ControlCount=18
Control1=IDC_NEW_WIDTH,edit,1350631552
Control2=IDC_NEW_HEIGHT,edit,1350631552
Control3=IDC_KERNEL_TYPE,button,1342308361
Control4=IDC_GAUSS,button,1342177289
Control5=IDC_NEW_SMOOTH,edit,1350762624
Control6=IDC_STEPOVERSHOOT,edit,1350762624
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_PREDEFINED,combobox,1344274435
Control16=IDC_STATIC,static,1342308352
Control17=IDC_KEEPASPECT,button,1342242816
Control18=IDC_STATIC,button,1342177287

[CLS:CFourierTransformDialog]
Type=0
HeaderFile=FourierTransformDialog.h
ImplementationFile=FourierTransformDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_KEEPASPECT
VirtualFilter=dWC

[CLS:CCustomImageDialog]
Type=0
HeaderFile=CustomImageDialog.h
ImplementationFile=CustomImageDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CBrushDialog]
Type=0
HeaderFile=BrushDialog.h
ImplementationFile=BrushDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CBrushDialog

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=CTransformDialog
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PAGE_PAINTING_OPTIONS (English (U.S.))]
Type=1
Class=CPageAlphaBlending
ControlCount=7
Control1=IDC_ALPHA_BLENDING,button,1342312457
Control2=IDC_RADIO8,button,1342181385
Control3=IDC_RADIO9,button,1342181385
Control4=IDC_RADIO10,button,1342181385
Control5=IDC_RADIO11,button,1342181385
Control6=IDC_RADIO12,button,1342181385
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_PAGE_BRUSH_SIZE_AND_FORM (English (U.S.))]
Type=1
Class=CPageSize
ControlCount=5
Control1=IDC_BRUSH_SIZE,edit,1350631552
Control2=IDC_SIZE_SPIN,msctls_updown32,1342177334
Control3=IDC_NEW,button,1342242816
Control4=IDC_RESIZE,button,1342242816
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_PAGE_BRUSH_COLOR (English (U.S.))]
Type=1
Class=CPageColor
ControlCount=6
Control1=IDC_COLOR,button,1342312457
Control2=IDC_COLOR5,button,1342181385
Control3=IDC_COLOR2,button,1342181385
Control4=IDC_COLOR4,button,1342181385
Control5=IDC_COLOR6,button,1342181385
Control6=IDC_STATIC,button,1342177287

[DLG:IDD_PAGE_BRUSH_FORM (English (U.S.))]
Type=1
Class=CPageForm
ControlCount=9
Control1=IDC_RECT_WIDTH,msctls_trackbar32,1342242840
Control2=IDC_RECT_HEIGHT,msctls_trackbar32,1342242840
Control3=IDC_ADD_RECT,button,1342242816
Control4=IDC_ADD_CIRCLE,button,1342242816
Control5=IDC_ROMB_RADIUS,msctls_trackbar32,1342242840
Control6=IDC_ADD_ROMB,button,1342242816
Control7=IDC_LOAD_FROM_BMP,button,1342242816
Control8=IDC_CLEAR,button,1342242816
Control9=IDC_RING_RADIUS,msctls_trackbar32,1342242840

[DLG:IDD_PAGE_BRUSH_OPACITY (English (U.S.))]
Type=1
Class=CPageOpacity
ControlCount=7
Control1=IDC_OPACITY_TYPE,button,1342312457
Control2=IDC_RADIO13,button,1342181385
Control3=IDC_RADIO14,button,1342181385
Control4=IDC_OPACITY_SIZE_OUTER,msctls_trackbar32,1350631448
Control5=IDC_OPACITY_SIZE_INNER,msctls_trackbar32,1350631448
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CPageColor]
Type=0
HeaderFile=PageColor.h
ImplementationFile=PageColor.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPageColor
VirtualFilter=idWC

[CLS:CPageForm]
Type=0
HeaderFile=PageForm.h
ImplementationFile=PageForm.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_RING_RADIUS
VirtualFilter=idWC

[CLS:CPageAlphaBlending]
Type=0
HeaderFile=PageAlphaBlending.h
ImplementationFile=PageAlphaBlending.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPageAlphaBlending
VirtualFilter=idWC

[CLS:CBrushSheet]
Type=0
HeaderFile=BrushSheet1.h
ImplementationFile=BrushSheet1.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC

[CLS:CBrushView]
Type=0
HeaderFile=BrushView.h
ImplementationFile=BrushView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC

[CLS:CBrushDoc]
Type=0
HeaderFile=BrushDoc.h
ImplementationFile=BrushDoc.cpp
BaseClass=CDocument
Filter=N
VirtualFilter=DC

[CLS:CBrushPreviewWindow]
Type=0
HeaderFile=BrushPreviewWindow.h
ImplementationFile=BrushPreviewWindow.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CBrushPreviewWindow

[CLS:CPageOpacity]
Type=0
HeaderFile=PageOpacity.h
ImplementationFile=PageOpacity.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC

[CLS:CPageSize]
Type=0
HeaderFile=PageSize.h
ImplementationFile=PageSize.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_BRUSH_SIZE

[CLS:CFilterDialog]
Type=0
HeaderFile=FilterDialog.h
ImplementationFile=FilterDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_PREDEFINED

[CLS:CFilterWnd]
Type=0
HeaderFile=FilterWnd.h
ImplementationFile=FilterWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[DLG:IDD_BRUSHVIEW_FORM (English (U.S.))]
Type=1
Class=CBrushView
ControlCount=1
Control1=IDC_STATIC,static,1350696961

[MNU:IDR_BRUSHVIEW_TMPL (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_SHOWBRUSHOPTIONS
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

[DLG:IDD_DIALOG2 (English (U.S.))]
Type=1
Class=CRotateAngleDialog
ControlCount=4
Control1=IDC_ANGLE,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_COMPRESS_DIALOG (English (U.S.))]
Type=1
Class=CCompressDialog
ControlCount=11
Control1=IDC_BROUSE_BUTTON,button,1342242816
Control2=IDC_FILE_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BLOCK_SIZE,edit,1350631552
Control5=IDC_THRESHOLD,edit,1350631552
Control6=IDC_START,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308353
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_PROGRESS,msctls_progress32,1350565889

[CLS:CTraceDialog]
Type=0
HeaderFile=TraceDialog.h
ImplementationFile=TraceDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CFilter2DDialog]
Type=0
HeaderFile=Filter2DDialog.h
ImplementationFile=Filter2DDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFilter2DDialog

[CLS:CNumberDialog]
Type=0
HeaderFile=NumberDialog.h
ImplementationFile=NumberDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SPIN

[DLG:IDD_NEWFILTER (English (U.S.))]
Type=1
Class=NewFilterDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308354
Control4=IDC_FILTER_NAME,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDC_FILTER_SIZE,edit,1350631552

[CLS:NewFilterDialog]
Type=0
HeaderFile=NewFilterDialog.h
ImplementationFile=NewFilterDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CFilterDialogProperties]
Type=0
HeaderFile=FilterDialogProperties.h
ImplementationFile=FilterDialogProperties.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ENTER
VirtualFilter=dWC

[ACL:IDR_ENTER_ACCEL (English (U.S.))]
Type=1
Class=?
Command1=ID_ENTER
CommandCount=1

[CLS:CTransformDialog]
Type=0
HeaderFile=TransformDialog.h
ImplementationFile=TransformDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CANCEL
VirtualFilter=dWC

[DLG:IDD_TRANSFORMDIALOG (Neutral)]
Type=1
Class=CTransformDialog
ControlCount=3
Control1=IDC_CANCEL,button,1342242816
Control2=IDC_PROGRESS1,msctls_progress32,1350565888
Control3=IDC_STATIC1,static,1342308352

[DLG:IDD_FOURIER_TRANSFORM_DIALOG (Russian)]
Type=1
Class=CFourierTransformDialog
ControlCount=18
Control1=IDC_NEW_WIDTH,edit,1350631552
Control2=IDC_NEW_HEIGHT,edit,1350631552
Control3=IDC_KERNEL_TYPE,button,1342308361
Control4=IDC_GAUSS,button,1342177289
Control5=IDC_NEW_SMOOTH,edit,1350762624
Control6=IDC_STEPOVERSHOOT,edit,1350762624
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_PREDEFINED,combobox,1344274435
Control16=IDC_STATIC,static,1342308352
Control17=IDC_KEEPASPECT,button,1342242816
Control18=IDC_STATIC,button,1342177287

[DLG:IDD_PROPDIALOG (Russian)]
Type=1
Class=CPropDialog
ControlCount=4
Control1=IDC_A,edit,1350631552
Control2=IDC_B,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG2]
Type=1
Class=CRotateAngleDialog
ControlCount=4
Control1=IDC_ANGLE,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[ACL:IDR_ENTER_ACCEL]
Type=1
Class=?
Command1=ID_ENTER
CommandCount=1

[DLG:IDD_FRACTALDIALOG1]
Type=1
Class=CFractalDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_P1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EPS,edit,1350631552

[CLS:CFractalDialog]
Type=0
HeaderFile=FractalDialog.h
ImplementationFile=FractalDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CFractalDialog
VirtualFilter=dWC

