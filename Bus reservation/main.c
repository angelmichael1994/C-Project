#include <stdio.h>
#include <string.h>

#define ROWS 4
#define COLS 5

enum BusType
{
    AC = 1,
    NON_AC,
    SLEEPER
};

struct Passenger
{
    char name[30];
    int age;
    char phone[15];
};

struct Bus
{
    enum BusType type;
    int seats[ROWS][COLS];
    struct Passenger passenger[ROWS][COLS];
};

void displayBusType(enum BusType type)
{
    if(type == AC)
        printf("AC Bus\n");
    else if(type == NON_AC)
        printf("Non-AC Bus\n");
    else
        printf("Sleeper Bus\n");
}

void displaySeats(struct Bus *bus)
{
    int i, j;

    int *ptr = &bus->seats[0][0];

    printf("SEAT CHART \n");

    printf("       1    2    3    4    5\n");

    for(i = 0; i < ROWS; i++)
    {
        printf("Row %d  ", i + 1);

        for(j = 0; j < COLS; j++)
        {

            if(*(ptr + (i * COLS + j)) == 0)
                printf("[ A ]");
            else
                printf("[ X ]");
        }

        printf("\n");
    }

    printf("\nA = Available\n");
    printf("X = Booked\n");
}


void bookSeat(struct Bus *bus)
{
    int row, col;
    int *ptr;

    printf("\nEnter row number (1-%d): ", ROWS);
    scanf("%d", &row);

    printf("Enter seat number (1-%d): ", COLS);
    scanf("%d", &col);

    if(row < 1 || row > ROWS || col < 1 || col > COLS)
    {
        printf("Invalid seat number!\n");
        return;
    }


    ptr = &bus->seats[0][0] + ((row - 1) * COLS + (col - 1));

    if(*ptr == 1)
    {
        printf("Seat is already booked!\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf(" %[^\n]", bus->passenger[row - 1][col - 1].name);

    printf("Enter age: ");
    scanf("%d", &bus->passenger[row - 1][col - 1].age);

    printf("Enter phone number: ");
    scanf("%14s", bus->passenger[row - 1][col - 1].phone);

    *ptr = 1;

    printf("\nSeat booked successfully!\n");
}


void cancelSeat(struct Bus *bus)
{
    int row, col;
    int *ptr;

    printf("\nEnter row number: ");
    scanf("%d", &row);

    printf("Enter seat number: ");
    scanf("%d", &col);

    if(row < 1 || row > ROWS || col < 1 || col > COLS)
    {
        printf("Invalid seat number!\n");
        return;
    }

    ptr = &bus->seats[0][0] + ((row - 1) * COLS + (col - 1));

    if(*ptr == 0)
    {
        printf("Seat is already available!\n");
        return;
    }

    *ptr = 0;

    strcpy(bus->passenger[row - 1][col - 1].name, "");
    bus->passenger[row - 1][col - 1].age = 0;
    strcpy(bus->passenger[row - 1][col - 1].phone, "");

    printf("Booking cancelled successfully!\n");
}

int main()
{
    struct Bus bus;
    int choice;
    int i, j;

    printf("Select Bus Type\n");
    printf("1. AC\n");
    printf("2. Non-AC\n");
    printf("3. Sleeper\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 3)
    {
        printf("Invalid bus type!\n");
        return 1;
    }

    bus.type = choice;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            bus.seats[i][j] = 0;
        }
    }

    printf("\nBus Type: ");
    displayBusType(bus.type);

    while(1)
    {
        printf("\n===== BUS RESERVATION SYSTEM =====\n");
        printf("1. Display Seats\n");
        printf("2. Book Seat\n");
        printf("3. Cancel Seat\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displaySeats(&bus);
                break;

            case 2:
                bookSeat(&bus);
                break;

            case 3:
                cancelSeat(&bus);
                break;

            case 4:
                printf("Thank you!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
