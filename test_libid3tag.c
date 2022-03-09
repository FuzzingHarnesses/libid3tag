#include <stdio.h>

#include <id3tag.h>

int main(int argc, char *argv[]) {
  struct id3_file *id3file = NULL;
  
  id3file = id3_file_open(argv[1], ID3_FILE_MODE_READONLY);
  if (!id3file)
  {
    return 1;
  }
  id3_file_close(id3file);
  return 0;
}
