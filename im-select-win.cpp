#include <Windows.h>
#include <cstdlib>
#include <SDKDDKVer.h>
#ifdef WINVER
#undef WINVER
#endif // WINVER
#define WINVER 0x4ff
#include <stdio.h>
#include <tchar.h>
using namespace std;

int getInputMethod() {
	HWND hwnd = GetForegroundWindow();
	if (!hwnd) return 0;

	DWORD threadID = GetWindowThreadProcessId(hwnd, nullptr);
	HKL  currentLayout = GetKeyboardLayout(threadID);

	DWORD_PTR val = reinterpret_cast<DWORD_PTR>(currentLayout);
	return static_cast<int>(val & 0x0000FFFF);
}

void switchInputMethod(int locale) {
	HWND hwnd = GetForegroundWindow();
	LPARAM currentLayout = ((LPARAM)locale);
	PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, currentLayout);
}

int main(int argc, char** argv)
{
	if (argc == 1) {
		int imID = getInputMethod();
		printf("%d\n", imID);
	} else {
		int locale = atoi(argv[1]);
		switchInputMethod(locale);
	}
	return 0;
}

