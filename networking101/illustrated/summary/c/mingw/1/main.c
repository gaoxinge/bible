#include <stdio.h>
#include <winsock2.h>

// inet_addr：字符串ip转化为long
// inet_ntoa: 结构体ip转化为字符串ip
// inet_aton：字符串ip转化为结构体ip
// htonl：    32位的主机字节序转换到网络字节序
// htnos：    16位的主机字节序转换到网络字节序
// ntohl：    32位的网络字节序转换到主机字节序
// ntohs：    16位的网络字节序转换到主机字节序

int main() {
    char *ip = "192.168.1.1";
    int long_ip = inet_addr(ip);
    int machine_ip = htonl(long_ip);
    
    struct in_addr struct_ip;
    struct_ip.S_un.S_addr = ntohl(machine_ip + 2);
    printf(inet_ntoa(struct_ip));
    
    return 0;
}