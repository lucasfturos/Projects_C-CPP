run: build
	@./tone "60" "120" "Sine" "Sine_60Hz"
build:
	@g++ -Wall -Wextra -Wpedantic -Werror -pedantic -g -o tone \
		   main.cpp tone_generate.cpp -lsndfile
clean:
	@rm -rf tone *.wav
