#!/usr/bin/python
# Copyright (c) 2014 Adafruit Industries
# Author: Tony DiCola
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import sys
import select

def pressEnter(timeout=1e-6):
    import sys
    import select

    """ See description of select in https://docs.python.org/2/library/select.html
    The first three arguments are 'waitable objects':
    rlist: wait until ready for reading
    wlist: wait until ready for writing
    xlist: wait for an "exceptional condition"
    the 4th argument is a timeout in seconds (a float number)
    see options for absent or zero timeout at the website
    When the timeout is reached without a file descriptor becoming ready,
    three empty lists are returned.
    """
    # timeout = 0.0001    # initial
    # timeout = 0.1
    # timeout = 1e-6      # 1 microsecond
    # timeout = 1e-9    # works, but I think that is overkill

    i,o,e = select.select([sys.stdin], [], [], timeout)
    for s in i:
        if s == sys.stdin:
            input = sys.stdin.readline()
            return True
    return False

# while not pressEnter():
#     print "Press Enter"
#     pass


# Can enable debug output by uncommenting:
#import logging
#logging.basicConfig(level=logging.DEBUG)

import Adafruit_BMP.BMP085 as BMP085
import time

def readBMP():
    # Default constructor will pick a default I2C bus.
    #
    # For the Raspberry Pi this means you should hook up to the only exposed I2C bus
    # from the main GPIO header and the library will figure out the bus number based
    # on the Pi's revision.
    #
    # For the Beaglebone Black the library will assume bus 1 by default, which is
    # exposed with SCL = P9_19 and SDA = P9_20.
    sensor = BMP085.BMP085()

    # Optionally you can override the bus number:
    #sensor = BMP085.BMP085(busnum=2)

    # You can also optionally change the BMP085 mode to one of BMP085_ULTRALOWPOWER,
    # BMP085_STANDARD, BMP085_HIGHRES, or BMP085_ULTRAHIGHRES.  See the BMP085
    # datasheet for more details on the meanings of each mode (accuracy and power
    # consumption are primarily the differences).  The default mode is STANDARD.
    #sensor = BMP085.BMP085(mode=BMP085.BMP085_ULTRAHIGHRES)

    print('Temp = {0:0.2f} *C'.format(sensor.read_temperature()))
    pressure_Pa = sensor.read_pressure()
    pressure_hPa = pressure_Pa / 100
    print('Pressure = {0:0.2f} hPa'.format(pressure_hPa))
    print('Altitude = {0:0.2f} m'.format(sensor.read_altitude()))
    print('Sealevel Pressure = {0:0.2f} Pa'.format(sensor.read_sealevel_pressure()))


def loopBMP(delay=0, timeout=0):
    # Default constructor will pick a default I2C bus.
    #
    # For the Raspberry Pi this means you should hook up to the only exposed I2C bus
    # from the main GPIO header and the library will figure out the bus number based
    # on the Pi's revision.
    #
    # For the Beaglebone Black the library will assume bus 1 by default, which is
    # exposed with SCL = P9_19 and SDA = P9_20.
    sensor = BMP085.BMP085()

    # Optionally you can override the bus number:
    #sensor = BMP085.BMP085(busnum=2)

    # You can also optionally change the BMP085 mode to one of BMP085_ULTRALOWPOWER,
    # BMP085_STANDARD, BMP085_HIGHRES, or BMP085_ULTRAHIGHRES.  See the BMP085
    # datasheet for more details on the meanings of each mode (accuracy and power
    # consumption are primarily the differences).  The default mode is STANDARD.
    #sensor = BMP085.BMP085(mode=BMP085.BMP085_ULTRAHIGHRES)

    start = time.time()

    ncycles = 0
    while True:
        ncycles += 1
        if delay > 0:
            time.sleep(delay)

        pressure_Pa = sensor.read_pressure()    # read the barometer BMP180
        # pressure_Pa = sensor.read_pressure()    # test: the second call
        # pressure_Pa = sensor.read_pressure()    # test: the third call

        i,o,e = select.select([sys.stdin], [], [], timeout)

        if len(i) > 0:
            break

    sys.stdin.readline()    # optional: read the <CR> hit to flush the stream

    end = time.time()
    dt = end - start
    frequency = float(ncycles) / float(dt)

    pressure_hPa = pressure_Pa / 100
    print('Last pressure = {0:0.2f} hPa'.format(pressure_hPa))

    print "\nDone {0:d} cycles during {1:0.1f} seconds. Frequency = {2:0.1f} Hz".format(ncycles, dt, frequency)


def plotBMP(delay=10, timeout=0):
    print "\nplotBMP: delay =", delay, "s"

    # Default constructor will pick a default I2C bus.
    #
    # For the Raspberry Pi this means you should hook up to the only exposed I2C bus
    # from the main GPIO header and the library will figure out the bus number based
    # on the Pi's revision.
    #
    # For the Beaglebone Black the library will assume bus 1 by default, which is
    # exposed with SCL = P9_19 and SDA = P9_20.
    sensor = BMP085.BMP085()

    # Optionally you can override the bus number:
    #sensor = BMP085.BMP085(busnum=2)

    # You can also optionally change the BMP085 mode to one of BMP085_ULTRALOWPOWER,
    # BMP085_STANDARD, BMP085_HIGHRES, or BMP085_ULTRAHIGHRES.  See the BMP085
    # datasheet for more details on the meanings of each mode (accuracy and power
    # consumption are primarily the differences).  The default mode is STANDARD.
    #sensor = BMP085.BMP085(mode=BMP085.BMP085_ULTRAHIGHRES)

    start = time.time()

    npoint = 0

    ncycles = 0
    while True:
        ncycles += 1
        if delay > 0:
            time.sleep(delay)
            print "\npoint", npoint
            npoint += 1
            readBMP()

        pressure_Pa = sensor.read_pressure()    # read the barometer BMP180
        # pressure_Pa = sensor.read_pressure()    # test: the second call
        # pressure_Pa = sensor.read_pressure()    # test: the third call

        i,o,e = select.select([sys.stdin], [], [], timeout)

        if len(i) > 0:
            break

    sys.stdin.readline()    # optional: read the <CR> hit to flush the stream

    end = time.time()
    dt = end - start
    frequency = float(ncycles) / float(dt)

    pressure_hPa = pressure_Pa / 100
    print('Last pressure = {0:0.2f} hPa'.format(pressure_hPa))

    print "\nDone {0:d} cycles during {1:0.1f} seconds. Frequency = {2:0.1f} Hz".format(ncycles, dt, frequency)


if __name__ == "__main__":

    print "Current state of BMP180:\n"
    readBMP()

    delay = 10
    if len(sys.argv) > 1:
        delay = float(sys.argv[1])

    timeout = 0
    if len(sys.argv) > 2:
        timeout = float(sys.argv[2])

    print "sleep delay =" , delay, "keyboard read timeout =", timeout

    print("\nAccess to pressure in loop. Press <Enter> to terminate.")
    # loopBMP(delay, timeout)
    plotBMP(delay, timeout)
