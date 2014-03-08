#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include "siphash24.h"

#define siphash crypto_auth

#define DEFAULT_SEED "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

static mrb_value
mrb_siphash_digest(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_value seed = mrb_nil_value();
  mrb_sym id_DEFAULT_SEED;
  mrb_value klass;
  uint8_t digest[8];
#ifndef MRB_ENDIAN_BIG
  uint8_t roll[8];
  int i;
#endif

  mrb_get_args(mrb, "S|S", &str, &seed);
  if (mrb_nil_p(seed)) {
    klass = mrb_obj_value(mrb_module_get(mrb, "SipHash"));
    id_DEFAULT_SEED = mrb_intern_cstr(mrb, "DEFAULT_SEED");
    seed = mrb_const_get(mrb, klass, id_DEFAULT_SEED);
  }
  if (RSTRING_LEN(seed) != 16) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "seed value must be 16 length string");
  }

  siphash(digest, (const unsigned char*) RSTRING_PTR(str), RSTRING_LEN(str), (const unsigned char*) RSTRING_PTR(seed));

#ifndef MRB_ENDIAN_BIG
  for (i = 0; i < 8; i++) {
    roll[i] = digest[7 - i];
  }
  memcpy(digest, roll, 8);
#endif

  return mrb_str_new(mrb, (char*) digest, 8);
}

void
mrb_mruby_siphash_gem_init(mrb_state *mrb)
{
  struct RClass *mSipHash = mrb_define_module(mrb, "SipHash");
  mrb_define_class_method(mrb, mSipHash, "digest", mrb_siphash_digest, MRB_ARGS_ANY());
  mrb_define_const(mrb, mSipHash, "DEFAULT_SEED", mrb_str_new(mrb, DEFAULT_SEED, 16));
}

void
mrb_mruby_siphash_gem_final(mrb_state *mrb)
{
}
