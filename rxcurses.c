// rxcurses - CREXX Wrapper for the ncurses library

#include <ncurses.h>
#include "crexxpa.h"    // crexx/pa - Plugin Architecture header file
#include <ctype.h>
#include <stdlib.h>

/*
 * Helper function to get a UTF-8 character from ncurses
 * It is a wrapper around the wgetch function that handles
 * special keys and UTF-8 characters. It returns the UTF-8
 * character as a string in the buffer passed as an argument.
 * If a special key is pressed, the key name is stored in the buffer.
 *
 * It has special functionality to handle BACKSPACE key; additionally 127
 * and '\b' are mapped to KEY_BACKSPACE
 *
 * The buffer must be at least 15 characters long to store the key name.
 *
 * returns 0 for a normal character, 1 for a special key, and
 *        -1 on error
 */
static int getch_utf8(WINDOW* window, char* buffer) {

    int ch;
    int i;
    switch (ch = wgetch(window)) {
        case KEY_CODE_YES:
            strcpy(buffer, "KEY_CODE_YES"); return 1;
        case KEY_BREAK:
            strcpy(buffer, "KEY_BREAK"); return 1;
        case KEY_SRESET:
            strcpy(buffer, "KEY_SRESET"); return 1;
        case KEY_RESET:
            strcpy(buffer, "KEY_RESET"); return 1;
        case KEY_DOWN:
            strcpy(buffer, "KEY_DOWN"); return 1;
        case KEY_UP:
            strcpy(buffer, "KEY_UP"); return 1;
        case KEY_LEFT:
            strcpy(buffer, "KEY_LEFT"); return 1;
        case KEY_RIGHT:
            strcpy(buffer, "KEY_RIGHT"); return 1;
        case KEY_HOME:
            strcpy(buffer, "KEY_HOME"); return 1;
        case KEY_BACKSPACE:
        case 127:
        case '\b':
            strcpy(buffer, "KEY_BACKSPACE"); return 1;
        case KEY_F(1):
            strcpy(buffer, "KEY_F(1)"); return 1;
        case KEY_F(2):
            strcpy(buffer, "KEY_F(2)"); return 1;
        case KEY_F(3):
            strcpy(buffer, "KEY_F(3)"); return 1;
        case KEY_F(4):
            strcpy(buffer, "KEY_F(4)"); return 1;
        case KEY_F(5):
            strcpy(buffer, "KEY_F(5)"); return 1;
        case KEY_F(6):
            strcpy(buffer, "KEY_F(6)"); return 1;
        case KEY_F(7):
            strcpy(buffer, "KEY_F(7)"); return 1;
        case KEY_F(8):
            strcpy(buffer, "KEY_F(8)"); return 1;
        case KEY_F(9):
            strcpy(buffer, "KEY_F(9)"); return 1;
        case KEY_F(10):
            strcpy(buffer, "KEY_F(10)"); return 1;
        case KEY_F(11):
            strcpy(buffer, "KEY_F(11)"); return 1;
        case KEY_F(12):
            strcpy(buffer, "KEY_F(12)"); return 1;
        case KEY_DL:
            strcpy(buffer, "KEY_DL"); return 1;
        case KEY_IL:
            strcpy(buffer, "KEY_IL"); return 1;
        case KEY_DC:
            strcpy(buffer, "KEY_DC"); return 1;
        case KEY_IC:
            strcpy(buffer, "KEY_IC"); return 1;
        case KEY_EIC:
            strcpy(buffer, "KEY_EIC"); return 1;
        case KEY_CLEAR:
            strcpy(buffer, "KEY_CLEAR"); return 1;
        case KEY_EOS:
            strcpy(buffer, "KEY_EOS"); return 1;
        case KEY_EOL:
            strcpy(buffer, "KEY_EOL"); return 1;
        case KEY_SF:
            strcpy(buffer, "KEY_SF"); return 1;
        case KEY_SR:
            strcpy(buffer, "KEY_SR"); return 1;
        case KEY_NPAGE:
            strcpy(buffer, "KEY_NPAGE"); return 1;
        case KEY_PPAGE:
            strcpy(buffer, "KEY_PPAGE"); return 1;
        case KEY_STAB:
            strcpy(buffer, "KEY_STAB"); return 1;
        case KEY_CTAB:
            strcpy(buffer, "KEY_CTAB"); return 1;
        case KEY_CATAB:
            strcpy(buffer, "KEY_CATAB"); return 1;
        case KEY_ENTER:
            strcpy(buffer, "KEY_ENTER"); return 1;
        case KEY_PRINT:
            strcpy(buffer, "KEY_PRINT"); return 1;
        case KEY_LL:
            strcpy(buffer, "KEY_LL"); return 1;
        case KEY_A1:
            strcpy(buffer, "KEY_A1"); return 1;
        case KEY_A3:
            strcpy(buffer, "KEY_A3"); return 1;
        case KEY_B2:
            strcpy(buffer, "KEY_B2"); return 1;
        case KEY_C1:
            strcpy(buffer, "KEY_C1"); return 1;
        case KEY_C3:
            strcpy(buffer, "KEY_C3"); return 1;
        case KEY_BTAB:
            strcpy(buffer, "KEY_BTAB"); return 1;
        case KEY_BEG:
            strcpy(buffer, "KEY_BEG"); return 1;
        case KEY_CANCEL:
            strcpy(buffer, "KEY_CANCEL"); return 1;
        case KEY_CLOSE:
            strcpy(buffer, "KEY_CLOSE"); return 1;
        case KEY_COMMAND:
            strcpy(buffer, "KEY_COMMAND"); return 1;
        case KEY_COPY:
            strcpy(buffer, "KEY_COPY"); return 1;
        case KEY_CREATE:
            strcpy(buffer, "KEY_CREATE"); return 1;
        case KEY_END:
            strcpy(buffer, "KEY_END"); return 1;
        case KEY_EXIT:
            strcpy(buffer, "KEY_EXIT"); return 1;
        case KEY_FIND:
            strcpy(buffer, "KEY_FIND"); return 1;
        case KEY_HELP:
            strcpy(buffer, "KEY_HELP"); return 1;
        case KEY_MARK:
            strcpy(buffer, "KEY_MARK"); return 1;
        case KEY_MESSAGE:
            strcpy(buffer, "KEY_MESSAGE"); return 1;
        case KEY_MOVE:
            strcpy(buffer, "KEY_MOVE"); return 1;
        case KEY_NEXT:
            strcpy(buffer, "KEY_NEXT"); return 1;
        case KEY_OPEN:
            strcpy(buffer, "KEY_OPEN"); return 1;
        case KEY_OPTIONS:
            strcpy(buffer, "KEY_OPTIONS"); return 1;
        case KEY_PREVIOUS:
            strcpy(buffer, "KEY_PREVIOUS"); return 1;
        case KEY_REDO:
            strcpy(buffer, "KEY_REDO"); return 1;
        case KEY_REFERENCE:
            strcpy(buffer, "KEY_REFERENCE"); return 1;
        case KEY_REFRESH:
            strcpy(buffer, "KEY_REFRESH"); return 1;
        case KEY_REPLACE:
            strcpy(buffer, "KEY_REPLACE"); return 1;
        case KEY_RESTART:
            strcpy(buffer, "KEY_RESTART"); return 1;
        case KEY_RESUME:
            strcpy(buffer, "KEY_RESUME"); return 1;
        case KEY_SAVE:
            strcpy(buffer, "KEY_SAVE"); return 1;
        case KEY_SBEG:
            strcpy(buffer, "KEY_SBEG"); return 1;
        case KEY_SCANCEL:
            strcpy(buffer, "KEY_SCANCEL"); return 1;
        case KEY_SCOMMAND:
            strcpy(buffer, "KEY_SCOMMAND"); return 1;
        case KEY_SCOPY:
            strcpy(buffer, "KEY_SCOPY"); return 1;
        case KEY_SCREATE:
            strcpy(buffer, "KEY_SCREATE"); return 1;
        case KEY_SDC:
            strcpy(buffer, "KEY_SDC"); return 1;
        case KEY_SDL:
            strcpy(buffer, "KEY_SDL"); return 1;
        case KEY_SELECT:
            strcpy(buffer, "KEY_SELECT"); return 1;
        case KEY_SEND:
            strcpy(buffer, "KEY_SEND"); return 1;
        case KEY_SEOL:
            strcpy(buffer, "KEY_SEOL"); return 1;
        case KEY_SEXIT:
            strcpy(buffer, "KEY_SEXIT"); return 1;
        case KEY_SFIND:
            strcpy(buffer, "KEY_SFIND"); return 1;
        case KEY_SHELP:
            strcpy(buffer, "KEY_SHELP"); return 1;
        case KEY_SHOME:
            strcpy(buffer, "KEY_SHOME"); return 1;
        case KEY_SIC:
            strcpy(buffer, "KEY_SIC"); return 1;
        case KEY_SLEFT:
            strcpy(buffer, "KEY_SLEFT"); return 1;
        case KEY_SMESSAGE:
            strcpy(buffer, "KEY_SMESSAGE"); return 1;
        case KEY_SMOVE:
            strcpy(buffer, "KEY_SMOVE"); return 1;
        case KEY_SNEXT:
            strcpy(buffer, "KEY_SNEXT"); return 1;
        case KEY_SOPTIONS:
            strcpy(buffer, "KEY_SOPTIONS"); return 1;
        case KEY_SPREVIOUS:
            strcpy(buffer, "KEY_SPREVIOUS"); return 1;
        case KEY_SPRINT:
            strcpy(buffer, "KEY_SPRINT"); return 1;
        case KEY_SREDO:
            strcpy(buffer, "KEY_SREDO"); return 1;
        case KEY_SREPLACE:
            strcpy(buffer, "KEY_SREPLACE"); return 1;
        case KEY_SRIGHT:
            strcpy(buffer, "KEY_SRIGHT"); return 1;
        case KEY_SRSUME:
            strcpy(buffer, "KEY_SRSUME"); return 1;
        case KEY_SSAVE:
            strcpy(buffer, "KEY_SSAVE"); return 1;
        case KEY_SSUSPEND:
            strcpy(buffer, "KEY_SSUSPEND"); return 1;
        case KEY_SUNDO:
            strcpy(buffer, "KEY_SUNDO"); return 1;
        case KEY_SUSPEND:
            strcpy(buffer, "KEY_SUSPEND"); return 1;
        case KEY_UNDO:
            strcpy(buffer, "KEY_UNDO"); return 1;
        case KEY_MOUSE:
            strcpy(buffer, "KEY_MOUSE"); return 1;
        case KEY_RESIZE:
            strcpy(buffer, "KEY_RESIZE"); return 1;
        case KEY_EVENT:
            strcpy(buffer, "KEY_EVENT"); return 1;
        default:
            if (ch > 0xFF) {
                // Handle unknown special keys
                strcpy(buffer, "KEY_SPECIAL");
                return 1;
            } else {
                // Handle UTF-8 or ASCII characters
                int bytes_to_read = 0;

                if ((ch & 0x80) == 0) {
                    // ASCII character (single byte)
                    buffer[0] = (char) ch;
                } else if ((ch & 0xE0) == 0xC0) {
                    // Start of a 2-byte UTF-8 sequence
                    buffer[0] = (char) ch;
                    bytes_to_read = 1;
                } else if ((ch & 0xF0) == 0xE0) {
                    // Start of a 3-byte UTF-8 sequence
                    buffer[0] = (char) ch;
                    bytes_to_read = 2;
                } else if ((ch & 0xF8) == 0xF0) {
                    // Start of a 4-byte UTF-8 sequence
                    buffer[0] = (char) ch;
                    bytes_to_read = 3;
                }

                for (i = 1; i <= bytes_to_read; ++i) {
                    buffer[i] = (char) wgetch(window);
                }
                buffer[i] = 0;
            }
    }
    return 0;
}

