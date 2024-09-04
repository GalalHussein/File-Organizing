/** «··Â„ «‰›⁄‰« »„« ⁄·„ ‰«, Ê⁄·„‰« »„« Ì‰›⁄‰«, Ê“œ‰« ⁄·„«
/**
 * Project: [File organizing]
 * Version: 1.1.0
 * Description: [Moving all files into folders that are created according to the type of files and open the folder in file explorer]
 *
 * Note:
 *    This project utilizes the "dirent" library for directory traversal and management,
 * allowing it to access and read directory contents effectively across different platforms.
 * Additionally, regular expressions (`regex`) have been employed to validate and filter
 * file types, ensuring accurate categorization and processing of files based on their extensions.
 *
 * Developed by: [Galal Hussein] ,studies at the Faculty of Computers and Artificial Intelligence, Helwan University
 *
 * Date: [2/9/2024]
 */

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <cstdlib> // system
#include <vector>
#include <algorithm>
#include "pattern.h"
#include "colors.h"

using namespace std;

 string MAIN_FLD_PATH;
 const string default_[5] = {"Imgs","Multimedia","Docs","Ideas","Data"};
 string FLD_NAMES[5];

 // PROTOTYPE SETTING
  void SETTING(bool chang_or_not);
  void RE_NAME();
  void NO_CHANGE();
  void DEFAULT();

 // PROTOTYPES
  int FILE_CATEGORY(string file_name);
  DIR *OPEN_DIR();
  void READE_DIR(DIR *main_dir);
  void FILTER_CATEGORY(vector<int>categories);
  void CREATE_FLD(string new_fld_name);
  void PASING_TO_MOVE(struct dirent *in_files, DIR *main_dir);
  void MOVE_FILES(string File_name, string New_fld_name);
  void OPEN_IN_EXPLORER();

int main()
{

  cout << YELLOW "Goto Setting? [1]:[0]\n";
  bool setting;
  cin >> setting;
  SETTING(setting);
  READE_DIR(OPEN_DIR());
  OPEN_IN_EXPLORER();

    return 0;
}


 // OPEND DIRECTOR:
 DIR *OPEN_DIR(){
   DIR *main_dir; // pointer to the main director
   string main_folder_path;
   cin.ignore();
   cout << YELLOW "Enter The Folder path: ";
   do{
      getline(cin, main_folder_path);
      main_dir = opendir(main_folder_path.c_str()); // c_str() to convert string to const *char
      if(main_dir != nullptr){
          MAIN_FLD_PATH = main_folder_path; // Store Path Of the main folder, to use it in two function ( Create fld, move folder)
       // cout << GREEN "Successful\n" RESET;
          break;
    }
      cerr << REDD << strerror(errno) << RESET;
      cout << YELLOW " Enter Valid path: ";
  } while(true);
  return main_dir; // return pointer to director to function READE_DIR
}// end function ==========================================



 // READ DIRECROTY:
 void READE_DIR(DIR *main_dir){
  struct dirent *in_files; // pointer to internal files in folder
  vector<int>Categories;
   while(in_files = readdir(main_dir)){
      Categories.push_back(FILE_CATEGORY(in_files->d_name));
  }
  FILTER_CATEGORY(Categories);
 // cout << GREEN "Successful\n" RESET;

  rewinddir(main_dir); // Return the pointer to the beginning of the director
  PASING_TO_MOVE(in_files, main_dir);

  closedir(main_dir);
}// end function ===========================================



 // File classification by regular expression:
 int FILE_CATEGORY(string file_name){
   if(regex_match(file_name, IMGS_PATTERN))
      return IMGS;
   else if(regex_match(file_name, MEDIA_PATERRN))
      return MEDIA;
   else if(regex_match(file_name, TXT_PATTERN))
      return IDEAS;
   else if(regex_match(file_name, DOCS_PATERRN))
      return DOCS;
   else if(regex_match(file_name, DATA_PATTERN))
      return DATA;

 }//end function ===========================================


 /* determines the folders needed for creation
    and call function CREATE_FLD */
 void FILTER_CATEGORY(vector<int>categories){

 //Delete duplicate types:
    sort(categories.begin(), categories.end());
    vector<int>::iterator repet = unique(categories.begin(), categories.end());
    categories.erase(repet, categories.end());

    for(int i: categories){
      switch(i){
        case IMGS:
         CREATE_FLD(FLD_NAMES[0]); // goto create folder imgs
         continue;
        case MEDIA:
         CREATE_FLD(FLD_NAMES[1]); // goto create folder media
         continue;
        case IDEAS:
         CREATE_FLD(FLD_NAMES[3]); // goto create folder ideas
         continue;
        case DOCS:
         CREATE_FLD(FLD_NAMES[2]); // goto create folder docs
         continue;
        case DATA:
         CREATE_FLD(FLD_NAMES[4]); // goto create folder data
         continue;
      }
    }
 }// end function =======================================


 // Create new folder:
 void CREATE_FLD(string new_fld_name){
   string new_fld_path = MAIN_FLD_PATH +"\\"+ new_fld_name;
   mkdir(new_fld_path.c_str());

 }// end function =======================================


 // Moving files into folder:
 void MOVE_FILES(string File_name, string New_fld_name){
    string FROM_PATH = MAIN_FLD_PATH + "\\" + File_name;
    string TO_PATH = MAIN_FLD_PATH + "\\" + New_fld_name +"\\"+ File_name;
  if(rename(FROM_PATH.c_str(),(TO_PATH.c_str())))
     cerr << REDD << strerror(errno);
  else
    cout << GREEN "Complete Successful\n" RESET;
 } // end function ========================================


 // Passing files name to move it:
 void PASING_TO_MOVE(struct dirent *in_files, DIR *main_dir){
    while(in_files = readdir(main_dir)){
    int temp = FILE_CATEGORY(in_files->d_name);
    switch(temp){
      case IMGS:
        MOVE_FILES(in_files->d_name,FLD_NAMES[0]);
        continue;
      case MEDIA:
         MOVE_FILES(in_files->d_name,FLD_NAMES[1]);
         continue;
      case IDEAS:
         MOVE_FILES(in_files->d_name,FLD_NAMES[3]);
         continue;
      case DOCS:
         MOVE_FILES(in_files->d_name,FLD_NAMES[2]);
         continue;
      case DATA:
         MOVE_FILES(in_files->d_name,FLD_NAMES[4]);
         continue;
   }
  }
}// end function =========================================


