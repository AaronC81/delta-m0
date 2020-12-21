# Delta M0

## What is this?

Delta M0 is a **basic, compact scientific calculator** based on an STM32F0
microcontroller.

![My hand holding the Delta M0, showing the result of 2 plus 2.](img/holding.jpg)

![The front of the Delta M0. It has a matrix of 4 columns and 5 rows of buttons, a small OLED display, a power switch on the side, and a 6-pin serial programming header on the top.](img/front.jpg)

![The back of the Delta M0. It has a JST battery connector on the top, a battery controller IC, an STM32 microcontroller, and some supporting passive components.](img/back.jpg)

## How well does it work?

It does _work_, but you probably don't want to use it as an actual calculator
yet. The software is really lacking.

## Project structure

This is based off the
[libopencm3 template](https://github.com/libopencm3/libopencm3-template).

  - `my-project` contains the C code for the firmware.
  - `test` is a small set of unit tests which you can run with `./test/run`.
  - `hardware` contains the KiCad files for the PCB. 

# Building

Make sure you clone with `--recurse-submodules`!

Then:

```
make -C libopencm3
make -C my-project
```
