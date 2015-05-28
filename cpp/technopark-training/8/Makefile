main := 8.cpp
headers := Queue.h
run := run8

do: $(main) $(headers) 
	g++ $(main) -o $(run)

test: $(main) $(headers)
	g++ $(main) -o $(run) && ./$(run)
