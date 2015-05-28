main := 7.cpp
headers := Item.h Book.h Magazine.h ItemCatalog.h
run := run7

do: $(main) $(headers)
	g++ $(main) -o $(run)

test: $(main) $(headers)
	g++ $(main) -o $(run) && ./$(run)
