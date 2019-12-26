#ifndef COMMANDCREATOR_H_
#define COMMANDCREATOR_H_

#include <functional>
#include <string>
#include <utility>
#include <algorithm>
#include <optional>

#include "KeyCommand.hpp"

namespace backends
{

class CommandCreator
{
public:
    static std::optional<std::unique_ptr<Command>> create(std::string sequence, std::function<void()> callback, std::string comment, std::function<void()> changeModeCallback)
    {
        if (sequence[0] == '#' && sequence.find('#', 1) != std::string::npos)
        {
            static const std::string name = "#vim#";
            if (sequence.substr(0, name.size()) != name)
                return std::optional<std::unique_ptr<Command>>();
            else
                sequence = sequence.substr(name.size());
        }

        sequence.erase(std::min({sequence.size(), sequence.find('%'), sequence.find('.')}));

        static const std::string editS = "!EDIT";
        bool edition = false;
        if (sequence.size() >= editS.size()
            && std::equal(editS.begin(), editS.end(), sequence.end() - editS.size()))
        {
            sequence.erase(sequence.size() - editS.size());
            callback = [callback, changeModeCallback](){ callback(); changeModeCallback(); };
        }

        if (sequence.empty())
            return std::optional<std::unique_ptr<Command>>();

        // TODO
        // if (sequence[0] == ':')

        return std::optional<std::unique_ptr<Command>>(new KeyCommand(sequence, callback, comment));
    }
};


} // namespace

#endif
