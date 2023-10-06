#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    char str[100];

    printf("Input string: ");
    fgets(str, sizeof(str), stdin);

    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    int result = strlen(str);
    printf("Strlen : %d\n", result);

    __asm {
        // 문자열 길이 계산을 위한 어셈블리 코드
        mov eax, 0  // eax 레지스터를 0으로 초기화 (문자열 길이 저장)

        lea ecx, str  // ecx 레지스터에 문자열 주소를 저장
        mov edx, 100  // edx 레지스터에 문자열의 크기를 저장 (str 배열의 크기)

        CountLoop:
            mov al, [ecx]  // ecx 주소에 있는 바이트를 al 레지스터로 로드
            cmp al, 0  // al 레지스터 값이 0인지 확인 (문자열 끝인지)
            je Done  // 문자열 끝이면 루프 종료

            inc eax  // eax 값 증가 (문자열 길이 증가)
            inc ecx  // ecx 주소 증가 (다음 문자로 이동)
            cmp eax, edx  // eax 값이 edx (문자열 크기)와 같은지 확인
            jl CountLoop  // eax 값이 edx보다 작으면 루프 반복

            Done :
            dec eax  // 문자열 끝의 NULL 문자를 제외하기 위해 eax에서 1 빼기
            mov result, eax  // 계산된 문자열 길이를 result 변수에 저장
    }


    //printf("Strlen (ASM): %d\n", result);

    return 0;
}

