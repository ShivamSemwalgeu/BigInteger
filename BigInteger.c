#include <stdio.h>
#include <stdlib.h>

struct BigInteger {
    struct node *l;
    int length;
};

struct node {
    struct node *next;
    int data;
};

struct node *createnode(struct node **head, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
    } else {
        struct node *cur = *head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = temp;
    }
    return temp;
}

struct node *reverse(struct node **head) {
    struct node *prev = NULL, *current = *head, *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    return *head;
}

struct BigInteger initialize(char *s) {
    struct BigInteger a;
    struct node *node = NULL;
    int i, len = 0;
    for (i = 0; s[i] != '\0'; i++) {
        int digit = s[i] - '0';
        len++;
        createnode(&node, digit);
    }
    a.l = node;
    a.length = len;
    return a;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct node *bigA = reverse(&a.l);
    struct node *bigB = reverse(&b.l);
    struct node *result = NULL;
    int sum = 0, carry = 0;
    while (bigA || bigB) {
        sum = 0;
        if (bigA) {
            sum = sum + bigA->data;
        }
        if (bigB) {
            sum = sum + bigB->data;
        }
        sum = sum + carry;
        carry = sum / 10;
        sum = sum % 10;
        createnode(&result, sum);
        if (bigA) {
            bigA = bigA->next;
        }
        if (bigB) {
            bigB = bigB->next;
        }
    }
    if (carry)
        result = createnode(&result, carry);
    result = reverse(&result);
    struct BigInteger c;
    c.l = result;
    return c;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) 
{
    struct node *bigA = reverse(&a.l);
    struct node *bigB = reverse(&b.l);
    struct node *result = NULL;
    int borrow = 0;

    while (bigA || bigB) {
        int numA = bigA ? bigA->data : 0;
        int numB = bigB ? bigB->data : 0;
        int diff = numA - numB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        createnode(&result, diff);

        if (bigA) {
            bigA = bigA->next;
        }
        if (bigB) {
            bigB = bigB->next;
        }
    }

    // Remove leading zeros from the result.
    while (result && result->data == 0) {
        struct node *temp = result;
        result = result->next;
        free(temp);
    }

    // If the result is empty, it means a - b is zero.
    if (!result) {
        struct BigInteger zero;
        zero.l = createnode(&zero.l, 0);
        zero.length = 1;
        return zero;
    }

    result = reverse(&result);

    struct BigInteger c;
    c.l = result;
    return c;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b) {
    struct node *bigA = a.l;
    struct node *bigB = b.l;
    struct node *result = NULL;
    int n1 = 0, n2 = 0, n3;
    struct node *itr = bigA;
    struct node *ptr = bigB;
    while (itr) {
        n1 = n1 * 10 + itr->data;
        itr = itr->next;
    }
    while (ptr) {
        n2 = n2 * 10 + ptr->data;
        ptr = ptr->next;
    }
    n3 = n1 / n2;
    while (n3 > 0) {
        createnode(&result, n3 % 10);
        n3 = n3 / 10;
    }
    struct node *res = reverse(&result);
    struct BigInteger c;
    c.l = res;
    return c;
}

void display(struct BigInteger a) {
    struct node *itr = a.l;
    while (itr) {
        printf("%d", itr->data);
        itr = itr->next;
        a.length++;
    }
   // printf("\nlength of big integer=%d\n", a.length);
}
