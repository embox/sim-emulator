FILE_MF;
FILE_DF("DF.GSM", 0x7f20, "GSM Network related files", get_file_by_name("MF"));
FILE_LIN_EF("EF.DIR", 0x2f00, 0x1e, "Application directory", get_file_by_name("MF"), 108, 54, 2);
SIM_FILE_NAME("EF.DIR")->data.rec = malloc(SIM_FILE_NAME("EF.DIR")->n_recs*sizeof(struct record));
SIM_FILE_NAME("EF.DIR")->data.rec[0].size = 43;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data = malloc(SIM_FILE_NAME("EF.DIR")->data.rec[0].size*sizeof(unsigned char));
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[0] = 0x61;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[1] = 0x29;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[2] = 0x4f;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[3] = 0x10;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[4] = 0xa0;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[5] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[6] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[7] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[8] = 0x87;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[9] = 0x10;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[10] = 0x02;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[11] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[12] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[13] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[14] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[15] = 0x89;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[16] = 0x07;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[17] = 0x09;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[18] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[19] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[20] = 0x50;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[21] = 0x05;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[22] = 0x55;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[23] = 0x53;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[24] = 0x69;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[25] = 0x6d;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[26] = 0x31;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[27] = 0x73;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[28] = 0x0e;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[29] = 0xa0;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[30] = 0x0c;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[31] = 0x80;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[32] = 0x01;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[33] = 0x17;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[34] = 0x81;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[35] = 0x02;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[36] = 0x5f;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[37] = 0x60;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[38] = 0x82;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[39] = 0x03;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[40] = 0x45;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[41] = 0x41;
SIM_FILE_NAME("EF.DIR")->data.rec[0].data[42] = 0x50;
SIM_FILE_NAME("EF.DIR")->data.rec[1].size = 27;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data = malloc(SIM_FILE_NAME("EF.DIR")->data.rec[1].size*sizeof(unsigned char));
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[0] = 0x61;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[1] = 0x19;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[2] = 0x4f;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[3] = 0x10;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[4] = 0xa0;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[5] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[6] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[7] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[8] = 0x87;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[9] = 0x10;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[10] = 0x04;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[11] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[12] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[13] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[14] = 0xff;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[15] = 0x89;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[16] = 0x07;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[17] = 0x09;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[18] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[19] = 0x00;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[20] = 0x50;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[21] = 0x05;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[22] = 0x49;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[23] = 0x53;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[24] = 0x69;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[25] = 0x6d;
SIM_FILE_NAME("EF.DIR")->data.rec[1].data[26] = 0x31;
FILE_TRN_EF("EF.ICCID", 0x2fe2, 0x02, "ICC Identification", get_file_by_name("MF"), 10);
SIM_FILE_NAME("EF.ICCID")->data.trn = malloc(SIM_FILE_NAME("EF.ICCID")->size*sizeof(unsigned char));
SIM_FILE_NAME("EF.ICCID")->data.trn[0] = 0x98;
SIM_FILE_NAME("EF.ICCID")->data.trn[1] = 0x88;
SIM_FILE_NAME("EF.ICCID")->data.trn[2] = 0x12;
SIM_FILE_NAME("EF.ICCID")->data.trn[3] = 0x01;
SIM_FILE_NAME("EF.ICCID")->data.trn[4] = 0x00;
SIM_FILE_NAME("EF.ICCID")->data.trn[5] = 0x00;
SIM_FILE_NAME("EF.ICCID")->data.trn[6] = 0x40;
SIM_FILE_NAME("EF.ICCID")->data.trn[7] = 0x03;
SIM_FILE_NAME("EF.ICCID")->data.trn[8] = 0x10;
SIM_FILE_NAME("EF.ICCID")->data.trn[9] = 0xf0;
FILE_LIN_EF("EF.PL", 0x2f05, 0x05, "Preferred Languages", get_file_by_name("MF"), 6, 2, 3);
SIM_FILE_NAME("EF.PL")->data.rec = malloc(SIM_FILE_NAME("EF.PL")->n_recs*sizeof(struct record));
SIM_FILE_NAME("EF.PL")->data.rec[0].size = 2;
SIM_FILE_NAME("EF.PL")->data.rec[0].data = malloc(SIM_FILE_NAME("EF.PL")->data.rec[0].size*sizeof(unsigned char));
SIM_FILE_NAME("EF.PL")->data.rec[0].data[0] = 0x64;
SIM_FILE_NAME("EF.PL")->data.rec[0].data[1] = 0x65;
SIM_FILE_NAME("EF.PL")->data.rec[1].size = 2;
SIM_FILE_NAME("EF.PL")->data.rec[1].data = malloc(SIM_FILE_NAME("EF.PL")->data.rec[1].size*sizeof(unsigned char));
SIM_FILE_NAME("EF.PL")->data.rec[1].data[0] = 0x65;
SIM_FILE_NAME("EF.PL")->data.rec[1].data[1] = 0x6e;
SIM_FILE_NAME("EF.PL")->data.rec[2].size = 2;
SIM_FILE_NAME("EF.PL")->data.rec[2].data = malloc(SIM_FILE_NAME("EF.PL")->data.rec[2].size*sizeof(unsigned char));
SIM_FILE_NAME("EF.PL")->data.rec[2].data[0] = 0xff;
SIM_FILE_NAME("EF.PL")->data.rec[2].data[1] = 0xff;
FILE_TRN_EF("EF.IMSI", 0x6f07, 0, "IMSI", get_file_by_name("DF.GSM"), 9);
SIM_FILE_NAME("EF.IMSI")->data.trn = malloc(SIM_FILE_NAME("EF.IMSI")->size*sizeof(unsigned char));
SIM_FILE_NAME("EF.IMSI")->data.trn[0] = 0x08;
SIM_FILE_NAME("EF.IMSI")->data.trn[1] = 0x29;
SIM_FILE_NAME("EF.IMSI")->data.trn[2] = 0x82;
SIM_FILE_NAME("EF.IMSI")->data.trn[3] = 0x60;
SIM_FILE_NAME("EF.IMSI")->data.trn[4] = 0x82;
SIM_FILE_NAME("EF.IMSI")->data.trn[5] = 0x00;
SIM_FILE_NAME("EF.IMSI")->data.trn[6] = 0x00;
SIM_FILE_NAME("EF.IMSI")->data.trn[7] = 0x20;
SIM_FILE_NAME("EF.IMSI")->data.trn[8] = 0x80;
FILE_TRN_EF("EF.KC", 0x6f20, 0, "Ciphering key Kc", get_file_by_name("DF.GSM"), 9);
SIM_FILE_NAME("EF.KC")->data.trn = malloc(SIM_FILE_NAME("EF.KC")->size*sizeof(unsigned char));
SIM_FILE_NAME("EF.KC")->data.trn[0] = 0x83;
SIM_FILE_NAME("EF.KC")->data.trn[1] = 0x7d;
SIM_FILE_NAME("EF.KC")->data.trn[2] = 0x78;
SIM_FILE_NAME("EF.KC")->data.trn[3] = 0x36;
SIM_FILE_NAME("EF.KC")->data.trn[4] = 0x09;
SIM_FILE_NAME("EF.KC")->data.trn[5] = 0xa3;
SIM_FILE_NAME("EF.KC")->data.trn[6] = 0x85;
SIM_FILE_NAME("EF.KC")->data.trn[7] = 0x8f;
SIM_FILE_NAME("EF.KC")->data.trn[8] = 0x05;
FILE_LIN_EF("EF.LP", 0x6f05, 0, "Language Preference", get_file_by_name("DF.GSM"), 1, 1, 1);
SIM_FILE_NAME("EF.LP")->data.rec = malloc(SIM_FILE_NAME("EF.LP")->n_recs*sizeof(struct record));
SIM_FILE_NAME("EF.LP")->data.rec[0].size = 1;
SIM_FILE_NAME("EF.LP")->data.rec[0].data = malloc(SIM_FILE_NAME("EF.LP")->data.rec[0].size*sizeof(unsigned char));
SIM_FILE_NAME("EF.LP")->data.rec[0].data[0] = 0x24;
