//IN DEVELOP
/*
CerviOS_1.6.0
Added LINUX support
Added copy for files and folders
Added move for files and folders
Developed by C0D3R11
MIT License
*/
#define WINDOWS 0
#define LINUX 1

// OS: LINUX OR WINDOWS
#define OS LINUX

#include <iostream>

#if OS == WINDOWS
	#include <conio.h>
#elif OS == LINUX
	//Using milliseconds
#endif // OS

#include <fstream>

#if OS == WINDOWS
	#include <windows.h>
#elif OS == LINUX
	#include <stdlib.h>
	#include <unistd.h>
#endif //OS

#include <string>
#include <sstream>
#include <bits/basic_string.h>
#include "include/md5.h"
#include "include/types.h"

//GOTOXY not used and not LINUX supported
//#include "include/gotoxy/gotoxy.h"

using namespace std;

//Version
#define VERSION "CerviOS v1.6.2"

bool existsFile(string filename)
{
    ifstream file(filename.c_str());
    return file.good();
}

sys_memory sysmem;

void first_boot()
{
    cout << "It seems that this is the first time you run CerviOS, so we need you to configure it." << endl;
    string username;
    while (true)
    {
        cout << "Please insert the first username to create:";
        cin >> username;
        if (username[0] != '_')
        {
            break;
        }
        cout << "Please don't insert usernames that begin with _" << endl;
    }
    cout << "Username configured" << endl;
    string passwd;
    cout << "Please insert a password for the username:";
    cin >> passwd;
    cout << "Passwd configured" << endl;
    cout << "Please insert a password for the root user _system_:";
    string _system_pwd;
    cin >> _system_pwd;
    if (existsFile("usr_file.usrf"))
    {
        system("rm usr_file.usrf");
    }
    if (existsFile("init.cos"))
    {
        system("rm init.cos");
    }
    if (existsFile("_all_folders_file.fof"))
    {
        system("rm _all_folders_file.fof");
    }
    if (existsFile("_all_files_file.fif"))
    {
        system("rm _all_files_file.fif");
    }
    ofstream init_cos("init.cos");
    init_cos << "<usr_file.usrf>" << endl;
    init_cos << "<_all_folders_file.fof>" << endl;
    init_cos << "<_all_files_file.fif>" << endl;
    init_cos.close();

    ofstream usr_file_usrf("usr_file.usrf");
    usr_file_usrf << "<usr_file><2>" << endl;
    string usr_file_tmp_line = "<_system_><0><1><";
    usr_file_tmp_line = usr_file_tmp_line + md5(_system_pwd);
    usr_file_tmp_line = usr_file_tmp_line + "><_system_.fof><_system_.fif>";
    usr_file_usrf << usr_file_tmp_line.c_str() << endl;
    usr_file_tmp_line = "<" + username + "><1><0><" + md5(passwd) + "><" + username + ".fof><" + username + ".fif>";
    usr_file_usrf << usr_file_tmp_line.c_str() << endl;
    usr_file_usrf.close();

    ofstream all_folders_file_fof("_all_folders_file.fof");
    all_folders_file_fof << "<_all_folders_file><4>" << endl;
    all_folders_file_fof << "</><_system_>" << endl;
    all_folders_file_fof << "</config><_system_>" << endl;
    all_folders_file_fof << string("</" + username + "><_system_>").c_str() << endl;
    all_folders_file_fof << "</bin><_system_>" << endl;
    all_folders_file_fof.close();

    ofstream all_files_file_fif("_all_files_file.fif");
    all_files_file_fif << "<_all_files_file><2>" << endl;
    all_files_file_fif << "</config/cat.conf><0><_system_>" << endl;
    all_files_file_fif << "</bin/cat.coscode><1><_system_>" << endl;
    all_files_file_fif.close();

    ofstream _system__fof("_system_.fof");
    _system__fof << "<_system_><folder_file>" << endl;
    _system__fof << "</><0><0>" << endl;
    _system__fof << "</config><0><0>" << endl;
    _system__fof << string("</" + username + "><0><0>").c_str() << endl;
    _system__fof << "</bin><0><0>" << endl;
    _system__fof.close();

    ofstream user_fof(string(username + ".fof").c_str());
    user_fof << string("<" + username + "><folder_file>").c_str() << endl;
    user_fof << "</><0><0>" << endl;
    user_fof << "</config><0><0>" << endl;
    user_fof << string("</" + username + "><2><1>").c_str() << endl;
    user_fof << "</bin><0><0>" << endl;
    user_fof.close();

    ofstream _system__fif("_system_.fif");
    _system__fif << "<_system_><files_file>" << endl;
    _system__fif << "</config/cat.conf><0><0><0>" << endl;
    _system__fif << "</bin/cat.coscode><0><0><0>" << endl;
    _system__fif.close();

    ofstream user_fif(string(username + ".fif").c_str());
    user_fif << string("<" + username + "><files_file>").c_str() << endl;
    user_fif << "</config/cat.conf><0><0><0>" << endl;
    user_fif << "</bin/cat.coscode><0><0><0>" << endl;
    user_fif.close();

    //CAT_CONF FILE
    ofstream cat_conf("file0");
    cat_conf << "This is cat.conf file" << endl;
    cat_conf << "I hope you are enjoying CerviOS ;-)" << endl;
    cat_conf.close();
    //CAT_COSCODE FILE
    ofstream cat_coscode("file1");
    cat_coscode << "#this is a test coscode that prints 'A' to screen" << endl;
    cat_coscode << "boot" << endl;
    cat_coscode << "jmp main" << endl;
    cat_coscode << "main:" << endl;
    cat_coscode << "mov [stp+0],'A'" << endl;
    cat_coscode << "callf cout,[stp+0],[stp+0]" << endl;
    cat_coscode << "exit" << endl;
    cat_coscode.close();

    ofstream inited_cos("inited.cos");
    inited_cos << "Inited";
    inited_cos.close();

    cout << "Configured correctly!" << endl;
#if OS == WINDOWS
    cout << "Press a key for continue" << endl;
    getch();
#elif OS == LINUX
    //Using milliseconds instead of getch()
    usleep(5000);
#endif //OS
}

enum filetype
{
    file_init_cos,
    file_usr_file,
    file_all_folders_file,
    file_all_files_file,
    file_user_folder,
    file_user_file
};

void process_string(string str_to_proc,int file_line,filetype ftype, int usrnum)
{
    string str = "";
    string str1 = "";
    stringstream strstream;
    stringstream strstream1;
    stringstream strstream2;
    bool usr_found = false;
    int res = 0, res1 = 0;
    int last_i = 0;
    switch (ftype)
    {
    case file_init_cos:
        switch (file_line)
        {
        case 0:
            for (int i = 1; str_to_proc[i] != '>'; i++)
            {
                str += str_to_proc[i];
            }
            cout << "SYSMEM._USR_FILE_LOCATION = " << str << endl;
            sysmem.usr_file_location = str;
            break;
        case 1:
            for (int i = 1; str_to_proc[i] != '>'; i++)
            {
                str += str_to_proc[i];
            }
            cout << "SYSMEM._ALL_FOLDERS_FILE_LOCATION = " << str << endl;
            sysmem._all_folders_file_location = str;
            break;
        case 2:
            for (int i = 1; str_to_proc[i] != '>'; i++)
            {
                str += str_to_proc[i];
            }
            cout << "SYSMEM._ALL_FILES_FILE_LOCATION = " << str << endl;
            sysmem._all_files_file_location = str;
            //cout << "SYSMEM2._ALL_FILES_FILE_LOCATION" << endl;
            break;
        }
        break;
        case file_usr_file:
            if (file_line == 0)
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                try
                {
                    if (str.compare("usr_file"))
                    {
                        throw 1;
                    }
                }
                catch (int e)
                {
                    cout << "Error line:" << file_line << "\nFile:" << sysmem.usr_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nFile doesn't correspond to usr_file" << endl;
                    cout << "\nGetted value:" << str << endl;
#if OS == WINDOWS
		    cout << "Press a key to exit" << endl;
                    getch();
#elif OS == LINUX
		    //Using milliseconds instead of getch()
		    usleep(8000);
#endif //OS
                    exit(1);
                }
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream << str;
                strstream >> res;
                sysmem.usersnum = res;
                sysmem.users = new user[res];
                cout << "Users detected:" << res << endl;;
            }
            else
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str1 += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream << str1;
                strstream >> res;
                sysmem.users[res].username = str;
                sysmem.users[res].user_id = res;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream1 << str;
                strstream1 >> res1;
                sysmem.users[res].user_type = res1;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.users[res].md5passwd = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.users[res].folders_file_location = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.users[res].files_file_location = str;
            }
            break;
        case file_all_folders_file:
            if (file_line == 0)
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                try
                {
                    if (str.compare("_all_folders_file"))
                    {
                        throw 1;
                    }
                }
                catch (int e)
                {
                    cout << "Error line:" << file_line << "\nFile:" << sysmem._all_folders_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nFile doesn't correspond to _all_folders_file" << endl;
                    cout << "\nGetted value:" << str << endl;
#if OS == WINDOWS
		    cout << "Press a key to exit" << endl;
                    getch();
#elif OS == LINUX
		    //Using milliseconds instead of getch();
		    usleep(8000);
#endif //OS
                    exit(1);
                }
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream << str;
                strstream >> res;
                sysmem.foldernum = res;
                sysmem.folders = new folder[res];
                cout << "Folders detected:" << res << endl;;
            }
            else
            {
                for(int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.folders[file_line-1].dir = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.folders[file_line-1].property = str;
                usr_found = false;
                for (int i = 0; i < sysmem.usersnum; i++)
                {
                    if (!sysmem.users[i].username.compare(sysmem.folders[file_line-1].property))
                    {
                        sysmem.folders[file_line-1].prop_user_id = sysmem.users[i].user_id;
                        usr_found = true;
                    }
                }
                if (usr_found == false)
                {
                    sysmem.folders[file_line-1].property = "_system_";
                    sysmem.folders[file_line-1].prop_user_id = 0;
                }
            }
            break;
        case file_all_files_file:
            if (file_line == 0)
            {
                str = "";
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                try
                {
                    if (str.compare("_all_files_file"))
                    {
                        throw 1;
                    }
                }
                catch (int e)
                {
                    cout << "Error line:" << file_line << "\nFile:" << sysmem._all_files_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nFile doesn't correspond to _all_files_file" << endl;
                    cout << "\nGetted value:" << str << endl;
#if OS == WINDOWS
		    cout << "Press a key to exit" << endl;
                    getch();
#elif OS == LINUX
		    //Using milliseconds instead of getch()
		    usleep(8000);
#endif //OS
                    exit(1);
                }
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream << str;
                strstream >> res;
                sysmem.filenum = res;
                sysmem.files = new file[res];
                cout << "Files detected:" << res << endl;;
            }
            else
            {
                for(int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.files[file_line-1].filename = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.files[file_line-1].filenum = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.files[file_line-1].property = str;
                usr_found = false;
                for (int i = 0; i < sysmem.usersnum; i++)
                {
                    if (!sysmem.users[i].username.compare(sysmem.files[file_line-1].property))
                    {
                        sysmem.files[file_line-1].user_id = sysmem.users[i].user_id;
                        usr_found = true;
                    }
                }
                if (usr_found == false)
                {
                    sysmem.folders[file_line-1].property = "_system_";
                    sysmem.folders[file_line-1].prop_user_id = 0;
                }
            }
            break;
        case file_user_folder:
            if (file_line == 0)
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str1 += str_to_proc[i];
                    last_i = i + 3;
                }
                try
                {
                    if (sysmem.users[usrnum].username.compare(str))
                    {
                        throw 2;
                    }
                    else if (str1.compare("folder_file"))
                    {
                        throw 1;
                    }
                }
                catch(int e)
                {
                    if (e == 2)
                    {
                    cout << "Error line:" << file_line << "\nFile:" << sysmem.users[usrnum].folders_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nUser from file doesn't correspond to memory user" << endl;
                    cout << "\nGetted value:" << str << endl;
                    }
                    else if (e == 1)
                    {
                        cout << "Error line:" << file_line << "\nFile:" << sysmem.users[usrnum].folders_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nFiletype doesn't correspond to folder_file" << endl;
                        cout << "\nGetted value:" << str << endl;
                    }
#if OS == WINDOWS
		    cout << "Press a key to exit" << endl;
                    getch();
#elif OS == LINUX
		    //Using milliseconds instead of getch()
		    usleep(8000);
#endif //OS
                    exit(1);
                }
                sysmem.users[usrnum].fof.folders = new user_folder[sysmem.foldernum];
            }
            else
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.users[usrnum].fof.folders[file_line-1].dir = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream << str;
                strstream >> res;
                sysmem.users[usrnum].fof.folders[file_line-1].write = res;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream1 << str;
                strstream1 >> res;
                sysmem.users[usrnum].fof.folders[file_line-1].read = res;
            }
            break;
        case file_user_file:
            if (file_line == 0)
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str1 += str_to_proc[i];
                    last_i = i + 3;
                }
                try
                {
                    if (sysmem.users[usrnum].username.compare(str))
                    {
                        throw 2;
                    }
                    else if (str1.compare("files_file"))
                    {
                        throw 1;
                    }
                }
                catch(int e)
                {
                    if (e == 2)
                    {
                    cout << "Error line:" << file_line << "\nFile:" << sysmem.users[usrnum].folders_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nUser from file doesn't correspond to memory user" << endl;
                    cout << "\nGetted value:" << str << endl;
                    }
                    else if (e == 1)
                    {
                        cout << "Error line:" << file_line << "\nFile:" << sysmem.users[usrnum].folders_file_location << "\nLine:" << str_to_proc << "\nError num." << e << "\nFiletype doesn't correspond to files_file" << endl;
                        cout << "\nGetted value:" << str1 << endl;
                    }
#if OS == WINDOWS
		    cout << "Press a key to exit" << endl;
                    getch();
#elif OS == LINUX
		    //Using milliseconds instead of getch()
		    usleep(8000);
#endif //OS
                    exit(1);
                }
                sysmem.users[usrnum].fif.files = new user_file[sysmem.filenum];
            }
            else
            {
                for (int i = 1; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                sysmem.users[usrnum].fif.files[file_line-1].filename = str;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream << str;
                strstream >> res;
                sysmem.users[usrnum].fif.files[file_line-1].write = res;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream1 << str;
                strstream1 >> res;
                sysmem.users[usrnum].fif.files[file_line-1].read = res;
                str = "";
                for (int i = last_i; str_to_proc[i] != '>'; i++)
                {
                    str += str_to_proc[i];
                    last_i = i + 3;
                }
                strstream2 << str;
                strstream2 >> res;
                sysmem.users[usrnum].fif.files[file_line-1].execute = res;
            }
            break;
    }
}

