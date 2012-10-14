#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <string.h>
#include <vector>

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

#endif /* STRING_UTILS_H */
