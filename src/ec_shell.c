#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ec_shell.h"


char *
heading ()
{
    char *head;

    head = "\
EC 1.0.0 Shell\n\
Info: \"help\", \"copyright\", \"credits\" \"license\"\n";

    return head;
}


void
help ()
{
    char *help = "\
EC shell commands\n\
class    : define class\n\
help     : show commands\n\
exit     : exit\n";

    printf ("%s", help);
}


void
class (char *classname)
{
    char line[100];
    char temp;
    int over = 0;

    printf ("\n");
    printf ("#define EC_CLASS %s\n", classname);

    while (1)
    {
        strcpy (line, "");
        scanf ("%c", &temp);
        scanf ("%s", line);

        if (strcmp (line, "end") == 0)
        {
            printf ("EC_EXPAND(%s)\n", classname);
            printf ("#undef EC_CLASS\n\n");
            break;
        }
    }
}


int
ec_is_empty_str (char str[])
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (isgraph(str[i]))
        {
            return 0;
        }

        i++;
    }

    return 1;
}


char *
tokenize (char input[])
{
    char *s;

    s = strtok (input, " ");
    s = strtok (NULL, " ");

    return s;
}


void
shell ()
{
    char input[100];
    char temp;
    char *classname;

    printf ("%s", heading());

    printf (">>> ");
    scanf ("%[^\n]", input);

    while (strcmp (input, "exit") != 0)
    {
        /*
        if (!ec_is_empty_str (input))
        {
            printf("\n");
        }
        */

        classname  = tokenize (input);

        if (strcmp (input, "help") == 0)
        {
            help ();
        }
        else if (strcmp (input, "class") == 0)
        {
            if (classname != NULL)
                class (classname);
        }

        strcpy (input, "");

        printf (">>> ");
        scanf ("%c", &temp);
        scanf ("%[^\n]", input);
    }
}
