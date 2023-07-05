#include <stdio.h>
#include <fcntl.h>
#define PW_LEN 15 

void xor (char *s, int len, unsigned int XORKEY) {
    int i;
    for (i = 0; i < len; i++)
    {
        s[i] ^= XORKEY;
        s[i] &= 0xFF;
    }
}

/*
xor 함수는 char *s 포인터를 통해서 암호화 또는 복화화를 수행할 문자열의 시작 주소를 가리키는 포인터 
int len 변수를 통해서 암호화 또는 복호화를 수행할 문자열의 길이입니다.
unsigned int XORKEY를 받아서 XOR 연산에 사용할 키 값입니다.

함수 내부에서는 반복문을 사용하여 문자열의 각 문자에 대해 XOR 연산을 수행합니다.
->좀 더 자세히 말하면
s[i] ^=XORKEY; 현재 문자와 XORKEY 값을 XOR 연산을 하여 현재 문자를 암,복화화에 쓰이고
s[i] &=0XFF; 연산 결과로 생긴 비트 외에 다른 비트를 모두 0으로 만드는 작업입니다.
이렇게 함으로써 문자의 범위를 0~255 사이로 제한합니다.

*/


int main(int argc, char *argv[]){
    int fd = 0;
    char pw_buf[PW_LEN + 1];
    char pw_buf2[PW_LEN + 1];
    int len = 0;
    //setvbuf 함수를 사용하여 출력 버퍼링을 비활성화 합니다. 
    //이렇게 함으로써 출력이 즉시 화면에 나타납니다.
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

    if (!(!(fd = open("./password", O_RDONLY, 0400) < 0) ^ fd))
    {
        return 0;
    }
    //open 함수를 사용하여 ./password 파일을 읽기 전용으로 엽니다.
    //즉, ->0400권한에서 확인할 수 있듯이 Read Only!

    puts("Please find my password!\n");
    fd = fd;
    if (!(len = read(fd, pw_buf, PW_LEN) > 0))
    {
        printf("read error\n");
        close(fd);
        return 0;
    }
    //read 함수를 사용하여 파일에서 PW_LEN만큼의 길이로 패스워드를 읽어옵니다.
    //읽기에 실패하면 "read error" 메시지를 출력하고 프로그램이 종료됩니다.

    printf("input password : ");
    scanf("%15s", pw_buf2);
    xor(pw_buf2, PW_LEN, 0xDEADBEEF);
    //잘 열렸을 경우 password를 입력받고, 입력 받은 password에 대해 xor 연산을 수행
    //XORKEY= 0xDEADBEEF
    if (!strncmp(pw_buf, pw_buf2, PW_LEN))
    {
        printf("Password OK\n");
        system("/bin/cat flag\n");
    }
    else
    {
        printf("Wrong Password\n");
    }
    close(fd);
    return 0;
    //password가 맞으면 Password OK 구문과 /bin/cat flag를 출력하고
    //틀리면 Wrong Password를 출력합니다.
}
