for i in (0..100)
  x = rand
  x *= 7 * (rand(2) == 1 ? 1 : -1)
  d = rand(12) + 1
  puts x.to_s + " " + d.to_s
end
