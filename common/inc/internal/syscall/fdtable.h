#ifndef _SGX_SYSCALL_FDTABLE_H
#define _SGX_SYSCALL_FDTABLE_H

#include <stddef.h>
#include <bits/types.h>
#include <internal/syscall/fd.h>

#ifdef __cplusplus
extern "C" {
#endif

sgx_fd_t* sgx_fdtable_get(int fd, sgx_fd_type_t type);

int sgx_fdtable_assign(sgx_fd_t* desc);

int sgx_fdtable_reassign(int fd, sgx_fd_t* new_desc, sgx_fd_t** old_desc);

int sgx_fdtable_release(int fd);

void sgx_fdtable_foreach(
    sgx_fd_type_t type,
    void* arg,
    void (*callback)(sgx_fd_t* desc, void* arg));

#ifdef __cplusplus
}
#endif

#endif // _SGX_SYSCALL_FDTABLE_H
