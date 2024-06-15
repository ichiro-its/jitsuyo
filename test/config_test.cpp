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

#include <string>
#include <nlohmann/json.hpp>

#include "gtest/gtest.h"
#include "jitsuyo/config.hpp"

TEST(ConfigTest, FindKey)
{
  nlohmann::json j;
  j["key"] = 42;

  int val;
  EXPECT_EQ(jitsuyo::find_key(j, std::string("key"), val), 42) << "Key must exist";
}

TEST(ConfigTest, SaveConfigJson)
{
  nlohmann::json data;
  data["key"] = 42;

  EXPECT_TRUE(
    jitsuyo::save_config(std::string("/tmp/"), std::string("config.json"), data))
    << "Config must be saved";
}

TEST(ConfigTest, SaveConfigOrderedJson)
{
  nlohmann::ordered_json data;
  data["key"] = 42;

  EXPECT_TRUE(
    jitsuyo::save_config(std::string("/tmp/"), std::string("config.json"), data))
    << "Config must be saved";
}

TEST(ConfigTest, ParseJson)
{
  std::string data_str = R"({"key": 42})";
  nlohmann::json parsed_data = jitsuyo::parse_json(data_str);

  EXPECT_TRUE(parsed_data.contains("key")) << "Key must exist";
  EXPECT_EQ(parsed_data["key"], 42);
}

TEST(ConfigTest, LoadConfig)
{
  nlohmann::json data = jitsuyo::load_config(std::string("/tmp/"), std::string("config.json"));

  EXPECT_TRUE(data.contains("key")) << "Key must exist";
  EXPECT_EQ(data["key"], 42);
}
