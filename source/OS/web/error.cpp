INTERNAL void LogError (const char* file, int line, ErrorLevel level, const char* format, ...)
{
    va_list args;

    std::string file_str = FixPathSlashes(file);
    std::string time_str = FormatTime("%m/%d/%Y %H:%M:%S");

    const char* err_format = "[%s] Error in %s at line %d: ";

    va_start(args, format);
    fprintf(stderr, err_format, time_str.c_str(), file_str.c_str(), line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    fflush(stderr);
}

INTERNAL bool InitErrorSystem ()
{
    // Nothing...
    return true;
}

INTERNAL void QuitErrorSystem ()
{
    // Nothing...
}
