/* Here's a simple example of combining SDL and PDCurses functionality.
   The top portion of the window is devoted to SDL, with a four-line
   (assuming the default 8x16 font) stdscr at the bottom.
*/

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define INTENTIONALLY_UNUSED_PARAMETER( param) (void)(param)

#include "pdcsdl.h"

int main(int argc, char **argv)
{
    char inp[60];
    int i, j;
    const unsigned seed = (unsigned)time((time_t *)0);

    srand(seed);

    /* Initialize SDL */

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(1);

#ifdef PDC_WIDE
    if( argc > 1)
    {
         pdc_sdl_render_mode = atoi( argv[1]);
    }
#else
    INTENTIONALLY_UNUSED_PARAMETER( argc);
    INTENTIONALLY_UNUSED_PARAMETER( argv);
#endif

    atexit(SDL_Quit);

    pdc_window = SDL_CreateWindow("PDCurses for SDL", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    pdc_screen = SDL_GetWindowSurface(pdc_window);

    /* Initialize PDCurses */

    pdc_yoffset = 416;  /* 480 - 4 * 16 */

    initscr();
    start_color();
    scrollok(stdscr, TRUE);

    PDC_set_title("PDCurses for SDL");

    /* Do some SDL stuff */

    for (i = 640, j = 416; j; i -= 2, j -= 2)
    {
        SDL_Rect dest;

        dest.x = (640 - i) / 2;
        dest.y = (416 - j) / 2;
        dest.w = i;
        dest.h = j;

        SDL_FillRect(pdc_screen, &dest,
                     SDL_MapRGB(pdc_screen->format, rand() % 256,
                                rand() % 256, rand() % 256));
    }

    SDL_UpdateWindowSurface(pdc_window);

    /* Do some curses stuff */

    init_pair(1, COLOR_WHITE + 8, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));

    addstr("This is a demo of ");
    attron(A_UNDERLINE);
    addstr("PDCurses for SDL");
    attroff(A_UNDERLINE);
    addstr(".\nYour comments here: ");
    getnstr(inp, 59);
    addstr("Press any key to exit.");

    getch();
    endwin();

    return 0;
}
