# Ray Tracer in C++

This repository contains code for a ray tracer that reads input from a text file and outputs an image that is described by that text file. The entire code base is implemented in C++ and uses no outside library at all (not even libraries for vectors and matrices). However, the it does use FreeImage to write a PNG file after the ray tracer is done.

# Disclaimer

Until attempting to write this ray tracer, I had never written code in C++. So, I apologize for all the memory leaks that I did not deal with. Additionally, I had never taken any formal course in College about graphics or worked with openGL before. So, please excuse my incorrect coding conventions.

# Usage

To use the ray trace, run:
```
./transform example_inputs/scene1.test
```
or
```
./transform example_inputs/scene5.test
```
etc.

# Platform requirements:

MacOS with gcc installed.
