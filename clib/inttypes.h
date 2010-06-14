
/*
The MIT License

Copyright (c) 2009 UCSC Autonomous Systems Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/


// This file is included since Microchip does not provide inttypes.h as PART
// of the C30 compiler. This is NOT a full inttypes.h implementation

#ifndef INTTYPES_H_INCL
#define INTTYPES_H_INCL 

#include <limits.h>
#include <stdint.h>

#define UINT8_MAX  UCHAR_MAX
#define INT8_MAX   SCHAR_MAX
#define INT8_MIN   SCHAR_MIN
#define UINT16_MAX USHRT_MAX
#define INT16_MAX  SHRT_MAX
#define INT16_MIN  SHRT_MIN
#define UINT32_MAX ULONG_MAX
#define INT32_MAX  LONG_MAX
#define INT32_MIN  LONG_MIN
#define UINT64_MAX ULLONG_MAX
#define INT64_MAX  LLONG_MAX
#define INT64_MIN  LLONG_MIN

#endif // #ifndef INTTYPES_H_INCL
