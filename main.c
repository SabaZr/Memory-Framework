#include <stdio.h>
#include <stdlib.h>

enum type {Integer, Double, Char, Float};
struct adrs{
    void* start;
    void* end;
    enum type t;
    int count;
    int* if_int;
    float* if_float;
    double* if_double;
    char* if_char;
    int val_int;
    float val_float;
    double val_double;
    char val_char;
} adrs;

struct adrs Allocation(enum type t, int count);
struct adrs Write(void *arr, int count, enum type t);
struct adrs Read(void* start, void* end, enum type t);
void Free(struct adrs a);
struct adrs Reallocation(struct adrs a, int count);

int main() {
}
struct adrs Write(void *arr, int count, enum type t)
{
    struct adrs a = Allocation(t, count);

    for(int i=0;i<count;i++)
    {
        switch (t) {
            case Integer:
                a.if_int[i] = ((int*) arr)[i];
                break;
            case Double:
                a.if_double[i] = ((double*) arr)[i];
                break;
            case Float:
                a.if_float[i] = ((float *) arr)[i];
                break;
            case Char:
                a.if_char[i] = ((char*) arr)[i];
                break;
        }
    }
    return a;
}
struct adrs Read(void* start, void* end, enum type t)
{
    struct adrs a;
    a.t = t;
    a.start = start;
    a.end = end;
    switch (t) {
        case Integer:
            a.if_int = (int*) a.start;
            a.count = (int*) a.end - (int*)a.start + 1;
            break;
        case Double:
            a.if_double = (double*) a.start;
            a.count = (double*) a.end - (double*)a.start + 1;
            break;
        case Float:
            a.if_float = (float*) a.start;
            a.count = (float*) a.end - (float*)a.start + 1;
            break;
        case Char:
            a.if_char = (char*) a.start;
            a.count = (char*) a.end - (char*)a.start + 1;
            break;
    }
    return a;
}

void Free(struct adrs a)
{
    free(a.start);
}

struct adrs Reallocation(struct adrs a, int count)
{
    struct adrs alloced;
    alloced.count = count;
    int n = (count < a.count)?count:a.count;
    switch (a.t) {
        case Integer:
            alloced = Allocation(a.t, count);
            for (int i = 0; i < n; i++)
                alloced.if_int[i] = a.if_int[i];
            break;
        case Double:
            alloced = Allocation(a.t, count);
            for (int i = 0; i < n; i++)
                alloced.if_double[i] = a.if_double[i];
            break;
        case Float:
            alloced = Allocation(a.t, count);
            for (int i = 0; i < n; i++)
                alloced.if_float[i] = a.if_float[i];
            break;
        case Char:
            alloced = Allocation(a.t, count);
            for (int i = 0; i < n; i++)
                alloced.if_char[i] = a.if_char[i];
            break;
    }
    Free(a);
    return adrs;
}

struct adrs Allocation(enum type t, int count)
{
    struct adrs a;
    a.count = count;

    switch (t) {
        case Integer:
            a.start = malloc(sizeof(int)*count);
            a.end = a.start + ((count-1)*sizeof(int));
            a.t = Integer;
            a.if_int = (int*) a.start;
            return a;
        case Double:
            a.start = malloc(sizeof(double )*count);
            a.end = a.start + ((count-1)*sizeof(double));
            a.t = Double;
            a.if_double = (double*) a.start;
            return a;
        case Char:
            a.start = malloc(sizeof(char )*count);
            a.end = a.start + ((count-1)*sizeof(char));
            a.t = Char;
            a.if_char = (char*) a.start;
            return a;
        case Float:
            a.start = malloc(sizeof(float )*count);
            a.end = a.start + ((count-1)*sizeof(float));
            a.t = Float;
            a.if_float = (float*) a.start;
            return a;
        default:
            break;
    }
    return a;
}


