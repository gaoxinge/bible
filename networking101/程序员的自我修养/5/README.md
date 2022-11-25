# 第5章 Windows PE/COFF

## COFF

- IMAGE_FILE_HEADER：相当于ELF Header
- IMAGE_SECTION_HEADER[]：相当于Section Table

## PE

- IMAGE_DOS_HEADER：兼容DOS
- IMAGE_NT_HEADERS：扩展PE头文件
  - IMAGE_FILE_HEADERS：相当于ELF HEADER
  - IMAGE_OPTIONAL_HEADER32/IMAGE_OPTIONAL_HEADER64：包含数据目录
    - IMAGE_DATA_DIRECTORY[]：包含表的地址和长度
      - 导出表
      - 导入表
      - 资源表
      - 异常表
      - 重定位表
      - 调试信息表
      - TLS
- IMAGE_SECTION_HEADER[]：相当于Section Table
