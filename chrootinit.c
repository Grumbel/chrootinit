// Copyright (c) 2006 Ingo Ruhnke <grumbel@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include <sys/mount.h>
#include <unistd.h>
#include <stdio.h>

#define ROOT_DEVICE     "/dev/hde1"
#define ROOT_FILESYSTEM "reiserfs"
#define CHROOT_TARGET   "/debian"

int main(int argc, char** argv)
{
  if (mount(ROOT_DEVICE, "/", ROOT_FILESYSTEM, MS_REMOUNT, "") != 0)
  {
    puts("Remount failed");
  }
  else
  {
    puts("Remount successfull");
  }

  if (chroot(CHROOT_TARGET) == 0)
  {
    puts("Starting Child Init");
    execv("/sbin/init", argv);
  }
  else
  {
    puts("Error: Couldn't chroot into /debian");
  }

  if (mount(ROOT_DEVICE, "/", ROOT_FILESYSTEM, MS_REMOUNT | MS_RDONLY, "") != 0)
  {
    puts("Remount / failed");
  }
  else
  {
    puts("Remount / successfull");
  }

  return 0;
}

/* EOF */
