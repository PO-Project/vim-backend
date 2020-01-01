#ifndef TEXTCOMMANDCONTAINER_H_
#define TEXTCOMMANDCONTAINER_H_

#include <functional>
#include <string>
#include <utility>
#include <algorithm>
#include <map>

#include "TextCommand.hpp"
#include "TextCall.hpp"
#include "ToolBase.hpp"

namespace backends
{

class TextCommandContainer
{
public:
    void add(TextCommand command)
    {
        commandMap.insert({command.getBase(), std::move(command)});
    }
    std::string readBuffer(const std::string& buffer, tools::ToolBase& tool)
    {
        try
        {
            TextCall textCall(buffer);
            auto it = commandMap.find(textCall.getBase());
            if (it == commandMap.end())
                return "Command " + textCall.getBase() + " not found.";
            if (it->second.getArguments().size() != textCall.getArguments().size())
                return "Command " + textCall.getBase() + " needs "
                    + std::to_string(it->second.getArguments().size()) + " arguments, "
                    + std::to_string(textCall.getArguments().size()) + " were provided.";
            it->second(buffer, tool);
            return "";
        }
        catch (std::invalid_argument e)
        {
            return e.what();
        }
    }

private:
    struct TextCommandCmp
    {
        bool operator()(const TextCommand& a, const TextCommand& b) const
        {
            return a.getBase() < b.getBase();
        }
    };
    std::map<std::string, TextCommand> commandMap;
};


} // namespace
#endif