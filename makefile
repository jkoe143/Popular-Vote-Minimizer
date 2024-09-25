build:
	rm -f app.exe
	gcc app.c MinPopVote.c -o app.exe       

run:
	./app.exe

run_quiet:
	./app.exe -q

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./app.exe

run_fast:
	./app.exe -f

run_year:
	./app.exe -y 1864

run_fast_quiet:
	./app.exe -f -q

build_test:
	rm -f test.exe
	gcc test.c MinPopVote.c -o test.exe

run_test:
	./test.exe

clean:
	rm -f app.exe test.exe



