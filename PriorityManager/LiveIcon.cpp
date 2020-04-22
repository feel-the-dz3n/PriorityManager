#include "pch.h"
#include "PriorityManager.h"

VOID HandleLiveIcon(HWND hWnd)
{
	if (!Settings::Instance().EnableLiveIcon) return;

	HANDLE hProcess;
	DWORD priority;
	DWORD pid;
	GetWindowThreadProcessId(hWnd, &pid);
	if (!pid) return;

	hProcess = OpenProcess(
		PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_SET_INFORMATION,
		FALSE, pid);
	if (!hProcess) return;

	priority = GetPriorityClass(hProcess);
	CloseHandle(hProcess);

	auto iconResource = GetPriorityClassIconId(priority);
	UpdateTrayIcon(LoadIcon(hInst, iconResource));
}
