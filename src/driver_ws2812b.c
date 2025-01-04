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
 * @file      driver_ws2812b.c
 * @brief     driver ws2812b source file
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

#include "driver_ws2812b.h"

/**
 * @brief chip register definition
 */
#define CHIP_NAME                 "Worldsemi WS2812B"        /**< chip name */
#define MANUFACTURER_NAME         "Worldsemi "               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.7f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.3f                       /**< chip max supply voltage */
#define MAX_CURRENT               16.0f                      /**< chip max current */
#define TEMPERATURE_MIN           -25.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                      /**< chip max operating temperature */
#define DRIVER_VERSION            1000                       /**< driver version */

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
uint8_t ws2812b_init(ws2812b_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->spi_10mhz_init == NULL)                                  /* check spi_10mhz_init */
    {
        handle->debug_print("ws2812b: spi_10mhz_init is null.\n");       /* spi_10mhz_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_deinit == NULL)                                      /* check spi_deinit */
    {
        handle->debug_print("ws2812b: spi_deinit is null.\n");           /* spi_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_write_cmd == NULL)                                   /* check spi_write_cmd */
    {
        handle->debug_print("ws2812b: spi_write_cmd is null.\n");        /* spi_write_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("ws2812b: delay_ms is null.\n");             /* delay_ms is null */
       
        return 3;                                                        /* return error */
    }
    
    if (handle->spi_10mhz_init() != 0)                                   /* spi init */
    {
        handle->debug_print("ws2812b: spi init failed.\n");              /* spi init failed */
       
        return 1;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */
    
    return 0;                                                            /* success return 0 */
}

/**
 * @brief     write one frame
 * @param[in] rgb input color
 * @param[in] *temp pointer to a temp buffer
 * @note      none
 */
static void a_ws2812b_write_one_frame(uint32_t rgb, uint8_t temp[48])
{
    uint8_t r, g, b;
    uint8_t i, j;
    uint32_t c, point;
    const uint16_t one_code = 0xFFF8U;
    const uint16_t zero_code = 0xE000U;
    
    r = (uint8_t)((rgb >> 16) & 0xFF);                               /* set red */
    g = (uint8_t)((rgb >> 8) & 0xFF);                                /* set green */
    b = (uint8_t)((rgb >> 0) & 0xFF);                                /* set blue */
    c = ((uint32_t)(g) << 16) | ((uint32_t)(r) << 8) | b;            /* set color */
    
    memset(temp, 0, sizeof(uint8_t) * 30);                           /* clear the temp buffer */
    
    point = 0;                                                       /* clear point */
    for (i = 0; i < 24; i++)                                         /* set 24 bit */
    {
        if (((c >> (23 - i)) & 0x01) != 0)                           /* if bit 1 */
        {
            for (j = 0; j < 16; j ++)                                /* 16 bit */
            {
                if (((one_code >> (15 - j)) & 0x01) != 0)            /* if one code */
                {
                    temp[point / 8] |= 1 << (7 - (point % 8));       /* set bit 1 */
                }
                else
                {
                    temp[point / 8] |= 0 << (7 - (point % 8));       /* set bit 0 */
                }
                point = point + 1;                                   /* point++ */
            }
        }
        else                                                         /* if bit 0 */
        {
            for (j = 0; j < 16; j ++)                                /* 16 bit */
            {
                if (((zero_code >> (15 - j)) & 0x01) != 0)           /* if zero code */
                {
                    temp[point / 8] |= 1 << (7 - (point % 8));       /* set bit 1 */
                }
                else
                {
                    temp[point / 8] |= 0 << (7 - (point % 8));       /* set bit 0 */
                }
                point = point + 1;                                   /* point++ */
            }
        }
    }
}

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
uint8_t ws2812b_write(ws2812b_handle_t *handle, uint32_t *rgb, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    uint32_t i, bit_size;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (rgb == NULL)                                                        /* check rgb */
    {
        handle->debug_print("ws2812b: rgb is null.\n");                     /* rgb is null */
       
        return 4;                                                           /* return error */
    }
    if (temp == NULL)                                                       /* check temp */
    {
        handle->debug_print("ws2812b: temp is null.\n");                    /* temp is null */
       
        return 5;                                                           /* return error */
    }
    
    bit_size = WS2812B_EACH_RESET_BIT_FRAME_LEN * len;                      /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */
    if (bit_size > temp_len)                                                /* check temp length */
    {
        handle->debug_print("ws2812b: temp buffer is too small and "
                            "size will be %d.\n", bit_size);                /* temp buffer is too small*/
       
        return 5;                                                           /* return error */
    }
    for (i = 0; i < bit_size; i++)                                          /* set the reset frame */
    {
        temp[i] = 0x00;                                                     /* set 0x00 */
    }
    if (handle->spi_write_cmd(temp, (uint16_t)bit_size) != 0)               /* write command */
    {
        handle->debug_print("ws2812b: write command failed.\n");            /* write command failed */
        
        return 1;                                                           /* return error */
    }
    
    bit_size = 24 * 16 * len ;                                              /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */
    if (bit_size > temp_len)                                                /* check temp length */
    {
        handle->debug_print("ws2812b: temp buffer is too small and "
                            "size will be %d.\n", bit_size);                /* temp buffer is too small*/
       
        return 6;                                                           /* return error */
    }
   
    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        a_ws2812b_write_one_frame(rgb[i], &temp[i * 48]);                   /* set color */
    }
    
    if (handle->spi_write_cmd(temp, (uint16_t)bit_size) != 0)               /* write command */
    {
        handle->debug_print("ws2812b: write command failed.\n");            /* write command failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ws2812b_write_only_reset(ws2812b_handle_t *handle, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    uint32_t i, bit_size;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (temp == NULL)                                                       /* check temp */
    {
        handle->debug_print("ws2812b: temp is null.\n");                    /* temp is null */
       
        return 4;                                                           /* return error */
    }
    
    bit_size = WS2812B_EACH_RESET_BIT_FRAME_LEN * len;                      /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */
    if (bit_size > temp_len)                                                /* check temp length */
    {
        handle->debug_print("ws2812b: temp buffer is too small and "
                            "size will be %d.\n", bit_size);                /* temp buffer is too small*/
       
        return 5;                                                           /* return error */
    }
    
    for (i = 0; i < bit_size; i++)                                          /* set the reset frame */
    {
        temp[i] = 0x00;                                                     /* set 0x00 */
    }
    
    if (handle->spi_write_cmd(temp, (uint16_t)bit_size) != 0)               /* write command */
    {
        handle->debug_print("ws2812b: write command failed.\n");            /* write command failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ws2812b_write_only_color(ws2812b_handle_t *handle, uint32_t *rgb, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    uint32_t i, bit_size;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (rgb == NULL)                                                        /* check rgb */
    {
        handle->debug_print("ws2812b: rgb is null.\n");                     /* rgb is null */
       
        return 4;                                                           /* return error */
    }
    if (temp == NULL)                                                       /* check temp */
    {
        handle->debug_print("ws2812b: temp is null.\n");                    /* temp is null */
       
        return 5;                                                           /* return error */
    }
    
    bit_size = 24 * 16 * len ;                                              /* set the bit size */
    bit_size = bit_size / 8;                                                /* set the bit size */
    if (bit_size > temp_len)                                                /* check temp length */
    {
        handle->debug_print("ws2812b: temp buffer is too small and "
                            "size will be %d.\n", bit_size);                /* temp buffer is too small*/
       
        return 6;                                                           /* return error */
    }
   
    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        a_ws2812b_write_one_frame(rgb[i], &temp[i * 48]);                   /* set color */
    }
    
    if (handle->spi_write_cmd(temp, (uint16_t)bit_size) != 0)               /* write command */
    {
        handle->debug_print("ws2812b: write command failed.\n");            /* write command failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ws2812b_deinit(ws2812b_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = handle->spi_deinit();                                      /* spi deinit */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("ws2812b: spi deinit failed.\n");        /* spi deinit failed */
       
        return 1;                                                    /* return error */
    }
    handle->inited = 0;                                              /* flag closed */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ws2812b_set_reg(ws2812b_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    return handle->spi_write_cmd(buf, len);        /* write to reg */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a ws2812b info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ws2812b_info(ws2812b_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ws2812b_info_t));                        /* initialize ws2812b info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
