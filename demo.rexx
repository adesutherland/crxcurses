/* cRexx rxcurses demo - A file viewer */
options levelb  /* This is a rexx level b program */
import rxfnsb
import rxcurses

/* Main program */
main: procedure = .int expose screen header footer log filelist contents files fileline
    say "cRexx - File Viewer Demo. Initialising ncurses ..."

    /* Initialize the curses library */
    call setlocale "" /* Set the locale to the default / utf-8 */
    screen = initscr()
    if screen = 0 then do
        say "Error initializing ncurses" /* We should never get here as initscr() will exit on error */
        exit 1
    end

    /* Window variables */
    header = 0
    footer = 0
    log = 0
    filelist = 0
    contents = 0

    /* Initialize colors */
    call start_color
    if can_change_color() then do
        call init_color "WHITE", 1000, 1000, 1000
    end
    call init_pair 1, "BLUE", "WHITE"  /* Blue text on white background */
    call init_pair 2, "GREEN", "WHITE"
    call init_pair 3, "WHITE", "BLUE"
    call init_pair 4, "GREEN", "BLACK"

    call bkgd "COLOR_PAIR(1)"
    call refresh

    files = .string[]
    address cmd "ls" output files
    if rc <> 0 then do
        say "List Files Error - RC = "rc "when doing : ls"
        call endwin
        exit 1
    end
    fileline = 1

    call setup_screen

    call noecho
    call curs_set 0
    call keypad screen, 1
    call wtimeout screen, 1000

    call print_log "Starting"

    /* Main loop to handle user input */
    do forever
        key = wgetch(screen)
        if key = "[RESIZE]" then do
            call setup_screen
            iterate
        end
        if key = "[F3]" then leave
        if key = "x" then leave
        if key = "[ENTER]" then do
            call read_file files.fileline
            call draw_filecontents
        end
        if key = "[UP]" then do
            fileline = fileline - 1
            if fileline < 1 then fileline = 1
            call draw_filelist
        end
        if key = "[DOWN]" then do
            fileline = fileline + 1
            if fileline > files.0 then fileline = files.0
            call draw_filelist
        end
        call print_date
    end

    /* Clean up */
    if header <> 0 then call delwin header
    if footer <> 0 then call delwin footer
    if log <> 0 then call delwin log
    if filelist <> 0 then call delwin filelist
    if contents <> 0 then call delwin contents
    call endwin

    return 0


setup_screen: procedure expose header footer log filelist contents screen date_col logs content_width ,
                               content_length

    content_width = .int
    content_length = .int

    /* Clean up - in case of screen resize */
    if header <> 0 then call delwin header
    if footer <> 0 then call delwin footer
    if log <> 0 then call delwin log
    if filelist <> 0 then call delwin filelist
    if contents <> 0 then call delwin contents

    call clear
    call refresh

    /* Get screen size */
    rows = 0
    cols = 0
    call getmaxyx screen, rows, cols

    /* Create a 1 line header screen */
    header = newwin(1, cols, 0, 0)
    if header = 0 then do
        call endwin
        say "Error creating header window"
        exit 1
    end
    call wbkgd header, "COLOR_PAIR(3)"
    call wattron header, "BOLD"
    call waddstr header, " cRexx File Viewer"
    call wattroff header, "BOLD"
    call wrefresh header
    date_col = cols - 22
    if date_col < 0 then date_col = 0

    /* Create a 1 line footer screen */
    footer = newwin(1, cols, rows - 1, 0)
    if footer = 0 then do
        call endwin
        say "Error creating footer window"
        exit 1
    end
    call wbkgd footer, "COLOR_PAIR(3)"
    call wattron footer, "BOLD"
    call wprintw footer, center("F3:EXIT      x:EXIT      ENTER:OPEN", cols)
    call wattroff footer, "BOLD"
    call wrefresh footer

    /* Create a log window - bottom 5 lines (or don't bother creating it) */
    log = newwin(5, cols, rows - 6, 0)
    if log = 0 then do
        call endwin
        say "Error creating log window"
        exit 1
    end
    call wbkgd log, "COLOR_PAIR(4)"
    call scrollok log, 1
    /* Repopulate the log window */
    format = unescape("> %s\n")
    do i = 1 to logs.0
        call wprintw log, format, logs.i
    end
    call wrefresh log

    /* Create a file list window - left 20 columns */
    filelist = newwin(rows - 7, 35, 1, 0)
    if filelist = 0 then do
        call endwin
        say "Error creating file list window"
        exit 1
    end
    call wbkgd filelist, "COLOR_PAIR(1)"
    call scrollok filelist, 1
    /* Repopulate the files window */
    call draw_filelist

    /* Create a contents window - right remaining columns */
    contents = newwin(rows - 7, cols - 36, 1, 36)
    if contents = 0 then do
        call endwin
        say "Error creating contents window"
        exit 1
    end
    call wbkgd contents, "COLOR_PAIR(2)"
    content_width = cols - 36 - 7
    content_length = rows - 7
    call draw_filecontents

    return

print_date: procedure expose header date_col
    if header = 0 then return
    if date_col = 0 then return
    call wmove header, 0, date_col
    call wprintw header, " %s", right(date() time(), 20)
    call wrefresh header
    return

print_log: procedure expose log logs
    arg text = .string
    if log = 0 then return
    logs = .string[]

    logs[logs.0 + 1] = text

    format = unescape("> %s\n")

    call wprintw log, format, text
    call wrefresh log
    return

draw_filelist: procedure expose filelist files fileline
    if filelist = 0 then return
    call wclear filelist

    /* Repopulate the files window */
    format = unescape("%s%s\n")
    do i = 1 to files.0
        if i = fileline then do
            call wattron filelist, "BOLD"
            call wprintw filelist, format, ">", files.i
            call wattroff filelist, "BOLD"
        end
        else call wprintw filelist, format, " ", files.i
    end
    call wrefresh filelist
    return

read_file: procedure = .void expose filecontents filelength
    arg filename = .string
    filecontents = .string[]
    filelength = .int

    /* Truncate the filecontents array */
    /* CLEAR filecontents */ /* This is not implemented yet */

    do i = 1 to 100 while lines(filename)
        filecontents.i = linein(filename)
    end
    call lineout filename

    filelength = i - 1
    if filelength < 1 then do
        filecontents.1 = "No data in file"
        filelength = 1
    end

    call print_log "File read:" filename "with" filelength "lines"
    return

draw_filecontents: procedure expose contents filecontents content_width content_length filelength
    filecontents = .string[]
    content_width = .int
    content_length = .int
    if contents = 0 then return

    rows = filelength
    if rows > content_length then rows = content_length

    call wclear contents

    /* Repopulate the contents window */
    format = unescape("%s %s\n")
    do i = 1 to rows
        call wprintw contents, format, right(i,5,"0"), left(filecontents.i, content_width)
    end
    call wrefresh contents
    return
