////Speak me not

/*
The MIT License (MIT)

Copyright (c) 2013 Crazoter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

////METHOD: Console
////ALSO INCLUDES: Fake input method
//
//#include <iostream>
//#include <string.h>
//
//#include <Windows.h>//Window handling
//#include <tchar.h>//_T
//
////#include <Shlwapi.h>//UrlEscape
////#include "UriCodec.h"//UrlEncode
//
//using namespace std;
//
//void f___VLC();
//void f___VLC2(string networkURL);
//bool goToOpenMedia(HWND &vlcPlayer,HWND &f___ingVLC, HWND &shittyVLC,bool doLittlePause);
//
//void keyUp(INPUT&,WORD);
//void keyDown(INPUT&,WORD);
//
////void ForceForegroundWindow(INT_PTR);
//
//
//int thisWasMyain()
//{
//	//HWND shittyVLC = FindWindow(_T("QWidget"),_T("Open Media"));
//	//PostMessage(shittyVLC,
//	//PostMessage(shittyVLC, WM_CLEAR, 0,0);
//	//PostMessage(shittyVLC,EM_SETSEL,0,-1);
//	//SetWindowText(shittyVLC,"");
//	string input="";
//	cout << "Speak me not V2.0\nType in something you want me to say!\nSay nothing to exit." << endl;
//	//system("dir");
//	do
//	{
//		getline(cin,input);
//		if(input != "f___")
//		{
//			// = UriEncode(input);
//			string command = "vlcLNK.lnk -vvv ";
//			string networkURL = "\"http://translate.google.com/translate_tts?ie=UTF-8&q=";
//			networkURL.append(input);
//			networkURL.append("&tl=en&prev=input.mpeg\"");
//			command.append(networkURL);
//			command.append(" --qt-start-minimized --play-and-exit");
//			//cout << command << endl;
//			system(command.c_str());
//			/*Sleep(2000);
//			HWND prevWindow = GetForegroundWindow();
//			f___VLC();
//			Sleep(50);
//			f___VLC2(networkURL);
//			if(!SetForegroundWindow(prevWindow))
//			{
//				cout << "SETFOREGROUNDWINDOW DIDN'T f___ING WORK" << endl;
//				SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, 0, SPIF_UPDATEINIFILE);
//				if(!SetForegroundWindow(prevWindow))
//				{
//					cout << "SYSTEMPARAMETERSINFO DIDN'T f___ING WORK EITHER" << endl;
//				}
//			}
//			/*cout << BringWindowToTop(prevWindow);
//			cout << SetForegroundWindow(prevWindow) << endl;
//			SetFocus(prevWindow);*/
//			
//		}
//	}while(input != "");
//	system("pause");
//	return 0;
//}
//
//void f___VLC()
//{
//	// Create a generic keyboard event structure
//    /*INPUT ip;
//    ip.type = INPUT_KEYBOARD;
//    ip.ki.wScan = 0;
//    ip.ki.time = 0;
//    ip.ki.dwExtraInfo = 0;*/
//
//	//HWND vlcPlayer,f___ingVLC,shittyVLC;
//
//	//http://www.dreamincode.net/forums/topic/200043-simulate-mouse-click-to-non-foreground-window-using-sendmessage/
//
//	//Init
//	HWND vlcPlayer = FindWindow(_T("QWidget"),_T("VLC media player"));
//	WORD mouseX,mouseY;
//	
//	ShowWindow(vlcPlayer,SW_RESTORE);
//
//	if(!vlcPlayer)
//	{
//		cout << "Error Encountered : VLC media player not found" << endl;
//		return;
//	}
//	else
//	{
//		//Select f___ing Media
//		mouseX = 20;// x coord of mouse
//		mouseY = 10;// y coord of mouse
//		PostMessage(vlcPlayer,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		PostMessage(vlcPlayer,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//	}
//
//	Sleep(50);
//
//	//Per talk
//	HWND f___ingVLC = FindWindow(_T("QPopup"),_T("vlc"));
//	if(!f___ingVLC)
//	{
//		cout << "Error Encountered : VLC media player QPopup not found" << endl;
//		return;
//	}
//	else
//	{
//		//Select f___ing Open Network Stream
//		mouseX = 41;// x coord of mouse
//		mouseY = 100;// y coord of mouse
//		PostMessage(f___ingVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		PostMessage(f___ingVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));	
//
//		Sleep(50);
//		HWND shittyVLC = FindWindow(_T("QWidget"),_T("Open Media"));
//		if(!shittyVLC)
//		{
//			cout << "Error Encountered : VLC media player Open Media not found" << endl;
//			return;
//		}
//		else
//	//if(goToOpenMedia(vlcPlayer,f___ingVLC,shittyVLC,true))
//		{
//			//Clear text
//			RECT rect;
//			GetWindowRect(shittyVLC,&rect);
//			long height = rect.bottom - rect.top;
//			mouseX = 616;// x coord of mouse
//			mouseY = height - 60;// y coord of mouse
//			PostMessage(shittyVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//		}
//	}
//}
//
//void f___VLC2(string networkURL)
//{
//	// Create a generic keyboard event structure
//    /*INPUT ip;
//    ip.type = INPUT_KEYBOARD;
//    ip.ki.wScan = 0;
//    ip.ki.time = 0;
//    ip.ki.dwExtraInfo = 0;*/
//
//	//http://www.dreamincode.net/forums/topic/200043-simulate-mouse-click-to-non-foreground-window-using-sendmessage/
//
//	//Init
//	HWND vlcPlayer = FindWindow(_T("QWidget"),_T("VLC media player"));
//	WORD mouseX,mouseY;
//
//	ShowWindow(vlcPlayer,SW_RESTORE);
//
//	if(!vlcPlayer)
//	{
//		cout << "Error Encountered : VLC media player not found" << endl;
//		return;
//	}
//	else
//	{
//		//Select f___ing Media
//		mouseX = 20;// x coord of mouse
//		mouseY = 10;// y coord of mouse
//		PostMessage(vlcPlayer,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		PostMessage(vlcPlayer,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//	}
//
//	HWND f___ingVLC = FindWindow(_T("QPopup"),_T("vlc"));
//	if(!f___ingVLC)
//	{
//		cout << "Error Encountered : VLC media player QPopup not found" << endl;
//		return;
//	}
//	else
//	{
//		//Select f___ing Open Network Stream
//		mouseX = 41;// x coord of mouse
//		mouseY = 100;// y coord of mouse
//		PostMessage(f___ingVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		PostMessage(f___ingVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//
//		HWND shittyVLC = FindWindow(_T("QWidget"),_T("Open Media"));
//		if(!shittyVLC)
//		{
//			cout << "Error Encountered : VLC media player Open Media not found" << endl;
//			return;
//		}
//		else
//		{
//			RECT rect;
//			GetWindowRect(shittyVLC,&rect);
//			long height = rect.bottom - rect.top;
//			//Network tab
//			mouseX = 178;// x coord of mouse
//			mouseY = 24;// y coord of mouse
//			PostMessage(shittyVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//			//Select entire network URL (if exists)
//			mouseX = 41;// x coord of mouse
//			mouseY = 98;// y coord of mouse
//			PostMessage(shittyVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//			/*PostMessage(shittyVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//			*/
//			//back f___ing space please work
//			//f___ IT
//			//SendMessage(shittyVLC, WM_CHAR,(WPARAM)VK_BACK,1);
//			/*PostMessage(shittyVLC, WM_KEYDOWN, VK_BACK,0);
//			PostMessage(shittyVLC, WM_CHAR,'\b',1);
//			PostMessage(shittyVLC, WM_KEYUP, VK_BACK,(1 << 31));*/
//			//PostMessage(shittyVLC, WM_CHAR,'\b',1);
//			//Override
//
//			for(size_t i=0;i < networkURL.size();++i)
//			{
//				PostMessage(shittyVLC, WM_CHAR, networkURL[i],1);
//				//PostMessage(shittyVLC, WM_KEYUP, VK_BACK,(1 << 31));
//			}
//			
//			//Press Play
//			mouseX = 533;// x coord of mouse, non-variable
//			mouseY = height - 60;// y coord of mouse
//			PostMessage(shittyVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//			PostMessage(shittyVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//
//			ShowWindow(vlcPlayer,SW_SHOWMINIMIZED);
//			//Gasm
//		}
//
//		//Some other shit
//		//PostMessage(vlcPlayer, WM_COMMAND, MAKEWPARAM(openNetworkStream, 0), 0);	
//		//keyDown(ip,VK_CONTROL);
//		//PostMessage(f___ingVLC, WM_KEYDOWN, VK_CONTROL,0x001D0001);
//		//PostMessage(f___ingVLC, WM_KEYDOWN, 'N',0x00310001);
//		//Sleep(200);
//		//PostMessage(vlcPlayer, WM_KEYUP, 'N', 0xC01D0001);
//        //PostMessage(vlcPlayer, WM_KEYUP, VK_CONTROL, 0xC01D0001);
//		//keyUp(ip,VK_CONTROL);
//		//HWND prevWindow = GetForegroundWindow();
//		//SendMessage(shittyVLC, WM_KEYDOWN, VK_BACK,0);
//		//SendMessage(shittyVLC, WM_KEYUP, VK_BACK,(1 << 31));
//		//PostMessage(shittyVLC,WM_COPYDATA,NULL,
//		//PostMessage(f___ingVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		//PostMessage(f___ingVLC, WM_KEYDOWN, VK_CONTROL,0x001D0001);
//		//PostMessage(f___ingVLC, WM_KEYDOWN, VK_CONTROL,0x001D0001);
//	}
//}
//
//bool goToOpenMedia(HWND &vlcPlayer,HWND &f___ingVLC, HWND &shittyVLC,bool doLittlePause)
//{
//		// Create a generic keyboard event structure
//    INPUT ip;
//    ip.type = INPUT_KEYBOARD;
//    ip.ki.wScan = 0;
//    ip.ki.time = 0;
//    ip.ki.dwExtraInfo = 0;
//
//	//http://www.dreamincode.net/forums/topic/200043-simulate-mouse-click-to-non-foreground-window-using-sendmessage/
//
//	//Init
//	vlcPlayer = FindWindow(_T("QWidget"),_T("VLC media player"));
//	WORD mouseX,mouseY;
//
//	ShowWindow(vlcPlayer,SW_RESTORE);
//
//	if(!vlcPlayer)
//	{
//		cout << "Error Encountered : VLC media player not found";
//		return false;
//	}
//	else
//	{
//		//Select f___ing Media
//		mouseX = 20;// x coord of mouse
//		mouseY = 10;// y coord of mouse
//		PostMessage(vlcPlayer,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		PostMessage(vlcPlayer,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));
//	}
//
//	if(doLittlePause)
//		Sleep(50);
//
//	//Per talk
//	f___ingVLC = FindWindow(_T("QPopup"),_T("vlc"));
//	if(!f___ingVLC)
//	{
//		cout << "Error Encountered : VLC media player QPopup not found";
//		return false;
//	}
//	else
//	{
//		//Select f___ing Open Network Stream
//		mouseX = 41;// x coord of mouse
//		mouseY = 100;// y coord of mouse
//		PostMessage(f___ingVLC,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
//		PostMessage(f___ingVLC,WM_LBUTTONUP,0,MAKELPARAM(mouseX,mouseY));	
//
//		Sleep(50);
//		HWND shittyVLC = FindWindow(_T("QWidget"),_T("Open Media"));
//		if(!shittyVLC)
//		{
//			cout << "Error Encountered : VLC media player Open Media not found";
//			return false;
//		}
//		return true;
//	}
//}
//
//void keyUp(INPUT &ip,WORD w)
//{
//	ip.ki.wVk = w;
//    ip.ki.dwFlags = KEYEVENTF_KEYUP;
//    SendInput(1, &ip, sizeof(INPUT));
//}
//
//void keyDown(INPUT &ip,WORD w)
//{
//	ip.ki.wVk = w;
//    ip.ki.dwFlags = 0; // 0 for key press
//    SendInput(1, &ip, sizeof(INPUT));
//}