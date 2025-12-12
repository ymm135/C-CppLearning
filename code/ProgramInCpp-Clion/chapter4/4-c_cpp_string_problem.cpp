#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

/*
 * C String Problems Demonstration
 * 
 * Main problems with C strings (char*):
 * 1. Buffer overflow risk
 * 2. O(n) time to get length
 * 3. Cannot contain binary data ('\0' terminator)
 * 4. Inefficient string concatenation (multiple reallocations)
 * 5. No record of allocated memory size
 */

// ============ Problem 1: Buffer Overflow ============
void problem1_buffer_overflow() {
    cout << "\n=== Problem 1: Buffer Overflow ===" << endl;
    
    char buffer[10];  // Only 10 bytes
    
    // Dangerous: strcpy doesn't check boundaries
    // strcpy(buffer, "This is a very long string");  // Would overflow! Commented to avoid crash
    
    // Safer way: use strncpy
    strncpy(buffer, "This is a very long string", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
    
    cout << "After copy: " << buffer << endl;
    cout << "Explanation: strncpy only copied 9 characters, avoiding overflow" << endl;
}

// ============ Problem 2: O(n) Length Complexity ============
void problem2_length_complexity() {
    cout << "\n=== Problem 2: O(n) to Get Length ===" << endl;
    
    const char* str = "Hello, World!";
    
    // strlen must traverse the entire string until '\0'
    size_t len = strlen(str);
    
    cout << "String: " << str << endl;
    cout << "Length: " << len << " (strlen must traverse the whole string)" << endl;
    cout << "Explanation: Frequent calls to strlen waste CPU time" << endl;
}

// ============ Problem 3: Cannot Store Binary Data ============
void problem3_binary_data() {
    cout << "\n=== Problem 3: Cannot Store Binary Data ===" << endl;
    
    // C strings end with '\0', so data containing '\0' will be truncated
    char binary_data[] = {'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd', '\0'};
    
    cout << "Actual data length: " << sizeof(binary_data) << " bytes" << endl;
    cout << "Using C string functions: \"" << binary_data << "\"" << endl;
    cout << "strlen: " << strlen(binary_data) << " (stops at first \\0)" << endl;
    cout << "Explanation: C strings cannot store data containing '\\0' bytes" << endl;
}

// ============ Problem 4: Inefficient String Concatenation ============
void problem4_append_inefficiency() {
    cout << "\n=== Problem 4: Inefficient Concatenation ===" << endl;
    
    char* str = (char*)malloc(10);
    strcpy(str, "Hello");
    
    // Append " World"
    const char* append = " World";
    
    // Must manually calculate new length and reallocate
    size_t old_len = strlen(str);
    size_t append_len = strlen(append);
    size_t new_len = old_len + append_len;
    
    // Reallocate memory
    char* new_str = (char*)realloc(str, new_len + 1);
    if (new_str) {
        str = new_str;
        strcat(str, append);
    }
    
    cout << "After concatenation: " << str << endl;
    cout << "Explanation: Each concatenation may require memory reallocation, inefficient" << endl;
    
    free(str);
}

// ============ Problem 5: No Record of Allocated Size ============
void problem5_no_allocated_size() {
    cout << "\n=== Problem 5: No Record of Allocated Size ===" << endl;
    
    char* str = (char*)malloc(100);  // Allocated 100 bytes
    strcpy(str, "Hello");
    
    cout << "Actually used: " << strlen(str) << " bytes" << endl;
    cout << "Allocated: 100 bytes (but C strings cannot know this)" << endl;
    cout << "Remaining space: Cannot obtain directly" << endl;
    cout << "Explanation: Must recalculate or remember allocation size for each append" << endl;
    
    free(str);
}

int main() {
    cout << "=====================================" << endl;
    cout << "  C String Problems Demonstration" << endl;
    cout << "=====================================" << endl;
    
    problem1_buffer_overflow();
    problem2_length_complexity();
    problem3_binary_data();
    problem4_append_inefficiency();
    problem5_no_allocated_size();
    
    cout << "\n=====================================" << endl;
    cout << "Summary: These limitations of C strings" << endl;
    cout << "led Redis to design SDS (Simple Dynamic" << endl;
    cout << "String) to solve these problems." << endl;
    cout << "=====================================" << endl;
    
    return 0;
}
