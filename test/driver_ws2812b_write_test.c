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
 * @file      driver_ws2812b_write_test.c
 * @brief     driver ws2812b write test source file
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
#include <stdlib.h>

static ws2812b_handle_t gs_handle;        /**< ws2812b handle */
static uint8_t gs_buffer[1024];           /**< inner temp buffer */
static uint32_t gs_rgb[21];               /**< inner rgb buffer */

/**
 * @brief     write test
 * @param[in] cnt number of the ws2812b led
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ws2812b_write_test(uint32_t cnt, uint32_t times)
{
    uint8_t res;
    uint32_t num;
    uint32_t i, j;
    ws2812b_info_t info;
    const uint32_t color[7] = {0xFF0000U, 0xFF7F00U, 0xFFFF00U, 0x00FF00U, 0x00FFFFU, 0x0000FFU, 0x8F00FFU};
    
    /* link interface function */
    DRIVER_WS2812B_LINK_INIT(&gs_handle, ws2812b_handle_t);
    DRIVER_WS2812B_LINK_SPI_10MHZ_INIT(&gs_handle, ws2812b_interface_spi_10mhz_init);
    DRIVER_WS2812B_LINK_SPI_DEINIT(&gs_handle, ws2812b_interface_spi_deinit);
    DRIVER_WS2812B_LINK_SPI_WRITE_COMMAND(&gs_handle, ws2812b_interface_spi_write_cmd);
    DRIVER_WS2812B_LINK_DELAY_MS(&gs_handle, ws2812b_interface_delay_ms);
    DRIVER_WS2812B_LINK_DEBUG_PRINT(&gs_handle, ws2812b_interface_debug_print);;
    
    /* get information */
    res = ws2812b_info(&info);
    if (res != 0)
    {
        ws2812b_interface_debug_print("ws2812b: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        ws2812b_interface_debug_print("ws2812b: chip is %s.\n", info.chip_name);
        ws2812b_interface_debug_print("ws2812b: manufacturer is %s.\n", info.manufacturer_name);
        ws2812b_interface_debug_print("ws2812b: interface is %s.\n", info.interface);
        ws2812b_interface_debug_print("ws2812b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ws2812b_interface_debug_print("ws2812b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ws2812b_interface_debug_print("ws2812b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ws2812b_interface_debug_print("ws2812b: max current is %0.2fmA.\n", info.max_current_ma);
        ws2812b_interface_debug_print("ws2812b: max temperature is %0.1fC.\n", info.temperature_max);
        ws2812b_interface_debug_print("ws2812b: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* check cnt */
    if (cnt == 0)
    {
        ws2812b_interface_debug_print("ws2812b: cnt can't be 0.\n");
        
        return 1;
    }
    if (cnt > 21)
    {
        ws2812b_interface_debug_print("ws2812b: cnt is over 21 and use 21.\n");
    }
    
    /* start register test */
    ws2812b_interface_debug_print("ws2812b: start register test.\n");
    
    /* ws2812b initialization */
    res = ws2812b_init(&gs_handle);
    if (res != 0)
    {
        ws2812b_interface_debug_print("ws2812b: init failed.\n");
       
        return 1;
    }
    
    /* set number */
    num = cnt > 21 ? 21 : cnt;
    
    for (i = 0; i < times; i++)
    {
        for (j = 0; j < num; j++)
        {
            gs_rgb[j] = color[i % 7];
        }
        res = ws2812b_write(&gs_handle, (uint32_t *)gs_rgb, num, gs_buffer, 1024);
        if (res != 0)
        {
            ws2812b_interface_debug_print("ws2812b: write failed.\n");
            (void)ws2812b_deinit(&gs_handle);
           
            return 1;
        }
        
        /* delay 1000 ms */
        ws2812b_interface_delay_ms(1000);
        
        /* output */
        ws2812b_interface_debug_print("ws2812b: %d/%d times.\n", i + 1, times);
    }
    
    /* close all LEDs */
    for (j = 0; j < num; j++)
    {
        gs_rgb[j] = 0x00;
    }
    res = ws2812b_write(&gs_handle, (uint32_t *)gs_rgb, num, gs_buffer, 1024);
    if (res != 0)
    {
        ws2812b_interface_debug_print("ws2812b: write failed.\n");
        (void)ws2812b_deinit(&gs_handle);
       
        return 1;
    }
    
    /* finish register test */
    ws2812b_interface_debug_print("ws2812b: finish register test.\n");
    
    /* close the chip */
    (void)ws2812b_deinit(&gs_handle);
    
    return 0;
}
