/* cRexx rxcurses demo program                                               */
/* This program is used to demonstrate and test the rxcurses library         */
options levelb  /* This is a rexx level b program */
import rxcurses

/* Initialise the curses library */
screen = initscr()
if screen = 0 then do
    say "Error initialising ncurses" /* We should never get here as initscr() will exit on error */
    exit 1
end

rows = 0
cols = 0
call getmaxyx screen, rows, cols

/* Create a window */
window = newwin(10, 50, rows % 2, cols % 2 - 25)
if window = 0 then do
    call endwin
    say "Error creating window"
    exit 1
end

call mvprintw 5,10,"Window id is %s", window

/* Refresh the Screen */
call refresh

/* Set up the window mode */
call noecho
call curs_set 0
call keypad window, 1
call scrollok window, 1

/* Loop */
key = "Nothing Yet"
format = unescape("Key pressed was %s (x or F3 to exit)\n")

do forever
    call wprintw window, format, key

    /* Refresh the Window */
    call wrefresh window

    /* Wait for a key press */
    key = wgetch(window)

    if key = "KEY_F(3)" then leave
    if key = "x" then leave
end

/* Delete the window */
call delwin window

/* Shutdown the curses library */
call endwin

return 0
