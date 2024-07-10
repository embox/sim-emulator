#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>

struct sim_file file_table[N_FILES];
struct app_file ADFusim;
int i_file = 0;

/* Create virtual file system*/
void init_sim_fs(){
    printf("Initializing filesystem...");

    #include "fs.inc"

    printf("done\n");

    /*[> GSM Phase 2+ level<]*/
    /*APP_FILE_ENTRY("ADF.USIM", 0xa0000000871002, "Application DF", &MF)*/
}
