seed = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"

assert 'digest mruby' do
  SipHash::digest("mruby") == "\x41\x0c\xa3\xd1\xaf\xfd\xe0\x3f"
end

assert 'digest mruby with seed' do
  SipHash::digest("mruby", seed) == "\x41\x69\xd4\x8b\xa6\xdb\x7e\x68"
end

assert 'SipHash::DEFAULT_SEED' do
  assert_kind_of String, SipHash::DEFAULT_SEED
  assert_equal SipHash::DEFAULT_SEED.length, 16
end

assert 'digest must be string' do
  assert_raise(TypeError) do
    SipHash::digest(1)
  end
end

assert 'seed value must be 16 length string' do
  assert_raise(ArgumentError) do
    SipHash::digest("", "")
  end
end
