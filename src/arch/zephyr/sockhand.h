/************************************************************************************
 Copyright (c) 2023-2024 KT Elektronik GmbH
 This program and the accompanying materials are made available under the
 terms of the Eclipse Public License 2.0 which is available at
 http://www.eclipse.org/legal/epl-2.0.

 SPDX-License-Identifier: EPL-2.0
 
 Contributors:
  Dirk Kaar - initial API and implementation and/or initial documentation
 ************************************************************************************/

#ifndef SRC_ARCH_ZEPHYR_SOCKHAND_H_
#define SRC_ARCH_ZEPHYR_SOCKHAND_H_

#include <string.h>

#include "devlog.h"

#include <zephyr/net/net_if.h>
#include <zephyr/posix/arpa/inet.h>
#include <zephyr/net/socket.h>
#include <zephyr/kernel.h>

#ifdef CONFIG_POSIX_API
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#else
#include <zephyr/posix/netinet/in.h>
#endif

inline in_addr_t inet_addr(const char *cp) {
  in_addr_t in_addr;
  if (0 == net_addr_pton(AF_INET, cp, &in_addr)) return in_addr;
  return -1;
}

void setupMulticastGroup(char* paIPAddr, const char* paMCInterface);

//these include needs to be last
#include "../gensockhand.h"
#include "../fdselecthand.h"
#include "../bsdsocketinterf.h"

typedef CGenericIPComSocketHandler<CFDSelectHandler, CBSDSocketInterface> CIPComSocketHandler;

#endif /* SRC_ARCH_ZEPHYR_SOCKHAND_H_ */

