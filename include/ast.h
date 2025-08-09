#ifndef AST_H
#define AST_H

// THIS FILE DEFINES THE ABSTRACT SNTAX TREE

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Value;

struct Key
{
    string key;
};

inline bool operator<(const Key& lhs, const Key& rhs) {
    return lhs.key < rhs.key;
}

struct Obj
{
    map<Key, Value> data;
};

struct Value
{
    enum Type
    {
        Object,
        Array,
        String,
        Number,
        Boolean,
        Null
    };
    Type type;
    Obj object;
    vector<Value> array;
    string str;
    string number; // store the numbers as string only
    bool boolean;

    Value()
    {
        type = Null;
    }
};

#endif