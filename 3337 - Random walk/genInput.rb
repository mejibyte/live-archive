for cuantos in (1..10)
  puts "3"
  3.times do
    a = rand(6)
    b = rand(6)
    a *= rand(2)== 0 ? 1 : -1
    b *= rand(2)== 0 ? 1 : -1
    puts "#{a} #{b}"
  end
end
puts "0"
