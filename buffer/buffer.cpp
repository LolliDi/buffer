#include <Windows.h>
#include <stdio.h>

int main()
{
    LPWSTR Message = L"Какой-то текст";
    ClipBoardInpText(Message);
    ClipBoardOutText();
}

int ClipBoardInpText(LPWSTR buf)
{
    DWORD len = wcslen(buf) + 1;
    HANDLE hMem;
    hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR)); //выделение памяти в глобальной области видимости
    memcpy(GlobalLock(hMem), buf, len * sizeof(LPWSTR));
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    return 0;
}

int ClipBoardOutText()
{
    LPWSTR mes = NULL;
    OpenClipboard(NULL);
    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
    mes = (LPWSTR)GlobalLock(hClipboardData);
    GlobalUnlock(hClipboardData);
    MessageBox(NULL, mes, L"Текст из буфера", MB_OK);
    return 0;
}