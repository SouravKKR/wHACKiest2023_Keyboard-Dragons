#include "Utility.h"

int main()
{
    std::string pathtofiles;
    std::cout << "Enter the path to store the fetched files (use '/' and end with '/'): ";
    std::cin >> pathtofiles;
    std::cout << std::endl;
    std::string Query = "select* from problems;", result;
    std::fstream file;
    file.open("QueryToRun.txt", std::fstream::out | std::fstream::trunc);
    file << Query;
    file.close();
    system("Test.exe");
    if (WaitForResult())
    {
        result = ReadFile("Result.txt");
        EraseFile("Result.txt");
        EraseFile("ResultStatus.txt");
        std::vector<Problem> List;
        ParseQueryResult(List, result);
        int i = 1;
        for (auto ele : List)
        {
            std::string FileName = pathtofiles;
            FileName.append("Entry");
            FileName.append(std::to_string(i));
            FileName.append(".txt");
            std::fstream Entry;
            file.open(FileName, std::fstream::out | std::fstream::trunc);
            file << "ID: "<<ele.ProblemID<<"\n"<<"Description: "<<ele.ProblemDescription<<"\n"<<"Time: "<<ele.TimeStamp<<"\n"<<"USN: "<<ele.USN<<"\n"<<"Contact: "<<ele.Contact<<"\n"<<"Comments by faculty:"<<ele.Comments<<"\n"<<"Publicly Visible: "<<ele.Public<<"\n"<<"Resolved: "<<ele.Resolved<<"\n";
            file.close();
            i++;
        }
    }
}