/*
중단점 설정 하는 것 확인하기!
----------------
Hello S-Dev출력
#include <stdio.h>

char str[]="Hello S-Dev\n";

int main(){
	printf("%s",str);

}
----------------
어셈블리어
#include <stdio.h>

char str[] = "Hello S-Dev\n";

int main() {
	__asm {
	 mov edx, offset str //문자열 str의 주소를 edx 레지스터에 저장합니다. offset 키워드는 주어진 변수의 주소를 얻을 수 있게 함.
	 push edx //레지스터에 저장된 문자열 str의 주소를 스택에 push 합니다. printf 함수 호출 시 인자로 사용하기 위함
	 call printf //printf 함수 호출
	 mov esp, ebp //스택 조작을 통해 프로그램을 종료하기 위해 esp 레지스터를 ebp 레지스터에 저장된 값으로 설정
	 pop ebp // ebp 레지스터에 저장된 프레임 포인터 값을 복원
	 retn //main 함수를 빠져나가며 프로그램을 종료.
   }
}
#include <stdio.h>

char str[] = "Hello S-Dev\n";  // "Hello S-Dev" 문자열을 저장하는 char 배열

int main() {
	__asm {
		mov edx, offset str   // 문자열의 주소를 edx 레지스터에 로드
		push edx              // 문자열 주소를 스택에 푸시
		call printf           // printf 함수 호출
		mov esp, ebp          // 스택 조작하여 프로그램 종료
		pop ebp
		retn
	}
}


----------------
두 숫자의 합을 계산하는 함수
#include <stdio.h>

void add(int a, int b) {
	int result = 0;

	result = a + b;
	printf("%d", result);
}

int main() {
	add(2, 3);
}
-----------
#include <stdio.h>

void sum_add(int a, int b) {
	int result = 0;

	result = a + b;
	printf("%d", result);
}

int main() {
	__asm {
		push 2              // 첫 번째 인자: a = 2를 스택에 푸시
		push 3              // 두 번째 인자: b = 3을 스택에 푸시
		call sum_add        // sum_add 함수 호출

		// 스택 정리
		add esp, 8
	}
}
----------
가위 바위 보 게임
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game() {
	int com, user;
	srand((unsigned)time(NULL)); // rand 값 매번 결과가 다르게 시드 값 설정

	printf("가위 바위 보 게임을 시작합니다.");

	while (1) {
		com = rand() % 3 + 1; //1~3 값 중 하나 랜덤하게 발생

		printf("(1 :가위, 2 :바위, 3 :보 / 0 :종료)\n\n");
		printf("Input Number :");
		scanf_s("%d", &user);
		if (user > 0 && user < 4) {
			printf("Com : %d, User : %d\n", com, user);

			if (com == user) {
				printf("비겼습니다.\n");
			}
			else if ((com == 1) && (user == 3) || (com == 2) && (user == 1) || (com == 3) && (user == 2)) {
				printf("졌습니다.\n");
			}
			else {
				printf("이겼습니다.");
			}

		}
		else {
			if (user == 0) {
				printf("게임을 종료합니다.");
				break;
			}
			printf("숫자를 제대로 입력해주세요\n\n");
		}


	}
}

int main() {
	game();
	return 0;
}
------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char msg1[] = "가위(1), 바위(2), 보(3) 종료(0) 중 하나를 선택하세요: ";
char format[] = "%d";
char msg_draw[] = "비겼습니다.\n";
char msg_lose[] = "졌습니다.\n";
char msg_win[] = "이겼습니다.\n";
char msg_end[] = "게임을 종료합니다...\n";

int main() {
    int user, computer;

    __asm {
    start_game:
        // msg1 출력
        push offset msg1
            call dword ptr printf
            add esp, 4

            // user 입력
            lea eax, [user]
            push eax
            push offset format
            call dword ptr scanf
            add esp, 8

            cmp dword ptr[user], 0
            je end_game

            // 시드 값 설정 및 랜덤한 computer 선택
            push 0
            call dword ptr time
            add esp, 4
            mov esi, esp
            push eax
            call dword ptr srand
            add esp, 4
            cmp esi, esp

            call dword ptr rand
            xor edx, edx
            mov ecx, 0x3
            div ecx     // div 연산을 통해 몫은 eax, 나머지는 edx로 간다.
            add edx, 1       // rand()%3+1
            mov computer, edx

            // 사용자의 선택과 컴퓨터의 선택을 비교하여 승자를 결정합니다
            mov ecx, user
            mov eax, ecx
            push eax // 백업 (유저)

            push computer
            mov eax, offset format
            push eax
            call printf
            add esp, 8

            pop eax      // 사용자 값 백업 복구
            cmp eax, 1       // 사용자가 가위(1)를 선택했는지 비교
            je scissors_chosen

            cmp eax, 2       // 사용자가 바위(2)를 선택했는지 비교
            je rock_chosen

            cmp eax, 3       // 사용자가 보(3)를 선택했는지 비교
            je paper_chosen
            jmp start_game
            //this

            //가위를 선택한 경우(1)
            scissors_chosen:
            cmp computer, eax
            je draw
            cmp computer, 3
            je win
            jmp lose

            //바위를 선택한 경우(2)
            rock_chosen :
            cmp computer, eax
            je draw
            cmp computer, 1
            je win
            jmp lose

            //보를 선택한 경우(3)
            paper_chosen :
            cmp computer, eax
            je draw
            cmp computer,2
            je win
            jmp lose


            //비긴 경우
            draw:
            push offset msg_draw
            call dword ptr printf
            add esp, 4
            jmp start_game

            //진 경우
            lose :
            push offset msg_lose
            call dword ptr printf
            add esp, 4
            jmp start_game

            //이긴 경우
            win :
            push offset msg_win
            call dword ptr printf
            add esp, 4
            jmp start_game

            //끝내는 경우
            end_game :
            push offset msg_end
            call dword ptr printf
            add esp, 4
    }

    return 0;
}

-----------
#define _CRT_SEUCRE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void mystrlen() {
	char str[100];

	printf("Input string: ");
	fgets(str, sizeof(str), stdin); // fgets를 사용하여 문자열 입력

	// fgets는 개행 문자도 읽어들이므로 개행 문자를 제거
	if (str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = '\0';
	}

	int result = strlen(str);
	printf("Strlen : %d\n", result);
}

int main() {
	mystrlen();
	return 0;
}
----------

#define _CRT_SEUCRE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void mystrlen() {
	__asm{
	
	
	}
}

int main() {
	__asm {
		call mystrlen
	}
}

*/