void load_files()
{
    ifstream init_cos("init.cos");
    cout << "Init_cos_file" << endl;
    string line_buffer;
    int a = 0;
    while (getline(init_cos,line_buffer))
    {
        process_string(line_buffer,a,file_init_cos,0);
        cout << "Process line " << a << ";" << line_buffer << endl;
        a+=1;
    }
    init_cos.close();
    cout << "Init_cos_close" << endl;
    ifstream usr_file(sysmem.usr_file_location.c_str());
    cout << "Usr_file" << endl;
    a = 0;
    while(getline(usr_file,line_buffer))
    {
        process_string(line_buffer,a,file_usr_file,0);
        a++;
    }
    usr_file.close();
    cout << "Usr_file close" << endl;
    ifstream all_folders_file(sysmem._all_folders_file_location.c_str());
    cout << "All_folders_file" << endl;
    a = 0;
    while(getline(all_folders_file,line_buffer))
    {
        process_string(line_buffer,a,file_all_folders_file,0);
        a++;
    }
    all_folders_file.close();
    cout << "All_folders_file close" << endl;
    ifstream all_files_file(sysmem._all_files_file_location.c_str());
    cout << "All_files_file" << endl;
    a = 0;
    line_buffer = "";
    while(getline(all_files_file,line_buffer))
    {
        process_string(line_buffer,a,file_all_files_file,0);
        a++;
    }
    all_files_file.close();
    cout << "All_files_file close" << endl;
    cout << "User folder_files and files_files" << endl;
    for (int i = 0; i < sysmem.usersnum; i++)
    {
        ifstream user_fof(sysmem.users[i].folders_file_location.c_str());
        a = 0;
        while(getline(user_fof,line_buffer))
        {
            process_string(line_buffer,a,file_user_folder,i);
            a++;
        }
        user_fof.close();
        ifstream user_fif(sysmem.users[i].files_file_location.c_str());
        a = 0;
        while(getline(user_fif,line_buffer))
        {
            process_string(line_buffer,a,file_user_file,i);
            a++;
        }
        user_fif.close();
    }
    cout << "User folder_files and files_file close" << endl;
    cout << "Load successfuly completed" << endl;
}

void login()
{
    cout << VERSION << endl;
    while(true)
    {
    string user,pass;
    cout << "Username:";
    cin >> user;
    cout << "Password:";
    cin >> pass;
#if OS == WINDOWS
    Sleep(500);
#elif OS == LINUX
    usleep(500);
#endif // OS
    bool found = false;
    int usrnum;
    for (int i = 0; i < sysmem.usersnum; i++)
    {
        if (!sysmem.users[i].username.compare(user))
        {
            found = true;
            usrnum = i;
        }
    }
    if (found)
    {
        if (!sysmem.users[usrnum].md5passwd.compare(md5(pass)))
        {
            sysmem.current_user_id = usrnum;
            return;
        }
    }
    cout << "Error!!!" << endl;
    }
}

void save()
{
    //Deleted systems to solve error WINDOWS_H_SYSTEM_INJECTION
    cout << "Saving" << endl;
    //system(string("del " + sysmem.usr_file_location).c_str());
    ofstream usr_file(sysmem.usr_file_location.c_str());
    usr_file << string("<usr_file><" + std::to_string(sysmem.usersnum) + ">").c_str() << endl;
    for (int i = 0; i < sysmem.usersnum; i++)
    {
        usr_file << string("<" + sysmem.users[i].username + "><" + std::to_string(sysmem.users[i].user_id) + "><" + std::to_string(sysmem.users[i].user_type) + "><" + sysmem.users[i].md5passwd + "><" + sysmem.users[i].folders_file_location + "><" + sysmem.users[i].files_file_location + ">").c_str() << endl;
    }
    usr_file.close();
    //system(string("del " + sysmem._all_folders_file_location).c_str());
    ofstream all_folders_file(sysmem._all_folders_file_location.c_str());
    all_folders_file << string("<_all_folders_file><" + std::to_string(sysmem.foldernum) + ">").c_str() << endl;
    for (int i = 0; i < sysmem.foldernum; i++)
    {
        all_folders_file << string("<" + sysmem.folders[i].dir + "><" + sysmem.folders[i].property + ">").c_str() << endl;
    }
    all_folders_file.close();
    //system(string("del " + sysmem._all_files_file_location).c_str());
    ofstream all_files_file(sysmem._all_files_file_location);
    all_files_file << string("<_all_files_file><" + std::to_string(sysmem.filenum) + ">") << endl;
    for (int i = 0; i < sysmem.filenum; i++)
    {
        all_files_file << string("<" + sysmem.files[i].filename + "><" + sysmem.files[i].filenum + "><" + sysmem.files[i].property + ">").c_str() << endl;
    }
    all_files_file.close();
    for (int i = 0; i < sysmem.usersnum; i++)
    {
        //system(string("del " + sysmem.users[i].folders_file_location).c_str());
        ofstream fof(sysmem.users[i].folders_file_location.c_str());
        fof << string("<" + sysmem.users[i].username + "><folder_file>").c_str() << endl;
        for (int j = 0; j < sysmem.foldernum; j++)
        {
            fof << string("<" + sysmem.users[i].fof.folders[j].dir + "><" + std::to_string(sysmem.users[i].fof.folders[j].write) + "><" + std::to_string(sysmem.users[i].fof.folders[j].read) + ">") << endl;
        }
        fof.close();
        //system(string("del " + sysmem.users[i].files_file_location).c_str());
        ofstream fif(sysmem.users[i].files_file_location);
        fif << string("<" + sysmem.users[i].username + "><files_file>").c_str() << endl;
        for (int j = 0; j < sysmem.filenum; j++)
        {
            fif << string("<" + sysmem.users[i].fif.files[j].filename + "><" + std::to_string(sysmem.users[i].fif.files[j].write) + "><" + std::to_string(sysmem.users[i].fif.files[j].read) + "><" + std::to_string(sysmem.users[i].fif.files[j].execute) + ">") << endl;
        }
        fif.close();
    }
    cout << "Saved completed" << endl;
}