/*
 * Helper function to process a printf format specifier
 * The function returns an integer offset to the next specifier in the format string
 * or NULL if there are no more specifiers, or -1 if the specifier is invalid.
 *
 * This function is called in a loop, the caller can then call the curses printf
 * type function with one argument at a time.
 *
 * The cRexx Curse library only supports string specifiers (e.g. %s) so this
 * function validates that only these exist in the string. The actual curses
 * printf function will interpret and format the output string and arguments.
 *
 * param format The format string to validate
 * return The offset to the start of the next specifier, or
 *      NULL if there are no more specifiers, or
 *      -1 if the format string is invalid
 */
static int validate_format_string(char* format)
{
    /*
     * The printf format specifier contains argument specified in this format
     *    %[flags][width][.precision][length]specifier
     *    The hazards are
     *    - any non-s specifier
     *    - any escaped '%' character (acceptable - but does not count as an argument)
     *    - any * (a width or precision requiring an additional non-string argument)
     */
    int i;
    size_t len = strlen(format);
    for (i = 0; i < len; i++) {
        if (format[i] == '%') {
            if (i + 1 < len) {
                // Escaped % character
                if (format[i + 1] == '%') {
                    i++;
                    continue;
                }
                // Skip flags
                while (format[i + 1] == '-' ||
                       format[i + 1] == '+' ||
                       format[i + 1] == ' ' ||
                       format[i + 1] == '#' ||
                       format[i + 1] == '0') {
                    i++;
                }
                // Skip width
                if (format[i + 1] == '*') {
                    return -1; // Error - width requires an integer argument
                }
                while (isdigit(format[i + 1])) {
                    i++;
                }
                // Skip precision
                if (format[i + 1] == '.') {
                    i++;
                    if (format[i + 1] == '*') {
                        return -1; // Error - precision requires an integer argument
                    }
                    while (isdigit(format[i + 1])) {
                        i++;
                    }
                }
                // Skip Length
                // h or hh
                if (format[i + 1] == 'h') {
                    i++;
                    if (format[i + 1] == 'h') {
                        i++;
                    }
                }
                // l or ll
                if (format[i + 1] == 'l') {
                    i++;
                    if (format[i + 1] == 'l') {
                        i++;
                    }
                }
                // The rest of lengths
                if (format[i + 1] == 'L' ||
                    format[i + 1] == 'z' ||
                    format[i + 1] == 'j' ||
                    format[i + 1] == 't') {
                    i++;
                }
                // Check for the specifier
                if (format[i + 1] != 's') {
                    return -1; // Error - only string specifiers are supported
                }
                return i + 2; // Offset to the next specifier
            }
        }
    }
    return 0; // No more specifiers
}

