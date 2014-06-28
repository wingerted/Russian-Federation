// ����˹����.cpp : ����Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "����˹����.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
    
Background *background = NULL;
BaseShape *shape = NULL;
BaseShape *next_shape = NULL;
TCHAR szBuffer[10];

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void                Init(HDC hdc) ;
void CreateShape(BaseShape* &shape);
VOID CALLBACK  TimerProc (HWND hWnd, UINT message, UINT iTimerID, DWORD dwTime);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 400, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

    


	switch (message)
	{
    case WM_CREATE:
      {
         CreateWindowEx(0,		//��0�ͺ�
           		       TEXT("button"),		//��ť�࣬windows��Ϊ����ע��ã��ص�����Ҳ��д��
           		       TEXT("��ʼ"),			//��ť���ƣ��ڰ�ť����ʾ��
           		       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,	//���ڷ��������ͺ�
           		       20, 10, 80, 40,	//���ꡢ����
           		       hWnd, 			//�丸������hwnd��������������
				       (HMENU)0,		//��ť��ID������������Ϊ0
				       ((LPCREATESTRUCT) lParam)->hInstance, //���ǵ�Ӧ�ó����ţ�������ͺ�
				       NULL) ;			//��NULL�ͺ�
         CreateWindowEx(0,		//��0�ͺ�
           		       TEXT("button"),		//��ť�࣬windows��Ϊ����ע��ã��ص�����Ҳ��д��
           		       TEXT("����"),			//��ť���ƣ��ڰ�ť����ʾ��
           		       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,	//���ڷ��������ͺ�
           		       290, 10, 80, 40,	//���ꡢ����
           		       hWnd, 			//�丸������hwnd��������������
				       (HMENU)1,		//��ť��ID������������Ϊ0
				       ((LPCREATESTRUCT) lParam)->hInstance, //���ǵ�Ӧ�ó����ţ�������ͺ�
				       NULL) ;			//��NULL�ͺ�
         hdc = GetDC(hWnd);
         Init(hdc);
         SetTimer(hWnd,11,1000,TimerProc);	//��ʱ��idΪ11��ʱ����Ϊ1000ms��ʱ��ص�������TimerProc()
   
      } 
         break;
    case WM_KEYDOWN:
	    switch(wParam) {
		  case VK_UP:
            shape->Change(background);
            
            InvalidateRect(hWnd, NULL, TRUE);

			break;
          case VK_DOWN:

            shape->Down(background);
           
            InvalidateRect(hWnd, NULL, TRUE);		
			break;
		  case VK_LEFT:
            shape->Left(background);
            
            InvalidateRect(hWnd, NULL, TRUE);
			
            break;
		  case VK_RIGHT:

            shape->Right(background);
            
            InvalidateRect(hWnd, NULL, TRUE);		
			break;
		}
		break;

	case WM_COMMAND:
        wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
        switch(wParam){
				case 0:			//ID��Ϊ0�İ�ť������ 
					MessageBox(NULL, TEXT("��ʼ������"), TEXT("��ʾ"), MB_OK);
					break;
				case 1:			//ID��Ϊ1�İ�ť������ 
					MessageBox(NULL, TEXT("����������"), TEXT("��ʾ"), MB_OK);
					break;
			}


        // �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
      
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...	
        background->DrawSmallMap();

        background->DrawBigMap();

        TextOut (hdc, 290, 300, (LPCWSTR)szBuffer, wsprintf(szBuffer, TEXT("�ȼ�:    %d"), background->grade)) ;

        TextOut (hdc, 290, 400, (LPCWSTR)szBuffer, wsprintf(szBuffer, TEXT("����:    %d"), background->score)) ;

		EndPaint(hWnd, &ps);
      
        break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void CreateShape(BaseShape* &shape) {
//  srand((int)time(0));
  int shape_type = rand() % 7;

  switch(rand() % 7){		
		case 0:
          shape = new I_Shape;
          break;
		case 1:
          shape = new T_Shape;
          break;
		case 2:
          shape = new O_Shape;
          break;
		case 3:
          shape = new S_Shape;
          break;
		case 4:
          shape = new Z_Shape;
          break;
		case 5:
          shape = new L_Shape;
          break;
		case 6:
          shape = new J_Shape;
          break;
	}
}

void Init(HDC hdc) {
   background = new Background(hdc);

   CreateShape(shape);

   CreateShape(next_shape);

   background->SetSmallMap(next_shape->GetShape());

   background->SetBigMap(shape->GetShape(), shape->GetX(), shape->GetY());
}

   

VOID CALLBACK  TimerProc (HWND hWnd, UINT message, UINT iTimerID, DWORD dwTime){
  if (!shape->Down(background)) {
    background->FillBigMap(shape->GetShape(), shape->GetX(), shape->GetY());
    background->ClearLine();

    shape = next_shape;
    if (!shape->Bumb(background->GetBigMap())) {
      KillTimer(hWnd, 11);
      MessageBox(NULL, TEXT("��Ϸ����!"), TEXT("��ʾ"), MB_OK);
      return ;
    }
    CreateShape(next_shape);
    
    background->SetSmallMap(next_shape->GetShape());

    background->SetBigMap(shape->GetShape(), shape->GetX(), shape->GetY());
  }

  InvalidateRect(hWnd, NULL, TRUE);
}