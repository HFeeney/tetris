default: tetris

tetris: main.cc
	g++ -o tetris main.cc

clean:
	rm tetris 
