# Questions

## What's `stdint.h`?

A header file that declares sets of integer types with specified wideths, and defines corresponding sets of macros. Defines macros
that specify limits of integer types corresponding to types defined in other standard headers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Preserve correct numerical values of various properties.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2, respectively.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats
## (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is the size in bits of the bitmap file.

## What does it mean if `biHeight` is negative?

The bitmap is a top-down DIB and the origin starts in the upper-left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The OS might fail to open fiven file for reasons like invalid name

## Why is the third argument to `fread` always `1` in our code?

There's only 1 file header and info header sizeof() returns number of bytes necessary to store entire structure

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Sets file position indicator for the file stream to the value pointed to by offset

## What is `SEEK_CUR`?

Flag that determines originating position of fseek file op.

## Whodunit?

It was Professor Plum with the candlestick in the library.
