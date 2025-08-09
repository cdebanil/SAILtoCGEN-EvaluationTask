#include "headers.h"

using namespace std;

// Helper function to strip leading and trailing whitespace.
void trim(string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos)
    {
        s.clear();
        return;
    }
    size_t end = s.find_last_not_of(" \t\n\r");
    s = s.substr(start, end - start + 1);
}

/* Helper function to replace all contiguous blocks of whitespace
(outside matching sets of double quotes - to ensure strings are
not touched) with a single whitespace. */
void simplifyString(string &input)
{
    trim(input);

    string output;
    bool inQuotes = false;
    bool prevWasSpace = false;
    int len = input.length();
    for (int i = 0; i < len; ++i)
    {
        char c = input[i];

        // Handle quotes - skip escaped quotes
        if (c == '"')
        {
            // Count backslashes before this quote
            int backslashCount = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                if (input[j] == '\\')
                {
                    backslashCount++;
                }
                else
                {
                    break;
                }
            }
            // If even number of backslashes, quote is not escaped
            if (backslashCount % 2 == 0)
            {
                inQuotes = !inQuotes;
            }
            output += c;
            prevWasSpace = false;
            continue;
        }

        if (inQuotes)
        {
            output += c;
            prevWasSpace = false;
        }
        else
        {
            if (isspace(static_cast<unsigned char>(c)))
            {
                // Only add a space if the previous character wasn't whitespace
                if (!prevWasSpace)
                {
                    output += ' ';
                    prevWasSpace = true;
                }
            }
            else
            {
                output += c;
                prevWasSpace = false;
            }
        }
    }

    // Remove any trailing space
    if (!output.empty() && output.back() == ' ')
    {
        output.pop_back();
    }

    input = output;
}

/* Helper function to tokenize a string with a specified token character
while ignoring tokens within matched double quotes, curly braces or
square brackets. */
vector<string> tokenize(string input, char separator)
{
    vector<string> tokens;
    string curToken;
    bool inQuotes = false;
    int squareBracketDepth = 0;
    int curlyBraceDepth = 0;
    char quote = '\"';

    size_t i = 0;
    while (i < input.size())
    {
        char c = input[i];
        if (inQuotes)
        {
            if (c == '\\')
            {
                curToken += c;
                i++;

                if (i < input.size())
                {
                    char next = input[i];
                    curToken += next;
                    i++;
                }

                continue;
            }
            else if (c == quote)
            {
                inQuotes = false;
                curToken += c;
                i++;
                continue;
            }
            // Any other character inside quotes
            curToken += c;
            i++;
            continue;
        }
        else
        {
            // Not in quotes
            if (c == quote)
            {
                inQuotes = true;
                curToken += c;
                i++;
                continue;
            }
            else if (c == '{')
            {
                curlyBraceDepth++;
                curToken += c;
                i++;
                continue;
            }
            else if (c == '}')
            {
                if (curlyBraceDepth > 0)
                {
                    curlyBraceDepth--;
                }
                curToken += c;
                i++;
                continue;
            }
            else if (c == '[')
            {
                squareBracketDepth++;
                curToken += c;
                i++;
                continue;
            }
            else if (c == ']')
            {
                if (squareBracketDepth > 0)
                {
                    squareBracketDepth--;
                }
                curToken += c;
                i++;
                continue;
            }
            else if (c == separator)
            {
                if (curlyBraceDepth == 0 && squareBracketDepth == 0)
                {
                    tokens.push_back(curToken);
                    curToken.clear();
                    i++;
                    continue;
                }
                // Otherwise, treat as normal char
                curToken += c;
                i++;
                continue;
            }
            else
            {
                // Normal character
                curToken += c;
                i++;
                continue;
            }
        }
    }
    // Add last token if any
    tokens.push_back(curToken);
    return tokens;
}
