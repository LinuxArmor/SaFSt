//
// Created by root on 7/10/18.
//

#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>

void hello(char *str) {
    printf("Hello, %s\n", str);
}

int main() {
    hello("world");
    socket(AF_INET, SOCK_STREAM, 1);
    return 0;
}