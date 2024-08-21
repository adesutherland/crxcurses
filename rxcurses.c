// rxcurses - CREXX Wrapper for the ncurses library

#include <ncurses.h>
#include "crexxpa.h"    // crexx/pa - Plugin Architecture header file
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

/*
 * Helper function to get a UTF-8 character from ncurses
 * It is a wrapper around the wgetch function that handles
 * special keys and UTF-8 characters. It returns the UTF-8
 * character as a string in the buffer passed as an argument.
 * If a special key is pressed, the key name is stored in the buffer.
 * If there is no input (timeout), the buffer is set to an empty string.
 *
 * It has special functionality to handle the BACKSPACE key; additionally 127
 * and '\b' are mapped to BACKSPACE. Also the \n a d \r are mapped to ENTER.
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
        case ERR: // No input / Timeout
            strcpy(buffer, ""); return 0;
        case '\n':
        case '\r':
            strcpy(buffer, "[ENTER]"); return 0;
        case KEY_CODE_YES:
            strcpy(buffer, "[CODE_YES]"); return 1;
        case KEY_BREAK:
            strcpy(buffer, "[BREAK]"); return 1;
        case KEY_SRESET:
            strcpy(buffer, "[SRESET]"); return 1;
        case KEY_RESET:
            strcpy(buffer, "[RESET]"); return 1;
        case KEY_DOWN:
            strcpy(buffer, "[DOWN]"); return 1;
        case KEY_UP:
            strcpy(buffer, "[UP]"); return 1;
        case KEY_LEFT:
            strcpy(buffer, "[LEFT]"); return 1;
        case KEY_RIGHT:
            strcpy(buffer, "[RIGHT]"); return 1;
        case KEY_HOME:
            strcpy(buffer, "[HOME]"); return 1;
        case KEY_BACKSPACE:
        case 127:
        case '\b':
            strcpy(buffer, "[BACKSPACE]"); return 1;
        case KEY_F(1):
            strcpy(buffer, "[F1]"); return 1;
        case KEY_F(2):
            strcpy(buffer, "[F2]"); return 1;
        case KEY_F(3):
            strcpy(buffer, "[F3]"); return 1;
        case KEY_F(4):
            strcpy(buffer, "[F4]"); return 1;
        case KEY_F(5):
            strcpy(buffer, "[F5]"); return 1;
        case KEY_F(6):
            strcpy(buffer, "[F6]"); return 1;
        case KEY_F(7):
            strcpy(buffer, "[F7]"); return 1;
        case KEY_F(8):
            strcpy(buffer, "[F8]"); return 1;
        case KEY_F(9):
            strcpy(buffer, "[F9]"); return 1;
        case KEY_F(10):
            strcpy(buffer, "[F10]"); return 1;
        case KEY_F(11):
            strcpy(buffer, "[F11]"); return 1;
        case KEY_F(12):
            strcpy(buffer, "[F12]"); return 1;
        case KEY_DL:
            strcpy(buffer, "[DL]"); return 1;
        case KEY_IL:
            strcpy(buffer, "[IL]"); return 1;
        case KEY_DC:
            strcpy(buffer, "[DC]"); return 1;
        case KEY_IC:
            strcpy(buffer, "[IC]"); return 1;
        case KEY_EIC:
            strcpy(buffer, "[EIC]"); return 1;
        case KEY_CLEAR:
            strcpy(buffer, "[CLEAR]"); return 1;
        case KEY_EOS:
            strcpy(buffer, "[EOS]"); return 1;
        case KEY_EOL:
            strcpy(buffer, "[EOL]"); return 1;
        case KEY_SF:
            strcpy(buffer, "[SF]"); return 1;
        case KEY_SR:
            strcpy(buffer, "[SR]"); return 1;
        case KEY_NPAGE:
            strcpy(buffer, "[NPAGE]"); return 1;
        case KEY_PPAGE:
            strcpy(buffer, "[PPAGE]"); return 1;
        case KEY_STAB:
            strcpy(buffer, "[STAB]"); return 1;
        case KEY_CTAB:
            strcpy(buffer, "[CTAB]"); return 1;
        case KEY_CATAB:
            strcpy(buffer, "[CATAB]"); return 1;
        case KEY_ENTER:
            strcpy(buffer, "[ENTER]"); return 1;
        case KEY_PRINT:
            strcpy(buffer, "[PRINT]"); return 1;
        case KEY_LL:
            strcpy(buffer, "[LL]"); return 1;
        case KEY_A1:
            strcpy(buffer, "[A1]"); return 1;
        case KEY_A3:
            strcpy(buffer, "[A3]"); return 1;
        case KEY_B2:
            strcpy(buffer, "[B2]"); return 1;
        case KEY_C1:
            strcpy(buffer, "[C1]"); return 1;
        case KEY_C3:
            strcpy(buffer, "[C3]"); return 1;
        case KEY_BTAB:
            strcpy(buffer, "[BTAB]"); return 1;
        case KEY_BEG:
            strcpy(buffer, "[BEG]"); return 1;
        case KEY_CANCEL:
            strcpy(buffer, "[CANCEL]"); return 1;
        case KEY_CLOSE:
            strcpy(buffer, "[CLOSE]"); return 1;
        case KEY_COMMAND:
            strcpy(buffer, "[COMMAND]"); return 1;
        case KEY_COPY:
            strcpy(buffer, "[COPY]"); return 1;
        case KEY_CREATE:
            strcpy(buffer, "[CREATE]"); return 1;
        case KEY_END:
            strcpy(buffer, "[END]"); return 1;
        case KEY_EXIT:
            strcpy(buffer, "[EXIT]"); return 1;
        case KEY_FIND:
            strcpy(buffer, "[FIND]"); return 1;
        case KEY_HELP:
            strcpy(buffer, "[HELP]"); return 1;
        case KEY_MARK:
            strcpy(buffer, "[MARK]"); return 1;
        case KEY_MESSAGE:
            strcpy(buffer, "[MESSAGE]"); return 1;
        case KEY_MOVE:
            strcpy(buffer, "[MOVE]"); return 1;
        case KEY_NEXT:
            strcpy(buffer, "[NEXT]"); return 1;
        case KEY_OPEN:
            strcpy(buffer, "[OPEN]"); return 1;
        case KEY_OPTIONS:
            strcpy(buffer, "[OPTIONS]"); return 1;
        case KEY_PREVIOUS:
            strcpy(buffer, "[PREVIOUS]"); return 1;
        case KEY_REDO:
            strcpy(buffer, "[REDO]"); return 1;
        case KEY_REFERENCE:
            strcpy(buffer, "[REFERENCE]"); return 1;
        case KEY_REFRESH:
            strcpy(buffer, "[REFRESH]"); return 1;
        case KEY_REPLACE:
            strcpy(buffer, "[REPLACE]"); return 1;
        case KEY_RESTART:
            strcpy(buffer, "[RESTART]"); return 1;
        case KEY_RESUME:
            strcpy(buffer, "[RESUME]"); return 1;
        case KEY_SAVE:
            strcpy(buffer, "[SAVE]"); return 1;
        case KEY_SBEG:
            strcpy(buffer, "[SBEG]"); return 1;
        case KEY_SCANCEL:
            strcpy(buffer, "[SCANCEL]"); return 1;
        case KEY_SCOMMAND:
            strcpy(buffer, "[SCOMMAND]"); return 1;
        case KEY_SCOPY:
            strcpy(buffer, "[SCOPY]"); return 1;
        case KEY_SCREATE:
            strcpy(buffer, "[SCREATE]"); return 1;
        case KEY_SDC:
            strcpy(buffer, "[SDC]"); return 1;
        case KEY_SDL:
            strcpy(buffer, "[SDL]"); return 1;
        case KEY_SELECT:
            strcpy(buffer, "[SELECT]"); return 1;
        case KEY_SEND:
            strcpy(buffer, "[SEND]"); return 1;
        case KEY_SEOL:
            strcpy(buffer, "[SEOL]"); return 1;
        case KEY_SEXIT:
            strcpy(buffer, "[SEXIT]"); return 1;
        case KEY_SFIND:
            strcpy(buffer, "[SFIND]"); return 1;
        case KEY_SHELP:
            strcpy(buffer, "[SHELP]"); return 1;
        case KEY_SHOME:
            strcpy(buffer, "[SHOME]"); return 1;
        case KEY_SIC:
            strcpy(buffer, "[SIC]"); return 1;
        case KEY_SLEFT:
            strcpy(buffer, "[SLEFT]"); return 1;
        case KEY_SMESSAGE:
            strcpy(buffer, "[SMESSAGE]"); return 1;
        case KEY_SMOVE:
            strcpy(buffer, "[SMOVE]"); return 1;
        case KEY_SNEXT:
            strcpy(buffer, "[SNEXT]"); return 1;
        case KEY_SOPTIONS:
            strcpy(buffer, "[SOPTIONS]"); return 1;
        case KEY_SPREVIOUS:
            strcpy(buffer, "[SPREVIOUS]"); return 1;
        case KEY_SPRINT:
            strcpy(buffer, "[SPRINT]"); return 1;
        case KEY_SREDO:
            strcpy(buffer, "[SREDO]"); return 1;
        case KEY_SREPLACE:
            strcpy(buffer, "[SREPLACE]"); return 1;
        case KEY_SRIGHT:
            strcpy(buffer, "[SRIGHT]"); return 1;
        case KEY_SRSUME:
            strcpy(buffer, "[SRSUME]"); return 1;
        case KEY_SSAVE:
            strcpy(buffer, "[SSAVE]"); return 1;
        case KEY_SSUSPEND:
            strcpy(buffer, "[SSUSPEND]"); return 1;
        case KEY_SUNDO:
            strcpy(buffer, "[SUNDO]"); return 1;
        case KEY_SUSPEND:
            strcpy(buffer, "[SUSPEND]"); return 1;
        case KEY_UNDO:
            strcpy(buffer, "[UNDO]"); return 1;
        case KEY_MOUSE:
            strcpy(buffer, "[MOUSE]"); return 1;
        case KEY_RESIZE:
            strcpy(buffer, "[RESIZE]"); return 1;
        case KEY_EVENT:
            strcpy(buffer, "[EVENT]"); return 1;
        default:
            if (ch > 0xFF) {
                // Handle unknown special keys
                strcpy(buffer, "[SPECIAL]");
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
 * Helper function to process a string of space seperated attributes and color pairs and return
 * the ore'd value for all the attributes and the color pair number.
 *
 * Returns the ore'd value of the attributes and the color pair number.
 *
 * On error, the function returns -1.
 */
