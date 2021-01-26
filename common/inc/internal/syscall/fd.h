#ifndef _SGX_SYSCALL_FD_H
#define _SGX_SYSCALL_FD_H

#include <stddef.h>
#include <bits/types.h>
//#include <internal/syscall/sys/epoll.h>
//#include <internal/syscall/sys/socket.h>
//#include <internal/syscall/sys/stat.h>
//#include <internal/syscall/sys/uio.h>
#include <bits/syscall_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _sgx_fd_type
{
    SGX_FD_TYPE_NONE = 0,
    SGX_FD_TYPE_ANY,
    SGX_FD_TYPE_FILE,
    SGX_FD_TYPE_SOCKET,
    SGX_FD_TYPE_EPOLL,
} sgx_fd_type_t;

typedef struct _sgx_fd sgx_fd_t;

/* Common operations on file-descriptor objects. */
typedef struct _sgx_fd_ops
{
    ssize_t (*read)(sgx_fd_t* desc, void* buf, size_t count);

    ssize_t (*write)(sgx_fd_t* desc, const void* buf, size_t count);

//    ssize_t (*readv)(sgx_fd_t* desc, const struct sgx_iovec* iov, int iovcnt);

//    ssize_t (*writev)(sgx_fd_t* desc, const struct sgx_iovec* iov, int iovcnt);

    int (*flock)(sgx_fd_t* desc, int operation);

    int (*dup)(sgx_fd_t* desc, sgx_fd_t** new_fd);

    int (*ioctl)(sgx_fd_t* desc, unsigned long request, u_int64_t arg);

    int (*fcntl)(sgx_fd_t* desc, int cmd, u_int64_t arg);

    int (*close)(sgx_fd_t* desc);

    sgx_host_fd_t (*get_host_fd)(sgx_fd_t* desc);
} sgx_fd_ops_t;

/* File operations. */
typedef struct _sgx_file_ops
{
    /* Inherited operations. */
    /*sgx_fd_ops_t fd;

    sgx_off_t (*lseek)(sgx_fd_t* file, sgx_off_t offset, int whence);

    ssize_t (*pread)(sgx_fd_t* desc, void* buf, size_t count, sgx_off_t offset);

    ssize_t (
        *pwrite)(sgx_fd_t* desc, const void* buf, size_t count, sgx_off_t offset);

    int (*getdents64)(sgx_fd_t* file, struct sgx_dirent* dirp, uint32_t count);

    int (*fstat)(sgx_fd_t* file, struct sgx_stat_t* buf);

    int (*ftruncate)(sgx_fd_t* file, sgx_off_t length);

    int (*fsync)(sgx_fd_t* file);
    int (*fdatasync)(sgx_fd_t* file);*/
} sgx_file_ops_t;

/* Socket operations .*/
typedef struct _sgx_socket_ops
{
    /* Inherited operations. */
    /*sgx_fd_ops_t fd;

    int (*connect)(
        sgx_fd_t* sock,
        const struct sgx_sockaddr* addr,
        sgx_socklen_t addrlen);

    sgx_fd_t* (*accept)(
        sgx_fd_t* sock,
        struct sgx_sockaddr* addr,
        sgx_socklen_t* addrlen);

    int (*bind)(
        sgx_fd_t* sock,
        const struct sgx_sockaddr* addr,
        sgx_socklen_t addrlen);

    int (*listen)(sgx_fd_t* sock, int backlog);

    ssize_t (*send)(sgx_fd_t* sock, const void* buf, size_t len, int flags);

    ssize_t (*recv)(sgx_fd_t* sock, void* buf, size_t len, int flags);

    ssize_t (*sendto)(
        sgx_fd_t* sock,
        const void* buf,
        size_t len,
        int flags,
        const struct sgx_sockaddr* dest_addr,
        sgx_socklen_t addrlen);

    ssize_t (*recvfrom)(
        sgx_fd_t* sock,
        void* buf,
        size_t len,
        int flags,
        struct sgx_sockaddr* src_addr,
        sgx_socklen_t* addrlen);

    ssize_t (*sendmsg)(sgx_fd_t* sock, const struct sgx_msghdr* msg, int flags);

    ssize_t (*recvmsg)(sgx_fd_t* sock, struct sgx_msghdr* msg, int flags);

    int (*shutdown)(sgx_fd_t* sock, int how);

    int (*getsockopt)(
        sgx_fd_t* sock,
        int level,
        int optname,
        void* optval,
        sgx_socklen_t* optlen);

    int (*setsockopt)(
        sgx_fd_t* sock,
        int level,
        int optname,
        const void* optval,
        sgx_socklen_t optlen);

    int (*getpeername)(
        sgx_fd_t* sock,
        struct sgx_sockaddr* addr,
        sgx_socklen_t* addrlen);

    int (*getsockname)(
        sgx_fd_t* sock,
        struct sgx_sockaddr* addr,
        sgx_socklen_t* addrlen);*/
} sgx_socket_ops_t;

/* epoll operations. */
typedef struct _sgx_epoll_ops
{
    /* Inherited operations. */
    sgx_fd_ops_t fd;

    int (*epoll_ctl)(
        sgx_fd_t* epoll,
        int op,
        int fd,
        struct sgx_epoll_event* event);

    int (*epoll_wait)(
        sgx_fd_t* epoll,
        struct sgx_epoll_event* events,
        int maxevents,
        int timeout);

    void (*on_close)(sgx_fd_t* epoll, int fd);
} sgx_epoll_ops_t;

struct _sgx_fd
{
    sgx_fd_type_t type;
    union {
        sgx_fd_ops_t fd;
        sgx_file_ops_t file;
        sgx_socket_ops_t socket;
        sgx_epoll_ops_t epoll;
    } ops;
};

#ifdef __cplusplus
}
#endif


#endif // _SGX_SYSCALL_FD_H
