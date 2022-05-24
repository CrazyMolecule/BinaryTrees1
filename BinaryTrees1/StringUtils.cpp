#include "StringUtils.h"

forward_list< std::string > splitString(const std::string& str, const std::string& delimiter)
{
  forward_list< std::string > strings;

  std::string::size_type pos = 0;
  std::string::size_type prev = 0;
  while ((pos = str.find(delimiter, prev)) != std::string::npos)
  {
    strings.pushBack(str.substr(prev, pos - prev));
    prev = pos + 1;
  }

  strings.pushBack(str.substr(prev));

  return strings;
}
