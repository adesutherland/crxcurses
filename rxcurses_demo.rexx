/* cRexx rxcurses demo program                                               */
/* This program is used to demonstrate and test the rxcurses library         */
options levelb  /* This is a rexx level b program */
import rxcurses

/* Initialise the curses library */
call setlocale "" /* Set the locale to the default / utf-8 */
screen = initscr()
if screen = 0 then do
    say "Error initialising ncurses" /* We should never get here as initscr() will exit on error */
    exit 1
end

rows = 0
cols = 0
call getmaxyx screen, rows, cols

/* Create a border window */
border = newwin(10, 50, rows % 2, cols % 2 - 25)
if border = 0 then do
    call endwin
    say "Error creating border window"
    exit 1
end
call box border, 0, 0

/* Create subwindow */
window = derwin(border, 8, 48, 1, 1)
call start_color

/* Make white whiter if we can */
if can_change_color() then do
    call init_color "WHITE", 1000, 1000, 1000
end

call init_pair 1, "BLUE", "WHITE"  /* Blue text on white background */
call init_pair 2, "GREEN", "BLACK"
call init_pair 3, "WHITE", "BLACK"

/* Screen Colour */
call bkgd "COLOR_PAIR(1)"

call attron "BOLD UNDERLINE COLOR_PAIR(1)"
call mvprintw 5,10,"Window id is %s", window
call attroff "BOLD UNDERLINE COLOR_PAIR(1)"

/* Refresh the Screen */
call refresh
call wbkgd border, "COLOR_PAIR(3)"
call wbkgd window, "COLOR_PAIR(3)"
call wrefresh border

/* Set up the window mode */
call noecho
call curs_set 0
call keypad window, 1
call scrollok window, 1
call wtimeout window, 1000
call wredirectsay window

say "Window id is" window
say "Goodbye"

/* Loop */
key = "Nothing Yet"
format = unescape("\nKey pressed was %s (x or F3 to exit)\n")

do forever
    call wprintw window, format, key
    call wattron window, "BOLD COLOR_PAIR(2)"
    call waddstr window, "Enter a key: "
    call wattroff window, "BOLD COLOR_PAIR(2)"

    /* Refresh the Window */
    call wrefresh window

    /* Get cursor position */
    x = 0
    y = 0
    call getyx window, y, x

    call mvprintw 6, 10, "Cursor is at (y,x) %s, %s", y, x
    call refresh

    /* Wait for a key press */
    key = wgetch(window)

    if key = "[F3]" then leave
    if key = "x" then leave
end

/* Delete the window */
call delwin window

/* Shutdown the curses library */
call endwin

return 0
