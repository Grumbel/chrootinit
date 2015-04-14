#include <sys/mount.h>
#include <unistd.h>
#include <stdio.h>

#define ROOT_DEVICE     "/dev/hde1"
#define ROOT_FILESYSTEM "reiserfs"
#define CHROOT_TARGET   "/debian"

int main(int argc, char** argv)
{   
   if (mount(ROOT_DEVICE, "/", ROOT_FILESYSTEM, MS_REMOUNT, "") != 0)
     puts("Remount failed");
   else
     puts("Remount successfull");
   
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
     puts("Remount / failed");
   else
     puts("Remount / successfull");
   
   return 0;
}
