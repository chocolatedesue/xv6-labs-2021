#include "kernel/types.h"
#include "user/user.h"
   
const int N = 512;

int main(int argc, char *argv[]) {

	int p1[2],p2[2];
    pipe (p1);
    pipe (p2);

    char buf[N];

    if (fork()==0){
        close (p1[1]);
        close (p2[0]);
        
        read(p1[0],buf,1);
        printf("%d: received ping\n", getpid());
        write(p2[1]," ",1);
        close (p2[1]);
        close (p1[0]);
        // exit(0);
    }
    else {
        close (p1[0]);
        close (p2[1]);

        write(p1[1]," ",1);
        // wait()
        // read 自身阻塞
        read (p2[0],buf,1);
        printf("%d: received pong\n", getpid());
        close (p1[1]);
        close (p2[0]);
    }
    exit(0);

}   