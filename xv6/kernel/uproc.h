struct uproc {
    int pid;
    int state;
    int sz;
    char name[16];
    uint64 nsched;
    uint64 nticks;
};
