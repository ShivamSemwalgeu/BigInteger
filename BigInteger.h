#ifndef BIGINTEGER_LIBRARY_H
#define BIGINTEGER_LIBRARY_H
struct node* createnode(struct node **head,int data);
//void display(struct BigInteger a);
struct BigInteger display(struct BigInteger a);
struct node *reverse(struct node **head);
struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger a,struct BigInteger b);
struct BigInteger sub(struct BigInteger a,struct BigInteger b);
struct BigInteger mul(struct BigInteger a,struct BigInteger b);
struct BigInteger div1(struct BigInteger a,struct BigInteger b);
#endif
