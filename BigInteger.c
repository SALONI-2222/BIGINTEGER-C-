#include "BigInteger.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct BigInteger allocateBigint (unsigned int capacity)
{
    struct BigInteger ret;
    ret.capacity=capacity;
    ret.nodigits=0;
    ret.sign=true;
    ret.list=NULL;
    return ret;
}

int isnull (struct BigInteger a)
{
    struct node *n = duplicate(a.list);
    while (n)
    {
        if (n->data != 0)
        {
            return 1;
        }
        n=n->next;
    }
    return 0;
}


struct node* Newnode (int data)
{
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}

int length (struct node *b)
{
    int l=0;
    struct node *n=reverse(duplicate(b));
    while (n->data == 0)
    {
        n=n->next;
    }
    while (n)
    {
        l++;
        n=n->next;
    }
    return l;
}

struct node* duplicate(struct node *b1) 
{
    struct node *list = NULL; 
    struct node *current = b1;
    struct node *prev = NULL;
    struct node *newDigits = NULL;

    while (current) 
    {
        struct node *newNode = Newnode(current->data);
        if (!prev) 
        {
            list= newNode;  
        }
        else 
        {
            prev->next = newNode; 
        }
        prev = newNode;
        current = current->next;
    }

    return list;
}

struct node* reverse (struct node *s)
{
    struct node *prev = NULL;
    struct node *nxt = NULL;
    struct node *current = s;
    while (current != NULL)
    {
        nxt = current->next;
        current ->next = prev;
        prev = current;
        current = nxt;
    }
    return prev;
}

int comp (struct BigInteger b1,struct BigInteger b2)
{
    struct node *head1=reverse(duplicate(b1.list));
    struct node *head2=reverse(duplicate(b2.list));
    while (head1->data == 0)
    {
        head1=head1->next;
    }
    while (head2->data == 0)
    {
        head2=head2->next;
    }
    while (head1)
    {
        if (head1->data > head2->data)
        {
            return 1;
        }
        else if (head1->data < head2->data)
        {
            return 2;
        }
        else 
        {
            return 0;
        }
        head1=head1->next;
        head2=head2->next;
    }
}

void dis(struct node *head)
{
    if (!head)
    {
        return;
    }
    dis(head->next);
    printf ("%d",head->data);
    
}

void display (struct BigInteger b)
{
    struct node *head=b.list;
    if (b.sign == false)
    {
        printf ("-");
    }
    dis (head);
    printf ("\n");
}

struct BigInteger initialize (char *str)
{
    unsigned int len = strlen (str);
    unsigned int noDigits = len;
    int i=0;
    bool sign = true;
    if (str[0] == '-')
    {
        sign = false;
        i++;
    }

    if (noDigits == 0)
    {
        return allocateBigint(0);
    }

    struct BigInteger ret = allocateBigint(noDigits);
    ret.nodigits=noDigits;
    ret.sign=sign;

    for (i; i < noDigits; i++)
    {
        char c= str[i];
        if (c>='0' && c<='9')
        {
            struct node *temp=(struct node*)malloc(sizeof(struct node));
            int d=c-'0';
            temp->data = d;
            temp->next=ret.list;
            ret.list=temp;
        }
        else
        {
            struct node *temp=(struct node*)malloc(sizeof(struct node));
            temp->data = 0;
            temp->next=ret.list;
            ret.list=temp;
        }
    }
    return ret;

}

struct BigInteger add (struct BigInteger b1,struct BigInteger b2)
{
    if (!b1.nodigits || (isnull(b1)==0))
    {
        return b2;
    }
    if (!b2.nodigits || (isnull(b2)==0))
    {
        return b1;
    }
    
    struct BigInteger res;
    struct node *itr=(struct node*)malloc(sizeof(struct node));
    struct node *resnode=NULL;
    res.nodigits=0;
    res.sign=true;
    res.list=NULL;
    if (b1.sign == false && b2.sign == true)
    {
        b1.sign=true;
        res=sub(b2,b1);
        return res;
    }
    if (b1.sign == true && b2.sign== false)
    {
        b2.sign=true;
        res=sub(b1,b2);
        return res;
    }
    int l1=length(b1.list);
    int l2=length(b2.list);
    struct node *n1=NULL,*n2=NULL;
    if (l1>l2)
    {
        n1=duplicate(b1.list);
        n2=duplicate(b2.list);
    }
    else
    {
        n1=duplicate(b2.list);
        n2=duplicate(b1.list);
    }
    while ((n1!=NULL) && (n2!=NULL))
    {
        res.nodigits++;
        int d=n1->data+n2->data;
        if (d>9)
        {
            d-=10;
            if (!n1->next)
            {
                n1->next=Newnode(1);
            }
            else
            {
                n1->next->data++;
            }    
        }
        if (!(resnode))
        {
            resnode=Newnode(d);
            itr=resnode;
            n1=n1->next;
            n2=n2->next;

        }
        else
        {
            itr->next=Newnode(d);
            itr=itr->next;
            n1=n1->next;
            n2=n2->next;
        }
    }
    while (n1)
    {
        res.nodigits++;
        itr->next=Newnode(n1->data);
        itr=itr->next;
        n1=n1->next;
    }
    while (n2)
    {
        res.nodigits++;
        itr->next=Newnode(n2->data);
        itr=itr->next;
        n2=n2->next;
    }
    res.capacity=res.nodigits;
    if (b1.sign == false && b2.sign == false)
    {
        res.sign=false;
    }
    resnode=reverse(resnode);
    while (resnode->data == 0) 
    {
        struct node* temp = resnode;
        resnode = resnode->next;
        free(temp);
        res.nodigits--;
    }
    resnode=reverse(resnode);
    res.list=resnode;
    return res;
}

