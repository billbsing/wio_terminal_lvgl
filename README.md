# wio_terminal_lvgl

This project is a reference build to get the WioTerminal working
with the lvgl library.

The code was originally copied from [Seed_arduino_lvGL](https://github.com/Seeed-Studio/Seeed_Arduino_LvGL)
and examples from [LVGL](https://github.com/lvgl/lvgl)


## Setup

To setup this project first clone the github repo:

``` bash

    $ git clone https://github.com/billbsing/wio_terminal_lvgl.git
    $ cd wio_terminal_lvgl.git
```

You can now install the build environment and libraries:

```  bash
    $ ./getBuildEnviorment.sh
    $ ./getLibraries.sh
```

Build the project:

``` bash

    $ cd src
    $ make
    # upload the project
    $ make upload
```
