// COMP 281 Assignment 2 Part 2
// Author: Maadhyam Rawal-->201765354
// Description: Converting numbers provided in the form of integers to words

#include <stdio.h>
#include <stdlib.h>


// Word mappings for numbers
const char* single_digit_words[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
const char* teen_words[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const char* tens_words[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const char* scale_words[] = {"", "Thousand", "Million", "Billion"};



// Making a function to calculate the length of the string
size_t get_string_length(const char* str) {
    size_t length = 0;

    while (str[length] != '\0') {
        length++;
    }
    return length;
}



// Making a function to concatenate two strings
void concatenate_strings(char* destination, const char* source) {
    while (*destination) {
        destination++;
    }

    while (*source) {
        *destination++ = *source++;
    }
    
    *destination = '\0';
}



// Making a function to convert three-digit numbers into words
void convert_three_digit_number(int number, char* output_buffer, int is_subunit) {
    int hundreds = number / 100;
    int remainder = number % 100;

    if (hundreds > 0) {
        char temp[50];
        sprintf(temp, "%s Hundred", single_digit_words[hundreds]);
        concatenate_strings(output_buffer, temp);

        if (remainder > 0) {
            // Include "and"
            // I initally forgot about 'and' and the '-' in the code 
            concatenate_strings(output_buffer, " and ");
        }
    }


    if (remainder >= 20) {
        int tens = remainder / 10;
        int ones = remainder % 10;
        concatenate_strings(output_buffer, tens_words[tens]);
        
        if (ones > 0) {
            concatenate_strings(output_buffer, "-");
            concatenate_strings(output_buffer, single_digit_words[ones]);
        }
    } 
    
    else if (remainder >= 10) {
        concatenate_strings(output_buffer, teen_words[remainder - 10]);
    } 
    
    else if (remainder > 0) {
        concatenate_strings(output_buffer, single_digit_words[remainder]);
    }
}



// Making a function to convert a full number into words
char* convert_number_to_words(int number) {
    if (number == 0) {
        char* zero_output = (char*)malloc(5 * sizeof(char));
        sprintf(zero_output, "Zero");
        return zero_output;
    }
    
    // Trying to allocate a space for output
    char* output_buffer = (char*)calloc(1024, sizeof(char)); 
    int scale_index = 0;
    int is_negative = 0;

    // Converting a negative number to positive for processing
    // I initially forgot about the fact that negative numbers are also being tested in the code just realised it the mmorning of the submission
    if (number < 0) {
        is_negative = 1;
        number = -number; 
    }

    // Just checking if the last chunk was less than 100
    int last_chunk_was_small = 0; 
    
    while (number > 0) {
        // Processing only non-zero chunks
        if (number % 1000 != 0) { 
            char chunk_buffer[256] = "";
            convert_three_digit_number(number % 1000, chunk_buffer, scale_index > 0);

            if (scale_index > 0) {
                char temp[50];
                sprintf(temp, " %s", scale_words[scale_index]);
                concatenate_strings(chunk_buffer, temp);
            }

            char new_output[1024];
            
            // Add "and" if the last chunk was small (< 100) and we're appending to a larger chunk
            if (last_chunk_was_small && get_string_length(output_buffer) > 0) {
                sprintf(new_output, "%s and %s", chunk_buffer, output_buffer);
            } 
            
            else {
                sprintf(new_output, "%s%s%s", chunk_buffer, (output_buffer[0] != '\0' ? " " : ""), output_buffer);
            }

            output_buffer[0] = '\0';
            concatenate_strings(output_buffer, new_output);

            // Tracking small chunks
            last_chunk_was_small = (number % 1000 < 100); 
        }
        number /= 1000;
        scale_index++;
    }
    

    // Prepending "Minus " if the original number was negative
    // I initially forgot about the fact that negative numbers are also being tested in the code just realised it the mmorning of the submission
    if (is_negative) {
        char new_output[1024];
        sprintf(new_output, "Minus %s", output_buffer);
        output_buffer[0] = '\0';  
        concatenate_strings(output_buffer, new_output);
    }

    // Reduce the trailing space.
    size_t length = get_string_length(output_buffer);
    if (length > 0 && output_buffer[length - 1] == ' ') {
        output_buffer[length - 1] = '\0';
    }

    return output_buffer;
}

// Main Function
// Reading numbers from input and printing their word representations
int main() {
    int number;
    while (scanf("%d", &number) != EOF) {
        char* words = convert_number_to_words(number);
        printf("%d => %s\n", number, words);
    }
    return 0;
}

// Finally code khatam hogya bahut mehnat lag gayi yaar isme 
