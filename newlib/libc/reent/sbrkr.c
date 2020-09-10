/* Reentrant version of sbrk system call. */

#include <reent.h>
#include <unistd.h>
#include <_syslist.h>

/* Some targets provides their own versions of these functions.  Those
   targets should define REENTRANT_SYSCALLS_PROVIDED in TARGET_CFLAGS.  */

#ifdef _REENT_ONLY
#ifndef REENTRANT_SYSCALLS_PROVIDED
#define REENTRANT_SYSCALLS_PROVIDED
#endif
#endif

#if defined (REENTRANT_SYSCALLS_PROVIDED)

int _dummy_sbrk_syscalls = 1;

#else

/* We use the errno variable used by the system dependent layer.  */
#undef errno
extern int errno;

/*
FUNCTION
	<<_sbrk_r>>---Reentrant version of sbrk
	
INDEX
	_sbrk_r

SYNOPSIS
	#include <reent.h>
	void *_sbrk_r(struct _reent *<[ptr]>, ptrdiff_t <[incr]>);

DESCRIPTION
	This is a reentrant version of <<sbrk>>.  It
	takes a pointer to the global data block, which holds
	<<errno>>.
*/

char* current_brk = 0;

void sbrk_init (ptrdiff_t init_addr) {
    current_brk = (char*)init_addr;
}

void *
_sbrk_r (struct _reent *ptr,
     ptrdiff_t incr)
{
//  printf("Calling sbrk with old brk %#lx and incr %ld\n", current_brk, (uint64_t)incr);
//  printf("incr signed is %ld\n", (int64_t)incr);
  char* old_brk = current_brk;
  current_brk += incr;
  return old_brk;
  // char *ret;
  // void *_sbrk(ptrdiff_t);

  // errno = 0;
  // if ((ret = (char *)(_sbrk (incr))) == (void *) -1 && errno != 0)
  //   ptr->_errno = errno;
  // return ret;
}

#endif /* ! defined (REENTRANT_SYSCALLS_PROVIDED) */
