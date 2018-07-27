# Indent style

This document explains the codestyle that the Aurora Framework uses. We use this rules to keep our code spaghetti safe and with a better look.

## Aurora Codestyle Specification
This specification is based on K&R variants: 1TBS, Stroustrup, Linux kernel and BSD KNF codestyles.

<!-- TOC depthFrom:3 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Comments](#comments)
	- [Initial Comments](#initial-comments)
	- [Documentation Comments](#documentation-comments)
	- [Code Comments](#code-comments)
- [Naming](#naming)
	- [Types](#types)
	- [Functions](#functions)
	- [Objects and Variables](#objects-and-variables)
	- [Acronyms](#acronyms)
- [Lines](#lines)
	- [Length](#length)
	- [Ending](#ending)
- [File encoding](#file-encodig)
- [Braces](#braces)
- [Tab idention](#tab-idention)
	- [Single and multiple statements](#single-and-multiple-statements)
- [Spaces](#spaces)
	- [Pointers](#pointers)
- [Headers](#headers)

<!-- /TOC -->

### Comments
In Aurora code files, we have a very well defined anatomy for comment blocks. You have three types of comments: the initial comments, documentation comments and code comments. All of them need to be written in English and well explained for easier development of other programmers that want to contribute to the project.

#### Initial Comments
Initial comments have general information about the file and should be present on ALL source code files. We have a boilerplate for C-like languages and languages that have `#` as 'keyword' for comment blocks. Depending on the license of the repository, you should use GPL-3.0 and LGPL-3.0 boilerplates. You can find them [here](BOILERPLATES.md).


#### Documentation Comments
To compile our documentation we use Doxygen, which uses JavaDoc Style for C-like languages and Doxygen style for other languages as a comment standard for automatically code structure detection. When you write a code file you should use this structure on header files:
```cpp
/** Example comment
 * Another comment
 *
 */
```
or this, in case of a non C-like language:
```cmake
## Example comment
# Another comment
#
```

You should use special commands so Doxygen knows what you want to do with the comment. Here are some useful and most used commands: 
- `@file`
- `@param`
- `@return`
- `@see`
- `@author`

You can find the full list [here](http://www.stack.nl/~dimitri/doxygen/manual/commands.html).

For better codestyle we activated the `JAVADOC_AUTOBRIEF`, which means that you can automatically initialize a brief description ending with a first dot followed by a space or a new line. For example:
```cpp
/** Brief description which ends at this dot. Details follow
 * here.
 */
```
**Note:** Because of the aesthetics, use the brief in the first line (follow the example) whenever possible.

Each file must have a brief description, a `@file` tag, which has a partial path of the file and a `@since` tag to determinate when this file was created (framework version). It can also have the general author and contributers of the file, using `@author` or `@authors`.

`@file` tag must have this syntax: `module-name/src/File.cpp` or `AuroraFW/Module/Header.h`.

Each function must have an initial comment which explains:
- What its purpose or use is.
- What arguments it requires or accepts and what their use is.
- What value(s) the function returns.
- The version number of the framework since the first implementation.

It can also have the creator of the function, but its not mandatory.

In these comments you should use a formal and clear language, because the purpose of those comments are to automatically create the documentation reference of the framework.

Here is a practical example of a documentation comment:
```cpp
/** Constructs a vector with the given coordinates.
 * @param x The x value for the x coordinate.
 * @param y The y value for the y coordinate.
 * @see Vector2D( )
 * @see Vector2D(float )
 */
```
You can see the result [here](https://aurora-fw.github.io/docs/reference/snapshot/d7/dc9/structAuroraFW_1_1Math_1_1Vector2D.html#aa1573e1f3c75fae2b0e8ebcbd3a59adc).

You can also use single comments for documentation: `///`.

#### Code Comments
These types of comments can be used on headers and source files. The purpose of these comments is to help people understand an instruction or even a block of code. We use the common syntax of a comment: `//` and:
```cpp
/*
block comments
*/
```
Here you just need to be clear on what you want to explain to the programmer, so no formal language is needed and, for better communication, use easy words.

### Naming
To name our code we use typical methods adopted in programming to know what's the type of the instructions used. We use a different name idention for types, functions and objects/variables.

#### Types
For types such as a `class`, `struct`, `typedef`, `enum`, `namespace`, etc, you should use PascalCase, which means that the first letter of each concatenated word is capitalized. Here are some examples:

- `BackColor`
- `TimeUtc`
- `Timer`

#### Functions
For functions you should use camelCase, which means that the first word is in lowercase and the rest of the words start with a capital letter. Here are some examples:
- `getName()`
- `setName()`
- `isNull()`

#### Objects and Variables
For objects or variables we write them in lowercase. Specifically, for private members use an `_` at the begin.

**Note**: Words that are already assigned by the language (keywords) should have an `_` at the end.

#### Acronyms
If the first letter is uppercase then the whole acronym should have uppercase letters. Else if the first letter is lowercase then the whole acronym should have lowercase letters. Here are some examples:
- `ASCIIArt`
- `asciiArt`

### Lines
Line structure is important for programmers. If lines are separated and with a length limit, code readability is improved and the development workflow is way better. It's important that blank lines exist and may be added to separate different blocks of code. It doesn't affect the compiler in any way, so there's no excuse for not using them.

#### Length
When talking about soft limit, the lines should not pass 80 characters. For hard limit, lines must not pass 120 characters.

#### Ending
For line ending we use Unix LF (linefeed). If you are developing on Windows, you should use a linefeed compatible editor.

### File encoding
You must use 8-bit unicode, UTF-8.

### Braces
If it's a function, don't open braces in the same line as the declarations, else please open it in the same line. To close braces you must always do it in a new line, unless its has no body.

#### Single and multiple statements
Do not unnecessarily use braces where a single statement will do.
```cpp
if (condition)
	action();
```
and
```cpp
if (condition)
	do_this();
else
	do_that();
```

This does not apply if only one branch of a conditional statement is a single statement; in the latter case use braces in both branches:
```cpp
if (condition) {
	do_this();
	do_that();
} else {
	otherwise();
}
```

### Tab idention
Use tab instead of spaces for tab idention, if supported in the language, and configure your editor for 4 spaces in a single tab. Then, for alignment, use spaces. This helps to reduce significantly the project size.

### Spaces
Use a space after these keywords: `if`, `switch`, `case`, `for`, `do`, `while`, but not with `sizeof`, `typeof`, `alignof`, or `__attribute__`. Also don't add spaces around (inside) parenthesized expressions.

#### Pointers
When declaring pointer data or a function that returns a pointer type, the preferred use of * is adjacent to the type name and not adjacent to the data or function name. For example:
```cpp
char* name;
unsigned int memory(char* ptr, char** retptr);
char* convert(string* s);
```

### Headers
In header files, you should write functions without argument names, or if needed, use very short names, like `s`, `t`, `str`, `n`, `i`, etc.
Always use the global header on ALL headers (`AuroraFW/Global.h`). Use aurora defined data types, like `ArInt_t`, `ArInt8_t`, etc.

### Macros
Names of macros defining constants and labels in enums are capitalized.
Enums are preferred when defining several related constants.
CAPITALIZED macro names are appreciated but macros resembling functions may be named in lower case.
Generally, inline functions are preferable to macros resembling functions.

Macros with multiple statements should be enclosed in a do - while block:
```cpp
#define macrofun(a, b, c)    \
	do {                     \
		if (a == 5)          \
		do_this(b, c);       \
	} while (0)
```

Global macros must be defined on headers and shouldn't be used on source files (only if strictly needed).