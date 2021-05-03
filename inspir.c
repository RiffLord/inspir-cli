/*
 *  INSPIR, v0.5
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
#define LINECHARS 500

//  Number of suggestions each category contains
#define WRITE 47
#define ARRNG 29
#define SOUND 37
#define MIX 20

const char *program_version = "\nINSPIR CLI 0.3";
const char *bug_address = "<bruno.pezer@tutanota.com>";

//  Program documentation
static char doc[] = "\nINSPIR is a tool to help overcome creative blocks and get inspiration while producing music.\nINSPIR works by generating random, musically relevant suggestions for you to apply in your productions.\nThere are a total of 137 suggestions divided into 4 categories, representing different stages of the\nproduction process; Writing, Arranging, Sound Design or Mixing.\nA suggestion for any of the categories can be obtained by inputting the corresponding command:\n\n\t  write\n\t  arrange\n\t  sound\n\t  mix";
static char usage[] = "\nUSAGE>    inspir <category>\nEXAMPLE>  inspir write         will randomly display a suggestion to apply in your writing process.";
//  Accepted arguments
static char args_doc[] = "category";

/*  
 *  Accepted options.
 *  Enumeration is used in order
 *  to easily pass the options to
 *  the switch control structure
 */
typedef enum {write, arrange, sound, mix, help} Command;

//  Filenames for each category of suggestions
const char *FNARRNG = "arranging";
const char *FNMIX = "mixing";
const char *FNWRITE = "writing";
const char *FNSOUND = "sound_design";

/*
 *  Associates the string arguments
 *  with the appropriate enum options
 */
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

//  Formats the line of text for display
void parse_line(char* line) {
    size_t i = 0;
    while (line[i]) {
      if (line[i] == '>') line[i] = '\n';
      i++;  
    }  
}

//  Reads a line of text from the file
//  Reads a line of text from the file
void read_file(const char *filename, unsigned int line) {
    FILE *cfPtr;
    char path[50] = "..\\res\\";
    unsigned int currentline = 0;
    strcat(path, filename);
    //puts(path);
    if ((cfPtr = fopen(path, "r")) == NULL) {
        puts("Couldn't open file");
    } else {
        char suggestion[LINECHARS];
        while (!feof(cfPtr)) {
            fgets(suggestion, LINECHARS, cfPtr);
            if (currentline == line) {
                parse_line(suggestion);
                //printf("%d: %s\n", currentline + 1, suggestion);
                printf("\n%s\n", suggestion);
                break;                
            }
            currentline++;
            //  Reads the entire file
            /*   
            parse_line(suggestion);
            printf("%d: %s\n", currentline + 1, suggestion);
            fgets(suggestion, LINECHARS, cfPtr);
            currentline++;
            */
        }
        //  Reads the last line in the file
        //fgets(suggestion, LINECHARS, cfPtr);
        //printf("%d: %s\n", currentline + 1, suggestion);

    fclose(cfPtr);
    }
}

void inspir(const char *str) {
    switch(convert_command(str)) {
        unsigned int line;
        case write:
            line = (rand() % WRITE);
            //printf("%d\n", line);
            read_file(FNWRITE, line);
            break;
        case arrange:
            line = (rand() % ARRNG);
            //printf("%d\n", line);
            read_file(FNARRNG, line);
            break;
        case sound:
            line = (rand() % SOUND);
            //printf("%d\n", line);
            read_file(FNSOUND, line);
            break;
        case mix:
            line = (rand() % MIX);
            //printf("%d\n", line);
            read_file(FNMIX, line);
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
