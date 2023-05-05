#include <cstdio>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

class KbhitGetch {
  public:
    char getch(); 
    int kbhit(void);
};
