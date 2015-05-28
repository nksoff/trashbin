main := Docs.cpp Docs_test.cpp
headers := Docs.h
run := run

do: $(main) $(headers) 
	g++ -std=c++11 $(main) -o $(run)

test: $(main) $(headers)
	g++ -std=c++11 $(main) -o $(run) && ./$(run)