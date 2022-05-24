#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <iostream>
#include <string>
#include <functional>
#include "Dictionary.h"
#include "Command.h"
#include "ForwardList.h"
#include "StringUtils.h"

namespace bavykin
{
  class CommandExecutor
  {
  public:
    CommandExecutor();

    void readFile(std::istream& input);
    void run(std::istream& input);

  private:
    dictionary < std::string, void (CommandExecutor::*)(forward_list< std::string >) > m_RegisteredCommands;
    dictionary < std::string, dictionary < int, std::string > > m_Dictionaries;

    void checkDictNames(forward_list< std::string > args);
    void print(forward_list< std::string > args);
    void complement(forward_list< std::string > args);
    void intersect(forward_list< std::string > args);
    void myUnion(forward_list< std::string > args);
    void reg_command(std::string command, void (CommandExecutor::* function)(forward_list< std::string >));
  };
}
#endif
