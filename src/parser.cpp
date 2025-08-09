#include "headers.h"

using namespace std;

string parse_string(string &str)
{
    if (str.size() < 2)
    {
        throw runtime_error("Invalid json input  =>  " + str);
    }

    if (str[0] != '\"' || str[str.size() - 1] != '\"')
    {
        throw runtime_error("Invalid json input  =>  " + str);
    }

    size_t pos = 1;
    while (pos < str.size() - 1)
    {
        if (str[pos] != '\"' && str[pos] != '\\' && !iscntrl(str[pos]))
        {
            pos++;
            continue;
        }
        else
        {
            if (iscntrl(str[pos]))
            {
                throw runtime_error("Invalid json input  =>  " + str);
            }
            if (str[pos] == '\"' && pos < str.size() - 1)
            {
                throw runtime_error("Invalid json input  =>  " + str);
            }
            if (str[pos] == '\\')
            {
                if (pos > str.size() - 3)
                {
                    throw runtime_error("Invalid json input  =>  " + str);
                }
                else
                {
                    pos++;
                    char ch = str[pos];
                    if (ch == '\"' || ch == '\\' || ch == '/' || ch == 'b' || ch == 'f' || ch == 'n' || ch == 'r' || ch == 't')
                    {
                        pos++;
                        continue;
                    }
                    else if (ch == 'u' && pos <= str.size() - 6)
                    {
                        string chars = str.substr(pos + 1, 4);
                        for (int i = 0; i < 4; i++)
                        {
                            if (isdigit(chars[i]))
                            {
                                continue;
                            }
                            else if (chars[i] >= 'A' && chars[i] <= 'F')
                            {
                                continue;
                            }
                            else if (chars[i] >= 'a' && chars[i] <= 'f')
                            {
                                continue;
                            }
                            else
                            {
                                throw runtime_error("Invalid json input  =>  " + str);
                            }
                        }
                    }
                    else
                    {
                        throw runtime_error("Invalid json input  =>  " + str);
                    }
                }
            }
        }
    }
    return str.substr(1, str.size() - 2);
}

string parse_number(string &str)
{
    size_t pos = 0;
    if (str[pos] == '-')
    {
        pos++;
    }

    vector<string> numberParts = tokenize(str, '.'); // divide into integer and fractional parts
    if (numberParts.size() > 2)
    {
        throw runtime_error("Invalid json input  =>  " + str);
    }

    string integerPart = numberParts[0];
    while (pos < integerPart.size())
    {
        if (!isdigit(integerPart[pos]))
        {
            throw runtime_error("Invalid json input  =>  " + str);
        }
        pos++;
    }

    string fractionalPart;
    if (numberParts.size() > 1)
    {
        fractionalPart.append(numberParts[1]);
    }
    else
    {
        return str;
    }

    pos = 0;
    string exponentialPart;
    while (pos < fractionalPart.size())
    {
        if (!isdigit(fractionalPart[pos]))
        {
            if (fractionalPart[pos] == 'E' || fractionalPart[pos] == 'e')
            {
                exponentialPart = fractionalPart.substr(pos + 1);
                break;
            }
            else
            {
                throw runtime_error("Invalid json input  =>  " + str);
            }
        }
        pos++;
    }

    if (exponentialPart.empty())
    {
        return str;
    }

    pos = 0;
    if (exponentialPart[pos] == '+' || exponentialPart[pos] == '-')
    {
        pos++;
    }

    while (pos < exponentialPart.size())
    {
        if (!isdigit(exponentialPart[pos]))
        {
            throw runtime_error("Invalid json input  =>  " + str);
        }
        pos++;
    }

    return str;
}

vector<Value> parse_array(string &str)
{
    if (str.size() < 2)
    {
        throw runtime_error("Invalid json input  =>  " + str);
    }
    vector<Value> vec;
    if (str.size() == 2)
    {
        return vec;
    }
    string s = str.substr(1, str.size() - 2);
    vector<string> vals = tokenize(s, ',');
    for (size_t i = 0; i < vals.size(); i++)
    {
        vec.push_back(parse_value(vals[i]));
    }
    return vec;
}

Value parse_value(string &str)
{
    trim(str);

    Value val;
    if (str.compare("null") == 0)
    {
        return val;
    }
    else if (str.compare("true") == 0)
    {
        val.type = Value::Boolean;
        val.boolean = true;
        return val;
    }
    else if (str.compare("false") == 0)
    {
        val.type = Value::Boolean;
        val.boolean = false;
        return val;
    }
    else if (str[0] == '{' && str.back() == '}')
    {
        val.type = Value::Object;
        val.object = parse_object(str);
        return val;
    }
    else if (str[0] == '[' && str.back() == ']')
    {
        val.type = Value::Array;
        val.array = parse_array(str);
        return val;
    }
    else if (str[0] == '\"' && str.back() == '\"')
    {
        val.type = Value::String;
        val.str = parse_string(str);
        return val;
    }
    else if (str[0] == '-' || isdigit(str[0]))
    {
        val.type = Value::Number;
        val.number = parse_number(str);
        return val;
    }
    else
    {
        throw runtime_error("Invalid json input  =>  " + str);
    }
}

// This function will parse a key : value pair
pair<Key, Value> parse_pair(string &s)
{
    trim(s);

    if (s[0] != '\"')
    {
        throw runtime_error("Invalid json input  =>  " + s);
    }

    int idx = 0; // Index of second double quote char in the string, which is not escaped.

    for (size_t i = 1; i < s.length(); i++)
    {
        if (s[i] != '\"')
        {
            continue;
        }

        // Count number of consecutive backslashes before current character
        int backslashCount = 0;
        int j = i - 1;
        while (j >= 0 && s[j] == '\\')
        {
            backslashCount++;
            j--;
        }

        // If even number of backslashes => character is not escaped
        if (backslashCount % 2 == 0)
        {
            idx = i;
            break;
        }
    }

    if (idx == 0)
    {
        throw runtime_error("Invalid json input  =>  " + s);
    }

    string name = s.substr(0, idx + 1);
    Key k = {parse_string(name)};

    string str = s.substr(idx + 1);
    trim(str);

    if (str[0] != ':')
    {
        throw runtime_error("Invalid json input  =>  " + s);
    }

    string strVal = str.substr(1);
    Value val = parse_value(strVal);

    pair<Key, Value> pair = make_pair(k, val);
    return pair;
}

Obj parse_object(string &s)
{
    Obj parsed{};

    if (s.size() < 2)
    {
        throw runtime_error("Invalid json input  =>  " + s);
    }
    if (s[0] != '{' || s[s.size() - 1] != '}')
    {
        throw runtime_error("Invalid json input  =>  " + s);
    }

    string str = s.substr(1, s.size() - 2);
    trim(str);
    if (str.empty())
    {
        return parsed;
    }

    if (str.back() == ',')
    {
        throw runtime_error("Invalid json input  =>  " + s);
    }
    vector<string> pairs = tokenize(str, ',');

    for (size_t i = 0; i < pairs.size(); i++)
    {
        pair<Key, Value> item = parse_pair(pairs[i]);
        parsed.data[item.first] = item.second;
    }

    return parsed;
}

Obj parse(string &str)
{
    Obj root = parse_object(str);
    return root;
}