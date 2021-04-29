/*
 *  INSPIR, v0.2
 *  https://elphnt.io/store/inspir-paper/
 *  
 *  @author: Bruno Pezer
 *  28/04/2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAXARGS 2

//  Number of suggestions each category contains
#define WRITE 48
#define ARRNG 30
#define SOUND 38
#define MIX 21

typedef enum {write, arrange, sound, mix, help} Command;

const static struct {
    Command cmd;
    const char *str;
} conversion[] = {
    {write, "write"},
    {arrange, "arrange"},
    {sound, "sound"},
    {mix, "mix"},
    {help, "help"}
};

const char *parse_str(const char *str) {
    unsigned int str_size = sizeof(str) / sizeof(str[0]);   //  Calculate the size of the input string
    char *parsed_str = malloc(str_size);                    //  Allocate memory from the heap
    int i = 0;
    while(str[i]) {
        parsed_str[i] = tolower(str[i]);
        i++;
    }
    return parsed_str;
}

Command convert_command(const char *str) {
    for (size_t j = 0; j < sizeof(conversion) / sizeof(conversion[0]); j++) {
        if (strcmp(str, conversion[j].str) == 0) return conversion[j].cmd;
    }
    puts("No such category.");
    return help;
}

void inspir(Command cmd) {
    switch(cmd) {
        case write:
            puts("selected: write");
            printf("%d", (rand() % WRITE) + 1);
            break;
        case arrange:
            puts("selected: arrange");
            printf("%d", (rand() % ARRNG) + 1);
            break;
        case sound:
            puts("selected: sound design");
            printf("%d", (rand() % SOUND) + 1);
            break;
        case mix:
            puts("selected: mix");
            printf("%d", (rand() % MIX) + 1);
            break;
        case help:
            puts("selected: help");
            break;
        default:
            puts("No such category");
            break; 
    }
}

char* read_paper() {}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    inspir(convert_command(parse_str(argv[1])));
}
