
 //Server Code
 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<sys/ipc.h>
 #include<sys/shm.h>
 #include<string.h>
 struct data{
 char str[100];
 int flag;
 };
 void main()
 {
 key_t key= ftok("abc.txt",'A');
 int shmid= shmget(key,1024,0777|IPC_CREAT);
 struct data *d= shmat(shmid , NULL ,0);
 d->flag=0;
 printf("\nEnter data");
 gets(d->str);
 d->flag=1;
 while(d-> flag != -1)
 {
 printf("\n waiting");
 sleep(2);
 }
 shmdt(d);
 shmctl(shmid, IPC_RMID , NULL);
 }

 //Client Code
 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<unistd.h>
 #include<sys/ipc.h>
 #include<sys/shm.h>
 struct data{
 char str[100];
 int flag;
 };
 void main(){
 key_t key= ftok("abc.txt",'A');
 int shmid= shmget(key,1024,0777|IPC_CREAT);
 struct data *d= shmat(shmid , NULL ,0);
 d->flag=0;
 while(d->flag!=1)
 {
 printf("\n waiting ");
 sleep(2);
 }
 printf("\n received data id ");
 printf("%s",d->str);
 d->flag=-1;
 shmdt(d);
 }
