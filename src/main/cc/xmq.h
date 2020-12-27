/*
 Copyright (c) 2019-2020 Fredrik Öhrström

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

#ifndef XMQ_H
#define XMQ_H

#include <string>
#include <vector>
#include <set>

namespace xmq
{
    // The render type is how the output from the xmq command is presented.
    // Plain is the exact xmq/xml/html input/output.
    // Terminal means that it will inject ansi color sequences.
    // Html means that it will inject html color sequences and formatting.
    // Tex means that it will inject tex color sequences and formatting.
    enum class RenderType { plain, terminal, html, tex };

    // Xmq can be converted between the selected or auto tree type.
    enum class TreeType { auto_detect, xml, html };

    class Settings
    {
    public:
        std::string filename;
        std::vector<char> *in;
        std::vector<char> *out;

        TreeType tree_type {};  // Set input type to: auto_detect, xml or html.
        RenderType output {};   // Write plain text, text+ansi, text+html or text+tex.
        bool use_color {};      // Set to true to produce colors. Color can never be enabled with the plain output type.
        bool no_declaration {}; // Do not print any xml-declaration <? ?> nor doctype <!DOCTYPE html>.
        bool preserve_ws {};    // When converting from xml to xmq. Preserve whitespace as much as possible.
        bool view {};           // Do not convert, just view the input, potentially adding color and formatting.
        bool compress {};       // Find common prefixes of the tags.
        std::set<std::string> excludes; // Exclude these attributes
    };

    enum class TokenType
    {
        none,          // eof
        equals,        // =
        brace_open,    // {
        brace_close,   // }
        paren_open,    // (
        paren_close,   // )
        quote,         // '....'
        comment,       // / starts either // or /*
        text           // Not quoted text, can be tag or content.
     };

    struct Token
    {
        Token(TokenType t, const char *v) : type(t), value(v) { }

        TokenType type;
        const char *value; // Zero terminated string allocated by rapid_xml allocate_string.
    };

    struct ParseActions
    {
        virtual void *root() = 0;
        virtual char *allocateCopy(const char *content, size_t len) = 0;
        virtual void *appendElement(void *parent, Token t) = 0;
        virtual void appendComment(void *parent, Token t) = 0;
        virtual void appendData(void *parent, Token t) = 0;
        virtual void appendAttribute(void *parent, Token key, Token value) = 0;
    };

    int main_xml2xmq(Settings *settings);
    int main_xmq2xml(const char *filename, Settings *settings);

    void renderXMQ(void *node, Settings *provided_settings);
    void parse(const char *filename, char *xmq, ParseActions *actions);
}

#endif