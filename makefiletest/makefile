src=$(wildcard ./src/*.c)
obj=$(patsubst ./src/%.c, ./obj/%.o, $(src))
inc_path=./inc
myArgs= -Wall -g
ALL:a.out

#add.o:add.c
#	gcc -c add.c -o add.o

#sub.o:sub.c
#	gcc -c sub.c -o sub.o

#test2.o:test2.c
#	gcc -c test2.c -o test2.o
a.out: $(obj)
	gcc $^ -o $@

$(obj): ./obj/%.o: ./src/%.c
	gcc -c $< -o $@ -I $(inc_path)

clean:
	-rm -rf $(obj) a.out
