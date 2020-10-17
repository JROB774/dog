INTERNAL constexpr const char* CRASH_DUMP_NAME = "GameCrash.dmp";
INTERNAL constexpr const char* DEBUG_DUMP_NAME = "GameDebug.dmp";
INTERNAL constexpr const char*  ERROR_LOG_NAME = "error.log";

GLOBAL FILE* gErrorLog;

#ifdef PLATFORM_WIN32
// Unhandled exception dump taken from here <https://stackoverflow.com/a/700108>
INTERNAL LONG WINAPI InternalUnhandledExceptionFilter (struct _EXCEPTION_POINTERS* info)
{
    ShowAlert("Error", "Fatal exception occurred!\nCreating crash dump!", ALERT_TYPE_ERROR, ALERT_BUTTONS_OK);

    std::string file_name(CRASH_DUMP_NAME);
    HANDLE file = CreateFileA(file_name.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION mini_dump_info = {};
        mini_dump_info.ThreadId          = GetCurrentThreadId();
        mini_dump_info.ExceptionPointers = info;
        mini_dump_info.ClientPointers    = TRUE;

        MINIDUMP_TYPE type = (MINIDUMP_TYPE)(MiniDumpWithFullMemory|MiniDumpWithHandleData);
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file, type, &mini_dump_info, NULL, NULL);

        CloseHandle(file);
    }

    if (ErrorTerminateCallback)
    {
        ErrorTerminateCallback();
    }

    return EXCEPTION_EXECUTE_HANDLER;
}
#endif

INTERNAL void LogError (const char* file, int line, ErrorLevel level, const char* format, ...)
{
    // We only open the error log once the first error occurs.
    if (!gErrorLog)
    {
        std::string error_log_name(ERROR_LOG_NAME);
        gErrorLog = fopen(error_log_name.c_str(), "a");
    }

    va_list args;

    std::string file_str = FixPathSlashes(file);
    std::string time_str = FormatTime("%m/%d/%Y %H:%M:%S");

    const char* err_format = "[%s] Error in %s at line %d: ";

    #if defined(BUILD_DEBUG)
    va_start(args, format);
    fprintf(stderr, err_format, time_str.c_str(), file_str.c_str(), line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    fflush(stderr);
    #endif

    if (gErrorLog)
    {
        va_start(args, format);
        fprintf(gErrorLog, err_format, time_str.c_str(), file_str.c_str(), line);
        vfprintf(gErrorLog, format, args);
        fprintf(gErrorLog, "\n");
        va_end(args);
        fflush(gErrorLog);
    }

    if (level == ERR_MIN) return;

    va_start(args, format);
    std::string msg = FormatStringV(format, args);
    ShowAlert("Error!", msg, ALERT_TYPE_ERROR, ALERT_BUTTONS_OK);
    va_end(args);

    if (level == ERR_MED) return;

    gWindow.running = false;

    if (ErrorMaximumCallback)
    {
        ErrorMaximumCallback();
    }
}

INTERNAL bool InitErrorSystem ()
{
    #ifdef PLATFORM_WIN32
    SetUnhandledExceptionFilter(&InternalUnhandledExceptionFilter);
    #endif
    return true;
}

INTERNAL void QuitErrorSystem ()
{
    // This condition is important because, for some reason, calling
    // fclose(NULL) results in a long hang-time during program exit.
    if (gErrorLog)
    {
        fclose(gErrorLog);
        gErrorLog = NULL;
    }
}