/*
 * Helper function providing the common printw wrapper
 *
 * The function uses printf() style format strings and arguments to print
 * except it only supports string specifiers.
 */
static void
common_printw(WINDOW* window, rxinteger _numargs, rxpa_attribute_value *_arg, rxpa_attribute_value _return, rxpa_attribute_value _signal)
{
    int args = NUM_ARGS - 1;
    int arg = 0;

    // Need to check that the format string only contains string specifiers
    // and that the number of arguments matches the number of specifiers
    char* format = GETSTRING(ARG(0));
    size_t format_len = strlen(format);
    size_t pos = 0;

    // Loop round processing specifiers
    while (pos < format_len) {
        // Find the next specifier
        int next = validate_format_string(format + pos);
        if (next < 0) {
            RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid format string, only strings are supported")
        }
        if (next == 0) {
            // No additional specifier found.
            // Print the remaining format string
            waddstr(window, format + pos);
            // Check error
            if (args != arg) {
                RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "number of arguments does not match format string")
            }
            break;
        }

        // Malloc a buffer and copy the format specifier part to it
        char* specifier = malloc(next - pos + 1);
        if (specifier == NULL) {
            RETURNSIGNAL(SIGNAL_FAILURE, "out of memory")
        }
        memcpy(specifier, format + pos, next - pos);
        specifier[next - pos] = '\0';
        // Print specifier with arg
        arg++;
        wprintw(window, specifier, GETSTRING(ARG(arg)));
        free(specifier);
        pos += next;
    }
}

