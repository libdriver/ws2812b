[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WS2812B
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ws2812b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

WS2812B is a intelligent control LED light source that the control circuit and RGB chip are integrated in a package of 5050 components.It internal include intelligent digital port data latch and signal reshaping amplification drive circuit.Also include a precision internal oscillator and a voltage programmable constant current control part, effectively ensuring the pixel point light color height consistent.The data transfer protocol use single NZR communication mode. After the pixel power-on reset, the DIN port receive data from controller, the first pixel collect initial 24bit data then sent to the internal data latch, the other data which
reshaping by the internal signal reshaping amplification circuit sent to the next cascade pixel through the DO port. After transmission for each pixel, the signal to reduce 24bit. pixel adopt auto reshaping transmit technology, making the pixel cascade number is not limited the signal transmission, only depend on the speed of signal transmission.RESET time>280μs , it won't cause wrong reset while interruption, it supports the lower frequency and inexpensive MCU.Refresh Frequency updates to 2KHz, Low Frame Frequency and No Flicker appear in HD Video Camera, it improve excellent display effect.LED with low driving voltage, environmental protection and energy saving, high brightness, scattering angle is large,good consistency, low power, long life and other advantages. The control chip integrated in LED above becoming more simple circuit, small volume, convenient installation.

LibDriver WS2812B is the full function driver of ws2812b  launched by LibDriver. WS2812B provides led writing and other functions. LibDriver complies with MISRA.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example write](#example-write)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver WS2812B source files.

/interface includes LibDriver WS2812B SPI platform independent template.

/test includes LibDriver WS2812B driver test code and this code can test the chip necessary function simply.

/example includes LibDriver WS2812B sample code.

/doc includes LibDriver WS2812B offline document.

/datasheet includes WS2812B datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example write

```C
#include "driver_ws2812b_basic.h"

uint8_t res;
uint32_t i;
static uint32_t gs_rgb[21]; 
static uint8_t gs_temp[1024];

/* init */
res = ws2812b_basic_init();
if (res != 0)
{
    return 1;
}

/* write color */
for (i = 0; i < 21; i++)
{
    gs_rgb[i] = color;
}

/* write data */
res = ws2812b_basic_write(gs_rgb, 21, gs_temp, 1024);
if (res != 0)
{
    (void)ws2812b_basic_deinit();

    return 1;
}

/* close the chip */
res = ws2812b_basic_deinit();
if (res != 0)
{
    return 1;
}
else
{
    return 0;
}
```

### Document

Online documents: [https://www.libdriver.com/docs/ws2812b/index.html](https://www.libdriver.com/docs/ws2812b/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.
