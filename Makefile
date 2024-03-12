soujourn:
	g++ main.cpp -o main
	
run: soujourn
	.\main

pvenv: run
	.\.venv\Scripts\activate
	python .\main.py
