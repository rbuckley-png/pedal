# Pedal
by Buckly & Graves & Associates

Made using Daisy Seed.

# Building the Pedal

## Pre-reqs
Make sure you follow the [install guide](https://daisy.audio/tutorials/cpp-dev-env/). This will help you install all of the libraries required. 

Ensure you tweak the `Makefile` to point to the correct directories for your dependencies
```make
...
# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP
...
```
## Building and flashing

```
make clean
make 
sudo make program-dfu
```

Make sure that your daisy is put into bootloader mode when running that last command.

# Hot Swappable Pedal System
The ultimate goal is to create a set of guitar pedals with a partially open face for the daisy to slot in. The Daisy Seed should know what recepticle its in and change the effect and pin mapping accoringly.

