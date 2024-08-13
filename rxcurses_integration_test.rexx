/* rxcurses integration test program                                         */
/* This program is used to test the integration of the rxcurses library with */
/* cRexx. It only calls initscr() as this shows the integrartion and can     */
/* be automated                                                              */
options levelb  /* This is a rexx level b program */
import rxcurses

say "Curses integration test program"

/* Initialise the curses library */
screen = initscr()
if screen = 0 then do
    say "Error initialising ncurses"
    exit 1
end

return 0
