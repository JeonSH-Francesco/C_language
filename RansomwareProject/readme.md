# 랜섬웨어 개발 프로젝트
※들어가기 전)
이 프로젝트는 S개발자 1기 개인 과제 프로젝트로, 랜섬웨어를 개발하여 원리를 파악하고 분석가의 입장에서 성장하기 위한 프로젝트이다.
윤리적이고 선한 마음가짐을 토대로 사용하고 참고해야 함을 엄숙히 약속해야 한다!

## 서버,클라이언트 구조로 이루어짐.
일반적 시나리오-> "C:\\Users\\Desktop\\", "C:\\Users\\Downloads\\", "C:\\Users"\\Documents\\", "C:\\Users\\AppData\\Local\\Temp\\"의 경로에 특정 파일들(jpg, png, zip, ppt,doc,xlsx,pdf)에 대하여 AES 암호화 수행 및 
특정 레지스트리에 키 삽입 랜섬 노트 실행
</br>
</br>
실제 테스트 -> "C:\\Users\\Desktop\\RansomwareTest1,2,3,4"의 경로에 특정 파일들(jpg, png, zip, ppt,doc,xlsx,pdf)에 대하여 AES(AES-CBC) 암호화 수행 및 
특정 레지스트리에 키 삽입 랜섬 노트 실행

## 개발에 사용된 주요 함수
GetUserName, FindFirstFileW, FindNextFileW, CreateFile, ReadFile, WrtieFile, SetFilePointer, DeleteFile 
</br>
setlocale, _wsetlocale, RegOpenKeyEx, RegSetValueEx, RegCloseKey, ShellExecute

## 특정 레지스트리 경로에 키 삽입
<img width="1688" height="597" alt="image" src="https://github.com/user-attachments/assets/60c2daa7-5db6-41be-b452-a9da87b0effd" />

## 실행 결과
Client.c 결과
<img width="1181" height="969" alt="image" src="https://github.com/user-attachments/assets/9a564f1c-748b-4eaa-a4a4-9718d20b0b18" />

Server.cpp 결과
<img width="1105" height="203" alt="image" src="https://github.com/user-attachments/assets/ffc4fe53-b98a-4bd3-8980-21e32f342731" />

암호화 진행 시, 파일은 삭제되고 확장자가 .SDEV로 변경된 형태로 된다. 또한, 복호화 로직을 검증하기 위해 폴더 안에 Test 폴더들을 생성하여 복호화한 결과를 넣어
검증을 완료 하였다.(공격자가 실제 복호화 할 수 있는지 여부=키로 협박하여 비트코인을 요구하는 것이 정당한지 여부)
실제로도 원본과 동일하다.

## 특정 폴더의 특정 파일에 대하여 암호화 진행
<img width="1865" height="706" alt="image" src="https://github.com/user-attachments/assets/812677ba-8916-45ba-9a19-f07ee877ffec" />

## 특정 폴더의 특정 파일에 대하여 복호화 진행
<img width="1770" height="771" alt="image" src="https://github.com/user-attachments/assets/18192fc3-9793-44cd-a27b-f81a41fda5e2" />
<img width="1406" height="1025" alt="image" src="https://github.com/user-attachments/assets/a5ed8b23-da3a-460a-a885-26f514676451" />

## 랜섬노트 실행
<img width="729" height="411" alt="image" src="https://github.com/user-attachments/assets/11996d09-965e-4b45-ba6a-40cb451fae97" />

## 실행 영상
https://github.com/user-attachments/assets/63d5f896-1d8a-4452-8960-debe747dd9af

