//cc -Wall -Wextra -Werror replace.c -o place && cc -Wall -Wextra -Werror repl.c -o rep && ./place > place_out.txt && ./rep > rep_out.txt && diff place_out.txt rep_out.txt

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
   og           refers to the original string passed in
   displace     refers to the word to be replaced
   sub          refers to the word to replace displace with
*/
char    *repl(char *og, char *displace, char *sub)
{
    // get the length of each param
    int len_og = strlen(og);
    int len_dis = strlen(displace);
    int len_sub = strlen(sub);

    int occur = -1;
    // shift is initialized to the original string and it will be shifted to the right
    char *shift = og;
    // extracted will be wherever displace is found in shift/og
    char *extracted = strstr(shift, displace);
    while (extracted != NULL)
    {
        occur++;
        extracted = strstr(shift, displace);
        if (extracted != NULL)
            // shift is shifted to the right till the end of extracted
            shift = extracted + len_dis;
    }
    //printf("displace occurs %i amount of times in og\n", occur);

    int diff = len_sub - len_dis;
    //printf("difference in characters between sub and displace\n%s - %s = %i\n", sub, displace, len_sub - len_dis);
    // "hello helloworld" (16)
    // "goodbye goodbyeworld" (20)
    // "goodbye" - "hello / 7 - 5 (2)
    // 2 occurrences * 2 (4)
    // 16 + 4 = 20
    char *ret = malloc(sizeof(char) * (len_og + (diff * occur) + 1));
    char *tmp = ret;
    int moved;

    while (occur--)
    {
        shift = strstr(og, displace);
        
        // gives a segfault because strlen is unsafe
        //moved = len_og - strlen(shift);
        // get the length of beginning of og till the first occurence of displace
        moved = shift - og;
        
        //ret = strncpy(ret, og, moved);
        // if strncpy into ret, ret will have to increment which loses the part before displace
        //tmp = strncpy(tmp, og, moved);
        // copy the part from beginning of og till the first occurence of displace
        strncpy(tmp, og, moved);
        
        //shift tmp to the end which is also right before the beginning of displace
        tmp += moved;
        
        //tmp = strcpy(tmp, sub);
        // copy sub into tmp which is also right at where displace begins
        strcpy(tmp, sub);
        
        //shift tmp to the end of sub
        tmp += len_sub;
        
        //shift og to after the substitued displace
        og += moved + len_dis;
    }
    strcpy(tmp, og);
    return (ret);
}

int main()
{
    char *s = "idkhelpWTF JESUS CHRIST JESUSmother JESUSJESUSJESUS holyJESUSwater";
    char *r = repl(s, "JESUS", "chickenegg");
    printf("%s\n", r);
}
