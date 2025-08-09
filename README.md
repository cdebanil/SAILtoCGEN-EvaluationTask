# SAIL to CGEN Evaluation Task
Using any programming language/environment of your choice, make a program that reads in structured data in form of tables and nested trees (e.g., JSON, YAML) using a fixed format/schema and produces an S-expression representation of the same data. For example, provided YAML from https://en.wikipedia.org/wiki/YAML#Example the output would be:
```
((yaml:receipt "Oz-Ware Purchase Invoice")
(yaml:date (make-date 2012 08 06))
(yaml:customer (yaml:first_name "Dorothy") (yaml:family_name "Gale"))
(yaml:items (yaml:item (yaml:part_no 'A4786) (yaml:descrip "Water Bucket (Filled)") (yaml:price 1.47) (yaml:quantity 4))
(yaml:item (yaml:part_no 'E1628) (yaml:descrip "High Heeled \"Ruby\" Slippers") (yaml:size 8) (yaml:price 133.7) (yaml:quantity 1)))
...and so on...)
```
The specification of input format (any variation of JSON/YAML would do) and output format (any LISP/Scheme dialect would do) but should be well-defined (you're free to select the description schema yourself), and the transformation steps should show adherence to the conversion semantics (you're free to select the way to enforce it).

# Methodology 
- Since this is a coding challenge, I implemented a json parser myself instead of using a library.
- The json specification as described in https://www.json.org/json-en.html has been used.
- Strings are considered to be double-quoted, not single quoted, as per official json specification.
- Keys in the key-value pairs are assumed to be unique, although it isn’t required by the specification.
- Numbers are stored as strings. This is because -
    - The code simply parses numbers and there is no need to operate on them.
    - Data types such as int, double, long etc, have limits on the maximum or minimum value they can represent, because they use a fixed number of bits in memory.
    - Strings can store any character, and since there is no need to operate on the numbers, strings can be used to represent them, especially since strings can represent arbitrarily large numbers.

# Usage Instructions

You can compile using

```bash
make clean && make
```

You can execute using (inputFIles are the files with json data in them - you can test with dummy json files given in test folder in the github repo) 

```bash
./bin/jsontosexp inputFile1 inputFile2 ...
```

Example

```bash
$ ./bin/jsontosexp ./test/examplejson

 S-Expression for ./test/examplejson -

((json::glossary ((json::GlossDiv ((json::GlossList ((json::GlossEntry ((json::Abbrev "ISO 8879:1986")
(json::Acronym "SGML")
(json::GlossDef ((json::GlossSeeAlso ("GML") ("XML") )
(json::para "A meta-markup language, used to create markup languages such as DocBook.")
))
(json::GlossSee "markup")
(json::GlossTerm "Standard Generalized Markup Language")
(json::ID "SGML")
(json::SortAs "SGML")
))
))
(json::title "S")
))
(json::title "example glossary")
))
)
```

If the input is invalid it shows an error

```bash
$ ./bin/jsontosexp ./test/invalidjson
terminate called after throwing an instance of 'std::runtime_error'
  what():  Invalid json input  =>  "SGML" "Abbrev": "ISO 8879:1986"
Aborted (core dumped)
```