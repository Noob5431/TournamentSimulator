build:
	gcc main.c list.c queue.c stack.c bst.c -o "lanParty"
	mv "lanParty.exe" "lanParty"

clean:
	rm -f "lanParty"

winbuild:
	gcc main.c list.c queue.c stack.c bst.c -o "lanParty"
	ren "lanParty.exe" "lanParty"
	./lanParty c.in d.in d.out

winclean:
	del /f "lanParty"