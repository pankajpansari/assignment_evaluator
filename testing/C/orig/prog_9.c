#include <stdio.h>

/*
Exercise 2-5. Write the function any(s1, s2), which returns the first location in the string s1 where any character from the string s2 occurs,
or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)
*/

int any(char s1[], char s2[]);

int main()
{
    char str[] = "The quick brown fox jumped over the lazy dog!";
    printf("%s '%s' %d\n", str, " ", any(str, " "));
    printf("%s '%s' %d\n", str, "aeiouy", any(str, "aeiouy"));
    printf("%s '%s' %d\n", str, "bcdfghjklmn", any(str, "bcdfghjklmn"));
    printf("%s '%s' %d\n", str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", any(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    printf("%s '%s' %d\n", str, "!", any(str, "!"));
    printf("%s '%s' %d\n", str, "ABCDEFGHIJKLMNOPQRSUVWXYZ", any(str, "ABCDEFGHIJKLMNOPQRSUVWXYZ"));
    printf("%s '%s' %d\n", str, "\t", any(str, "\t"));
    return 0;
}

// squeeze: returns first location of any char within s2 that is found in s1. Returns -1 if no chars found
int any(char s1[], char s2[])
{
    int i, j;
    for (i = 0; s1[i] != '\0'; i++)
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i + 1;

    return -1;
}