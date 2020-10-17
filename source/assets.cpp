#ifdef PLATFORM_WIN32
INTERNAL void SetupAssetPath ()
{
    // Get the location of the executable as the assets folder should be defined relative to that.
    char exe_path[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);
    char* slash = NULL;
    for (char* c=exe_path; *c; ++c) if (*c == '\\') slash = c;
    if (slash) *slash = '\0'; // Strip the executable's name from the path.

    gAssetPath = exe_path;
    gAssetPath += "\\";

    // If there is a file in the current working directory specifying the assets relative path
    // then we append that to the executable path, otherwise we just expect the exe directory.
    std::ifstream file("asset_path.txt", std::ios::in);
    if (file.is_open())
    {
        std::string asset_path;
        std::getline(file, asset_path);
        gAssetPath += asset_path;
    }
    else
    {
        gAssetPath += "assets\\";
    }

    // Make sure the asset path always ends in a slash.
    if (gAssetPath.back() != '\\' && gAssetPath.back() != '/')
    {
        gAssetPath += "\\";
    }

    printf("%s\n", gAssetPath.c_str());
}
#endif
