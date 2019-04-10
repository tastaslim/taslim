#include<stdio.h>
void push(int x);
int pop();
void sortByArrival();
int isInQueue(int i);

//Structure 

struct process
{
char name;
long Arrival_time,Completion_time;
long Burst_time,Waiting_time,Turnaround_time,Response_time;
int completed;
}p[100];
int n;
long q[100];  //queue 
int front=-1,rear=-1;//initially

//Main function starts here/Execution starts here.
int main()
{
int i,j,time=0,sum_bt=0,Time_quantum;
char c;
float avgwt=0,avgtt=0;
printf("#################################Created By TASLIM:#####################\n");
printf("                  K17SM SECTION LPU. For more info contact at taslimarif600@gmail.com         ");
printf("\n\n####################################################################################################");
 printf("\n\nEnter no of processes:");
 scanf("%d",&n);
 for(i=0,c='A';i<n;i++,c++)
 {
 p[i].name=c;
 printf("\n\t#############   PROCESS %c   ################: ",p[i].name);
 printf("\n\nEnter Arrival Time:");
 scanf("%d",&p[i].Arrival_time);
 printf("\nEnter Burst Time:");
 scanf("%d",&p[i].Burst_time);
 p[i].Response_time=p[i].Burst_time;
 p[i].completed=0;
 sum_bt+=p[i].Burst_time;
 
}
printf("\n####################################################################################################");
printf("\nEnter TIME QUANTUM:");
scanf("%d",&Time_quantum);

sortByArrival();
push(0);          // enqueue the first process
printf("\t\t\nProcess execution order: ");

for(time=p[0].Arrival_time;time<sum_bt;) // for each loop,runs until the total burst time reached
{   i=pop();

if(p[i].Response_time<=Time_quantum)
{                          /* for processes having remaining time with less than                                             or  equal  to time quantum  */
                       
time+=p[i].Response_time;
p[i].Response_time=0;
p[i].completed=1;          
    printf(" %c ",p[i].name);
            p[i].Waiting_time=time-p[i].Arrival_time-p[i].Burst_time;
            p[i].Turnaround_time=time-p[i].Arrival_time;       
            for(j=0;j<n;j++)                /*enqueue the processes which have come                                         while scheduling */
            {
            if(p[j].Arrival_time<=time && p[j].completed!=1&& isInQueue(j)!=1)
            {
            push(j);
            
            }
           }
        }
    else               // more than time quantum
    {
    time+=Time_quantum;
    p[i].Response_time-=Time_quantum;
    printf(" %c ",p[i].name);
    for(j=0;j<n;j++)    //first enqueue the processes which have come while scheduling 
            {
            if(p[j].Arrival_time<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
             {
            push(j);
            
            }
           }
           push(i);   // then enqueue the uncompleted process
           
    }

    
    
}

printf("\n\nPROCESS\t    ARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\tCOMPLETION TIME");
for(i=0;i<n;i++)
{
  p[i].Turnaround_time=p[i].Burst_time+p[i].Waiting_time;
  p[i].Completion_time=p[i].Arrival_time+p[i].Burst_time+p[i].Waiting_time;
 avgwt+=p[i].Waiting_time;
 avgtt+=p[i].Turnaround_time;
printf("\n%c\t\t%d      \t\t%d    \t\t%d  \t\t%d  \t\t%d",p[i].name,p[i].Arrival_time,p[i].Burst_time,p[i].Waiting_time,p[i].Turnaround_time,p[i].Completion_time);
}
printf("\nAverage waiting time:%2f",avgwt/n);
printf("\nAverage Turnaround time:%2f",avgtt/n);
return 0;
}

//////////push operation////////////

void push(int i) // Can call enqueue
{
if(rear==100)
{
printf("overflow");
exit(0);
}
rear++;//increaments rear
q[rear]=i;// FIFO or LILO
if(front==-1)
{
front=0;
}
}

//////////////pop operation///////////////////////////////////

int pop()   //can call dequeue
{
if(front==-1)
{
printf("underflow");
exit(0);
}
int temp=q[front];
if(front==rear)
front=rear=-1;
else
{
front++;
}
return temp;
}
///////Checking process in queue or not

int isInQueue(int i)
{int k;
for(k=front;k<=rear;k++)
{
if(q[k]==i)
return 1;
}
return 0;
}

//Sorting according to arrival time////////////
void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n-1;i++)
for(j=i+1;j<n;j++)
{
if(p[i].Arrival_time>p[j].Arrival_time)
{
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}

