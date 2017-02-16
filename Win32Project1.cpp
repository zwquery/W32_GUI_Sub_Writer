// Win32Project1.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include "stdafx.h"
#include "Win32Project1.h"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"

#include <stdlib.h>
#include <comdef.h>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAX_LOADSTRING 100
#define BUFFER_SIZE 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



void iswine(){

	HKEY hKey;
	//Assume hKey contains a valid HKEY obtained from calling RegOpenKeyEx(...)
	LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Wine", 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey);
	
	if (result == ERROR_SUCCESS) {
	
	}
	else if (result == ERROR_FILE_NOT_FOUND) {
	MessageBox(NULL,L"This program is NOT used in Wine, it will close", L"Fatal error", 0);
	PostQuitMessage(0);
	}
	else {
	MessageBox(NULL,L"This program is NOT used in Wine, it will close", L"Fatal error", 0);
	PostQuitMessage(0);
	}

}

void writeKey(){

	HKEY hkey;
	    DWORD dwDisposition;
	    if(RegCreateKeyEx(HKEY_CURRENT_USER,
	      TEXT("Software\\SOFT_NAME\\KEY"),
	      0, NULL, 0,
	      KEY_WRITE, NULL,
	      &hkey, &dwDisposition) == ERROR_SUCCESS)
	    {

			LPCTSTR data = TEXT("VALUE");

	    	if (RegSetValueEx(hkey, L"VALUE", 0, REG_SZ, (LPBYTE)data, _tcslen(data) * sizeof(TCHAR)) != ERROR_SUCCESS)
	    	{
	    		cout <<"Unable to set registry value value_name";
	    	}
	    	else
	    	{
	//    		cout << "OK)" << endl;
	    	}

	    	RegCloseKey(hkey);
	    	}
	    	else
	        MessageBox(NULL,L"error",L"",0);
			}



const std::string forbiddenChars = "\\";

static char ClearForbidden(char toCheck)
{
    if(forbiddenChars.find(toCheck) != string::npos)
    {
         return '/';
    }

    return toCheck;
}


  	bool ListDirectoryContents(const wchar_t *sDir)
{ 
    WIN32_FIND_DATA fdFile; 
    HANDLE hFind = NULL; 

    wchar_t sPath[2048]; 

    //Specify a file mask. *.* = We want everything! 
    wsprintf(sPath, L"%s\\FOLDER\\*.*", sDir); 

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE) 
    { 
        wprintf(L"Path not found: [%s]\n", sDir); 
        return false; 
    } 

    do
    { 
        //Find first file will always return "."
        //    and ".." as the first two directories. 
        if(wcscmp(fdFile.cFileName, L".") != 0
                && wcscmp(fdFile.cFileName, L"..") != 0) 
        { 
            //Build up our file path using the passed in 
            //  [sDir] and the file/foldername we just found: 
            wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName); 

            //Is the entity a File or Folder? 
            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) 
            { 
                wprintf(L"Directory: %s\n", sPath);

				std::wstring mywstring(sPath);
				std::wstring mywstring2(fdFile.cFileName);
				std::wstring to_display = L"Product '" + mywstring2 + L"' is activated !";
				LPCWSTR concatted = to_display.c_str();

							MessageBoxW(NULL, concatted, L"Information", MB_ICONINFORMATION);



				std::wstring fullpath(sDir);
				std::wstring fullpath2(fdFile.cFileName);
				std::wstring fullpath3 = fullpath + L"\\FOLDER\\" + fullpath2 + L"\\FILE_TO_MODIFY";
				LPCWSTR fullpath4 = fullpath3.c_str();

				//MessageBoxW(NULL, fullpath4, L"Information", MB_ICONINFORMATION);

    HANDLE hFindo = NULL; 
    wchar_t sPatho[2048]; 

	//Specify a file mask. *.* = We want everything! 
    wsprintf(sPatho, L"%s\\FILE_TO_MODIFY", sPath); 

//r4c10	MessageBoxW(NULL, sPatho, L"Information", MB_ICONINFORMATION); --> fullpath3 or fullpath4


	std::string soo;
	#ifdef UNICODE
    std::wstring w;
    w = sPatho;
	std::wstring ali = w + L"FOLDER";
	std::transform(ali.begin(), ali.end(), ali.begin(), ClearForbidden);
    soo = std::string(ali.begin(), ali.end()); // magic here
#else
     soo = input;
#endif


	/*
	std::transform(mywstring.begin(), mywstring.end(), mywstring.begin(), ClearForbidden);
	LPCWSTR erf = mywstring.c_str();
	MessageBoxW(NULL, erf, L"Information", MB_ICONINFORMATION);
	*/

	//Convert to prepare...


	// Get UGCPATH var
	string line;
	string ugcpath;
	ifstream f (fullpath3);
	int i = 0;

	while(getline(f, line)) {
		if (i == 1){
        ugcpath = line;

			LPCSTR ugcpath;
			std::string s = line;
			ugcpath = (LPCSTR)s.c_str();
			OutputDebugStringA(ugcpath);
		}
	i++;
	}
	
	 f.close();




	
	 // Write to file
		// Return value from "PathFileExists".
    int retval;
    
    // Search for the presence of a file with a true result.
    retval = PathFileExists(fullpath4);
    if(retval == 1)
    {
		/*
	  errno_t err;
	  FILE *pFile;
	  */



	  //const char *fullpath_final;
	  
	  size_t outputSize = fullpath3.length() + 1; // +1 for null terminator
	  char * outputString;
	  outputString = new char[outputSize];
	  size_t charsConverted = 0;
      const wchar_t * inputW = fullpath3.c_str();
	  wcstombs_s(&charsConverted, outputString, outputSize, inputW, fullpath3.length());

	  const char *mycharp = ugcpath.c_str();



	  /*
	  	ofstream log;
		log.open ("log.txt");
		log << fullpath4;
		log << ugcpath;
		log.close();
	 */


	  ofstream g;
	  g.open(fullpath3);
	  g << "activated\n";
	  g << ugcpath;
	  g << "\n                                                                                                                                              ";
	  g.close();

	  /*
      err = fopen_s(&pFile, outputString, "r+");
      fputs("activated\n", pFile);
	  //fputs(mycharp, pFile);
	  fputs("\n                                                                                                                                              ", pFile);
	  fseek(pFile, 10, SEEK_SET);
	  fclose(pFile);
	  */
	}




				//MessageBoxW(NULL, concatted, L"Information", MB_ICONINFORMATION);
                //ListDirectoryContents(sPath); //Recursion, I love it! 
            } 
            else{ 
                wprintf(L"File: %s\n", sPath); 
            } 
        }
    } 
    while(FindNextFile(hFind, &fdFile)); //Find the next file. 

    FindClose(hFind); //Always, Always, clean things up! 

    return true; 
} 



