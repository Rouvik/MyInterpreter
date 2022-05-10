/**
* This code aims at making my own programming language (LowCode)
* To run simple commands in a virtual system (interpreter)
* By Rouvik Maji 14/12/2021
* P.S. - I know this is dumb and utter nonsense
*/

// check if cpp
#ifndef __cplusplus
  #error This program requires CPP compiler to compile
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// NOTE: Helper uses them so declare them before
// limit for registers
int REGLIMIT = 8;
bool DEBUG = false;

// helper functions
#include "helper.hpp"

// driver of interpreter code
int runlow(std::string filename)
{
	REGLIMIT = 8; // set number of registers allowed to 8
	
	// virtual data registers for the program
	int *i = (int*) calloc(REGLIMIT, 4);
	double *d = (double*) calloc(REGLIMIT, 8);
	float *f = (float*) calloc(REGLIMIT, 4);
	
	std::ifstream in;
	in.open("./" + filename);
	if(!in)
	{
		std::cout << "Error: File not found" << std::endl;
		in.close();
		return 1;
	}
	
	int lc = 0; // line counter
	
	while(!in.eof())
	{
		lc++; // increment line
		
		std::string line = "";
		std::getline(in, line);
		
		// print debug lines
		if(DEBUG)
		{
			std::cout << "\tDEBUG(" << lc << "): " << line << std::endl;
		}
		
		// manage comments
		if(line[0] == '#') // dont process empty lines
		{
			continue;
		}
		
		int compos = 0;
		if((compos = line.find('#')) > -1)
		{
			line = line.substr(0, compos);
		}
		
		try {
			
			// interpreted code
			std::istringstream tokens(line);
			std::string cmd;
			tokens >> cmd;
			
			// ignore if no command
			if(cmd == "")
			{
				continue;
			}
			
			// always convert to uppercase
			for(short i = 0; i < cmd.length(); i++)
			{
				cmd[i] = std::toupper(cmd[i]);
			}
			
			// registers a value to a register in memory
			if(cmd == "REG")
			{
				std::string regname, value; // stores the register name ex: i8
				if(!(tokens >> regname)) // check if regname exists
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				// if value doesnot exists
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				setRegValue(regname, value, i, f, d); // set value
			}
			
			else if(cmd == "IN")
			{
				std::string regname;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				std::string value;
				if(!(std::cin >> value))
				{
					std::cout << "BADIN: No input provided\n";
					throw 1;
				}
				
				setRegValue(regname, value, i, f, d);
			}
			
			// prints out a value from a register or raw numbers
			// NOTE: Could not use getRegValue(); to get specific values
			else if(cmd == "OUT")
			{
				std::string operand;
				if(!(tokens >> operand))
				{
					std::cout << std::endl;
					continue;
				}
				
				char x = operand[0];
				if(x == 'i')
				{
					std::cout << i[std::stoi(operand.substr(1))] << std::endl;
				} else if(x == 'd')
				{
					std::cout << d[std::stoi(operand.substr(1))] << std::endl;
				} else if(x == 'd')
				{
					std::cout << f[std::stoi(operand.substr(1))] << std::endl;
				} else {
					std::cout << std::stod(operand) << std::endl;
				}
			}
			
			else if(cmd == "ADD")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				setRegValue(regname, (getRegValueF(regname, i, f, d) + getRegValue(value, i, f, d)), i, f, d);
			}
			
			else if(cmd == "SUB")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				setRegValue(regname, (getRegValueF(regname, i, f, d) - getRegValue(value, i, f, d)), i, f, d);
			}
			
			else if(cmd == "MULT")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				setRegValue(regname, (getRegValueF(regname, i, f, d) * getRegValue(value, i, f, d)), i, f, d);
			}
			
			else if(cmd == "DIV")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				double toDiv = getRegValue(value, i, f, d);
				if(toDiv == 0)
				{
					std::cout << "DIV0\n";
					throw 1;
				}
				
				setRegValue(regname, (getRegValueF(regname, i, f, d) / toDiv), i, f, d);
			}
			
			else if(cmd == "IFEQ")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				// skip line if not equal
				if(getRegValueF(regname, i, f, d) != getRegValue(value, i, f, d))
				{
					getline(in, line);
					
					// print debug lines
					if(DEBUG)
					{
						std::cout << "\tDEBUG[ignored]: " << line << std::endl;
					}
				}
			}
			
			else if(cmd == "IFGT")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				double x = getRegValueF(regname, i, f, d),
				       y = getRegValue(value, i, f, d);
				
				// skip line if not greater than
				if((x == y) || (x < y))
				{
					getline(in, line);
					
					// print debug lines
					if(DEBUG)
					{
						std::cout << "\tDEBUG[ignored]: " << line << std::endl;
					}
				}
			}
			
			else if(cmd == "IFLT")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				double x = getRegValueF(regname, i, f, d),
				       y = getRegValue(value, i, f, d);
				
				// skip line if not less than
				if((x == y) || (x > y))
				{
					getline(in, line);
					
					// print debug lines
					if(DEBUG)
					{
						std::cout << "\tDEBUG[ignored]: " << line << std::endl;
					}
				}
			}
			
			else if(cmd == "IFLE")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				double x = getRegValueF(regname, i, f, d),
				       y = getRegValue(value, i, f, d);
				
				// skip line if not less than
				if(x > y)
				{
					getline(in, line);
					
					// print debug lines
					if(DEBUG)
					{
						std::cout << "\tDEBUG[ignored]: " << line << std::endl;
					}
				}
			}
			
			else if(cmd == "IFGE")
			{
				std::string regname, value;
				if(!(tokens >> regname))
				{
					std::cout << "NOREG: Reg not provided\n";
					throw 1;
				}
				
				if(!(tokens >> value))
				{
					std::cout << "BADVAL: Value not provided\n";
					throw 1;
				}
				
				double x = getRegValueF(regname, i, f, d),
				       y = getRegValue(value, i, f, d);
				
				// skip line if not less than
				if(x < y)
				{
					getline(in, line);
					
					// print debug lines
					if(DEBUG)
					{
						std::cout << "\tDEBUG[ignored]: " << line << std::endl;
					}
				}
			}
			
			else if(cmd == "JMP")
			{
				std::string lineTo, garbage;
				if(!(tokens >> lineTo))
				{
					std::cout << "NOREG: Reg not provided\n";
				}
				
				in.seekg(0); // get to beginning
				int toJump = (int) getRegValue(lineTo, i, f, d);
				for(int k = 1; k < toJump; k++)
				{
					std::getline(in, garbage); // garbage lines to be deleted
				}
				
				lc = toJump; // reset line number
			}
				
			
			// exits from the program
			else if(cmd == "EXIT")
			{
				std::string type;
				if(!(tokens >> type))
				{
					throw 1;
				}
				
				if(type == "0")
				{
					in.close();
					cleanup(i, f, d);
					return 0;
				} else if(type == "1")
				{
					std::cout << "BADEXIT\n";
					in.close();
					cleanup(i, f, d);
					return 1;
				} else {
					throw 0;
				}
			} else {
				std::cout << "BADCMD: Unknown command " << cmd << std::endl;
				throw 1;
			}
			
		} catch(...)
		{
			std::cout << "BADEXIT error at line " << lc << std::endl;
			in.close();
			cleanup(i, f, d);
			return 1;
		}
	}
	in.close();
	
	// view debug status
	viewReg(i, f, d);
}

