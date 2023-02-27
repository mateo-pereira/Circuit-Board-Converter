#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct node {
   char *letter;
   int truthVal;
   struct node *next;
}Node;

typedef enum { AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER } kind_t;

typedef struct gate {
kind_t kind;
int size; 
char **inputs;
char **outputs;
}gate;

typedef struct gateNode {
   gate *current;
   struct gateNode *next;
}gateNode;

void insertVar(Node** head, char *string, int truthVal)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
 
    Node *ptr = *head;
    new_node->letter  = string;
    new_node->next = NULL;
    new_node->truthVal = truthVal;
 
    if (*head == NULL)
    {
       *head = new_node;
       return;
    } 
      
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = new_node;
    return;   
}

void insertGateNode(gateNode** head, gate *gate)
{
    gateNode* new = (gateNode*) malloc(sizeof(gateNode));
    gateNode* ptr = *head;
    new->current = gate;
    new->next = NULL;
    if (*head == NULL)
    {
       *head = new;
       return;
    } 

    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = new;
    return;   
}

Node * getNode(Node* head, char *string)
{
    Node* current = head;
    while (current != NULL) 
    {
        if (strcmp(current->letter,string) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void freeList(Node* head)
{
   Node* temp;

   while (head != NULL)
    {
       temp = head;
       head = head->next;
       free(temp->letter);
       free(temp);
    }
}

void freeGate(gateNode* head)
{
    gateNode* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        for (int i = 0;i<temp->current->size;i++)
        {
            free(temp->current->inputs[i]);
        }
        free(temp->current->inputs);
        free(temp->current->outputs);
        free(temp->current);
        free(temp);
    }
}

int main(int argc, char* argv[])
{
    Node * inputHead = NULL;
    Node * outputHead = NULL;
    Node * tempHead = NULL;
    FILE *fp = fopen("example.txt","r");
    char *input = (char*)malloc(15*sizeof(char));
    char *output = (char*)malloc(15*sizeof(char));
    int numInputs;
    int numOutputs;
    int tempOutputs;
    fscanf(fp, "%5s", input);
    fscanf(fp, "%d",&numInputs);
    int iterations = (1 << numInputs);
    for (int i = 0; i<numInputs;i++)
    {
        char *temp = malloc(17*sizeof(char));
        fscanf(fp,"%s",temp);
        insertVar(&inputHead,temp,0);
    }
    fscanf(fp,"%6s",output);
    fscanf(fp, "%d",&numOutputs);
    for (int i = 0; i<numOutputs;i++)
    {
        char *temp = malloc(17*sizeof(char));
        fscanf(fp,"%s",temp);
        insertVar(&outputHead,temp,0);
    }
    int check = 1;
    int operations = 0;
    char *operand = (char*)malloc(15*sizeof(char));
    gateNode *operGateLL = NULL;
    gateNode *gateLLptr = operGateLL;
    while(check != 0)
    {
        int check = fscanf(fp,"%s",operand);
        if (check <= 0) break;
        char **twoDInputs = (char**)malloc(20*sizeof(char));
        char **twoDOutputs = (char**)malloc(20*sizeof(char));
        gate *operGate = (gate*)malloc(sizeof(gate));
        if (strcmp(operand,"AND") == 0)
        {
            operGate->kind = AND;
            operGate->size = 2;
            for (int i = 0; i < 2; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));

            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));

            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDInputs[1]);

            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"NOT") == 0)
        {
            operGate->kind = NOT;
            operGate->size = 1;
            for (int i = 0; i < 1; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));

            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));

            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"OR") == 0)
        {
            operGate->kind = OR;
            operGate->size = 2;
            for (int i = 0; i < 2; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));

            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));
            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDInputs[1]);
            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"NAND") == 0)
        {
            operGate->kind = NAND;
            operGate->size = 2;
            for (int i = 0; i < 2; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));

            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));
            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDInputs[1]);
            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"NOR") == 0)
        {
            operGate->kind = NOR;
            operGate->size = 2;
            for (int i = 0; i < 2; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));
                
            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));
            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDInputs[1]);
            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"XOR") == 0)
        {
            operGate->kind = XOR;
            operGate->size = 2;
            for (int i = 0; i < 2; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));

            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));
            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDInputs[1]);
            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"PASS") == 0)
        {
            operGate->kind = PASS;
            operGate->size = 1;
            for (int i = 0; i < 2; i++)
                twoDInputs[i] = (char*)malloc(20*sizeof(char));

            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));
            fscanf(fp,"%s",twoDInputs[0]);
            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }
        if (strcmp(operand,"MULTIPLEXER") == 0)
        {
            operGate->kind = MULTIPLEXER;
            fscanf(fp,"%d",&operGate->size);
            int temp = operGate->size;
            for (int i = 0; i < temp + (1 << temp); i++)
            {
                twoDInputs[i] = (char*)malloc(20*sizeof(char));
                fscanf(fp,"%s",twoDInputs[i]);
            }
            for (int i = 0; i < 1; i++)
                twoDOutputs[i] = (char*)malloc(20*sizeof(char));

            fscanf(fp,"%s",twoDOutputs[0]);
            operGate->inputs = twoDInputs;
            operGate->outputs = twoDOutputs;
            operations++;
        }

        insertGateNode(&operGateLL,operGate);
        //& means pass a pointer to whatever is after
    }
    gateLLptr = operGateLL;
    Node *inputptr = inputHead;
    int x = 0;
    int count = numInputs - 1;
    for (int i = 0;i < iterations;i++)
    {
        gateLLptr = operGateLL;
        count = numInputs - 1;
        inputptr = inputHead;
        while (inputptr != NULL) //Sets the truth val for every letter in the input
        {
            x = (i >> count) & 1; //means im looking the counth bit for the number i
            inputptr->truthVal = x;
            inputptr = inputptr->next;
            count--;
            printf("%d ",x);
        }
        printf("| ");
        int var = 0;
        int varTwo = 0;
        int result = 0;
        for (int j = 0;j < operations;j++)
        {   
            if (getNode(inputHead,gateLLptr->current->inputs[0]) != NULL) //Checks to see if the input is a temp or actual input, if its a temp, use the temp LL instead
                var = getNode(inputHead,gateLLptr->current->inputs[0])->truthVal;
            else if (strcmp(gateLLptr->current->inputs[0],"0") == 0 || strcmp(gateLLptr->current->inputs[0],"1") == 0)
            {
                var = atoi(gateLLptr->current->inputs[0]);
            }
            else
            {
                var = getNode(tempHead,gateLLptr->current->inputs[0])->truthVal;
            }

            if (gateLLptr->current->size > 1)
            {
                if (getNode(inputHead,gateLLptr->current->inputs[1]) != NULL) //Checks to see if the input is a temp or actual input, if its a temp, use the temp LL instead, if there is a 2nd input
                    varTwo = getNode(inputHead,gateLLptr->current->inputs[1])->truthVal;
                else if (strcmp(gateLLptr->current->inputs[0],"0") == 0 || strcmp(gateLLptr->current->inputs[0],"1") == 0)
                {
                    var = atoi(gateLLptr->current->inputs[0]);
                }
                else
                    varTwo = getNode(tempHead,gateLLptr->current->inputs[1])->truthVal;
            }
            if (gateLLptr->current->kind == MULTIPLEXER)
            {
                int temp = 0;
                int size = gateLLptr->current->size;
                int j = (1 << gateLLptr->current->size) - 1;
                for (int i = size - 1; i >= 0;i--)
                {
                    if (strcmp(gateLLptr->current->inputs[j],"0") == 0 || strcmp(gateLLptr->current->inputs[j],"1") == 0)
                    {
                        int truthVal = atoi(gateLLptr->current->inputs[j]);
                        if (truthVal == 1)
                        {
                            temp |= 1 << i;
                            j++;
                        }
                    }
                    else
                    {
                        Node *nodePtr = getNode(inputHead,gateLLptr->current->inputs[j]);
                        if (nodePtr != NULL && nodePtr->truthVal == 1)
                        {
                            temp |= 1 << i;
                            j++;
                        }
                        if (nodePtr == NULL)
                        {
                            Node *tempPtr = getNode(tempHead,gateLLptr->current->inputs[j]);
                            if (tempPtr->truthVal == 1)
                            {
                                temp |= 1 << i;
                                j++;
                            }
                        }
                    }
                    
                }
                result = getNode(tempHead,gateLLptr->current->inputs[temp])->truthVal;
            }
            if (gateLLptr->current->kind == AND)
                result = var && varTwo;
                
            if (gateLLptr->current->kind == NOT)
                result = !var;

            if (gateLLptr->current->kind == OR)
                result = var || varTwo;

            if (gateLLptr->current->kind == NAND)
                result = !(var && varTwo);

            if (gateLLptr->current->kind == NOR)
                result = !(var || varTwo);

            if (gateLLptr->current->kind == XOR)
                result = (var && !varTwo) || (!var && varTwo);
            if (getNode(outputHead,gateLLptr->current->outputs[0]) == NULL) //If the output of this operation is not an original output, put it in temp
                {
                    if (getNode(tempHead,gateLLptr->current->outputs[0]) != NULL)
                    {
                        getNode(tempHead,gateLLptr->current->outputs[0])->truthVal = result;
                    }
                    else 
                    {   
                        insertVar(&tempHead,gateLLptr->current->outputs[0],result);
                        tempOutputs++;
                    }
                }
            else
                getNode(outputHead,gateLLptr->current->outputs[0])->truthVal = result;
            gateLLptr = gateLLptr->next;
        }
        Node *outputptr = outputHead;
        while (outputptr != NULL)
        {
            printf("%d ",outputptr->truthVal);
            outputptr = outputptr->next;
        }
        printf("\n");    
    }
    freeList(inputHead);
    freeList(outputHead);
    freeList(tempHead);
    freeGate(operGateLL);
    free(input);
    free(output);
    free(operand);
}