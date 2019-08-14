# 3. IP Addresses, structs, and Data Munging

## 3.2. Byte Order

- inet_addr: 字符串IP转化为长整型IP
- inet_ntoa: 结构体IP转化为字符串IP
- inet_aton: 字符串IP转化为结构体IP
- `htons`: host to network short / 16位的主机字节序转换到网络字节序
- `htonl`: host to network long / 32位的主机字节序转换到网络字节序
- `ntohs`: network to host short / 16位的网络字节序转换到主机字节序
- `ntohl`: network to host long / 32位的网络字节序转换到主机字节序