struct BigInteger sub(struct BigInteger b1,struct BigInteger b2)
{
    if (!b1.nodigits || (isnull(b1)==0))
    {
        b2.sign = false;
        return b2;
    }
    if (!b2.nodigits || (isnull(b2)==0))
    {
        return b1;
    }
    struct BigInteger res;
    struct node *resnode=NULL;
    res.nodigits=0;
    res.sign=true;
    res.list=NULL;
    if (b1.sign == false && b2.sign == true)
    {
        b1.sign=true;
        res=add(b2,b1);
        res.sign=false;
        return res;
    }
    if (b2.sign == false)
    {
        b2.sign=true;
        res=add(b1,b2);
        return res;
    }
    int l1=length(b1.list);
    int l2=length(b2.list);
    struct node *h1=NULL;
    struct node *h2=NULL;
    if (l1<l2)
    {
        h1=b2.list;
        h2=b1.list;
    }
    else if (l1==l2)
    {
        if (comp(b1,b2)==2)
        {
            h1=b2.list;
            h2=b1.list;
            res.sign=false;
        }
        else
        {
            h1=b1.list;
            h2=b2.list;
        } 
    }
    else
    {
        h1=b1.list;
        h2=b2.list;
    }
    struct node *itr=(struct node*)malloc(sizeof(struct node));
    while ((h1!=NULL) && (h2!=NULL))
    {
        res.nodigits++;
        int d=h1->data-h2->data;
        if (d<0)
        {
            if (!h1->next)
            {
                res.sign=false;
                d=0;
            }
            else
            {
                if (h1->next->data <= 0)
                {
                    h1->next->data +=10;
                    h1->next->next->data --;
                }
                h1->next->data--;
                d+=10;
            }
        }
        if (!(resnode))
        {
            resnode=Newnode(d);
            itr=resnode;
            h1=h1->next;
            h2=h2->next;

        }
        else
        {
            itr->next=Newnode(d);
            itr=itr->next;
            h1=h1->next;
            h2=h2->next;
        }
    }
    while (h1)
    {
        res.nodigits++;
        itr->next=Newnode(h1->data);
        itr=itr->next;
        h1=h1->next;
    }
    while (h2)
    {
        res.nodigits++;
        itr->next=Newnode(h2->data);
        itr=itr->next;
        h2=h2->next;
    }
    res.capacity=res.nodigits;
    if (l1<l2)
    {
        res.sign=false;
    }
    struct node *s=duplicate(resnode);
    struct node *x=s;
    while (s->next)
    {
        if (s->data < 0)
        {
            s->data+=10;
            s->next->data --;
        }
        s=s->next;
    }
    resnode=duplicate(x);
    resnode=reverse(resnode);
    while (resnode->data == 0) 
    {
        struct node* temp = resnode;
        resnode = resnode->next;
        free(temp);
        res.nodigits--;
    }
    resnode=reverse(resnode);
    res.list=resnode;
    return res;
}

struct BigInteger dupl(struct BigInteger b1) 
{
    struct BigInteger ret;
    ret.capacity = b1.capacity;
    ret.nodigits = b1.nodigits;
    ret.sign = b1.sign;
    ret.list = NULL; 
    struct node *current = b1.list;
    struct node *prev = NULL;
    struct node *newDigits = NULL;

    while (current) 
    {
        struct node *newNode = Newnode(current->data);
        if (!prev) 
        {
            ret.list = newNode;  
        } 
        else 
        {
            prev->next = newNode; 
        }
        prev = newNode;
        current = current->next;
    }

    return ret;
}


