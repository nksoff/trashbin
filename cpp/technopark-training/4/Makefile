main := 4.cpp
additional := Train.cpp
headers := Train.h
run := run4

trains := trains.txt

do: $(main)
	g++ $(main) $(additional) -o $(run)

test: $(main) $(additional) $(headers) $(trains)
	g++ $(main) $(additional) -o $(run) && ./$(run)