static int get_attributes(char* attribute_list)
{
    int attributes = 0;
    int colour_pair = 0;
    char* p;
    char* q;

    // Copy the attribute string to a buffer and convert it to uppercase
    // to make the comparison case-insensitive, and we can write to the buffer
    char* attribute_uppercase = strdup(attribute_list);
    if (attribute_uppercase == NULL) {
        return -1;
    }
    for (p = attribute_uppercase; *p; p++) {
        *p = (char)toupper(*p);
    }

    // Process the string character by character skipping spaces,
    // finding the start of the next attribute or color pair and zero terminating it,
    // then checking if it is a known attribute or a color pair
    for (p = attribute_uppercase; *p; p++) {
        if (*p == ' ') {
            continue;
        }
        char* start = p;
        while (*p && *p != ' ') {
            p++;
        }
        *p = 0;
        if (strcmp(start, "NORMAL") == 0) {
            attributes |= A_NORMAL;
        } else if (strcmp(start, "STANDOUT") == 0) {
            attributes |= A_STANDOUT;
        } else if (strcmp(start, "UNDERLINE") == 0) {
            attributes |= A_UNDERLINE;
        } else if (strcmp(start, "REVERSE") == 0) {
            attributes |= A_REVERSE;
        } else if (strcmp(start, "BLINK") == 0) {
            attributes |= A_BLINK;
        } else if (strcmp(start, "DIM") == 0) {
            attributes |= A_DIM;
        } else if (strcmp(start, "BOLD") == 0) {
            attributes |= A_BOLD;
        } else if (strcmp(start, "PROTECT") == 0) {
            attributes |= A_PROTECT;
        } else if (strcmp(start, "INVIS") == 0) {
            attributes |= A_INVIS;
        } else if (strcmp(start, "ALTCHARSET") == 0) {
            attributes |= A_ALTCHARSET;
        } else if (strcmp(start, "CHARTEXT") == 0) {
            attributes |= A_CHARTEXT;
        } else {
            // Assume it is a color pair that is in the format COLOR_PAIR(n) where n is the
            // colour pair number we need to extract n
            if (strncmp(start, "COLOR_PAIR(", 11) != 0) {
                free(attribute_uppercase);
                return -1;
            }
            start += 11;
            // Find the ) and null terminate the string
            q = strchr(start, ')');
            if (q == NULL) {
                free(attribute_uppercase);
                return -1;
            }
            *q = 0;
            /* Convert the string to an integer using strtol */
            colour_pair = (int)strtol(start, &q, 10);
            if (*q != 0) {
                free(attribute_uppercase);
                return -1;
            }
            attributes |= COLOR_PAIR(colour_pair);
        }
    }
    free(attribute_uppercase);

    return attributes;
}

