// 俄罗斯方块.cpp : 定义应用程序的入口点。

#include "stdafx.h"
#include "俄罗斯方块.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
    
Background *background = NULL;
BaseShape *shape = NULL;
BaseShape *next_shape = NULL;
TCHAR szBuffer[10];

// 此代码模块中包含的函数的前向声明:
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

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
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
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
         CreateWindowEx(0,		//添0就好
           		       TEXT("button"),		//按钮类，windows已为我们注册好，回调函数也已写好
           		       TEXT("开始"),			//按钮名称（在按钮上显示）
           		       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,	//窗口风格，这样添就好
           		       20, 10, 80, 40,	//坐标、长宽
           		       hWnd, 			//其父窗口是hwnd，即我们主窗口
				       (HMENU)0,		//按钮的ID，这里我们设为0
				       ((LPCREATESTRUCT) lParam)->hInstance, //我们的应用程序编号，这样添就好
				       NULL) ;			//添NULL就好
         CreateWindowEx(0,		//添0就好
           		       TEXT("button"),		//按钮类，windows已为我们注册好，回调函数也已写好
           		       TEXT("结束"),			//按钮名称（在按钮上显示）
           		       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,	//窗口风格，这样添就好
           		       290, 10, 80, 40,	//坐标、长宽
           		       hWnd, 			//其父窗口是hwnd，即我们主窗口
				       (HMENU)1,		//按钮的ID，这里我们设为0
				       ((LPCREATESTRUCT) lParam)->hInstance, //我们的应用程序编号，这样添就好
				       NULL) ;			//添NULL就好
         hdc = GetDC(hWnd);
         Init(hdc);
         SetTimer(hWnd,11,1000,TimerProc);	//定时器id为11，时间间隔为1000ms，时间回调函数是TimerProc()
   
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
				case 0:			//ID号为0的按钮被按下 
					MessageBox(NULL, TEXT("开始被按下"), TEXT("提示"), MB_OK);
					break;
				case 1:			//ID号为1的按钮被按下 
					MessageBox(NULL, TEXT("结束被按下"), TEXT("提示"), MB_OK);
					break;
			}


        // 分析菜单选择:
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
		// TODO: 在此添加任意绘图代码...	
        background->DrawSmallMap();

        background->DrawBigMap();

        TextOut (hdc, 290, 300, (LPCWSTR)szBuffer, wsprintf(szBuffer, TEXT("等级:    %d"), background->grade)) ;

        TextOut (hdc, 290, 400, (LPCWSTR)szBuffer, wsprintf(szBuffer, TEXT("分数:    %d"), background->score)) ;

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

// “关于”框的消息处理程序。
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
      MessageBox(NULL, TEXT("游戏结束!"), TEXT("提示"), MB_OK);
      return ;
    }
    CreateShape(next_shape);
    
    background->SetSmallMap(next_shape->GetShape());

    background->SetBigMap(shape->GetShape(), shape->GetX(), shape->GetY());
  }

  InvalidateRect(hWnd, NULL, TRUE);
}