//======================================================================
//
// Test program to test the infrared sensors (and motors) of the
// 4tronix initio robot car. One can run this program within an
// ssh session.
//
// Compilation: 
// gcc -o line_follower -Wall -Werror -lcurses -lwiringPi -lpthread -linitio line_follower.c
//
//======================================================================

#include <stdlib.h>
#include <initio.h>
#include <curses.h>

//======================================================================
// line_follower():
// Simple program to test infrared line sensors:
// Drive along a black line. The black line is bordered on both sides
// with a white line to ensure contrast for the line sensors.
//======================================================================
void line_follower(int argc, char *argv[]) 
{
  int ch = 0;
  int irL,irR;	// status of infrared sensors
  int lfL,lfR;	// status of line sensors

  // initio_DriveForward (... ); // todo: Initially, try to drive straight forward

  while (ch != 'q') {
    mvprintw(1, 1,"%s: Press 'q' to end program", argv[0]);

    irL = initio_IrLeft();
    irR = initio_IrRight();
    lfL = initio_IrLineLeft(); // todo: replace by read left line sensor
    lfR = initio_IrLineRight(); // todo: replace by read right line sensor

    if (irL != 0 || irR != 0) {
      mvprintw(3, 1,"Action 1: Stop (IR sensors: %d, %d)     ", irL, irR);
      initio_DriveForward (0); // Stop
    }
    // no obstacle ahead, so focus on line following
    else if (lfL && lfR) { 
      mvprintw(3, 1,"Action 2: Straight (Line sensors: %d, %d)    ", lfL, lfR);
      // todo: move straight forward
      initio_DriveForward(70);
    }
    else if (lfL && !lfR) {
      // car is too much on the right
      mvprintw(3, 1,"Action 3: Spin left (Line sensors: %d, %d)    ", lfL, lfR);
      // todo: turn left
      initio_SpinLeft(100);
    }
    else if ( lfR && !lfL) {
      // car is too much on the left
      mvprintw(3, 1,"Action 4: Spin right (Line sensors: %d, %d)    ", lfL, lfR);
      // todo: turn right
      initio_SpinRight(100);
    }
    else {
      mvprintw(3, 1,"Lost my line (Line sensors: %d, %d)        ", lfL, lfR);
      // todo: Stop
      initio_DriveForward(0);

      initio_SpinRight(80); //search line if lost clockwise direction
      initio_DriveReverse(50);
    }

    ch = getch();
    if (ch != ERR)
      mvprintw(2, 1,"Key code: '%c' (%d)", ch, ch);
    refresh();  // curses
  } // while

  return;
}


//======================================================================
// main(): initialisation of libraries, etc
//======================================================================
int main (int argc, char *argv[])
{
  WINDOW *mainwin = initscr();  // curses: init screen
  noecho ();                    // curses: prevent the key being echoed
  cbreak();                     // curses: disable line buffering 
  nodelay(mainwin, TRUE);       // curses: set getch() as non-blocking 
  keypad (mainwin, TRUE);       // curses: enable detection of cursor and other keys

  initio_Init (); // initio: init the library

  line_follower(argc, argv);

  initio_Cleanup ();  // initio: cleanup the library (reset robot car)
  endwin();           // curses: cleanup the library
  return EXIT_SUCCESS;
}

