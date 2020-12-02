# Delta M0

## What is this?

Delta M0 is a **basic, compact scientific calculator** based on an STM32F0
microcontroller.

It's far from fully featured, but it's getting there!

## How well does it work?

Great question! The software works fine on a breadboard prototype, but the
hardware is untested.

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