/**
 * @brief Adds a string to the screen
 *
 * Prints a string to the screen at the current cursor position.
 *
 * This function is a wrapper for curses `addstr()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `addstr()`.
 */
PROCEDURE(rx_addstr)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected string")

    // Call addstr() and check for errors
    if (addstr(GETSTRING(ARG(0))) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses addstr() failure")
    }
}

/**
 * @brief Sets the visibility of the cursor
 *
 * This function is a wrapper for curses `curs_set()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `curs_set()`.
 */
PROCEDURE(rx_curs_set)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected visibility")

    // Call curs_set() and check for errors
    int result = curs_set(GETINT(ARG(0)));
    if (result == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses curs_set() failure")
    }
}

/**
 * @brief Deletes a window
 *
 * This function is a wrapper for curses `delwin()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `delwin()`.
 */
PROCEDURE(rx_delwin)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call delwin() and check for errors
    int result = delwin(win);
    if (result != OK) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses delwin() failure")
    }
}

/**
 * @brief Turns on echo
 *
 * This function is a wrapper for curses `echo()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `echo()`.
 */
PROCEDURE(rx_echo)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "no arguments expected")

    // Call echo() and check for errors
    int result = echo();
    if (result != OK) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses echo() failure")
    }
}

/**
 * @brief Turns off echo
 *
 * This function is a wrapper for curses `noecho()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `noecho()`.
 */
