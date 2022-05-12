/* Calculates the best name based on the requested criteria*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHAR 20

void find_smaller_name_variant(char* name, int namesize, char* minname);
void reorganise_name(char* name, int namesize);
int read_word_in_line(char* word);

int main(void)
{

    freopen("names.in", "r", stdin);
    freopen("names.out", "w", stdout);

    struct names {
        char mainname[MAX_CHAR+1];
        char minname[MAX_CHAR+1];
        int namesize;
    };



    int namecount;
    scanf("%d\n", &namecount);

    struct names namelist[namecount];


    for (int i = 0; i < namecount; i++) {
        namelist[i].namesize = read_word_in_line(namelist[i].mainname);
        find_smaller_name_variant(namelist[i].mainname, namelist[i].namesize, namelist[i].minname);
    }

    struct names bestname = namelist[0];
    for (int i = 1; i < namecount; i++) {
        if (strcmp(bestname.minname, namelist[i].minname) > 0)
            bestname = namelist[i];
    }

    printf("%s", bestname.mainname);

}


void find_smaller_name_variant(char* name, int namesize, char* minname)
{
   char tempname[MAX_CHAR+1];
    strcpy(tempname, name);
    strcpy(minname, name);

    for (reorganise_name(tempname, namesize); strcmp(name, tempname); reorganise_name(tempname, namesize)) {
        if (strcmp(minname, tempname) > 0) {
            strcpy(minname, tempname);
        }
    }


}

void reorganise_name(char* name, int namesize)
{
    char last = name[namesize - 1];

    for (int i = namesize - 2; i >= 0; i--) {
        name[i + 1] = name[i];
    }

    name[0] = last;
}

int read_word_in_line(char* word)
{
    int length = 0;
    for (char c = getchar(); c != '\n' && c != EOF; c = getchar()) {
        word[length++] = c;
    }

    word[length] = '\0';
    return length;
}