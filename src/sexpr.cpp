#include "headers.h"

using namespace std;

string output_value(Value val)
{
    string str;
    vector<Value> vals;
    switch (val.type)
    {
    case Value::Null:
        str = "'()";
        break;
    case Value::Boolean:
        if (val.boolean)
        {
            str = "#t";
        }
        else
        {
            str = "#f";
        }
        break;
    case Value::Number:
        str = val.number;
        break;
    case Value::String:
        str += '\"';
        str.append(val.str);
        str += '\"';
        break;
    case Value::Array:
        vals = val.array;
        for (size_t i = 0; i < vals.size(); i++)
        {
            str += '(';
            str.append(output_value(vals[i]));
            str.append(") ");
        }
        break;
    case Value::Object:
        str = output_object(val.object);
        break;
    default:
        str = "'()";
    }

    return str;
}

string output_pair(Key k, Value val)
{
    string prefix = "(";
    string content;
    string suffix = ")";

    string str = "json::";
    str.append(k.key);
    content.append(str);
    content += ' ';
    content.append(output_value(val));

    string result = prefix + content + suffix;
    return result;
}

string output_object(Obj tree)
{
    string prefix = "(";
    string content;
    string suffix = ")";

    map<Key, Value> input = tree.data;
    for (map<Key, Value>::iterator it = input.begin(); it != input.end(); it++)
    {
        Key k = it->first;
        Value val = it->second;
        content.append(output_pair(k, val));
        content += '\n';
    }

    string result = prefix + content + suffix;
    return result;
}

void printSexp(Obj tree)
{
    cout << output_object(tree) << endl;
    return;
}