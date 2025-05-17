// main.c
#include <stdio.h>
#include <string.h>
#include "rle.h"
#include "crypto.h"
#include "fileio.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./notes [add | view]\n");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        // TODO: 사용자 입력 → 압축 → 암호화 → 저장
    } else if (strcmp(argv[1], "view") == 0) {
        // TODO: 파일 읽기 → 복호화 → 압축 해제 → 출력
    } else {
        printf("Invalid command. Use 'add' or 'view'\n");
    }

    return 0;
}