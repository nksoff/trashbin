main := 3.c
run := run3

test1 := test.txt
test2 := test1.txt

out := .out.txt

do: $(main)
	gcc $(main) -o $(run)

test: $(main) $(test1) $(test2)
	gcc $(main) -o $(run) && ./$(run) $(test1) $(test1)$(out)
	echo "\n\n" && cat $(test1)$(out) && echo "\n"
	gcc $(main) -o $(run) && ./$(run) $(test2) $(test2)$(out)
	echo "\n\n" && cat $(test2)$(out) && echo "\n"
