#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<pthread.h>
#include<stdbool.h>

void isFile(char *name);
void read_dir(char *dir)
{
    char path[256];  //放置地址路径
    /*opendir函数的返回值是一个DIR指针，成功将返回指向该目录的句柄，一个 DIR 指针（其实质是一个结构体指针），
    其作用类似于open函数返回的文件描述符fd，后续对该目录的操作需要使用该DIR指针变量；若调用失败，则返回NULL。
    readdir函数的返回值是一个指向dirent结构体的指针*/
    DIR *dp;
    struct dirent *sdp;
    //打开目录项
    dp=opendir(dir);
    if(dp==NULL)
    {
        perror("opendir error");
        return;
    }
    //读取目录项
    /*每调用一次 readdir()，就会从 dp指针 所指向的目录流中读取下一条目录项（目录条目），并返回 struct dirent结构体指针，
    指向经静态分配而得的 struct dirent 类型结构，每次调用 readdir()都会覆盖该结构。
    一旦遇到目录结尾或是出错，readdir()将返回 NULL，针对后一种情况，还会设置 errno 以示具体错误。*/
    while((sdp=readdir(dp))!=NULL)
    {
        if(strcmp(sdp->d_name,".")==0 || strcmp(sdp->d_name,"..")==0)
        {
            continue;
        }
        sprintf(path, "%s/%s",dir,sdp->d_name);
        isFile(path);
    }
    closedir(dp);
    return;

}

void isFile(char *name)
{
    int ret =0;
    struct stat sb;
    ret = stat(name,&sb);
    if(ret==-1)
    {
        perror("stat error");
        return ;
    }
    if(S_ISDIR(sb.st_mode))
    {
        read_dir(name);
    }
    else
    {
        printf("%10s\t\t%ld\n",name,sb.st_size);
    }
    return ;
}

int main(int argc,char *argv[])
{
    if(argc==1)
    {
        isFile(".");
    }
    else{
        isFile(argv[1]);
    }
    return 0;
}
