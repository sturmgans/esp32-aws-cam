# FSU-Eye

Frellie-Sees-You is a home survelleince project, intended to surveil your home with cameras.
This project part implements the Eye unit (imagination!) controllong the camera. It runs on a ESP32, connects to AWS and uploads images taken with its camera.

## Prerequsites

The following are confirmed working versions

- CMAKE 3.13 or higher
- Python 3.8.2 or higher
- AWS Cli 2
- Ninja 1.10.0

Python 2.7 should work, but if using Ubuntu 20.04 pip is no longer available, causing issues. This can be solved by ensuring Python3 is invoked through 'python' calls from PATH.

When running under Linux it may be required to symlink 'ninja' to 'ninja-build'.

### Notes

This project is based on AWS Demo Application, for more detailed prerequisite description please visit:
https://docs.aws.amazon.com/freertos/latest/userguide/getting_started_espressif.html

## Initialization

```bash
    git submodule update --init --recursive
```

## Build

The provided bash script can be used to build on Linux

```
./build.sh
```

## ESP32 Physical Connection

The physical connection to the ESP32-S can be done by connecting over UART using 3V3 logic, and powering it up with 5V. NOTE: During flashing the the pin IO0 needs to be connected to GND.

The pin connections to UART can be summarized as:
| ESP32-S | UART 3V3 Logic |
|---------|----------------|
|   GND   |      GND       |
|   U0R   |      TX        |
|   U0T   |      RX        |

In addition the power supply needs to connect:

| ESP32-S |  Power Supply |
|---------|---------------|
|   5V    |     5VGND     |

### Flashing

When flashing IO0 needs also to be connected to GND.

| ESP32-S | ESP32-S |
|---------|---------|
|   IO0   |   GND   |

Once the physical connection is setup you can flash using the provided bash script in the following way:

```
./build.sh flash
```

## Versioning

Git Tags are used in order to keep some kind of versioning of milestones. The format is  <MAJOR>.<MINOR>. Example on how to create and push a tag:

git tag -a 0.1 -m "Hello World!"

Once the tag is created it can be pushed to origin:

git push origin --tags
