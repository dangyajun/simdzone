/*
 * bench.c -- SSE4.2 compilation target for benchmark function(s)
 *
 * Copyright (c) 2023, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "zone.h"
#include "diagnostic.h"
#include "heap.h"
#include "log.h"
#include "westmere/simd.h"
#include "westmere/bits.h"
#include "lexer.h"
#include "generic/scanner.h"

diagnostic_push()
clang_diagnostic_ignored(missing-prototypes)

zone_return_t zone_bench_westmere_lex(zone_parser_t *parser, size_t *tokens)
{
  zone_token_t token;
  zone_return_t result;

  (*tokens) = 0;
  while ((result = lex(parser, &token)) >= 0 && token.data != zone_end_of_file)
    (*tokens)++;

  return result;
}

diagnostic_pop()
