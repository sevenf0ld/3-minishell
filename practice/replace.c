//cc -Wall -Wextra -Werror replace.c -o place && cc -Wall -Wextra -Werror repl.c -o rep && ./place > place_out.txt && ./rep > rep_out.txt && diff place_out.txt rep_out.txt

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        //fprintf(stderr, "-----------------------------------------\n");
        //printf("begin og: %s (result %s)\n", orig, result);
        ins = strstr(orig, rep);
        //printf("ins: %s (result %s)\n", ins, result);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front);
        //printf("tmp strncpy: %s (result %s)\n", tmp, result);
        tmp += len_front;
        //printf("tmp + len_front: %s (result %s)\n", tmp, result);
        tmp = strcpy(tmp, with);
        //printf("tmp strcpy: %s (result %s)\n", tmp, result);
        tmp += len_with;
        //printf("tmp + with: %s (result %s)\n", tmp, result);
        orig += len_front + len_rep; // move to next "end of rep"
        //printf("end og: %s (result %s)\n", orig, result);
        //fprintf(stderr, "-----------------------------------------\n");
    }
    strcpy(tmp, orig);
    return result;
}

int main()
{
    char *s = "idkhelpWTF JESUS CHRIST JESUSmother JESUSJESUSJESUS holyJESUSwater";
    char *r = str_replace(s, "JESUS", "chickenegg");
    printf("%s\n", r);;
}
