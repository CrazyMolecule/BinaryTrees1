#ifndef COMMAND_H
#define COMMAND_H
#include "StringUtils.h"

namespace bavykin
{
  class Command
  {
  public:
    Command(const std::string& raw_command);

    std::string getOperation() const;
    forward_list< std::string > getArgs() const;

  private:
    std::string m_Operation;
    forward_list< std::string > m_Args;
  };
}
#endif
