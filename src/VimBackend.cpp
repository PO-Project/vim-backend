
#include "VimBackend.hpp"

#include <iostream>

#include "ToolBase.hpp"
#include "CursesWindow.hpp"
#include "InputReader.hpp"
#include "Command.hpp"
#include "KeyCommand.hpp"
#include "CommandCreator.hpp"
#include "KeyCommandContainer.hpp"

#include <ncurses.h>


namespace backends
{

struct VimBackend::Impl
{
    bool edition = false;

    std::function<void()> editionCallback;

    tools::ToolBase* tool;

    KeyCommandContainer keyCommandContainer;

    void bind(const std::string &command, std::function<void()> callback, const std::string &comment)
    {
        auto maybeCommandPtr = CommandCreator::create(command, callback, comment, [this](){
            edition = true;
        });
        if (maybeCommandPtr)
        {
            KeyCommand* keyPtr = dynamic_cast<KeyCommand*>((*maybeCommandPtr).get());
            if (keyPtr)
            {
                std::cerr << keyPtr->getPrintableCommand() << std::endl;
                if (keyPtr->getPrintableCommand() == "<EDITION>")
                    editionCallback = keyPtr->getCallback();
                else
                {
                    keyCommandContainer.add(std::move(*keyPtr));
                }
            }
        }
        else
        {
            //TODO
        }
    }

    void resizeWindows()
    {
        tool->setCoordinates(LINES-1, COLS, 0, 0);
    }

    void run()
    {
        resizeWindows();

        std::string buffer;

        while (true)
        {
            CursesWindow::update();
            std::string key = InputReader::read();
            if (key == InputReader::resizeKey)
                resizeWindows();
            else if (edition)
            {
                if (key == "<ESC>")
                    edition = false;
                else
                {
                    tool->setEntry("KEY", key);
                    editionCallback();
                }
            }
            else
            {
                buffer += key;
                keyCommandContainer.readBuffer(buffer);
            }
        }
    }
};

VimBackend::VimBackend()
{
    // todo move this to nice place
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    set_escdelay(25);

    pImpl = std::unique_ptr<Impl>(new Impl);
}

VimBackend::~VimBackend()
{
    endwin();
}

void VimBackend::bind(const std::string &command, std::function<void()> callback, const std::string &helpMessage) noexcept
{
    pImpl->bind(command, callback, helpMessage);
}

void VimBackend::operator()()
{
    pImpl->run();
}

void VimBackend::setTool(tools::ToolBase& newTool)
{
    pImpl->tool = &newTool;
}

}
