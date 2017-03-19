typedef struct bignumber_s {
    char sign;
    int len;
    char data[];
} bignumber_s;

bignumber_s *make_bignumber_temp(int len, int sign);

bignumber_s *make_bignumber_fromstr(const char *str);

void print_bignumber(bignumber_s* b);

bignumber_s *make_bignumber_temp(int len, int sign)
{
    bignumber_s *temp = malloc(sizeof(bignumber_s) + len);
    if (NULL == temp) {
        perror("Malloc");
        exit(-1);
    }
    temp->sign = sign;
    temp->len = len;
    memset(temp->data, 0, len);
    return temp;
}

bignumber_s *make_bignumber_fromstr(const char *str)
{
    int sign = 0;
    if (str[0] == '-') {
        sign = 1;
        str++;
    }
    const char *striped_str = strip_str(str);

    int len = strlen(striped_str);

    bignumber_s *temp = make_bignumber_temp(len, sign);

    fill_data_fromstr(temp, striped_str);

    return temp;
}

const char *strip_str(const char *str)
{
    int i = 0;
    int len = strlen(str);
    for (i = 0; i < len-1 && str[i] == '0'; i++);
    return str+i;
}

void fill_data_fromstr(bignumber_s *n, const char *str)
{
    int i = 0;
    int len = n->len;
    for (i = 0; i < len; i ++) {
        int d = str[len-1-i]-'0';
        if (d >= 0 && d <= 9)
            n->data[i] = d;
        else {
            fprintf(stderr, "Invalid Number:%s\n", str);
            exit(-1);
        } 
    } 
}
void print_bignumber(bignumber_s* b) 
{ 
    int len = b->len; 
    char *str = malloc(len+1); 
    int i = 0; 
    for (i=0; i<len; i++) { 
        str[i] = b->data[len-i-1]+'0'; 
    } 
    str[len] = '\0'; 
    fprintf(stdout,"%s%s\n", b->sign==1?"-":"", strip_str(str)); 
    free(str); 
}
