PROGRAM ?= timer-interrupt

$(PROGRAM): $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)

clean:
	rm -f $(PROGRAM) $(PROGRAM).hex

