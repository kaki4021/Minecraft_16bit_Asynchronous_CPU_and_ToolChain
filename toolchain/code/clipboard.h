#pragma once

#include <string>
#include <Windows.h>

bool CopyToClipboard(const std::string& s) {
    if (!OpenClipboard(nullptr)) return false;
    EmptyClipboard();

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hMem) {
        CloseClipboard();
        return false;
    }

    memcpy(GlobalLock(hMem), s.c_str(), s.size() + 1);
    GlobalUnlock(hMem);


    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return true;
}