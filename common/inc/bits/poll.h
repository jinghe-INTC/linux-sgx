#ifndef SGX_POLLFD_H
#define SGX_POLLFD_H

#include "bits/types.h"
#include "bits/syscall_types.h"

#ifndef SGX_UNTRUSTED_POLLFD
#define SGX_UNTRUSTED_POLLFD
typedef struct sgx_host_pollfd
{
    sgx_host_fd_t fd;
    short int events;
    short int revents;
} sgx_host_pollfd;
#endif

typedef struct sgx_pollfd
{
    int fd;
    short int events;
    short int revents;
} sgx_pollfd;

#endif // SGX_POLLFD_H
