#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <fstream>      // std::ifstream


// Splits a multiprocessor output file into n single processor outputs
// ARGV[1] - number of processes 
// ARGV[2] - prefix to search for
// ARGV[3] - path to output file

// The code loops over all lines of output and searches for the string prefix+process_number for each process.
// When the string is found, the output is written to a file corresponding to that process

int main(int argc, char* argv[])
{
    int proc_number = atoi(argv[1]);
    std::string seek_prefix(argv[2]);
  
    std::ifstream src;  src.open (argv[3]);
    
    
    std::cout << "Splitting " << proc_number << " processor file " << argv[3] << " using prefix " << seek_prefix << std::endl;
    
    
    std::ofstream outs[proc_number];
    for (int i = 0; i < proc_number; i++) {  
      std::string tmp_name = "out/out" + std::to_string(i) + ".txt";
      outs[i].open( tmp_name ); 
    }
    
    std::string tmp_line;
    
    if (src.is_open())
    {
        while ( getline (src, tmp_line) )
        {
            for (int i = 0; i < proc_number; i++)
            {
                if (tmp_line.find(seek_prefix + std::to_string(i)) != std::string::npos) { outs[i] << tmp_line << std::endl; }
            }
      
        }
      src.close();
    }
    
    for (int i = 0; i < proc_number; i++) { outs[i].close();}
    
    
    return 0;
}