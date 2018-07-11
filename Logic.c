//
// Created by Alwin on 7/10/18.
//
#include <stdio.h>
#include <elf.h>
/**
 * This file contains one main function: check_permissions(File f).
 * It takes in an ELF file and returns the permissions the libraries and imported functions of the file need
 * if there is a library that is not in our database, it also returns "UIL" (unidentified library)
 */


int check_permissions(FILE *elf_file) {
    Elf64_Ehdr main_header;
    Elf64_Shdr s_header;
    Elf64_Sym dynsym_entry;
    fread(&main_header, 1, sizeof(main_header), elf_file);
    printf((char*) main_header.e_ident);
    printf("\n");
    int s_count = main_header.e_shnum;
    long offset = main_header.e_shoff;
    long count = 0;
    long strtab_offset;
    FILE *func_list;
    printf("%ld\n", offset);

    Elf64_Shdr sh_list[s_count];
    fseek(elf_file, offset, SEEK_SET);
    for(int i = 0; i < s_count; i++) {
        fread(&s_header, 1, sizeof(s_header), elf_file);
        sh_list[i] = s_header;
    }
    for (int i = 0; i < s_count; i++) {
        Elf64_Shdr hdr = sh_list[i];
        if (hdr.sh_type == 11) {
            long dynsym_ecount = (hdr.sh_size / hdr.sh_entsize);
            int dynstr_idx = hdr.sh_link;
            long eoff = 0;
            fseek(elf_file, hdr.sh_offset, SEEK_SET);
            for (long j = 0; j < dynsym_ecount; j++) {
                fread(&dynsym_entry, 1, hdr.sh_entsize, elf_file);
                eoff += dynsym_entry.st_size;
                int e_type = dynsym_entry.st_info & 15;
                printf("type : %x\n", e_type);
                if (e_type == 2) {
                    FILE *name = elf_file;
                    long toff = (long) sh_list[dynstr_idx].sh_offset + (long) dynsym_entry.st_name;
                    printf("index: %d\n", dynstr_idx);
                    char *str_name;
                    str_name = name + toff;
                    printf("%x\n", str_name);
                    printf("name: %s\n", *str_name);


                }
            }
        }
    }
    return 0;
}

int main()
{
    FILE *elf = fopen("a.out", "rb");
    check_permissions(elf);
    fclose(elf);
    return 0;
}