PROCEDURE(rx_noecho)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "no arguments expected")

    // Call noecho() and check for errors
    int result = noecho();
    if (result != OK) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses noecho() failure")
    }
}

/**
 * @brief Restores the terminal after Curses activity.
 *
 * This function is a wrapper for curses `endwin()`. It does not free the storage
 * associated with a screen, so `delscreen()` should be called after `endwin()`
 * if a particular screen is no longer needed.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `endwin()`.
 */
PROCEDURE(rx_endwin)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "No arguments expected")

    // Call endwin() and check for errors
    if( endwin() != OK) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses endwin() failure")
}

/**
 *
 * @brief Reads a single character from the keyboard.
 *
 * This function is a wrapper for curses `getch()`.
 *
 * @return Returns the character read as a string.
 */
PROCEDURE(rx_getch)
{
    char character[15]; // utf8 character buffer
    int rc;
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "No arguments expected")

    // Get the character
    rc = getch_utf8(stdscr, character);
    if (rc == -1) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses getch() failure")
    }

    // Set the return value
    SETSTRING(RETURN, character);
}

/**
 * @brief Retrieves the dimensions of a window
 *
 * This function is a wrapper for curses `getmaxyx()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `getmaxyx()`.
 */
PROCEDURE(rx_getmaxyx)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, y, x")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the dimensions
    int y, x;
    getmaxyx(win, y, x);

    // Set the return values
    SETINT(ARG(1), y);
    SETINT(ARG(2), x);
}

/**
 * @brief Initializes the library and sets up the screen.
 *
 * This function is a wrapper for curses `initscr()` and returns a `WINDOW` pointer.
 * If an error occurs, this function will exit the program.
 *
 * @return Returns a WINDOW pointer as an integer on success.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 */
