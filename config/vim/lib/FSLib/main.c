#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

typedef enum hl : char{
  NORM,
  MY,
  OTH
} hl;

typedef struct writer {
  char *buf;
  int cursor;
  hl hl;
} writer;

const char my_perms_hl[] = "%#MyPerms#";
const char oth_perms_hl[] = "%#OthPerms#";
const char norm_hl[] = "%#StatusLine#";
const int buf_size = 128;

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

#define SET_HL(hl, writer) \
    memcpy(&writer->buf[writer->cursor], hl, sizeof(hl)); \
    writer->cursor += sizeof(hl) - 1

void write_hl(writer *writer, hl hl) {
  if (writer->hl == hl) return;

  switch (hl) {
  case NORM:
    SET_HL(norm_hl, writer);
    break;
  case MY:
    SET_HL(my_perms_hl, writer);
    break;
  case OTH:
    SET_HL(oth_perms_hl, writer);
    break;
  }

  writer->hl = hl;
}

void write_perms(const struct stat *st, writer *writer) {
  unsigned int mode_bit = 256;
  char symbols[] = {'r', 'w', 'x'};
  int ids[] = {getuid(), getgid(), 0};
  int fids[] = {st->st_uid, st->st_gid, 0};

  for (int i = 0; i < LEN(ids); ++i) {
    if (ids[i] == fids[i]) {
      write_hl(writer, MY);
      for (int j = i; j < LEN(ids); ++j)
        ids[j] = -1;
    } else {
      write_hl(writer, OTH);
    }

    for (int i = 0; i < sizeof(symbols); ++i) {
      if (st->st_mode & mode_bit) {
        writer->buf[writer->cursor++] = symbols[i];
      } else {
        writer->buf[writer->cursor++] = '-';
      }
      mode_bit >>= 1;
    }
  }

  SET_HL(norm_hl, writer);
}

void write_size(writer *writer, double size) {
  char suffixes[] = {'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y', 'R', 'Q'};
  char suffix = 0;
  while (size >= 1024) {
    size /= 1024;
    ++suffix;
  }
  suffix = suffixes[suffix];
  writer->cursor += sprintf(&writer->buf[writer->cursor], " %.2f%c ", size, suffix);
}

void write_time(writer *writer, long timestamp) {
  struct tm mtm;
  localtime_r(&timestamp, &mtm);
  char *time_fmt;
  time_t now = time(NULL);
  struct tm *localnow = localtime(&now);

  if (localnow->tm_year != mtm.tm_year || localnow->tm_mon != mtm.tm_mon ||
      localnow->tm_mday - mtm.tm_mday > 5) {
    time_fmt = "%d %b %EY";
  } else if (localnow->tm_wday == mtm.tm_wday) {
    time_fmt = "%H:%M:%S";
  } else {
    time_fmt = "%a %H:%M";
  }

  strftime(&writer->buf[writer->cursor], buf_size - writer->cursor, time_fmt, &mtm);
}

char *fileInfo(const char *path) { // external - vim can call this
  char *buf = malloc(buf_size);
  writer writer = {buf, 0, NORM};

  struct stat st;
  if (stat(path, &st) != 0) return "";

  write_perms(&st, &writer);
  write_size(&writer, st.st_size);
  write_time(&writer, st.st_mtim.tv_sec);
  return buf;
}
