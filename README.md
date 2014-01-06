# mruby-siphash

siphash message digest.

```ruby
puts SipHash::digest("mruby") #=> "\x3f\xe0\xfd\xaf\xd1\xa3\x0c\x41"

seed = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
puts SipHash::digest("mruby", seed) #=> "\x68\x7e\xdb\xa6\x8b\xd4\x69\x41"
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
