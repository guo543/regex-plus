# regex-plus

A simple regular expression engine.

Now supports union "|", concat "1001" and Kleene star "*".
The symbols allowed are alphanumeric characters and the wildcard symbol '.'.

It will print out the syntax tree and the equivalent NFA (Nondeterministic Finite Automaton) by default for now.

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

Syntax Tree:
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

Generating NFA ...

NFA:
{
size = 28

q0 (entry state):
  Epsilon:
    q27
    q1

q1:
  Epsilon:
    q2
    q3

q2:
  Epsilon:
    q4
    q5

q3:
  Symbol 0:
    q6

q4:
  Epsilon:
    q7

q5:
  Symbol 1:
    q8

q6:
  Epsilon:
    q7

q7:
  Epsilon:
    q1
    q27

q8:
  Epsilon:
    q9

q9:
  Epsilon:
    q10
    q11

q10:
  Epsilon:
    q12

q11:
  Symbol 0:
    q13

q12:
  Symbol 1:
    q14

q13:
  Epsilon:
    q15

q14:
  Epsilon:
    q5
    q4

q15:
  Epsilon:
    q16
    q17

q16:
  Epsilon:
    q18

q17:
  Symbol 1:
    q19

q18:
  Epsilon:
    q20
    q21

q19:
  Epsilon:
    q17
    q16

q20:
  Epsilon:
    q22

q21:
  Symbol 0:
    q23

q22:
  Symbol 0:
    q24

q23:
  Epsilon:
    q25

q24:
  Epsilon:
    q11
    q10

q25:
  Symbol 0:
    q26

q26:
  Epsilon:
    q21
    q20

q27 (accept state):

}
```