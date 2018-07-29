#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <string>

using namespace std;

struct folder
{
    string dir;
    string property;
    int prop_user_id;
};

typedef struct folder folder;

struct user_folder
{
    string dir;
    int write;
    int read;
};

typedef struct user_folder user_folder;

struct user_folder_file
{
    user_folder *folders;
};

typedef struct user_folder_file user_folder_file;

struct file
{
    string filename;
    string property;
    int user_id;
    string filenum;
};

struct user_file
{
    string filename;
    int write;
    int read;
    int execute;
};

typedef struct user_file user_file;

struct user_files_file
{
    user_file *files;
};

typedef struct user_files_file user_files_file;

struct user
{
    string username;
    int user_id;
    int user_type;
    string md5passwd;
    string folders_file_location;
    string files_file_location;
    user_folder_file fof;
    user_files_file fif;
};

typedef struct user user;

struct sys_memory
{
    int usersnum;
    int foldernum;
    int filenum;
    int next_user;
    int next_file;
    folder *folders;
    file *files;
    string usr_file_location;
    string _all_files_file_location;
    string _all_folders_file_location;
    user *users;
    int current_user_id;
};

typedef struct sys_memory sys_memory;

#endif // TYPES_H_INCLUDED
