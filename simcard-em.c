#include "simcard-em.h"
#include "filesystem.h"
#include "list.h"
#include <stdio.h>

extern struct sim_file file_table[];

int main(int argc, char **argv){
    struct list_head *ptr, *iter;

    printf("starting\n");

    init_sim_fs();

    walk_df("MF");

    free_fs_mem();

    return 0;
}
