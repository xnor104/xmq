/*
 Copyright (c) 2019 Fredrik Öhrström

 MIT License

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef UTIL_H
#define UTIL_H

#include <map>
#include <string>
#include <vector>

#include <string.h>

typedef std::map<std::string,int> StringCount;

void add_string(char *s, StringCount &c);
std::string find_prefix(char *s, StringCount &c);
bool loadFile(std::string file, std::vector<char> *buf);
bool loadStdin(std::vector<char> *buf);

extern const char *manual;

bool isWhiteSpace(char c);

bool isNewLine(char c);

bool isHtml(std::vector<char> &buffer);
bool firstWordIsHtml(std::vector<char> &buffer);

// String which is not necessarily zero-terminated!
struct str
{
    const char *s; // Start of string.
    size_t l; // Length of string.

    str(const char *st, size_t le) : s(st), l(le) {}
    bool equals(std::string &st) {
        if (l != st.size()) return false;
        return !strncmp(st.c_str(), s, l);
    }
    bool equals(str &st) {
        if (l != st.l) return false;
        return !strncmp(st.s, s, l);
    }

    str() : s(""), l(0) {}
};

#endif