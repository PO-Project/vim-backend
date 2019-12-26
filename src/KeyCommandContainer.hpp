#ifndef KEYCOMMANDCONTAINER_H_
#define KEYCOMMANDCONTAINER_H_

#include <functional>
#include <string>
#include <utility>
#include <algorithm>
#include <set>

#include "KeyCommand.hpp"

namespace backends
{

class KeyCommandContainer
{
public:
    void add(KeyCommand command)
    {
        commandSet.insert(std::move(command));
    }
    void readBuffer(std::string& buffer)
    {
        for(const auto& c : commandSet)
            if(c.isCall(buffer))
            {
                buffer.clear();
                c();
                return;
            }
    }

private:
    //TODO more efficient data structure?
    struct commandCmp
    {
        bool operator()(const KeyCommand& a, const KeyCommand& b) const
        {
            return a.getKeys().size() > b.getKeys().size();
        }
    };
    std::set<KeyCommand, commandCmp> commandSet;
};


} // namespace
#endif
