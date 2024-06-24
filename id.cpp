#include <stdio.h>

int main() {
    std::string filename = "example.txt";
    FILE* fp = fopen(filename.c_str(), "wb");
    if (fp != nullptr) {
        // File opened successfully, you can write to it here
        // Remember to close the file when you're done using fclose(fp)
    } else {
        // Failed to open the file, handle the error
    }
    return 0;
}
