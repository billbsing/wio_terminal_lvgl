# wio_terminal_lvgl

This project is a reference build to get the WioTerminal working
with the lvgl library.

This just creates three buttons on the bottom of the display, the
5 way switch left/right buttons changes focus, and click on the button.

The 3 buttons at the top select one of the 3 lvgl buttons. 

The code was originally copied from [Seed_arduino_lvGL](https://github.com/Seeed-Studio/Seeed_Arduino_LvGL)
and examples from [lvgl](https://github.com/lvgl/lvgl)


## Setup

To setup this project first clone the github repo:

``` bash

    $ git clone https://github.com/billbsing/wio_terminal_lvgl.git
    # go to the cloned folder
    $ cd wio_terminal_lvgl.git
```

You can now install the build environment and libraries:

```  bash
    # download the arduino build scripts
    $ ./getBuildEnvironment.sh
    # get the lvgl library
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
