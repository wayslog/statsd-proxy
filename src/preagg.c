
#include "preagg.h"

size_t is_prefix
(
 const char *str1, size_t len_str1,
 const char *str2, size_t len_str2
);

int preagg(struct parser_result *result, struct parser_result *out_result)
{
  for (size_t i = 0; i < PREAGG_RULES->rules_num; i++)
  {
    struct agg_rule *rule = PREAGG_RULES->rules[i];
    if (result->len < rule->prefix_len) continue;
    // to find out if  there have the special prefix
    size_t pos = is_prefix(rule->prefix, rule->prefix_len,
                                  result->key, result->len);
    if (!pos) return AGG_NOAGG;
    size_t left_len = result->len -1 - pos;
    size_t key_len = rule->prefix_len + rule->to_len + left_len;
    char *cpy = malloc(key_len);
    strncpy(cpy, rule->prefix, rule->prefix_len);
    strncpy(&cpy[rule->prefix_len], rule->to, rule->to_len);
    strncpy(&cpy[rule->prefix_len + rule->to_len], &result->key[pos], left_len);
    size_t blk_len = result->blen - result->len + key_len;
    char *blk = malloc(blk_len);
    memcpy(blk, cpy, key_len);
    memcpy(&blk[key_len], &result->block[result->len], blk_len);
    out_result->block = blk;
    out_result->blen = blk_len;
    out_result->key = cpy;
    out_result->len = key_len;
  }

  return AGG_NOAGG;
}

/*
 return the pos where should we substr if  str1 is the prefix of str2
 return 0 if  len_str2 < len_str1 or str1 is not the prefix of str2
 */
size_t is_prefix
(
 const char *str1, size_t len_str1,
 const char *str2, size_t len_str2
)
{
  if (len_str2 < len_str1) return 0;
  size_t matched = 0;
  for (size_t pos = 0; pos < len_str1; ++pos)
  {
    if (str1[pos] != str2[pos]) return 0;
    ++matched;
  }

  size_t next_dot_pos = matched;
  // find next dot and exclude it
  size_t pos = matched;
  while (pos < len_str2)
  {
    if (str2[pos]== '.')
    {
      next_dot_pos = pos;
      break;
    }
    ++pos;
  }

  if (next_dot_pos == matched)
  {
    return len_str2 - 1;
  }
  else
  {
    return next_dot_pos;
  }

}
