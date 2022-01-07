name=cheekytesting
dest=/usr/bin
cc=gcc
deps = $(wildcard *.h)
scrs = $(wildcard *.c)
objs = $(patsubst %.c,./obj/%.o,$(scrs))
o = ./obj
dir = if [ ! -d $(o) ];then mkdir $(o);fi

$(o)/%.o: %.c $(deps)
	$(dir)
	$(cc) -c -o $@ $< 

$(name): $(objs)
	$(cc) -o $@ $^ 

install:
	cp $(name) $(dest)/$(name)

clean:
	rm -r $(o) $(name)