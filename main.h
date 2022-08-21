#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <termios.h>
#include <cstdio>
#include <ctype.h>
#include <vector>
#include <string.h>

#define BACK_SPACE 0x08
#define DELETE 0x7F
#define ESC 0x1B
#define RETURN 0x0A
#define FORWARD_SLASH 0x2F
#define SPACE 0x20

#define FIRST_STATE 0x1B
#define SECOND_STATE 0x5B
#define UP_KEY 0X41
#define DOWN_KEY 0x42
#define RIGHT_KEY 0x43
#define LEFT_KEY 0x44

#define BELL '\a'
#define ERASE "\b \b"
#define MAX_DIRECTORY_LEN 16
#define MAX_INDEX 10
#define PERCENT "% "
#define DIRECTORY_PREPEND "/.../"
#define STRING_END '\0'



/*
extern std::vector<unsigned char> UP_KEY;
extern std::vector<unsigned char> RIGHT_KEY;
extern std::vector<unsigned char> DOWN_KEY;
extern std::vector<unsigned char> LEFT_KEY;
*/

/*noncanmode.cpp*/
void ResetCanonicalMode(int fd, struct termios *savedattributes);
void SetNonCanonicalMode(int fd, struct termios *savedattributes);
/****************/


/*IO.cpp*/
void write_string(std::string print_str);
void clear_string(std::string terminal_string);
void read_char(char *input);
void display_char(char input);
void set_directory(char * curr_direct, std::string terminal_str, 
char input, bool override_write);
std::string convert_char(char *char_str);
bool perform_instruct(char input, std::vector<std::string> history,
signed int *index,signed int *static_index, std::string *terminal_line);
void history_instruct(std::vector<std::string> history, signed int *index, signed int *static_index,bool up_pressed, bool down_pressed, std::string *terminal_line);
 std::vector<std::string> string_vectorizer(std::string terminal_line);



/******/




#endif

