
#include "VimBackend.hpp"

#include <iostream>

#include "CursesWindow.hpp"

#include <ncurses.h>


namespace backends
{

struct VimBackend::Impl
{
    CursesWindow win = CursesWindow(11, 11, 5, 5);

    void windowTest()
    {
        win.print("hello!!!", 0, 2);
        CursesWindow::update();
        getch();
        win.move(0, 0);
        CursesWindow::update();
        getch();
        //win.resize(16, 16);
        CursesWindow::update();
        getch();
        win.print("....");
        CursesWindow::update();
        getch();
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
}

void VimBackend::operator()()
{
    pImpl->windowTest();

}

}
