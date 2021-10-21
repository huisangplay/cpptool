#include <Windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType) {
	if (CTRL_CLOSE_EVENT == dwCtrlType) {
		keybd_event(VK_F5, (BYTE)0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_TAB, (BYTE)0, KEYEVENTF_KEYUP, 0);
	}
}
int main()
{
	int gap = 60;
	cout << "请输入屏幕切换时长（单位：秒）" << endl;
	cin >> gap;
	cout << "程序启动，切换屏幕间隔"<<gap<<"秒，请在5秒内打开chrome浏览器..." << endl;
	Sleep(5000);
	gap *= 1000;
	keybd_event(VK_F11, (BYTE)0, 0, 0);
	Sleep(1000);
	keybd_event(VK_F11, (BYTE)0, KEYEVENTF_KEYUP, 0);
	Sleep(gap);
	while (true) {
		keybd_event(VK_CONTROL, (BYTE)0, 0, 0);
		keybd_event(VK_TAB, (BYTE)0, 0, 0);

		Sleep(100);

		keybd_event(VK_TAB, (BYTE)0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);

		keybd_event(VK_F5, (BYTE)0, 0, 0);
		Sleep(100);
		keybd_event(VK_F5, (BYTE)0, KEYEVENTF_KEYUP, 0);
		Sleep(gap);
	}
	return 0;
}