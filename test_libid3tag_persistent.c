#include <stdio.h>
#include <id3tag.h>
#include <unistd.h>


#ifndef __AFL_FUZZ_TESTCASE_LEN
  ssize_t fuzz_len;
  #define __AFL_FUZZ_TESTCASE_LEN fuzz_len
  unsigned char fuzz_buf[1024000];
  #define __AFL_FUZZ_TESTCASE_BUF fuzz_buf
  #define __AFL_FUZZ_INIT() void sync(void);
  #define __AFL_LOOP(x) ((fuzz_len = read(0, fuzz_buf, sizeof(fuzz_buf))) > 0 ? 1 : 0)
  #define __AFL_INIT() sync()
#endif

__AFL_FUZZ_INIT();

int main(int argc, char *argv[]) {

#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
#endif

unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;  // must be after __AFL_INIT
                                                 // and before __AFL_LOOP!
struct id3_tag *tag;                                            
  while (__AFL_LOOP(10000)) {

    int len = __AFL_FUZZ_TESTCASE_LEN;  // don't use the macro directly in a
                                        // call!

    /* Setup function call, e.g. struct target *tmp = libtarget_init() */
    /* Call function to be fuzzed, e.g.: */
    tag = id3_tag_parse(buf, len);
    if (tag) {
        id3_tag_delete(tag);
    }
    /* Reset state. e.g. libtarget_free(tmp) */
  }
  return 0;
}

