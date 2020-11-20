#ifndef CRC_COMMAND_H
#define CRC_COMMAND_H

#ifdef __cplusplus
    extern "C" {
#endif

class CRC_Command
{
public:
    CRC_Command();

public:
    unsigned short CrcCcittGet(const char * i_buf, int i_buf_len);
    unsigned char ChecksumGet (const char *i_buf, int i_buf_len);

};

#ifdef __cplusplus
    }
#endif

#endif // CRC_COMMAND_H

