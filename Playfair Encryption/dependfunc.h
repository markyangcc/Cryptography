#ifndef DEPENDFUNC_H_
#define DEPENDFUNC_H

#include <algorithm>
#include <set>
#include <string>

std::string rmstr_duplicates(std::string srcstr) {
  std::string str = std::move(srcstr);

  std::set<char> chars;

  str.erase(std::remove_if(str.begin(), str.end(),
                           [&chars](char i) {
                             // If encountered character, remove this one.
                             if (chars.count(i)) {
                               return true;
                             }

                             // Otherwise, mark this character encountered and
                             // don't remove.
                             chars.insert(i);
                             return false;
                           }),
            str.end());

  str.erase(std::remove_if(str.begin(), str.end(),
                           [](unsigned char x) { return std::isspace(x); }),
            str.end());

  return str;
}

std::string rmstr_isspace(std::string srcstr) {
  std::string str = std::move(srcstr);

  str.erase(std::remove_if(str.begin(), str.end(),
                           [](unsigned char x) { return std::isspace(x); }),
            str.end());

  return str;
}

#endif