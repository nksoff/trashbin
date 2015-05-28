main := Sort.cpp Set.cpp 9.cpp
headers := Sort.h Set.h
run := run9

do: $(main) $(headers) 
	g++ $(main) -o $(run)

test: $(main) $(headers)
	g++ $(main) -o $(run) && ./$(run)
