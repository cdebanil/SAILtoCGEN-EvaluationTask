#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <stdexcept>
#include "ast.h"  

using namespace std;

void trim(string &s);
void simplifyString(string &input);
vector<string> tokenize(string input, char separator);

string parse_string(string &str);
string parse_number(string &str);
vector<Value> parse_array(string &str);
Value parse_value(string &str);
pair<Key, Value> parse_pair(string &s);
Obj parse_object(string &s);
Obj parse(string &str);

string output_value(Value val);
string output_pair(Key k, Value val);
string output_object(Obj tree);
void printSexp(Obj tree);

#endif