#include "CommandExecutor.h"

namespace bavykin
{
  CommandExecutor::CommandExecutor()
  {
    reg_command("print", &CommandExecutor::print);
    reg_command("complement", &CommandExecutor::complement);
    reg_command("intersect", &CommandExecutor::intersect);
    reg_command("union", &CommandExecutor::myUnion);
  }

  void CommandExecutor::readFile(std::istream& input)
  {
    std::string line = "";
    while (getline(input, line))
    {
      if (!line.empty())
      {
        forward_list< std::string > splittedCommandLine = splitString(line, " ");
        const std::string dictionaryName = splittedCommandLine[0];
        dictionary< int, std::string > fillingDictionary(dictionaryName);
        splittedCommandLine.popFront();
        while (splittedCommandLine.size() > 0)
        {
          fillingDictionary.insert(std::stoi(splittedCommandLine[0]), splittedCommandLine[1]);
          splittedCommandLine.popFront();
          splittedCommandLine.popFront();
        }
        m_Dictionaries.insert(dictionaryName, fillingDictionary);
      }
    }
  }

  void CommandExecutor::run(std::istream& input)
  {
    readFile(input);

    std::string line = "";
    while (getline(std::cin, line))
    {
      if (!line.empty())
      {
        try
        {
          Command currentCommand(line);
          if (m_RegisteredCommands.contains(currentCommand.getOperation()))
          {
            void (CommandExecutor:: * operation)(forward_list< std::string >);
            operation = m_RegisteredCommands[currentCommand.getOperation()];
            forward_list< std::string > args = currentCommand.getArgs();
            (this->*operation)(args);
          }
          else
          {
            throw std::invalid_argument("The command is not registered.");
          }
        }
        catch (const std::invalid_argument&)
        {
          std::cout << "<INVALID COMMAND>" << std::endl;
        }
      }
    }
  }

  void CommandExecutor::checkDictNames(forward_list< std::string > args)
  {
    for (size_t i = 1; i < args.size(); i++)
    {
      if (!m_Dictionaries.contains(args[i]))
      {
        throw std::invalid_argument("Invalid argument.");
      }
    }
  }

  void CommandExecutor::print(forward_list< std::string > args)
  {
    if (args.size() != 1)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    if (!m_Dictionaries.contains(args[0]))
    {
      throw std::invalid_argument("Invalid argument.");
    }

    dictionary < int, std::string > toPrint = m_Dictionaries[args[0]];
    std::cout << toPrint << std::endl;
  }

  void CommandExecutor::complement(forward_list< std::string > args)
  {
    if (args.size() != 3)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    checkDictNames(args);

    std::string newDataSet = args[0];
    std::string dataSetOne = args[1];
    std::string dataSetTwo = args[2];

    dictionary< int, std::string > newDict(newDataSet);
    newDict = m_Dictionaries[dataSetOne];
    newDict.changeName(newDataSet);

    m_Dictionaries.insert(newDataSet, newDict.getComplement(m_Dictionaries[dataSetTwo]));
  }

  void CommandExecutor::intersect(forward_list< std::string > args)
  {
    if (args.size() != 3)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    checkDictNames(args);

    std::string newDataSet = args[0];
    std::string dataSetOne = args[1];
    std::string dataSetTwo = args[2];

    dictionary< int, std::string > newDict(newDataSet);
    newDict = m_Dictionaries[dataSetOne];
    newDict.changeName(newDataSet);

    m_Dictionaries.insert(newDataSet, newDict.getIntersect(m_Dictionaries[dataSetTwo]));
  }

  void CommandExecutor::myUnion(forward_list< std::string > args)
  {
    if (args.size() != 3)
    {
      throw std::invalid_argument("Invalid number of command arguments.");
    }

    checkDictNames(args);

    std::string newDataSet = args[0];
    std::string dataSetOne = args[1];
    std::string dataSetTwo = args[2];

    dictionary< int, std::string > newDict(newDataSet);
    newDict = m_Dictionaries[dataSetOne];
    newDict.changeName(newDataSet);

    m_Dictionaries.insert(newDataSet, newDict.getUnion(m_Dictionaries[dataSetTwo]));
  }

  void CommandExecutor::reg_command(std::string command, void (CommandExecutor::* function)(forward_list< std::string >))
  {
    m_RegisteredCommands.insert(command, function);
  }
}