/* Helper function to convert a color string to an integer value */
static short get_color(char* color)
{
    char* p;
    /* Copy and uppercase the color string */
    char* color_uppercase = strdup(color);
    if (color_uppercase == NULL) {
        return -1;
    }
    for (p = color_uppercase; *p; p++) {
        *p = (char)toupper(*p);
    }

    if (strcmp(color_uppercase, "BLACK") == 0) {
        return COLOR_BLACK;
    } else if (strcmp(color_uppercase, "RED") == 0) {
        return COLOR_RED;
    } else if (strcmp(color_uppercase, "GREEN") == 0) {
        return COLOR_GREEN;
    } else if (strcmp(color_uppercase, "YELLOW") == 0) {
        return COLOR_YELLOW;
    } else if (strcmp(color_uppercase, "BLUE") == 0) {
        return COLOR_BLUE;
    } else if (strcmp(color_uppercase, "MAGENTA") == 0) {
        return COLOR_MAGENTA;
    } else if (strcmp(color_uppercase, "CYAN") == 0) {
        return COLOR_CYAN;
    } else if (strcmp(color_uppercase, "WHITE") == 0) {
        return COLOR_WHITE;
    } else {
        return -1;
    }
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
        char* specifier = malloc(next + 1);
        if (specifier == NULL) {
            RETURNSIGNAL(SIGNAL_FAILURE, "out of memory")
        }
        memcpy(specifier, format + pos, next);
        specifier[next] = '\0';
        // Print specifier with arg
        arg++;
        wprintw(window, specifier, GETSTRING(ARG(arg)));
        free(specifier);
        pos += next;
    }
}

