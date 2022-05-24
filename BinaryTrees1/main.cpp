#include <iostream>
#include <fstream>
#include "CommandExecutor.h"
#include "BinarySearchTree.h"

using namespace bavykin;

const int ARGUMENT_COUNT_REQUIRED = 2;

int main(int argc, char* argv[])
{
  BST< int, std::string > lol;

  std::ifstream dictionaryDataSource;

  dictionaryDataSource.open("input.txt");

  if (!dictionaryDataSource.is_open())
  {
    std::cerr << "The input file was not opened.";
    return 1;
  }

  CommandExecutor().run(dictionaryDataSource);

  try
  {
    if (argc == ARGUMENT_COUNT_REQUIRED)
    {
      dictionaryDataSource.open(argv[1]);

      if (!dictionaryDataSource.is_open())
      {
        std::cerr << "The input file was not opened.";
        return 1;
      }

      CommandExecutor().run(dictionaryDataSource);
    }
    else
    {
      throw std::runtime_error("Invalid number of arguments.");
    }
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << std::endl;
    return 2;
  }
}
