/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:______Kevin Klions___________________ Date:____2/1/19___        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.01, Spring 2018.             */

void handleInterrupt21(int,int,int,int);
/* void printString(char*,int); */
void printLogo();
void readString(char* buffer);
void readInt(int* n);
void writeInt(int n);
int mod(int a, int b);
int div(int a, int b);

void main()
{
   makeInterrupt21();
   printLogo();
   /* printString("Hello world.\r\n\0", 1); */
   interrupt(33,0,"Hola mondo.\r\n\0",0,0);
   readString();
   while(1);
}

void printString(char* c, int d)
{
  if (d == 0) {
    while (*c != '\0') {
      char al = *c;
      char ah = 14;
      int ax = ah*256 + al;
      interrupt(16, ax, 0, 0, 0);
      ++c;
    }
  } else if (d == 1) {
    while (*c != '\0') {
      interrupt(23, *c, 0, 0, 0);
      ++c;
    }
  }
  return;
}

void printLogo()
{
   printString("       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0);
   printString("      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0);
   printString("     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0);
   printString("    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0);
   printString("   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0);
   printString("._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0);
   printString(" BlackDOS2020 v. 1.01, c. 2018. Based on a project by M. Black. \r\n\0",0);
   printString(" Author(s): Kevin Klions.\r\n\r\n\0",0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

void readString(char* buffer) {
  int size = 80;
  int count = 0;
  char c;

  printString("\n\r\0");

  do {
    c = interrupt(22, 0, 0, 0, 0);

    /* 0x8 = Backspace; so if (NOT backspace) */
    if (c != 0x8) {
      buffer[count] = c;
    }

    /* Print the typed character */
    interrupt(16, 14*256 + c, 0, 0, 0);

    /* This time checking if c is a backspace */
    if (c == 0x8) {
      if (count - 1 >= 0) {
        --count; /* decrement */
      }
    } else {
      count++;
    }
  } while (c != 0xD && count < 80);

  buffer[count] = '\0';
  printString("\n\r\0", 0);
  return;
}

void readInt(int* buffer) {
  char integer[10];
  readString(integer);

  int i;
  int n = 0;
  for (i = 0; i < 10; ++i) {
      int temp = integer[i] - '0';
      n = n*10 + temp;
  }

  buffer = n;
}

void writeInt(int n) {
  char string[9];
  if (n < 0) {
    string[0] = '-';
    n = n * -1;
  }

  int i = 0;
  while (n != 0) {
    string[i++] = (char) ((mod(n, 10)) + '0');
    n = div(n, 10);
  }

  string[i++] = '\r';
  string[i++] = '\n';

}

int mod(int a, int b) {
  int x = a;
  while (x >= b) {
    x = x - b;
  }
  return x;
}

int div(int a, int b) {
  int q = 0;
  while (q * b <= a) {
    q++
  }
  return (q - 1);
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*   return;  */
   switch(ax) {
      case 0: printString(bx,cx); break;
/*      case 1: case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 13: case 14: case 15: */
      default: printString("General BlackDOS error.\r\n\0");
    }
}
