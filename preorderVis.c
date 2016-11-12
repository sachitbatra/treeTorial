#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct bTree
{
    int data;
    struct bTree *left;
    struct bTree *right;
}treeNode;

typedef struct queueNode
{
    treeNode *data;
    struct queueNode *next;
}queue;

typedef struct stackNode
{
    treeNode *data;
    struct stackNode *next;
}stack;

typedef struct listNode
{
    struct listNode *next;
    int data;
}list;

void enqueue(treeNode*, queue**, queue**);
treeNode* dequeue(queue**, queue**);
void displayTree(stack*, treeNode*, char*, list*);
void preVis(treeNode*);
void push(stack**, treeNode*);
treeNode* pop(stack**);
int isEmptyStack(stack*);
treeNode* insert(treeNode*, int);
int isPresentinStack(stack *, int);
void insertEnd(list**, int);

treeNode *treeRoot = NULL;

void main()
{
    int input, value;

    while(1)
    {
        printf("1. Insert Value into Tree.\n2. Get PreOrder Traversal Visualization.\n");
        scanf("%d",&input);

        switch(input)
        {
            case 1: printf("Insert value to be inserted: ");
                    scanf("%d",&value);
                    treeRoot = insert(treeRoot, value);
                    break;
            case 2: preVis(treeRoot);
                    break;
        }
    }
}

void displayTree(stack *stk, treeNode *root, char *name, list *listElement)
{
    if (root == NULL)
    {
        printf("Empty Tree!\n");
        return;
    }

    else
    {
        FILE *fileOp = fopen("temp.dot", "w");
        fprintf(fileOp, "digraph BST\n{\n");
        char integer_str[32];
        char other_str[64] = "label = \" Pre-Order Traversal: ";

        while (listElement!=NULL)
        {
            sprintf(integer_str, "%d -> ", listElement->data);
            strcat(other_str, integer_str);
            listElement = listElement->next;
        }
        strcat(other_str, "\"");

        fprintf(fileOp, other_str);
        fprintf(fileOp, "%d [shape = box, color = \"#ff0000\"];\n", root->data);
        int nullCount = 0;

        queue *front, *rear;
        front = rear = NULL;

        enqueue(root, &front, &rear);

        while(front != NULL)
        {
            treeNode *current = dequeue(&front, &rear);

            if (isPresentinStack(stk, current->data))
            {
                fprintf(fileOp, "%d [fillcolor = red, style = filled];", current->data);
            }

            if ((!current->left) && (!current->right) && (current!=root))
            {
                fprintf(fileOp, "%d [color = \"blue\"];", current->data);
            }

            if (current->left)
            {
                fprintf(fileOp, "%d -> %d;\n", current->data, current->left->data);
                enqueue(current->left, &front, &rear);
            }

            else
            {
                nullCount++;
                fprintf(fileOp, "NULL%d [shape=point];\n %d -> NULL%d;\n", nullCount, current->data, nullCount);
            }

            if (current->right)
            {
                fprintf(fileOp, "%d -> %d;\n", current->data, current->right->data);
                enqueue(current->right, &front, &rear);
            }

            else
            {
                nullCount++;
                fprintf(fileOp, "NULL%d [shape=point];\n %d -> NULL%d;\n", nullCount, current->data, nullCount);
            }
        }

        fprintf(fileOp, "\n}");
        fclose(fileOp);

        //system("PATH=C:\\Program Files (x86)\\Graphviz\\bin");
        //system("cd C:\\Users\\sachi\\Desktop");
        char cmd[] = "dot -Tpng temp.dot -o ";
        strcat(cmd, name);
        strcat(cmd, ".png");
        system(cmd);
    }
}

treeNode* insert(treeNode *node, int value)
{
    if (node == NULL)
    {
        treeNode *link = (treeNode*)malloc(sizeof(treeNode));
        link->data = value;
        link->left = link->right = NULL;
        node = link;
    }

    else if (value < (node->data))
    {
        node->left = insert(node->left,value);
    }

    else if (value > (node->data))
    {
        node->right = insert(node->right,value);
    }

    return node;
}

void preVis(treeNode *root)
{
    stack *stk = NULL;
    list *head = NULL;
    int count = 0;
    while(1)
    {
        while(root)
        {
            count++;
            char integer_string[32];
            sprintf(integer_string, "%d", count);

            char file_name[64] = "preOrder";
            strcat(file_name, integer_string);

            insertEnd(&head ,root->data);
            push(&stk, root);
            root = root->left;
            displayTree(stk, treeRoot, file_name, head);
            printf("%s\n", file_name);
        }

        if(isEmptyStack(stk))
        {
            break;
        }

        root = pop(&stk);
        root = root->right;

        count++;
        char integer_string[32];
        sprintf(integer_string, "%d", count);

        char file_name[64] = "preOrder";
        strcat(file_name, integer_string);

        displayTree(stk, treeRoot, file_name, head);
        printf("%s\n", file_name);
    }
}

void enqueue(treeNode *node, queue **first, queue **rear)
{
    queue *link = (queue*)malloc(sizeof(queue));
    link->data = node;
    link->next = NULL;

    if (*first == NULL)
    {
        *first = *rear = link;
    }

    else
    {
        (*rear)->next = link;
        (*rear) = link;
    }
}

treeNode* dequeue(queue **first, queue **rear)
{
    queue *temp;
    treeNode *retVal;
    temp = *first;

    if (temp == NULL)
    {
        return NULL;
    }

    else
    {
        retVal = temp->data;

        if ((*first) == (*rear))
        {
            (*first) = (*rear) = NULL;
        }

        else
        {
            (*first) = temp->next;
        }

        free(temp);
        return retVal;
    }
}

void push(stack **stk, treeNode *node)
{
    stack *link = (stack*)malloc(sizeof(stack));
    link->data = node;
    link->next = *stk;
    *stk = link;
}

treeNode* pop(stack **stk)
{
    if (isEmptyStack(*stk))
    {
        printf("Underflow Exception!\n");
        return NULL;
    }

    stack *temp = *stk;
    treeNode *node = temp->data;
    *stk=temp->next;
    free(temp);
    return node;
}

int isEmptyStack(stack *stk)
{
    if(stk == NULL)
    {
        return 1;
    }

    return 0;
}

int isPresentinStack(stack *stk, int value)
{
    while((stk!=NULL) && (stk->data->data!=value))
    {
        stk = stk->next;
    }

    if (stk == NULL)
    {
        return 0;
    }

    else
    {
        return 1;
    }
}

void insertEnd(list **headNode, int value)
{
    list *link = (list*)malloc(sizeof(list));
    link->data = value;
    link->next = NULL;

    if (*headNode == NULL)
    {
        *headNode = link;
    }

    else
    {
        list *temp = *headNode;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = link;
    }
}
