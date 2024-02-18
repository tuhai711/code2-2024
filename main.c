#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <linux/sockios.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_arp.h>
#include <sys/uio.h>

#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/un.h>
#include <pthread.h>
#include <sys/stat.h>
#include <limits.h>

#define HELLO_APP_CTRL        "/tmp/hello_app_ctrl"
int webCtrlAgentSendtoApp(const char *buf, size_t len)
{
  struct sockaddr_un      serveraddr;
  int sock = -1;
  sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock < 0) {
    printf("[webCtrlAgentSendtoApp] socket error\n");
    return -1;
  }

  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sun_family = AF_UNIX;
  strncpy(serveraddr.sun_path, HELLO_APP_CTRL,sizeof(serveraddr.sun_path)-1);
//printf("[webCtrlAgentSendtoApp] %s, %d\n", buf, len);
//  printf("webCtrlAgentSendtoApp Send: %s\n", buf);
  if(sendto(sock, buf, len, 0, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
  {
    printf("webCtrlAgentSendtoApp send err():%d \n", errno);
    close(sock);
    return -1;
  }
  close(sock);
  return 0;
}
int main (int argc, char* argv[])
{
	char buffin[8] = {0, };
	while(1)
	{
		printf("Input 1 to send ABcontrol. and 2 exit ABcontrol.\n");
		memset(buffin, 0, 8);
		scanf("%s",buffin);
		printf("Abnormal Start %s\n", buffin);
		if(strncmp(buffin, "1", 1) == 0)
		{
			webCtrlAgentSendtoApp("HELLO-AB", strlen("HELLO-AB"));
			struct timeval now = {0 };
                        gettimeofday(&now, NULL);
                        long tmp = now.tv_sec * 1000000 + now.tv_usec;
			int i = 0;
			while(1)
			{
				i++;
				printf(" %d\n", i);
				sleep(1);
				if(i == 10)
					break;
			}
		}else  if(strncmp(buffin, "2", 1) == 0)
		{
			webCtrlAgentSendtoApp("HELLO-EX", strlen("HELLO-EX"));
		}
//		usleep(500);
	}
	return 1;
}
