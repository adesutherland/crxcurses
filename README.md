# Essential Curses APIs for CREXX (MVP)

## Plugin
File name: `rxcurses.rxplugin`
Namespace: `rxcurses`

## Screen and Window Management
- initscr(): Initialises the library and sets up the screen.
- endwin(): Restores the terminal after the library is no longer in use.
- refresh(): Refreshes the screen to reflect changes.
- newwin(): Creates a new window.
- delwin(): Deletes a window.
- derwin(): Creates a subwindow.

## Input Handling
- getch(): Reads a single character from the keyboard.
- keypad(): Enables the reading of function keys and arrow keys.
- curs_set(): Sets the visibility of the cursor.

## Output and Display
- printw(): Prints formatted output to the window.
- mvprintw(): Moves the cursor and prints formatted output.
- addstr(), mvaddstr(): Adds a string to the window at the current or specified position.

## Scrolling:
- scrl(): Scrolls the entire window up or down by a specified number of lines. Positive values scroll up (content moves down), and negative values scroll down (content moves up).
- scrollok(): Enables or disables the ability to scroll a window when new lines are added beyond the bottom edge. This function is crucial for allowing smooth scrolling in a window.
- wscrl(): Similar to scrl(), but operates on a specific window.
- scroll(): Scrolls the window one line up, making room at the bottom for new content. This is a simpler version of scrl().

## Attributes and Color
- attron(), attroff(): Turns on and off text attributes like bold or underline.
- start_color(): Initialises color functionality.
- init_color(): Changes the definition of a color.
- init_pair(): Manages color pairs for text display.
- bkgd(), wbkgd() to set the background color of the screen or window

## Special Functions
- box(): Draws a box around a window.
- getmaxyx(): Retrieves the dimensions of a window
- getyx(): Retrieves the current cursor position.
- wgetyx(): Retrieves the current cursor position for a window
- clear(), clrtobot(), clrtoeol(): Clears parts of the screen.
- wclear(), wclrtobot(), wclrtoeol(): Clears parts of the window.
- move(): Moves the cursor to a specified position.
- wmove(): Moves the cursor to a specified position in a window.
- timeout(): Sets a delay for getch().
- wtimeout(): Sets a delay for wgetch() in a window.

## cREXX Specific Functions
- unescape(): Unescapes a string containing escape sequences.
- setlocale(): Sets the locale for the library.
- redirectsay(): Redirects the SAY output to the screen
- wredirectsay(): Redirects the SAY output to a window
