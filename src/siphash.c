#include "siphash24.h"
#include <mruby.h>
#include <mruby/string.h>

#define siphash crypto_auth

#ifdef MRB_ENDIAN_BIG
#endif

#define DEFAULT_SEED "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

static mrb_value
mrb_siphash_digest(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv;
  int argc;
  mrb_value str;
  mrb_value seed;
  struct RString *pstr;
  struct RString *pseed;
  uint8_t digest[8];

  mrb_get_args(mrb, "*", &argv, &argc);

  switch (argc) {
  case 1:
	str = argv[0];
    seed = mrb_str_new(mrb, DEFAULT_SEED, 16);
	break;
  case 2:
	str = argv[0];
	seed = argv[1];
	break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
  }

  pstr = mrb_str_ptr(str);
  pseed = mrb_str_ptr(seed);

  if (pseed->len != 16) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "seed value need 128 bit chars");
  }

  siphash(digest, (const unsigned char*) pstr->ptr, pstr->len, (const unsigned char*) pseed->ptr);

  return mrb_str_new(mrb, (char*) digest, 8);
}

void
mrb_mruby_siphash_gem_init(mrb_state *mrb)
{
  struct RClass *mSipHash = mrb_define_module(mrb, "SipHash");
  mrb_define_class_method(mrb, mSipHash, "digest", mrb_siphash_digest, MRB_ARGS_ANY());
}

void
mrb_mruby_siphash_gem_final(mrb_state *mrb)
{
}
