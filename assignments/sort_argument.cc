#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXLEN 100	// maximum length of each input word

int main(int argc, char *argv[])
{
    // if no arguments passed, exit
    if (argc == 1)
	return 0;

    // Use selection sort
    for (int i = 1; i < argc; i++)
    {
	//min_idx is index of smallest string in str_l[i....n+str - 1]
	int min_idx = i;
        for (int j = i + 1; j < argc; j++)
	{
	    if (strcmp(argv[j], argv[min_idx]) < 0)
		min_idx = j;
	}
	
	// swap pointers to string constants 
	char *temp = argv[i];
	argv[i] = argv[min_idx];
	argv[min_idx] = temp;
    }

    for (int p = 1; p < argc; p++)
        fprintf(stdout, "%s\n", argv[p]);

    return 0;
}
