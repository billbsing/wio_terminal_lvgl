![testing](https://github.com/billbsing/wio_terminal_lvgl/workflows/testing/badge.svg)

# WioTerminal using the lvgl library


This project is a reference build to get the WioTerminal working
with the lvgl library.

This just creates three buttons on the bottom of the display, the
5 way switch left/right buttons changes focus, and click on the button.

If one of the 3 buttons at the top of the WioTerminal are pressed then one of the 3 lvgl buttons will be clicked.

The code was originally copied from [Seed_arduino_LvGL](https://github.com/Seeed-Studio/Seeed_Arduino_LvGL)
and examples from [lvgl](https://github.com/lvgl/lvgl) library.


## Setup

You first need to setup your arduino with the Seeed-Studio SAMD boards.
See [Getting started with Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/#software)

To setup this project first clone the github repo:

``` bash

    $ git clone https://github.com/billbsing/wio_terminal_lvgl.git

    # go to the cloned folder
    $ cd wio_terminal_lvgl
```

You can now install the build environment and libraries:

```  bash
    # download the arduino build scripts
    $ ./getBuildEnvironment.sh

    # get the supporting libraries for this project
    $ ./getLibraries.sh
```

Build the project:

``` bash

    # go to the src folder
    $ cd src

    # make the project
    $ make

    # upload the project
    $ make upload
```

To debug the events and see the debug messages, you can connect to the serial port using a terminal
at a baud rate of 1152000
