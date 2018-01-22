#include <iostream>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

using namespace std;
void operation();
int flag = 0;

void exit_()
{
    cout << "exit system" << endl;
    return;
}
void pwd()
{
    char buf[64];
    getcwd(buf, sizeof(buf));
    cout << "current working directory:  " << buf << endl;
    operation();
}
int mydir(char *name)
{
    DIR *dirp;
    struct dirent *ent;
    if (strcmp("", name) == 0)
        dirp = opendir(".");
    else
        dirp = opendir(name);
    if (dirp == NULL)
    {
        cout << "Failed ectory!" << endl;
        return -1;
    }
    cout << "output file:  ";
    while ((ent = readdir(dirp)) != NULL)
        if (ent->d_name[0] != '.')
            cout << ent->d_name << "  "<<endl;
    closedir(dirp);
    cout << endl
         << endl;
    operation();
    return 0;
}
void mycd(char *name)
{
    if (strcmp("", name) == 0)
        return;
    if (chdir(name) == 0)
        cout << "work directory changed successfully!";
    else
        cout << "the directory does not exist!";
    cout << endl;
    operation();
}

void makedir(char *name)
{
    if (mkdir(name,0766) == 0)
    {
        cout << "successful mkdir " << name;
    }
    else
    {
        cout << "failure mkdir " << name;
    }
    cout << endl;
    operation();
}

void deldir(char *name)
{

    if (rmdir(name) == 0)
        cout << "delete successfull " << name;
    else
        cout << "delete failure " << name;
    cout << endl;
    operation();
}
void reName(char *oldName, char *newName)
{
    if (rename(oldName, newName) == 0)
        cout << newName << " success change to" << oldName;
    else
        cout << newName << " failure change to" << oldName;

    cout << endl;
    operation();
}

void mycopy(char *oldName, char *newName)
{
    char sourcepath[255];
    char aimpath[255];
    FILE *newfp;
    FILE *oldfp;
    char ch;
    getcwd(sourcepath, 255);
    getcwd(aimpath, 255);
    strcat(sourcepath, "/");
    strcat(sourcepath, newName);
    strcat(aimpath, "/");
    strcat(aimpath, oldName);
    if ((oldfp = fopen(aimpath, "r")) == NULL)
    {
        printf("no push file %s!\n ", aimpath);
        return;
    }
    if ((newfp = fopen(sourcepath, "w")) == NULL)
    {
        printf("file open failed！");
        return;
    }
    while ((ch = fgetc(oldfp)) != EOF)
    {
        fputc(ch, newfp);
    }
    fclose(oldfp);
    fclose(newfp);
    cout << sourcepath << " " << aimpath;
    cout << endl;
    operation();
}

void show_file(char *path, char *file)
{
    struct dirent *ent = NULL;
    DIR *pDir;
    if ((pDir = opendir(path)) != NULL)
    {
        while (NULL != (ent = readdir(pDir)))
        {
	    if (ent->d_name[0] != '.')
               show_file(ent->d_name,file);

	    if(strcmp(ent->d_name,file) == 0){
	    	flag = 1;
		cout<<path<<"/"<<file;
	    }
        }
        closedir(pDir);
    }
}
void pass(char *A, char *B)
{
    show_file(A,B);
    if (flag == 0)
    {
        cout << "file does not exis";
    }else{
	flag = 0;
    }
    cout << endl;
    operation();
}
void operation()
{ 
    const char *d = " ";
    char *p;
    char str[20];
    int i = 0;
    cout << "enter command: ";
    while ((str[i] = getchar()) != '\n')
        i++;
    str[i] = '\0';
    p = strtok(str, d);

    if (strcmp("pwd", p) == 0)
    {
        p = strtok(NULL, d);
        if (p != NULL)
        {
            cout << "enter the error command";
            return;
        }
        pwd();
    }
    else if (strcmp("list", p) == 0)
    {
        p = strtok(NULL, d);
        if (p)
        {
            mydir(p);
        }
    }
    else if (strcmp("chdir", p) == 0)
    {
        p = strtok(NULL, d);
        if (p)
        {
            mycd(p);
        }
    }
    else if (strcmp("mkdir", p) == 0)
    {
        p = strtok(NULL, d);
        if (p)
        {
            makedir(p);
        }
    }
    else if (strcmp("deldir", p) == 0)
    {
        p = strtok(NULL, d);
        if (p)
        {
            deldir(p);
        }
    }
    else if (strcmp("rename", p) == 0)
    {
        char *A, *B;
        p = strtok(NULL, d);
        A = p;
        p = strtok(NULL, d);
        B = p;
        if (A && B)
            reName(A, B);
    }
    else if (strcmp("copy", p) == 0)
    {
        char *C, *D;
        p = strtok(NULL, d);
        C = p;
        p = strtok(NULL, d);
        D = p;
        if (C && D)
            mycopy(C, D);
    }
    else if (strcmp("find", p) == 0)
    {
        char *targetDirectory, *targetFile;
        p = strtok(NULL, d);
        targetDirectory = p;
        p = strtok(NULL, d);
        targetFile = p;
        if (targetDirectory && targetFile)
            pass(targetDirectory, targetFile);
    }
    else if (strcmp("out", p) == 0)
    {
        exit_();
    }
    else
    {
        cout << "enter mistaken" << endl;
        operation();
    }
}
int main()
{
    operation();
    return 0;
}
