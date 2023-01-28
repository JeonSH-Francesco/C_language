#include <stdio.h>

struct point{
    int x;
    int y;
};

struct point function(void);

int main(void)
{

    struct point p;
    p=function();
    printf("%d %d\n",p.x,p.y);

    return 0;
}

struct point function(void){

    struct point call ={10,20};
    return call; //구조체 변수 call을 14행으로 반환
};

----------
#include <stdio.h>

struct point{
    int x;
    int y;
};

struct point *function(void);

int main(void)
{

    struct point *p;
    p=function();
    printf("%d %d\n",p->x,p->y);
    printf("%d %d\n",(*p).x,(*p).y);

    return 0;
}

struct point* function(void){

    static struct point call={10,20};
    return &call; //구조체 변수 call을 14행으로 반환
};
