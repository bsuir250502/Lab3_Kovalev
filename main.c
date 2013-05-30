#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256

typedef struct information {
    char name[STR_MAX];
    char main_info[STR_MAX];
    struct information *next;
} information_t;

typedef struct ring {
    information_t *first;
    information_t *last;
} ring_t;

void str_input(char *information, char *input_text, int max_number_of_symbols);
int int_input(char *information, int Min, int Max);
void ring_fill(ring_t point);
int ring_add(ring_t *point);
void ring_output(char *which, ring_t *point, int elements_number);
void ring_inverse(ring_t *point, int elements_number);

int main(int argc, char **argv)
{
    ring_t point;
    point.first = NULL;
    point.last = NULL;
    ring_fill(point);
    return 0;
}

void ring_fill(ring_t point)
{
    int counter = 0;
    puts ("\n-----   Enter info about appliances('stop' for input end):   -----\n");
          printf ("%d)",counter + 1);
    while (ring_add(&point)) {
        printf ("%d)",++counter + 1);
    }
    point.last->next = point.first;
    ring_output("normal", &point, counter);
    ring_inverse(&point, counter);
    ring_output("inversed", &point, counter);
}

int ring_add(ring_t *point)
{
    information_t *new_elem;
    new_elem = (information_t*)malloc(sizeof(*new_elem));
    new_elem->next = NULL;
    str_input(" name: ", new_elem->name, STR_MAX);
    if (!strcmp(new_elem->name, "stop")) {
        return 0;
    }
    str_input("   info: ", new_elem->main_info, STR_MAX);
    if (point->first == NULL) {
        point->first = new_elem;
    }
    else {
        point->last->next = new_elem;
    }
    point->last = new_elem;
    return 1;
}

void ring_inverse(ring_t *point, int counter)
{   int i,j;
    information_t *info, *element;
    info = point->last;
    for (i = counter - 2; i > 0; i--) {
        element = point->first;
        for (j = 0; j < i; j++) {
            element = element->next;
        }
        point->last->next = element;
        point->last = element;
    }
    point->last->next = point->first;
    point->last = point->first;
    point->first = info;
    point->last->next = point->first;
}

void ring_output(char *manner, ring_t *point, int counter)
{
    int i;
    information_t *info;
    info = point->first;
    printf ("The ring in %s manner\n", manner);
    for(i = 0; i < counter; i++) {
        printf ("%d) Name: %s\n   Info:%s\n",
                 i + 1, info->name, info->main_info);
        info = info->next;
    }
}

void str_input(char *information, char *input_text, int max_number_of_symbols)
{
    while (1) {
        printf("%s", information);
        fgets(input_text, max_number_of_symbols, stdin);
        if (input_text[0] == '\n' || input_text[0] == ' ') {
            puts("Invalid input, try again.");
        }
        else {
            input_text[strlen(input_text)-1]='\0';
            break;
        }
    }
}

int int_input(char *information, int Min, int Max)
{
    int input_text;
    char input_buffer[128];
    printf("%s (min - %d, max - %d): ", information, Min, Max);
    while (1) {
        fgets(input_buffer, 128, stdin);
        input_buffer[strlen(input_buffer)-1]='\0';
        if (!(input_text = atoi(input_buffer)) || input_text < Min || input_text > Max) {
            puts("Invalid input, try again.");
        }
        else {
            break;
        }
    }
    return input_text;
}
