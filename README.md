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
- scrollok(): Enables or disables the ability to scroll a window when new lines are added beyond the bottom edge. This function is crucial for allowing smooth scrolling in a window.
- scrl(): Scrolls the entire window up or down by a specified number of lines. Positive values scroll up (content moves down), and negative values scroll down (content moves up).
- wscrl(): Similar to scrl(), but operates on a specific window.
- scroll(): Scrolls the window one line up, making room at the bottom for new content. This is a simpler version of scrl() when only single-line scrolling is needed.

## Attributes and Colour
- attron(), attroff(): Turns on and off text attributes like bold or underline.
- start_color(): Initialises colour functionality.
- init_pair(), COLOR_PAIR(): Manages colour pairs for text display.

## Special Functions
- box(): Draws a box around a window.
- getyx(): Retrieves the current cursor position.
- clear(), clrtobot(), clrtoeol(): Clears parts of the window.
- move(): Moves the cursor to a specified position.
- timeout(): Sets a delay for getch().
- getmaxyx(): Retrieves the dimensions of a window
