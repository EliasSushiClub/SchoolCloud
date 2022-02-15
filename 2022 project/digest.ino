#include <MD5.h>

String md5Hash(String hashInput) {
    unsigned char* hash=MD5::make_hash(hashInput);
    char *md5str = MD5::make_digest(hash, 16);
    free(hash);
    while(!Serial);
    return md5str;
    //free(md5str);
}
