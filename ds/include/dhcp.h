#ifndef _OL_102_DHCP_H_
#define _OL_102_DHCP_H_

#include <stddef.h>

typedef struct dhcp dhcp_t;

typedef enum status
{
    SUCCESS,
    MALLOC_FAILED,
    DOES_NOT_EXIST,
    ALLREADY_FREED,
    TRIE_IS_FULL,
    NOT_IN_SUBNET_RANGE
} status_t;

/*o(?)*/
dhcp_t *DhcpCreate(const unsigned char subnet_id_bytes[4], size_t occupied_bits); 

/*o(log(n)) return*/
status_t DhcpAllocteIp(dhcp_t *dhcp,
                 const unsigned char optional_ip[4], unsigned char new_ip[4]); 

/* o(log(n)) */
status_t DhcpFreeIp(dhcp_t *dhcp, const unsigned char ip_address[4]); 

 /* o(n) */
size_t DhcpCountFree(const dhcp_t *dhcp);

/* */
void DhcpDestroy(dhcp_t *dhcp)

#endif /* _OL_102_DHCP_H_ */