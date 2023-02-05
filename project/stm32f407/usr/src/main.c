/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-11-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/11/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ws2812b_write_test.h"
#include "driver_ws2812b_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                  /**< uart buffer */
volatile uint16_t g_len;             /**< uart buffer length */
static uint32_t gs_rgb[21];          /**< rgb buffer */
static uint8_t gs_temp[1024];        /**< temp buffer*/

/**
 * @brief     ws2812b full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ws2812b(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 1},
        {"number", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    uint32_t color = 16711680;
    uint32_t number = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* color */
            case 1 :
            {
                /* set the color */
                color = atol(optarg);
                
                break;
            }
            
            /* number */
            case 2 :
            {
                /* set the number */
                number = atoi(optarg);
                
                break;
            }

            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_write", type) == 0)
    {
        uint8_t res;
        
        /* run write test */
        res = ws2812b_write_test(number, times);
        if (res != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* check number */
        if (number > 21)
        {
            number = 21;
            ws2812b_interface_debug_print("ws2812b: num is over 21 and use 21.\n");
        }
        
        /* init */
        res = ws2812b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* write color */
        for (i = 0; i < number; i++)
        {
            gs_rgb[i] = color;
        }
        
        /* print */
        ws2812b_interface_debug_print("ws2812b: number is %d and written color is 0x%X.\n", number, color);
        
        /* write data */
        res = ws2812b_basic_write(gs_rgb, number, gs_temp, 1024);
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
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ws2812b_interface_debug_print("Usage:\n");
        ws2812b_interface_debug_print("  ws2812b (-i | --information)\n");
        ws2812b_interface_debug_print("  ws2812b (-h | --help)\n");
        ws2812b_interface_debug_print("  ws2812b (-p | --port)\n");
        ws2812b_interface_debug_print("  ws2812b (-t write | --test=write) [--number=<number>] [--times=<num>]\n");
        ws2812b_interface_debug_print("  ws2812b (-e write | --example=write) [--number=<number>] [--color=<color>]\n");
        ws2812b_interface_debug_print("\n");
        ws2812b_interface_debug_print("Options:\n");
        ws2812b_interface_debug_print("      --color=<color>                Set the chip display color.([default: 16711680])\n");
        ws2812b_interface_debug_print("  -e <write>, --example=<write>      Run the driver example.\n");
        ws2812b_interface_debug_print("  -h, --help                         Show the help.\n");
        ws2812b_interface_debug_print("  -i, --information                  Show the chip information.\n");
        ws2812b_interface_debug_print("      --number=<number>              Set the chip number.([default: 3])\n");
        ws2812b_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        ws2812b_interface_debug_print("  -t <write>, --test=<write>         Run the driver test.\n");
        ws2812b_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ws2812b_info_t info;
        
        /* print ws2812b info */
        ws2812b_info(&info);
        ws2812b_interface_debug_print("ws2812b: chip is %s.\n", info.chip_name);
        ws2812b_interface_debug_print("ws2812b: manufacturer is %s.\n", info.manufacturer_name);
        ws2812b_interface_debug_print("ws2812b: interface is %s.\n", info.interface);
        ws2812b_interface_debug_print("ws2812b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ws2812b_interface_debug_print("ws2812b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ws2812b_interface_debug_print("ws2812b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ws2812b_interface_debug_print("ws2812b: max current is %0.2fmA.\n", info.max_current_ma);
        ws2812b_interface_debug_print("ws2812b: max temperature is %0.1fC.\n", info.temperature_max);
        ws2812b_interface_debug_print("ws2812b: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ws2812b_interface_debug_print("ws2812b: SPI interface SCK connected to GPIOA PIN5.\n");
        ws2812b_interface_debug_print("ws2812b: SPI interface MISO connected to GPIOA PIN6.\n");
        ws2812b_interface_debug_print("ws2812b: SPI interface MOSI connected to GPIOA PIN7.\n");
        ws2812b_interface_debug_print("ws2812b: SPI interface CS connected to GPIOA PIN4.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register ws2812b function */
    shell_init();
    shell_register("ws2812b", ws2812b);
    uart_print("ws2812b: welcome to libdriver ws2812b.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ws2812b: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ws2812b: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ws2812b: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ws2812b: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ws2812b: param is invalid.\n");
            }
            else
            {
                uart_print("ws2812b: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
