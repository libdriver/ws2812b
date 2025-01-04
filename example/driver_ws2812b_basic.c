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
 * @file      driver_ws2812b_basic.c
 * @brief     driver ws2812b basic source file
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

#include "driver_ws2812b_basic.h"

static ws2812b_handle_t gs_handle;        /**< ws2812b handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ws2812b_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_WS2812B_LINK_INIT(&gs_handle, ws2812b_handle_t);
    DRIVER_WS2812B_LINK_SPI_10MHZ_INIT(&gs_handle, ws2812b_interface_spi_10mhz_init);
    DRIVER_WS2812B_LINK_SPI_DEINIT(&gs_handle, ws2812b_interface_spi_deinit);
    DRIVER_WS2812B_LINK_SPI_WRITE_COMMAND(&gs_handle, ws2812b_interface_spi_write_cmd);
    DRIVER_WS2812B_LINK_DELAY_MS(&gs_handle, ws2812b_interface_delay_ms);
    DRIVER_WS2812B_LINK_DEBUG_PRINT(&gs_handle, ws2812b_interface_debug_print);
    
    /* ws2812b initialization */
    res = ws2812b_init(&gs_handle);
    if (res != 0)
    {
        ws2812b_interface_debug_print("ws2812b: init failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write 
 * @param[in] *rgb pointer to a rgb color buffer
 * @param[in] len rgb length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ws2812b_basic_write(uint32_t *rgb, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    if (ws2812b_write(&gs_handle, rgb, len, temp, temp_len) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ws2812b_basic_deinit(void)
{
    if (ws2812b_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
