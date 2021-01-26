#ifndef _SGX_SYSCALL_TYPES_H
#define _SGX_SYSCALL_TYPES_H

//#include <openenclave/bits/defs.h>
//#include <openenclave/bits/types.h>

typedef int64_t sgx_host_fd_t;

typedef u_int64_t sgx_nfds_t;

typedef union _sgx_epoll_data_t {
    void* ptr;
    int fd;
    u_int32_t u32;
    u_int64_t u64;
} sgx_epoll_data_t;

struct sgx_epoll_event
{
    u_int32_t events;
    sgx_epoll_data_t data;
};

#endif // _SGX_SYSCALL_TYPES_H

