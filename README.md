# SAIL to CGEN EvaluationTask
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
