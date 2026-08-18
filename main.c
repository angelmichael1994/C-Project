#include <stdio.h>
#include <stdlib.h>

#define PASS 1
#define FAIL 2
#define DISTINCTION 4

struct Student
{
    char name[20];
    int roll;
    int marks[5];
    int flag;
};
float average(struct Student *p);

void Topper(struct Student *p, int n);

void subjectPerformance(struct Student *p, int n);


int main()
{
    int n;
    int i, j;
    struct Student *s;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid Case\n");
        return 1;
    }

    s = malloc(n * sizeof(struct Student));

    if(s == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for(i = 0; i < n; i++)
    {
        printf("\nEnter name: ");
        scanf("%s", s[i].name);

        printf("Enter roll number: ");
        scanf("%d", &s[i].roll);

        printf("Enter 5 marks: ");

        for(j = 0; j < 5; j++)
        {
            scanf("%d", &s[i].marks[j]);
        }

        if(s[i].marks[0] >= 40 &&
           s[i].marks[1] >= 40 &&
           s[i].marks[2] >= 40 &&
           s[i].marks[3] >= 40 &&
           s[i].marks[4] >= 40)
        {
            s[i].flag = PASS;

            if(average(&s[i]) >= 75)
            {
                s[i].flag = s[i].flag | DISTINCTION;
            }
        }
        else
        {
            s[i].flag = FAIL;
        }
    }

    printf("\nStudent Details\n");

    for(i = 0; i < n; i++)
    {
        printf("Name: %s\n", s[i].name);
        printf("Roll: %d\n", s[i].roll);
        printf("Average: %.2f\n", average(&s[i]));

        if(s[i].flag & FAIL)
        {
            printf("Status: FAIL\n\n");
        }
        else if(s[i].flag & DISTINCTION)
        {
            printf("Status: PASS + DISTINCTION\n\n");
        }
        else
        {
            printf("Status: PASS\n\n");
        }

    }

    Topper(s, n);

    subjectPerformance(s, n);

    free(s);

    return 0;
}
float average(struct Student *p)
{
    int i;
    int sum = 0;
    float avg;

    for(i = 0; i < 5; i++)
    {
        sum = sum + p->marks[i];
    }

  avg = (float)sum / 5;
  return avg;

}

void Topper(struct Student *p, int n)
{
    int i;
    int topper = 0;

    for(i = 1; i < n; i++)
    {
        if(average(&p[i]) > average(&p[topper]))
        {
            topper = i;
        }
    }

    printf("Topper = %s\n", p[topper].name);
    printf("Average = %.2f\n", average(&p[topper]));
}

void subjectPerformance(struct Student *p, int n)
{
    int i, j;
    int total;

    printf("Subject-wise average:\n");

    for(j = 0; j < 5; j++)
    {
        total = 0;

        for(i = 0; i < n; i++)
        {
            total = total + p[i].marks[j];
        }

        printf("Subject %d Average = %.2f\n",
               j + 1, (float)total / n);
    }
}


