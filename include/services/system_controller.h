/*
* @file system_controller.h
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

#ifndef SYSTEM_CONTROLLER__H
#define SYSTEM_CONTROLLER__H

#include <stdint.h>

typedef struct service_interface {
  int (*init_service)();
  int (*deinit_service)();
  int (*recv_msg)(uint8_t, void*);
  uint8_t service_id;
} sc_service_t;

typedef enum {
  sc_service_wifi = 1,
  sc_service_aws,
  sc_service_camera,
  sc_service_kvs,
  sc_service_count
} sc_service_list_t;

int SC_init();
int SC_deinit();
int SC_register_service(sc_service_t *service);
int SC_deregister_service(uint8_t service_id);

/*
* @brief Sends a command to registered service
* @param sid The service identifier
* @param cmd An applicable command defined in the service
* @param arg Any other arguments required for the command
*/
int SC_send_cmd(sc_service_list_t sid, uint8_t cmd, void* arg);

#endif /* ifndef SYSTEM_CONTROLLER__H */
