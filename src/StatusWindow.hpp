#ifndef STATUSWINDOW_H_
#define STATUSWINDOW_H_

#include <string>
#include <ncurses.h>
#include <panel.h>

#include "CursesWindow.hpp"

namespace backends
{

class StatusWindow
{
public:
    StatusWindow(bool hidden = false)
        : cursesWindow(1, COLS, LINES-1, 0, hidden)
    {
        moveToBottom();
        if (hidden)
            hide();
    };

    void print(const std::string& s)
    {
        cursesWindow.clear();
        cursesWindow.print(s, 0, 0);
    }
    void clear()
    {
        cursesWindow.clear();
    }

    void fixAfterResize()
    {
        cursesWindow.resize(1, COLS);
        cursesWindow.move(LINES - 1, 0);
    }

    void focus()
    {
        cursesWindow.focus();
    }
    void moveToBottom()
    {
        cursesWindow.moveToBottom();
    }
    void hide()
    {
        cursesWindow.hide();
    }

private:
    CursesWindow cursesWindow;
};



} // namespace backends
#endif

