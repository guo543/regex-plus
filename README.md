# regex-plus

A simple regular expression engine.
Now supports union "|", concat "1001" and Kleene star "*".
The symbols allowed are alphanumeric characters and the wildcard symbol '.'.

It will print out the syntax tree by default for now.

Generate make files:
```
mkdir build
cd build
cmake ..
```

Build with cmake:
```
cmake --build .
```
or simply
```
make
```

Sample usage:
```
./regexp "(0|(1(01*(00)*0)*1)*)*"
```
output:
```
Parser: { source = (0|(1(01*(00)*0)*1)*)* }

SyntaxTree: 
{
KleeneStar:
---Union:
------Symbol: 0
------KleeneStar:
---------Concat:
------------Symbol: 1
------------KleeneStar:
---------------Concat:
------------------Symbol: 0
------------------KleeneStar:
---------------------Symbol: 1
------------------KleeneStar:
---------------------Concat:
------------------------Symbol: 0
------------------------Symbol: 0
------------------Symbol: 0
------------Symbol: 1
}
```