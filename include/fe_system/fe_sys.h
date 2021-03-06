/*
* @file fe_system.h
*
* The MIT License (MIT)
*
* Copyright (c) 2020 Fredrik Danebjer
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/


#ifndef FE_SYS__H
#define FE_SYS__H

#include <stdint.h>

typedef struct ip_address {
  uint16_t ip4_addr1;
  uint16_t ip4_addr2;
  uint16_t ip4_addr3;
  uint16_t ip4_addr4;
} ip_address_t;

/*
* @brief Fetches the IP address from the underlying TCPIP stack.
* @arg ip is the address where to store the four ip fields
* @retval EXIT_SUCCESS on success, otherwise EXIT_FAILURE
*/
int FE_SYS_get_ip(ip_address_t *ip);

/*
* @brief Initializes the system resources required to run the application.
* @retval EXIT_SUCCES on success, otherwise EXIT_FAILURE
*/
int FE_SYS_init();

#endif /* ifndef FE_SYS__H */
