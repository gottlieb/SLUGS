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

// This file is included since Microchip does not provide stdint.h as PART
// of the C30 compiler. This is NOT a full stdint.h implementation


#ifndef _STDINT_H_
#define _STDINT_H_

#define __WORDSIZE 16

#ifndef _INT8_T
#define _INT8_T
typedef int __attribute__((__mode__(QI))) int8_t;
#endif /*_INT8_T */

#ifndef _INT16_T
#define _INT16_T
typedef int __attribute__((__mode__(HI))) int16_t;
#endif /* _INT16_T */

#ifndef _INT32_T
#define _INT32_T
typedef int __attribute__((__mode__(SI))) int32_t;
#endif /* _INT32_T */

#ifndef _INT64_T
#define _INT64_T
typedef int __attribute__((__mode__(DI))) int64_t;
#endif /* _INT64_T */

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned int __attribute__((__mode__(QI))) uint8_t;
#endif /*_UINT8_T */

#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned int __attribute__((__mode__(HI))) uint16_t;
#endif /* _UINT16_T */

#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int __attribute__((__mode__(SI))) uint32_t;
#endif /* _UINT32_T */

#ifndef _UINT64_T
#define _UINT64_T
typedef unsigned int __attribute__((__mode__(DI))) uint64_t;
#endif /* _UINT64_T */


#ifndef _INTPTR_T
#define _INTPTR_T
typedef int16_t   intptr_t;
#endif /* _INTPTR_T */

#ifndef _UINTPTR_T
#define _UINTPTR_T
typedef int16_t   uintptr_t;
#endif /* _UINTPTR_T */



#endif /* _STDINT_H_ */
