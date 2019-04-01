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
void readSector(char* buffer, int count);
void writeSector(char* buffer, int count);
void clearScreen(int bgColor, int fgColor);
void readString(char* buffer);
void readInt(int* n);
void writeInt(int n, int d);
int mod(int a, int b);
int div(int a, int b);
int findFirstFreeSector(char* map);
void readFile(int, int, int);
void deleteFile(int);
void writeFile(int, int, int);
void error(int);
/* void unicornLogo(); */
void runProgram(char*, int);
void stop();


void main()
{
   char buffer[12288];
   int size;
   makeInterrupt21();
   interrupt(33, 2, buffer, 258, 0);
   interrupt(33, 12, buffer[0] + 1, buffer[1]+1, 0);
   printLogo();

   interrupt(33, 4, "Stenv\0", 2, 0);
   interrupt(33, 0, "Error if this executes.\r\n\0", 0, 0);
   
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

/* 
void unicornLogo() {
  printString("                     /\r\n\0", 0);
  printString("               ,.. /\r\n\0", 0);
  printString("             ,'   ';\r\n\0", 0);
  printString("  ,,.__    _,' /';  .\r\n\0", 0);
  printString(" :','  ~~~~    '. '~\r\n\0", 0);
  printString(":' (   )         )::,\r\n\0", 0);
  printString("'. '. .=----=..-~  .;'\r\n\0", 0);
  printString(" '  ;'  ::   ':.  '\"\r\n\0", 0);
  printString("   (:   ':    ;)\r\n\0", 0);
  printString("    \\\\   '\"  ./\r\n\0", 0);
  printString("     '\"      '\"\r\n\0", 0);
  printString(" UnicornOS v. 1.01, c. 2018. Based on a project by M. Black. \r\n\0",0);
  printString(" Author(s): Kevin Klions.\r\n\r\n\0",0);
}
*/ 

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

void readSector(char* bx, int sector) {
  int ah, al, dl;
  int relSecNo, headNo, trackNo;
  int ax, cx, dx;
  ah = 2;
  al = 1;
  dl = 0;

  relSecNo = mod(sector, 18) + 1;
  headNo = mod(div(sector, 18), 2);
  trackNo = div(sector, 36);

  ax = ah * 256 + al;
  cx = trackNo * 256 + relSecNo;
  dx = headNo * 256 + dl;

  interrupt(19, ax, bx, cx, dx);
}

void writeSector(char* buffer, int sector) {
  int ah, al, dl;
  int relSecNo, headNo, trackNo;
  int ax, cx, dx;
  ah = 3;
  al = 1;
  trackNo = div(sector, 36);
  relSecNo = mod(sector, 18) + 1;
  headNo = mod(div(sector, 18), 2);
  dl = 0;

  ax = ah * 256 + al;
  cx = trackNo * 256 + relSecNo;
  dx = headNo * 256 + dl;

  interrupt(19, ax, buffer, cx, dx);
}

void clearScreen(int bgColor, int fgColor) {
  int clearCount = 24;
  int i = 0;

  for (i = 0; i < 24; ++i) {
    printString("\r\n\0", 0);
  }
  interrupt(16, 512, 0, 0, 0);

  if (bgColor > 0 && fgColor > 0) {
    interrupt(16, 1536, 4096 * (bgColor - 1) + 256 * (fgColor - 1), 0, 6223);
  }
}

/* How is this not in this version of C */
void memcopy(char* source, char* destination, int size) {
  int i = 0;
  while (i < size) {
    destination[i] = source[i];
    ++i;
  }
}

int compareFilenames(char* seeking, char* fromDisk) {
  int i = 0;
  // Fileanmes shouldn't be null terminated, but if there is one, then stop? i guess?
  while (seeking[i] != '\0') {
    if (i >= 8) {
      // filenames are limited to 8 characters
      return 0;
    }
    if (seeking[i] != fromDisk[i]) {
      // if a character isnt the same, return 'false'
      return 0;
    }
    ++i;
  }
  // if we get here, then the filenames should be the same
  return 1;
}

void readFile(char* fname, char* buffer, int* size) {
  char directory[512];
  char filename[8];
  char* currentEntry;
  char* currentEntryEnd;
  char* currentSector;
  int filenamesSame = 0;
  int sectorCount = 0;
  *size = 0;
  
  readSector(directory, 257);
  currentEntry = directory;

  while (currentEntry < directory + 512) {
    currentEntryEnd = currentEntry + 32;
    // copy the current entry's filename to the temp filename
    memcopy(currentEntry, filename, 8);
    filenamesSame = compareFilenames(fname, filename);    

    if (filenamesSame == 1) {
      currentSector = currentEntry + 8; // accounting for the filename
      while (currentSector < currentEntryEnd) {
        if (*currentSector != 0) { // cannot use sector 0
          readSector(buffer, *currentSector);
          buffer += 512;
          *size += 1;
          sectorCount++;
        }
        currentSector++;
      }
      return;
    } else {
      currentEntry = currentEntry + 32;
    }
  }
  interrupt(33, 15, 0, 0, 0);
  return;
}

/* Returns index of the first free sector in the map */
int findFirstFreeSector(char* map) {
  int i = 0;
  while (i < 512) {
    if (map[i] == 0) {
      return i;
    }
    ++i;
  }
  /* Error code 2, no disk space */
  interrupt(33, 15, 2, 0, 0);
}

void writeFile(char* name, char* buffer, int numberOfSectors) {
  char directory[512]; /* Sector 257 */
  char map[512]; /* Sector 256 */
  char chunk[512];
  char seekFilename[8];
  char* currentEntry;
  char* currentEntryEnd;
  char* currentSector;
  char* freeDirectory;
  int i = 0;
  int j = 0;
  int freeSectorIndex;

  readSector(directory, 257);
  readSector(map, 256);

  currentEntry = directory;
  currentEntryEnd = currentEntry + 32;

  while (currentEntry < directory + 512) {
    memcopy(currentEntry, seekFilename, 8);

    if (compareFilenames(name, seekFilename) == 1) {
      interrupt(33, 15, 1, 0, 0);
      return;
    } else if (*currentEntry == 0) {
      freeDirectory = currentEntry;
      break;
    }
    currentEntry += 32;
  }

  if (currentEntry >= directory + 512) {
    interrupt(33, 15, 2, 0, 0);
    return;
    /* if we get here, then there is no space */
  }

  /* copy the name into the open directory */
  while (name[i] != '\0') {
    freeDirectory[i] = name[i];
    ++i;
  }

  while (i < 8) {
    freeDirectory[i] = 0;
    ++i;
  }

  /* Find a free sector by searching through the map for a 0 */
  i = 0;
  currentSector = freeDirectory + 8;
  currentEntryEnd = freeDirectory + 32;
  freeSectorIndex = findFirstFreeSector(map);
  while (i < numberOfSectors && currentSector < currentEntryEnd) {
    map[freeSectorIndex] = 255;
    *currentSector = freeSectorIndex;
    ++currentSector;
    ++i;
    
    j = 0;
    while (j < 512) {
      chunk[j] = *buffer;
      ++j;
      ++buffer;
    }

    writeSector(chunk, freeSectorIndex);
  }

  while (currentSector < currentEntryEnd) {
    *currentSector = 0;
    ++currentSector;
  }

  writeSector(directory, 257);
  writeSector(map, 256);
}

void deleteFile(char* name) {
  char directory[512], map[512], testFilename[8];
  char* currentEntry, * currentEntryEnd, * currentSector, * filename;
  int i = 0;
  char deletedFilename[8];

  readSector(directory, 257);
  readSector(map, 256);

  currentEntry = directory;

  while (currentEntry < directory + 512) {
    memcopy(currentEntry, testFilename, 8);

    if (compareFilenames(name, testFilename) == 1) {
      currentEntry[0] = 0;
      currentSector = currentEntry + 8;

      while (*currentSector != 0 && currentSector < currentEntry + 32) {
        map[*currentSector] = 0;
        ++currentSector;
      }

      writeSector(directory, 257);
      writeSector(map, 256);
      return;
    } else {
      currentEntry += 32;
    }
  }

  if (currentEntry >= directory + 512) {
    error(0);
  }
}

void runProgram(char* name, int segment) {
  char buffer[12288];
  int segmentLocation = 0;
  int offset = 0;
  int numberOfSectors = 0;

  if (segment < 2 || segment > 9) {
    printString("Invalid Segment\r\n\0");
    stop();
  }
  
  /* readFile(name, buffer, numberOfSectors) */ 
  interrupt(33, 3, name, buffer, &numberOfSectors, 0);

  segmentLocation = segment * 4096;

  while (offset < 12288) {
    putInMemory(segmentLocation, offset, buffer[offset]);
    ++offset;
  }

  launchProgram(segmentLocation);  
}

void stop() {
  while(1);
}

void error(int bx) {
  switch (bx) {
    case 0: interrupt(33, 0, "File not found.\n\r\0", 0, 0); stop(); break;
    case 1: interrupt(33, 0, "Bad file name.\r\n\0", 0, 0); stop(); break;
    case 2: interrupt(33, 0, "Disk full.\r\n\0", 0, 0); stop(); break;
    default: interrupt(33, 0, "General Error\r\n\0", 0, 0); stop(); break;
  }
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   switch(ax) {
      case 0: printString(bx,cx); break;
      case 1: readString(bx); break;
      case 2: readSector(bx, cx); break;
      case 3: readFile(bx, cx, dx); break;
      case 4: runProgram(bx, cx); break;
      case 5: stop(); break;
      case 6: writeSector(bx, cx); break;
      case 7: deleteFile(bx); break;
      case 8: writeFile(bx, cx, dx); break;
      case 12: clearScreen(bx, cx); break;
      case 13: writeInt(bx, cx); break;
      case 14: readInt(bx); break;
      case 15: error(bx); break;
      default: printString("General BlackDOS error.\r\n\0");
    }
}