// Open main folder in explorer
 void OPEN_IN_EXPLORER(){
  string open_exp = "explorer " + MAIN_FLD_PATH;
  system(open_exp.c_str());
}// end function



// *******************************************************
// SETTING SETTING SETTING SETTING SETTING SETTING SETTING

// select setting:
 void SETTING(bool chang_or_not){

  if(chang_or_not){
  cout << BLUE "Setting: \n" RESET;
  cout << YELLOW " to rename folder press [1]\n";
  cout << " to get default names press [2]\n";
  cout << " to no change press [0]\n";
   int c;
   cin >> c;
   if(c == 1)
     RE_NAME();
   else if(c==2)
     DEFAULT();
   else
     NO_CHANGE();
  }
  else
    NO_CHANGE();
 }// end function =====================================


 // RENAME FOLDERS:
 void RE_NAME(){

   ofstream FILE_IN("new file_1.txt");
   cout << "Enter new names folders:\n";
   cin.ignore();
   for(int i=0; i<5; i++){
      string new_names;
      cout << default_[i] << ": ";
      getline(cin, new_names);
      FILE_IN << new_names << endl;
   }
  FILE_IN.close();
  NO_CHANGE();
}// end function ============================================

// DEFALUT NAMES:
 void DEFAULT(){
   ofstream FILE_IN("new file_1.txt");
   for(int i=0; i<5; i++){
     FILE_IN << default_[i] << endl;
   }
   NO_CHANGE();
}// end function ===========================================

/* NO CHANGING :
   It is always called after specifying
   or not specifying the settings,
   because it is responsible for extracting folder names
   from the text file.  */
 void NO_CHANGE(){
  ifstream FILE_OUT("new file_1.txt");

   if(!FILE_OUT.good()){ // To Handle The First Run Of Project
      DEFAULT();
   }
   else {

     for(int i=0; i<5; i++){
      string line;
      getline(FILE_OUT, line);
      FLD_NAMES[i] = line;
    }
   }
  FILE_OUT.close();
}// end function =======================================

/** End Of project ************************ Good luck*/


