#include <iostream>
#include <iomanip>

#include "jitsuyo/cli.hpp"

namespace jitsuyo
{

std::string uppercased(std::string str)
{
  for (char &ch : str) {
    if (ch >= 'a' && ch <= 'z') {
      ch = 'A' + (ch - 'a');
    }
  }

  return str;
}

std::string lowercased(std::string str)
{
  for (char &ch : str) {
    if (ch >= 'A' && ch <= 'Z') {
      ch = 'a' + (ch - 'A');
    }
  }

  return str;
}

void clear() { std::cout << "\033[2J\033[2H" << std::endl; }
void end_line() { std::cout << std::endl; }

void print_line()
{
  std::cout << fg_white() << "================================================================" << std::endl;
}

void print(std::string value)
{
  std::cout << value << std::endl;
}

void print_error(std::string value)
{
  std::cout << fg_red() << value << std::endl;
}

void print_block(std::string value)
{
  std::cout << fg_white() << "[ ";
  std::cout << fg_blue() << uppercased(value);
  std::cout << fg_white() << " ]" << std::endl;
}

void print_parameter(std::string key, std::string value)
{
  std::cout << key << ": " << fg_yellow() << value << reset() << std::endl;
}

void print_parameter(std::string key, bool value)
{
  std::stringstream ss;
  ss << std::boolalpha << value << std::noboolalpha;
  print_parameter(key, ss.str());
}

void print_parameter(std::string key, int value)
{
  std::stringstream ss;
  ss << value;
  print_parameter(key, ss.str());
}

void print_parameter(std::string key, float value)
{
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);
  ss << value << std::setprecision(6) << std::defaultfloat;
  print_parameter(key, ss.str());
}

void print_parameter_block(std::string key, std::string value)
{
  std::cout << fg_white() << "[ ";
  std::cout << fg_blue() << uppercased(key);
  std::cout << fg_white() << " ";
  std::cout << fg_yellow() << value;
  std::cout << fg_white() << " ] " << reset();
}

void print_parameter_block(std::string key, bool value)
{
  std::stringstream ss;
  ss << std::boolalpha << value << std::noboolalpha;
  print_parameter_block(key, ss.str());
}

void print_parameter_block(std::string key, int value)
{
  std::stringstream ss;
  ss << value;
  print_parameter_block(key, ss.str());
}

void print_parameter_block(std::string key, float value)
{
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);
  ss << value << std::setprecision(6) << std::defaultfloat;
  print_parameter_block(key, ss.str());
}

std::string reset() { return "\033[0m"; }

std::string fg_white() { return "\033[37m"; }
std::string fg_black() { return "\033[30m"; }
std::string fg_red() { return "\033[31m"; }
std::string fg_green() { return "\033[32m"; }
std::string fg_yellow() { return "\033[33m"; }
std::string fg_blue() { return "\033[34m"; }
std::string fg_magenta() { return "\033[35m"; }
std::string fg_cyan() { return "\033[36m"; }

} // namespace jitsuyo