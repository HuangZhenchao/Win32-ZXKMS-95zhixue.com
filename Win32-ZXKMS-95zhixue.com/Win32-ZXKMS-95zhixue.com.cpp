// Win32-ZXKMS-95zhixue.com.cpp : 定义应用程序的入口点。
//
#include "stdafx.h"
#include "Win32-ZXKMS-95zhixue.com.h"
#include <Shlwapi.h>
#pragma comment(lib,"shlwapi.lib")


#define MAX_LOADSTRING 100

struct WNDINI {
	int WndMainX;
	int WndMainY;
	int WndMainWidth;
	int WndMainHeight;
};
WNDINI WndIni = { 0 };

// 全局变量: 
HINSTANCE hInst;							// 当前实例
HWND hWndMain;
HWND hWndSide;
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

WCHAR path[MAX_PATH];							//运行程序文件或dll所在的位置
WCHAR IniPath[MAX_PATH];


// 此代码模块中包含的函数的前向声明: 
ATOM                RegWndMain(HINSTANCE hInstance);
ATOM                RegWndSide(HINSTANCE hInstance);
ATOM                RegWndCatalog(HINSTANCE hInstance);
ATOM                RegWndFileList(HINSTANCE hInstance);
ATOM                RegWndSpiltter(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int					WriteWndIni();					//用来写入Windows配置文件
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32ZXKMS95ZHIXUECOM, szWindowClass, MAX_LOADSTRING);
	//初始化path
	HMODULE hModule = GetModuleHandleW(NULL);
	GetModuleFileName(hModule, path, MAX_PATH);
	// setting -> link add Shlwapi.lib   #include <Shlwapi.h>
	PathRemoveFileSpec(path);
	//初始化配置文件路径
	wcscpy_s(IniPath, path);
	wcscat_s(IniPath, L"\\wnd.ini");

	//从配置文件取出结构体到WndIniRead
	if (!GetPrivateProfileStruct(_T("Windows"), _T("Struct"), &WndIni, sizeof(WndIni), IniPath))
	{
		WndIni.WndMainX = CW_USEDEFAULT;
		WndIni.WndMainY = 0;
		WndIni.WndMainWidth = CW_USEDEFAULT;
		WndIni.WndMainHeight = 0;
	}


	//用于测试字符串变量
	WCHAR DebugOutputField[] = L"测试";
	WCHAR DebugOutputInfo[] = L"字符串变量输出测试可行";
	WCHAR DebugOutputFilePath[] = L"D:\\DebugOutputFile.ini";
	WritePrivateProfileString(_T("Debug"), DebugOutputField, DebugOutputInfo, DebugOutputFilePath);

	//wchar_t tempStr[10];
	//_itow_s(WndIniRead.WndMainWidth, tempStr, 10);


	RegWndMain(hInstance);
	RegWndSide(hInstance);
    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32ZXKMS95ZHIXUECOM));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  函数: RegWndMain()
//
//  目的: 注册主窗口类。
//
ATOM RegWndMain(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32ZXKMS95ZHIXUECOM));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32ZXKMS95ZHIXUECOM);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}
//
//  函数: RegWndSide()
//
//  目的: 注册侧边栏窗口类。
//
ATOM RegWndSide(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(42, 51, 60));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"WndSide";
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
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
   hInst = hInstance; // 将实例句柄存储在全局变量中


   hWndMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   WndIni.WndMainX, WndIni.WndMainY, WndIni.WndMainWidth, WndIni.WndMainHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWndMain)
   {
      return FALSE;
   }

   ShowWindow(hWndMain, nCmdShow);
   UpdateWindow(hWndMain);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		
		hWndSide = CreateWindowEx(NULL, L"WndSide", NULL, WS_CHILD | WS_VISIBLE,
			0, 0, 50, 50, hWnd, NULL, hInst, NULL);
		

	}
	case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hWnd,&rect);
			int widthClient = rect.right - rect.left;  // 获得客户区宽度
			int heightClient = rect.bottom - rect.top;  // 获得客户区高度
			MoveWindow(hWndSide,0, 0, 50, heightClient,TRUE);
		}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		WriteWndIni();
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

int WriteWndIni() 
{
	RECT rect;
	GetWindowRect(hWndMain, &rect);
	int widthWndMain = rect.right - rect.left;  // 获得主窗体宽度
	int heightWndMain = rect.bottom - rect.top;  // 获得主窗体高度
	WndIni.WndMainX = rect.left;
	WndIni.WndMainY = rect.top;
	WndIni.WndMainWidth = widthWndMain;
	WndIni.WndMainHeight = heightWndMain;
	return WritePrivateProfileStruct(_T("Windows"), _T("Struct"), &WndIni, sizeof(WndIni), IniPath);
	
}