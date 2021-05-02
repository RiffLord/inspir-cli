/*
 *  INSPIR, v0.3
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
#define COMMANDS 5

//  Number of suggestions each category contains
#define WRITE 48
#define ARRNG 30
#define SOUND 38
#define MIX 21

const char *program_version = "\nINSPIR CLI 0.3";
const char *bug_address = "<bruno.pezer@tutanota.com>";

//  Program documentation
static char doc[] = "\nINSPIR is a tool to help overcome creative blocks and get inspiration while producing music.\nINSPIR works by generating random, musically relevant suggestions for you to apply in your productions.\nThere are a total of 137 suggestions divided into 4 categories, representing different stages of the\nproduction process; Writing, Arranging, Sound Design or Mixing.\nA suggestion for any of the categories can be obtained by inputting the corresponding command:\n\n\t  write\n\t  arrange\n\t  sound\n\t  mix";
static char usage[] = "\nUSAGE>    inspir <category>\nEXAMPLE>  inspir write         will randomly display a suggestion to apply in your writing process.";
//  Accepted arguments
static char args_doc[] = "category";

//  Accepted options.
//  Enumeration is used in order
//  to easily pass the options to
//  the switch control structure
typedef enum {write, arrange, sound, mix, help} Command;

//  Associates the string arguments
//  with the appropriate enum options
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

//  Converts the user input into lowercase
void parse_str(char *str) {
    int i = 0;
    while (str[i]) {
        str[i] = tolower(str[i]);
        i++;
    }
}

//  Converts the string argument to the corresponding enum command
Command convert_command(const char *str) {
    for (size_t i = 0; i < COMMANDS; i++)
        if (strcmp(str, conversion[i].str) == 0) 
            return conversion[i].cmd;
    return 42;  //  Returned when a non-recognized command is provided.
}

//  Opens the file and returns the line of text
//char* read_paper(FILE f, unsigned int line) {
//    char *str;
//    size_t i = 0;
//    while (str[i]) {
//      if (str[i] == '>') str[i] = '\n';    
//    }
//    return str;    
//}

void inspir(const char *str) {
    switch(convert_command(str)) {
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
            puts(program_version);
            puts(doc);
            puts(usage);
            printf("\nSend bug reports to %s\n", bug_address);
            break;
        default:
            puts("No such category");
            break; 
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    parse_str(argv[1]);
    inspir(argv[1]);
}
