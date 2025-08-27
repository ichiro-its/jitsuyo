// Copyright (c) 2024 ICHIRO ITS
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef JITSUYO__CONFIG_HPP_
#define JITSUYO__CONFIG_HPP_

#include "keisan/angle/angle.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace jitsuyo
{

template <typename T>
bool assign_val_impl(
  const nlohmann::json & json, const std::string & key, T & val, const std::string & val_name,
  const std::string & json_name)
{
  auto it = json.find(key);
  if (it != json.end()) {
    if constexpr (std::is_same_v<
                    typename std::remove_reference<decltype(val)>::type,
                    decltype(keisan::Angle<double>())>) {
      if (!it->is_number()) {
        std::cout << "Expected double value at key `" << key << "` for variable name `" << val_name
                  << "` in `" << json_name << "`" << std::endl;
        return false;
      }

      double val_double = it->get<double>();
      val = keisan::make_degree(val_double);
    } else {
      try {
        it->get_to(val);
      } catch (const std::exception & e) {
        std::cout << "Error found at key `" << key << "` for variable name `" << val_name
                  << "` in `" << json_name << "`" << std::endl;
        std::cout << e.what() << std::endl;

        return false;
      }
    }

    return true;
  }

  std::cout << "Failed to find key `" << key << "` for variable name `" << val_name << "` in `"
            << json_name << "`" << std::endl;
  return false;
}

template <typename T>
typename std::enable_if<
  std::is_same<T, nlohmann::json>::value || std::is_same<T, nlohmann::ordered_json>::value,
  bool>::type
save_config(
  const std::string & path, const std::string & file_name, const T & data,
  bool create_backup = true)
{
  if (create_backup) {
    std::ifstream file(path + file_name, std::ios::in);
    namespace fs = std::filesystem;
    if (!fs::is_directory((path + "backup/"))) {
      if (!fs::create_directory(path + "backup/")) {
        throw std::runtime_error("Failed to create directory `backup/` at path `" + path + "`.");
      }
    }
    std::ofstream file_bak(path + "backup/" + file_name, std::ios::out | std::ios::trunc);
    file_bak << file.rdbuf();
    file_bak.close();
  }

  std::ofstream file(path + file_name, std::ios::out | std::ios::trunc);
  if (!file.is_open()) {
    std::cout << "Failed to open file `" << path + file_name << "`" << std::endl;
    return false;
  }

  file << std::setw(2) << data << std::endl;
  file.close();
  return true;
}

template <typename T>
typename std::enable_if<
  std::is_same<T, nlohmann::json>::value || std::is_same<T, nlohmann::ordered_json>::value,
  bool>::type
load_config(const std::string & path, const std::string & file_name, T & data)
{
  std::ifstream file(path + file_name, std::ios::in);
  if (!file.is_open()) {
    std::cout << "Failed to open file `" << path + file_name << "`" << std::endl;
    return false;
  }

  try {
    data = T::parse(file);
  } catch (std::exception & e) {
    std::cout << "Failed to parse file `" << path + file_name << "` to json data" << std::endl;
    return false;
  }

  file.close();
  return true;
}

#define assign_val(json, key, val) assign_val_impl(json, key, val, #val, #json)

}  // namespace jitsuyo

#endif  // JITSUYO__CONFIG_HPP_
