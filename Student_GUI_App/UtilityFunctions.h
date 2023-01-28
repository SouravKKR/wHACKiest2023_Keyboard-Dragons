#pragma once
#include<string>
#include<vector>
#include <bits/stdc++.h>
#include<chrono>
#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

struct Problem
{
    std::string ProblemID;
    std::string ProblemType;
    std::string ProblemDescription;
    std::string TimeStamp;
    std::string USN;
    std::string Contact;
    bool Resolved;
    std::string Comments;
    bool Public;

    Problem(std::string problemID, std::string problemType,std::string problemDescription,std::string timeStamp,std::string uSN,std::string contact,bool resolved, std::string comments,bool bpublic)
    {
        ProblemID=problemID;
        ProblemType =problemType;
        ProblemDescription = problemDescription;
        TimeStamp=timeStamp;
        USN =uSN;
        Contact =contact;
        Comments =comments;
        Public = bpublic;
    }
};

std::string GetDateTime()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y-%X", now);
    buffer[13]= buffer[16]= '-';
    return buffer;
}

std::string GetRandomString(const int len) {
    srand(time(0));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

bool MakeInsertQuery(Problem Data, std::string& Query)
{
    if(!Data.ProblemDescription.size())
    {
        return false;
    }

    Data.ProblemID =  GetRandomString(18);
    Data.TimeStamp = GetDateTime();
    Data.Resolved = false;
    Data.Comments ="";

    if(!Data.USN.size())
    {
        Data.USN = "Anonymous";
    }
    if(!Data.Contact.size())
    {
        Data.Contact = "Not Given";
    }
    else if(Data.Contact.size()>10)
    {
        return false;
    }

    Query = "insert into problems values('";
    Query.append(Data.ProblemID);
    Query.append("','");
    Query.append(Data.ProblemType);
    Query.append("','");
    Query.append(Data.ProblemDescription);
    Query.append("','");
    Query.append(Data.TimeStamp);
    Query.append("','");
    Query.append(Data.USN);
    Query.append("','");
    Query.append(Data.Contact);
    Query.append("',");
    Query.append("0");
    Query.append(",'");
    Query.append("");
    Query.append("',");
    Query.append(std::to_string((int)Data.Public));
    Query.append(");");
    return true;

}

void ParseQueryResult(std::vector<Problem>& OutArray, std::string FileContent)
{
        std::vector<std::string> v;
        std::stringstream ss(FileContent);

        while (ss.good()) {
            for(int i=0;i<9;i++)
            {
                std::string substr;
                getline(ss, substr, ',');
                v.push_back(substr);
            }
            bool resolved= false;
            bool bpublic = false;
            if (v[6]=="1")
                resolved = true;
            if(v[8]=="1")
                bpublic =true;


            OutArray.emplace_back(Problem(v[0],v[1],v[2],v[3],v[4],v[5],resolved,v[7],bpublic));
            v.clear();

        }
}

bool WaitForResult()
{
     std::string str;
     while(true)
     {
        std::ifstream ResultFile("ResultStatus.txt");

        if (ResultFile)
        {
            std::ostringstream ss;
            ss << ResultFile.rdbuf();
            str = ss.str();
            if(str=="1")
                return true;
            else if(str=="0")
                return false;
        }

      }
     return false;
}

std::string ReadFile(std::string FilePath)
{
    std::ifstream ResultFile(FilePath);
    if (ResultFile)
    {
        std::ostringstream ss;
        ss << ResultFile.rdbuf();
        return ss.str();
    }
    else
        return std::string();

}

void EraseFile(std::string FilePath)
{
    std::ofstream myfile(FilePath, std::ios::trunc);
    myfile.close();
}
#endif // UTILITYFUNCTIONS_H

