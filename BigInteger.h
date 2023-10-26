#include <stdarg.h>
#include <stdio.h>

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

typedef unsigned char bool;
#define false 0
#define true 1

struct node 
{
    int data;
    struct node *next;
};

struct BigInteger
{
    bool sign;
    unsigned int capacity;
    unsigned int nodigits;
    struct node *list;
};


struct BigInteger allocateBigint (unsigned int capacity);

struct node* Newnode (int data);

int isnull (struct BigInteger a);

int length (struct node *b);

struct node* duplicate(struct node *b1);

struct node* reverse (struct node *s);

int comp (struct BigInteger b1,struct BigInteger b2);

void dis (struct node *head);

void display (struct BigInteger b);

struct BigInteger initialize (char *str);

struct BigInteger add (struct BigInteger b1,struct BigInteger b2);

struct BigInteger sub(struct BigInteger b1,struct BigInteger b2);

int compare (struct BigInteger d,struct BigInteger b);

struct BigInteger dupl(struct BigInteger b1);

struct BigInteger div1(struct BigInteger b1,struct BigInteger b2);

struct BigInteger mod(struct BigInteger b1,struct BigInteger b2);

void push(struct node** head, int data);

struct node* make_empty_list(int size);

struct BigInteger mul(struct BigInteger b1, struct BigInteger b2);

#endif