/*
 * Copyright (c) 2015 Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef  _SVC_H_
#define  _SVC_H_

#include <pthread.h>
#include <arch/atomic.h>

enum svc_state {
    SVC_STATE_STOPPED,
    SVC_STATE_RUNNING,
};

struct unipro_link_cfg;

struct svc {
    struct tsb_switch *sw;
    struct ara_board_info *board_info;

    enum svc_state state;
    int stop;
    atomic_t allow_idle;
    pid_t svcd_pid;
    pthread_mutex_t lock;
    pthread_cond_t cv;

    uint8_t ap_intf_id;
    bool ap_initialized;
};

extern struct svc *svc;

struct interface;

int svc_intf_device_id(uint8_t, uint8_t);
int svc_route_create(uint8_t, uint8_t, uint8_t, uint8_t);
int svc_route_destroy(uint8_t, uint8_t);
int svc_connection_create(uint8_t, uint16_t, uint8_t, uint16_t, uint8_t, uint8_t);
int svc_dme_peer_get(uint8_t, uint16_t, uint16_t, uint16_t*, uint32_t*);
int svc_dme_peer_set(uint8_t, uint16_t, uint16_t, uint32_t, uint16_t*);
int svc_connection_destroy(uint8_t, uint16_t, uint8_t, uint16_t);
int svc_hot_unplug(uint8_t, bool);
/* Eject interface given the interface ID */
int svc_intf_eject(uint8_t);
/* Request of interface ejection */
int svc_interface_eject_request(struct interface *, uint32_t delay);
/* Request to eject all interfaces */
int svc_interface_eject_request_all(uint32_t delay);
/* Notify the completion of interface ejection */
int svc_interface_eject_completion_notify(struct interface *);
int svc_intf_vsys_enable(uint8_t);
int svc_intf_vsys_disable(uint8_t);
int svc_intf_refclk_enable(uint8_t);
int svc_intf_refclk_disable(uint8_t);
int svc_intf_unipro_enable(uint8_t);
int svc_intf_unipro_disable(uint8_t);
int svc_intf_set_power_mode(uint8_t, struct unipro_link_cfg *);

int svcd_start(void);
void svcd_stop(void);
int svcd_power_down(void);

int svc_connect_interfaces(struct interface *iface1, uint16_t cportid1,
                           struct interface *iface2, uint16_t cportid2,
                           uint8_t tc, uint8_t flags);

#endif


