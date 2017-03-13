https://gist.github.com/sfantree/831ab83b751b6cf72e9e9a005f2d6e8b
struct icmp {
    unsigned char type; // 类型
    unsigned char code; // 代码
    unsigned short checksum; // 校检和
    unsigned short id; // 标识符
    unsigned short sequence; // 序号
    struct timeval timestamp; // 时间戳
};

struct ip {
    unsigned char version:4; // 版本
    unsigned char hlen:4; // 首部长度
    unsigned char tos; // 服务类型
    unsigned short len; // 总长度
    unsigned short id; // 标识符
    unsigned short offset; // 标志和片偏移
    unsigned char ttl; // 生存时间
    unsigned char protocol; // 协议
    unsigned short checksum; // 校验和
    struct in_addr ipsrc; // 32位圆ip地址
    struct in_addr ipdst; // 32位目的ip地址
};

struct sockaddr_in {
    sa_family_t sin_family; // 地址族
    uint16_t sin_port; // 端口号
    struct in_addr sin_addr; // 32位IP地址
    char sin_zero[8]; // 不使用
};

#define in_addr_t uint32_t
struct in_addr {
    in_addr_t s_addr; // 32位IP地址
};
