#!/usr/bin/ruby

puts File.read("../config.yaml")

payload = Marshal.dump(Gem)
Marshal.load(payload)