PROCEDURE(rx_initscr)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "No arguments expected")

    // Initialise the screen
    SETINT(RETURN, (size_t)initscr());
}

/**
 * @brief Enables the reading of function keys and arrow keys
 *
 * This function is a wrapper for curses `keypad()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `keypad()`.
 */
PROCEDURE(rx_keypad)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, enable")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call keypad() and check for errors
    int result = keypad(win, GETINT(ARG(1)));
    if (result != OK) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses keypad() failure")
    }
}

/**
 * @brief Adds a string to the screen at a position
 *
 * Prints a string to the screen at the specified position.
 *
 * This function is a wrapper for curses `mvaddstr()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `mvaddstr()`.
 */
PROCEDURE(rx_mvaddstr)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "y, x, string")

    // Get the window pointer
    int y = GETINT(ARG(0));
    int x = GETINT(ARG(1));
    char *string = GETSTRING(ARG(2));

    // Call mvaddstr() and check for errors
    if (mvaddstr(y, x, string) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses mvaddstr() failure")
    }
}

/**
 * @brief Moves the cursor and prints formatted output
 *
 * Moves the cursor to the specified location and prints formatted output.
 * The function uses printf() style format strings and arguments to print
 * except it only supports string specifiers.
 *
 * This function is a wrapper for `mvprintw()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal INVALID_ARGUMENTS if the format string is invalid.
 * @signal FAILURE if an error occurs during the execution of `mvprintw()`.
 */
PROCEDURE(rx_mvprintw)
{
    /* Check for the correct number of arguments (at least 3) */
    if( NUM_ARGS < 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected y, x, format, ...")
    int y = GETINT(ARG(0));
    int x = GETINT(ARG(1));

    /* Move the cursor */
    if (move(y, x) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses move() failure")
    }

    /* Call common wrapper */
    common_printw(stdscr, _numargs - 2, &(_arg[2]), _return, _signal);
}

/**
 * @brief Moves the cursor and adds a string to a window
 *
 * Moves the cursor to the specified location and prints a string to the window.
 *
 * This function is a wrapper for curses `mvwaddstr()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `mvwaddstr()`.
 */
PROCEDURE(rx_mvwaddstr)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 4) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, y, x, string")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));
    int y = GETINT(ARG(1));
    int x = GETINT(ARG(2));
    char *string = GETSTRING(ARG(3));

    // Call mvwaddstr() and check for errors
    if (mvwaddstr(win, y, x, string) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses mvwaddstr() failure")
    }
}

/**
 * @brief Moves the cursor and prints formatted output to a window
 *
 * Moves the cursor to the specified location and prints formatted output.
 *
 * The function uses printf() style format strings and arguments to print
 * except it only supports string specifiers.
 *
 * This function is a wrapper for `mvwprintw()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal INVALID_ARGUMENTS if the format string is invalid.
 * @signal FAILURE if an error occurs during the execution of `mvwprintw()`.
 */
PROCEDURE(rx_mvwprintw)
{
    /* Check for the correct number of arguments (at least 4) */
    if( NUM_ARGS < 4) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, y, x, format, ...")
    WINDOW* window = (WINDOW*)GETINT(ARG(0));
    int y = GETINT(ARG(1));
    int x = GETINT(ARG(2));

    /* Move the cursor */
    if (wmove(window, y, x) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wmove() failure")
    }

    /* Call common wrapper */
    common_printw(window, _numargs - 3, &(_arg[3]), _return, _signal);
}


/**
 * @brief Creates a new window
 *
 * Creates a new window with the given number of lines and columns.
 * The upper left-hand corner of the window is at line begin_y, column begin_x
 * A new full-screen window is created by calling newwin(0,0,0,0).
 *
 * This function is a wrapper for curses `newwin()`
 *
 * @return Returns a WINDOW pointer as an integer on success.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `refresh()`.
 */
