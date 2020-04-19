#pragma once

#include "resource.h"

extern HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL MakeDialogVisible(HWND, BOOL);
