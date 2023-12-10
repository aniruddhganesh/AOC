#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// #define PART_ONE

/* Crates */
static long line_where_instructions_start = 0;
char buffer[40];

typedef struct Crate {
    char id;
    struct Crate *next;
    struct Crate *prev;
} Crate;

typedef struct Contaner {
    bool first_time;
    Crate *bottom;
    Crate *top;
} Container;

Container *stacks = NULL;

/* Also provides line number to start parsing from next time?
* That is line where instructions start
*/
int count_stacks(FILE *fd)
{
    char buffer[40] = {0};
    while(fgets(buffer, 40, fd)) {
        if (isdigit(buffer[1])) {
            break;
        }
    }

    /* Seems like we on 9th char so lazily subtract from there *
     * to get first location of line                           */
    line_where_instructions_start = (ftell(fd) + '\n' - 9);

    return atoi(&buffer[strlen(buffer) - 3]);
}

void stack_prepend(char value, Container *stack)
{
    Crate *new = malloc(sizeof(Crate));
    new->id = value;

    if (stack->first_time) {
        stack->top = new;
        stack->first_time = false;
    } else {
        stack->bottom->prev = new;
    }

    new->next = stack->bottom;
    stack->bottom = new;

    return;
}

void squeeze(char value, int idx)
{
    Crate *new = malloc(sizeof(Crate));
    new->id = value;

    if (stacks[idx-1].top->prev == NULL) {
        stacks[idx-1].top->prev = new;
        new->next = stacks[idx-1].top;
    } else {
        Crate *second_last = stacks[idx-1].top->prev;
        stacks[idx-1].top->prev = new;

        new->next = stacks[idx-1].top;
        second_last->next = new;
        new->prev = second_last;
    }
}


char pop(int idx)
{
    Crate *s = stacks[idx-1].top;
    char to_return = stacks[idx-1].top->id;
    if (s->prev == NULL) {
        stacks[idx-1].top = NULL;
    } else {
        stacks[idx-1].top = stacks[idx-1].top->prev;
    }
    free(s);
    return to_return;
}

void push(char value, int idx)
{
    Crate *s;
    if (stacks[idx-1].top == NULL) {
        s = stacks[idx-1].top;
    } else {
        s = stacks[idx-1].top->next;
    }

    s = malloc(sizeof(Crate));

    s->prev = stacks[idx-1].top;
    stacks[idx-1].top = s;

    s->id = value;
}


void dump_stack_data_from_file(FILE *fd, Container stacks[])
{
    char buf[40] = {0};

    rewind(fd);
    while (fgets(buf, 40, fd)) {
        if (isdigit(buf[1])) {
            break;
        }
        
        for (size_t j = 1; j < strlen(buf)-1; j += 4) {
            if (!isspace(buf[j]))
                    stack_prepend(buf[j], &stacks[j/4]);
        }

    }
    return;
}

void parse_instructions(FILE *fd)
{
    char buf[40] = {0};

    fseek(fd, line_where_instructions_start, SEEK_SET);
    while (fgets(buf, 40, fd)) {
        int amt, src, dst;
        sscanf(buf, "move %d from %d to %d", &amt, &src, &dst);

        for (int i = 1; i <= amt; i++) {
#ifndef PART_ONE
            if (i > 1) { squeeze(pop(src), dst);}
            else 
#endif
            { push(pop(src), dst); }
        }
    }
}

void top_stack_print(int y)
{
    for (int i = 0; i < y; i++) {
        printf(" [%c] ", stacks[i].bottom->id);
    }
    printf("<- Bottom\n");
    for (int i = 0; i < y; i++) {
        printf(" [%c] ", stacks[i].top->id);
    }
    printf("<- Top\n");
}

void full_stack_print(int idx)
{
    Crate *c;
    putchar('\n');

    for (c = stacks[idx-1].top; c != NULL;c = c->prev) { 
        printf("\t[%c]\n", c->id);
    }
}

void init_stacks(int num)
{
    for (int i = 0; i < num; i++) {
        stacks[i].top = NULL;
        stacks[i].bottom = NULL;
        stacks[i].first_time = true;
    }
}

int main(void)
{
    FILE *data =  fopen("./example.txt", "r");
    int num_of_stacks = count_stacks(data);

    stacks = malloc(num_of_stacks*(sizeof(Container)));
    init_stacks(num_of_stacks);

    dump_stack_data_from_file(data, stacks);
    parse_instructions(data);
    printf("-----------------------\n");
    top_stack_print(num_of_stacks);
    free(stacks);
    fclose(data);
    return 0;
}
