//
// Created by Alwin on 7/10/18.
//
#include <stdio.h>
#include <elf.h>
/**
 * This file contains one main function: check_permissions(File f).
 * It takes in an ELF file and returns the permissions the libraries of the file need
 * if there is a library that is not in our database, it also returns "UIL" (unidentified library)
 */

int check_permissions(FILE *elf_file) {
    Elf64_Ehdr main_header;
    Elf64_Shdr s_header;
    fread(&main_header, 1, sizeof(main_header), elf_file);
    printf((char*) main_header.e_ident);
    printf("\n");
    int s_count = main_header.e_shnum;
    long offset = main_header.e_shoff;
    long count = 0;
    printf("%ld\n", offset);

    for(int i = 0; i < s_count; i++) {
        fseek(elf_file, offset + count, SEEK_SET);
        fread(&s_header, 1, sizeof(s_header), elf_file);
        count += sizeof(s_header);

        printf("name: %d\n", s_header.sh_type);
        if (s_header.sh_type == 11) {
            long dynsym_off = s_header.sh_offset;
            fseek(elf_file, dynsym_off, SEEK_SET);
        }
    }
    return 0;
}

int main()
{
    FILE *elf = fopen("a.out", "rb");
    check_permissions(elf);
    return 0;
}