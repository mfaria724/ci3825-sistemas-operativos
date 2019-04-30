processes = $(wildcard Processes/sources/*.c)
threads = $(wildcard Threads/*.c)

main: 
	rm -f paisHilos paisProcesos
	gcc $(processes) -o paisProcesos
	gcc $(threads) -o paisHilos


clean:
	rm -f paisHilos paisProcesos