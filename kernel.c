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
void printString(char*,int);
void printLogo();
void readString(char* buffer);
void readInt(int* n);
void writeInt(int n, int d);
int mod(int a, int b);
int div(int a, int b);
void madLibs();

void main()
{
   char string[81];
   int test = 0;
   makeInterrupt21();
   printLogo();
   /* printString("Hello world.\r\n\0", 1); */
   interrupt(33, 0, "Hola mondo.\r\n\0", 0, 0);
   madLibs();
   while(1);
}

void printString(char* c, int d)
{
  if (d == 0) {
    while (*c != '\0') {
      char al = *c;
      int ah = 14;
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
  char string[9];
  int i = 0;
  char c;

  do {
    c = interrupt(22, 0, 0, 0, 0);

    /* 0x8 = Backspace; so if (NOT backspace) */
    if (c != 0x8 && c != '\n' && c != '\r') {
      buffer[count++] = c;
    }

    /* Print the typed character */
    interrupt(16, 14*256 + c, 0, 0, 0);

    /* This time checking if c is a backspace */
    if (c == 0x8) {
      if (count - 1 >= 0) {
        --count; /* decrement */
      }
    }
  } while (c != 0xD && count < 80);

  buffer[count] = '\0';
  printString("\r\n\0", 0);
  return;
}

void readInt(int* n) {
  char input[10];
  int i = 0;
  *n = 0;
  readString(input);

  while (input[i] != '\0') {
    *n = (*n) * 10 + input[i] - '0';
    ++i;
  }
}

void writeInt(int n, int d) {
  char output[6], digits;
  int i;

  if (n == 0) {
    output[0] = '0';
    output[1] = '\0';
  } else {
    int len = 0;
    for (; n > 0; ++len) {
      output[len] = mod(n, 10) + '0';
      n = div(n, 10);
    }

    output[len] = '\0';

    for (i = 0; i < div(len, 2); ++i) {
      digits = output[i];
      output[i] = output[len - i - 1];
      output[len - i - 1] = digits;
    }
  }
  printString(output, d);
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
    q++;
  }
  return (q - 1);
}

void madLibs() {
  char food[25], adjective[25], color[25], animal[25];
  int temp;
  interrupt(33,0,"\r\nWelcome to the Mad Libs kernel.\r\n\0",0,0);
  interrupt(33,0,"Enter a food: \0",0,0);
  interrupt(33,1,food,0,0);
  temp = 0;
  while ((temp < 100) || (temp > 120)) {
     interrupt(33,0,"Enter a number between 100 and 120: \0",0,0);
     interrupt(33,14,&temp,0,0);
  }
  interrupt(33,0,"Enter an adjective: \0",0,0);
  interrupt(33,1,adjective,0,0);
  interrupt(33,0,"Enter a color: \0",0,0);
  interrupt(33,1,color,0,0);
  interrupt(33,0,"Enter an animal: \0",0,0);
  interrupt(33,1,animal,0,0);
  interrupt(33,0,"Your note is on the printer, go get it.\r\n\0",0,0);
  interrupt(33,0,"Dear Professor O\'Neil,\r\n\0",1,0);
  interrupt(33,0,"\r\nI am so sorry that I am unable to turn in my program at this time.\r\n\0",1,0);
  interrupt(33,0,"First, I ate a rotten \0",1,0);
  interrupt(33,0,food,1,0);
  interrupt(33,0,", which made me turn \0",1,0);
  interrupt(33,0,color,1,0);
  interrupt(33,0," and extremely ill.\r\n\0",1,0);
  interrupt(33,0,"I came down with a fever of \0",1,0);
  interrupt(33,13,temp,1,0);
  interrupt(33,0,". Next my \0",1,0);
  interrupt(33,0,adjective,1,0);
  interrupt(33,0," pet \0",1,0);
  interrupt(33,0,animal,1,0);
  interrupt(33,0," must have\r\nsmelled the remains of the \0",1,0);
  interrupt(33,0,food,1,0);
  interrupt(33,0," on my computer, because he ate it. I am\r\n\0",1,0);
  interrupt(33,0,"currently rewriting the program and hope you will accept it late.\r\n\0",1,0);
  interrupt(33,0,"\r\nSincerely,\r\n\0",1,0);
  interrupt(33,0,"(your name here)\r\n\0",1,0);
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*   return;  */
   switch(ax) {
      case 0: printString(bx,cx); break;
      case 1: readString(bx); break;
      case 13: writeInt(bx, cx); break;
      case 14: readInt(bx); break;
/*      case 1: case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 13: case 14: case 15: */
      default: printString("General BlackDOS error.\r\n\0");
    }
}
