#include "Command.h"

namespace bavykin
{
  Command::Command(const std::string& raw_command)
  {
    forward_list< std::string > entries = splitString(raw_command, " ");

    if (entries.size() < 2)
    {
      throw std::invalid_argument("String '" + raw_command + "' cannot be used as a command.");
    }

    m_Operation = entries[0];
    entries.popFront();
    m_Args = entries;
  }

  std::string Command::getOperation() const
  {
    return m_Operation;
  }

  forward_list< std::string > Command::getArgs() const
  {
    return m_Args;
  }
}
