/* railway management system

DSA mini project
team number- 9
team members- PES1UG19ME081(Jaishankar), PES1UG19ME906(Shruti)


*/
#include<stdio.h>
#include<stdlib.h>
typedef struct booking
{
    //structure representing a seat with it's booking id and coach number
    int bookingid;
    int coach;
} booking;
typedef struct waiting
{
    //a singly linked list for the waiting list
    booking info;
    struct waiting* next;
}node;
int bookingcount=0;
void display_specific_seats(booking* reserved, int coachtype, int coachseats[3])
{
    // function to retrieve available seats or if a specific type of seat is available
    int max=0;
    for( int i=0 ; i<coachtype; i++)
    {
        max+=coachseats[i];
    }
    int min=max-coachseats[coachtype-1];
    int free_seats=0;
    for(int i=min;i<max;i++)
    {
        if(reserved[i].bookingid==-1)
        {
            printf("seat number - %d in coach %d\n",i,coachtype);
            free_seats+=1;
        }
    }
    if(free_seats==0)
    {
        printf("All seats in the coach are booked \n");
    }
    else
    {
        printf("Number of free seats = %d \n",free_seats);
    }
} 
int count(node* waiting, int coachtype)
{ 
    // function to check how many bookings are currently present in the waiting list
    int c=0;
    while(waiting != NULL)
    {
        if(waiting->info.coach==coachtype)
        {
            c++;
        }
        waiting=waiting->next;
    }
    return c;
}
node* input(booking* reserved, node* waitinglist, int coachseats[3])
{   
    //function to add a new booking
    node* waiting;
    waiting=waitinglist;
    int a=2;
    while(a!=3)
    {
        booking_selection:
        printf("Input type of seat \n");
        printf("1)seater\n2)3rd class sleeper\n3)2nd class sleeper\n4)1st class sleeper\n5)all seats\nEXIT\n");
        int coachtype;
        scanf("%d",&coachtype);
        if(coachtype==5)
        {
            for( int i=1 ;i<=4;i++)
            {
                display_specific_seats(reserved,i,coachseats);
            }
            goto booking_selection;
        }
        else if(coachtype<5)
        {
            display_specific_seats(reserved,coachtype,coachseats);
        }
        else
        {
            break;
        }
        printf(" 1)To book seat in the coach selected\n");
        printf(" 2)To check availability in another coach\n");
        printf(" 3)Exit\n");
        scanf("%d",&a);
        if(a==1)
        {
            int max=0;
            for( int i=0 ; i<coachtype; i++)
            {
                max+=coachseats[i];
            }
            int min=max-coachseats[coachtype-1];
            int free_seats=0;
            for(int i=min;i<max;i++)
            {
                if(reserved[i].bookingid==-1)
                {
                    free_seats+=1;
                }
            }
            printf("Number of seats required ");
            int number=10;
            scanf("%d",&number);
            if(number>free_seats)
            {
                printf("Selected number of seats not available (select action from choices)\n");
                printf("1)To re-enter number of seats\n");
                printf("2)To change coach\n");
                printf("3)To book with waiting list\n");
                printf("Exit to main menu\n");
                int choice;
                scanf("%d",&choice);
                switch (choice)
                {
                    case 1:
                        scanf("%d",&number);
                        break;
                    case 2:
                        goto booking_selection;
                        break;
                    case 3:
                        if(free_seats>0)
                        {
                            printf("available seats in coach = %d \n",free_seats);
                            printf("do you wish to continue booking with %d seats reserved and %d seats in waiting\n",free_seats,number-free_seats);
                            printf("1)continue\n");
                            printf("return to main menu\n");
                            int cont;
                            scanf("%d",&cont);
                            if(cont==1)
                            {
                                number=number-free_seats;
                                printf("seats booked with booking id %d to %d\n",bookingcount+1,bookingcount+free_seats);
                                for(int i=min;i<max;i++)
                                {
                                    if(reserved[i].bookingid==-1)
                                    {
                                        if(free_seats>0)
                                        {
                                            reserved[i].bookingid=++bookingcount;
                                            reserved[i].coach=coachtype;
                                            free_seats--;
                                        }
                                        else
                                        {
                                            break;
                                        }   
                                    }
                                }
                                printf("reservation made in waiting list with bookingid %d to %d\n",bookingcount+1,bookingcount+number);
                                for( int i=0; i<number;i++)
                                {
                                    node* newnode=malloc(sizeof(node));
                                    newnode->info.bookingid=++bookingcount;
                                    newnode->info.coach=coachtype;
                                    newnode->next=NULL;
                                    if(waiting==NULL)
                                    {
                                        waitinglist=newnode;
                                        waiting=newnode;
                                    }
                                    else
                                    {
                                        while(waiting->next!=NULL)
                                        {
                                            waiting=waiting->next;
                                        }
                                        waiting->next=newnode;
                                    }
                                }
                            }
                            else
                            {
                                goto booking_selection;
                            }
                        }
                        else
                        {
                            printf("waiting list for coach = %d \n",count(waiting,coachtype));
                            printf("reservation made in waiting list with bookingid %d to %d\n",bookingcount+1,bookingcount+number);
                            for( int i=0; i<number;i++)
                            {
                                node* newnode=malloc(sizeof(node));
                                newnode->info.bookingid=++bookingcount;
                                newnode->info.coach=coachtype;
                                newnode->next=NULL;
                                if(waiting==NULL)
                                {
                                    waitinglist=newnode;
                                    waiting=newnode;
                                }
                                while(waiting->next!=NULL)
                                {
                                    waiting=waiting->next;
                                }
                                waiting->next=newnode;
                            }
                        }
                        break;
                    default:
                        goto booking_selection;
                        break;
                }
            }
            else
            {
                int max=0;
                for( int i=0 ; i<coachtype; i++)
                {
                    max+=coachseats[i];
                }
                int min=max-coachseats[coachtype-1];
                printf("seats booked with booking id %d to %d\n",bookingcount+1,bookingcount+number);
                for(int i=min;i<max;i++)
                {
                    if(reserved[i].bookingid==-1)
                    {
                        if(number>0)
                        {
                            reserved[i].bookingid=++bookingcount;
                            reserved[i].coach=coachtype;
                            number--;
                        }
                        else
                        {
                            break;
                        }   
                    }
                }
            }
        }
        if(a==2)
        {
            goto booking_selection;
        }
    }
    /*for(int i=0;i<17;i++)
    {
        printf("%d",reserved[i].bookingid);
    }
    printf("\nwaiting list\n");
    while(waitinglist!=NULL)
    {
        printf("*");
        printf("%d",waitinglist->info.bookingid);
        waitinglist=waitinglist->next;
    }*/
    return waitinglist;
}
node* delete(booking* reserved, node* waiting, int coachseats[4])
{
    //function to cancel existing bookings
    //printf("1)to delete bookings\n");
   //printf("2)to delete a range of bookings");
    int n=1;
    //scanf("%d",&n);
    int max_seats=0;
    for(int i=0;i<=3;i++)
    {
        max_seats+=coachseats[i];
    }
    //printf("%d",max_seats);
    printf("enter the booking id to be deleted\n");
    int deleteid;
    scanf("%d",&deleteid);
    int i;
    for(i=0;i<max_seats;i++)
    {
        //printf("%d ",i);
        if(reserved[i].bookingid==deleteid)
        {
            printf("deleted bookingid %d\n",reserved[i].bookingid);
            reserved[i].bookingid=-1;
            break;
        }
    }
    if(waiting==NULL)
    {
        printf("NULL");
        return NULL;
    }
    if(waiting->next==NULL)
    {
        if(waiting->info.coach==reserved[i].coach)
        {
            printf("booking id %d's seat is now reserved\n",waiting->info.bookingid);
            reserved[i].bookingid=waiting->info.bookingid;
            waiting=NULL;
        }
        return waiting;
    }
    else if(waiting->info.coach==reserved[i].coach)
    {
        printf("booking id %d's seat is now reserved\n",waiting->info.bookingid);
        reserved[i].bookingid=waiting->info.bookingid;
        node* x=waiting;
        waiting=waiting->next;
        free(x);
        return waiting;
    }
    else
    {
        node* next;
        node* x=waiting;
        next=waiting->next;
        while(next!=NULL)
        {
            //printf(")");
            if(next->info.coach==reserved[i].coach)
            {
                printf("booking id %d's seat is now reserved\n",next->info.bookingid);
                reserved[i].bookingid=next->info.bookingid;
                node* y=next;
                x=next->next;
                free(y);
                return waiting;
            }
            else
            {
                x=next;
                next=next->next;
            }
        }
    }
    return waiting;
}
int main()
{
    printf("WELCOME TO RAILWAY RESERVATION SYSTEM\n");
    booking reserved[17];
    for(int i=0;i<17;i++)
    {
        reserved[i].bookingid=-1;
    }
    int coachseats[]={7,5,3,2};
    node* waiting;
    waiting=NULL;
    int choice=0;
    while(choice<=3)
    {
        printf("\n1)new booking\n");
        printf("2)cancel booking(s)\n");
        printf("3)display booking and waiting list\n");
        printf("EXIT\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            waiting=input(reserved,waiting,coachseats);
            choice = 0;
            /*for(int i=0;i<17;i++)
            {
                printf("%d",reserved[i].bookingid);
            }
            printf("\nwaiting list\n");
            while(waiting!=NULL)
            {
                printf("*");
                printf("%d",waiting->info.bookingid);
                waiting=waiting->next;
            }*/
        }
        else if(choice == 2)
        {   
            waiting=delete(reserved,waiting,coachseats);
            choice=0;
        }
        else if(choice==3)
        {
            printf("reserved list\n");
            int coach=0;
            for(int i=0;i<17;i++)
            {
                if(reserved[i].bookingid!=-1)
                {
                    if(reserved[i].coach!=coach)
                    {
                        coach=reserved[i].coach;
                        printf("\n %d \n",coach);
                    }
                    printf("%d, ",reserved[i].bookingid);
                }
            }
            printf("\nwaiting list\n");
            coach=0;
            node* x=waiting;
            if(x==NULL)
            {
                printf("no waiting\n");
            }
            while(x!=NULL)
            {
                if(x->info.coach!=coach)
                {
                    coach=x->info.coach;
                    printf("\n %d \n",coach);
                }
                printf("%d, ",x->info.bookingid);
                x=x->next;
            }
        }
    }
}