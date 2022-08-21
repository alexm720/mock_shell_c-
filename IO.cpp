#include "main.h"

void write_string(std::string print_str)
{
  for(int i = 0; i < print_str.length();i++)
  {
    write(STDOUT_FILENO, &print_str[i], 1);
  }
}

void clear_string(std::string terminal_string)
{
   if(terminal_string.empty()) return; 
   
   for(int i = 0; i < terminal_string.length(); i++)
   {
      write_string(ERASE);
   }
}

void read_char(char *input)
{
  read(STDIN_FILENO,&(*input),1);
}

void display_char(char input)
{
  write(STDOUT_FILENO, &input, 1);
}

void set_directory(char * curr_direct, std::string terminal_string,
		   char input, bool override_write)
{
  if(!terminal_string.empty() || (input == BACK_SPACE || input == DELETE ||
     input == ESC) || override_write)
  {
    return;
  }

  getcwd(curr_direct, FILENAME_MAX);
  std::string directory_name = convert_char(curr_direct);
  std::string directory_str;
  if(directory_name.length() > MAX_DIRECTORY_LEN)
  {
  directory_str = DIRECTORY_PREPEND;
  std::string temp;
    for(int i = directory_name.length()-1; i >= 0; i--)
    {
      if(directory_name[i] == FORWARD_SLASH)
      {
        directory_str += temp;
        directory_name = directory_str;
        break;
      }
      temp.insert(0, std::string(1,directory_name[i]));
    }
  }
  directory_name += PERCENT;
  write_string(directory_name);
}

std::string convert_char(char *char_str)
{
  std::string converted(char_str);
  return converted;
}

bool perform_instruct(char input, std::vector<std::string> history,signed int *index,
		      signed int *static_index, std::string *terminal_line)
{
  switch(input)
  {
    case UP_KEY:
      history_instruct(history, index,static_index, true, false, terminal_line);
      return true;
    case DOWN_KEY:
      history_instruct(history, index, static_index, false, true, terminal_line);
      return true;
    default:
      display_char(BELL);
      return true;
  }
  return true;
}

void history_instruct(std::vector<std::string> history, signed int *index, 
		      signed int *static_index,bool up_pressed, bool down_pressed, 
		      std::string *terminal_line)
{   
  bool check;
  if(up_pressed)
  {
    check = (*index > 0) ? false : true;
    if(check)
    {
      display_char(BELL); 
      return;
    }
    *index -= 1;
    clear_string((*terminal_line));
    (*terminal_line) = history[*index];
    write_string(*terminal_line); 
    return; 
  }

  check = (*index + 1 >= *static_index) ? false : true;
  if(!check || (*terminal_line).empty())
  {
    if(!(*terminal_line).empty())
    {
      clear_string((*terminal_line));
      (*terminal_line).clear();
    }
    else
    {
      display_char(BELL);
    }
    *index = *static_index;
    return;
  }
  *index += 1;
  clear_string((*terminal_line));
  (*terminal_line) = history[*index];
  write_string(*terminal_line); 

}


std::vector<std::string> string_vectorizer(std::string terminal_line)
{
  std::vector<std::string> parsed_string;
  std::string temp = "";
 
  if(terminal_line.empty()) return parsed_string;

  for(int i = 0; i < terminal_line.length();i++)
  {
    if((terminal_line[i] == SPACE && !temp.empty()) || terminal_line[i+1] == STRING_END)
    {
      if(terminal_line[i+1] == STRING_END && terminal_line[i] != SPACE)
      {
        temp.push_back(terminal_line[i]);
      }
      parsed_string.push_back(temp);
      temp = "";
      continue;
    }
    temp.push_back(terminal_line[i]);
  }
  return parsed_string;
}

