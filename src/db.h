/* Database file format.

Copyright (C) 2005 Red Hat, Inc. All rights reserved.

You can use this file without restriction.

This file is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

(This file defines a file format, so even the LGPL seems too restrictive.
   Share and enjoy.)

Author: Miloslav Trmac <mitr@redhat.com> */

#ifndef DB_H__
#define DB_H__

#include <stdint.h>

/* FIXME: See mlocate.db(5) */

/* File header */
struct db_header
{
  uint8_t magic[8];		/* See DB_MAGIC below */
  uint8_t version;	       /* File format version, see DB_VERSION* below */
  uint8_t check_visibility;	/* Check file visibility in locate(1) */
};
/* Followed by an EOF-terminated sequence of directories.
   
   Directory records are not output for unreadable directories; such
   directories do have an entry in their parent directory.

   "/" does not have a parent directory, so it is not present in the database
   at all. */

/* Contains a '\0' byte to unambiguously mark the file as a binary file. */
#define DB_MAGIC { '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e' }

#define DB_VERSION_0 0x00

/* Directory header */
struct db_directory
{
  uint64_t ctime;		/* st_ctime of the directory in big endian */
  /* Followed by NUL-terminated absolute path of the directory */
};
/* Followed by directory entries terminated by DBE_END, sorted by name using
   strcmp () */

/* Directory entry */
struct db_entry
{
  uint8_t type;			/* See DBE_* below */
  /* Followed by NUL-terminated name if tag != DBE_END */
};

enum
  {
    DBE_NORMAL		= 0,	/* A non-directory file */
    DBE_DIRECTORY	= 1,	/* A directory */
    DBE_END		= 2   /* End of directory contents; contains no name */
  };

#endif
