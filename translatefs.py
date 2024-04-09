#!/usr/bin/python

import os

print('Translating file system')

get_func_name = "get_file_by_name"
out_file = "fs.inc"

mcr_mf = "FILE_MF"
mcr_df = "FILE_DF"
mcr_trn = "FILE_TRN_EF"
mcr_lin = "FILE_LIN_EF"

with open(out_file, "w") as out_f:
    out_f.write("FILE_MF;\n")
    print('Added MF')

    for (root,dirs,files) in os.walk('MF', topdown=True): 
        parent = os.path.basename(root)

        # process dedicated file entries
        dir_desc_files = []
        for dir in dirs:
            desc_file = dir + ".desc" 
            dir_desc_files.append(desc_file)
            with open(root + "/" + desc_file, "r") as f:
                dir_fid = f.readline().strip()
                dir_desc = f.readline().strip()
            def_str = f'FILE_DF("{dir}", {dir_fid}, "{dir_desc}", {get_func_name}("{parent}"));'
            out_f.write(def_str+"\n")
            print('Added ' + dir)

        # process elementary file entries
        for ef in files:
            # skip dedicated file description files
            if ef in dir_desc_files:
                continue
            with open(root + '/' + ef, "r") as f:
                ef_type = f.readline().strip()
                ef_fid  = f.readline().strip()
                ef_sfid = f.readline().strip()
                ef_desc = f.readline().strip()
                ef_recl = f.readline().strip()
                ef_size = f.readline().strip()

                # if transparent EF read last line as data string
                if ef_type == "TRN":
                    bytes = []
                    def_str = f'FILE_TRN_EF("{ef}", {ef_fid}, {ef_sfid}, "{ef_desc}", {get_func_name}("{parent}"), {ef_size});'
                    out_f.write(def_str+"\n")
                    data = f.readline().strip()
                    bytes = [data[2*i]+data[2*i+1] for i in range(int(len(data)/2))]
                    out_f.write(f'SIM_FILE_NAME("{ef}")->data.trn = malloc(SIM_FILE_NAME("{ef}")->size*sizeof(unsigned char));\n')
                    if int(ef_size) != len(bytes):
                        print('Warning: data size doesn‘t match with specified file size')
                    for i in range(int(ef_size)):
                          out_f.write(f'SIM_FILE_NAME("{ef}")->data.trn[{i}] = 0x{bytes[i]};\n')

                # if linear fixed EF read last lines as separate record entries
                elif ef_type == "LIN":
                    bytes = [[]]
                    records = list()
                    # read records
                    l = 0;
                    rec = f.readline().strip()
                    while rec:
                        records.append(rec)
                        l += 1
                        rec = f.readline().strip()

                    if (len(rec) % 2 == 1):
                        print("Warning: odd data string length. Two symbols per byte assumed.")
                    if (len(rec)/2 > int(ef_recl)):
                        print("Warning: entry length is greater than specified record length")

                    bytes = [[rec[2*i]+rec[2*i+1] for i in range(int(len(rec)/2))] for rec in records]

                    def_str = f'FILE_LIN_EF("{ef}", {ef_fid}, {ef_sfid}, "{ef_desc}", {get_func_name}("{parent}"), {l*int(ef_recl)}, {ef_recl}, {l});'
                    out_f.write(def_str+"\n")
                    out_f.write(f'SIM_FILE_NAME("{ef}")->data.rec = malloc(SIM_FILE_NAME("{ef}")->n_recs*sizeof(struct record));\n')

                    for i in range(l):
                        out_f.write(f'SIM_FILE_NAME("{ef}")->data.rec[{i}].size = {len(bytes[i])};\n')
                        out_f.write(f'SIM_FILE_NAME("{ef}")->data.rec[{i}].data = malloc(SIM_FILE_NAME("{ef}")->data.rec[{i}].size*sizeof(unsigned char));\n')
                        t = 0
                        for byte in bytes[i]:
                            out_f.write(f'SIM_FILE_NAME("{ef}")->data.rec[{i}].data[{t}] = 0x{byte};\n')
                            t += 1

                else:
                    print("unknown file format")
                    continue
                print('Added ' + ef)
