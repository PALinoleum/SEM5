// OS_4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OS_4.h"

#define _USE_MATH_DEFINES
#include <math.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

//some shit happens there
MEMORYSTATUS memStatus;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	MMDialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OS_4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	memStatus.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memStatus);


	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OS_4));

	// Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//

int getX(float radius, float angle, int xOffset)
{
	return radius * (float)cos(angle * M_PI / 180.) + xOffset + radius;
}

int getY(float radius, float angle, int yOffset)
{
	return radius * (float)sin(angle * M_PI / 180.) + yOffset + radius;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OS_4));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OS_4);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	int diagSize = 200;

	RECT windRect;
	HBRUSH redBrush;
	HBRUSH oldBrush;

	TCHAR infoString[200];

	int height, width, xOffset, yOffset, x1, y1, x2, y2;
	float nonFree;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_MMBUTTON:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_MMDIALOG), hWnd, MMDialog);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		GetClientRect(hWnd, &windRect);

		height = windRect.bottom - windRect.top;
		width = windRect.right - windRect.left;

		xOffset = 100;
		yOffset = 100;

		Ellipse(hdc, xOffset, yOffset, xOffset + diagSize, yOffset + diagSize);

		Ellipse(hdc, xOffset + diagSize + 30, yOffset, xOffset + diagSize * 2 + 30, yOffset + diagSize);

		Ellipse(hdc, xOffset + diagSize * 2 + 60, yOffset, xOffset + diagSize * 3 + 60, yOffset + diagSize);

		redBrush = CreateSolidBrush(RGB(150, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, redBrush);

		//занятая память
		wsprintf(infoString, L"Занято %i процентов памяти", memStatus.dwMemoryLoad);

		x1 = getX(diagSize / 2, 0., xOffset);
		y1 = getY(diagSize / 2, 0., yOffset);
		x2 = getX(diagSize / 2, memStatus.dwMemoryLoad * 360 / 100, xOffset);
		y2 = getY(diagSize / 2, memStatus.dwMemoryLoad * 360 / 100, yOffset);

		Pie(hdc, xOffset, yOffset, xOffset + diagSize, yOffset + diagSize, x1, y1, x2, y2);

		TextOut(hdc, xOffset, yOffset - 20, infoString, wcslen(infoString));

		//занятая физическая память
		nonFree =  (float)((memStatus.dwTotalPhys - memStatus.dwAvailPhys) / (float)memStatus.dwTotalPhys);
		wsprintf(infoString, L"Занято %i процентов физической памяти", (int)(nonFree * 100));

		x1 = getX(diagSize / 2, 0., xOffset + diagSize + 30);
		y1 = getY(diagSize / 2, 0., yOffset);
		x2 = getX(diagSize / 2, nonFree * 360, xOffset + diagSize + 30);
		y2 = getY(diagSize / 2, nonFree * 360, yOffset);

		Pie(hdc, xOffset + diagSize + 30, yOffset, xOffset + diagSize * 2 + 30, yOffset + diagSize, x1, y1, x2, y2);

		TextOut(hdc, xOffset + diagSize + 30, yOffset - 20, infoString, wcslen(infoString));

		//занятая виртуальная память
		nonFree =  (float)((memStatus.dwTotalPageFile - memStatus.dwAvailPageFile) / (float)memStatus.dwTotalPageFile);
		wsprintf(infoString, L"Используется %i процентов файла подкачки", (int)(nonFree * 100));

		x1 = getX(diagSize / 2, 0., xOffset + diagSize * 2 + 60);
		y1 = getY(diagSize / 2, 0., yOffset);
		x2 = getX(diagSize / 2, nonFree * 360, xOffset + diagSize * 2 + 60);
		y2 = getY(diagSize / 2, nonFree * 360, yOffset);

		Pie(hdc, xOffset + diagSize * 2 + 60, yOffset, xOffset + diagSize * 3 + 60, yOffset + diagSize, x1, y1, x2, y2);

		TextOut(hdc, xOffset + diagSize * 2 + 60, yOffset - 20, infoString, wcslen(infoString));


		DeleteObject(SelectObject(hdc, oldBrush));
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

// Message handler for about box.
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

INT_PTR CALLBACK MMDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	MEMORY_BASIC_INFORMATION basicInfo;
	TCHAR tempString[300];
	TCHAR memState[3][20] = {L"FREE", L"RESERVED", L"COMMITED"};
	TCHAR memType[3][20] = {L"IMAGE", L"MAPPED", L"PRIVATE"};
	TCHAR *state, *type;
	long *point = 0;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:


		while(VirtualQuery(point, &basicInfo, sizeof(MEMORY_BASIC_INFORMATION)))
		{
	
			switch(basicInfo.State)
			{
			case MEM_FREE:
				state = memState[0];
				break;
			case MEM_RESERVE:
				state = memState[1];
				break;
			case MEM_COMMIT:
				state = memState[2];
				break;
			}

			switch(basicInfo.Type)
			{
			case MEM_IMAGE:
				type = memType[0];
				break;
			case MEM_MAPPED:
				type = memType[1];
				break;
			case MEM_PRIVATE:
				type = memType[2];
				break;
			default:
				type = memType[2];
			}
			wsprintf(tempString, L"Base adr: %p\t Reg Size: %i \t State: %s \t Type: %s", basicInfo.AllocationBase, basicInfo.RegionSize, state, type);
			SendMessage(GetDlgItem(hDlg, IDC_MMLIST), LB_ADDSTRING, 0, (LPARAM)tempString);
			point = point + basicInfo.RegionSize;
		}
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