int patch_files(){
	//MessageBoxW(NULL, (LPWSTR)L"Patched !", L"Information", MB_ICONINFORMATION);




	


	/*******GET APPDATA FOLDER*********/
		DWORD bufferSize = 65535; //Limit according to http://msdn.microsoft.com/en-us/library/ms683188.aspx
		std::wstring buff;
		std::wstring buffo;
		buff.resize(bufferSize);
		bufferSize = GetEnvironmentVariableW(L"APPDATA", &buff[0], bufferSize);
		if (!bufferSize)
		 //error
		buff.resize(bufferSize);

	LPCWSTR pathok;
	std::wstring t = buff;
	pathok = (LPCWSTR)t.c_str();
	ListDirectoryContents(pathok);


	return 0;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
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

   hWnd = CreateWindow(szWindowClass, szTitle, /*WS_OVERLAPPEDWINDOW*/WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
      GetSystemMetrics(SM_CXSCREEN) /3 , GetSystemMetrics(SM_CYSCREEN) /3, 600, 200, NULL, NULL, hInstance, NULL);

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
	//HDC hdc = BeginPaint(hWnd, &ps);

	HDC hdc, MemDCExercising;
    PAINTSTRUCT Ps;
    HBITMAP bmpExercising;
	

	switch (message)
	{
	case WM_CREATE:
		// Create a push button
		HWND hWndButton;
		HGDIOBJ hfDefault;
		
		hfDefault=GetStockObject(DEFAULT_GUI_FONT);
		hWndButton=CreateWindowEx(NULL,
				L"BUTTON",
				L"Run",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				150,
				20,
				60,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);


		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDC_MAIN_BUTTON:
		{
			//MessageBoxW(NULL, (LPWSTR)L"OK !", L"Information", MB_ICONINFORMATION);
			iswine();
			patch_files();
			writeKey();
		}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &Ps);
		// Load the bitmap from the resource
	    bmpExercising = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXERCISING));
	    // Create a memory device compatible with the above DC variable
	    MemDCExercising = CreateCompatibleDC(hdc);
             // Select the new bitmap
             SelectObject(MemDCExercising, bmpExercising);

	    // Copy the bits from the memory DC into the current dc
	    BitBlt(hdc, 5, 5, 850, 600, MemDCExercising, 0, 0, SRCCOPY);

	    // Restore the old bitmap
	    DeleteDC(MemDCExercising);
	    DeleteObject(bmpExercising);
		// TODO: Add any drawing code here...
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
