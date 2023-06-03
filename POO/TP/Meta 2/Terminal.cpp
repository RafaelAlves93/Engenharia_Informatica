// POO 22/23
// Biblioteca para manipulação da consola
//
// Uso fora do âmbito de POO -> Perguntar primeiro aos professores
// Depósito em repositórios públicos -> Perguntar primeiro aos professores
//
// Pode ser aumentada com funcionalidades novas (desde que funcionem)

#include "Terminal.h"

namespace term {


    TerminalFormatter move_to(int x, int y) {
        TerminalFormatter tf(TerminalFormatter::Type::MOVE, x, y);
        return tf;
    }

    TerminalFormatter set_color(int i) {
        TerminalFormatter tf(TerminalFormatter::Type::COLOR, i);
        return tf;
    }

    TerminalFormatter no_color() {
        TerminalFormatter tf(TerminalFormatter::Type::NOCOLOR);
        return tf;
    }



    Window::Window(int x, int y, int w, int h, bool with_border) {
        if( with_border ) {
            border = newwin(h, w, y, x);
            window = newwin(h-2, w-2, y+1, x+1);
            box(border, 0, 0);
            //wborder(border, '|', '|', '-', '-', '+', '+', '+', '+');
            //wborder(border, 0xb3, 0xb3, 0xc4, 0xc4, 0xda, 0xbf, 0xc0, 0xd9);
            wrefresh(border);
        } else {
            window = newwin(h, w, y, x);
        }
        wrefresh(window);
    }

    Window::Window(Window&& win) {
        border = win.border;
        win.border = NULL;
        window = win.window;
        win.window = NULL;
    }

    Window::~Window() {

        if( border!=NULL ) {
            wborder(border, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wrefresh(border);
            delwin(border);
        }
        if( window!=NULL ) {
            delwin(window);
        }

    }


    Window& Window::operator<<(const std::string& str) {
        ::wprintw(window, "%s", str.c_str());
        ::wrefresh(window);
        return *this;
    }

    Window& Window::operator<<(const TerminalFormatter& tf) {
        switch (tf.type) {
            case TerminalFormatter::Type::MOVE:
                ::wmove(window, tf.y, tf.x);
                break;
            case TerminalFormatter::Type::COLOR:
                if (last_color_pair != -1) {
                    ::wattroff(window,COLOR_PAIR(last_color_pair));
                }
                ::wattron(window,COLOR_PAIR(tf.color));
                last_color_pair = tf.color;
                break;
            case TerminalFormatter::Type::NOCOLOR:
                ::wattroff(window,COLOR_PAIR(tf.color));
                last_color_pair = -1;
                break;
        }
        return *this;
    }

    Window& Window::operator<<(const int& i) {
        ::wprintw(window, "%d",i);
        ::wrefresh(window);
        return *this;
    }
    Window& Window::operator<<(const double& d) {
        ::wprintw(window, "%f",d);
        ::wrefresh(window);
        return *this;
    }
    Window& Window::operator<<(const char& c) {
        ::wprintw(window, "%c",c);
        ::wrefresh(window);
        return *this;
    }

    Window& Window::operator>>(char& c) {
        c = ::wgetch(window);
        return *this;
    }

    Window& Window::operator>>(std::string& str) {
        ::noecho();
        ::cbreak();
        ::keypad(window, TRUE);
        int c = ::wgetch(window);
        switch(c) {
            case KEY_UP:
                str = "KEY_UP";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_DOWN:
                str = "KEY_DOWN";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_RIGHT:
                str = "KEY_RIGHT";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_LEFT:
                str = "KEY_LEFT";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_RESIZE:
                str = "KEY_RESIZE";
                ::nocbreak();
                ::echo();
                return *this;
        }
        ::ungetch(c);
        ::keypad(window, FALSE);
        ::nocbreak();
        ::echo();

        char buffer[255];
        ::wgetnstr(window, buffer, 255);
        str = std::string(buffer);
        return *this;
    }

    int Window::getchar() {
        return ::wgetch(window);
    }

    void Window::clear() {
        ::wclear(window);
    }



    Terminal::Terminal() {
        ::initscr();
        ::start_color();
        //::init_pair(1, COLOR_RED, COLOR_BLACK);
    }

    Terminal::~Terminal() {
        ::endwin();
    }

    Terminal& Terminal::operator<<(const std::string& str) {
        ::printw("%s", str.c_str());
        ::refresh();
        return *this;
    }

    Terminal& Terminal::operator<<(const TerminalFormatter& tf) {
        switch (tf.type) {
            case TerminalFormatter::Type::MOVE:
                ::move(tf.y, tf.x);
                break;
            case TerminalFormatter::Type::COLOR:
                if (last_color_pair != -1) {
                    ::attroff(COLOR_PAIR(last_color_pair));
                }
                ::attron(COLOR_PAIR(tf.color));
                last_color_pair = tf.color;
                break;
            case TerminalFormatter::Type::NOCOLOR:
                ::attroff(COLOR_PAIR(tf.color));
                last_color_pair = -1;
                break;
        }
        return *this;
    }

    Terminal& Terminal::operator<<(const int& i) {
        ::printw("%d",i);
        ::refresh();
        return *this;
    }
    Terminal& Terminal::operator<<(const double& d) {
        ::printw("%f",d);
        ::refresh();
        return *this;
    }
    Terminal& Terminal::operator<<(const char& c) {
        ::printw("%c",c);
        ::refresh();
        return *this;
    }

    Terminal& Terminal::operator>>(char& c) {
        c = ::getch();
        return *this;
    }

    Terminal& Terminal::operator>>(std::string& str) {
        ::noecho();
        ::cbreak();
        ::keypad(stdscr, TRUE);
        int c = ::getch();
        switch(c) {
            case KEY_UP:
                str = "KEY_UP";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_DOWN:
                str = "KEY_DOWN";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_RIGHT:
                str = "KEY_RIGHT";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_LEFT:
                str = "KEY_LEFT";
                ::nocbreak();
                ::echo();
                return *this;
            case KEY_RESIZE:
                str = "KEY_RESIZE";
                ::nocbreak();
                ::echo();
                return *this;
        }
        ::ungetch(c);
        ::keypad(stdscr, FALSE);
        ::nocbreak();
        ::echo();

        char buffer[255];
        ::getnstr(buffer, 255);
        str = std::string(buffer);
        return *this;
    }

    Terminal& Terminal::init_color(int i, int color, int bg_color) {
        ::init_pair(i, color, bg_color);
        return *this;
    }

    Window Terminal::create_window(int x, int y, int w, int h, bool with_border) {
        return Window(x, y, w, h, with_border);
    }

    int Terminal::getchar() {
        return ::getch();
    }

    void Terminal::clear() {
        ::clear();
    }

    int Terminal::getNumCols() {
        return COLS;
    }

    int Terminal::getNumRows() {
        return LINES;
    }


}