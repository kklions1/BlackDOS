#include "blackdos.h"

void parseCommand(char*);
int strCompare(char*, char*);
void strSplitter(char*, char*, char*, char);
int findInString(char*, char);
void displayHelp();
void clearScreen(char*);
void clearBuffer(char*, int);

void main() {
  char config[512];
  char command[128];

  /* Read the config file and clear the screen */
  interrupt(33, 2, config, 258, 0);
  //  interrupt(33, 12, config[0] + 1, config[1]+1, 0);

  while(1) {
    clearBuffer(command, 128);
    PRINTS("^(~(oo)~)^ > \0"); 
    SCANS(command);
    PRINTS("\r\n\0");
    parseCommand(command, config);
  }
}

int strCompare(char* arg1, char* arg2) {
  int i = 0;
  
  while (arg1[i] != '\0') {
    if (arg1[i] != arg2[i]) {
      return 0;
    }
    ++i;
  }

  return 1;
}

/* Splits the original string into two separate strings, arg1 and arg2, on a delimiter character
   then adds a null terminator to arg1 and arg2 */ 
void strSplitter(char* original, char* arg1, char* arg2, char delim) {
  int i; // Index of the delimiter character
  int j = 0; // Position in arg1
  int k = 0; // Position in arg2
  
  i = findInString(original, delim);
  if (i == -1) {
    while (original[j] != '\0') {
      arg1[j] = original[j];
      ++j;
    }
    arg1[j] = '\0';
    return;
  } else {
    while (j < i) {
      arg1[j] = original[j];
      ++j;
    }
    arg1[j] = '\0'; // Null terminate the string after the loop
    ++j;

    while (original[j] != '\0') {
      arg2[k] = original[j];
      ++k;
      ++j;
    }
    arg2[k] = '\0'; 
  }
}

/* Returns the index of the first occurence of the target character in the string */ 
int findInString(char* string, char target) {
  int i = 0;

  while (string[i] != '\0') {
    if (string[i] == target) {
      return i;
    } else {
      ++i;
    }
  }
  return -1;
}

void clearScreen(char* config) {
  interrupt(33, 12, config[0] + 1, config[1] + 1, 0);
}

void parseCommand(char* command, char* config) {
  /** arg1 is basically just the command, and arg2 is the arguments to that command
    * if the command doesn't take arguments, we currently just execute that command without caring if there
    * are arguments or not 
    */
  char arg1[64];
  char arg2[64];

  // For the commands that have two arguments of their own, we will need to use the string splitter again
  char subArg1[64];
  char subArg2[64];

  char directory[512];
  char map[512];
  
  // For Testing
  char testCommand[128];

  char buffer[12288];
  int size;
  
  strSplitter(command, arg1, arg2, ' ');
  clearBuffer(buffer, 12288);
  
  if (strCompare(arg1, "boot\0")) {
    // Reboot
    interrupt(33, 11, 0, 0, 0, 0);
  } else if (strCompare(arg1, "clrs\0")) {
    // Clear screen
    clearScreen(config);
  } else if (strCompare(arg1, "copy\0")) {
    PRINTS("This breaks everything.\r\n\0");
  } else if (strCompare(arg1, "ddir\0")) {
    /*    interrupt(33, 2, directory, 257, 0);
    interrupt(33, 2, map, 256, 0);

    displayDirectory(directory);
    */ 
  } else if (strCompare(arg1, "echo\0")) {
    interrupt(33, 0, arg2, 0, 0);
    PRINTS("\r\n\0");
  } else if (strCompare(arg1, "exec\0")) {
    interrupt(33, 4, arg2, 4, 0);
    PRINTS("\r\n\0");

  } else if (strCompare(arg1, "help\0")) {
    displayHelp(buffer, config);
    PRINTS("\r\n\0");
  } else if (strCompare(arg1, "prnt\0")) {
    interrupt(33, 3, arg2, buffer, &size);
    interrupt(33, 0, buffer, 1, 0);
    PRINTS("\r\n\0");
    
  } else if (strCompare(arg1, "remv\0")) {
    interrupt(33, 7, arg2, 0, 0);
    PRINTS("\r\n\0");
    
  } else if (strCompare(arg1, "senv\0")) {
    interrupt(33, 4, "Stenv\0", 4, 0);
    PRINTS("\r\n\0");
    
  } else if (strCompare(arg1, "show\0")) {
    interrupt(33, 3, arg2, buffer, size);
    interrupt(33, 0, buffer, 0, 0);
    PRINTS("\r\n\0");
    
  } else if (strCompare(arg1, "twet\0")) {
    PRINTS("Enter a line of text: \0");
    SCANS(buffer);
    interrupt(33, 8, arg2, buffer, 1);
    PRINTS("\r\n\0");
    
  } else {
    PRINTS("Command '\0");
    PRINTS(arg1);
    PRINTS("' not found.\r\n\0");
    PRINTS("\r\n\0");
  }
}