// Global variable holding the say rediect window
WINDOW* say_window = NULL;

/*
 * Helper function that prints a string to window `say_window`
 */
static void print_to_window(char* string)
{
    if (say_window != NULL) {
        waddstr(say_window, string);
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
 * @brief Turns on text attributes like bold or underline for the screen
 *
 * This function is a wrapper for curses `attron()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `attron()`.
 */
PROCEDURE(rx_attron)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected attributes")

    // Get the attributes
    int attributes = get_attributes(GETSTRING(ARG(0)));
    if (attributes == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid attributes")
    }

    // Call attron() and check for errors
    if (attron(attributes) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses attron() failure")
    }
}

/**
 * @brief Turns off text attributes like bold or underline for the screen
 *
 * This function is a wrapper for curses `attroff()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `attroff()`.
 */
PROCEDURE(rx_attroff)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected attributes")

    // Get the attributes
    int attributes = get_attributes(GETSTRING(ARG(0)));
    if (attributes == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid attributes")
    }

    // Call attroff() and check for errors
    if (attroff(attributes) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses attroff() failure")
    }
}

/**
 * @brief Set the background color of the screen
 *
 * This function is a wrapper for curses `bkgd()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `bkgd()`.
 */
PROCEDURE(rx_bkgd)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected attributes")

    // Get the attributes
    int attributes = get_attributes(GETSTRING(ARG(0)));
    if (attributes == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid attributes")
    }

    // Call bkgd() and check for errors
    bkgd(attributes);
}

/**
 * @brief Draws a box around a window
 *
 * This function is a wrapper for curses `box()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `box()`.
 */
PROCEDURE(rx_box)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, vertical, horizontal")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call box() and check for errors
    if (box(win, GETINT(ARG(1)), GETINT(ARG(2))) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses box() failure")
    }
}

/**
 * @brief Sees if the terminal can change colors
 *
 * This function is a wrapper for curses `can_change_color()`.
 *
 * @return Returns 1 if the terminal can change colors, 0 otherwise.
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `can_change_color()`.
 */
PROCEDURE(rx_can_change_color)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "no arguments expected")

    // Call can_change_color() and check for errors
    int result = can_change_color();
    if (result == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses can_change_color() failure")
    }

    // Set the return value
    SETINT(RETURN, result);
}

/** @brief Clears the screen
 *
 * This function is a wrapper for curses `clear()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `clear()`.
 */
