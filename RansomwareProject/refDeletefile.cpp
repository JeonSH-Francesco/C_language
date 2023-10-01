#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    // 원본 파일 경로와 파일 내용 정의
    std::string original_file_path = "C:\\path1\\to\\original.txt";
    std::string file_content = "Hello, this is the content of the original file.";

    // 임시 폴더 경로 설정 (아래 예시는 C 드라이브의 temp 폴더)
    std::string temp_folder = "C:\\temptest";
    // 임시 파일 경로 생성
    std::string temp_file_path = temp_folder + "\\temp_file.txt";

    // 원본 파일 생성 및 쓰기
    HANDLE hFile = CreateFileA(
        original_file_path.c_str(),    // 원본 파일 경로
        GENERIC_WRITE,                  // 쓰기 권한
        0,                              // 공유 모드 (다른 프로세스와 공유하지 않음)
        nullptr,                        // 보안 속성 (기본값)
        CREATE_ALWAYS,                  // 파일이 존재하면 덮어쓰기
        FILE_ATTRIBUTE_NORMAL,          // 파일 속성 (일반 파일)
        nullptr                         // 템플릿 파일 핸들 (기본값)
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "원본 파일 생성에 실패하였습니다." << std::endl;
        return 1;
    }

    // 원본 파일에 내용 쓰기
    DWORD bytes_written;
    if (!WriteFile(
        hFile,                          // 파일 핸들
        file_content.c_str(),           // 쓸 데이터
        static_cast<DWORD>(file_content.length()), // 데이터 길이
        &bytes_written,                 // 실제로 쓰여진 바이트 수를 받을 변수
        nullptr                         // 동기화 객체 (기본값)
    )) {
        std::cout << "원본 파일 쓰기에 실패하였습니다." << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    std::cout << "원본 파일이 성공적으로 생성되고 내용이 쓰여졌습니다." << std::endl;

    // 원본 파일 핸들 닫기
    CloseHandle(hFile);

    // 원본 파일을 임시 폴더로 복사
    if (CopyFileA(original_file_path.c_str(), temp_file_path.c_str(), FALSE)) {
        std::cout << "원본 파일을 임시 폴더로 복사하였습니다." << std::endl;
    }
    else {
        std::cout << "파일 복사에 실패하였습니다." << std::endl;
        return 1;
    }

    // 원본 파일 삭제
    if (DeleteFileA(original_file_path.c_str())) {
        std::cout << "원본 파일이 성공적으로 삭제되었습니다." << std::endl;
    }
    else {
        std::cout << "원본 파일 삭제에 실패하였습니다." << std::endl;
        return 1;
    }

   std::cout << "임시 폴더에 원본 파일을 복사하고 원본 파일을 삭제했습니다." << std::endl;

    return 0;
}
