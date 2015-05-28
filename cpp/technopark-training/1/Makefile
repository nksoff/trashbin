main := 1.c
run := run1

test1 := test.txt
test2 := test1.txt

do: $(main)
	gcc $(main) -o $(run)

test: $(main) $(test1) $(test2)
	gcc $(main) -o $(run) && ./$(run) Толстой $(test1)
	gcc $(main) -o $(run) && ./$(run) the $(test2)

