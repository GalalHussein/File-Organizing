#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED

#include <regex>
#include <errno.h> // errno
#define IMGS 1
#define MEDIA 2
#define IDEAS 3
#define DOCS 4
#define DATA 5

 //  Regular expressions
  std::regex IMGS_PATTERN("(.*\\.(jpg|jpeg|png|psd)$)"); // imgs
  std::regex MEDIA_PATERRN("(.*\\.(mp4|mp3|mkv|mov|webm)$)"); // multimedia
  std::regex TXT_PATTERN("(.*\\.(md|txt)$)"); // Ideas
  std::regex DOCS_PATERRN("(.*\\.(pdf|ppt|pptx|ppsx|xls|xlsx|xlsm|doc|docx)$)"); // Docs
  std::regex DATA_PATTERN("(.*\\.(dat|json|csv)$)"); // Data


#endif // PATTERN_H_INCLUDED
