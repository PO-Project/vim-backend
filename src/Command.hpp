#ifndef COMMAND_H_
#define COMMAND_H_

#include <functional>
#include <string>
#include <utility>
#include <algorithm>

namespace backends
{

class Command
{
public:
    std::string getHelpText() const
    {
        return getPrintableCommand() + " - " + comment;
    }

    void operator()() const
    {
        callback();
    }

    const std::function<void()>& getCallback() const
    {
        return callback;
    }

    virtual std::string getPrintableCommand() const = 0;

protected:
    Command(std::function<void()> _callback, std::string _comment)
        : callback(_callback), comment(_comment) {}

    std::function<void()> callback;
    std::string comment;
};



} // namespace
#endif
