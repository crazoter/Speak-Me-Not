//Speak me not V5.0

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

//TODO: Global Home key cooldown

#include <iostream>
#include <string.h>
#include "UriCodec.h"//UrlEncode

//Global mode
#include <Windows.h>
#ifdef max 
#undef max
#endif 
#ifdef min
#undef min
#endif 

#include <thread>        
#include <mutex>          

//Long MSG submission Console
#include <deque>
#include <sstream>

//Hot Text
#include <fstream>
#include <map>
#include <algorithm>
#include <iterator>

//Timing
#pragma comment(lib, "winmm.lib")

using namespace std;

//Global variables
const int FPS = 10;//30;
const string KILLPHRASE = "\\exit";
const int CHAR_LIMIT = 100;
const int UPDATE_INTERVAL_MS_HIGH = 40;
const int UPDATE_INTERVAL_MS_LOW = 500;
const int PAINT_INTERVAL_MS = 1000/FPS;//Yeah I know it's not 100% accurate... LIKE I REALLY GIVE A f___
const int COUNT_LIMIT = 10;
const int COUNT_RESET = 10;

int UPDATE_INTERVAL_MS_NOW = UPDATE_INTERVAL_MS_HIGH;
bool useHotText = true;
bool hasRegisteredClassEx;
int mode = 0;
bool isActive_GLOBAL = false;
HWND currWindow = NULL;
char prevChar = NULL;
static HWND hwnd_label;

map<string,string> map_hotText;

//Methods
int consoleMode();
void globalMode();
void globalMode_old();
int handleInput(string input);
void printHelp();

string convertToSpeechURL(string input);
void sendToVLC(string input, bool async);
void prepLongMsgToVLC(string &command,string input,char delim,unsigned int length);

int handleKeyState(string &input,int &count);
void toggleIsActive();
bool manageCount(int &count,char currChar);
bool checkKey(int vk,char theChar,string &input,int &count);

void doubleBufferText(HWND,string);
void updateText(HWND,string);

void setupHotText();
string hotText_processInput(string input);

void displayHoldTime();

deque<string> &split(const std::string &s, char delim, std::deque<std::string> &elems, bool skipEmpty);
deque<string> split(const std::string &s, char delim, bool skipEmpty);


//IMPLEMENTATION

template <class charT, class traits>
std::basic_istream<charT, traits>&
empty_buffer(std::basic_istream<charT, traits>& is)
{
    std::basic_streambuf<charT, traits>* p = is.rdbuf();
    p->pubseekpos(0, std::ios_base::in);

    return is.ignore(std::numeric_limits<std::streamsize>::max());
}

