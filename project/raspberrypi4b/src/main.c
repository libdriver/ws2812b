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
#include <stdlib.h>

/**
 * @brief global var definition
 */
static uint32_t gs_rgb[21];                /**< rgb buffer */
static uint8_t gs_temp[1024];              /**< temp buffer*/

/**
 * @brief     ws2812b full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t ws2812b(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            ws2812b_info_t info;
            
            /* print ws2812b info */
            (void)ws2812b_info(&info);
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
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            ws2812b_interface_debug_print("ws2812b: SPI interface SCK connected to GPIO11(BCM).\n");
            ws2812b_interface_debug_print("ws2812b: SPI interface MISO connected to GPIO9(BCM).\n");
            ws2812b_interface_debug_print("ws2812b: SPI interface MOSI connected to GPIO10(BCM).\n");
            ws2812b_interface_debug_print("ws2812b: SPI interface CS connected to GPIO8(BCM).\n");
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show ws2812b help */

            help:
            
            ws2812b_interface_debug_print("ws2812b -i\n\tshow ws2812b chip and driver information.\n");
            ws2812b_interface_debug_print("ws2812b -h\n\tshow ws2812b help.\n");
            ws2812b_interface_debug_print("ws2812b -p\n\tshow ws2812b pin connections of the current board.\n");
            ws2812b_interface_debug_print("ws2812b -t read <number> <times>\n\trun ws2812b read test."
                                          "number is the ws2812b chip number and times is the test times.\n");
            ws2812b_interface_debug_print("ws2812b -c write <number> <color>\n\trun ws2812b write function."
                                          "number is the ws2812b chip number and color is the rgb color.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t num;
                uint32_t times;
                
                num = atoi(argv[3]);
                times = atoi(argv[4]);
                
                /* run read test */
                res = ws2812b_read_test(num, times);
                if (res != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 5;
            }
        }
        else if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("write", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i;
                uint32_t num;
                uint32_t color;
                
                /* get number */
                num = atoi(argv[3]);
                
                /* get color */
                color = atoi(argv[4]);
                
                /* check number */
                if (num > 21)
                {
                    num = 21;
                    ws2812b_interface_debug_print("ws2812b: num is over 21 and use 21.\n");
                }
                
                /* init */
                res = ws2812b_basic_init();
                if (res != 0)
                {
                    return 1;
                }
                
                /* write color */
                for (i = 0; i < num; i++)
                {
                    gs_rgb[i] = color;
                }
                
                /* print */
                ws2812b_interface_debug_print("ws2812b: number is %d and written color is 0x%X.\n", num, color);
                
                /* write data */
                res = ws2812b_basic_write(gs_rgb, num, gs_temp, 1024);
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
            else
            {
                return 5;
            }
        }
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = ws2812b(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        ws2812b_interface_debug_print("ws2812b: run failed.\n");
    }
    else if (res == 5)
    {
        ws2812b_interface_debug_print("ws2812b: param is invalid.\n");
    }
    else
    {
        ws2812b_interface_debug_print("ws2812b: unknow status code.\n");
    }

    return 0;
}
