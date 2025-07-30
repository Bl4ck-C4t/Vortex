## Summary
This is a thesis project for ELSYS. An interpretative programming language called 'Vortex'

## Installation
For installation on Linux systems, a C++ compiler supporting version 20 or higher is required, programs: “bison” 3.4 or higher and “flex” 2.6.4 or higher. 
To compile the entire project, it is only necessary to execute the ‘make all’ command. The interpreter will be located in the ‘out’ directory under the name ‘vortex’.

## Language usage documentation
The ‘examples’ folder contains examples of using any parts of the language. Files can be imported into others using the keyword ‘import <filepath>’.

## Standard library
For input and output, the standard functions `input(<string text>)` for input and `print(<any value>)` for output to the console are used. 

### Other functions:

`exit()` - For exiting the program
`toString(<expression>)` - for converting a value to a text string. Only basic types can be converted to text strings. To override this function in user-created classes, the `fn toString() -> string {...}` method must be implemented in the corresponding class.
## Variables

The language supports the following data types:<br>
**integer**: 2,3,4,5<br>
**float**: 2.56, 3.14….<br>
**char**: ‘a’, ‘b’...<br>
**string**: “hello world”, ‘person’...<br>
**bool**: true, false<br>

Variables are defined in two ways:<br>
`a = 10; or int a = 10;`
It is also possible to create variables whose value can be changed to any type, using:
`any a = 10; a = ‘c’;`

## Arithmetic
The following operations are supported for each data type:<br>

|    |int | char | float | string | bool |
|----|------|-------|--------|------|-----|
|int | +,-,/,*,**,-(uminus)| | +,-,/,*,**,-(uminus) | | |
|char | | + | | +| |
|float | +,-,/,*,**,-(uminus)| | +,-,/,*,**,-(uminus) | | |
|string | | + | | +| |
|bool | 

## Conditions
Conditions are used in the following way:<br>
```
if(n > 1){
  ret n * fact(n-1); }
  else{
  ret 4;
}
```
The condition can also be written without “else”

## Functions
Functions are defined using the keyword “fn” in the following way `fn <name>(<arguments>) -> <return_type> { body… }`. 
When the return type is “void”, it is mandatory to use `ret;` when exiting the function. 
With `ret <value>;` the function is exited and a value is returned. Recursion is supported.

## Classes and vectors
A class is defined by `class <classname> [extends <class, .. class>] { body... }`
A class instance is created by calling the class name to call the corresponding constructor `new <classname>()`
A class is inherited by using the word “extends”.
If a method/member variable already exists in the inheritor, the given method/member variable will not be added to the inheritor. Multiple inheritance is supported. 
The keyword ‘this’ is the instance on which a method is called.

## Example definition and use of classes:
```
class Person{
  int age;
  string name;
  
  fn construct(int age, string name) -> void{
    this.age = age;
    this.name = name;
    ret;
  }
  
  fn getAge() -> int{
    ret this.age;
  }
  
  fn getName() -> string{
    ret this.name;
  }
}

class God extends Person {
  object powers;
  fn construct(int age, string name, object pows) -> void{
    this.age = age;
    this.name = name;
    this.powers = pows;
    ret;
  }
  
  fn getPowers() -> object {
    ret this.powers;
  }

}

p1 = new Person(18, “Stefan”);
stela = new God(9000, “Stela”, [“Boi s kabeli”]);

stela.getPowers()
p1.getAge()
///////

A vector is created using square brackets. For example:
//////
a = []
b = [2,3,4]
///////
Vectors have a method to add an element ‘push’ and to remove an element by index ‘remove’, ‘reverse’ - to reverse the array in the reverse order of the elements, ‘len’ - the total number of elements.
It is also possible to call methods on copies of objects. This is useful in cases where we do not want to change the original. The syntax for this is to use two “.” instead of one, when calling a method:
///
а = [2,3,4];
b = a..reverse();
-- b is [4,3,2]
-- a remains [2,3,4]
///
To access an element, square brackets are used in the following way:
/////
a = [2]
a.push(5);
a.push(10);
a.remove(2);
a[1] /// returns 2
//////
```
## Loops
A loop is defined by `loop{if(<boolean_condition>) {... break;} }`
Example:
```
int a = 0;
loop{
  a = a + 1;
  if(a == 10) {
    break;
  }
}
```

## Using the interpreter
The interpreter has 2 modes of operation: Reading and executing from a file and interpretive mode. To enter interpretive mode, use: `vortex -`, and to execute a file: `vortex <filename>`
