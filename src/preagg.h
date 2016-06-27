// Copyright (C) 2016 by wayslog

#ifndef _CW_PREAGG_H
#define _CW_PREAGG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "parser.h"

// test is_prefix, if matched, replace with "to" till next dot
#define MAX_AGG_RULE_NUM 1024
#define MAX_KEY_LENGTH 1024 * 16
#define MAX_RULE_TYPE_LENGTH 10
#define AGG_COPY_LEN 4
#define AGG_REMOVE_LEN 5

enum {
  AGG_OK = 0,            // operation is ok
  AGG_NOAGG = 1,         // No need to agg
  AGG_ECONF = 2,         // CONFIG parse error
  AGG_ECFGNOTFOUND = 3,  // config file not found

  AGG_REMOVE = 4,  // Remove originnal stream
  AGG_COPY = 5,  // Default Operation, copy and throw a new parse_result object
  AGG_ETYPE = 6,
  AGG_ESPLIT = 7,
  AGG_ETOOMUCH = 8,
};

struct agg_rule {
  char *prefix;
  size_t prefix_len;
  char *to;
  size_t to_len;
  int rule_type;
};

struct agg_rules {
  struct agg_rule rules[MAX_AGG_RULE_NUM] ;
  size_t rules_num;
};

struct agg_rules PREAGG_RULES;

int parse_preagg_rules(struct agg_rules *rules, const char* value, size_t value_len) ;

int preagg(struct parser_result *result, struct parser_result *out_result);

#endif