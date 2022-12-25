### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ws2812b REQUIRED)
```


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
./ws2812b -i

ws2812b: chip is Worldsemi WS2812B.
ws2812b: manufacturer is Worldsemi .
ws2812b: interface is SPI.
ws2812b: driver version is 1.0.
ws2812b: min supply voltage is 3.7V.
ws2812b: max supply voltage is 5.3V.
ws2812b: max current is 16.00mA.
ws2812b: max temperature is 85.0C.
```

```shell
./ws2812b -p

ws2812b: SPI interface SCK connected to GPIO11(BCM).
ws2812b: SPI interface MISO connected to GPIO9(BCM).
ws2812b: SPI interface MOSI connected to GPIO10(BCM).
ws2812b: SPI interface CS connected to GPIO8(BCM).
```

```shell
./ws2812b -t write --number=12 --times=10

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
./ws2812b -e write --number=12 --color=16711680

ws2812b: number is 12 and written color is 0xFF0000.
```

```shell
./ws2812b -h

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

