// COMP 281 Assignment 2 Part 1
// Author: Maadhyam Rawal --> 201765354
// Description: Converting ASCII Art to Hex and vice-versa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Maximum Input Line Length
#define MAX_LINE_LENGTH 1000  
// 10 characters + null terminator for safety
#define HEX_BUFFER_SIZE 11    


// Function to convert an integer to a hexadecimal string
void convert_int_to_hex(unsigned int number, char *hex_output) {
    int index = 0;
    unsigned int remainder;
    char temp_buffer[HEX_BUFFER_SIZE]; // Temporary buffer to store hex digits

    // If number is zero, store "0" and return
    if (number == 0) {
        hex_output[0] = '0';
        hex_output[1] = '\0';
        return;
    }

    // Converting number to hex by continuously dividing by 16
    while (number != 0) {
        remainder = number % 16;
        // Store corresponding hexadecimal character
        temp_buffer[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        number /= 16;
    }
    temp_buffer[index] = '\0';

    // Reverse the hexadecimal to get the correct order 
    int hex_length = index;
    for (int i = 0; i < hex_length; i++) {
        hex_output[i] = temp_buffer[hex_length - i - 1];
    }
    hex_output[hex_length] = '\0';
}



// Function to compressthe ASCII art line
void compress_ascii_art(const char *input_line) {
    int index = 0;
    while (input_line[index] != '\0') {
        int repeat_count = 1;


        // Counting consecutive similar characters
        while (input_line[index] == input_line[index + 1]) {
            repeat_count++;
            index++;
        }

        // If a character repeats 2 or more times use the above function to convert integer to hex
        if (repeat_count >= 2) {
            char hex_count[HEX_BUFFER_SIZE];
            convert_int_to_hex(repeat_count, hex_count);
            printf("%c%c%s*", input_line[index], input_line[index], hex_count);

        } 
        
         // If the characters are not repeated print them as it is they were
        else {
            printf("%c", input_line[index]);
        }
        index++;
    }
}



// Function to convert a hexadecimal string to an integer
int convert_hex_to_int(const char *hex_string) {
    int result = 0;

    // Loop over each character in the hexadecimal string
    while (*hex_string && *hex_string != '*') {

        // Convert '0'-'9' to integer
        if (*hex_string >= '0' && *hex_string <= '9') {
            result = result * 16 + (*hex_string - '0'); 
        } 

        // Convert 'A'-'F' to integer
        else if (*hex_string >= 'A' && *hex_string <= 'F') {
            result = result * 16 + (*hex_string - 'A' + 10); 
        }
        hex_string++;
    }
    return result;
}



// Function to expand a compressed ASCII art line to a hexadecimal value
void expand_ascii_art(const char *compressed_line) {
    int index = 0;

    while (compressed_line[index] != '\0') {
        // Detecting sequences qhere two identical characters are followed by a hex count
        if (compressed_line[index] == compressed_line[index + 1] &&
           ((compressed_line[index + 2] >= '0' && compressed_line[index + 2] <= '9') || (compressed_line[index + 2] >= 'A' && compressed_line[index + 2] <= 'F'))) 
        
        {
            char hex_buffer[HEX_BUFFER_SIZE];
            int hex_index = 0;
            int j = index + 2;

            // Extracting the hexadecimal count from the compressed sequence
            while (compressed_line[j] != '*' && compressed_line[j] != '\0') {
                hex_buffer[hex_index++] = compressed_line[j++];
            }
            hex_buffer[hex_index] = '\0';

            // Converting extracted hexadecmial to an integer
            int repeat_count = convert_hex_to_int(hex_buffer);

            // Printing the repeated characters
            for (int k = 0; k < repeat_count; k++) {
                printf("%c", compressed_line[index]);
            }

            // Making sure that the character goes on to thhe next position if there is a '*'
            index = (compressed_line[j] == '*') ? j + 1 : j;
        } 
        
        // If its not a repeated sequence just print the character
        else {
            // Print normal characters directly
            printf("%c", compressed_line[index]);
            index++;
        }
    }
}



// Main function
int main() {
    char mode;
    char input_line[MAX_LINE_LENGTH];

    // Reading if the file given is to be compressed ('C' in the first line) or expanded ('E' in the first line)

    // Exiting the code if input is invalid
    if (scanf("%c", &mode) != 1){
        return 1;
    }  
    // First I was adding \n after %c but that resulted in the first line of the input not being solved properly

    // Remove the first line
    getchar(); 
    // The only reason I added the above getchar() is because I was getting the right output but there was always a blank line in the output file

    // Process each input line till the end of the file
    while (fgets(input_line, sizeof(input_line), stdin) != NULL) {
        
        if (mode == 'C' || mode == 'c') {
            compress_ascii_art(input_line);
        } 
        
        else if (mode == 'E' || mode == 'e') {
            expand_ascii_art(input_line);
        }
    }
    return 0;
}

// Finally code khatam hogya bahut mehnat lag gayi yaar isme 