PROCEDURE(rx_clear)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "no arguments expected")

    // Call clear() and check for errors
    if (clear() == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses clear() failure")
    }
}

/**
 * @brief Clears the screen to the end of the line
 *
 * This function is a wrapper for curses `clrtoeol()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `clrtoeol()`.
 */
PROCEDURE(rx_clrtoeol)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "no arguments expected")

    // Call clrtoeol() and check for errors
    if (clrtoeol() == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses clrtoeol() failure")
    }
}

/**
 * @brief Clears the screen to the bottom right corner
 *
 * This function is a wrapper for curses `clrtobot()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `clrtobot()`.
 */
PROCEDURE(rx_clrtobot)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "no arguments expected")

    // Call clrtobot() and check for errors
    if (clrtobot() == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses clrtobot() failure")
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

    // If the delwin() is called on the say_window, reset the say_window
    if (win == say_window) {
        say_window = NULL;
        RESET_SAY_EXIT();
    }

    // Call delwin() and check for errors
    int result = delwin(win);
    if (result != OK) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses delwin() failure")
    }
}

/**
 * @brief Creates a subwindow
 *
 * This function is a wrapper for curses `derwin()` and returns a `WINDOW` pointer.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `derwin()`.
 */
PROCEDURE(rx_derwin)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 5) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, height, width, starty, startx")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the dimensions
    int height = GETINT(ARG(1));
    int width = GETINT(ARG(2));
    int starty = GETINT(ARG(3));
    int startx = GETINT(ARG(4));

    // Call derwin() and check for errors
    WINDOW* subwin = derwin(win, height, width, starty, startx);
    if (subwin == NULL) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses derwin() failure")
    }

    // Set the return value
    SETINT(RETURN, (size_t)subwin);
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

    // Check if say is redirected and reset if need be
    if (say_window != NULL) {
        say_window = NULL;
        RESET_SAY_EXIT();
    }

    // Call endwin() and check for errors
    if( endwin() != OK) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses endwin() failure")
}

/**
 *
 * @brief Reads a single character from the keyboard.
 *
 * This function is a wrapper for curses `getch()`.
 * The function returns
 * - the character read as a string.
 * - the special key as a string in the format [XXX] where XXX is the special key.
 * - an empty string if there was no input within the timeout.
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
 * @brief Retrieves the current cursor position
 *
 * This function is a wrapper for curses `getyx()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `getyx()`.
 */
PROCEDURE(rx_getyx)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, y, x")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the cursor position
    int y, x;
    getyx(win, y, x);

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
 * @brief Define a custom color
 *
 * This function is a wrapper for curses `init_color()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `init_color()`.
 */
PROCEDURE(rx_init_color)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 4) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected color, r, g, b")

    // Check the color number from the color string
    short color = get_color(GETSTRING(ARG(0)));
    if (color == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid color")
    }

    int r = GETINT(ARG(1));
    int g = GETINT(ARG(2));
    int b = GETINT(ARG(3));

    // Call init_color() and check for errors
    if (init_color(color, (short)r, (short)g, (short)b) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses init_color() failure")
    }
}

/**
 * @brief Manages color pairs for text display
 *
 * This function is a wrapper for curses `init_pair()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `init_pair()`.
 */
PROCEDURE(rx_init_pair)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected pair, fg, bg")

    short fg = get_color(GETSTRING(ARG(1)));
    if (fg == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid foreground color")
    }

    short bg = get_color(GETSTRING(ARG(2)));
    if (bg == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid background color")
    }

    // Call init_pair() and check for errors
    if (init_pair(GETINT(ARG(0)), fg, bg) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses init_pair() failure")
    }
}

/**
 * @brief Moves the cursor to a position
 *
 * This function is a wrapper for curses `move()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `move()`.
 */
PROCEDURE(rx_move)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected y, x")

    // Call move() and check for errors
    if (move(GETINT(ARG(0)), GETINT(ARG(1))) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses move() failure")
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
 * @brief Redirects the SAY output to the screen
 *
 * This function is a crexx specific function that redirects the SAY output to the screen.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 */
PROCEDURE(rx_redirectsay)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "No arguments expected")

    // Set the return value
    say_window = stdscr;
    SET_SAY_EXIT(print_to_window);
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
 * @brief Scrolls the entire window up or down by a specified number of lines
 *
 * This function is a wrapper for `scrl()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `scrl()`.
 */
PROCEDURE(rx_scrl)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected n")

    // Call scrl() and check for errors
    if (scrl(GETINT(ARG(0))) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses scrl() failure")
    }
}

/**
 * @brief Scrolls the window one line up
 *
 * This function is a wrapper for `scroll()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `scroll()`.
 */
