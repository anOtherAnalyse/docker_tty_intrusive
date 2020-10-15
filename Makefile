exploit: exploit.c
	gcc exploit.c -o exploit

hijack: hijack.c
	gcc hijack.c -o hijack

.PHONY: clean
clean:
	rm hijack exploit
