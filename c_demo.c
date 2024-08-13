//
// Created by Adrian Sutherland on 12/08/2024.
//
// This is a simple curses demo program that demonstrates the use of the curses library.
// The program creates a window and displays a message in the center of the window.
// The program then waits for a key press before exiting.
//
// To compile and run this program:
// gcc -o c_demo c_demo.c -lncurses
// ./c_demo
//
// To exit the program, press the x key
//

#include <ncurses.h>
#include <locale.h>
#include <string.h>

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
            strcpy(buffer, "KEY_F1"); return 1;
        case KEY_F(2):
            strcpy(buffer, "KEY_F2"); return 1;
        case KEY_F(3):
            strcpy(buffer, "KEY_F3"); return 1;
        case KEY_F(4):
            strcpy(buffer, "KEY_F4"); return 1;
        case KEY_F(5):
            strcpy(buffer, "KEY_F5"); return 1;
        case KEY_F(6):
            strcpy(buffer, "KEY_F6"); return 1;
        case KEY_F(7):
            strcpy(buffer, "KEY_F7"); return 1;
        case KEY_F(8):
            strcpy(buffer, "KEY_F8"); return 1;
        case KEY_F(9):
            strcpy(buffer, "KEY_F9"); return 1;
        case KEY_F(10):
            strcpy(buffer, "KEY_F10"); return 1;
        case KEY_F(11):
            strcpy(buffer, "KEY_F11"); return 1;
        case KEY_F(12):
            strcpy(buffer, "KEY_F12"); return 1;
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




int main() {
/*
    initscr();            // Start curses mode
    printw("Hello, World!"); // Print Hello World
    refresh();            // Print it on the real screen
    getch();              // Wait for user input
    endwin();             // End curses mode

    return 0;
*/
    // Initialize the screen
    setlocale(LC_ALL, "");  // Set the locale to UTF-8 based on the environment
    initscr();              // Initialize curses mode

    // Get the screen dimensions
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create a new window
    WINDOW* boxWin = newwin(10, 50, yMax / 2, xMax / 2 - 25);
    // Draw a border around the window
    box(boxWin, 0, 0);
    wrefresh(boxWin);

    // Create a subwindow with a margin of 1 character inside the main window
    WINDOW *newWin = derwin(boxWin, 8, 48, 1, 1);
    keypad(newWin, TRUE);   // Enable special keys like arrow keys

    // Enable scrolling
    scrollok(newWin, TRUE);

    // Echo off for the window
    noecho();

    // Display a message in the window
    char ch[15];
    int rc;
    while (1) {
        wprintw(newWin, "Hello, Rène! (press x to exit)\n");

        // Refresh the window
        wrefresh(newWin);

        // Wait for a key press
        rc = getch_utf8(newWin, ch);
        if (rc == -1) {
            wprintw(newWin, "Error reading key\n");
            break;
        }
        if (rc == 1) {
            wprintw(newWin, "Special key pressed: %s\n", ch);
            continue;
        }

        if (strcmp(ch, "x") == 0) break;

        // Display the key pressed in integer hexadecimal format
        wprintw(newWin, "Key pressed: %s\n", ch);
    }

    // Clean up
    delwin(newWin);
    delwin(boxWin);
    endwin();

    return 0;
}