PROCEDURE(rx_scroll)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call scroll() and check for errors
    if (scroll(win) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses scroll() failure")
    }
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
 * @brief Sets the locale for the terminal
 *
 * This function is a wrapper for `setlocale()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 *  @signal FAILURE if an error occurs during the execution of `setlocale()`.
 */
PROCEDURE(rx_setlocale)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected locale")

    // Call setlocale() and check for errors
    char* result = setlocale(LC_ALL, GETSTRING(ARG(0)));
    if (result == NULL) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses setlocale() failure")
    }
}

/**
 * @brief Initialises color functionality
 *
 * This function is a wrapper for curses `start_color()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `start_color()`.
 */
PROCEDURE(rx_start_color)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 0) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "No arguments expected")

    // Call start_color() and check for errors
    if( start_color() != OK) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses start_color() failure")
}

/**
 * @brief Sets the timeout for keyboard input
 *
 * This function is a wrapper for curses `timeout()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `timeout()`.
 */
PROCEDURE(rx_timeout)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected milliseconds")

    // Call timeout() and check for errors
    timeout(GETINT(ARG(0)));
}

/**
 *
 * @brief Reads a single character from the keyboard.
 *
 * This function is a wrapper for curses `wgetch()`.
 * The function returns
 * - the character read as a string.
 * - the special key as a string in the format [XXX] where XXX is the special key.
 * - an empty string if there was no input within the timeout.
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
 * @brief Turns on text attributes like bold or underline for a window
 *
 * This function is a wrapper for curses `wattron()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wattron()`.
 */
PROCEDURE(rx_wattron)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, attributes")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the attributes
    int attributes = get_attributes(GETSTRING(ARG(1)));
    if (attributes == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid attributes")
    }

    // Call wattron() and check for errors
    if (wattron(win, attributes) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wattron() failure")
    }
}

/**
 * @brief Turns off text attributes like bold or underline for a window
 *
 * This function is a wrapper for curses `wattroff()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wattroff()`.
 */
PROCEDURE(rx_wattroff)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, attributes")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the attributes
    int attributes = get_attributes(GETSTRING(ARG(1)));
    if (attributes == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid attributes")
    }

    // Call wattroff() and check for errors
    if (wattroff(win, attributes) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wattroff() failure")
    }
}

/**
 * @brief Set the background color of a window
 *
 * This function is a wrapper for curses `wbkgd()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wbkgd()`.
 */
PROCEDURE(rx_wbkgd)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, attributes")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the attributes
    int attributes = get_attributes(GETSTRING(ARG(1)));
    if (attributes == -1) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "invalid attributes")
    }

    // Call wbkgd() and check for errors
    wbkgd(win, attributes);
}

/**
 * @brief Clears the window
 *
 * This function is a wrapper for curses `wclear()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wclear()`.
 */
PROCEDURE(rx_wclear)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call wclear() and check for errors
    if (wclear(win) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wclear() failure")
    }
}

/**
 * @brief Clear windows to the bottom right corner
 *
 * This function is a wrapper for curses `wclrtobot()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wclrtobot()`.
 */
PROCEDURE(rx_wclrtobot)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call wclrtobot() and check for errors
    if (wclrtobot(win) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wclrtobot() failure")
    }
}

/**
 * @brief Clears the window to the end of the line
 *
 * This function is a wrapper for curses `wclrtoeol()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wclrtoeol()`.
 */
PROCEDURE(rx_wclrtoeol)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call wclrtoeol() and check for errors
    if (wclrtoeol(win) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wclrtoeol() failure")
    }
}

/**
 * @brief Get the current cursor position in a window
 *
 * This function is a wrapper for curses `wgetyx()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wgetyx()`.
 */
PROCEDURE(rx_wgetyx)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, y, x")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Get the cursor position
    int y, x;
    getyx(win, y, x);

    // Set the return values
    SETINT(ARG(1), y);
    SETINT(ARG(2), x);
}

/**
 * @brief Moves the cursor to a position in a window
 *
 * This function is a wrapper for curses `wmove()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wmove()`.
 */
