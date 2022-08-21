#include "main.h"

int main(int argc, char *argv[])
{
  char input, curr_direct[FILENAME_MAX];
  std::string terminal_string;
  struct termios SavedTermAttributes;
  bool state_one_check,state_two_check,instruct_check,override_write = false;
  std::vector<std::string> history, parsed_string;
  signed int index,static_index = 0;

  SetNonCanonicalMode(STDIN_FILENO, &SavedTermAttributes);
  while(true)
  {
    set_directory(curr_direct, terminal_string, input, override_write);
    override_write = false;
    read_char(&input);

    if((input == BACK_SPACE || input == DELETE))
    {
      if(terminal_string.empty())
      {
	display_char(BELL);
        continue;
      }
      terminal_string.pop_back();
      write_string(ERASE);
      continue;
    }
    
    if(state_one_check || input == FIRST_STATE)
    {
      if(input == FIRST_STATE)
      {
      	state_one_check = true;
	override_write = true;
        continue;
      }
      if(state_one_check && input == SECOND_STATE)
      {
    	state_two_check = true;
	override_write = true;
	continue;
      }
      if(state_one_check && state_two_check)
      {
	override_write = perform_instruct(input,history,&index,&static_index,&terminal_string);
	state_one_check = false;
	state_two_check = false;
	continue;
      }
      state_one_check = false;
      state_two_check = false;
    } 
    display_char(input);
    terminal_string.push_back(input);

    if(input == RETURN)
    {
      terminal_string.pop_back();
      if (terminal_string.empty()) continue;
      if(static_index < MAX_INDEX) 
      {
        history.push_back(terminal_string);
        static_index += 1;
      }
      else
      {
        history.erase(history.begin());
        history.push_back(terminal_string);
      }
      index = static_index;
      parsed_string = string_vectorizer(terminal_string);
      terminal_string.clear();
    }
  }


  ResetCanonicalMode(STDIN_FILENO, &SavedTermAttributes);
  return 0;
}
