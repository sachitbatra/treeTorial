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
void displayTree(treeNode *root);

void displayTree(treeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    else
    {
        FILE *fileOp = fopen("temp.dot", "w");
        fprintf(fileOp, "digraph BST\n{\n");
        fprintf(fileOp, "label = \"Tree-Torial\"\n");
        fprintf(fileOp, "%d [shape = box, color = \"#ff0000\"];\n", root->data);
        int nullCount = 0;

        queue *front, *rear;
        front = rear = NULL;

        enqueue(root, &front, &rear);

        while(front != NULL)
        {
            treeNode *current = dequeue(&front, &rear);

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
        system("dot -Tpng temp.dot -o BST.png");
        system("BST.png");
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
