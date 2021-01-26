#ifndef _SGX_SYSCALL_SYS_POLL_H
#define _SGX_SYSCALL_SYS_POLL_H

#include <stddef.h>
#include <bits/types.h>
#include <bits/poll.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SGX_POLLIN     0x001
#define SGX_POLLPRI    0x002
#define SGX_POLLOUT    0x004
#define SGX_POLLRDNORM 0x040
#define SGX_POLLRDBAND 0x080
#define SGX_POLLWRNORM 0x100
#define SGX_POLLWRBAND 0x200
#define SGX_POLLMSG    0x400
#define SGX_POLLRDHUP  0x2000
#define SGX_POLLERR    0x008
#define SGX_POLLHUP    0x010
#define SGX_POLLNVAL   0x020

int sgx_poll(struct sgx_pollfd* fds, sgx_nfds_t nfds, int timeout);

#ifdef __cplusplus
}
#endif


#endif /* _SGX_SYSCALL_SYS_POLL_H */
