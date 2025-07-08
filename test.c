// #define BRIN_LITE

#include <brin.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
#ifndef BRIN_LITE
    Brin txt = brin_new("");

    printf("Brin instance weight: %ldB\n", sizeof(txt));

    if (txt.is_empty(&txt)) printf("True\n");
    else printf("False\n");

    txt.insert(&txt, 0, "          ");

    if (txt.is_whitespace(&txt)) printf("True\n");
    else printf("False\n");

    txt.insert(&txt, 5, "This Text Is Capitalized");
    printf("%s\n", txt.string);

    txt.to_lower(&txt);
    printf("%s\n", txt.string);

    txt.to_upper(&txt);
    printf("%s\n", txt.string);

    txt.trim_start(&txt);
    printf("trimmed start:%s\n", txt.string);

    txt.trim_end(&txt);
    printf("%s:trimmed end\n", txt.string);

    txt.destroy(&txt);

    Brin msg = brin_new("Bonjour");

    printf("Index of 'jour' in 'Bonjour': %d\n",
           msg.index_of(&msg, "jour"));

    msg.concat(&msg, " Lucas");
    msg.concat(&msg, " comment ca va ?");
    printf("Hello, World + %s\n", msg.string);

    if (msg.contains(&msg,
                     "Lucas")) printf("Lucas is contained in the message\n");
    else printf("Lucas is not contained in the message\n");
    if (msg.contains(&msg,
                     "Mathias")) printf("Mathias is contained in the message\n");
    else printf("Mathias is not contained in the message\n");

    if (msg.equals(&msg, "Bonjour Lucas comment ca va ?"))
        printf("Messages are equals\n");
    else printf("Messages aren't equals\n");

    msg.insert(&msg, 7, " Mathias et");

    printf("%s\n", msg.string);

    const char *array[] = {"This", "is", "a", "join", "test."};

    Brin join = brin_join(array, sizeof(array)/sizeof(array[0]), " ");
    printf("%s\n", join.string);

    char **split = join.split(&join, " ");
    for (size_t i = 0; split[i] != NULL; i++)
    {
        printf("%ld: %s\n", i+1, split[i]);
        free(split[i]);
    }
    free(split);

    join.destroy(&join);

    msg.destroy(&msg);
#else
    Brin txt = brin_new("");

    printf("Lite Brin instance weight: %zuB\n", sizeof(txt));

    printf("%s\n", brin_is_empty(&txt) ? "True" : "False");

    brin_insert(&txt, 0, "          ");

    printf("%s\n", brin_is_whitespace(&txt) ? "True" : "False");

    brin_insert(&txt, 5, "This Text Is Capitalized");
    printf("%s\n", txt.string);

    brin_to_lower(&txt);
    printf("%s\n", txt.string);

    brin_to_upper(&txt);
    printf("%s\n", txt.string);

    brin_trim_start(&txt);
    printf("trimmed start:%s\n", txt.string);

    brin_trim_end(&txt);
    printf("%s:trimmed end\n", txt.string);

    brin_destroy(&txt);

    Brin msg = brin_new("Bonjour");

    printf("Index of 'jour' in 'Bonjour': %d\n",
           brin_index_of(&msg, "jour"));

    brin_concat(&msg, " Lucas");
    brin_concat(&msg, " comment ca va ?");
    printf("Hello, World + %s\n", msg.string);

    printf("%s\n", brin_contains(&msg, "Lucas") ?
           "Lucas is contained in the message" :
           "Lucas is not contained in the message");

    printf("%s\n", brin_contains(&msg, "Mathias") ?
           "Mathias is contained in the message" :
           "Mathias is not contained in the message");

    printf("%s\n", brin_equals(&msg, "Bonjour Lucas comment ca va ?") ?
           "Messages are equals" :
           "Messages aren't equals");

    brin_insert(&msg, 7, " Mathias et");

    printf("%s\n", msg.string);

    const char *array[] = {"This", "is", "a", "join", "test."};

    Brin join = brin_join(array, sizeof(array)/sizeof(array[0]), " ");
    printf("%s\n", join.string);

    char **split = brin_split(&join, " ");
    for (size_t i = 0; split[i] != NULL; i++)
    {
        printf("%ld: %s\n", i+1, split[i]);
        free(split[i]);
    }
    free(split);
    brin_destroy(&join);

    brin_destroy(&msg);
#endif
    return 0;
}