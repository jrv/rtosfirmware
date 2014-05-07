# Embedded software (firmware) for LaOs laser
RTOS experimental version

##Build setup, using MBED library and GCC

* Get your compiler here: https://launchpad.net/gcc-arm-embedded
* Download LaosLaser source
```
git clone https://github.com/jrv/rtosfirmware.git
```
* Download mbed libraries (latest version)
```
git clone https://github.com/mbedmicro/mbed
```
* Patch mbed libraries:
```
cd mbed/
patch -p1 < ../rtosfirmware/mbed.patch
```
* Set your full GCC path in mbed/workspace_tools/private_settings.py, for example:
```
GCC_ARM_PATH = "/home/jaap/LaOS/gcc-arm-none-eabi-4_8-2014q1/bin"
```
* In the mbed directory, build the MBED libraries:
```
python workspace_tools/build.py -m LPC1768 -t GCC_ARM -r -e -u -c
```
* Link LaOSlaser as an mbed example project
```
cd Firmware/mbed/libraries/tests/net/protocols/
ln -s  ../../../../../rtosfirmware .
```
* Build LaosLaser:
```
cd mbed
python workspace_tools/make.py -m LPC1768 -t GCC_ARM -n laser
```

*Read http://mbed.org/handbook/mbed-tools for more info*
