#include <rpmalloc.h>

#undef NDEBUG
#include <assert.h>
#include <string.h>

int main (void)
{
  assert (rpmalloc_initialize (0) == 0);
  assert (rpmalloc_is_thread_initialized () != 0);

  size_t n = 128;
  char *p = (char *) rpmalloc (n);
  assert (p != 0);
  assert (rpmalloc_usable_size (p) >= n);

  memset (p, 0x5a, n);

  size_t m = 4096;
  p = (char *) rprealloc (p, m);
  assert (p != 0);
  assert (rpmalloc_usable_size (p) >= m);
  assert ((unsigned char) p[0] == 0x5a);

  rpfree (p);

  rpmalloc_thread_finalize ();
  rpmalloc_finalize ();

  return 0;
}
