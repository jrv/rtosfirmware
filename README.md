# Embedded software (firmware) for LaOs laser
RTOS experimental version

==Build setup, using MBED library and GCC

* Get your compiler here: https://launchpad.net/gcc-arm-embedded
* Download LaosLaser source

> git clone https://github.com/LaosLaser/Firmware.git -b mbed-gcc

* Download mbed libraries (latest version)

> cd Firmware
> git clone https://github.com/mbedmicro/mbed

* Patch mbed libraries:

> cd mbed/
> patch -p1 < ../laser/mbed.patch

* Set your GCC path in Firmware/mbed/workspace_tools/private_settings.py, for example:

> GCC_ARM_PATH = "/usr/bin/"

* Build MBED libraries:

> python workspace_tools/build.py -m LPC1768 -t GCC_ARM -r -e -u -c

* Link LaOSlaser as an mbed example project

> cd Firmware/mbed/libraries/tests/net/protocols/
> ln -s  ../../../../../laser .

* Build LaosLaser:

> cd Firmware/mbed
> python workspace_tools/make.py -m LPC1768 -t GCC_ARM -n laser

*Read http://mbed.org/handbook/mbed-tools for more info*
