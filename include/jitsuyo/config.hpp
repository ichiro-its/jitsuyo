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

#include <string>
#include <nlohmann/json.hpp>

namespace jitsuyo
{

template<typename T>
bool check_val(const nlohmann::json & i, const std::string & key, T & val)
{
  if (i.contains(key)) {
    i.at(key).get_to(val);
    return true;
  }
  return false;
}

bool save_config(
  const std::string & path, const std::string & file_name,
  const nlohmann::json & data);
bool save_config(
  const std::string & path, const std::string & file_name,
  const std::string & data_str);
nlohmann::json load_config(const std::string & path, const std::string & file_name);

}  // namespace jitsuyo

#endif  // JITSUYO__CONFIG_HPP_
