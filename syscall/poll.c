#include <stdlib.h>
#include <syscall/fdtable.h>
#include <se_trace.h>
#include <sgx_error.h>
#include <syscall/sys/poll.h>
#include "syscall_t.h"

int sgx_poll(struct sgx_pollfd* fds, sgx_nfds_t nfds, int timeout)
{
    int ret = -1;
    int retval = -1;
    struct sgx_host_pollfd* host_fds = NULL;
    sgx_nfds_t i;

    if (!fds || nfds == 0)
        se_trace(SE_TRACE_ERROR, "Error: return: %d\n", SGX_ERROR_INVALID_PARAMETER);

    if (!(host_fds = calloc(nfds, sizeof(struct sgx_host_pollfd))))
		se_trace(SE_TRACE_ERROR, "Error: return: %d\n", SGX_ERROR_OUT_OF_MEMORY);	

    /* Convert enclave fds to host fds. */
    for (i = 0; i < nfds; i++)
    {
        sgx_host_fd_t host_fd;
        sgx_fd_t* desc;

        /* Fetch the fd struct for this fd struct. */
        if (!(desc = sgx_fdtable_get(fds[i].fd, SGX_FD_TYPE_ANY)))
            se_trace(SE_TRACE_ERROR, "Error: bad file.\n");

        /* Get the host fd for this fd struct. */
        if ((host_fd = desc->ops.fd.get_host_fd(desc)) == -1)
             se_trace(SE_TRACE_ERROR, "Error: bad file.\n");

        host_fds[i].events = fds[i].events;
        host_fds[i].fd = host_fd;
    }

    if (sgx_syscall_poll_ocall(&retval, host_fds, nfds, timeout) != SGX_SUCCESS) 
        se_trace(SE_TRACE_ERROR, "Error: return: %d\n", SGX_ERROR_INVALID_PARAMETER);

    /* Update fds[] with any recieved events. */
    for (i = 0; i < nfds; i++)
        fds[i].revents = host_fds[i].revents;

    ret = retval;

done:

    if (host_fds)
        free(host_fds);

    return ret;
}

