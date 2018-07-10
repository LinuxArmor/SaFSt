//
// Created by root on 7/10/18.
//

#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>

int main() {
    printf("Hello, world!\n");
    socket(AF_INET, SOCK_STREAM, 1);
    return 0;
}