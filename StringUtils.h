#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <sstream>

/**
 * Reverse a null terminated string in place
 */
void reverseString(char* s)
{
  char* p = s; char* q = s;
  while (*++q); --q;
  while (p < q) {
    char c = *q;
    *q = *p; *p = c;
    q--; p++;
  }
}

void reverseString(char* s, int len)
{
  char* p = s; char* q = s + len - 1;
  while (p < q) {
    char c = *q;
    *q = *p; *p = c;
    q--; p++;
  }
}

/**
 * Split a string into tokens, using the given separator
 */
std::vector<std::string> tokenize(char* s, const char* sep)
{
  std::vector<std::string> v;
  char* token;
  while ((token = strsep(&s, sep)) != 0) {
    v.push_back(token);
  }
  return v;
}

/**
 * Reverse the words in a phrase, separated by 'sep'.  
 * The ordering of the words in the phrase is kept the same, 
 * and each word is just reversed in place.
 */
void reverseWords(char* phrase, const char sep)
{
  char* p = phrase;
  char* q = phrase;
  while (*q) {
    while(*q && *q != sep) {
      q++;
    }
    int len = q - p;
    reverseString(p, len);
    if (*q) q++;
    p = q;
  }
}

/**
 * Convert an integer into Roman numerals
 * n must be in the range 1 to 3999
 */
std::string intToRoman(int n)
{
  // 1, 5, 10, 50, 100, 500, 1000
  // I, V, X, L, C, D, M
  //
  // The number must be arranged with highest letters first.
  // E.g. 1511 = MDXI and not IXDM
  // I, X, C, M can only be repeated 3 times in succession
  // D, L, V can never be repeated in succession
  // I can be subtracted from V and X only
  // X can be subtracted from L and C only
  // C can be subtracted from D and M only
  // V, L, D can never be subtracted
  // Only one small value symbol may be subtracted from any large value symbol
  int num[13] = 
    {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  const char* str[13] = 
    {"M", "XM", "D", "MD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  std::ostringstream os;
  for (int i = 0; i < 13; i++) {
    while (n >= num[i]) {
      n -= num[i];
      os << str[i];
    }
  }
  return os.str();
}

#endif /* STRING_UTILS_H */
