// PriorityManager.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    hInst = hInstance;

    INITCOMMONCONTROLSEX icce = { };
    icce.dwSize = sizeof(icce);
    icce.dwICC = ICC_LINK_CLASS;

    InitCommonControlsEx(&icce);

    DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINDLG), NULL, (DLGPROC)DlgProc);

    return 0;
}

BOOL MakeDialogVisible(HWND hWnd, BOOL visible)
{
    return ShowWindow(hWnd, visible ? SW_SHOW : SW_HIDE);
}

LRESULT CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT pt;

    switch (message)
    {
    case WM_INITDIALOG:
    {
        InitializeServices(hWnd);
        return 0;
    }
    break;
    case WM_HOTKEY:
    {
        HandleHotkeys(hWnd, LOWORD(wParam));
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if (HIWORD(wParam) == BN_CLICKED) // parse button clicks
        {
            switch (wmId)
            {
            case IDOK:
                MakeDialogVisible(hWnd, FALSE);
                break;
            case ID_MENU_EXIT:
            case IDCANCEL:
                EndDialog(hWnd, 0);
                break;
            case ID_MENU_OPEN:
                MakeDialogVisible(hWnd, TRUE);
                break;
            default:
                return 0;
            }
        }
    }
    break;
    case WM_NOTIFYICONMSG:
        switch (lParam)
        {
        case WM_LBUTTONUP:
            MakeDialogVisible(hWnd, TRUE);
            break;
        case WM_RBUTTONDOWN:
            GetCursorPos(&pt);
            HandleTrayPopupMenu(hWnd, pt);
            break;
        default:
            break;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DestroyServices(hWnd);
        PostQuitMessage(0);
        break;
    default:
        return 0;
    }
    return 0;
}
