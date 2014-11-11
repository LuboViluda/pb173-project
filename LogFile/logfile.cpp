#include "logfile.h"

LogFile::LogFile()
{
    file_name = "loggs.txt";
}

LogFile::LogFile(string new_file_name)
{
    file_name = new_file_name;
}

void LogFile::Make_log(string buffer)
{
    ofstream log_file;
    SYSTEMTIME st;
    GetSystemTime(&st);

    log_file.open(file_name.c_str(), std::ofstream::app);
    log_file << st.wYear << "," << st.wMonth << "," <<st.wDay << "," <<st.wHour << ","
             << st.wMinute << "," << st.wSecond << "," << st.wMilliseconds << ";";
    log_file << buffer << endl;
    log_file.close();
}
