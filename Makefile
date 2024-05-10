soujourn:
	g++ main.cpp -o main
	
run: soujourn
	.\main

pvenv: run
	.\.venv\Scripts\activate
	python .\main.py

main:
	g++ main.cpp -o main

testing:
	g++ testing.cpp -o testing 

clean:
	rm ./main ./testing