#ifndef INPUTREADER_H_
#define INPUTREADER_H_

#include <string>
#include <unordered_map>

#include <ncurses.h>

namespace backends
{

class InputReader
{
public:
    const static std::string resizeKey;
    static std::string read()
    {
        static const std::unordered_map<int, std::string> notStandard =
        {
            {10, "<ENTER>"},
            {27, "<ESC>"},
            {KEY_BACKSPACE, "<DEL>"},
            {KEY_RESIZE, resizeKey}
        };

        int k = getch();
        // std::cerr << k << std::endl;

        auto it = notStandard.find(k);
        if (it != notStandard.end())
            return it->second;

        std::string cursesName(keyname(k));

        if (cursesName.size() == 2 && cursesName[0] == '^')
            return "<CTRL>" + cursesName.substr(1);

        return cursesName;
    }
};

} // namespace backends
#endif

