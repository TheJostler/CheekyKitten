name=cheeky
dest=/usr/bin
cc=gcc
flags=-Wall -Werror -Wextra -O3 -ffast-math
deps = $(wildcard *.h)
scrs = $(wildcard *.c)
objs = $(patsubst %.c,./obj/%.o,$(scrs))
o = ./obj
dir = if [ ! -d $(o) ];then mkdir $(o);fi

$(o)/%.o: %.c $(deps)
	$(dir)
	$(cc) $(flags) -c -o $@ $< 

$(name): $(objs)
	$(cc) $(flags)  -o $@ $^
	strip $(name)

install:
	cp $(name) $(dest)/$(name)

clean:
	rm -r $(o) $(name)