int compare (struct BigInteger d,struct BigInteger b)
{
    struct BigInteger s = sub(dupl(d),dupl(b));
    //display(s);
    if (s.sign == false)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

struct BigInteger div1(struct BigInteger b1,struct BigInteger b2)
{
    struct BigInteger a1=dupl(b1);
    a1.sign=true;
    struct BigInteger a2=dupl(b2);
    a2.sign=true;
    long long int quotient=0;
    struct BigInteger q;
    if (!b1.nodigits || (isnull(dupl(a1))==0))
    {
        q.list=Newnode(0);
        return q;
    }
    if (compare(dupl(a1),dupl(a2))==0)
    {
        q.list=Newnode(0);
        return q;
    }
    if (!b2.nodigits || (isnull(dupl(a2))==0))
    {
        printf ("Division don't exists.\n");
        q.list=Newnode(0);
        return q;
    }
    struct BigInteger a=sub(dupl(a1),dupl(a2));
    int l=isnull(a);
    if (l==0)
    {
        q.list=Newnode(1);
        return q;
    }
    while (compare(dupl(a1),dupl(a2)))
    {
        quotient++;
        a1=sub(dupl(a1),dupl(a2));
    }      
    struct node *list= Newnode(quotient);
    q.list = duplicate(list);
    if ((b1.sign == false  && b2.sign == true)) 
    {
        q.sign=false;
    }
    if ((b2.sign == false  && b1.sign == true))
    {
        q.sign=false;
    }
    return q;
}

struct BigInteger mod(struct BigInteger b1,struct BigInteger b2)
{
    struct BigInteger a1=dupl(b1);
    a1.sign=true;
    struct BigInteger a2=dupl(b2);
    a2.sign=true;
    struct BigInteger m;
    if (!b1.nodigits || (isnull(dupl(a1))==0))
    {
        m.list=Newnode(0);
        return m;
    }
    if (compare(dupl(a1),dupl(a2))==0)
    {
        return a2;
    }
    if (!b2.nodigits || (isnull(dupl(a2))==0))
    {
        printf ("Division don't exists.\n");
        m.list=Newnode(0);
        return m;
    }
    struct BigInteger a=sub(dupl(a1),dupl(a2));
    int l=isnull(a);
    if (l==0)
    {
        m.list=Newnode(0);
        return m;
    }
    while (compare(dupl(a1),dupl(a2)))
    {
        a1=sub(dupl(a1),dupl(a2));
    }
    m=dupl(a1);
    struct node *res=m.list;
    res=reverse(res);
    while (res->data == 0) 
    {
        struct node* temp = res;
        res = res->next;
        free(temp);
        m.nodigits--;
    }
    res=reverse(res);
    m.list=res;
    if (b1.sign == false) 
    {
        m.sign=false;
    }
    return m;
}

void push(struct node** head, int data)
{
    struct node* new_node = Newnode(data);
    new_node->next = (*head);
    (*head) = new_node;
}
 

struct node* make_empty_list(int size)
{
    struct node* head = NULL;
    while (size--)
        push(&head, 0);
    return head;
}

struct BigInteger mul(struct BigInteger b1, struct BigInteger b2)
{
    if (!b1.nodigits || (isnull(dupl(b1))==0))
    {
        return b1;
    }
    if (!b2.nodigits || (isnull(dupl(b2))==0))
    {
        return b2;
    }
    struct node *first =b1.list;
    struct node *second =b2.list;
    first=reverse(first);
    while (first->data == 0) 
    {
        struct node* temp = first;
        first = first->next;
        free(temp);
        b1.nodigits--;
    }
    first=reverse(first);
    second=reverse(second);
    while (second->data == 0) 
    {
        struct node* temp = second;
        second = second->next;
        free(temp);
        b2.nodigits--;
    }
    second=reverse(second);
    int m =length (first) , n = length(second);
    struct BigInteger result = allocateBigint (m + n + 1);
    struct node* res= make_empty_list(m + n + 1);
 
    struct node *second_ptr = second,*result_ptr1 = res, *result_ptr2, *first_ptr;
 
    while (second_ptr) 
    {
 
        int carry = 0;
 
        result_ptr2 = result_ptr1;
 
        first_ptr = first;
 
        while (first_ptr) 
        {
            int multi = first_ptr->data * second_ptr->data + carry;
            result_ptr2->data += multi % 10;
            carry = multi / 10 + result_ptr2->data / 10;
            result_ptr2->data = result_ptr2->data % 10;
 
            first_ptr = first_ptr->next;
            result_ptr2 = result_ptr2->next;
        }
        if (carry > 0) 
        {
            result_ptr2->data += carry;
        }
 
        result_ptr1 = result_ptr1->next;
        second_ptr = second_ptr->next;
        result.nodigits++;
    }
    res=reverse(res);
    while (res->data == 0) 
    {
        struct node* temp = res;
        res = res->next;
        free(temp);
        result.nodigits--;
    }
    res=reverse(res);
    result.list=res;
    if ((b1.sign == false  && b2.sign == true)) 
    {
        result.sign=false;
    }
    if ((b2.sign == false  && b1.sign == true))
    {
        result.sign=false;
    }
    return result;
}
