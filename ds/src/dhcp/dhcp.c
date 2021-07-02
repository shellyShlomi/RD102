/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:27.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By:  ;	        	    						    *
 *  Description: DHCP a network management protocol used on     *
 *               Internet Protocol (IP) networks for            * 
 *               automatically assigning IP addresses           */

#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* printf */

#include "dhcp.h"
#include "trie.h"

#define BITS_IN_4BYTES (32)
#define IPV4 (4)
#define BITS_IN_BYTE (8)
#define LEST_BYTE (3)
#define FAULT (0)
#define TRUE (1)

enum reserved_ips
{
    NETWORK_ADDRESS,
    SERVER_ADDRESS,
    BROADCAST_ADDRESS,
    RESERVED_IPS
};

typedef enum func
{
    FREE,
    ALLOC
} func_t;

struct dhcp
{
    trie_t *trie;
    unsigned long subnet_id;
    unsigned long bit_of_claint;
    unsigned long reserved_ip[RESERVED_IPS];
};

/*------------- helper funcs ------------*/
static void CovertToArr(unsigned long ip, unsigned char new_ip[4]);
static unsigned long CovertToLong(unsigned char ip[]);

static int InitReservedIp(dhcp_t *dhcp);

static int IsInSubnetRange(dhcp_t *dhcp, unsigned long ip);
/*------------------------------ implementetion --------------------------------*/

dhcp_t *DhcpCreate(const unsigned char subnet_id_bytes[4], size_t occupied_bits)
{
    unsigned long mask = ~0 << ((unsigned long)BITS_IN_4BYTES - (unsigned long)occupied_bits);

    dhcp_t *dhcp = NULL;

    assert(subnet_id_bytes);

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (!dhcp)
    {
        return (NULL);
    }

    dhcp->subnet_id = CovertToLong((unsigned char *)subnet_id_bytes) & mask;

    dhcp->bit_of_claint = (unsigned long)(BITS_IN_4BYTES - occupied_bits);

    dhcp->trie = TrieCreate((dhcp->bit_of_claint));

    if (!dhcp->trie)
    {
        dhcp->subnet_id = 0;
        dhcp->bit_of_claint = 0;

        free(dhcp);
        dhcp = NULL;
    }

    InitReservedIp(dhcp);

    return (dhcp);
}

/* o(n) */
size_t DhcpCountFree(const dhcp_t *dhcp)
{
    assert(dhcp);
    assert(dhcp->trie);

    return ((0x1 << dhcp->bit_of_claint) - TrieSize(dhcp->trie));
}

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(dhcp);
    assert(dhcp->trie);

    TrieDestroy(dhcp->trie);

    dhcp->trie = NULL;
    dhcp->subnet_id = 0;
    dhcp->bit_of_claint = 0;

    free(dhcp);
    dhcp = NULL;

    return;
}

dhcp_status_t DhcpAllocteIp(dhcp_t *dhcp,
                            const unsigned char optional_ip[4], unsigned char new_ip[4])
{
    int status = SUCCESS;
    unsigned long returnd_ip = 0;
    unsigned long ip = 0;

    assert(new_ip);
    assert(dhcp);

    if (optional_ip)
    {
        ip = CovertToLong((unsigned char *)optional_ip);
    }
    else
    {
        ip = (~ip & dhcp->subnet_id) + 1;
    }

    if (!IsInSubnetRange(dhcp, ip))
    {
        return (NOT_IN_SUBNET_RANGE);
    }
    status = TrieInsert(dhcp->trie, ip, &returnd_ip);
    CovertToArr(returnd_ip, new_ip);

    return (status);
}

dhcp_status_t DhcpFreeIp(dhcp_t *dhcp, const unsigned char ip_address[4])
{
    unsigned long ip = 0;

    assert(dhcp);
    assert(ip_address);

    ip = CovertToLong((unsigned char *)ip_address);

    if (!IsInSubnetRange(dhcp, ip))
    {
        return (NOT_IN_SUBNET_RANGE);
    }
    if (IsIpFree(dhcp->trie, ip))
    {
        return (ALLREADY_FREED);
    }

    TrieRemove(dhcp->trie, ip);

    return (SUCCESS);
}

static unsigned long CovertToLong(unsigned char ip[])
{
    unsigned long mask = 0;
    size_t i = 0;

    assert(ip);

    for (i = 0; i < IPV4; ++i)
    {
        mask = mask << BITS_IN_BYTE;
        mask |= ip[i];
    }

    return (mask);
}

static void CovertToArr(unsigned long ip, unsigned char new_ip[4])
{
    size_t i = 0;
    assert(ip);
    assert(new_ip);

    for (i = 0; i < IPV4; ++i)
    {
        new_ip[IPV4 - i - 1] |= (unsigned char)ip;
        ip = (ip) >> BITS_IN_BYTE;
    }

    return;
}

static int IsInSubnetRange(dhcp_t *dhcp, unsigned long ip)
{
    unsigned long mask = ~(~0 << dhcp->bit_of_claint);
    unsigned long mask1 = ~0 << dhcp->bit_of_claint;

    assert(dhcp);

    mask = mask & ip;
    mask1 = mask1 & ip;

    if ((mask1 ^ dhcp->subnet_id) ||
        (mask >= (dhcp->reserved_ip[SERVER_ADDRESS]) ||
         (mask <= (dhcp->reserved_ip[NETWORK_ADDRESS]))))
    {
        return (FAULT);
    }

    return (TRUE);
}

static int InitReservedIp(dhcp_t *dhcp)
{
    unsigned long mask = ~0 << dhcp->bit_of_claint;
    unsigned long returnd_ip = 0;

    assert(dhcp);

        /*the reserved addres X .11111110 */
    if (TrieInsert(dhcp->trie, ((~mask) ^ 0x1), &returnd_ip) ||
        /*the reserved addres X.11111111*/
        TrieInsert(dhcp->trie, (~mask), &returnd_ip) ||
        /*the reserved addres X.000000000*/
        TrieInsert(dhcp->trie, 0, &returnd_ip))
    {
        DhcpDestroy(dhcp);
        dhcp = NULL;
        return (FAULT);
    }

    dhcp->reserved_ip[NETWORK_ADDRESS] = 0;
    dhcp->reserved_ip[SERVER_ADDRESS] = ((~mask) ^ 0x1);
    dhcp->reserved_ip[BROADCAST_ADDRESS] = (~mask);

    return (TRUE);
}