### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

spi pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

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

​          ws2812b is a basic command which can test all ws2812b driver function:

​           -i        show ws2812b chip and driver information.

​           -h       show ws2812b help.

​           -p       show ws2812b pin connections of the current board.

​           -t read <number> <times>       run ws2812b read test. number is the ws2812b chip number and times is the test times.

​           -c write <number> <color>       run ws2812b write function.number is the ws2812b chip number and color is the rgb color.

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
ws2812b: min temperature is -25.0C.
```

```shell
./ws2812b -p

ws2812b: SPI interface SCK connected to GPIO11(BCM).
ws2812b: SPI interface MISO connected to GPIO9(BCM).
ws2812b: SPI interface MOSI connected to GPIO10(BCM).
ws2812b: SPI interface CS connected to GPIO8(BCM).
```

```shell
./ws2812b -t read 12 10

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
./ws2812b -c write 12 16711680

ws2812b: number is 12 and written color is 0xFF0000.
```

```shell
./ws2812b -h

ws2812b -i
	show ws2812b chip and driver information.
ws2812b -h
	show ws2812b help.
ws2812b -p
	show ws2812b pin connections of the current board.
ws2812b -t read <number> <times>
	run ws2812b read test.number is the ws2812b chip number and times is the test times.
ws2812b -c write <number> <color>
	run ws2812b write function.number is the ws2812b chip number and color is the rgb color.
```

