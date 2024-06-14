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

#include "jitsuyo/config.hpp"

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "jitsuyo/linux.hpp"

namespace jitsuyo
{

nlohmann::json parse_json(const std::string & data_str)
{
  nlohmann::json data;

  try {
    data = nlohmann::json::parse(data_str);
  } catch (const nlohmann::json::parse_error & e) {
    throw e;
  }

  return data;
}

nlohmann::json load_config(const std::string & path, const std::string & file_name)
{
  if (path.empty() || file_name.empty() || !is_directory_exist(path)) {
    return nlohmann::json();
  }

  std::ifstream file(path + file_name);
  nlohmann::json data;

  try {
    data = nlohmann::json::parse(file);
  } catch (const nlohmann::json::parse_error & e) {
    throw e;
  }

  file.close();
  return data;
}

nlohmann::ordered_json load_ordered_config(
  const std::string & path, const std::string & file_name)
{
  if (path.empty() || file_name.empty() || !is_directory_exist(path)) {
    return nlohmann::ordered_json();
  }

  std::ifstream file(path + file_name);
  nlohmann::ordered_json data;

  try {
    data = nlohmann::ordered_json::parse(file);
  } catch (const nlohmann::json::parse_error & e) {
    throw e;
  }

  file.close();
  return data;
}

}  // namespace jitsuyo
