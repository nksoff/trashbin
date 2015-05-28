main := 6.cpp
headers := IObject.h IntObject.h StringObject.h Tree.h
run := run6

test := integers.txt strings.txt

do: $(main) $(headers) 
	g++ -Wno-write-strings $(main) -o $(run)

test: $(main) $(headers) $(test)
	g++ -Wno-write-strings $(main) -o $(run) && ./$(run)
