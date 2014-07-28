#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char* strncpy(char*, const char*, size_t);

char* replace_space(char* str)
{
    int i, space = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            space++;
        }
    }
    int new_len = i + space*2;
    char* new_str = (char*)calloc(new_len, sizeof(char));

    int p = i-1;
    int q = new_len-1;
    while (p >= 0) {
        if (str[p] == ' ') {
            strncpy(&new_str[q-2], "%20", 3);
            p--;
            q-=3;
        } else {
            new_str[q--] = str[p--];
        }
    }
    return new_str;
}

int main(void)
{
    char* sample = "This is a sample!";
    char* replaced = replace_space(sample);
    printf("%s\n", replaced);
}
