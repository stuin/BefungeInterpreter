# Kagof Befunge-93 Interpreter

<p align="center"><img src="https://github.com/kagof/BefungeInterpreter/blob/master/BefungeInterpreter/Misc/icon.ico"></p>

# Current Version: 1.2.0

A C++/QT GUI interpreter for the Befunge-93 esoteric programming language. Tested and created on Windows 10 with QT version 5.7.1 & MinGW G++ 32bit compiler 5.3.0. Developed by Karl Goffin. Released under the MIT open source license. 

(c) 2016-2017 Karl Goffin.

## Screenshot

<p align="center"><img src="https://github.com/kagof/BefungeInterpreter/blob/master/Screenshots/kbfi1-0-1-screenshot-NumberGuesser.PNG"></p>

## Installing

There is a Windows installer for version 1.2.0 - built using [Inno Setup Compiler](http://www.jrsoftware.org/isinfo.php) 5.5.9 - hosted [here](https://github.com/kagof/BefungeInterpreter/tree/master/Installer) in this repo. Note that it is not recommended to download and run strange .exe files from the Internet, and your virus checker will probably not like this file, so it may be preferable to instead follow the build instructions. Checksums are also located in the Installer directory.

**Executable:** [kagof-bfi-setup-windows-1-2-0.exe](https://github.com/kagof/BefungeInterpreter/tree/master/Installer/kagof-bfi-setup-windows-1-2-0.exe)

## Building

The easiest way to build this project is to clone this repository and build it as a project in [QtCreator](https://www.qt.io/ide/). You will need Qt version 5.1 or greater, and a C++ compiler.

## Features

* GUI display - showing the source code, stack, an input field, and output.
* Start, debug, step, and slow modes for running Befunge programs
* Save/Load Befunge source code files
* Source code editing
* Program counter highlights the current instruction being carried out
* Three different ways to deal with unexpected characters (abort, ignore, reflect)
* Two ways of handling division by zero, and three for modulus by zero.

## Testing

This interpreter was tested against the Befunge-93 parts of the [Mycology test suite](https://github.com/Deewiant/Mycology), and the few test files in the [*eg* folder](https://github.com/catseye/Befunge-93/tree/master/eg) of the reference implementation.

## Differences from Canonical Befunge-93

This interpreter only accepts the traditional Befunge-93 instructions, however there are several differences.

* The playing field is not restricted to the original 80x25 torus. When a file is readied to be interpreted, its maximum width and height are found, and these are the boundaries of the playing field. Note that attempting to put characters outside of these boundaries with 'p' will result in the character not being placed.
* The way to deal with unsupported characters is not specified in the [official Befunge-93 specifications](http://catseye.tc/view/befunge-93/doc/Befunge-93.markdown), so three different versions have been provided:
	* **Abort** - program stops with an error message
	* **Ignore** - program continues over instruction (treats it as a NOP)
	* **Reflect** - program "bounces" back in opposite direction it was coming from
	
	Note that the [reference implementation](https://github.com/catseye/Befunge-93/blob/master/src/bef.c) of Befunge offers the first two options, and the [Mycology test suite](https://github.com/Deewiant/Mycology)'s [*sanity.bf*](https://github.com/Deewiant/Mycology/blob/master/sanity.bf) expects the last.
* The [reference implementation](https://github.com/catseye/Befunge-93/blob/master/src/bef.c) of Befunge-93 asks the user what input they wanted when a program attempts to perform a division by zero. This is further acknowledge as being the way BF-93 is meant to handle this in the [funge-98 specs](http://quadium.net/funge/spec98.html). However, this interpreter gives the option of asking for input (default), or pushing 0 to the stack upon encountering a division by zero.

	The reference implementation does not do anything to handle modulus by zero; in fact, it crashes when it encounters it. So, this interpreter gives three options for this: ask for input (default), push 0 to the stack, or crash, as traditional BF-93 does. Obviously, the third option is not recommended, but is included to better match the traditional specs.
* Integer and character input *only* accept an integer or character, respectively. Only a single character is accepted as character input in this version, although that will probably be changed in future versions.
* In the Befunge-93 specs, if a user attempts to perform a division by 0, the interpreter is supposed to ask what number the user wanted that to be. Right now, this interpreter just ignores it and moves on. This is expected to change in future versions.
* The size of characters and integers is not specified in the [official Befunge-93 specifications](http://catseye.tc/view/befunge-93/doc/Befunge-93.markdown). The stack in this interpreter stores information as chars, so the integers are contained in [-128,127], and overflows are allowed, as is shown in this fizzbuzz example:

<p align="center"><img src="https://github.com/kagof/BefungeInterpreter/blob/master/Screenshots/kbfi1-0-0-screenshot-fizzbuzz.PNG"></p>

## Sample Code

There are many sources of Befunge-93 code. This repository has a simple [helloworld.bf](https://github.com/kagof/BefungeInterpreter/blob/master/helloworld.bf) file to use. Other places to get some Befunge source code are:
* The [*eg* folder](https://github.com/catseye/Befunge-93/tree/master/eg) in the reference implementation. Many of these are "classic" Befunge programs.
* My own [Befunge Repo](https://github.com/kagof/BefungeRepo) contains Befunge programs written by me.

Of course, the best way to use Befunge is to write your own programs!

## Future Implementations

These features should be implemented in the future:
* Some pretty huge code refactoring is needed. Serves me right for not properly planning out the structure before I started programming this, but there is currently very high coupling between classes, and fairly low cohesion, so added any new features is becoming an increasing challenge.
* Foreground and background threads.
* Toggle whether to restrict playing field to 80x25 torus.
* Persistent reset button (to reset when partway through a run)
* customizable syntax highlighting colours, ability to turn syntax highlighting off.
* Allow input of longer strings, taking only first character, then the next, etc.
* Help in the software (tooltips and/or whats this).

## Version History

* Kagof Befunge-93 Interpreter v1.2.0
	- debug mode - click characters in run mode to add breakpoint.
	- minor bugfixes & improvements

* Kagof Befunge-93 Interpreter [v1.0.1](https://github.com/kagof/BefungeInterpreter/tree/d8da112cd4bf857b5876c451a327c14fa1712638)
    - bugfixes
	- stop button in start mode
	- syntax highlighting
	- reset button
	- handling of division by zero

* Kagof Befunge-93 Interpreter [v1.0.0](https://github.com/kagof/BefungeInterpreter/tree/08720162ecccd65ef653ac339eb89af98a8be23c)
	- initial release
	- there will be bugs

