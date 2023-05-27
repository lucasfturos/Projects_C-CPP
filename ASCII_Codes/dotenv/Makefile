run: build
	@./main
run_key: build
	@./key > .env
build:
	@g++ -Wall -g -o env_read env_read.cpp
	@g++ -Wall -g -o key key.cpp -lssl -lcrypto
clean:
	@rm -rf env_read key
