#include "filesystem.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern struct sim_file file_table[N_FILES];
extern struct app_file ADFusim;
extern int i_file;

/* Get file by name */
struct sim_file *get_file_by_name(char *name){
    for (int i = 0; i < i_file; i++){
        if(!strcmp(name, file_table[i].name)){
            return &file_table[i];
        }
    }
    return NULL;
}

/* Get file by fid */
struct sim_file *get_file_by_fid(uint16_t fid){
    for (int i = 0; i < i_file; i++){
        if(file_table[i].fid == fid){
            return &file_table[i];
        }
    }
    return NULL;
}

/* free memory allocated for sim filesystem*/
void free_fs_mem(){
    for (int i = 0; i < i_file; i++) {
        if(file_table[i].type == TYPE_EF_TR) {
            free(file_table[i].data.trn);
        }
        if((file_table[i].type == TYPE_EF_LF) || (file_table[i].type == TYPE_EF_CY)) {
            for (int j=0; j < file_table[i].n_recs; j++) {
                free(file_table[i].data.rec[j].data);
            }
            free(file_table[i].data.rec);
        }
    }
}

/* Walk files in the path and print info*/
void walk_df(char *name){
    struct list_head *ptr, *iter;
    struct sim_file *file_ptr = SIM_FILE_NAME(name);
    printf("===\n");
    foreach_child(file_ptr){
        struct sim_file *this_file = GET_SIM_FILE_BY_LNK(iter);
        print_file_info(this_file);
        if (this_file->type == TYPE_DF)
            walk_df(this_file->name);
    }
    printf("===\n");
    return;
}

/* Print file info*/
void print_file_info(struct sim_file *file){
    char *type[] = {"Master File", "Dedicated File", "Transparent EF",
                    "Linear Fixed EF", "Cyclic EF", "Application DF"};
    printf("file:\t%s\n", file->name);
    printf("fid:\t0x%.4x\n", file->fid);
    if (file->sfid)
        printf("sfid:\t0x%.2x\n", file->sfid);
    printf("type:\t%s\n", type[file->type]);
    printf("parent: %s\n", file->parent->name);
    printf("size:\t%d\n", file->size);
    if (file->type == TYPE_EF_LF) {
        printf("rec_len:%d\n", file->rec_len);
        printf("n_recs:\t%d\n", file->n_recs);
    }
    printf("desc:\t%s\n", file->desc);
    if (IS_EF(file)){
        printf("data:\n");
        print_file_data(file);
    }
    printf("\n");
}

/* Print out contents of file */
void print_file_data(struct sim_file *file){
    /* TODO: Cyclic files */

    if (file->type == TYPE_EF_TR) {
        for (int i = 0; i < file->size; i++) {
            printf("0x%02x ", file->data.trn[i]);
        }
        printf("\n");
    }

    if (file->type == TYPE_EF_LF) {
        for (int i = 0; i < file->n_recs; i++) {
            printf("[%d]:\t", i);
            for (int j = 0; j < file->data.rec[i].size; j++) {
                printf("0x%02x ", file->data.rec[i].data[j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
