#include <cstdio>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

class KbhitGetch {
  public:
    char getch(); /*le um caracter da entrada padrão sem o bloqueio de
                     entrada(nao necessita apertar enter) */
    int kbhit(void);
};
