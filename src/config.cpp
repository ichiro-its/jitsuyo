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

bool save_config(
  const std::string & path, const std::string & file_name,
  const nlohmann::json & data)
{
  std::string parsed_path = path;
  std::string parsed_file_name = file_name;

  if (path.back() != '/') {
    parsed_path += '/';
  }

  if (file_name.find(".json") == std::string::npos) {
    parsed_file_name += ".json";
  }

  if (path.empty() || file_name.empty() || data.empty() || !is_directory_exist(path)) {
    return false;
  }

  std::ofstream file(parsed_path + parsed_file_name, std::ios::out | std::ios::trunc);
  file << std::setw(2) << data << std::endl;
  file.close();
  return true;
}

bool save_config(const std::string & path, const std::string & file_name)
{
  nlohmann::json data = nlohmann::json::parse(file_name);
  return save_config(path, file_name, data);
}

}  // namespace jitsuyo
