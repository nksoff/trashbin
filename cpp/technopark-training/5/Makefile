main := 5.cpp
headers := Queue.h
run := run5

do: $(main) $(headers) 
	g++ $(main) -o $(run)

test: $(main) $(headers)
	g++ $(main) -o $(run) && ./$(run)
