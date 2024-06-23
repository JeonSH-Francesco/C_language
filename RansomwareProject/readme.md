# 랜섬웨어 개발 프로젝트

## 서버,클라이언트 구조로 이루어짐.
-> "C:\\Users\\Desktop\\", "C:\\Users\\Downloads\\", "C:\\Users"\\Documents\\", "C:\\Users\\AppData\\Local\\Temp\\"의 경로에 특정 파일들(hwp,ppt,doc,zip,jpg,png)에 대하여 AES 암호화 수행 및 
특정 레지스트리에 키 삽입 랜섬 노트 실행

## 개발에 사용된 주요 함수
GetUserName, FindFirstFileW, FindNextFileW, CreateFile, ReadFile, WrtieFile, SetFilePointer, 
</br>
setlocale, _wsetlocale, RegOpenKeyEx, RegSetValueEx, RegCloseKey, ShellExecute

## 특정 레지스트리 경로에 키 삽입
![image](https://github.com/JeonSH-Francesco/C_language/assets/112309895/a30cc9be-cddc-4967-94ee-74af09fa190b)


## 특정 폴더의 특정 파일에 대하여 암호화 진행
Client.c 결과
![image](https://github.com/JeonSH-Francesco/C_language/assets/112309895/d9ee4780-7853-4cfe-abcf-d6270d84dd25)
![image](https://github.com/JeonSH-Francesco/C_language/assets/112309895/b89ad577-3132-4c6c-bc5d-9bf3fe4ba148)
Server.cpp 결과
![image](https://github.com/JeonSH-Francesco/C_language/assets/112309895/b3a1bdd6-0de8-4197-b481-f9383fba4281)


## 특정 폴더의 특정 파일에 대하여 복호화 진행
![image](https://github.com/JeonSH-Francesco/C_language/assets/112309895/f7a21945-f512-4c53-85d4-a8c667cc217d)

![image](https://github.com/JeonSH-Francesco/C_language/assets/112309895/a7030cf5-1967-4e4f-8efe-369e63885be5)

