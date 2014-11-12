
NAME=tsifro

default: $(NAME).o

.DEFAULT spec clean:
	$(MAKE) -C tmp/ $@ NAME=$(NAME)

cs: clean spec

.PHONY: spec clean upgrade cs

