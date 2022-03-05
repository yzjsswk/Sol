$filename = $args[0]
$compile = "g++ $filename.cpp -o $filename.exe -std=c++11 -Wall"
$run = "cat in.txt | $filename.exe > out.txt"
$clear = "rm $filename.exe"
iex $compile
iex $run
#Start-Sleep -s 2
#iex $clear 
