# Directory of processes files
processes = $(wildcard Processes/sources/*.c)
# Directory of threads files
threads = $(wildcard Threads/*.c)

# Main function
main: 
	# Remove old compiled files
	rm -f paisHilos paisProcesos
	# Compile processes files
	gcc $(processes) -pthread -o paisProcesos
	# Compile threads files
	gcc $(threads) -pthread -o paisHilos

# Function to remove compiled files
clean:
	rm -f paisHilos paisProcesos