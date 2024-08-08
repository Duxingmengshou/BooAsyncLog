#include <algorithm>
#include "fileName.h"


namespace boo::file {
    bool fileName::dirExists(const std::string &folder) {
        DWORD attributes = GetFileAttributes(folder.c_str());
        return (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_DIRECTORY);
    }

    bool fileName::makeDir(const std::string &folder) {
        std::string path = folder;
        std::vector<std::string> paths;

        // Normalize the path (replace backslashes with forward slashes)
        for (char &c: path) {
            if (c == '\\') {
                c = '/';
            }
        }

        size_t pos = 0;
        while ((pos = path.find('/', pos)) != std::string::npos) {
            paths.push_back(path.substr(0, pos));
            pos++;
        }
        paths.push_back(path); // Add the full path

        for (const std::string &p: paths) {
            if (!dirExists(p)) {
                if (!CreateDirectory(p.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
                    return false;
                }
            }
        }
        return true;
    }

    bool fileName::delDir(const std::string &folder) {
        return RemoveDirectory(folder.c_str()) != 0;

    }

    bool fileName::makeSingleDir(const std::string &str) {
        if (!dirExists(str)) {
            return CreateDirectory(str.c_str(), NULL) != 0;
        }
        return true;
    }

    bool fileName::delFile(const std::string &file) {
        return DeleteFile(file.c_str()) != 0;
    }

    std::vector<std::string> fileName::dirFileNames(std::string parse_path, std::string suffix) {
        std::vector<std::string> file_names;
        std::string search_path = parse_path + "\\*" + suffix;

        WIN32_FIND_DATAA find_data;
        HANDLE hFind = FindFirstFileA(search_path.c_str(), &find_data);

        if (hFind == INVALID_HANDLE_VALUE) {
            return file_names;
        }

        do {
            if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                file_names.push_back(find_data.cFileName);
            }
        } while (FindNextFileA(hFind, &find_data) != 0);

        FindClose(hFind);
        return file_names;
    }
}