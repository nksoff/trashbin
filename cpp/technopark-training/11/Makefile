main := 11.cpp
headers := Replace.h
run := run11

do: $(main) $(headers) 
	g++ -std=c++11 $(main) -o $(run)

test: $(main) $(headers)
	g++ -std=c++11 $(main) -o $(run) && ./$(run)