long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
    switch(msg)
    {
        case WM_DESTROY:
            cout << "\nDestroying window...\n" ;
			DestroyWindow(hwnd_label);
            PostQuitMessage(0) ;
            return 0L ;
        default:
            //std::cout << '.' ;
            return DefWindowProc( window, msg, wp, lp ) ;
    }
}
void updateWindow_thread(HWND window,HWND hwnd_label)
{
	string input="";
	long updateTime,currentTime;
	updateTime = timeGetTime();//
	int heldCount = 0;
	while(mode == 1)
	{
	//Update
		currentTime = timeGetTime();
		if(currentTime - updateTime >= UPDATE_INTERVAL_MS_NOW)
		{
			updateTime = currentTime;
			//Check for input
			int hksCase;
			if((hksCase = handleKeyState(input,heldCount)) != 0)
			{
				switch(hksCase)
				{
					case 1://open without activate
						SetWindowPos(window,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
						ShowWindow( window, SW_SHOWNOACTIVATE );
						break;
					case 2://close 
						SetWindowPos(window, HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
						ShowWindow( window, SW_MINIMIZE );
						break;
					case 3://update text
						SetWindowText(hwnd_label, ("Global: " + input).c_str());
						break;
				}
			}
		}
	//Paint
		/*if(isActive_GLOBAL)
		{
			if(currentTime - paintTime >= PAINT_INTERVAL_MS)
			{
				paintTime = currentTime;

				//DWORD dwExStyle = ::GetWindowLong(window, GWL_EXSTYLE);
				//if (window != GetAncestor(window,GA_ROOT))//GetWindow(window,GW_HWNDFIRST) != window)//((dwExStyle & WS_EX_TOPMOST) != 0)
				//{
					//Set it to top, if it isn't
					//SetWindowPos(window,HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
				//}
			}
		}*/
	}
	PostMessage( window, WM_CLOSE, 0, 0 );
}

int main()
{
	cout << "Loading..." << endl;
	setupHotText();
	cout << endl << "=-----------------" << endl <<
			        "Speak me not V5.0" << endl << 
		            "=-----------------" << endl <<
			"Type in something you want me to say!\nInput \\help for help." << endl;
	while(mode != -1)
	{
		if(mode == 0)
		{
			mode = consoleMode();
		}
		else if(mode == 1)
		{
			globalMode();//The mode is set in handleKeyInput at Return
			//empty_buffer(cin);
			//cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
	}
	system("pause");
	return 0;
}

int consoleMode()
{
	string input;
	do
	{
		cout << "Console: ";
		getline(cin,input);
		int result = handleInput(input);
		if(result != 0)
			return result;
	}while(input != KILLPHRASE);
	return -1;
}
void globalMode()
{
	const char* const myclass = "myclass" ;
	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
							0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
							LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
							0, myclass, LoadIcon(0,IDI_APPLICATION) } ;

	if(!hasRegisteredClassEx)
		hasRegisteredClassEx = RegisterClassEx(&wndclass);

	if( hasRegisteredClassEx )
	{//WS_EX_TRANSPARENT at the 1st zero
		RECT desktop;
		// Get the size of screen to the variable desktop
		GetWindowRect(GetDesktopWindow(), &desktop);

		const int W_HEIGHT = 18;
		const int xPos = 0,yPos = 0;
		HWND window = CreateWindowEx( 0, myclass, "Speak me not display",//Set position as 0,0, size as desktopWidthx25, and remove border and shit
					WS_POPUP | WS_BORDER, 0, 0,
					desktop.right, W_HEIGHT, 0, 0, GetModuleHandle(0), 0 );
		if(window)
		{
			//Remove the header
			SetWindowLong(window, GWL_STYLE, 0);
			//Make it layered so it can be translucent
			SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED);

			//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			//SetClassLongPtr(window, GCLP_HBRBACKGROUND, (LONG)brush);//Give it a sexy black touch
			SetLayeredWindowAttributes(window, 0, (255 * 80) / 100, LWA_ALPHA);//50% alpha
			//SetWindowPos(window,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);//Set it such that it's always at the top
			//SetLayeredWindowAttributes(window, 0, (255 * 20) / 100, LWA_ALPHA);
			ShowWindow( window, SW_SHOWMINIMIZED );
			//SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);

			//Create my sexy label
			hwnd_label = CreateWindow("static", "ST_U",
                            WS_CHILD | WS_VISIBLE, //| WS_TABSTOP,
							xPos, yPos, desktop.right, W_HEIGHT,
                            window, (HMENU)(501),
                            (HINSTANCE) GetWindowLong (window, GWL_HINSTANCE), NULL);
			//SetTextColor(hwnd_label, RGB(0,0,0));    
			//SetBkMode (hwnd_label, TRANSPARENT);
			SetWindowText(hwnd_label, "Global:");
				//CreateWindowEx( WS_EX_TRANSPARENT, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , xPos, yPos, width, height, window, (HMENU) 0, hInst, NULL); 

			//Setup new thread for input and to ensure window is at top
			thread backgroundThread = thread(updateWindow_thread,window,hwnd_label);

			MSG msg;
			BOOL bRet;
			//Handle window. While window is handled here, thread is locked.
			while((bRet = GetMessage( &msg, 0, 0, 0 )) != 0)
			{ 
				if (bRet == -1)
				{
					// handle the error and possibly exit
					PostMessage( window, WM_CLOSE, 0, 0 );
				}
				else
				{
					TranslateMessage(&msg); 
					DispatchMessage(&msg); 
				}
			}
			//DeleteObject(brush);
			if(mode == 1)
				mode = 0;//the window is closed!
			backgroundThread.join();//make main wait for input to finish
		}
		else
		{
			cout << "ERROR: FAILED TO CREATE WINDOW" << endl;
			if(mode == 1)
				mode = 0;
		}
	}
}
void globalMode_old()
{
	string input="";
	//As of now doesn't handle exceptions...
	HWND prevWindow = NULL;
	long updateTime,paintTime,currentTime;
	updateTime = paintTime = timeGetTime();

	int heldCount = 0;
	while(1 == mode)
	{
//Update
		currentTime = timeGetTime();
		if(currentTime - updateTime >= UPDATE_INTERVAL_MS_NOW)
		{
			updateTime = currentTime;
			//Check for input
			handleKeyState(input,heldCount);
		}
//Paint
		if(isActive_GLOBAL)
		{
			if(currentTime - paintTime >= PAINT_INTERVAL_MS)
			{
				paintTime = currentTime;
				currWindow = GetForegroundWindow();
				if(currWindow != prevWindow)
				{
					if(prevWindow != NULL)
						InvalidateRect(prevWindow,NULL,FALSE);//Clear screen
					prevWindow = currWindow;
				}
				doubleBufferText(currWindow,"Global: "+input);
				//cout << input << "|" << prevChar << endl;
			}
		}

		Sleep(10);
	}

	if(currWindow != NULL)
	{
		InvalidateRect(prevWindow,NULL,FALSE);//Clear screen
		currWindow = NULL;
	}
}
int handleInput(string input)
{
	if(!input.empty())
	{
		if(mode == 1)
			cout << "Global: " << input << endl;

		if(input == KILLPHRASE)
		{
			cout << "Thanks for using my application." << endl;
			return -1;
		}
		else if(input == "\\mode")
		{
			cout << "Changing to " << (mode==0?"Global":"Console") << " mode..." << endl;
			mode = mode==0?1:0;
			return mode;
		}
		else if(input == "\\help")
		{
			printHelp();
		}
		else if(input == "\\hottext")
		{
			useHotText = !useHotText;
			cout << "Hot Text is now " << (useHotText?"Enabled":"Disabled") << "." << endl;
		}
		else 
		{
			if(useHotText)
			{
				input = hotText_processInput(input);
			}

			if(input.size() <= CHAR_LIMIT)
			{
				sendToVLC(input,true);
			}
			else
			{
				string f___ingLongCommand = "start vlcLNK.lnk -vvv ";
				prepLongMsgToVLC(f___ingLongCommand, input,'.',input.size());
				f___ingLongCommand.append(" --qt-start-minimized --play-and-exit --auto-preparse --quiet &");
				system(f___ingLongCommand.c_str());
				//cout << f___ingLongCommand << endl;
			}
		}
	}
	return 0;
}
void printHelp()
{
	cout <<
		"----------------------------" << endl <<
		"Speak me not - HELP\n" <<
		"----------------------------" << endl <<
		"You are currently in: " << (mode==0?"Console":"Global") << " mode." << endl << endl <<
		"----------------------------" << endl <<
		"HOW TO USE:" << endl <<
		"----------------------------" << endl << endl <<
		"Input anything - words, numbers, sentences in English and listen to Google Translate's narrator say it on your computer." << endl <<
		"The method of input is different for each kind of mode - the application starts in console mode." << endl <<
		"This application also has other commands that are preceded by a \'\\\' sign. e.g. \\exit would exit this application." << endl << endl <<
		"----------------------------" << endl <<
		"CONSOLE MODE:" << endl <<
		"----------------------------" << endl <<
		"Input and commands are typed into the console - pressing Enter will proccess the input." << endl << endl <<
		"----------------------------" << endl <<
		"GLOBAL MODE:" << endl <<
		"----------------------------" << endl <<
		"In global mode, you have to first press the Home key to begin input." << endl <<
		"Whatever you have input will be displayed on the top right hand corner if the current active window." << endl <<
		"Pressing Home key again will stop all keypresses from registering as input." << endl <<
		"To clear what you have input (but did not process), press the Delete key." << endl <<
		"Pressing Enter will process the input." << endl <<
		"To make the program listen for pressed keys every "<< UPDATE_INTERVAL_MS_HIGH <<"ms, press Page Up (active by default)." << endl <<
		"Listening for keyboard input may be CPU-intensive, so press Page Down to make it check for pressed keys every "<< UPDATE_INTERVAL_MS_LOW <<"ms." << endl <<
		"The page up and page down commands will only activate after Home key is pressed and will play a beep sound." << endl <<
		"Finally, the following characters are not recorded in Global mode: \"<>[]{}`~-_^*|/" << endl << endl <<
		"----------------------------" << endl <<
		"Commands" << endl <<
		"----------------------------" << endl <<
		"\\exit \t\t-Quit application" << endl <<
		"\\mode \t\t-Toggle between console & global mode" << endl <<
		"\\hottext\t-Toggle hot text (See hotText.txt for more details)" << endl << endl <<
		"----------------------------" << endl <<
		"Known bugs" << endl <<
		"----------------------------" << endl <<
		"Keeping the console in focus while using global mode will cause what you have typed to be repeated in console mode." << endl <<
		"Crazoter 2013" << endl << endl;
}
	
string convertToSpeechURL(string input)
{
	string networkURL = "\"http://translate.google.com/translate_tts?ie=UTF-8&q=";
	networkURL.append(UriEncode(input));
	networkURL.append("&tl=en&prev=input.mpeg\"");
	return networkURL;
}

void sendToVLC(string input, bool async)
{
	string command = (async?"start ":"");
	command.append("vlcLNK.lnk -vvv ");
	command.append(convertToSpeechURL(input));
	command.append(" --qt-start-minimized --play-and-exit --quiet");
	if(async)
		command.append(" &");
	//cout << command << endl;
	system(command.c_str());	
}

void prepLongMsgToVLC(string &command,string input, char delim,unsigned int length)
{
	deque<string> wordDeque = split(input,delim,true);
	string manipulatedInput = "";
	//Deque used because we'll be manipulating the front node
	//http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1069897449&id=1073086407
	while(length > CHAR_LIMIT)
	{
		if(manipulatedInput.size() + wordDeque.front().size() < CHAR_LIMIT || manipulatedInput.empty())
		{
			if(wordDeque.front().size() > CHAR_LIMIT)
			{//The word is longer than 100 characters
				//Continue onto next delimiter - break out if it doesn't exist 1.'.'|2.','|3.';'|4.' '
				if(delim == ' ')
				{//If at last delimiter (' ')
					//sendToVLC(wordDeque.front().substr(0,CHAR_LIMIT),false);
					command.append(" ");
					command.append(convertToSpeechURL(wordDeque.front().substr(0,CHAR_LIMIT)));
					wordDeque.front().erase(0,CHAR_LIMIT);
					length -= CHAR_LIMIT;
				}
				else
				{
					switch(delim)
					{
						case '.':prepLongMsgToVLC(command,wordDeque.front(),',',wordDeque.front().size());
							break;
						case ',':prepLongMsgToVLC(command,wordDeque.front(),';',wordDeque.front().size());
							break;
						case ';':prepLongMsgToVLC(command,wordDeque.front(),':',wordDeque.front().size());
							break;
						case ':':prepLongMsgToVLC(command,wordDeque.front(),' ',wordDeque.front().size());
							break;
					}
					length -= wordDeque.front().size();
					wordDeque.pop_front();
				}
			}
			else
			{//Append with delimiter
				manipulatedInput.push_back(delim);
				manipulatedInput.append(wordDeque.front());
				wordDeque.pop_front();
			}
		}
		else
		{//We're full
			length -= manipulatedInput.size();
			command.append(" ");
			command.append(convertToSpeechURL(manipulatedInput));
			//sendToVLC(manipulatedInput,false);
			manipulatedInput = "";
		}
	}

	//clean up the rest
	while(!wordDeque.empty())
	{
		manipulatedInput.push_back(delim);
		manipulatedInput.append(wordDeque.front());
		wordDeque.pop_front();
	}
	if(!manipulatedInput.empty())
	{
		command.append(" ");
		command.append(convertToSpeechURL(manipulatedInput));
		//sendToVLC(manipulatedInput,false);
	}
}

int handleKeyState(string &input,int &count)
{
	if(( 1 << 16 ) & GetAsyncKeyState(VK_HOME))
	{
		if(prevChar != '{')
		{
			toggleIsActive();
			prevChar = '{';
			return isActive_GLOBAL?1:2;//open & close
		}
		return 0;
	}
	else if(( 1 << 16 ) & GetAsyncKeyState(VK_PRIOR))
	{
		if(UPDATE_INTERVAL_MS_NOW != UPDATE_INTERVAL_MS_HIGH)
		{
			UPDATE_INTERVAL_MS_NOW = UPDATE_INTERVAL_MS_HIGH;
			cout << '\a';
			prevChar = '~';//lol placeholders
		}
		return 0;
	}
	else if(( 1 << 16 ) & GetAsyncKeyState(VK_NEXT))
	{
		if(UPDATE_INTERVAL_MS_NOW != UPDATE_INTERVAL_MS_LOW)
		{
			UPDATE_INTERVAL_MS_NOW = UPDATE_INTERVAL_MS_LOW;
			cout << '\a';
			prevChar = '~';//lol placeholders
		}
		return 0;
	}
	else if(isActive_GLOBAL)
	{
		if(( 1 << 16 ) & GetAsyncKeyState(VK_RETURN))
		{//Process
			int result = handleInput(input);
			if(result == 1)
				mode = 0;
			else if(result == -1)
				mode = -1;
			input = "";
			prevChar = '~';//lol placeholders
			//if(currWindow != NULL)
				//InvalidateRect(currWindow,NULL,FALSE);//Clear screen
			//toggleIsActive();
		}
		else if(( 1 << 16 ) & GetAsyncKeyState(VK_DELETE))
		{//Remove all
			if(input != "")
			{
				input = "";
				count = 0;
				prevChar = '~';//lol placeholders
				//if(currWindow != NULL)
					//InvalidateRect(currWindow,NULL,FALSE);//Clear screen
			}
		}
		else if(( 1 << 16 ) & GetAsyncKeyState(VK_BACK))
		{//Pop 1
			if(manageCount(count,'-'))//not defined in HTML standard
			{
				if(!input.empty())
					input.pop_back();
				//if(currWindow != NULL)
					//InvalidateRect(currWindow,NULL,FALSE);//Clear screen
			}
		}
		else
		{
			for(int a=65;a<91;++a)
			{//All alphabets
				if(( 1 << 16 ) & GetAsyncKeyState(a))
				{
					if(manageCount(count,a))
					{
						bool isLower = true;
						if(( 1 << 16 ) & GetAsyncKeyState(VK_SHIFT))
						{
							isLower = !isLower;
						}

						if(GetKeyState(VK_CAPITAL) & 1)
						{
							isLower = !isLower;
						}

						char myChar = (char)a;
						if(isLower)
						{
							myChar = tolower(myChar);
						}
						input.push_back(myChar);
					}
					return 3;
				}
			}

			//Misc characters: :;,.? and SPC in order of most frequently used
			//SPC.,;:?!
			if(checkKey(VK_SPACE,' ',input,count) ||
				checkKey(VK_OEM_PERIOD,'.',input,count) || 
				checkKey(VK_OEM_COMMA,',',input,count) ||
				checkKey(VK_OEM_5,'\\',input,count) || 
				checkKey(VK_OEM_7,'\'',input,count)){}
			else if(( 1 << 16 ) & GetAsyncKeyState(VK_OEM_1))
			{//: or ;
				char c = ';';
				if(( 1 << 16 ) & GetAsyncKeyState(VK_SHIFT))
				{
					c = ':';
				}
				if(manageCount(count,c))
				{
					input.push_back(c);
				}
			}
			else if(( 1 << 16 ) & GetAsyncKeyState(VK_OEM_2))
			{// / or ?
				if(( 1 << 16 ) & GetAsyncKeyState(VK_SHIFT))
				{
					if(manageCount(count,'?'))
					{
						input.push_back('?');
					}
				}
			}
			else
			{
				for(int a=0;a<10;++a)
				{//All numbers and numpad numbers
					//Handle !@#$%&
					if(( 1 << 16 ) & GetAsyncKeyState(48 + a) || ( 1 << 16 ) & GetAsyncKeyState(96 + a))
					{//I'm lazy, so shift with numpad gives the special characters also
						char c = 48 + a;
						if(( 1 << 16 ) & GetAsyncKeyState(VK_SHIFT))
						{
							switch(c)
							{
								case '1':c='!';
									break;
								case '2':c='@';
									break;
								case '3':c='#';
									break;
								case '4':c='$';
									break;								
								case '5':c='%';
									break;
								case '7':c='&';
									break;
								case '8':c='*';
									break;
								case '9':c='(';
									break;
								case '0':c=')';
									break;
							}
						}

						if(manageCount(count,c))
						{
							input.push_back(c);
						}
						return 3;
					}
				}

				//Finally, +=
				if(( 1 << 16 ) & GetAsyncKeyState(VK_OEM_PLUS))
				{
					char c = '=';
					if(( 1 << 16 ) & GetAsyncKeyState(VK_SHIFT))
					{
						c = '+';
					}
					if(manageCount(count,c))
					{
						input.push_back(c);
					}
				}
				else
				{//You really didn't say anything!
					//f___!
					prevChar = '_';
					count = 0;
					return 0;//no change
				}
			}
		}
	}
	else
	{
		prevChar = '_';
		return 0;//no change
	}

	return 3;//input changed
}
void toggleIsActive()
{
	isActive_GLOBAL = !isActive_GLOBAL;
	if(!isActive_GLOBAL)
	{
		if(currWindow != NULL)
			InvalidateRect(currWindow,NULL,FALSE);//Clear screen
	}
}
bool manageCount(int &count,char currChar)
{
	if(currChar != prevChar)
	{
		prevChar = currChar;
		count = 0;
		return true;
	}
	else if(count <= COUNT_LIMIT)
	{
		++count;
		return false;
	}
	else
	{
		count = COUNT_RESET;
		return true;
	}
}
bool checkKey(int vk,char theChar,string &input,int &count)
{
	SHORT x = GetAsyncKeyState(vk);
	if(( 1 << 16 ) & GetAsyncKeyState(vk))
	{
		if(manageCount(count,theChar))
		{
			input.push_back(theChar);
		}
		return true;
	}
	return false;
}

void doubleBufferText(HWND hwnd,string s)
{
	RECT Client_Rect;
	GetClientRect(hwnd,&Client_Rect);
	int win_width = Client_Rect.right - Client_Rect.left;
	int win_height = Client_Rect.bottom + Client_Rect.left;
	PAINTSTRUCT ps;
	HDC Memhdc;
	HDC hdc;
	HBITMAP Membitmap;
	hdc = BeginPaint(hwnd, &ps);
	Memhdc = CreateCompatibleDC(hdc);
	Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
	SelectObject(Memhdc, Membitmap);
	updateText(hwnd,s);
	BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
	DeleteObject(Membitmap);
	DeleteDC    (Memhdc);
	DeleteDC    (hdc);
	EndPaint(hwnd, &ps);
}
void updateText(HWND thisHwnd,string s){
// Start Font
		//HWND thisHwnd = GetWindow(hwnd, GW_CHILD);
		//HFONT hf = 0;
		HDC hdc;
		//long lfHeight;
		HGDIOBJ  g_hfFont = GetStockObject(DEFAULT_GUI_FONT);
		int i = 14;

		hdc = GetDC(thisHwnd);
		//lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);

		//hf = CreateFont(lfHeight, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial Bold");

		//if(hf)
		//{
		//	DeleteObject(g_hfFont);
		//	g_hfFont = (HGDIOBJ)hf;
		//}
		//else
		//{
		//	cout << "Font creation failed!" << endl;
		//} 
// End font

// Start Text
		//char szSize[100];
		//char szTitle[]				= "These are the dimensions of your client area:";
		HGDIOBJ hfOld				= SelectObject(hdc, g_hfFont);
		COLORREF g_rgbText			= RGB(0,255,0);
		COLORREF g_rgbStrokeText	= RGB(0,0,0);
		COLORREF g_rgbBackground	= RGB(255,255,255);
		BOOL g_bOpaque				= FALSE;
					
		RECT rc;
		LPRECT prc = &rc;
		GetClientRect(thisHwnd, prc);
		prc->top = 5;

		SetBkColor(hdc, g_rgbBackground);
		i = SetTextColor(hdc, g_rgbStrokeText);

		if(g_bOpaque){
			SetBkMode(hdc, OPAQUE);
		}
		else{
			SetBkMode(hdc, TRANSPARENT);
		}

		//Stroke
		prc->left++;
		prc->top++;
		i = DrawText(hdc, s.c_str(), -1, prc, DT_WORDBREAK);
		prc->left-=2;
		prc->top-=2;
		i = DrawText(hdc, s.c_str(), -1, prc, DT_WORDBREAK);
		//Actual text
		prc->left++;
		prc->top++;
		i = SetTextColor(hdc, g_rgbText);
		i = DrawText(hdc, s.c_str(), -1, prc, DT_WORDBREAK);
		//i = wsprintf(szSize, "\n{This is the left = %d,\n This is the top = %d \n\n\n\n\n, %d \n, %d \n}", prc->left, prc->top, prc->right, prc->bottom);
		//i = DrawText(hdc, szSize, i, prc, DT_CENTER | DT_VCENTER | DT_NOCLIP );

		SelectObject(hdc, hfOld);
		//DeleteObject(hf);//Delete the font - we have finished with it.
		ReleaseDC(NULL, hdc);

// End Text
}

deque<string> &split(const std::string &s, char delim, std::deque<std::string> &elems, bool skipEmpty) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
		if(!skipEmpty || !item.empty())
			elems.push_back(item);
    }
    return elems;
}