int main(int argc, char const** argv)
{
	// if file provided run it and return exit code
	if(argc > 1)
	{
		return runlow(argv[1]);
	}
	
	// intro
	std::cout << "Welcome to LowCode virtual machine!" << std::endl
	     << "Type in \"run <filename>\" to run a program" << std::endl;
	std::string command = "";
	
	// event loop
	while(true)
	{
		std::cout << "$ ";
		std::getline(std::cin, command);
		std::istringstream cmdstream(command);
		
		std::string cmd; // contains actual command
		cmdstream >> cmd;
		if(cmd == "exit")
		{
			std::cout << "Terminating...";
			return 0;
		} else if(cmd == "run") // runs a code by calling runlow
		{
			std::string filename;
			if(!(cmdstream >> filename))
			{
				std::cout << "Error no filename provided\n";
				continue;
			}
			
			runlow(filename);
		} else if(cmd == "!") // run system commands
		{
			if(command.length() > 1)
			{
				system(command.substr(1).c_str());
			} else {
				std::cout << "Error no arguments\n";
			}
		} else if(cmd == "debug")
		{
			DEBUG = !DEBUG;
			if(DEBUG)
			{
				std::cout << "DEBUG mode on\n";
			} else {
				std::cout << "DEBUG mode off\n";
			}
		}
	}
}