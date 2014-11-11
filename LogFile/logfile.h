#ifndef LOGFILE_H
#define LOGFILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>

using namespace std;

class LogFile
{
    string file_name;
public:
    /**
    *	@brief constructor for loggFile, write loggs into file "loggs.txt"
    *   for now is this class WITHOUT UNIT TEST !!!
    *
    **/
    LogFile();

    /**
    *	@brief constructor for loggFile
    *
    *   @string fileName name of file to write loggs
    **/
    LogFile(string fileName);

    /**
    *	@brief log function for windows to write log's data into file loggs.txt, now in synchronous approach,
    *   later locks or mutexes will be add.
    *   Log data in format:
    *   [year],[month],[day],[hour],[minute],[second],[milisecond];[data]\n
    *
    *   @string buffer data to write into file
    **/
    void Make_log(string data);
};

#endif // LOGFILE_H
