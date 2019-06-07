# Main function
main:
	# Remove old compiled files
	rm -f tesh ../commands/grep ../commands/ls ../commands/chmod
	# Compile processes files
	gcc tesh.c -o tesh
	gcc ../commands/ls.c -o ../commands/ls	
	gcc ../commands/grep.c -o ../commands/grep
	gcc ../commands/chmod.c -o ../commands/chmod

# Function to remove compiled files
clean:
	rm -f tesh ../commands/grep ../commands/ls ../commands/chmod