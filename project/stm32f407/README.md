### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. WS2812B

#### 3.1 Command Instruction

1. Show ws2812b chip and driver information.

   ```shell
   ws2812b (-i | --information)
   ```

2. Show ws2812b help.

   ```shell
   ws2812b (-h | --help)
   ```

3. Show ws2812b pin connections of the current board.

   ```shell
   ws2812b (-p | --port)
   ```

4. Run ws2812b write test, number is the ws2812b chip number and num is the test times.

   ```shell
   ws2812b (-t write | --test=write) [--number=<number>] [--times=<num>]
   ```

5. Run ws2812b write function, number is the ws2812b chip number and color is the rgb color.

   ```shell
   ws2812b (-e write | --example=write) [--number=<number>] [--color=<color>]
   ```

#### 3.2 Command Example

```shell
ws2812b -i

ws2812b: chip is Worldsemi WS2812B.
ws2812b: manufacturer is Worldsemi .
ws2812b: interface is SPI.
ws2812b: driver version is 1.0.
ws2812b: min supply voltage is 3.7V.
ws2812b: max supply voltage is 5.3V.
ws2812b: max current is 16.00mA.
ws2812b: max temperature is 85.0C.
ws2812b: min temperature is -25.0C.
```

```shell
ws2812b -p

ws2812b: SPI interface SCK connected to GPIOA PIN5.
ws2812b: SPI interface MISO connected to GPIOA PIN6.
ws2812b: SPI interface MOSI connected to GPIOA PIN7.
ws2812b: SPI interface CS connected to GPIOA PIN4.
```

```shell
ws2812b -t write --number=12 --times=10

ws2812b: chip is Worldsemi WS2812B.
ws2812b: manufacturer is Worldsemi .
ws2812b: interface is SPI.
ws2812b: driver version is 1.0.
ws2812b: min supply voltage is 3.7V.
ws2812b: max supply voltage is 5.3V.
ws2812b: max current is 16.00mA.
ws2812b: max temperature is 85.0C.
ws2812b: min temperature is -25.0C.
ws2812b: start register test.
ws2812b: 1/10 times.
ws2812b: 2/10 times.
ws2812b: 3/10 times.
ws2812b: 4/10 times.
ws2812b: 5/10 times.
ws2812b: 6/10 times.
ws2812b: 7/10 times.
ws2812b: 8/10 times.
ws2812b: 9/10 times.
ws2812b: 10/10 times.
ws2812b: finish register test.
```

```shell
ws2812b -e write --number=12 --color=16711680

ws2812b: number is 12 and written color is 0xFF0000.
```

```shell
ws2812b -h

Usage:
  ws2812b (-i | --information)
  ws2812b (-h | --help)
  ws2812b (-p | --port)
  ws2812b (-t write | --test=write) [--number=<number>] [--times=<num>]
  ws2812b (-e write | --example=write) [--number=<number>] [--color=<color>]

Options:
      --color=<color>                Set the chip display color.([default: 16711680])
  -e <write>, --example=<write>      Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --number=<number>              Set the chip number.([default: 3])
  -p, --port                         Display the pin connections of the current board.
  -t <write>, --test=<write>         Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

