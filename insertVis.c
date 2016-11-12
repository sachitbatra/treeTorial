#include<stdio.h>
#include<stdlib.h>

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

void enqueue(treeNode*, queue**, queue**);
treeNode* dequeue(queue**, queue**);
void displayTree(treeNode*, char*, int, int);
void insertIter(treeNode**, int);
void insertIterWithDisplay(treeNode**, int);

void main()
{
    treeNode *treeRoot = NULL;

    printf("1. Insert Element to Binary Tree\n2. Insert Element to Binary Tree with Visualisation.\n");
    int input, value;

    while(1)
    {
        scanf("%d",&input);

        switch(input)
        {
            case 1: printf("Insert value to be inserted: ");
                    scanf("%d",&value);
                    insertIter(&treeRoot, value);
                    break;
            case 2: printf("Insert value to be inserted: ");
                    scanf("%d",&value);
                    insertIterWithDisplay(&treeRoot, value);
                    break;
        }
    }
}

void insertIter(treeNode **root, int value)
{
    treeNode *link = (treeNode*)malloc(sizeof(treeNode));
    link->data = value;
    link->left = NULL;
    link->right = NULL;

    if (*root == NULL)
    {
        *root = link;
    }

    else
    {
        treeNode *current = *root;
        treeNode *prev = NULL;

        while(current != NULL)
        {
            prev = current;
            if (current->data > value)
            {
                current = current->left;
            }

            else if (current->data < value)
            {
                current = current->right;
            }
        }

        if (prev->data > value)
        {
            prev->left = link;
        }

        else
        {
            prev->right = link;
        }
    }
}


void displayTree(treeNode *root, char *name, int value, int insertVal)
{
    if (root == NULL)
    {
        return;
    }

    else
    {
        char integer_str[32];

        if (insertVal < value)
        {
            sprintf(integer_str, "%d < %d", insertVal, value);
        }

        else if (insertVal > value)
        {
            sprintf(integer_str, "%d > %d", insertVal, value);
        }

        else
        {
            sprintf(integer_str, "%d", insertVal);
        }

        char other_str[64] = "label = \" Insert: ";
        strcat(other_str, integer_str);
        strcat(other_str, "\"");

        FILE *fileOp = fopen("temp.dot", "w");
        fprintf(fileOp, "digraph BST\n{\n");
        fprintf(fileOp, other_str);
        fprintf(fileOp, "%d [shape = box, color = \"#ff0000\"];\n", root->data);
        int nullCount = 0;

        queue *front, *rear;
        front = rear = NULL;

        enqueue(root, &front, &rear);

        while(front != NULL)
        {
            treeNode *current = dequeue(&front, &rear);

            if (current->data == value)
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

void insertIterWithDisplay(treeNode **root, int value)
{
    treeNode *link = (treeNode*)malloc(sizeof(treeNode));
    link->data = value;
    link->left = NULL;
    link->right = NULL;

    if (*root == NULL)
    {
        *root = link;
        displayTree(*root, "Insert", value, value);
        printf("Insert\n");
    }

    else
    {
        treeNode *current = *root;
        treeNode *prev = NULL;

        int count = 0;

        while(current != NULL)
        {
            count++;
            char integer_string[32];
            sprintf(integer_string, "%d", count);

            char file_name[64] = "Insert";
            strcat(file_name, integer_string);

            prev = current;
            if (current->data > value)
            {
                displayTree(*root, file_name, current->data, value);
                printf("%s\n", file_name);
                current = current->left;
            }

            else if (current->data < value)
            {
                displayTree(*root, file_name, current->data, value);
                printf("%s\n", file_name);
                current = current->right;
            }
        }

        count++;
        char integer_string[32];
        sprintf(integer_string, "%d", count);

        char file_name[64] = "Insert";
        strcat(file_name, integer_string);

        if (prev->data > value)
        {
            prev->left = link;
            displayTree(*root, file_name, value, value);
            printf("%s\n", file_name);
        }

        else
        {
            prev->right = link;
            displayTree(*root, file_name, value, value);
            printf("%s\n", file_name);
        }
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
