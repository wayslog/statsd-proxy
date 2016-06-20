// Copyright (C) 2016 by wayslog

#ifndef  _CW_PREAGG_H
#define  _CW_PREAGG_H
#include <stdlib.h>
#include <string.h>
#include "parser.h"


// test is_prefix, if matched, replace with "to" till next dot

enum
{
  AGG_OK = 0,      /* operation is ok */
  AGG_NOAGG = 1,   // No need to agg
};

struct agg_rule
{
  char *prefix;
  size_t prefix_len;
  char *to;
  size_t to_len;
};

struct agg_rules
{
  struct agg_rule **rules;
  size_t rules_num;
};

struct agg_rules *PREAGG_RULES;

int preagg(struct parser_result *result, struct parser_result *out_result);

#endif
