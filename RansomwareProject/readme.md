# 랜섬웨어 개발 프로젝트

## 서버,클라이언트 구조로 이루어짐.
-> "C:\\Users\\Desktop\\", "C:\\Users\\Downloads\\", "C:\\Users"\\Documents\\", "C:\\Users\\AppData\\Local\\Temp\\"의 경로에 특정 파일들(hwp,ppt,doc,zip,jpg,png)에 대하여 AES 암호화 수행 및 
특정 레지스트리에 키 삽입 랜섬 노트 실행

## 개발에 사용된 주요 함수
GetUserName, FindFirstFileW, FindNextFileW, CreateFile, ReadFile, WrtieFile, SetFilePointer, 
</br>
setlocale, _wsetlocale, RegOpenKeyEx, RegSetValueEx, RegCloseKey, ShellExecute

## 특정 레지스트리 경로에 키 삽입
![registry key insertion](https://github.com/JeonSH-Francesco/C_language/assets/112309895/c5e3ee47-7bb8-4bd5-b490-1279deece0ba)

## 특정 폴더의 특정 파일에 대하여 암호화 진행예시
![AES_encrypt](https://github.com/JeonSH-Francesco/C_language/assets/112309895/a8a0facb-142c-49ff-a423-eefab1e47ad2)
