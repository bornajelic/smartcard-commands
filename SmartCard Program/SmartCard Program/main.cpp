#include "card_Functionality.h"
#include "helpers.h"

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
#define CHECKBOX 5
#define GENERATE_BUTTON_2 6
#define CHECKBOX_2 7
#define GENERATE_BUTTON_3 8
#define GENERATE_BUTTON_4 9
#define GENERATE_BUTTON_5 10
#define GENERATE_BUTTON_6 11
//handleri
HMENU hMenu;
HWND hName, hAge, hOut, hOut2, hOut3, hOut4, hBut, hBut2, hBut3, hBut4, hBut5, hOut5, hBut6, hOut6;
//std::string reader, atr, challenge="";
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void addMenus(HWND);
void addControls(HWND hWnd);
Card card;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	//hInst -> ID of applicaton which is passed to the operating system(instanca nase aplikacije)
	try {
		WNDCLASSW wc = { 0 };
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hInstance = hInst;
		wc.lpszClassName = L"myWindowClass";
		wc.lpfnWndProc = WindowProcedure; //pointer to a function


		if (!RegisterClassW(&wc)) {
			return -1;
		}
		else {
			CreateWindowW(L"myWindowClass", L"SMARTCARD CONTROLLER", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 400, NULL, NULL, NULL, NULL);
			MSG msg = { 0 };
			while (GetMessage(&msg, NULL, NULL, NULL)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	catch (MyException ex) {
		std::cout << ex.what();
	}

	return 0;

}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	try {
		switch (msg) {

		case WM_COMMAND: //some control was presssed (wp je indetitet )
		
			switch (wp) {

			case FILE_MENU_EXIT:
				DestroyWindow(hWnd);
				break;
			case FILE_MENU_NEW:
				MessageBeep(MB_ICONINFORMATION);
				break;
			
			case GENERATE_BUTTON:
			{
				
				SetWindowText(hOut, card.getATR().c_str());
				UpdateWindow(hOut);
				break;
			}

			case GENERATE_BUTTON_2:
			{
				
				SetWindowText(hOut2, card.getReader().c_str());
				break;
			}

			case GENERATE_BUTTON_3:
			{

				SetWindowText(hOut3, card.getCommand("0084000008").c_str());
				break;
			}

			case GENERATE_BUTTON_4:
			{
				SetWindowText(hOut4, card.getCommand("FFCA000080").c_str());
				break;
			}
			case GENERATE_BUTTON_5:
			{
				
				std::string s2 = card.getCommand("00A4040C06FF534D524454");

				int l = s2.length();
				SetWindowText(hOut5, s2.c_str());
				break;
			}
			case GENERATE_BUTTON_6:
			{

				std::string s2 = card.getCommand("00A4040007A000000003201000");
				SetWindowText(hOut6, s2.c_str());
				break;
			}

			}
			break;
		case WM_CREATE:
			addMenus(hWnd); //window handler as argument
			addControls(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
		}
	}
	catch (MyException &ex) {
		std::cout << ex.what();
	}

}

void addMenus(HWND hWnd) {

	hMenu = CreateMenu();
	HMENU  hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	
	SetMenu(hWnd, hMenu);
}
void addControls(HWND hWnd) {
	
	
	hBut = CreateWindowW(L"Button", L"ATR", WS_VISIBLE | WS_CHILD, 30, 50, 58, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
	hOut = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 50, 400, 38, hWnd, NULL, NULL, NULL);

	hBut2 = CreateWindowW(L"Button", L"Reader", WS_VISIBLE | WS_CHILD, 30, 100, 58, 38, hWnd, (HMENU)GENERATE_BUTTON_2, NULL, NULL);
	hOut2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 100, 400, 38, hWnd, NULL, NULL, NULL);

	hBut3 = CreateWindowW(L"Button", L"Chall.", WS_VISIBLE | WS_CHILD, 30, 150, 58, 38, hWnd, (HMENU)GENERATE_BUTTON_3, NULL, NULL);
	hOut3 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 150, 400, 38, hWnd, NULL, NULL, NULL);

	hBut4 = CreateWindowW(L"Button", L"UID", WS_VISIBLE | WS_CHILD, 30, 200, 58, 38, hWnd, (HMENU)GENERATE_BUTTON_4, NULL, NULL);
	hOut4 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 200, 400, 38, hWnd, NULL, NULL, NULL);

	hBut5 = CreateWindowW(L"Button", L"Info", WS_VISIBLE | WS_CHILD, 30, 250, 58, 38, hWnd, (HMENU)GENERATE_BUTTON_5, NULL, NULL);
	hOut5 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 250, 400, 38, hWnd, NULL, NULL, NULL);

	hBut6 = CreateWindowW(L"Button", L"AID", WS_VISIBLE | WS_CHILD, 30, 300, 58, 38, hWnd, (HMENU)GENERATE_BUTTON_6, NULL, NULL);
	hOut6 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 300, 400, 38, hWnd, NULL, NULL, NULL);

}


//int main() {
//	try {
//		Card card;
//		std::vector<std::string> v = card.readersVector;
//		for (auto i = v.begin(); i != v.end(); ++i) {
//			std::cout << *i << std::endl;
//		}
//		std::cout << card.getATR() << "\n";
//		std::cout << card.getCommand("00A4040C06FF534D524454") << "\n"; //info
//		std::cout << card.getCommand("0084000008") << "\n"; //challenge
//		
//		std::cout << card.getCommand("FFCA000000") << "\n"; //UID
//		std::cout << card.getCommand("00A4040007A000000003201000") << "\n"; //AID
//
// 	}
//	
//	catch (MyException e){
//		std::cout << e.what();
//	}
//}