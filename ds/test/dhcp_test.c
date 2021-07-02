
#include "dhcp.h"

#include <stdio.h>  /* printf */
#include <math.h>   /* pow */
#include <string.h> /* pow */

#define IPV4_SIZE (4)
#define OCCUPIED_BITS (24)
#define NUM_OF_BIT (8)
#define RESERVED_IP (3)
#define IP_OPTION_SIZE (256)
#define LAST_BYTE_INDEX (3)

/*---------------test func-----------------*/
static void PrintIp(unsigned char *ip);
static void TestDhcp();

static void Test();

int main()
{
    Test();
    TestDhcp();
    return 0;
}
static void Test()
{
    dhcp_t *dhcp = NULL;
    unsigned char server_address[] = {192, 18, 32, 254};
    unsigned char broadcast_address[] = {192, 18, 32, 255};
    unsigned char network_address[] = {192, 18, 32, 0};
    unsigned char optional_ip[] = {192, 18, 32, 13};
    unsigned char temp_ip[] = {192, 18, 32, 13};
    unsigned char new_ip[IPV4_SIZE] = {0};
    int status = 10;

    size_t i = 0;

    dhcp = DhcpCreate(server_address, OCCUPIED_BITS);

    if (NULL == dhcp)
    {
        printf("DhcpCreate failed at line: %d\n", __LINE__);
    }

    if ((0X1 << NUM_OF_BIT) - RESERVED_IP != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
        printf("actual: %lu\n", DhcpCountFree(dhcp));
        printf("exp: %d\n", (0X1 << NUM_OF_BIT) - RESERVED_IP);
    }

    memset(new_ip, 0, IPV4_SIZE);
    if (NOT_IN_SUBNET_RANGE != (status = DhcpAllocteIp(dhcp, server_address, new_ip)))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
        PrintIp(new_ip);
    }

    memset(new_ip, 0, IPV4_SIZE);
    if (NOT_IN_SUBNET_RANGE != (status = DhcpAllocteIp(dhcp, network_address, new_ip)))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
        PrintIp(new_ip);
    }

    memset(new_ip, 0, IPV4_SIZE);
    if (NOT_IN_SUBNET_RANGE != (status = DhcpAllocteIp(dhcp, broadcast_address, new_ip)))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
        PrintIp(new_ip);
    }

    memset(new_ip, 0, IPV4_SIZE);
    if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", SUCCESS);
        PrintIp(new_ip);
    }

    if (NOT_IN_SUBNET_RANGE != (status = DhcpFreeIp(dhcp, server_address)))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
    }
    /* 252  */
    if (((0X1 << NUM_OF_BIT) - RESERVED_IP - 1) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
        printf("actual: %lu\n", DhcpCountFree(dhcp));
        printf("exp: %d\n", (0X1 << NUM_OF_BIT) - RESERVED_IP);
    }
    /* 256  */
    for (i = 0; i < IP_OPTION_SIZE; ++i)
    {
        memset(new_ip, 0, IPV4_SIZE);
        status = -1;
        optional_ip[LAST_BYTE_INDEX] = (unsigned char)(i + 1);

        if (SUCCESS != (status = DhcpAllocteIp(dhcp, optional_ip, new_ip)) &&
            (0X1 << NUM_OF_BIT) - RESERVED_IP - 1 > i)
        { /* 252  */
            printf("DhcpAllocteIp failed at line: %d in index: %lu\n", __LINE__, i);
            printf("actual: %d\n", status);
            printf("exp: %d\n", SUCCESS);
            PrintIp(new_ip);
            PrintIp(optional_ip);
        }
        /* 252  */
        if ((0X1 << NUM_OF_BIT) - RESERVED_IP - 1 == i && (TRIE_IS_FULL != (status = DhcpAllocteIp(dhcp, optional_ip, new_ip))))
        {
            printf("DhcpAllocteIp failed at line: %d in index: %lu\n", __LINE__, i);
            printf("actual: %d\n", status);
            printf("exp: %d\n", TRIE_IS_FULL);
            PrintIp(new_ip);
            PrintIp(optional_ip);
        }
        /* 252  */
        if ((0X1 << NUM_OF_BIT) - RESERVED_IP < i && (NOT_IN_SUBNET_RANGE != (status = DhcpAllocteIp(dhcp, optional_ip, new_ip))))
        {
            printf("DhcpAllocteIp failed at line: %d in index: %lu\n", __LINE__, i);
            printf("actual: %d\n", status);
            printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
            PrintIp(new_ip);
            PrintIp(optional_ip);
        }
    }

    for (i = 0; i < IPV4_SIZE; ++i)
    {
        optional_ip[i] = temp_ip[i];
    }

    status = DhcpFreeIp(dhcp, optional_ip);
    if (SUCCESS != status)
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", SUCCESS);
        PrintIp(optional_ip);
    }

    if (ALLREADY_FREED != (status = DhcpFreeIp(dhcp, optional_ip)))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", ALLREADY_FREED);
    }

    if (NOT_IN_SUBNET_RANGE != (status = DhcpFreeIp(dhcp, broadcast_address)))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
    }

    if (NOT_IN_SUBNET_RANGE != (status = DhcpFreeIp(dhcp, network_address)))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
    }
    if (NOT_IN_SUBNET_RANGE != (status = DhcpFreeIp(dhcp, server_address)))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
        printf("actual: %d\n", status);
        printf("exp: %d\n", NOT_IN_SUBNET_RANGE);
    }

    DhcpDestroy(dhcp);
    return;
}

static void TestDhcp()
{
    dhcp_t *dhcp = NULL;
    unsigned char subnet_id[4] = {192, 168, 0, 0};

    unsigned char optional_ip[4] = {192, 168, 15, 13};
    unsigned char network_address[4] = {192, 168, 0, 0};
    unsigned char broadcast_address[4] = {192, 175, 255, 255};
    unsigned char server_address[4] = {192, 175, 255, 254};
    unsigned char not_in_range[4] = {195, 168, 0, 254};
    unsigned char new_ip[4] = {0};
    unsigned char free_address[4] = {192, 168, 244, 54};

    size_t occupied_bits = 13;
    size_t i = 0;
    size_t size = pow(2, (32 - occupied_bits));

    dhcp = DhcpCreate(subnet_id, occupied_bits);

    if (NULL == dhcp)
    {
        printf("DhcpCreate failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, server_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, broadcast_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, network_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (ALLREADY_FREED != DhcpFreeIp(dhcp, optional_ip))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpFreeIp(dhcp, not_in_range))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, not_in_range, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size - 3; ++i)
    {
        memset(new_ip, 0, 4);

        if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
        {
            printf("DhcpAllocteIp failed at line: %d in index: %lu\n", __LINE__, i);
            printf("actual ip: ");
            PrintIp(new_ip);
        }
    }

    if (0 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (SUCCESS != DhcpFreeIp(dhcp, free_address))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (1 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
        printf("size: %lu\n", DhcpCountFree(dhcp));
    }

    memset(new_ip, 0, 4);

    if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (0 != memcmp(free_address, new_ip, 4))
    {
        printf("test failed at line: %d\n", __LINE__);
        puts("actual: \n");
        PrintIp(new_ip);
        puts("expected: \n");
        PrintIp(free_address);
    }

    DhcpDestroy(dhcp);

    return;
}

static void PrintIp(unsigned char *ip)
{
    size_t i = 0;

    puts("ip: ");

    for (i = 0; i < IPV4_SIZE; ++i)
    {
        printf("%d . ", ip[i]);
    }

    puts("\n");
}