deque<string> split(const std::string &s, char delim, bool skipEmpty) {
    std::deque<std::string> elems;
    split(s, delim, elems, skipEmpty);
    return elems;
}

void setupHotText()
{
	ifstream file("hotText.txt");
	if(file)
	{
		string str;
		deque<string> strDeque;
		while (getline(file, str))
		{//process shortcuts
			if(!str.empty() && str.front() != '#')
			{
				strDeque = split(str,'=',true);
				if(strDeque.size() == 2)
				{
					str = strDeque.at(0);
					transform(str.begin(), str.end(), str.begin(), tolower);//Convert key to lower
					strDeque.at(1).pop_back();
					strDeque.at(1).erase(0,1);//remove quotes
					map_hotText[str] = strDeque.at(1);
				}
				else
					cout << "ERROR: HOT TEXT WITH INVALID SYNTAX DETECTED. HOT TEXT IGNORED" << endl;
			}
		}
		cout << "All hot text loaded!" << endl;
	}
	else
	{
		cout << "ERROR: hotText.txt file is not found! The hot text function cannot be used." << endl;
	}
}

string hotText_processInput(string input)
{
	deque<string> strDeque = split(input,' ',true);
	for(size_t i=0;i < strDeque.size();++i)
	{
		if(map_hotText.count(strDeque.at(i)) == 1)//can most likely remove the == 1
		{//Found a hot text!
			strDeque.at(i) = map_hotText.at(strDeque.at(i));//Replace!
		}
	}
	ostringstream oss;

	//Join all but the last element to avoid trailing delimiter
	copy(strDeque.begin(), strDeque.end()-1,
        std::ostream_iterator<string>(oss, " "));
	
    // Now add the last element with no delimiter
    oss << strDeque.back();

	return oss.str();
}

void displayHoldTime()
{
	string rubbish;
	getline(cin,rubbish);
	while(!GetAsyncKeyState(VK_RETURN))
	{

	}
	long x = timeGetTime();
	while(GetAsyncKeyState(VK_RETURN))
	{

	}
	cout << timeGetTime() - x << endl;
}