PROCEDURE(rx_wmove)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 3) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, y, x")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call wmove() and check for errors
    if ( wmove(win, GETINT(ARG(1)), GETINT(ARG(2)) ) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wmove() failure")
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
 * @brief Redirects the SAY output to the screen
 *
 * This function is a crexx specific function that redirects the SAY output to the window
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 */
PROCEDURE(rx_wredirectsay)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Set the return value
    say_window = (WINDOW*)GETINT(ARG(0));
    SET_SAY_EXIT(print_to_window);
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
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Call refresh() and check for errors
    if( wrefresh(win) != OK) RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wrefresh() failure")
}

/**
 * @brief Scrolls a window up or down by a specified number of lines
 *
 * This function is a wrapper for `wscrl()`
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wscrl()`.
 */
PROCEDURE(rx_wscrl)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, n")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));

    // Check if the window pointer is valid
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call wscrl() and check for errors
    if (wscrl(win, GETINT(ARG(1))) == ERR) {
        RETURNSIGNAL(SIGNAL_FAILURE, "ncurses wscrl() failure")
    }
}

/**
 * @brief Set the timeout for keyboard input for a window
 *
 * This function is a wrapper for curses `wtimeout()`.
 *
 * @signal INVALID_ARGUMENTS if the number of arguments is incorrect.
 * @signal FAILURE if an error occurs during the execution of `wtimeout()`.
 */
