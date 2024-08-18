/* cRexx rxcurses demo program 2 */
options levelb  /* This is a rexx level b program */
import rxcurses

say "cRexx rxcurses demo program 2"

/* Initialize the curses library */
call setlocale "" /* Set the locale to the default / utf-8 */
screen = initscr()
if screen = 0 then do
    say "Error initializing ncurses" /* We should never get here as initscr() will exit on error */
    exit 1
end

rows = 0
cols = 0
call getmaxyx screen, rows, cols

/* Initialize colors */
call start_color
if can_change_color() then do
    call init_color "WHITE", 1000, 1000, 1000
end
call init_pair 1, "BLUE", "WHITE"  /* Blue text on white background */
call init_pair 2, "GREEN", "BLACK"
call init_pair 3, "WHITE", "BLACK"

/* Create a 1 line header screen */
header = newwin(1, cols, 0, 0)
if header = 0 then do
    call endwin
    say "Error creating header window"
    exit 1
end
call bkgd "COLOR_PAIR(1)"
call refresh

call wbkgd header, "COLOR_PAIR(3)"
call wattron header, "BOLD"
call waddstr header, "cRexx rxcurses demo program 2"
call wattroff header, "BOLD"
call wrefresh header

/* Create a 1 line footer screen */
footer = newwin(1, cols, rows - 1, 0)
if footer = 0 then do
    call delwin header
    call endwin
    say "Error creating footer window"
    exit 1
end
call wbkgd footer, "COLOR_PAIR(3)"
call wattron footer, "BOLD"
call wprintw footer, "Press x or F3 to exit"
call wattroff footer, "BOLD"
call wrefresh footer

/* Create a border window */
border = newwin(10, 50, rows % 2 - 5, cols % 2 - 25)
if border = 0 then do
    call endwin
    say "Error creating border window"
    exit 1
end
call box border, 0, 0

/* Create subwindow */
window = derwin(border, 8, 48, 1, 1)
if window = 0 then do
    call delwin border
    call endwin
    say "Error creating subwindow"
    exit 1
end

call wbkgd border, "COLOR_PAIR(3)"
call wbkgd window, "COLOR_PAIR(3)"
call wrefresh border
call wrefresh window

/* Set up window modes */
call noecho
call curs_set 0
call keypad window, 1
call scrollok window, 1
call wtimeout window, 1000

/* Display initial message */
call attron "BOLD UNDERLINE COLOR_PAIR(1)"
call mvprintw 5, 10, "Window id is displayed in the subwindow"
call attroff "BOLD UNDERLINE COLOR_PAIR(1)"
call refresh
call wrefresh header
call wrefresh footer

key = "Nothing Yet"
format = unescape("\nKey pressed was %s (x or F3 to exit)\n")

/* Main loop to handle user input */
do forever
    call wprintw window, format, key
    call wattron window, "BOLD COLOR_PAIR(2)"
    call waddstr window, "Enter a key: "
    call wattroff window, "BOLD COLOR_PAIR(2)"
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

    if key = "" then key = "Timeout"
    else if key >= "KEY_MIN" & key <= "KEY_MAX" then key = "KEY_" || key
    else key = key
end

/* Clean up */
call delwin window
call delwin border
call endwin

return 0