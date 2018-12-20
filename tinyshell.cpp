#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <time.h>

using namespace std;

struct comms{
      string commands;
      double time;
};

vector<comms>com;

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

bool compare (const comms& m, const comms& n)
{
	if(m.time <= n.time)
		return true;
}

void command_Exec(string command, bool sortHist){

    if(command=="history")
    {
	command = "";
	if(sortHist == false)
	{
	       vector<comms>::iterator itr;
	       int count = 1;
	       for(itr=com.end()-1;itr>=com.begin();itr--)
	       {
		   if(count <= 5)
		   	cout<<(*itr).commands<<"  "<<(*itr).time<<"s"<<endl;
		   count++;
	       }
	}
	else
	{
	  	vector<comms>::iterator itr;
	       	int count = 1;
		vector<comms>com_Sort;
		comms cmd;
	       	for(itr=com.end()-1;itr>=com.begin();itr--)
	       	{
		   if(count <= 5)
		   {
			cmd.commands = (*itr).commands;
			cmd.time = (*itr).time;
		   	com_Sort.push_back(cmd);
		   }
		   count++;
	       	}
		sort(com_Sort.begin(), com_Sort.end(), compare);
		vector<comms>::iterator itr2;
	        count = 1;
	        for(itr2=com_Sort.begin();itr2<com_Sort.end();itr2++)
	        {
		   if(count <= 5)
		   	cout<<(*itr2).commands<<"  "<<(*itr2).time<<"s"<<endl;
		   count++;
	        }
	}
    }
    else
    {
	const char *cmd = command.c_str(); 
	system(cmd);
    }
  exit(127);
}

int main()
{
    string command = "";
    pid_t pid;
    //int  status;
    cout << "tinyshell> ";
    while(getline(cin, command))
    {
        bool sortHist = false;
        bool isHist = false;
        trim(command);
        
        string word = "";
        command = command + " ";
        int len = command.length();
        
        for(int i = 0; i < len; i++)
        {
            if(command[i] == ' ')
            {
              if(word == "exit"){
                exit(0);
              }
              if(word == "-sbu"){
                sortHist = true;
              }
              if(word == "history"){
                isHist = true;
              }
              word = "";
            }
            else
                word = word + command[i];
        }
        trim(command);
        pid = fork();
	clock_t startTime;
        if(pid  == 0)
        {
	    startTime = clock();
            if(isHist == true)
                command_Exec("history", sortHist);
            else
                command_Exec(command, sortHist);
        }
        else if(pid < 0)
        {
            cout << "Fork Error";
        }
        if ((pid = waitpid(pid, NULL, 0)) < 0)
            cout<<"Error waiting for child"<<endl;
	else
	{
	    if(isHist != true)
	    {
		comms cmd;
		cmd.commands = command;
		cmd.time =  (double)(clock() - startTime);
	    	com.push_back(cmd);
	    }
        }

        cout << "tinyshell> ";
    }
    exit(0);
  }

