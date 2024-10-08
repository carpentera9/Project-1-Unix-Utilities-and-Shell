#include <stdio.h>
#include <string.h>

int main() {
    char line[1024];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        char *token = NULL;
        char *rest = line;

        while ((token = strsep(&rest, " \t\n")) != NULL) {
            if (*token != '\0') {
                printf("%s\n", token);
            }
        }
    }
    return 0;
}
