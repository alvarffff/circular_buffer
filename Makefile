all: host arm

host: circular_buffer.c 
	gcc circular_buffer.c -pthread -o circular_buffer

arm: circular_buffer.c
	arm-linux-gnueabihf-gcc -pthread circular_buffer.c -o circular_buffer_arm


clean:
	rm -f circular_buffer circular_buffer_arm