/*
 * ip6.h -- fallback parser for IPv6 addresses
 *
 * Copyright (c) 2022-2023, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef IP6_H
#define IP6_H

#if _WIN32
#include <ws2tcpip.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

zone_always_inline()
zone_nonnull_all()
static inline void parse_ip6(
  zone_parser_t *parser,
  const zone_type_info_t *type,
  const zone_field_info_t *field,
  zone_token_t *token)
{
  char buf[INET6_ADDRSTRLEN + 1];

  if (token->length > INET6_ADDRSTRLEN)
    SEMANTIC_ERROR(parser, "Invalid %s in %s",
                   field->name.data, type->name.data);

  memcpy(buf, token->data, token->length);
  buf[token->length] = '\0';
  if (inet_pton(AF_INET6, buf, &parser->rdata->octets[parser->rdata->length]) != 1)
    SEMANTIC_ERROR(parser, "Invalid %s in %s",
                   field->name.data, type->name.data);
  parser->rdata->length += sizeof(struct in6_addr);
}

#endif // IP6_H
