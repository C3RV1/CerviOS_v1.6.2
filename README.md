# CerviOS_v1.6.2

# Information
CervisOS is a virtual drive that is only used for text files(no programs)

CerviOS includes a set of commands for adding different users with different permissions.

CerviOS is an unfinished program that has a lot more things to add, like copying and moving folder with its own files inside.

# Guide

First you need to configure it setting the fist username, his password and the password for the master user _system_

After configuration, you will need to restart the program and then a login promp will open.

After loging in you can type help for the list of commands that you can use.

If you aren't logged in as _system_ you won't see the contents of the folder / because a normal user isn't alowed to, so in the end of the text that shows up when you type help, there will be your home folder, where you can do all the changes you want. Enter it with ed_<folder_name> (replace <folder_name> for you home folder name)

If you need help about how the permissions work you can type help_permissions and a help about permissions will show up.

# Version Changes

The versions have changed in the time including a lot of changes over the time and this version isn't an exception.

There isn't much to see like a user but there is a bug fix that made the command dp_change not work after some times typing it. This happened when stoi converted str6 to an integer. Str6 wasn't reset in the end of the command handling loop`and that made in acumulate data of past uses of command that used str6. Int doesn't have enought capacity of saving all that numbers that were accomulated and gived a std:out_range exception.

I found the error while testing all the program for getting sure there wasn't an error befor to start adding more things.

I am sure that the user was in fp too because it is the one that used str6 too.

# List of commands

sd..................................................Shows the current folder

ed_<directory>......................................Enters a directory

dpb.................................................Gets a directory back(like cd .. in linux)

nd_<new_directory_name>.............................Creates a directory with name: <new_directory_name>

deld_<directory>....................................Deletes <directory> directory

sf_<filename>.......................................Shows a file

delf_<filename>.....................................Deletes a file

wedit_<filename>....................................Edit's a file or creates a new one if it doesn't exist. End writing the file with $quit in a new line

user_add_<username>_<passwd>........................Adds the <username> user with the <passwd> password

user_delete_<username>..............................Deletes the <username> user

user_chpwd_<username>...............................Change the password of <username> user

user_user-type_<username>...........................Changes the type of the user <username>

user_list...........................................Shows a list of all users

dp_change_<username>_<fodler_name>_<write><read>....Changes the permission of the user <username> in the folder <folder_name> to <write><read>

dp_show_<username>_<folder_name>....................Shows the permission of the user <username> in the folder <folder_name>

dp_property_<folder_name>...........................Shows the owner of the folder <folder_name>

fp_change_<username>_<file_name>_<write><read>......Changes the permission of the user <username> in the file <file_name> to <write><read>

fp_show_<username>_<file_name>......................Shows the permission of the user <username> in the file <file_name>

fp_property_<file_name>.............................Shows the owner of the folder <file_name>

dcp_<oriigin>_<destiination>..........................Copies the origin folder to the destination(ONLY ABSOLUTE PATH)

fcp_<oriigin>_<destiination>..........................Copies the origin file to the destination(ONLY ABSOLUTE PATH)

dmv_<oriigin>_<destiination>..........................Moves the origin folder to the destination(ONLY ABSOLUTE PATH)

fmv_<oriigin>_<destiination>..........................Moves the origin file to the destination(ONLY ABSOLUTE PATH)

whoami..............................................Shows current user in use

logout..............................................Returns to login screen

exitos..............................................Exits CerviOS

version.............................................Shows the version of the system

help_permissions....................................Explains how the permissions work

help................................................Shows this information



I will keep working in this project as long as I want ;-)
C0D3R11
