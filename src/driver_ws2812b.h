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
 * @file      driver_ws2812b.h
 * @brief     driver ws2812b header file
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

#ifndef DRIVER_WS2812B_H
#define DRIVER_WS2812B_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ws2812b_driver ws2812b driver function
 * @brief    ws2812b driver modules
 * @{
 */

/**
 * @addtogroup ws2812b_base_driver
 * @{
 */

/**
 * @brief ws2812b each reset bit frame length definition
 */
#ifndef WS2812B_EACH_RESET_BIT_FRAME_LEN
    #define WS2812B_EACH_RESET_BIT_FRAME_LEN        512        /**< 512 */
#endif

/**
 * @brief ws2812b handle structure definition
 */
typedef struct ws2812b_handle_s
{
    uint8_t (*spi_10mhz_init)(void);                             /**< point to a spi_10mhz_init function address */
    uint8_t (*spi_deinit)(void);                                 /**< point to a spi_deinit function address */
    uint8_t (*spi_write_cmd)(uint8_t *buf, uint16_t len);        /**< point to a spi_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                               /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);             /**< point to a debug_print function address */
    uint8_t inited;                                              /**< inited flag */
} ws2812b_handle_t;

/**
 * @brief ws2812b information structure definition
 */
typedef struct ws2812b_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ws2812b_info_t;

/**
 * @}
 */

/**
 * @defgroup ws2812b_link_driver ws2812b link driver function
 * @brief    ws2812b link driver modules
 * @ingroup  ws2812b_driver
 * @{
 */

/**
 * @brief     initialize ws2812b_handle_t structure
 * @param[in] HANDLE pointer to a ws2812b handle structure
 * @param[in] STRUCTURE ws2812b_handle_t
 * @note      none
 */
#define DRIVER_WS2812B_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_10mhz_init function
 * @param[in] HANDLE pointer to a ws2812b handle structure
 * @param[in] FUC pointer to a spi_10mhz_init function address
 * @note      none
 */
#define DRIVER_WS2812B_LINK_SPI_10MHZ_INIT(HANDLE, FUC)          (HANDLE)->spi_10mhz_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to a ws2812b handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_WS2812B_LINK_SPI_DEINIT(HANDLE, FUC)              (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write_cmd function
 * @param[in] HANDLE pointer to a ws2812b handle structure
 * @param[in] FUC pointer to a spi_write_cmd function address
 * @note      none
 */
#define DRIVER_WS2812B_LINK_SPI_WRITE_COMMAND(HANDLE, FUC)       (HANDLE)->spi_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a ws2812b handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_WS2812B_LINK_DELAY_MS(HANDLE, FUC)                (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a ws2812b handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_WS2812B_LINK_DEBUG_PRINT(HANDLE, FUC)             (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ws2812b_base_driver ws2812b base driver function
 * @brief    ws2812b base driver modules
 * @ingroup  ws2812b_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a ws2812b info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ws2812b_info(ws2812b_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a ws2812b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t ws2812b_init(ws2812b_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a ws2812b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ws2812b_deinit(ws2812b_handle_t *handle);

/**
 * @brief     write reset and color frame
 * @param[in] *handle pointer to a ws2812b handle structure
 * @param[in] *rgb pointer to a rgb color buffer
 * @param[in] len rgb length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 rgb is null
 *            - 5 temp is null
 *            - 6 temp buffer is too small
 * @note      none
 */
uint8_t ws2812b_write(ws2812b_handle_t *handle, uint32_t *rgb, uint32_t len, uint8_t *temp, uint32_t temp_len);

/**
 * @brief     write the reset frame
 * @param[in] *handle pointer to a ws2812b handle structure
 * @param[in] len rgb length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 temp is null
 *            - 5 temp buffer is too small
 * @note      none
 */
uint8_t ws2812b_write_only_reset(ws2812b_handle_t *handle, uint32_t len, uint8_t *temp, uint32_t temp_len);

/**
 * @brief     write the color frame
 * @param[in] *handle pointer to a ws2812b handle structure
 * @param[in] *rgb pointer to a rgb color buffer
 * @param[in] len rgb length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 rgb is null
 *            - 5 temp is null
 *            - 6 temp buffer is too small
 * @note      none
 */
uint8_t ws2812b_write_only_color(ws2812b_handle_t *handle, uint32_t *rgb, uint32_t len, uint8_t *temp, uint32_t temp_len);

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a ws2812b handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ws2812b_set_reg(ws2812b_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
