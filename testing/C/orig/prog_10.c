void expand(const char from[], char to[]);
void append(char c, char toarr[], int ofdim);
int match(char some_chars[]);

void expand(const char from[], char to[])
{
    int i, j, k;
    char last_chars[3], c;

    for (i = 0; i < 3; i++)
        last_chars[i] = '\0';
    for (i = j = 0; (c = from[i]) != '\0'; i++, j++)
    {
        append(c, last_chars, 3);

        if (match(last_chars))
        {
            j = j - 1;
            for (k = last_chars[0] + 1; k < last_chars[2]; ++k)
                to[j++] = k;
            to[j] = last_chars[2];
        }
        else
        {
            to[j] = from[i];
        }
    }
    to[j] = '\0';
}

int match(char c[])
{
    int out;

    out = isdigit(c[0]) && (c[1] == '-') && isdigit(c[2]) || islower(c[0]) && (c[1] == '-') && islower(c[2]) || isupper(c[0]) && (c[1] == '-') && isupper(c[2]);
    return out;
}

void append(char c, char arr[], int dim)
{
    int i;

    for (i = 1; i < dim; i++)
        arr[i - 1] = arr[i];
    arr[dim - 1] = c;
}