void displayHelp(char* buffer, char* config) {
  clearScreen(config);
  PRINTS("Help Menu\r\n\0");
  PRINTS("- boot \r\n\0");
  PRINTS("Reboot the system\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- clrs\r\n\0");
  PRINTS("Clear the screen\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- copy [file1] [file2]\r\n\0");
  PRINTS("Copy the contents of file1, and create a new file2 with those contents\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- ddir\r\n\0");
  PRINTS("List Directory contents\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- echo [comment]\r\n\0");
  PRINTS("display the comment on the screen\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- exec [filename]\r\n\0");
  PRINTS("execute the program with the matching filename\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- help\r\n\0");
  PRINTS("Display this help manual\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- prnt [filename]\r\n\0");
  PRINTS("Print the contents of the given file to the printer\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("Press Enter to Continue\0");
  SCANS(buffer);
  clearScreen(config);

  PRINTS("- remv [filename]\r\n\0");
  PRINTS("Delete the file with the given name\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- senv\r\n\0");
  PRINTS("Set environment variables\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- show [filename]\r\n\0");
  PRINTS("Display the contents of the given file\r\n\0");
  PRINTS("\r\n\0");
  PRINTS("- twet [filename]\r\n\0");
  PRINTS("Prompts for a line of text and stores it as the given filename\r\n\0");
  
  PRINTS("Press Enter to Continue\0");
  SCANS(buffer);
  clearScreen(config);
}

void clearBuffer(char* buffer, int size) {
  int i = 0;
  while (i < size) {
    buffer[i] = 0;
    ++i;
  }
}
/* 
void strCopy(char* source, char* destination, int bytes) {
  int i = 0;

  while (i < bytes) {
    destination[i] = source[i];
    ++i;
  }
  destination[bytes] = '\0'; // Ensure there is a null terminator
}

int isUpper(char c) {
  // if c is upper-case, it should be in the range of ASCII values A <= c <= Z
  return (c <= 'Z' && c >= 'A'); 
}

int sectorsUsed(char* entry) {
  int full = 0;
  char* currentSector = entry + 8;

  while (currentSector < entry + 32) {
    if (*currentSector != 0) {
      ++full;
      ++currentSector;
    }
  }

  return full;
}

void displayDirectory(char* directory) {
  char filename[9];
  int fullSectors = 0;
  char* currentEntry = directory;

  while (currentEntry < directory + 512) {
    strCopy(currentEntry, filename, 8);

    if (filename[0] != 0) {
      // System files are listed with upper-case letters
      if (!isUpper(filename[0])) {
        PRINTS(filename);
        PRINTS("\t\0");
	PRINTN(sectorsUsed(currentEntry));
      }

      fullSectors += sectorsUsed(currentEntry);
    }
    currentEntry += 32;
  }
  PRINTS("\r\nCurrently using: \0");
  PRINTN(fullSectors);
  PRINTS(" Sectors. \0");
  PRINTN(255 - fullSectors);
  PRINTS(" Sectors Free\r\n\0");
}
*/