void shell()
{
    sysmem.next_file = sysmem.filenum - 1;
    sysmem.next_user = sysmem.usersnum - 1;
    string current_dir = "/";
    string cmd = "";
    string str1 = "",str2 = "", str4 = "", str5 = "", str6 = "";
    int last_i = 0;
    int barras = 0;
    int guis = 0;
    while(true)
    {
        guis = 0;
        cout << current_dir << "~";
        cin >> cmd;
        cmd += "_";
        for (int i = 0; i < cmd.length(); i++)
        {
            if (cmd[i] == '_')
            {
                guis++;
            }
        }
        for (int i = 0; cmd[i] != '_'; i++)
        {
            str1 += cmd[i];
            last_i = i + 2;
        }
        if (guis > 1)
        {
        for (int i = last_i; cmd[i] != '_'; i++)
        {
            str2 += cmd[i];
            last_i = i + 2;
        }
        }
        if (guis > 2)
        {
            for (int i = last_i; cmd[i] != '_'; i++)
            {
                str4 += cmd[i];
                last_i = i + 2;
            }
        }
        if (guis > 3)
        {
            for (int i = last_i; cmd[i] != '_'; i++)
            {
                str5 += cmd[i];
                last_i = i + 2;
            }
        }
        if (guis > 4)
        {
            for (int i = last_i; cmd[i] != '_'; i++)
            {
                str6 += cmd[i];
                last_i = i + 2;
            }
        }
        if (!str1.compare("sd"))
        {
            string current_dir1;
            int barras_cur_dir_folder = 0;
            int barras_cur_dir = 0;
            for (int i = 0; i < current_dir.length(); i++)
            {
                if (current_dir[i] == '/')
                {
                    barras_cur_dir++;
                    barras_cur_dir_folder++;
                }
            }
            if (barras_cur_dir_folder > 1)
            {
                for (int i = 0; i < current_dir.length()-1;i++)
                {
                    current_dir1 += current_dir[i];
                }
                barras_cur_dir_folder;
            }
            else
            {
                for (int i = 0; i < current_dir.length();i++)
                {
                    current_dir1 += current_dir[i];
                }
            }
            bool can_read = false;
            for (int i = 0; i < sysmem.foldernum; i++)
            {
                if (!sysmem.users[sysmem.current_user_id].fof.folders[i].dir.compare(current_dir1))
                {
                    if (sysmem.users[sysmem.current_user_id].fof.folders[i].read == 1 || sysmem.users[sysmem.current_user_id].user_type == 1)
                    {
                        can_read = true;
                    }
                    break;
                }
            }
            if (can_read)
            {
            for (int i = 0; i < sysmem.foldernum; i++)
            {
                barras = 0;
                for (int j = 0; j < sysmem.folders[i].dir.length(); j++)
                {
                    if (sysmem.folders[i].dir[j] == '/')
                    {
                        barras += 1;
                    }
                }
                if (barras == barras_cur_dir_folder)
                {
                    string str3 = "";
                    int a = 0;
                    for (int j = 0; j < barras; j = j)
                    {
                        if (sysmem.folders[i].dir[a] == '/')
                        {
                            j++;
                        }
                        str3 += sysmem.folders[i].dir[a];
                        a++;
                    }
                    if (!str3.compare(current_dir))
                    {
                        cout << "FOLDER   " << sysmem.folders[i].dir << endl;
                    }
                }
            }
            for (int i = 0; i < sysmem.filenum; i++)
            {
                barras = 0;
                for (int j = 0; j < sysmem.files[i].filename.length(); j++)
                {
                    if (sysmem.files[i].filename[j] == '/')
                    {
                        barras += 1;
                    }
                }
                if (barras == barras_cur_dir)
                {
                    string str3 = "";
                    int a = 0;
                    for (int j = 0; j < barras; j = j)
                    {
                        if (sysmem.files[i].filename[a] == '/')
                        {
                            j++;
                        }
                        str3 += sysmem.files[i].filename[a];
                        a++;
                    }
                    if (!str3.compare(current_dir))
                    {
                        cout << "FILE   " << sysmem.files[i].filename << endl;
                    }
                }
            }
            }
            else
            {
                cout << "Error 5: Access Denied: You can't see the content of this folder" << endl;
            }
        }
        else if (!str1.compare("ed"))
        {
            bool exist = false;
            for (int i = 0; i < sysmem.foldernum; i++)
            {
                if (!sysmem.folders[i].dir.compare(string(current_dir + str2)))
                {
                    exist = true;
                    break;
                }
            }
            if (exist)
            {
                string current_dir1 = string(current_dir + str2 + "/");
                current_dir = "";
                current_dir += current_dir1;
                cout << "Changed directory to " << current_dir1 << endl;
            }
            else
            {
                cout << "Error 405: Folder not found: The folder " << str2 << " was not found on this folder" << endl;
            }
        }
        else if (!str1.compare("dpb"))
        {
            string str3 = "";
            int barras_cur_dir = 0;
            for (int i = 0; i < current_dir.length();i++)
            {
                if (current_dir[i] == '/')
                {
                    barras_cur_dir += 1;
                }
            }
            if (barras_cur_dir > 1)
            {
                int a = 0;
                for(int i = 0; i < barras_cur_dir - 1; i = i)
                {
                    str3 += current_dir[a];
                    if (current_dir[a] == '/')
                    {
                        i++;
                    }
                    a++;
                }
                current_dir = str3;
            }
            else
            {
                cout << "Error 3: Can't get back: Can't get back because you already are in base dir" << endl;
            }
        }
        else if (!str1.compare("nd"))
        {
            string current_dir1;
            int barras_cur_dir_folder = 0;
            int barras_cur_dir = 0;
            for (int i = 0; i < current_dir.length(); i++)
            {
                if (current_dir[i] == '/')
                {
                    barras_cur_dir++;
                    barras_cur_dir_folder++;
                }
            }
            if (barras_cur_dir_folder > 1)
            {
                for (int i = 0; i < current_dir.length()-1;i++)
                {
                    current_dir1 += current_dir[i];
                }
                barras_cur_dir_folder--;
            }
            else
            {
                for (int i = 0; i < current_dir.length();i++)
                {
                    current_dir1 += current_dir[i];
                }
            }
            int current_dir_num = 0;
            for (int i = 0; i < sysmem.foldernum; i++)
            {
                if (!sysmem.folders[i].dir.compare(current_dir1))
                {
                    current_dir_num = i;
                    break;
                }
            }
            if ((sysmem.users[sysmem.current_user_id].fof.folders[current_dir_num].write == 2 || sysmem.users[sysmem.current_user_id].fof.folders[current_dir_num].write == 3) || (sysmem.users[sysmem.current_user_id].user_type == 1))
            {
            	if (guis == 2)
            	{
            	if (str2.compare(""))
            	{
                	bool slash = true;
                	for (int i = 0; i < str2.length(); i++)
                	{
                    		if (str2[i] == '/')
                    		{
                        		slash = false;
                    		}
                	}
                	if (slash)
                	{
	       	    		folder *old_folders = new folder[sysmem.foldernum];
        	    		int old_folder_num = sysmem.foldernum;
	            		for (int i = 0; i < sysmem.foldernum; i++)
           	    		{
               	   	 		old_folders[i].dir = sysmem.folders[i].dir;
               	  	 		old_folders[i].property = sysmem.folders[i].property;
               	    	 		old_folders[i].prop_user_id = sysmem.folders[i].prop_user_id;
            	    		}
            	    		sysmem.foldernum++;
           	    		sysmem.folders = new folder[sysmem.foldernum];
            	    		for (int i = 0; i < old_folder_num; i++)
            	    		{
                			sysmem.folders[i].dir = old_folders[i].dir;
                			sysmem.folders[i].property = old_folders[i].property;
                			sysmem.folders[i].prop_user_id = old_folders[i].prop_user_id;
            	    		}
            	    		sysmem.folders[sysmem.foldernum-1].dir = string(current_dir+str2);
            	    		sysmem.folders[sysmem.foldernum-1].property = sysmem.users[sysmem.current_user_id].username;
            	    		sysmem.folders[sysmem.foldernum-1].prop_user_id = sysmem.current_user_id;

            	    		user_folder *old_user_folders = new user_folder[old_folder_num];
            	    		for (int i = 0; i < sysmem.usersnum; i++)
            	    		{
                			for (int j = 0; j < old_folder_num; j++)
                			{
                    				old_user_folders[j].dir = sysmem.users[i].fof.folders[j].dir;
                    				old_user_folders[j].write = sysmem.users[i].fof.folders[j].write;
                    				old_user_folders[j].read = sysmem.users[i].fof.folders[j].read;
                			}
                			sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
                    			for (int j = 0; j < old_folder_num; j++)
                    			{
                    				sysmem.users[i].fof.folders[j].dir = old_user_folders[j].dir;
                    				sysmem.users[i].fof.folders[j].write = old_user_folders[j].write;
                    				sysmem.users[i].fof.folders[j].read = old_user_folders[j].read;
                    		}
               	    		sysmem.users[i].fof.folders[sysmem.foldernum-1].dir = string(current_dir+str2);
                    		if (sysmem.current_user_id == sysmem.users[i].user_id)
                    		{
                    			sysmem.users[i].fof.folders[sysmem.foldernum-1].write = 3;
                    			sysmem.users[i].fof.folders[sysmem.foldernum-1].read = 1;
                    		}
                    		else
                    		{
                    			if (true)
                    			{
                        			sysmem.users[i].fof.folders[sysmem.foldernum-1].write = 0;
                        			sysmem.users[i].fof.folders[sysmem.foldernum-1].read = 0;
                    			}
                    		}
            		}
            		cout << "Directory created successfully" << endl;
            	}
		else
		{
			cout << "Error: Folder name can't contain slashes" << endl;
		}
            }
            else
            {
                cout << "Folder name can't be nothing" << endl;
            }
            }
            else
            {
                cout << "Arguments diferent 2" << endl;
                cout << "Arguments:" << guis << endl;
            }
            }
            else
            {
                cout << "Error 5: Access Denied: You can't add content to this folder" << endl;
            }
        }
        else if (!str1.compare("deld"))
        {
            if (guis == 2)
            {
                if (str2.compare(""))
                {
                    int del_folder_num = 0;
                    bool found = false;
                    string current_dir1 = current_dir + str2;
                    for (int i = 0; i < sysmem.foldernum; i++)
                    {
                        if (!current_dir1.compare(sysmem.folders[i].dir))
                        {
                            found = true;
                            del_folder_num = i;
                            break;
                        }
                    }
                    if (found)
                    {
                        if (sysmem.users[sysmem.current_user_id].fof.folders[del_folder_num].write == 3 || sysmem.users[sysmem.current_user_id].user_type == 1)
                        {
                            string current_dir2 = current_dir1 + "/";
                            barras = 0;
                            int del_dir_barras = 0;
                            bool files_inside = false;
                            for (int i = 0; i < current_dir2.length(); i++)
                            {
                                if (current_dir2[i] == '/')
                                {
                                    del_dir_barras++;
                                }
                            }
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                barras = 0;
                                for (int j = 0; j < sysmem.files[i].filename.length(); j++)
                                {
                                    if (sysmem.files[i].filename[j] == '/')
                                    {
                                        barras++;
                                    }
                                }
                                if (barras == del_dir_barras)
                                {
                                    string dir3 = "";
                                    int a = 0;
                                    for (int j = 0; j < barras; j = j)
                                    {
                                        if (sysmem.files[i].filename[a] == '/')
                                        {
                                            j++;
                                        }
                                        dir3 += sysmem.files[i].filename[a];
                                        a++;
                                    }
                                    if (!dir3.compare(current_dir2))
                                    {
                                        files_inside = true;
                                        break;
                                    }
                                }
                            }
                            if (files_inside == true)
                            {
                                cout << "Can't delete folder: files inside" << endl;
                            }
                            else
                            {
                                del_dir_barras = 0;
                                for (int i = 0; i < current_dir2.length(); i++)
                                {
                                    if (current_dir2[i] == '/')
                                    {
                                        del_dir_barras++;
                                    }
                                }
                                for (int i = 0; i < sysmem.foldernum; i++)
                                {
                                    barras = 0;
                                    for (int j = 0; j < sysmem.folders[i].dir.length(); j++)
                                    {
                                        if (sysmem.folders[i].dir[j] == '/')
                                        {
                                            barras++;
                                        }
                                    }
                                    if (barras == del_dir_barras)
                                    {
                                        string dir3 = "";
                                        int a = 0;
                                        for (int j = 0; j < barras; j = j)
                                        {
                                            if (sysmem.folders[i].dir[a] == '/')
                                            {
                                                j++;
                                            }
                                            dir3 += sysmem.folders[i].dir[a];
                                            a++;
                                        }
                                        if (!dir3.compare(current_dir2))
                                        {
                                            files_inside = true;
                                            break;
                                        }
                                    }
                                }
                                if (files_inside == true)
                                {
                                    cout << "Can't delete folder: folders inside" << endl;
                                }
                                else
                                {
                                    folder * old_folders = new folder[sysmem.foldernum];
                                    int old_folder_num = sysmem.foldernum;
                                    for (int i = 0; i < old_folder_num; i++)
                                    {
                                        old_folders[i].dir = sysmem.folders[i].dir;
                                        old_folders[i].property = sysmem.folders[i].property;
                                        old_folders[i].prop_user_id = sysmem.folders[i].prop_user_id;
                                    }
                                    sysmem.foldernum--;
                                    sysmem.folders = new folder[sysmem.foldernum];
                                    bool rest1 = false;
                                    for (int i = 0; i < old_folder_num; i++)
                                    {
                                        if (rest1 == true)
                                        {
                                            sysmem.folders[i-1].dir = old_folders[i].dir;
                                            sysmem.folders[i-1].property = old_folders[i].property;
                                            sysmem.folders[i-1].prop_user_id = old_folders[i].prop_user_id;
                                        }
                                        else
                                        {
                                            if (i == del_folder_num)
                                            {
                                                rest1 = true;
                                            }
                                            else
                                            {
                                                sysmem.folders[i].dir = old_folders[i].dir;
                                                sysmem.folders[i].property = old_folders[i].property;
                                                sysmem.folders[i].prop_user_id = old_folders[i].prop_user_id;
                                            }
                                        }
                                    }
                                    user_folder *old_user_folder = new user_folder[old_folder_num];
                                    for (int i = 0; i < sysmem.usersnum; i++)
                                    {
                                        for (int j = 0; j < old_folder_num; j++)
                                        {
                                            old_user_folder[j].dir = sysmem.users[i].fof.folders[j].dir;
                                            old_user_folder[j].read = sysmem.users[i].fof.folders[j].read;
                                            old_user_folder[j].write = sysmem.users[i].fof.folders[j].write;
                                        }
                                        sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
                                        rest1 = false;
                                        for (int j = 0; j < old_folder_num; j++)
                                        {
                                            if (rest1 == true)
                                            {
                                                sysmem.users[i].fof.folders[j-1].dir = old_user_folder[j].dir;
                                                sysmem.users[i].fof.folders[j-1].read = old_user_folder[j].read;
                                                sysmem.users[i].fof.folders[j-1].write = old_user_folder[j].write;
                                            }
                                            else
                                            {
                                                if (j == del_folder_num)
                                                {
                                                    rest1 = true;
                                                }
                                                else
                                                {
                                                    sysmem.users[i].fof.folders[j].dir = old_user_folder[j].dir;
                                                    sysmem.users[i].fof.folders[j].read = old_user_folder[j].read;
                                                    sysmem.users[i].fof.folders[j].write = old_user_folder[j].write;
                                                }
                                            }
                                        }
                                    }
                                    cout << "Directory deleted successfully" << endl;
                                }
                            }
                        }
                        else
                        {
                            cout << "You can't delete this folder: Access denied" << endl;
                        }
                    }
                    else
                    {
                        cout << "Folder wasn't found inside this folder" << endl;
                    }
                }
                else
                {
                    cout << "Folder name can't be nothing" << endl;
                }
            }
            else
            {
                cout << "Invalid number of parameters" << endl;
            }
        }
        else if (!str1.compare("sf"))
        {
            string current_file = current_dir + str2;
            bool found = false;
            int current_file_num = 0;
            if (guis == 2)
            {
            if (str2.compare(""))
            {
            for (int i = 0; i < sysmem.filenum; i++)
            {
                if (!sysmem.files[i].filename.compare(current_file))
                {
                    found = true;
                    current_file_num = i;
                    break;
                }
            }
            if (found)
            {
                if (sysmem.users[sysmem.current_user_id].fif.files[current_file_num].read == 1 || sysmem.users[sysmem.current_user_id].user_type == 1)
                {
                    ifstream file(string("file" + sysmem.files[current_file_num].filenum).c_str());
                    string line_buffer;
                    while(getline(file,line_buffer))
                    {
                        cout << line_buffer << endl;
                    }
                }
                else
                {
                    cout << "Error: You can't read this file: Access Denied" << endl;
                }
            }
            else
            {
                cout << "Error: File wasn't found inside that folder" << endl;
            }
            }
            else
            {
                cout << "Error: Filename can't be nothing" << endl;
            }
            }
            else
            {
                cout << "Error: Invalid number of arguments" << endl;
            }
        }
        else if (!str1.compare("delf"))
        {
            if (guis == 2)
            {
                if (str2.compare(""))
                {
                    string current_file = current_dir + str2;
                    bool found = false;
                    int current_filenum = 0;
                    for (int i = 0; i < sysmem.filenum; i++)
                    {
                        if (!current_file.compare(sysmem.files[i].filename))
                        {
                            found = true;
                            current_filenum = i;
                        }
                    }
                    if (found == true)
                    {
                        if (sysmem.users[sysmem.current_user_id].fif.files[current_filenum].write == 2 || sysmem.users[sysmem.current_user_id].user_type == 1)
                        {
                            file *old_files = new file[sysmem.filenum];
                            int old_filenum = sysmem.filenum;
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                old_files[i].filename = sysmem.files[i].filename;
                                old_files[i].filenum = sysmem.files[i].filenum;
                                old_files[i].property = sysmem.files[i].property;
                                old_files[i].user_id = sysmem.files[i].user_id;
                            }
                            sysmem.filenum--;
                            sysmem.files = new file[sysmem.filenum];
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                if (i < current_filenum)
                                {
                                    sysmem.files[i].filename = old_files[i].filename;
                                    sysmem.files[i].filenum = old_files[i].filenum;
                                    sysmem.files[i].property = old_files[i].property;
                                    sysmem.files[i].user_id = old_files[i].user_id;
                                }
                                else
                                {
                                    sysmem.files[i].filename = old_files[i+1].filename;
                                    sysmem.files[i].filenum = std::to_string(i);
                                    sysmem.files[i].property = old_files[i+1].property;
                                    sysmem.files[i].user_id = old_files[i+1].user_id;
                                    ifstream ifile(string("file" + old_files[i+1].filenum).c_str());
                                    ofstream ofile(string("file" + to_string(i)).c_str());
                                    string line_buff;
                                    while(getline(ifile,line_buff))
                                    {
                                        ofile << line_buff << endl;
                                    }
                                }
                            }
                            system(string("del file" + to_string(old_filenum - 1)).c_str());
                            user_file *old_users_files = new user_file[old_filenum];
                            for (int j = 0; j < sysmem.usersnum; j++)
                            {
                                for(int i = 0; i < old_filenum; i++)
                                {
                                    old_users_files[i].filename = sysmem.users[j].fif.files[i].filename;
                                    old_users_files[i].write = sysmem.users[j].fif.files[i].write;
                                    old_users_files[i].read = sysmem.users[j].fif.files[i].read;
                                    old_users_files[i].execute = sysmem.users[j].fif.files[i].execute;
                                }
                                sysmem.users[j].fif.files = new user_file[sysmem.filenum];
                                for (int i = 0; i < sysmem.filenum; i++)
                                {
                                    if (i < current_filenum)
                                    {
                                        sysmem.users[j].fif.files[i].filename = old_users_files[i].filename;
                                        sysmem.users[j].fif.files[i].write = old_users_files[i].write;
                                        sysmem.users[j].fif.files[i].read = old_users_files[i].read;
                                        sysmem.users[j].fif.files[i].execute = old_users_files[i].execute;
                                    }
                                    else
                                    {

                                        sysmem.users[j].fif.files[i].filename = old_users_files[i].filename;
                                        sysmem.users[j].fif.files[i].write = old_users_files[i].write;
                                        sysmem.users[j].fif.files[i].read = old_users_files[i].read;
                                        sysmem.users[j].fif.files[i].execute = old_users_files[i].execute;
                                    }
                                }
                            }
                            cout << "File deleted successfuly" << endl;
                        }
                        else
                        {
                            cout << "Error: You can't delete this file: Access Denied" << endl;
                        }
                    }
                    else
                    {
                        cout << "Error: File not found" << endl;
                    }
                }
                else
                {
                    cout << "Error: Filename can't be nothing" << endl;
                }
            }
            else
            {
                cout << "Error: Invalid number of arguments" << endl;
            }
        }
        else if (!str1.compare("wedit"))
        {
            if (guis == 2)
            {
                if(str2.compare(""))
                {
                    bool found = false;
                    string current_file = current_dir + str2;
                    int current_filenum = 0;
                    for(int i = 0; i < sysmem.filenum; i++)
                    {
                        if (!current_file.compare(sysmem.files[i].filename))
                        {
                            found = true;
                            current_filenum = i;
                            break;
                        }
                    }
                    string filename;
                    bool can_write = false;
                    if (found == true)
                    {
                        if (sysmem.users[sysmem.current_user_id].fif.files[current_filenum].write == 1 || sysmem.users[sysmem.current_user_id].fif.files[current_filenum].write == 2 || sysmem.users[sysmem.current_user_id].user_type == 1)
                        {
                            can_write = true;
                        }
                        filename = sysmem.files[current_filenum].filename;
                    }
                    else
                    {
                        string current_dir1 = "";
                        int barras = 0;
                        for (int i = 0; i < current_file.length(); i++)
                        {
                            if (current_file[i] == '/')
                            {
                                barras++;
                            }
                        }
                        int a = 0;
                        for (int i = 0; i < barras; a++)
                        {
                            if (current_file[a] == '/')
                            {
                                i++;
                                if (i == barras)
                                {
                                    break;
                                }
                            }
                            current_dir1 += current_dir[a];
                        }
                        bool dir_found = false;
                        int dir_num = 0;
                        for (int i = 0; i < sysmem.foldernum; i++)
                        {
                            if (!sysmem.folders[i].dir.compare(current_dir1))
                            {
                                dir_found = true;
                                dir_num = i;
                                break;
                            }
                        }
                        if (dir_found)
                        {
                            if (sysmem.users[sysmem.current_user_id].fof.folders[dir_num].write == 2 || sysmem.users[sysmem.current_user_id].fof.folders[dir_num].write == 3 || sysmem.users[sysmem.current_user_id].user_type == 1)
                            {
                                can_write = true;
                            }
                        }
                        else
                        {
                            cout << "Dir not found" << endl;
                            cout << "Current_dir1:" << current_dir1 << endl;
                            cout << "Barras:" << barras << endl;
                            cout << "Current_file:" << current_file << endl;
                        }
                        filename = str2;
                    }
                    if (can_write == true)
                    {
#if OS == WINDOWS
                        system("cls");
#elif OS == LINUX
			system("clear");
#endif //OS
                        cout << "Filename:" << filename << "\n-------------------------------------" << endl;
                        string nothing,lines[100];
                        getline(cin,nothing);
                        int linesnum = 0;
                        for (int i = 0;i < 100;i++)
                        {
                            getline(cin,lines[i]);
                            if (!lines[i].compare("$quit"))
                            {
                                break;
                            }
                            linesnum++;
                        }
                        if (found == false)
                        {
                            file *old_files = new file[sysmem.filenum];
                            int old_filenum = sysmem.filenum;
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                old_files[i].filename = sysmem.files[i].filename;
                                old_files[i].filenum = sysmem.files[i].filenum;
                                old_files[i].property = sysmem.files[i].property;
                                old_files[i].user_id = sysmem.files[i].user_id;
                            }
                            sysmem.filenum++;
                            sysmem.files = new file[sysmem.filenum];
                            for (int i = 0; i < old_filenum; i++)
                            {
                                sysmem.files[i].filename = old_files[i].filename;
                                sysmem.files[i].filenum = old_files[i].filenum;
                                sysmem.files[i].property = old_files[i].property;
                                sysmem.files[i].user_id = old_files[i].user_id;
                            }
                            sysmem.files[sysmem.filenum-1].filename = current_file;
                            sysmem.files[sysmem.filenum-1].filenum = to_string(sysmem.next_file);
                            sysmem.files[sysmem.filenum-1].property = sysmem.users[sysmem.current_user_id].username;
                            sysmem.files[sysmem.filenum-1].user_id = sysmem.users[sysmem.current_user_id].user_id;
                            user_file *old_user_file = new user_file[old_filenum];
                            for (int j = 0; j < sysmem.usersnum; j++)
                            {
                                for (int i = 0; i < old_filenum; i++)
                                {
                                    old_user_file[i].filename = sysmem.users[j].fif.files[i].filename;
                                    old_user_file[i].write = sysmem.users[j].fif.files[i].write;
                                    old_user_file[i].read = sysmem.users[j].fif.files[i].read;
                                    old_user_file[i].execute = sysmem.users[j].fif.files[i].execute;
                                }
                                sysmem.users[j].fif.files = new user_file[sysmem.filenum];
                                for (int i = 0; i < old_filenum; i++)
                                {
                                    sysmem.users[j].fif.files[i].filename = old_user_file[i].filename;
                                    sysmem.users[j].fif.files[i].write = old_user_file[i].write;
                                    sysmem.users[j].fif.files[i].read = old_user_file[i].read;
                                    sysmem.users[j].fif.files[i].execute = old_user_file[i].execute;
                                }
                                if (j == sysmem.current_user_id)
                                {
                                    sysmem.users[j].fif.files[sysmem.filenum-1].filename = current_file;
                                    sysmem.users[j].fif.files[sysmem.filenum-1].write = 2;
                                    sysmem.users[j].fif.files[sysmem.filenum-1].read = 1;
                                    sysmem.users[j].fif.files[sysmem.filenum-1].execute = 1;
                                }
                                else
                                {
                                    sysmem.users[j].fif.files[old_filenum].filename = current_file;
                                    sysmem.users[j].fif.files[old_filenum].write = 0;
                                    sysmem.users[j].fif.files[old_filenum].read = 0;
                                    sysmem.users[j].fif.files[old_filenum].execute = 0;
                                }
                            }
                            current_filenum = sysmem.filenum-1;
                            sysmem.next_file++;
                        }
                        ofstream ofile(string("file" + sysmem.files[current_filenum].filenum));
                        for (int i = 0; i < linesnum; i++)
                        {
                            ofile << lines[i] << endl;
                        }
                        ofile.close();
                    }
                    else
                    {
                        cout << "Error: You can't write this file: Access Denied" << endl;
                    }
                }
                else
                {
                    cout << "Error: Filename can't be nothing" << endl;
                }
            }
            else
            {
               cout << "Error: Invalid number of arguments" << endl;
            }
        }
        else if (!str1.compare("user"))
        {
                if (str2.compare(""))
                {
                    if (!str2.compare("add"))
                    {
                        // ADD USER
                        if (str4.compare("") && str5.compare("") && sysmem.users[sysmem.current_user_id].user_type == 1)
                        {
                            bool already_exists = false;
                            bool invalid_args = false;
                            for (int i = 0; i < sysmem.usersnum; i++)
                            {
                                if (!str4.compare(sysmem.users[i].username))
                                {
                                    already_exists = true;
                                }
                            }
                            if (guis != 4)
                            {
                                invalid_args = true;
                            }
                            if (already_exists == false && invalid_args == false)
                            {
                                user *old_users = new user[sysmem.usersnum];
                                int old_usersnum = sysmem.usersnum;
                                for (int i = 0; i < sysmem.usersnum; i++)
                                {
                                    old_users[i].folders_file_location = sysmem.users[i].folders_file_location;
                                    old_users[i].files_file_location = sysmem.users[i].files_file_location;
                                    old_users[i].username = sysmem.users[i].username;
                                    old_users[i].user_id = sysmem.users[i].user_id;
                                    old_users[i].user_type = sysmem.users[i].user_type;
                                    old_users[i].md5passwd = sysmem.users[i].md5passwd;
                                    old_users[i].fof.folders = new user_folder[sysmem.foldernum];
                                    old_users[i].fif.files = new user_file[sysmem.filenum];
                                    for (int j = 0; j < sysmem.foldernum; j++)
                                    {
                                        old_users[i].fof.folders[j].dir = sysmem.users[i].fof.folders[j].dir;
                                        old_users[i].fof.folders[j].write = sysmem.users[i].fof.folders[j].write;
                                        old_users[i].fof.folders[j].read = sysmem.users[i].fof.folders[j].read;
                                    }
                                    for (int j = 0; j < sysmem.filenum; j++)
                                    {
                                        old_users[i].fif.files[j].filename = sysmem.users[i].fif.files[j].filename;
                                        old_users[i].fif.files[j].write = sysmem.users[i].fif.files[j].write;
                                        old_users[i].fif.files[j].read = sysmem.users[i].fif.files[j].read;
                                        old_users[i].fif.files[j].execute = sysmem.users[i].fif.files[j].execute;
                                    }
                                }
                                sysmem.usersnum++;
                                sysmem.users = new user[sysmem.usersnum];
                                for (int i = 0; i < old_usersnum; i++)
                                {
                                    sysmem.users[i].folders_file_location = old_users[i].folders_file_location;
                                    sysmem.users[i].files_file_location = old_users[i].files_file_location;
                                    sysmem.users[i].username = old_users[i].username;
                                    sysmem.users[i].user_id = old_users[i].user_id;
                                    sysmem.users[i].user_type = old_users[i].user_type;
                                    sysmem.users[i].md5passwd = old_users[i].md5passwd;
                                    sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
                                    sysmem.users[i].fif.files = new user_file[sysmem.filenum];
                                    for (int j = 0; j < sysmem.foldernum; j++)
                                    {
                                        sysmem.users[i].fof.folders[j].dir = old_users[i].fof.folders[j].dir;
                                        sysmem.users[i].fof.folders[j].write = old_users[i].fof.folders[j].write;
                                        sysmem.users[i].fof.folders[j].read = old_users[i].fof.folders[j].read;
                                    }
                                    for (int j = 0; j < sysmem.filenum; j++)
                                    {
                                        sysmem.users[i].fif.files[j].filename = old_users[i].fif.files[j].filename;
                                        sysmem.users[i].fif.files[j].write = old_users[i].fif.files[j].write;
                                        sysmem.users[i].fif.files[j].read = old_users[i].fif.files[j].read;
                                        sysmem.users[i].fif.files[j].execute = old_users[i].fif.files[j].execute;
                                    }
                                }
                                sysmem.users[sysmem.usersnum-1].folders_file_location = string(str4 + ".fof");
                                sysmem.users[sysmem.usersnum-1].files_file_location = string(str4 + ".fif");
                                sysmem.users[sysmem.usersnum-1].username = str4;
                                sysmem.users[sysmem.usersnum-1].user_id = sysmem.usersnum-1;
                                sysmem.users[sysmem.usersnum-1].user_type = 0;
                                sysmem.users[sysmem.usersnum-1].md5passwd = md5(str5);
                                sysmem.users[sysmem.usersnum-1].fof.folders = new user_folder[sysmem.foldernum];
                                sysmem.users[sysmem.usersnum-1].fif.files = new user_file[sysmem.filenum];
                                for (int j = 0; j < sysmem.foldernum; j++)
                                {
                                    sysmem.users[sysmem.usersnum-1].fof.folders[j].dir = sysmem.folders[j].dir;
                                    sysmem.users[sysmem.usersnum-1].fof.folders[j].write = 0;
                                    sysmem.users[sysmem.usersnum-1].fof.folders[j].read = 0;
                                }
                                for (int j = 0; j < sysmem.filenum; j++)
                                {
                                    sysmem.users[sysmem.usersnum-1].fif.files[j].filename = sysmem.files[j].filename;
                                    sysmem.users[sysmem.usersnum-1].fif.files[j].write = 0;
                                    sysmem.users[sysmem.usersnum-1].fif.files[j].read = 0;
                                    sysmem.users[sysmem.usersnum-1].fif.files[j].execute = 0;
                                }
                                //ADD USER FOLDER
                                folder *old_folders = new folder[sysmem.foldernum];
                                int old_folder_num = sysmem.foldernum;
                                for (int i = 0; i < sysmem.foldernum; i++)
                                {
                                    old_folders[i].dir = sysmem.folders[i].dir;
                                    old_folders[i].property = sysmem.folders[i].property;
                                    old_folders[i].prop_user_id = sysmem.folders[i].prop_user_id;
                                }
                                sysmem.foldernum++;
                                sysmem.folders = new folder[sysmem.foldernum];
                                for (int i = 0; i < old_folder_num; i++)
                                {
                                    sysmem.folders[i].dir = old_folders[i].dir;
                                    sysmem.folders[i].property = old_folders[i].property;
                                    sysmem.folders[i].prop_user_id = old_folders[i].prop_user_id;
                                }
                                sysmem.folders[sysmem.foldernum-1].dir = string("/"+str4);
                                sysmem.folders[sysmem.foldernum-1].property = sysmem.users[0].username;
                                sysmem.folders[sysmem.foldernum-1].prop_user_id = 0;

                                user_folder *old_user_folders = new user_folder[old_folder_num];
                                for (int i = 0; i < sysmem.usersnum; i++)
                                {
                                    for (int j = 0; j < old_folder_num; j++)
                                    {
                                        old_user_folders[j].dir = sysmem.users[i].fof.folders[j].dir;
                                        old_user_folders[j].write = sysmem.users[i].fof.folders[j].write;
                                        old_user_folders[j].read = sysmem.users[i].fof.folders[j].read;
                                    }
                                    sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
                                    for (int j = 0; j < old_folder_num; j++)
                                    {
                                        sysmem.users[i].fof.folders[j].dir = old_user_folders[j].dir;
                                        sysmem.users[i].fof.folders[j].write = old_user_folders[j].write;
                                        sysmem.users[i].fof.folders[j].read = old_user_folders[j].read;
                                    }
                                    sysmem.users[i].fof.folders[sysmem.foldernum-1].dir = string("/"+str4);
                                    if (sysmem.usersnum-1 == sysmem.users[i].user_id)
                                    {
                                        sysmem.users[i].fof.folders[sysmem.foldernum-1].write = 2;
                                        sysmem.users[i].fof.folders[sysmem.foldernum-1].read = 1;
                                    }
                                    else
                                    {
                                        if (true)
                                        {
                                            sysmem.users[i].fof.folders[sysmem.foldernum-1].write = 0;
                                            sysmem.users[i].fof.folders[sysmem.foldernum-1].read = 0;
                                        }
                                    }
                                }
                                cout << "User created successfully" << endl;
                            }
                            else
                            {
                                if (already_exists == true)
                                {
                                    cout << "Error: User already exists" << endl;
                                }
                                else
                                {
                                    cout << "Error: Invalid number of arguments" << endl;
                                }
                            }
                        }
                        else
                        {
                            if (!str4.compare("") || !str5.compare(""))
                            {
                                cout << "Error: Username or password can't be nothing" << endl;
                            }
                            else
                            {
                                cout << "Error: You can't create users: Access Denied" << endl;
                            }
                        }
                    }
                    else if (!str2.compare("delete"))
                    {
                        if (guis == 3)
                        {
                            if (str4.compare(""))
                            {
                                int current_usrnum = 0;
                                bool found = false;
                                for (int i = 0; i < sysmem.usersnum; i++)
                                {
                                    if (!str4.compare(sysmem.users[i].username))
                                    {
                                        found = true;
                                        current_usrnum = i;
                                        break;
                                    }
                                }
                                if (((sysmem.users[sysmem.current_user_id].user_type == 1 && sysmem.users[current_usrnum].user_type == 0) || current_usrnum == sysmem.current_user_id))
                                {
                                    user *old_users = new user[sysmem.usersnum];
                                    int old_usersnum = sysmem.usersnum;
                                    for (int i = 0; i < sysmem.usersnum; i++)
                                    {
                                        old_users[i].username = sysmem.users[i].username;
                                        old_users[i].md5passwd = sysmem.users[i].md5passwd;
                                        old_users[i].user_id = i;
                                        old_users[i].user_type = sysmem.users[i].user_type;
                                        old_users[i].folders_file_location = sysmem.users[i].folders_file_location;
                                        old_users[i].files_file_location = sysmem.users[i].files_file_location;
                                        old_users[i].fof.folders = new user_folder[sysmem.foldernum];
                                        old_users[i].fif.files = new user_file[sysmem.filenum];
                                        for (int j = 0; j < sysmem.foldernum; j++)
                                        {
                                            old_users[i].fof.folders[j].dir = sysmem.users[i].fof.folders[j].dir;
                                            old_users[i].fof.folders[j].write = sysmem.users[i].fof.folders[j].write;
                                            old_users[i].fof.folders[j].read = sysmem.users[i].fof.folders[j].read;
                                        }
                                        for (int j = 0; j < sysmem.filenum; j++)
                                        {
                                            old_users[i].fif.files[j].filename = sysmem.users[i].fif.files[j].filename;
                                            old_users[i].fif.files[j].write = sysmem.users[i].fif.files[j].write;
                                            old_users[i].fif.files[j].read = sysmem.users[i].fif.files[j].read;
                                            old_users[i].fif.files[j].execute = sysmem.users[i].fif.files[j].execute;
                                        }
                                    }
                                    sysmem.usersnum--;
                                    sysmem.users = new user[sysmem.usersnum];
                                    for (int i = 0; i < sysmem.usersnum; i++)
                                    {
                                        if (i < current_usrnum)
                                        {
                                            sysmem.users[i].username = old_users[i].username;
                                            sysmem.users[i].md5passwd = old_users[i].md5passwd;
                                            sysmem.users[i].user_id = i;
                                            sysmem.users[i].user_type = old_users[i].user_type;
                                            sysmem.users[i].folders_file_location = old_users[i].folders_file_location;
                                            sysmem.users[i].files_file_location = old_users[i].files_file_location;
                                            sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
                                            sysmem.users[i].fif.files = new user_file[sysmem.foldernum];
                                            for (int j = 0; j < sysmem.foldernum; j++)
                                            {
                                                sysmem.users[i].fof.folders[j].dir = old_users[i].fof.folders[j].dir;
                                                sysmem.users[i].fof.folders[j].write = old_users[i].fof.folders[j].write;
                                                sysmem.users[i].fof.folders[j].read = old_users[i].fof.folders[j].read;
                                            }
                                            for (int j = 0; j < sysmem.filenum; j++)
                                            {
                                                sysmem.users[i].fif.files[j].filename = old_users[i].fif.files[j].filename;
                                                sysmem.users[i].fif.files[j].write = old_users[i].fif.files[j].write;
                                                sysmem.users[i].fif.files[j].read = old_users[i].fif.files[j].read;
                                                sysmem.users[i].fif.files[j].execute = old_users[i].fif.files[j].execute;
                                            }
                                        }
                                        else
                                        {
                                            sysmem.users[i].username = old_users[i+1].username;
                                            sysmem.users[i].md5passwd = old_users[i+1].md5passwd;
                                            sysmem.users[i].user_id = i;
                                            sysmem.users[i].user_type = old_users[i+1].user_type;
                                            sysmem.users[i].folders_file_location = old_users[i+1].folders_file_location;
                                            sysmem.users[i].files_file_location = old_users[i+1].files_file_location;
                                            sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
                                            sysmem.users[i].fif.files = new user_file[sysmem.foldernum];
                                            for (int j = 0; j < sysmem.foldernum; j++)
                                            {
                                                sysmem.users[i].fof.folders[j].dir = old_users[i+1].fof.folders[j].dir;
                                                sysmem.users[i].fof.folders[j].write = old_users[i+1].fof.folders[j].write;
                                                sysmem.users[i].fof.folders[j].read = old_users[i+1].fof.folders[j].read;
                                            }
                                            for (int j = 0; j < sysmem.filenum; j++)
                                            {
                                                sysmem.users[i].fif.files[j].filename = old_users[i+1].fif.files[j].filename;
                                                sysmem.users[i].fif.files[j].write = old_users[i+1].fif.files[j].write;
                                                sysmem.users[i].fif.files[j].read = old_users[i+1].fif.files[j].read;
                                                sysmem.users[i].fif.files[j].execute = old_users[i+1].fif.files[j].execute;
                                            }
                                        }
                                    }
                                    cout << "User deleted successfully" << endl;
                                    if (current_usrnum == sysmem.current_user_id)
                                    {
                                        save();
                                        return;
                                    }
                                }
                                else
                                {
                                    cout << "Error: You can't delete this user: Access Denied" << endl;
                                }
                            }
                            else
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                        }
                        else
                        {
                            cout << "Error: Invalid number of arguments" << endl;
                        }
                    }
                    else if (!str2.compare("chpwd"))
                    {
                        if (guis == 3)
                        {
                            if (str4.compare(""))
                            {
                                int current_usrnum;
                                bool found = false;
                                for (int i = 0; i < sysmem.usersnum; i++)
                                {
                                    if (!str4.compare(sysmem.users[i].username))
                                    {
                                        found = true;
                                        current_usrnum = i;
                                        break;
                                    }
                                }
                                if (found == true)
                                {
                                    if ((sysmem.users[sysmem.current_user_id].user_type == 1 && sysmem.users[current_usrnum].user_type == 0) || current_usrnum == sysmem.current_user_id)
                                    {
                                        string new_pwd,new_pwd_check;
                                        cout << "New password:";
                                        cin >> new_pwd;
                                        cout << "Repeat new password:";
                                        cin >> new_pwd_check;
                                        if (!new_pwd.compare(new_pwd_check))
                                        {
                                            sysmem.users[current_usrnum].md5passwd = new_pwd;
                                            cout << "Password change correctly" << endl;
                                        }
                                        else
                                        {
                                            cout << "Error: Passwords don't match" << endl;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Error: You can't change the password of this user: Access Denied" << endl;
                                    }
                                }
                                else
                                {
                                    cout << "Error: User not found" << endl;
                                }
                            }
                            else
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                        }
                        else
                        {
                            cout << "Error: Invalid number of arguments" << endl;
                        }
                    }
                    else if (!str2.compare("user-type"))
                    {
                        if (guis == 3)
                        {
                            if (str4.compare(""))
                            {
                                bool found = false;
                                int current_usrnum;
                                for (int i = 0; i < sysmem.usersnum; i++)
                                {
                                    if (!str4.compare(sysmem.users[i].username))
                                    {
                                        found = true;
                                        current_usrnum = i;
                                        break;
                                    }
                                }
                                if (sysmem.users[sysmem.current_user_id].user_type == 1 && (sysmem.users[current_usrnum].user_type == 0 || sysmem.current_user_id == current_usrnum))
                                {
                                    if (sysmem.users[current_usrnum].user_type == 0)
                                    {
                                        sysmem.users[current_usrnum].user_type = 1;
                                    }
                                    else
                                    {
                                        sysmem.users[current_usrnum].user_type = 0;
                                    }
                                    cout << "User type changed successfully" << endl;
                                }
                                else
                                {
                                    cout << "Error: You can't change user types: Access Denied" << endl;
                                }
                            }
                            else
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                        }
                        else
                        {
                            cout << "Error: Invalid number of arguments" << endl;
                        }
                    }
                    else if (!str2.compare("list"))
                    {
                        for (int i = 0; i < sysmem.usersnum; i++)
                        {
                            cout << "User_id: " << sysmem.users[i].user_id << " " << sysmem.users[i].username << " User-type: " << sysmem.users[i].user_type << endl;
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid operation" << endl;
                    }
                }
                else
                {
                    cout << "Error: Operation can't be nothing" << endl;
                }
        }
        else if (!str1.compare("dp"))
        {
            if (str2.compare(""))
            {
                if (!str2.compare("change"))
                {
                    if (guis == 5)
                    {
                        if (str4.compare("") && str5.compare("") && str6.compare(""))
                        {
                            bool user_found = false;
                            int current_usernum;
                            string current_dir1 = current_dir + str5;
                            bool dir_found = false;
                            int current_dirnum;
                            for (int i = 0; i < sysmem.usersnum; i++)
                            {
                                if (!sysmem.users[i].username.compare(str4))
                                {
                                    user_found = true;
                                    current_usernum = i;
                                    break;
                                }
                            }
                            for (int i = 0; i < sysmem.foldernum; i++)
                            {
                                if (!sysmem.folders[i].dir.compare(current_dir1))
                                {
                                    dir_found = true;
                                    current_dirnum = i;
                                    break;
                                }
                            }
                            if (user_found == true && dir_found == true)
                            {
                                //SECURITY
                                if ((sysmem.users[sysmem.current_user_id].user_type == 1 && sysmem.users[sysmem.folders[current_dirnum].prop_user_id].user_type == 0) || sysmem.current_user_id == sysmem.folders[current_dirnum].prop_user_id)
                                {
                                    int permissions = stoi(str6,nullptr,10);
                                    if (true)
                                    {
                                        int new_read = permissions % 10;
                                        int new_write = ((permissions - (permissions % 10)) / 10) % 10;
                                        if (new_write == 0 || new_write == 2 || new_write == 3)
                                        {
                                            sysmem.users[current_usernum].fof.folders[current_dirnum].write = new_write;
                                        }
                                        else
                                        {
                                            cout << "Error: New Write not recognited" << endl;
                                            cout << "NEW_WRITE_VALUE: " << new_write << endl;
                                        }
                                        if (new_read == 0 || new_read == 1)
                                        {
                                            sysmem.users[current_usernum].fof.folders[current_dirnum].read = new_read;
                                        }
                                        else
                                        {
                                            cout << "Error: New Read not recognited" << endl;
                                            cout << "NEW_READ_VALUE: " << new_read << endl;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Error: Invalid permissions" << endl;
                                    }
                                }
                                else
                                {
                                    cout << "Error: You can't change the permissions of this folder: Access Denied" << endl;
                                }
                            }
                            else
                            {
                                if (user_found == false)
                                {
                                    cout << "Error: Username not found" << endl;
                                }
                                if (dir_found == false)
                                {
                                    cout << "Error: Folder not found" << endl;
                                }
                            }
                        }
                        else
                        {
                            if (!str4.compare(""))
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                            if (!str5.compare(""))
                            {
                                cout << "Error: Folder can't be nothing" << endl;
                            }
                            if (!str6.compare(""))
                            {
                                cout << "Error: Permissions can't be nothing" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid number of arguments" << endl;
                    }
                }
                else if (!str2.compare("show"))
                {
                    if (guis == 4)
                    {
                        if (str4.compare("") && str5.compare(""))
                        {
                            int current_usernum;
                            bool user_found = false;
                            string current_dir1 = current_dir + str5;
                            int current_foldernum;
                            bool folder_found = false;
                            for (int i = 0; i < sysmem.usersnum; i++)
                            {
                                if (!sysmem.users[i].username.compare(str4))
                                {
                                    user_found = true;
                                    current_usernum = i;
                                    break;
                                }
                            }
                            for (int i = 0; i < sysmem.foldernum; i++)
                            {
                                if (!sysmem.folders[i].dir.compare(current_dir1))
                                {
                                    current_foldernum = i;
                                    folder_found = true;
                                    break;
                                }
                            }
                            if (user_found == true && folder_found == true)
                            {
                                cout << "Folder: " << current_dir1 << " User: " << str4 << endl;
                                cout << "Write: " << sysmem.users[current_usernum].fof.folders[current_foldernum].write << endl;
                                cout << "Read: " << sysmem.users[current_usernum].fof.folders[current_foldernum].read << endl;
                            }
                            else
                            {
                                if (user_found == false)
                                {
                                    cout << "Error: User not found" << endl;
                                }
                                if (folder_found == false)
                                {
                                    cout << "Error: Folder not found" << endl;
                                }
                            }
                        }
                        else
                        {
                            if (!str4.compare(""))
                            {
                                cout << "Error: Folder name can't be nothing" << endl;
                            }
                            if (!str5.compare(""))
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid number of arguments" << endl;
                    }
                }
                else if (!str2.compare("property"))
                {
                    if (guis == 3)
                    {
                        if (str4.compare(""))
                        {
                            bool folder_found = false;
                            string current_dir1 = current_dir + str4;
                            int current_foldernum;
                            for (int i = 0; i < sysmem.foldernum; i++)
                            {
                                if (!sysmem.folders[i].dir.compare(current_dir1))
                                {
                                    folder_found = true;
                                    current_foldernum = i;
                                    break;
                                }
                            }
                            if (folder_found)
                            {
                                cout << "Property: " << sysmem.folders[current_foldernum].property << endl;
                            }
                            else
                            {
                                cout << "Error: Folder not found" << endl;
                            }
                        }
                        else
                        {
                            cout << "Error: Foldername can't be nothing" << endl;
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid number of arguments" << endl;
                    }
                }
                else
                {
                    cout << "Error: Invalid operation" << endl;
                }
            }
            else
            {
                cout << "Error: Operation can't be nothing" << endl;
            }
        }
        else if (!str1.compare("fp"))
        {
            if (str2.compare(""))
            {
                if (!str2.compare("change"))
                {
                    if (guis == 5)
                    {
                        if (str4.compare("") && str5.compare("") && str6.compare(""))
                        {
                            bool user_found = false;
                            int current_usernum;
                            bool file_found = false;
                            int current_filenum;
                            string current_file = current_dir + str5;
                            for (int i = 0; i < sysmem.usersnum; i++)
                            {
                                if (!sysmem.users[i].username.compare(str4))
                                {
                                    user_found = true;
                                    current_usernum = i;
                                    break;
                                }
                            }
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                if (!sysmem.files[i].filename.compare(current_file))
                                {
                                    file_found = true;
                                    current_filenum = i;
                                    break;
                                }
                            }
                            if (user_found == true && file_found == true)
                            {
                                if ((sysmem.users[sysmem.current_user_id].user_type == 1 && sysmem.users[sysmem.files[current_filenum].user_id].user_type == 0) || sysmem.files[current_filenum].user_id == sysmem.current_user_id)
                                {
                                    int permissions = stoi(str6,nullptr,10);
                                    int new_read = permissions % 10;
                                    int new_write = (permissions - (permissions % 10)) / 10;
                                    if (new_write == 0 || new_write == 1 || new_write == 2)
                                    {
                                        sysmem.users[current_usernum].fif.files[current_filenum].write = new_write;
                                    }
                                    else
                                    {
                                        cout << "Error: New Write not recognited" << endl;
                                        cout << "NEW_WRITE_VALUE: " << new_write << endl;
                                    }
                                    if (new_read == 0 || new_read == 1)
                                    {
                                        sysmem.users[current_usernum].fif.files[current_filenum].read = new_read;
                                    }
                                }
                                else
                                {
                                    cout << "Error: You can't change the permissions of this file: Access Denied" << endl;
                                }
                            }
                            else
                            {
                                if (user_found == false)
                                {
                                    cout << "Error: User not found" << endl;
                                }
                                if (file_found == false)
                                {
                                    cout << "Error: File not found" << endl;
                                }
                            }
                        }
                        else
                        {
                            if (!str4.compare(""))
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                            if (!str5.compare(""))
                            {
                                cout << "Error: Filename can't be nothing" << endl;
                            }
                            if (!str6.compare(""))
                            {
                                cout << "Error: Permissions can't be nothing" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid number of arguments" << endl;
                    }
                }
                else if (!str2.compare("show"))
                {
                    if (guis == 4)
                    {
                        if (str4.compare("") && str5.compare(""))
                        {
                            bool user_found = false;
                            int current_usernum;
                            bool file_found = false;
                            int current_filenum;
                            string current_file = current_dir + str5;
                            for (int i = 0; i < sysmem.usersnum; i++)
                            {
                                if (!sysmem.users[i].username.compare(str4))
                                {
                                    user_found = true;
                                    current_usernum = i;
                                    break;
                                }
                            }
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                if (!sysmem.files[i].filename.compare(current_file))
                                {
                                    file_found = true;
                                    current_filenum = i;
                                    break;
                                }
                            }
                            if (user_found == true && file_found == true)
                            {
                                cout << "File: " << current_file << " User: " << str4 << endl;
                                cout << "Write: " << sysmem.users[current_usernum].fif.files[current_filenum].write << endl;
                                cout << "Read: " << sysmem.users[current_usernum].fif.files[current_filenum].read << endl;
                            }
                            else
                            {
                                if (user_found == false)
                                {
                                    cout << "Error: Username not found" << endl;
                                }
                                if (file_found == false)
                                {
                                    cout << "Error: File not found" << endl;
                                }
                            }
                        }
                        else
                        {
                            if (!str4.compare(""))
                            {
                                cout << "Error: Username can't be nothing" << endl;
                            }
                            if (str5.compare(""))
                            {
                                cout << "Error: Filename can't be nothing" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid number of arguments" << endl;
                    }
                }
                else if (!str2.compare("property"))
                {
                    if (guis == 3)
                    {
                        if (str4.compare(""))
                        {
                            bool file_found = false;
                            int current_filenum;
                            string current_file = current_dir + str4;
                            for (int i = 0; i < sysmem.filenum; i++)
                            {
                                if (!sysmem.files[i].filename.compare(current_file))
                                {
                                    file_found = true;
                                    current_filenum = i;
                                    break;
                                }
                            }
                            if (file_found)
                            {
                                cout << "Property: " << sysmem.files[current_filenum].property << endl;
                            }
                            else
                            {
                                cout << "Error: File not found" << endl;
                            }
                        }
                        else
                        {
                            cout << "Error: Filename can't be nothing" << endl;
                        }
                    }
                    else
                    {
                        cout << "Error: Invalid number of arguments" << endl;
                    }
                }
                else
                {
                    cout << "Error: Invalid operation" << endl;
                }
            }
            else
            {
                cout << "Error: Operation can't be nothing" << endl;
            }
        }
	else if (!str1.compare("dcp"))
	{
		bool str2_slash_start = false;
		bool str4_slash_start = false;
		if (guis == 3)
		{
			if (str2[0] == '/')
			{
				str2_slash_start = true;
			}
			if (str4[0] == '/')
			{
				str4_slash_start = true;
			}
		}
		if (guis == 3 && str2.compare("") && str4.compare("") && str2_slash_start == true && str4_slash_start == true)
		{
			string origin_slashesout;
			bool origin_can_read = false;
			bool origin_found = false;
			int origin_num, origin_slashes = 0;
			bool destination_found = false;
			bool destination_folder_found = false;
			int destination_folder_num, destination_slashes = 0;
			bool destination_folder_can_write = false;
			bool origin_files = false, origin_folders = false;
			string destination = str4;
			string destination_folder;
			for (int i = 0; i < sysmem.foldernum; i++)
			{
				if (!sysmem.folders[i].dir.compare(str2))
				{
					origin_num = i;
					origin_found = true;
					break;
				}
			}
			for (int i = 0; i < str2.length(); i++)
			{
				if (str2[i] == '/')
				{
					origin_slashes++;
				}
			}
			//CHECK NO FOLDERS INSIDE ORIGIN
			string check_inside;
			for (int i = 0; i < sysmem.foldernum; i++)
			{
				check_inside = "";
				if (i != origin_num)
				{
					for (int dir_pos = 0, slashes = 0; dir_pos < sysmem.folders[i].dir.length(); dir_pos++)
					{
						if (sysmem.folders[i].dir[dir_pos] == '/')
						{
							slashes++;
							if (slashes == origin_slashes+1)
							{
								break;
							}
						}
						check_inside += sysmem.folders[i].dir[dir_pos];
					}
					if (!str2.compare(check_inside))
					{
						origin_folders = true;
						break;
					}
				}
			}
			for (int i = 0; i < sysmem.filenum; i++)
			{
				check_inside = "";
				for (int filename_pos = 0, slashes = 0; filename_pos < sysmem.files[i].filename.length(); filename_pos++)
				{
					if (sysmem.files[i].filename[filename_pos] == '/')
					{
						slashes++;
						if (slashes == origin_slashes+1)
						{
							break;
						}
					}
					check_inside += sysmem.files[i].filename[filename_pos];
				}
				if (!str2.compare(check_inside))
				{
					origin_files = true;
				}
			}
			for (int slashes_passed = 0, origin_pos = 0; origin_pos < str2.length(); origin_pos++)
			{
				if (slashes_passed == origin_slashes)
				{
					origin_slashesout += str2[origin_pos];
				}
				if (str2[origin_pos] == '/')
				{
					slashes_passed++;
				}
			}
			if (origin_found == true && origin_folders == false && origin_files == false)
			{
				//Security
				if (sysmem.users[sysmem.current_user_id].fof.folders[origin_num].read == 1 || (sysmem.users[sysmem.current_user_id].user_type == 1 && sysmem.users[sysmem.folders[origin_num].prop_user_id].user_type == 0))
				{
					origin_can_read = true;
				}
				if (origin_can_read == true)
				{
					//DESTINATIONS_CHECK
					if (str4[str4.length()-1] == '/')
					{
						destination += origin_slashesout;
					}
					for (int i = 0 ; i < sysmem.foldernum; i++)
					{
						if (!sysmem.folders[i].dir.compare(destination))
						{
							destination_found = true;
							break;
						}
					}
					if (destination_found == false)
					{
						for (int i = 0; i < destination.length(); i++)
						{
							if (destination[i] == '/')
							{
								destination_slashes++;
							}
						}
						for (int slashes = 0, destination_pos = 0; destination_pos < destination.length(); destination_pos++)
						{
							if (destination[destination_pos] == '/')
							{
								slashes++;
								if (slashes == destination_slashes)
								{
									break;
								}
							}
							destination_folder += destination[destination_pos];
						}
						for (int i = 0; i < sysmem.foldernum; i++)
						{
							if (!sysmem.folders[i].dir.compare(destination_folder))
							{
								destination_folder_found = true;
								destination_folder_num = i;
								break;
							}
						}
						if (destination_folder_found == true)
						{
							if ((sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 2 || sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 3) || (sysmem.users[sysmem.current_user_id].user_type == 1))
							{
								destination_folder_can_write = true;
							}
							if (destination_folder_can_write == true)
							{
								folder *old_folders;
								user_folder *old_userfolders;
								old_folders = new folder[sysmem.foldernum];
								old_userfolders = new user_folder[sysmem.foldernum];
								int old_foldernum = sysmem.foldernum;
								//OLD_COPY
								for (int i = 0; i < old_foldernum; i++)
								{
									old_folders[i].dir = sysmem.folders[i].dir;
									old_folders[i].property = sysmem.folders[i].property;
									old_folders[i].prop_user_id = sysmem.folders[i].prop_user_id;
								}
								//INCREASE ONE FOLDERNUM
								sysmem.foldernum++;
								sysmem.folders = new folder[sysmem.foldernum];
								//RECOPY_BACK
								for (int i = 0; i < old_foldernum; i++)
								{
									sysmem.folders[i].dir = old_folders[i].dir;
									sysmem.folders[i].property = old_folders[i].property;
									sysmem.folders[i].prop_user_id = old_folders[i].prop_user_id;
								}
								//ADD NEW FOLDER
								sysmem.folders[sysmem.foldernum-1].dir = destination;
								sysmem.folders[sysmem.foldernum-1].property = sysmem.users[sysmem.current_user_id].username;
								sysmem.folders[sysmem.foldernum-1].prop_user_id = sysmem.current_user_id;
								//USER_FOLDER
								for (int i = 0; i < sysmem.usersnum; i++)
								{
									for (int j = 0; j < old_foldernum; j++)
									{
										old_userfolders[j].dir = sysmem.users[i].fof.folders[j].dir;
										old_userfolders[j].write = sysmem.users[i].fof.folders[j].write;
										old_userfolders[j].read = sysmem.users[i].fof.folders[j].read;
									}
									sysmem.users[i].fof.folders = new user_folder[sysmem.foldernum];
									for (int j = 0; j < old_foldernum; j++)
									{
										sysmem.users[i].fof.folders[j].dir = old_userfolders[j].dir;
										sysmem.users[i].fof.folders[j].write = old_userfolders[j].write;
										sysmem.users[i].fof.folders[j].read = old_userfolders[j].read;
									}
									sysmem.users[i].fof.folders[sysmem.foldernum-1].dir = destination;
									sysmem.users[i].fof.folders[sysmem.foldernum-1].write = sysmem.users[i].fof.folders[origin_num].write;
									sysmem.users[i].fof.folders[sysmem.foldernum-1].read = sysmem.users[i].fof.folders[origin_num].read;
								}
								cout << "Copied successfuly" << endl;
							}
							else
							{
								cout << "Error: You can't copy to destination: Access Denied" << endl;
							}
						}
						else
						{
							cout << "Error: Destination not found" << endl;
						}
					}
					else
					{
						cout << "Error: Destination already exists" << endl;
					}
				}
				else
				{
					cout << "Error: You can't copy this folder: Access Denied" << endl;
				}
			}
			else
			{
				if (origin_found == false)
				{
					cout << "Error: Origin folder not found" << endl;
				}
				if (origin_folders == true)
				{
					cout << "Error: Folders inside origin" << endl;
				}
				if (origin_files == true)
				{
					cout << "Error: Files inside origin" << endl;
				}
			}
		}
		else
		{
			if (guis != 3)
			{
				cout << "Error: Invalid number of arguments" << endl;
			}
			else
			{
				if (!str2.compare(""))
				{
					cout << "Error: Origin can't be nothing" << endl;
				}
				if (!str4.compare(""))
				{
					cout << "Error: Destination can't be nothing" << endl;
				}
				if (str2.compare("") && str2_slash_start == false)
				{
					cout << "Error: " << str2 << " isn't a valid origin absolute path" << endl;
				}
				if (str4.compare("") && str4_slash_start == false)
				{
					cout << "Error: " << str4 << " isn't a valid destination absolute path" << endl;
				}
			}
		}
	}
	else if (!str1.compare("fcp"))
	{
		bool str2_slash_start = false;
		bool str4_slash_start = false;
		if (guis == 3)
		{
			if (str2[0] == '/')
			{
				str2_slash_start = true;
			}
			if (str4[0] == '/')
			{
				str4_slash_start = true;
			}
		}
		if (guis == 3 && str2.compare("") && str4.compare("") && str2_slash_start == true && str4_slash_start == true)
		{
			string origin_slashesout;
			bool origin_found = false;
			bool origin_can_read = false;
			int origin_num, origin_slashes = 0;
			bool destination_found = false;
			bool destination_folder_found = false;
			int destination_folder_num;
			bool destination_folder_can_write = false;
			string destination = str4, destination_folder;
			int destination_slashes = 0;
			for (int i = 0; i < sysmem.filenum; i++)
			{
				if (!str2.compare(sysmem.files[i].filename))
				{
					origin_found = true;
					origin_num = i;
					break;
				}
			}
			for (int i = 0; i < str2.length(); i++)
			{
				if (str2[i] == '/')
				{
					origin_slashes++;
				}
			}
			for (int slashes = 0, origin_pos = 0; origin_pos < str2.length(); origin_pos++)
			{
				if (slashes == origin_slashes)
				{
					origin_slashesout += str2[origin_pos];
				}
				if (str2[origin_pos] == '/')
				{
					slashes++;
				}
			}
			if (origin_found == true)
			{
				//DESTINATIONS_CHECKS
				if (destination[destination.length()-1] == '/')
				{
					destination += origin_slashesout;
				}
				for (int i = 0; i < sysmem.filenum; i++)
				{
					if (!sysmem.files[i].filename.compare(destination))
					{
						destination_found = true;
						break;
					}
				}
				if (destination_found == false)
				{
					//DESTINATION_FOLDER
					for (int i = 0; i < destination.length(); i++)
					{
						if (destination[i] == '/')
						{
							destination_slashes++;
						}
					}
					for (int slashes = 0, destination_pos = 0; destination_pos < destination.length(); destination_pos++)
					{
						if (destination[destination_pos] == '/')
						{
							slashes++;
							if (slashes == destination_slashes)
							{
								break;
							}
						}
						destination_folder += destination[destination_pos];
					}
					for (int i = 0; i < sysmem.foldernum; i++)
					{
						if (!sysmem.folders[i].dir.compare(destination_folder))
						{
							destination_folder_found = true;
							destination_folder_num = i;
							break;
						}
					}
					if (destination_folder_found == true)
					{
						if (sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 2 || sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 3 || sysmem.users[sysmem.current_user_id].user_type == 1)
						{
							destination_folder_can_write = true;
						}
						if (destination_folder_can_write == true)
						{
							if (sysmem.users[sysmem.current_user_id].fif.files[origin_num].read == 1 || sysmem.users[sysmem.current_user_id].user_type == 1)
							{
								file *old_files = new file[sysmem.filenum];
								user_file *old_userfiles = new user_file[sysmem.filenum];
								int old_filenum = sysmem.filenum;
								for (int i = 0; i < old_filenum; i++)
								{
									old_files[i].filename = sysmem.files[i].filename;
									old_files[i].property = sysmem.files[i].property;
									old_files[i].user_id = sysmem.files[i].user_id;
									old_files[i].filenum = sysmem.files[i].filenum;
								}
								sysmem.filenum++;
								sysmem.files = new file[sysmem.filenum];
								for (int i = 0; i < old_filenum; i++)
								{
									sysmem.files[i].filename = old_files[i].filename;
									sysmem.files[i].property = old_files[i].property;
									sysmem.files[i].user_id = old_files[i].user_id;
									sysmem.files[i].filenum = old_files[i].filenum;
								}
								sysmem.files[sysmem.filenum-1].filename = destination;
								sysmem.files[sysmem.filenum-1].property = sysmem.users[sysmem.current_user_id].username;
								sysmem.files[sysmem.filenum-1].user_id = sysmem.current_user_id;
								sysmem.files[sysmem.filenum-1].filenum = to_string(sysmem.next_file);
								sysmem.next_file++;
								//FILE READ ORIGINAL && WRITE NEW
								ifstream origin_file(string("file"+sysmem.files[origin_num].filenum).c_str());
								ofstream destination_file(string("file"+sysmem.files[sysmem.filenum-1].filenum).c_str());
								string line_buffer;
    								while (getline(origin_file,line_buffer))
    								{
        								destination_file << line_buffer << endl;
    								}
    								//USER
    								for (int i = 0; i < sysmem.usersnum; i++)
    								{
    									for (int j = 0; j < old_filenum; j++)
    									{
    										old_userfiles[j].filename = sysmem.users[i].fif.files[j].filename;
    										old_userfiles[j].write = sysmem.users[i].fif.files[j].write;
    										old_userfiles[j].read = sysmem.users[i].fif.files[j].read;
    										old_userfiles[j].execute = sysmem.users[i].fif.files[j].execute;
    									}
    									sysmem.users[i].fif.files = new user_file[sysmem.filenum];
    									for (int j = 0; j < old_filenum; j++)
    									{
    										sysmem.users[i].fif.files[j].filename = old_userfiles[j].filename;
    										sysmem.users[i].fif.files[j].write = old_userfiles[j].write;
    										sysmem.users[i].fif.files[j].read = old_userfiles[j].read;
    										sysmem.users[i].fif.files[j].execute = old_userfiles[j].execute;
    									}
    									sysmem.users[i].fif.files[sysmem.filenum-1].filename = destination;
    									sysmem.users[i].fif.files[sysmem.filenum-1].write = sysmem.users[i].fif.files[origin_num].write;
    									sysmem.users[i].fif.files[sysmem.filenum-1].read = sysmem.users[i].fif.files[origin_num].read;
    									sysmem.users[i].fif.files[sysmem.filenum-1].execute = sysmem.users[i].fif.files[origin_num].execute;
    								}
    								cout << "Copied successfuly" << endl;
							}
							else
							{
								cout << "Error: You can't copy this file: Access Denied" << endl;
							}
						}
						else
						{
							cout << "Error: You can't copy to destination: Access Denied" << endl;
						}
					}
					else
					{
						cout << "Error: Destination folder not found" << endl;
					}
				}
				else
				{
					cout << "Error: Destination already exists" << endl;
				}
			}
			else
			{
				cout << "Error: Origin not found" << endl;
			}
		}
		else
		{
			if (guis != 3)
			{
				cout << "Error: Invalid number of arguments" << endl;
			}
			else
			{
				if (!str2.compare(""))
				{
					cout << "Error: Origin can't be nothing" << endl;
				}
				if (!str4.compare(""))
				{
					cout << "Error: Destination can't be nothing" << endl;
				}
				if (str2.compare("") && str2_slash_start == false)
				{
					cout << "Error: " << str2 << " isn't a valid origin absolute path" << endl;
				}
				if (str4.compare("") && str4_slash_start == false)
				{
					cout << "Error: " << str4 << " isn't a valid destination absolute path" << endl;
				}
			}
		}
	}
	else if (!str1.compare("dmv"))
	{
		bool str2_slash_start = false;
		bool str4_slash_start = false;
		if (guis == 3)
		{
			if (str2[0] == '/')
			{
				str2_slash_start = true;
			}
			if (str4[0] == '/')
			{
				str4_slash_start = true;
			}
		}
		if (guis == 3 && str2_slash_start == true && str4_slash_start == true && str2.compare("") && str4.compare(""))
		{
			bool origin_found = false;
			int origin_num, origin_slashes = 0;
			bool origin_folders_inside = false;
			bool origin_files_inside = false;
			bool origin_can_read = false;
			string origin_slashesout = "";
			bool destination_found = false;
			bool destination_folder_found = false;
			int destination_folder_num, destination_slashes = 0;
			bool destination_can_write = false;
			string destination = str4, destination_folder = "";
			for (int i = 0; i < sysmem.foldernum; i++)
			{
				if (!str2.compare(sysmem.folders[i].dir))
				{
					origin_found = true;
					origin_num = i;
					break;
				}
			}
			if (origin_found == true)
			{
				//DESTINATION_CHECKS
				//CALCULATE origin_slashesout
				for (int i = 0; i < str2.length(); i++)
				{
					if (str2[i] == '/')
					{
						origin_slashes++;
					}
				}
				for (int slashes = 0, origin_pos = 0; origin_pos < str2.length(); origin_pos++)
				{
					if (slashes == origin_slashes)
					{
						origin_slashesout += str2[origin_pos];
					}
					if (str2[origin_pos] == '/')
					{
						slashes++;
					}
				}
				if (destination[destination.length()-1] == '/')
				{
					destination += origin_slashesout;
				}
				//DESTINATION_ALREADY_EXISTS?
				for (int i = 0; i < sysmem.foldernum; i++)
				{
					if (!destination.compare(sysmem.folders[i].dir))
					{
						destination_found = true;
						break;
					}
				}
				if (destination_found == false)
				{
					//DESTINATION_FOLDER_EXISTS?
					destination_slashes = 0;
					for (int i = 0; i < destination.length(); i++)
					{
						if (destination[i] == '/')
						{
							destination_slashes++;
						}
					}
					//cout << "Destination_slashes: " << destination_slashes << endl;
					for (int slashes = 0, destination_pos = 0; destination_pos < destination.length(); destination_pos++)
					{
						if (destination[destination_pos] == '/')
						{
							slashes++;
							if (destination_slashes == slashes)
							{
								break;
							}
						}
						if (slashes < destination_slashes)
						{
							destination_folder += destination[destination_pos];
						}
					}
					//cout << "Destination_folder: " << destination_folder << endl;
					for (int i = 0; i < sysmem.foldernum; i++)
					{
						//cout << "Comparing with: " << sysmem.folders[i].dir << endl;
						if (!destination_folder.compare(sysmem.folders[i].dir))
						{
							//cout << "Destination_folder_found" << endl;
							destination_folder_found = true;
							destination_folder_num = i;
							break;
						}
					}
					if (destination_folder_found == true)
					{
						//FOLDERS_INSIDE? && FILES_INSIDE?
						/*string origin_folder;
						for (int slashes = 0, origin_pos = 0; origin_pos < str2.length(); i++)
						{
							if (slashes < origin_slashes)
							{
								origin_folder += str2[origin_pos];
							}
							if (str2[origin_pos] == '/')
							{
								slashes++;
								if (slashes == origin_slashes)
								{
									break;
								}
							}
						}*/
						//FOLDERS_INSIDE
						string check_inside;
						for (int i = 0; i < sysmem.foldernum; i++)
						{
							check_inside = "";
							//cout << "CHECKING IS_FOLDER_INSIDE: " << sysmem.folders[i].dir << endl;
							if (i != origin_num)
							{
							for (int slashes = 0, string_pos = 0; string_pos < sysmem.folders[i].dir.length(); string_pos++)
							{
								if (sysmem.folders[i].dir[string_pos] == '/')
								{
									slashes++;
									if (slashes == origin_slashes+1)
									{
										break;
									}
								}
								if (slashes < origin_slashes+1)
								{
									check_inside += sysmem.folders[i].dir[string_pos];
								}
							}
							//cout << "CHECK_INSIDE: " << check_inside << endl;
							if (!check_inside.compare(str2))
							{
								//cout << "FOLDER_IS_INSIDE: " << endl;
								origin_folders_inside = true;
								break;
							}
							}
							//cout << "-------------------------------------------" << endl;
						}
						//FILES_INSIDE
						for (int i = 0; i < sysmem.filenum; i++)
						{
							check_inside = "";
							for (int slashes = 0, string_pos = 0; string_pos < sysmem.files[i].filename.length(); string_pos++)
							{
								if (sysmem.files[i].filename[string_pos] == '/')
								{
									slashes++;
									if (slashes == origin_slashes+1)
									{
										break;
									}
								}
								if (slashes < origin_slashes+1)
								{
									check_inside += sysmem.files[i].filename[string_pos];
								}
							}
							if (!check_inside.compare(str2))
							{
								origin_files_inside = true;
								break;
							}
						}
						if (origin_folders_inside == false && origin_files_inside == false)
						{
							//SECURITY
							if (sysmem.users[sysmem.current_user_id].fof.folders[origin_num].read == 1 || sysmem.users[sysmem.current_user_id].user_type == 1)
							{
								origin_can_read = true;
							}
							if (sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 2 || sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 3 || sysmem.users[sysmem.current_user_id].user_type == 1)
							{
								destination_can_write = true;
							}
							//cout << "SECURITY" << endl;
							if (origin_can_read == true && destination_can_write == true)
							{
								sysmem.folders[origin_num].dir = destination;
								for (int i = 0; i < sysmem.usersnum; i++)
								{
									sysmem.users[i].fof.folders[origin_num].dir = destination;
								}
								cout << "Moved successfuly" << endl;
							}
							else
							{
								if (origin_can_read == false)
								{
									cout << "Error: You can't move origin: Access Denied" << endl;
								}
								if (destination_can_write == false)
								{
									cout << "Error: You can't move to destination: Access Denied" << endl;
								}
							}
						}
						else
						{
							if (origin_folders_inside == true)
							{
								cout << "Error: Folders inside origin" << endl;
							}
							if (origin_files_inside == true)
							{
								cout << "Error: Files inside origin" << endl;
							}
						}
					}
					else
					{
						cout << "Error: Destination folder not found" << endl;
					}
				}
				else
				{
					cout << "Error: Destination already exists" << endl;
				}
			}
			else
			{
				cout << "Error: Origin not found" << endl;
			}
		}
		else
		{
			if (guis != 3)
			{
				cout << "Error: Invalid number of arguments" << endl;
			}
			else
			{
				if (!str2.compare(""))
				{
					cout << "Error: Origin can't be nothing" << endl;
				}
				if (!str4.compare(""))
				{
					cout << "Error: Destination can't be nothing" << endl;
				}
				if (str2.compare("") && str2_slash_start == false)
				{
					cout << "Error: " << str2 << " isn't a valid origin absolute path" << endl;
				}
				if (str4.compare("") && str4_slash_start == false)
				{
					cout << "Error: " << str4 << " isn't a valid destination absolute path" << endl;
				}
			}
		}
	}
	else if (!str1.compare("fmv"))
	{
		bool str2_slash_start = false;
		bool str4_slash_start = false;
		if (guis == 3)
		{
			if (str2[0] == '/')
			{
				str2_slash_start = true;
			}
			if (str4[0] == '/')
			{
				str4_slash_start = true;
			}
		}
		if (guis == 3 && str2.compare("") && str4.compare("") && str2_slash_start == true && str4_slash_start == true)
		{
			string origin_slashesout = "";
			bool origin_found = false;
			int origin_num, origin_slashes = 0;
			bool origin_can_read = false;
			string destination = str4, destination_folder="";
			bool destination_found = false;
			bool destination_folder_found = false;
			int destination_folder_num, destination_slashes = 0;
			bool destination_folder_can_write = false;
			//ORIGIN_FOUND
			for (int i = 0; i < sysmem.filenum; i++)
			{
				if (!str2.compare(sysmem.files[i].filename))
				{
					origin_found = true;
					origin_num = i;
					break;
				}
			}
			if (origin_found == true)
			{
				//DESTINATION_CHECK
				//CALCULATE ORIGIN_SLASHESOUT
				for (int i = 0; i < str2.length(); i++)
				{
					if (str2[i] == '/')
					{
						origin_slashes++;
					}
				}
				for (int slashes = 0, origin_pos = 0; origin_pos < str2.length(); origin_pos++)
				{
					if (slashes == origin_slashes)
					{
						origin_slashesout += str2[origin_pos];
					}
					if (str2[origin_pos] == '/')
					{
						slashes++;
					}
				}
				if (destination[destination.length()-1] == '/')
				{
					destination += origin_slashesout;
				}
				for (int i = 0; i < sysmem.filenum; i++)
				{
					if (!destination.compare(sysmem.files[i].filename))
					{
						destination_found = true;
						break;
					}
				}
				if (destination_found == false)
				{
					for (int i = 0; i < destination.length(); i++)
					{
						if (destination[i] == '/')
						{
							destination_slashes++;
						}
					}
					for (int slashes = 0, destination_pos = 0; destination_pos < destination.length(); destination_pos++)
					{
						if (destination[destination_pos] == '/')
						{
							slashes++;
							if (slashes == destination_slashes)
							{
								break;
							}
						}
						destination_folder += destination[destination_pos];
					}
					for (int i = 0; i < sysmem.foldernum; i++)
					{
						if (!destination_folder.compare(sysmem.folders[i].dir))
						{
							destination_folder_found = true;
							destination_folder_num = i;
							break;
						}
					}
					if (destination_folder_found == true)
					{
						//PERMISSIVE
						if (sysmem.users[sysmem.current_user_id].fif.files[origin_num].read == 1 || sysmem.users[sysmem.current_user_id].user_type == 1)
						{
							if (sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 2 || sysmem.users[sysmem.current_user_id].fof.folders[destination_folder_num].write == 3 || sysmem.users[sysmem.current_user_id].user_type == 1)
							{
								sysmem.files[origin_num].filename = destination;
								for (int i = 0; i < sysmem.usersnum; i++)
								{
									sysmem.users[i].fif.files[origin_num].filename = destination;
								}
								cout << "Moved successfuly" << endl;
							}
							else
							{
								cout << "Error: You can't copy to destination: Access Denied" << endl;
							}
						}
						else
						{
							cout << "Error: You can't move this file: Access Denied" << endl;
						}
					}
					else
					{
						cout << "Error: Destination folder not found" << endl;
					}
				}
				else
				{
					cout << "Error: Destination already exists" << endl;
				}
			}
			else
			{
				cout << "Error: Origin not found" << endl;
			}
		}
		else
		{
			if (guis != 3)
			{
				cout << "Error: Invalid number of arguments" << endl;
			}
			else
			{
				if (!str2.compare(""))
				{
					cout << "Error: Origin can't be nothing" << endl;
				}
				if (!str4.compare(""))
				{
					cout << "Error: Destination can't be nothing" << endl;
				}
				if (str2.compare("") && str2_slash_start == false)
				{
					cout << "Error: " << str2 << " isn't a valid origin absolute path" << endl;
				}
				if (str4.compare("") && str4_slash_start == false)
				{
					cout << "Error: " << str4 << " isn't a valid destination absolute path" << endl;
				}
			}
		}
	}
        else if (!str1.compare("whoami"))
        {
            cout << sysmem.current_user_id << " " << sysmem.users[sysmem.current_user_id].username << endl;
            cout << "User-type: " << sysmem.users[sysmem.current_user_id].user_type << endl;
        }
        else if (!str1.compare("logout"))
        {
            save();
            return;
        }
        else if (!str1.compare("exitos"))
        {
            save();
            exit(0);
        }
        else if (!str1.compare("help"))
        {
            if (guis == 1)
            {
                cout << VERSION << endl;
                cout << "By C0D3R11" << endl;
                cout << "sd..................................................Shows the current folder" << endl;
                cout << "ed_<directory>......................................Enters a directory" << endl;
                cout << "dpb.................................................Gets a directory back(like cd .. in linux)" << endl;
                cout << "nd_<new_directory_name>.............................Creates a directory with name: <new_directory_name>" << endl;
                cout << "deld_<directory>....................................Deletes <directory> directory" << endl;
                cout << "sf_<filename>.......................................Shows a file" << endl;
                cout << "delf_<filename>.....................................Deletes a file" << endl;
                cout << "wedit_<filename>....................................Edit's a file or creates a new one if it doesn't exist. End writing the" << endl;
		cout << "                                                    file with $quit in a new line" << endl;
                cout << "user_add_<username>_<passwd>........................Adds the <username> user with the <passwd> password" << endl;
                cout << "user_delete_<username>..............................Deletes the <username> user" << endl;
                cout << "user_chpwd_<username>...............................Change the password of <username> user" << endl;
                cout << "user_user-type_<username>...........................Changes the type of the user <username>" << endl;
                cout << "user_list...........................................Shows a list of all users" << endl;
                cout << "dp_change_<username>_<fodler_name>_<write><read>....Changes the permission of the user <username> in the folder <folder_name>" << endl;
		cout << "                                                    to <write><read>" << endl;
                cout << "dp_show_<username>_<folder_name>....................Shows the permission of the user <username> in the folder <folder_name>" << endl;
                cout << "dp_property_<folder_name>...........................Shows the owner of the folder <folder_name>" << endl;
                cout << "fp_change_<username>_<file_name>_<write><read>......Changes the permission of the user <username> in the file <file_name> to" << endl;
		cout << "                                                    <write><read>" << endl;
                cout << "fp_show_<username>_<file_name>......................Shows the permission of the user <username> in the file <file_name>" << endl;
                cout << "fp_property_<file_name>.............................Shows the owner of the folder <file_name>" << endl;
		cout << "dcp_<origin>_<destination>..........................Copies the origin folder to the destination(ONLY ABSOLUTE PATH)" << endl;
                cout << "fcp_<origin>_<destination>..........................Copies the origin file to the destination(ONLY ABSOLUTE PATH)" << endl;
		cout << "dmv_<origin>_<destination>..........................Moves the origin folder to the destination(ONLY ABSOLUTE PATH)" << endl;
		cout << "fmv_<origin>_<destination>..........................Moves the origin file to the destination(ONLY ABSOLUTE PATH)" << endl;
		cout << "whoami..............................................Shows current user in use" << endl;
                cout << "logout..............................................Returns to login screen" << endl;
                cout << "exitos..............................................Exits CerviOS" << endl;
                cout << "version.............................................Shows the version of the system" << endl;
                cout << "help_permissions....................................Explains how the permissions work" << endl;
                cout << "help................................................Shows this information" << endl;
		if (sysmem.current_user_id != 0)
		{
	 		cout << "\nYour home folder is /" << sysmem.users[sysmem.current_user_id].username << endl;
		}
            }
            else if (guis == 2)
            {
                if (!str2.compare("permissions"))
                {
                    cout << "-----WRITE-----" << endl;
                    cout << "FOLDERS" << endl;
                    cout << "0........NOT ERASE AND NOT CREATE FILES" << endl;
                    cout << "2........NOT ERASE BUT CREATE FILES" << endl;
                    cout << "3........ERASE AND CREATE FILES" << endl;
                    cout << "FILES" << endl;
                    cout << "0........NOT ERASE AND NOT WRITE" << endl;
                    cout << "1........NOT ERASE BUT WRITE" << endl;
                    cout << "2........ERASE AND WRITE" << endl;
                    cout << "-------READ-------" << endl;
                    cout << "FOLDERS" << endl;
                    cout << "0........CAN'T SEE CONTENT" << endl;
                    cout << "1........CAN SEE CONTENT" << endl;
                    cout << "FILES" << endl;
                    cout << "0........CAN'T SEE CONTENT" << endl;
                    cout << "1........CAN SEE CONTENT" << endl;
                }
                else
                {
                    cout << "Command not recognized" << endl;
                    cout << "Try help for command list" << endl;
                }
            }
            else
            {
                cout << "Command not recognized" << endl;
                cout << "Try help for command list" << endl;
            }
        }
        else if (!str1.compare("version"))
        {
            cout << VERSION << endl;
            cout << "By C0D3R11" << endl;
        }
        else
        {
            cout << "Command not recognized" << endl;
            cout << "Try help for command list" << endl;
        }
        cmd = "";
        str1 = "";
        str2 = "";
        str4 = "";
        str5 = "";
        str6 = "";
    }
}

void normal_boot()
{
    cout << "Loading..." << endl;
    load_files();
#if OS == WINDOWS
    Sleep(750);
#elif OS == LINUX
    usleep(750);
#endif //OS
    while(true)
    {
#if OS == WINDOWS
    system("cls");
#elif OS == LINUX
    system("clear");
#endif //OS
    login();
#if OS == WINDOWS
    system("cls");
#elif OS == LINUX
    system("clear");
#endif //OS
    shell();
    }
}

int main()
{
    cout << "Welcome to CerviOS Virtual Operative System" << endl;
    if (existsFile("inited.cos"))
    {
        normal_boot();
    }
    else
    {
        first_boot();
    }
    return 0;
}
