#include <nlohmann/json.hpp>

#include "jitsuyo/config.hpp"

namespace jitsuyo
{

template <typename T>
bool check_val(const nlohmann::json & i, const std::string& key, T& val) {
  if (i.contains(key)) {
    i.at(key).get_to(val);
    return true;
  }
  return false;
}

} // namespace jitsuyo