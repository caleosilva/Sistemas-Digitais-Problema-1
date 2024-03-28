 #include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../address_map_arm.h"

 /* Prototypesforfunctionsusedtoaccessphysicalmemoryaddresses */
int open_physical(int);
void * map_physical(int,unsignedint,unsignedint);
void close_physical(int);
int unmap_physical(void *,unsignedint);

/* ThisprogramincrementsthecontentsoftheredLEDparallelport */
 int main(void)
  {
  volatileint * LEDR_ptr; //virtualaddresspointertoredLEDs
  int fd =-1; //usedtoopen/dev/mem
  void *LW_virtual; //physicaladdressesforlight-weightbridge
 
  //CreatevirtualmemoryaccesstotheFPGAlight-weightbridge
  if ((fd=open_physical(fd))==-1)
  return (-1);
  if (!(LW_virtual=map_physical(fd,LW_BRIDGE_BASE,LW_BRIDGE_SPAN)))
  return (-1);
 
  //Set virtualaddresspointertoI/Oport
  LEDR_ptr=(int *)(LW_virtual+LEDR_BASE);
  *LEDR_ptr= *LEDR_ptr+1; //Add1totheI/Oregister
 
  unmap_physical(LW_virtual,LW_BRIDGE_SPAN);
  close_physical(fd);
  return 0;
}