PROCEDURE(rx_newwin)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 4) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected nlines, ncols, begin_y, begin_x")

    // Call newwin()
    WINDOW* win = newwin( GETINT(ARG(0)), GETINT(ARG(1)), GETINT(ARG(2)), GETINT(ARG(3)) );

    // Check for errors
    if (!win) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses newwin() failure")

    // Set the return value
    SETINT(RETURN, (uintptr_t)win);
}

/**
 * @brief Prints formatted output to the standard window (stdscr)
 *
 * The function uses printf() style format strings and arguments to print
 * except it only supports string specifiers.
 *
 * This function is a wrapper for `printw()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal INVALID_ARGUMENTS if the format string is invalid.
 * @signal FAILURE if an error occurs during the execution of `printw()`.
 */
PROCEDURE(rx_printw)
{
    /* Check for the correct number of arguments (at least 1) */
    if( NUM_ARGS < 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected format, ...")

    /* Call common wrapper */
    common_printw(stdscr, _numargs, _arg, _return, _signal);
}

/**
 * @brief Refreshes the screen to reflect changes
 *
 * This function is a wrapper for `refresh()
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `refresh()`.
 */
PROCEDURE(rx_refresh)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "No arguments expected")

    // Call refresh() and check for errors
    if( refresh() != OK) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses refresh() failure")
}

/**
 * @brief Enable or disable scrolling of the window
 *
 * This function is a wrapper for `scrollok()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `scrollok()`.
 */
PROCEDURE(rx_scrollok)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, enable")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call scrollok() and check for errors
    int result = scrollok(win, GETINT(ARG(1)));
    if (result != OK) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses scrollok() failure")
    }
}

/**
 *
 * @brief Reads a single character from the keyboard.
 *
 * This function is a wrapper for curses `wgetch()`.
 *
 * @return Returns the character read as a string.
 */
PROCEDURE(rx_wgetch)
{
    char character[15]; // utf8 character buffer
    int rc;
    WINDOW *win;
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    win = (WINDOW*)GETINT(ARG(0));

    // Get the character
    rc = getch_utf8(win, character);
    if (rc == -1) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses getch() failure")
    }

    // Set the return value
    SETSTRING(RETURN, character);
}

/**
 * @brief Adds a string to a window
 *
 * Prints a string to the window at the current cursor position.
 *
 * This function is a wrapper for curses `waddstr()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `waddstr()`.
 */
PROCEDURE(rx_waddstr)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, string")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));
    char *string = GETSTRING(ARG(1));

    // Call waddstr() and check for errors
    if (waddstr(win, string) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses waddstr() failure")
    }
}

/**
 * @brief Prints formatted output to the window
 *
 * The function uses printf() style format strings and arguments to print
 * except it only supports string specifiers.
 *
 * This function is a wrapper for `wprintw()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal INVALID_ARGUMENTS if the format string is invalid.
 * @signal FAILURE if an error occurs during the execution of `printw()`.
 */
PROCEDURE(rx_wprintw)
{
    /* Check for the correct number of arguments (at least 1) */
    if( NUM_ARGS < 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, format, ...")
    WINDOW* window = (WINDOW*)GETINT(ARG(0));

    /* Call common wrapper */
    common_printw(window, _numargs - 1, &(_arg[1]), _return, _signal);
}

/**
 * @brief Refreshes the screen to reflect changes
 *
 * This function is a wrapper for `wrefresh()
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `refresh()`.
 */
PROCEDURE(rx_wrefresh)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window");

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Call refresh() and check for errors
    if( wrefresh(win) != OK) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wrefresh() failure")
}

/**
 * @brief Helper function to un-escape a C string, which can then be passed to curses
 * @param str The string to un-escape
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during execution
 *
 * @return The un-escaped string
 */
