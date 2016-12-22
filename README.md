# Kagof Befunge-93 Interpreter

<p align="center"><img src="https://github.com/kagof/BefungeInterpreter/blob/master/BefungeInterpreter/Misc/icon.ico"></p>

# Current Version: 1.0.0

A C++/QT GUI interpreter for the Befunge-93 esoteric programming language. Tested and created on Windows 10 with QT version 5.7.0 & MinGW G++ 32bit compiler 5.3.0. Developed by Karl Goffin. Released under the MIT open source license. 

(c) 2016 Karl Goffin.

## Screenshot

<p align="center"><img src="https://github.com/kagof/BefungeInterpreter/blob/master/Screenshots/kbfi1-0-0-screenshot-NumberGuesser.PNG"></p>

## Installing

There is a Windows installer for version 1.0.0 - built using [Inno Setup Compiler](http://www.jrsoftware.org/isinfo.php) 5.5.9 - hosted [here](https://github.com/kagof/BefungeInterpreter/tree/master/Installer) in this repo. Note that it is not recommended to download and run strange .exe files from the Internet, and your virus checker will probably not like this file, so it may be preferable to instead follow the build instructions.

Executable: [kagof-bfi-setup-windows-1-0-0.exe](https://github.com/kagof/BefungeInterpreter/tree/master/Installer/kagof-bfi-setup-windows-1-0-0.exe)

## Building

The easiest way to build this project is to clone this repository and build it as a project in [QtCreator](https://www.qt.io/ide/). You will need Qt version 5.1 or greater, and a C++ compiler.

## Features

* GUI display - showing the source code, stack, an input field, and output.
* Start, step, and slow modes for running Befunge programs
* Save/Load Befunge source code files
* Source code editing
* Program counter highlights the current instruction being carried out
* Three different ways to deal with unexpected characters (abort, ignore, reflect)

## Testing

This interpreter was tested against the Befunge-93 parts of the [Mycology test suite](https://github.com/Deewiant/Mycology), and the few test files in the [*eg* folder](https://github.com/catseye/Befunge-93/tree/master/eg) of the reference implementation

## Differences from Canonical Befunge-93

This interpreter only accepts the traditional Befunge-93 instructions, however there are several differences.

* The playing field is not restricted to the original 80x25 torus. When a file is readied to be interpreted, its maximum width and height are found, and these are the boundaries of the playing field. Note that attempting to put characters outside of these boundaries with 'p' will result in the character not being placed.
* The way to deal with unsupported characters is not specified in the [official Befunge-93 specifications](http://catseye.tc/view/befunge-93/doc/Befunge-93.markdown), so three different versions have been provided:
	* **Abort** - program stops with an error message
	* **Ignore** - program continues over instruction (treats it as a NOP)
	* **Reflect** - program "bounces" back in opposite direction it was coming from
	
	Note that the [reference implementation](https://github.com/catseye/Befunge-93/blob/master/src/bef.c) of Befunge offers the first two options, and the [Mycology test suite](https://github.com/Deewiant/Mycology)'s [*sanity.bf*](https://github.com/Deewiant/Mycology/blob/master/sanity.bf) expects the last.
* Integer and character input *only* accept an integer or character, respectively. Only a single character is accepted as character input in this version.
* The size of characters and integers is not specified in the [official Befunge-93 specifications](http://catseye.tc/view/befunge-93/doc/Befunge-93.markdown), but they are undoubtedly smaller than what this interpreter allows.

## Sample Code

There are many sources of Befunge-93 code. This repository has a simple [helloworld.bf](https://github.com/kagof/BefungeInterpreter/blob/master/helloworld.bf) file to use. Other places to get some Befunge source code are:
* The [*eg* folder](https://github.com/catseye/Befunge-93/tree/master/eg) in the reference implementation. Many of these are "classic" Befunge programs.
* My own [Befunge Repo](https://github.com/kagof/BefungeRepo) contains Befunge programs written by me.

Of course, the best way to use Befunge is to write your own programs!

## Future Implementations

These features should be implemented in the future:
* Working keyboard shortcuts listed in the menus
* Toggle whether to restrict playing field to 80x25 torus
* Clickable "stop" button when running in "start" mode, instead of crashing on infinite loops
* Runtime timeout, for the same reason
* Syntax highlighting
* Allow input of longer strings, taking only first character, then the next, etc.
* Reset button. Currently the user must toggle between edit and run mode to reset the code torus.

## Version History

* Kagof Befunge-93 Interpreter v1.0.0
	- initial release
	- there will be bugs

