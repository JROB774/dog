INTERNAL AlertResult ShowAlert (std::string title, std::string msg, AlertType type, AlertButtons buttons)
{
    // NOTE: We don't allow hidden windows because it causes program hang.
    HWND hwnd = NULL;
    bool hidden = SDL_GetWindowFlags(gWindow.window) & SDL_WINDOW_HIDDEN;

    UINT win32_type = 0;
    UINT win32_buttons = 0;

    switch (type)
    {
    case (ALERT_TYPE_INFO   ): win32_type = MB_ICONINFORMATION; break;
    case (ALERT_TYPE_WARNING): win32_type = MB_ICONWARNING;     break;
    case (ALERT_TYPE_ERROR  ): win32_type = MB_ICONERROR;       break;
    }
    switch (buttons)
    {
    case (ALERT_BUTTONS_YES_NO_CANCEL): win32_buttons = MB_YESNOCANCEL; break;
    case (ALERT_BUTTONS_YES_NO       ): win32_buttons = MB_YESNO;       break;
    case (ALERT_BUTTONS_OK           ): win32_buttons = MB_OK;          break;
    case (ALERT_BUTTONS_OK_CANCEL    ): win32_buttons = MB_OKCANCEL;    break;
    }

    if (!hidden)
    {
        SDL_SysWMinfo win_info = {};
        SDL_VERSION(&win_info.version);
        if (SDL_GetWindowWMInfo(gWindow.window, &win_info))
        {
            hwnd = win_info.info.win.window;;
        }
    }

    int win32_result = MessageBoxA(hwnd, msg.c_str(), title.c_str(), (win32_type|win32_buttons));

    AlertResult result = ALERT_RESULT_INVALID;
    switch (win32_result)
    {
    case (IDCANCEL): result = ALERT_RESULT_CANCEL; break;
    case (IDOK    ): result = ALERT_RESULT_OK;     break;
    case (IDNO    ): result = ALERT_RESULT_NO;     break;
    case (IDYES   ): result = ALERT_RESULT_YES;    break;
    }

    return result;
}
