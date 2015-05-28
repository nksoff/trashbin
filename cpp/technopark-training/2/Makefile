main := 2.c
run := run2

test := test.txt

do: $(main)
	gcc $(main) -o $(run)

test: $(main) $(test)
	gcc $(main) -o $(run) && ./$(run) $(test)