PROCEDURE(rx_unescape)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected string");

    char* str = GETSTRING(ARG(0));
    char* buffer = malloc(strlen(str) + 1);
    if (buffer == NULL) {
        RETURNSIGNAL(SIGNAL_FAILURE, "out of memory");
    }
    char* p = buffer;
    while (*str) {
        if (*str == '\\') {
            str++;
            switch (*str) {
                case 'n':
                    *p++ = '\n';
                    break;
                case 'r':
                    *p++ = '\r';
                    break;
                case 't':
                    *p++ = '\t';
                    break;
                case '0':
                    *p++ = '\0';
                    break;
                case '\\':
                    *p++ = '\\';
                    break;
                default:
                    *p++ = *str;
                    break;
            }
        } else {
            *p++ = *str;
        }
        str++;
    }
    *p = '\0';

    SETSTRING(RETURN, buffer);
    free(buffer);
}

// Functions to be provided to rexx - these are loaded either when the plugin is loaded (dynamic) or
// before main() is called (static)
LOADFUNCS
//      C Function__, REXX namespace & name, Option_, Return Type_, Arguments
ADDPROC(rx_addstr,    "rxcurses.addstr",    "b",      ".void",    "string=.string");
ADDPROC(rx_curs_set,  "rxcurses.curs_set",  "b",      ".void",    "visibility=.int");
ADDPROC(rx_delwin,    "rxcurses.delwin",    "b",      ".void",    "window=.int");
ADDPROC(rx_endwin,    "rxcurses.endwin",    "b",      ".void",    "");
ADDPROC(rx_getch,     "rxcurses.getch",     "b",      ".string",  "");
ADDPROC(rx_getmaxyx,  "rxcurses.getmaxyx",  "b",      ".void",    "window=.int,expose y=.int,expose x=.int");
ADDPROC(rx_echo,      "rxcurses.echo",      "b",      ".void",    "");
ADDPROC(rx_noecho,    "rxcurses.noecho",    "b",      ".void",    "");
ADDPROC(rx_initscr,   "rxcurses.initscr",   "b",      ".int",     "");
ADDPROC(rx_keypad,    "rxcurses.keypad",    "b",      ".void",    "window=.int,enable=.int");
ADDPROC(rx_mvaddstr,  "rxcurses.mvaddstr",  "b",      ".void",    "y=.int,x=.int,string=.string");
ADDPROC(rx_mvprintw,  "rxcurses.mvprintw",  "b",      ".void",    "y=.int,x=.int,format=.string,...=.string");
ADDPROC(rx_mvwprintw, "rxcurses.mvwprintw", "b",      ".void",    "window=.int,y=.int,x=.int,format=.string,...=.string");
ADDPROC(rx_mvwaddstr, "rxcurses.mvwaddstr", "b",      ".void",    "window=.int,y=.int,x=.int,string=.string");
ADDPROC(rx_newwin,    "rxcurses.newwin",    "b",      ".int",     "nlines=.int,ncols=.int,begin_y=.int,begin_x=.int");
ADDPROC(rx_printw,    "rxcurses.printw",    "b",      ".void",    "format=.string,...=.string");
ADDPROC(rx_refresh,   "rxcurses.refresh",   "b",      ".void",    "");
ADDPROC(rx_scrollok,  "rxcurses.scrollok",  "b",      ".void",    "window=.int,enable=.int");
ADDPROC(rx_waddstr,   "rxcurses.waddstr",   "b",      ".void",    "window=.int,string=.string");
ADDPROC(rx_wgetch,    "rxcurses.wgetch",    "b",      ".string",  "window=.int");
ADDPROC(rx_wprintw,   "rxcurses.wprintw",   "b",      ".void",    "window=.int,format=.string,...=.string");
ADDPROC(rx_wrefresh,  "rxcurses.wrefresh",  "b",      ".void",    "window=.int");
ADDPROC(rx_unescape,  "rxcurses.unescape",  "b",      ".string",  "string=.string");
ENDLOADFUNCS
