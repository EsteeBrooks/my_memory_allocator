#include "header.h"

// Function for reporting an error and exiting program:
void error_and_exit(const char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}