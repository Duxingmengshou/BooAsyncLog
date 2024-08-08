#ifndef BOOASYNCLOG_FILENAME_H
#define BOOASYNCLOG_FILENAME_H

#include <string>
#include <vector>
#include <windows.h>
#include <io.h>
#include <direct.h>

namespace boo::file {

    class fileName {
    private:
        fileName() = default;

        ~fileName() = default;

    public:


        static bool dirExists(const std::string &folder);

        static bool makeDir(const std::string &folder);

        static bool delDir(const std::string &folder);

        static bool makeSingleDir(const std::string &str);

        static bool delFile(const std::string &file);

        static std::vector<std::string> dirFileNames(std::string parse_path, std::string suffix);

    };

}
#endif //BOOASYNCLOG_FILENAME_H
