#include <stdio.h>

struct student {
    char name[20];
    int money;
    struct student* link;
};

int main() {
    struct student stu[3] = {
        { "Kim", 90, NULL },
        { "Lee", 80, NULL },
        { "Goo", 60, NULL }
    };

    // for문으로 링크 설정
    for (int i = 0; i < 2; i++) {
        stu[i].link = &stu[i + 1]; //현재 학생의 link를 다음 학생으로 설정
    }
    stu[2].link = NULL; //마지막 학생의 link는 NULL로 설정

    // 연결된 학생 출력
    struct student* current = &stu[0];
    while (current != NULL) {
        printf("Name : %s, Money : %d\n",current->name, current->money);
        current = current->link; // 다음 학생으로 이동
    }
    return 0;
}
