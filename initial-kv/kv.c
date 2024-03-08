#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int size = 0;
int KEYS[100];
char VALUES[100][255];
int getIndex(int key) {
    for (int i = 0; i < size; ++i) {
        if (KEYS[i] == key) {
            return i;
        }
    }
    return -1;
}
char *getValue(int key) {
    int index = getIndex(key);
    if (index != -1) {
        return VALUES[index];
    }
    return NULL;
}
void put(int key, char value[]) {
    int index = getIndex(key);
    if (index != -1) {
        strcpy(VALUES[index], value);
    } else {
        KEYS[size] = key;
        strcpy(VALUES[size], value);
        size++;
    }
}

int main(int argc, char *argv[]) {
    FILE *database = NULL;
    database = fopen("database.txt", "a+");
    char line[255];
    while (fgets(line, 255, database) != NULL) {
        char *temp = line;
        temp[strlen(temp) - 1] = '\0';
        char *sKey = strsep(&temp, ",");
        int key = atoi(sKey);
        KEYS[size] = key;
        char *sValue = strsep(&temp, ",");
        strcpy(VALUES[size], sValue);
        size++;
    }
    fclose(database);
    if (argc >= 2) {
        for (int i = 1; i < argc; ++i) {
            char *input = argv[i];
            char *cmd = strsep(&input, ",");
            if (strcmp(cmd, "p") == 0) {
                char *sKey = strsep(&input, ",");
                if (sKey == NULL) {
                    printf("Error on sKey\n");
                    return 0;
                }
                int key = atoi(sKey);
                if (key == 0) {
                    printf("Error on key\n");
                    return 0;
                }
                char *sValue = strsep(&input, ",");
                if (sValue == NULL) {
                    printf("Error on sValue\n");
                    return 0;
                }
                put(key, sValue);
            }
            else if (strcmp(cmd, "g") == 0) {
                char *sKey = strsep(&input, ",");
                if (sKey == NULL) {
                    printf("Error on sKey\n");
                    return 0;
                }
                int key = atoi(sKey);
                if (key == 0) {
                    printf("Error on key\n");
                    return 0;
                }
                char *value = getValue(key);
                if (value == NULL) {
                    printf("%d not found\n", key);
                }
                else {
                    printf("%d,%s\n", key, value);
                }
            }
            else if (strcmp(cmd, "d") == 0) {
                char *sKey = strsep(&input, ",");
                if (sKey == NULL) {
                    printf("Error on sKey\n");
                    return 0;
                }
                int key = atoi(sKey);
                if (key == 0) {
                    printf("Error on key\n");
                    return 0;
                }
                int index = getIndex(key);
                if (index == -1) {
                    printf("%d not found\n", key);
                }
                else {
                    for (int j = index; j < size - 1; ++j) {
                        KEYS[j] = KEYS[j + 1];
                        strcpy(VALUES[j], VALUES[j + 1]);
                    }
                    size--;
                }
            }
            else if (strcmp(cmd, "c") == 0) {
                size = 0;
                fclose(fopen("database.txt", "w"));
            }
            else if (strcmp(cmd, "a") == 0) {
                for (int j = 0; j < size; ++j) {
                    printf("%d,%s\n", KEYS[j], VALUES[j]);
                }
            }
            else {
                printf("bad command\n");
            }
        }
    }
    database = fopen("database.txt", "w");
    for (int i = 0; i < size; ++i) {
        fprintf(database, "%d,%s\n", KEYS[i], VALUES[i]);
    }
    fclose(database);
    return 0;
}
