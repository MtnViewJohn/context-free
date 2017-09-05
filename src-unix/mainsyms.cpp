const char*
prettyInt(unsigned long v)
{
    if (!v) return "0";
    
    static char temp[32];
    temp[31] = '\0';
    int i = 0;
    char* pos = temp + 30;
    for(;;) {
        *pos = '0' + (v % 10);
        v = v / 10;
        if (!v) return pos;
        ++i;
        --pos;
        if (i % 3 == 0) {
            *pos = ',';
            --pos;
        }
    }
}