PROCEDURE(rx_wtimeout)
{
    // Check for the correct number of arguments
    if( NUM_ARGS != 2) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected window, milliseconds")

    // Get the window pointer
    WINDOW* win = (WINDOW*)GETINT(ARG(0));
    if (win == NULL) {
        RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "null window")
    }

    // Call wtimeout() and check for errors
    wtimeout(win, GETINT(ARG(1)));
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
    if( NUM_ARGS != 1) RETURNSIGNAL(SIGNAL_INVALID_ARGUMENTS, "expected string")

    char* str = GETSTRING(ARG(0));
    char* buffer = malloc(strlen(str) + 1);
    if (buffer == NULL) {
        RETURNSIGNAL(SIGNAL_FAILURE, "out of memory")
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
//      C Function__,   REXX namespace & name,   Option_, Return Type_, Arguments
ADDPROC(rx_addstr,      "rxcurses.addstr",      "b",      ".void",    "string=.string");
ADDPROC(rx_attron,      "rxcurses.attron",      "b",      ".void",    "attributes=.string");
ADDPROC(rx_attroff,     "rxcurses.attroff",     "b",      ".void",    "attributes=.string");
ADDPROC(rx_bkgd,        "rxcurses.bkgd",        "b",      ".void",    "attributes=.string");
ADDPROC(rx_box,         "rxcurses.box",         "b",      ".void",    "window=.int,vertch=.int,horch=.int");
ADDPROC(rx_can_change_color, "rxcurses.can_change_color", "b", ".int", "");
ADDPROC(rx_clear,       "rxcurses.clear",       "b",      ".void",    "");
ADDPROC(rx_clrtobot,    "rxcurses.clrtobot",    "b",      ".void",    "");
ADDPROC(rx_clrtoeol,    "rxcurses.clrtoeol",    "b",      ".void",    "");
ADDPROC(rx_curs_set,    "rxcurses.curs_set",    "b",      ".void",    "visibility=.int");
ADDPROC(rx_delwin,      "rxcurses.delwin",      "b",      ".void",    "window=.int");
ADDPROC(rx_derwin,      "rxcurses.derwin",      "b",      ".int",     "window=.int,height=.int,width=.int,starty=.int,startx=.int");
ADDPROC(rx_endwin,      "rxcurses.endwin",      "b",      ".void",    "");
ADDPROC(rx_getch,       "rxcurses.getch",       "b",      ".string",  "");
ADDPROC(rx_getmaxyx,    "rxcurses.getmaxyx",    "b",      ".void",    "window=.int,expose y=.int,expose x=.int");
ADDPROC(rx_getyx,       "rxcurses.getyx",       "b",      ".void",    "window=.int,expose y=.int,expose x=.int");
ADDPROC(rx_echo,        "rxcurses.echo",        "b",      ".void",    "");
ADDPROC(rx_noecho,      "rxcurses.noecho",      "b",      ".void",    "");
ADDPROC(rx_init_color,  "rxcurses.init_color",  "b",      ".void",    "color=.string,r=.int,g=.int,b=.int");
ADDPROC(rx_init_pair,   "rxcurses.init_pair",   "b",      ".void",    "pair=.int,fg=.string,bg=.string");
ADDPROC(rx_initscr,     "rxcurses.initscr",     "b",      ".int",     "");
ADDPROC(rx_keypad,      "rxcurses.keypad",      "b",      ".void",    "window=.int,enable=.int");
ADDPROC(rx_move,        "rxcurses.move",        "b",      ".void",    "y=.int,x=.int");
ADDPROC(rx_mvaddstr,    "rxcurses.mvaddstr",    "b",      ".void",    "y=.int,x=.int,string=.string");
ADDPROC(rx_mvprintw,    "rxcurses.mvprintw",    "b",      ".void",    "y=.int,x=.int,format=.string,...=.string");
ADDPROC(rx_mvwprintw,   "rxcurses.mvwprintw",   "b",      ".void",    "window=.int,y=.int,x=.int,format=.string,...=.string");
ADDPROC(rx_mvwaddstr,   "rxcurses.mvwaddstr",   "b",      ".void",    "window=.int,y=.int,x=.int,string=.string");
ADDPROC(rx_newwin,      "rxcurses.newwin",      "b",      ".int",     "nlines=.int,ncols=.int,begin_y=.int,begin_x=.int");
ADDPROC(rx_printw,      "rxcurses.printw",      "b",      ".void",    "format=.string,...=.string");
ADDPROC(rx_redirectsay, "rxcurses.redirectsay", "b",      ".void",    "");
ADDPROC(rx_refresh,     "rxcurses.refresh",     "b",      ".void",    "");
ADDPROC(rx_scrl,        "rxcurses.scrl",        "b",      ".void",    "n=.int");
ADDPROC(rx_scroll,      "rxcurses.scroll",      "b",      ".void",    "window=.int");
ADDPROC(rx_scrollok,    "rxcurses.scrollok",    "b",      ".void",    "window=.int,enable=.int");
ADDPROC(rx_setlocale,   "rxcurses.setlocale",   "b",      ".string",  "locale=.string");
ADDPROC(rx_start_color, "rxcurses.start_color", "b",      ".void",    "");
ADDPROC(rx_timeout,     "rxcurses.timeout",     "b",      ".void",    "milliseconds=.int");
ADDPROC(rx_waddstr,     "rxcurses.waddstr",     "b",      ".void",    "window=.int,string=.string");
ADDPROC(rx_wattron,     "rxcurses.wattron",     "b",      ".void",    "window=.int,attributes=.string");
ADDPROC(rx_wattroff,    "rxcurses.wattroff",    "b",      ".void",    "window=.int,attributes=.string");
ADDPROC(rx_wbkgd,       "rxcurses.wbkgd",       "b",      ".void",    "window=.int,attributes=.string");
ADDPROC(rx_wclear,      "rxcurses.wclear",      "b",      ".void",    "window=.int");
ADDPROC(rx_wclrtobot,   "rxcurses.wclrtobot",   "b",      ".void",    "window=.int");
ADDPROC(rx_wclrtoeol,   "rxcurses.wclrtoeol",   "b",      ".void",    "window=.int");
ADDPROC(rx_wgetch,      "rxcurses.wgetch",      "b",      ".string",  "window=.int");
ADDPROC(rx_wgetyx,      "rxcurses.wgetyx",      "b",      ".void",    "window=.int,expose y=.int,expose x=.int");
ADDPROC(rx_wmove,       "rxcurses.wmove",       "b",      ".void",    "window=.int,y=.int,x=.int");
ADDPROC(rx_wprintw,     "rxcurses.wprintw",     "b",      ".void",    "window=.int,format=.string,...=.string");
ADDPROC(rx_wredirectsay, "rxcurses.wredirectsay", "b",    ".void",    "window=.int");
ADDPROC(rx_wrefresh,    "rxcurses.wrefresh",    "b",      ".void",    "window=.int");
ADDPROC(rx_wscrl,       "rxcurses.wscrl",       "b",      ".void",    "window=.int,n=.int");
ADDPROC(rx_wtimeout,    "rxcurses.wtimeout",    "b",      ".void",    "window=.int,milliseconds=.int");
ADDPROC(rx_unescape,    "rxcurses.unescape",    "b",      ".string",  "string=.string");
ENDLOADFUNCS
