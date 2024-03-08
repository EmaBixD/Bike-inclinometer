# [ESP32-bike-inclinometer](https://github.com/EmaBixD/ESP32-bike-inclinometer/)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

![preview](https://i.imgur.com/1w352k8.gif)

## Requierements
- DOIT ESP32 DEVKIT V1
- MPU6050
- GC9A01

![finished product](https://i.imgur.com/pNKJaol_d.webp?maxwidth=760&fidelity=grand)

## Setup

- Be sure to change the following settings within the `User_Setup.h` file to the `C:\Users\name\Documents\Arduino\libraries\TFT_eSPI` directory.

![folder image](https://i.imgur.com/OH7uUhl.png)

```sh
#define GC9A01_DRIVER
```

![#define 1 image](https://i.imgur.com/72G7aAP.png)

```sh
#define TFT_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 18
#define TFT_CS   22  // Chip select control pin
#define TFT_DC   16  // Data Command control pin
#define TFT_RST  4  // Reset pin (could connect to Arduino RESET pin)
```

![#define 2 image](https://i.imgur.com/sEBBDJk_d.webp?maxwidth=760&fidelity=grand)

## Libraries

> This code requires followings libraries (and relatives dependencies) to run:
> - TFT_eSPI
> - Adafruit_MPU6050

---
***Code is not optimized at all. If you find a way to do it better, please, let me know in comments 🤗***
