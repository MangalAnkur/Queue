#include<stdio.h>
struct QueueADT
{
    int capacity;
    int front;
    int rear;
    int *arr;
};
struct QueueADT* createqueue(int cap);
int isemptyqueue(struct QueueADT *Q);
int isfullqueue(struct QueueADT *Q);
int queuecapacity(struct QueueADT *Q);
void doublequeue(struct QueueADT *Q);
void halfqueue(struct QueueADT *Q);
void enqueue(struct QueueADT *Q,int value);
void dequeue(struct QueueADT *Q);
struct QueueADT* deletequeue(struct QueueADT *Q);
int menu();
struct QueueADT* createqueue(int cap)
{
   struct QueueADT *temp;
    temp=(struct QueueADT *)malloc(sizeof(struct QueueADT));
    temp->front=-1;
    temp->rear=-1;
    temp->capacity=cap;
    temp->arr=(int *)malloc(sizeof(int)*cap);
    return (temp);
};

int isemptyqueue(struct QueueADT *Q)
{
    if(Q->front ==-1 )
        return 1;                   //It is empty
    else
        return 0;                   //not empty
}

int isfullqueue(struct QueueADT *Q)
{
    if(Q->front == 0 && Q->rear==Q->capacity-1)
        return 1;
    else if(Q->front==Q->rear+1)
        return 1;
    else
        return 0;
}

int queuecapacity(struct QueueADT *Q)
{
    return (Q->capacity);
}

void doublequeue(struct QueueADT *Q)
{
    int i,j;
    int *temp;
    Q->capacity=(Q->capacity)*2;
    temp= (int *)malloc(sizeof(int)*Q->capacity);
    for(j=0,i=Q->front;i!=Q->rear;j++)
    {
        temp[j]=Q->arr[i];
        if(i==(Q->capacity/2)-1 && Q->rear != i)
            i=0;
        else
            i++;
    }
    free (Q->arr);
    Q->front=0;
    Q->rear=(Q->capacity/2)-1;
    Q->arr=temp;
}

void halfqueue(struct QueueADT *Q)
{
    int *temp;
    int i,j,length;
    length=(Q->capacity/2);
    temp = (int *)malloc(sizeof(int)*length);
    for(i=0,j=Q->front;i<length;i++)
    {
        temp[i]=Q->arr[j];
        if(j==Q->capacity-1)
            j=0;
        else
            j++;
    }
    free (Q->arr);
    Q->arr=temp;
    Q->front=0;
    Q->rear=length-1;
    Q->capacity=length;
}


void enqueue(struct QueueADT *Q,int value)
{
    if(Q->capacity<1)
        printf("\n Invalid Capacity");
    else
    {
        if(isemptyqueue(Q))
        {
            Q->arr[0]=value;
            Q->front=0;
            Q->rear=0;
        }
        else if(isfullqueue(Q))
        {
            doublequeue(Q);
            Q->rear=Q->rear+1;
            Q->arr[Q->rear]=value;
        }
        else
        {
            if(Q->rear==Q->capacity-1)
                Q->rear==0;
            else
                Q->rear=Q->rear+1;

            Q->arr[Q->rear]=value;
        }
    }
}


void dequeue(struct QueueADT *Q)
{
    int i,size=0;
    if(isemptyqueue(Q))
        printf ("\n Queue is empty");
    else if(Q->front==Q->rear)
    {
        Q->front = -1;
        Q->rear = -1;
    }
    else if(Q->front==Q->capacity-1)
        Q->front=0;
    else
        Q->front=Q->front+1;
    //Now we will check that the no of elements in array are half of the capacity or not
    if(Q->front > -1)
    {
        for(i=Q->front;i!=Q->rear;)
        {
            size ++;
            if(i==Q->capacity-1)
                i=0;
            else
                i++;
        }
        size ++;
        if(size==(Q->capacity)/2)   //elements in array are half of the capacity
          halfqueue(Q);                           //so make half size of the array
    }
}

struct QueueADT* deletequeue(struct QueueADT *Q)
{
    free (Q->arr);
    free (Q);
    return NULL;
}

int menu()
{
    int choice;
    system ("cls");
    printf("\n1.See the status of Queue");
    printf("\n2.Insert value in Queue");
    printf("\n3.Delete value from Queue");
    printf("\n4.End Program");
    printf("\n Please Enter your choice ");
    scanf("%d",&choice);
    return choice;
}

main()
{
    int value;
    struct QueueADT *Q;
    Q=createqueue(4);
    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("\n capacity = %d",queuecapacity(Q));
            printf("\n front =%d rear= %d",Q->front,Q->rear);
            break;
        case 2:
            printf("\n Enter the value to insert in queue");
            scanf("%d",&value);
            enqueue(Q,value);
            break;
        case 3:
            dequeue(Q);
            printf("\n Data has deleted");
            break;
        case 4:
            Q=deletequeue(Q);
            exit(0);
            break;
        default:
            printf("\n Invalid choice");
        }
        getch();
    }
}
