/*
 * Declarations for simcard filesystem
 */
#ifndef __SIMCARD_FILESYSTEM_H__
#define  __SIMCARD_FILESYSTEM_H__

#include "stdint.h"
#include "list.h"
#include <stdint.h>

#define N_FILES 1000

enum sim_file_type {
    TYPE_MF,
    TYPE_DF,
    TYPE_EF_TR, /* Transparent EF*/
    TYPE_EF_LF, /* Linear fixed EF*/
    TYPE_EF_CY, /* Cyclic EF*/
    TYPE_ADF
};

struct record {
    unsigned int        size;
    unsigned char       *data;
};

struct sim_file{
    struct sim_file*    parent;

    enum sim_file_type  type;
    uint16_t            fid;
    uint16_t            sfid;
    char*               name;
    char*               desc;

    uint16_t            size;
    uint8_t             rec_len; /* for linear fixed and cyclic EF*/
    uint16_t            n_recs;  /* number of records for LF and CYC EF */
    uint16_t            cur_rec; /* current record for cyclic EF ?  */

    union {
        unsigned char*          trn;     /* transparent file, plain data*/
        struct record*          rec;     /* lin/cyc file, aray of records*/
    } data;

    struct list_head    lnk;
    struct list_head    children; /* for MF and DF - list of files under*/

    /*void                (*init)();*/
};

struct app_file{
    struct sim_file     *file;
    uint64_t            aid;
};

/* ETSI TS 102 221 V17.1.0 (2022-02)
Length      Description                         Status
1			Application template tag = '61'     M
1			Length of the applicationi          M
            template = '03'-'7F'
1			Application Identifier tag = '4F'   M
1			AID length = '01'-'10'              M
'01'to'10'  AID value. See ETSI TS 101 220 [3]  M
1			Application label tag = '50'        O
1			Application label length            O
Note 1      Application label value             O
NOTE 1: The application label is a DO that contains a string of bytes provided
by the application provider to be shown to the user for information,
e.g. operator name. The value part of the application label shall be
coded according to annex A. It is recommended that the number of
bytes in the application label does not exceed 32.
NOTE 2: Other Dos from ISO/IEC 7816-4 [12] may, at the application issuer's
discretion, be present as well.
*/

/* Common file entry macro */
#define FILE_ENTRY(_name, _fid, _sfid, _type, _desc, _parent, _size, _rec_len, _n_recs, _cur_rec) \
extern struct sim_file file_table[];  \
extern int i_file;          \
file_table[i_file] = (struct sim_file) {      \
    .parent		= _parent,	\
    .name		= _name,	\
    .fid 		= _fid,	    \
    .sfid		= _sfid,	\
    .type		= _type,	\
    .desc		= _desc, 	\
    .size   	= _size,	\
    .rec_len	= _rec_len,	\
    .n_recs 	= _n_recs,	\
    .cur_rec	= _cur_rec,	\
};\
INIT_LIST_HEAD(&file_table[i_file].lnk);     \
INIT_LIST_HEAD(&file_table[i_file].children);\
if(file_table[i_file].parent){               \
    list_add_tail(&file_table[i_file].lnk, &file_table[i_file].parent->children);\
}\
i_file++;\


#define FILE_MF \
    FILE_ENTRY("MF", 0x3f00, 0, TYPE_MF, "Master File", &MF, 0, 0, 0, 0); 

#define FILE_DF(_name, _fid, _desc, _parent) \
    FILE_ENTRY(_name, _fid, 0, TYPE_DF, _desc, _parent, 0, 0, 0, 0); 

#define FILE_TRN_EF(_name, _fid, _sfid, _desc, _parent, _size) \
    FILE_ENTRY(_name, _fid, _sfid, TYPE_EF_TR, _desc, _parent, _size, 0, 0, 0); 

#define FILE_LIN_EF(_name, _fid, _sfid, _desc, _parent, _size, _rec_len, _n_recs) \
    FILE_ENTRY(_name, _fid, _sfid, TYPE_EF_LF, _desc, _parent, _size, _rec_len, _n_recs, 0); 

/* Application file entry macro */
#define APP_FILE_ENTRY(_name, _aid, _desc, _parent) \
extern struct sim_file file_table[];  \
extern int i_file;          \
file_table[i_file] = (struct sim_file) {      \
    .parent		= _parent,	\
    .name		= _name,	\
    .fid 		= 0,	    \
    .sfid		= 0,	    \
    .type		= TYPE_ADF,	\
    .rec_len	= 0,    	\
    .desc		= _desc 	\
};\
INIT_LIST_HEAD(&file_table[i_file].lnk);     \
INIT_LIST_HEAD(&file_table[i_file].children);\
if(file_table[i_file].parent){               \
    list_add_tail(&file_table[i_file].lnk, &file_table[i_file].parent->children);\
}\
ADFusim.file = &file_table[i_file];\
ADFusim.aid = _aid;\
i_file++;\


void init_sim_fs();
void free_fs_mem();
void walk_df(char *name);
void print_file_info(struct sim_file *file);
void print_file_data(struct sim_file *file);
struct sim_file *get_file_by_name(char *name);
struct sim_file *get_file_by_fid(uint16_t fid);


#define IS_EF(file) (file->type==TYPE_EF_TR) ||\
                    (file->type==TYPE_EF_LF) ||\
                    (file->type==TYPE_EF_CY)
#define MF  file_table[0]
#define GET_SIM_FILE_BY_LNK(x) list_entry(x, struct sim_file, lnk)
#define SIM_FILE_NAME(name) get_file_by_name(name)
#define SIM_FILE_FID(fid) get_file_by_fid(fid)


#define foreach_child(file_ptr) \
    for (iter = file_ptr->children.next;\
         iter != &file_ptr->children;\
         iter = iter->next)


#endif  /*__SIMCARD_FILESYSTEM_H__*/
