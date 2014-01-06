# mruby-siphash

siphash message digest.

```ruby
puts SipHash::digest("mruby") #=> "\x41\x0c\xa3\xd1\xaf\xfd\xe0\x3f"

seed = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
puts SipHash::digest("mruby", seed) #=> "\x41\x69\xd4\x8b\xa6\xdb\x7e\x68"
```

## Installation

### use github repository

Write in build_config.rb

```ruby
MRuby::Build.new do |conf|
  conf.gem :github => 'ksss/mruby-siphash', :branch => 'master'
end
```

### or use mgem

```
mgem add mruby-siphash
```

### build

and exec.

```
rake clean
rake
rake test
mruby -e 'puts SipHash::digest("mruby")'
```
