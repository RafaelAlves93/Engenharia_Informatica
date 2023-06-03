// POO 22/23
// Biblioteca para manipulação da consola
//
// Uso fora do âmbito de POO -> Perguntar primeiro aos professores
// Depósito em repositórios públicos -> Perguntar primeiro aos professores
//
// Pode ser aumentada com funcionalidades novas (desde que funcionem)

#ifndef NCURSES_TERMINAL_H
#define NCURSES_TERMINAL_H

#include <string>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include "curses.h"
#else
#include <ncurses.h>
#endif

namespace term {


    class TerminalFormatter {
    public:
        enum class Type {
            MOVE,
            COLOR,
            NOCOLOR
        };

        TerminalFormatter(TerminalFormatter::Type type, int a=-1, int b=-1) {
            this->type = type;
            switch(type) {
                case TerminalFormatter::Type::MOVE:
                    x = a;
                    y = b;
                    break;
                case TerminalFormatter::Type::COLOR:
                    color = a;
                    break;
            }
        }
    private:
        TerminalFormatter::Type type;
        int x, y;
        int color;

        friend class Terminal;
        friend class Window;
    };

    TerminalFormatter move_to(int x, int y);
    TerminalFormatter set_color(int i);
    TerminalFormatter no_color();

    class Window {
    public:
        Window(int x, int y, int w, int h, bool with_border=true);
        Window(const Window&) = delete;
        Window(Window&& win);
        ~Window();

        Window& operator=(const Window&) = delete;

        Window& operator<<(const TerminalFormatter& tf);
        Window& operator<<(const std::string& str);
        Window& operator<<(const int& i);
        Window& operator<<(const double& d);
        Window& operator<<(const char& c);

        Window& operator>>(char& c);
        Window& operator>>(std::string& str);

        int getchar();
        void clear();

    private:
        int last_color_pair=-1;
        WINDOW *window=NULL;
        WINDOW *border=NULL;
    };

    class Terminal {
    public:
        Terminal(const Terminal& t) = delete;
        Terminal operator=(const Terminal&) = delete;
        ~Terminal();

        static Terminal& instance() {
            static Terminal terminal;
            return terminal;
        }

        Terminal& operator<<(const TerminalFormatter& tf);
        Terminal& operator<<(const std::string& str);
        Terminal& operator<<(const int& i);
        Terminal& operator<<(const double& d);
        Terminal& operator<<(const char& c);

        Terminal& operator>>(char& c);
        Terminal& operator>>(std::string& str);

        Terminal& init_color(int i, int color, int bg_color);

        Window create_window(int x, int y, int w, int h, bool with_border=true);

        int getchar();
        void clear();
        int getNumCols();
        int getNumRows();

    private:
        Terminal();

        int last_color_pair=-1;
    };

}


#endif //NCURSES_TERMINAL_H