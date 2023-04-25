#include <stdio.h>
#include <stdlib.h>
#define TYPE int
#define STACKSIZE 1000
typedef struct Stack Stack;
struct Stack
{
    int top;
    TYPE *items;
    int capacity;
};

Stack *constStack()
{
    Stack *s=malloc(sizeof(Stack));
    s->top=0;//  or this.top=0;
    s->items=(TYPE*) malloc(STACKSIZE*sizeof(TYPE));
    s->capacity=STACKSIZE;
    return s;
}
void push(Stack *s,TYPE value)
{
    s->items[s->top++]=value;
}
TYPE pop(Stack *s)
{
    return s->items[--s->top];
}
TYPE peek(Stack *s)
{
    return s->items[s->top-1];
}
int  isempty(Stack *s)
{
    return s->top==0?1:0;
}
int  isfull(Stack *s)
{
    return s->top<s->capacity?0:1;
}
void err()
{
    printf("Error in expression");
    exit(0);
}
int prec(char c)
{
    switch (c)
    {
    case '+' :
    case '-' :
        return 1;
    case '*' :
    case '/' :
        return 2;
    case '(':
        return 0;
    default  :
        printf("Error No Such operator[%c]",c);
        return -1;
    }
}
int lessPrec(char ch1,char ch2)
{
    return prec(ch1)<prec(ch2);
}
int VERBOSE=1;
void infPos(const char*inf,char *post)
{
    char ch;
    int index=0,j=0,i=0;
    Stack *s=constStack();
    while ((ch =inf[i++]))
    {
        if (ch==' ' )
            continue;

        if (ch>='0' && ch<= '9')
        {
            post[index++]=ch;

            if(inf[i]>='0' && inf[i]<= '9')
            {
                ch =inf[i++];
                post[index++]=ch;
                post[index++]=' ';
            }
            else
                post[index++]=' ';
        }

        else if (ch=='(')
            push(s,ch);


        else if (ch==')')
            // pop up to (
        {
            while(!isempty(s) && peek(s)!='(')
            {
                post[index++]=pop(s);
                post[index++]=' ';
            }

            if (isempty(s)|| peek(s)!='(')
                err();
            pop(s);
        }


        else
        {
            // operator
            while(!isempty(s) && peek(s)!='(' && lessPrec( ch,peek(s) ))
            {
                post[index++]=pop(s);
                post[index++]=' ';
            }
            push(s,ch);
        }

    }
    while(!isempty(s))
    {
        if (peek(s)=='(')
            err();
        post[index++]=pop(s);
    }// remaining
    post[index++]=0;

}
int main()
{
    char out[100];
    infPos("(((89+7)-(7-44))/(99-4*2))",out);
    printf("%s",out);
    return 0;
}
