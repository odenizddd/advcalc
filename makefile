SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)

advcalc: $(OBJ)
	gcc $^ -o $@

%.o: %.c
	gcc -o $@ -c $<

clean: $(OBJ)
	rm $^
	rm advcalc