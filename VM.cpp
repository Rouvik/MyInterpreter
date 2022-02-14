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

// limit for registers
int REGLIMIT = 8;
bool DEBUG = false;

// gets a register value or number
double getRegValue(std::string regname, int *i, float *f, double *d)
{
	int regid = 0;
	if(regname.length() > 1) // avoid substring of single digits
	{
		regid = std::stoi(regname.substr(1));
	}
	
	if(regid > REGLIMIT)
	{
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
	
	
	if(regname[0] == 'i')
	{
		return i[regid];
	} else if(regname[0] == 'f')
	{
		return f[regid];
	} else if(regname[0] == 'd')
	{
		return d[regid];
	} else {
		return std::stod(regname);
	}
}

// gets a register value
double getRegValueF(std::string regname, int *i, float *f, double *d)
{
	int regid = std::stoi(regname.substr(1));
	if(regid > REGLIMIT)
	{
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
	
	
	if(regname[0] == 'i')
	{
		return i[regid];
	} else if(regname[0] == 'f')
	{
		return f[regid];
	} else if(regname[0] == 'd')
	{
		return d[regid];
	} else {
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
}

// sets a register value
void setRegValue(std::string regname, std::string value, int *i, float *f, double *d)
{
	int regid = std::stoi(regname.substr(1));
	if(regid > REGLIMIT)
	{
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
	
	
	if(regname[0] == 'i')
	{
		i[regid] = std::stoi(value);
	} else if(regname[0] == 'f')
	{
		f[regid] = std::stof(value);
	} else if(regname[0] == 'd')
	{
		d[regid] = std::stod(value);
	} else {
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
}

void setRegValue(std::string regname, double value, int *i, float *f, double *d)
{
	int regid = std::stoi(regname.substr(1));
	if(regid > REGLIMIT)
	{
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
	
	
	if(regname[0] == 'i')
	{
		i[regid] = (int) value;
	} else if(regname[0] == 'f')
	{
		f[regid] = (float) value;
	} else if(regname[0] == 'd')
	{
		d[regid] = value;
	} else {
		std::cout << "NOREG: reg \'" << regname << "\' doesnot exists\n";
		throw 1;
	}
}

// display the register values for debugging
void viewReg(int *i, float *f, double *d)
{
	if(!DEBUG) return; // dont show if debug is off
	
    int len = 8;
    std::cout << "i: ";
	for(int k = 0; k < len; k++)
	{
		std::cout << "(" << k << "->" << i[k] << ") ";
	}
	
	std::cout << std::endl << "f: ";
	
	for(int k = 0; k < len; k++)
	{
		std::cout << "(" << k << "->" << f[k] << ") ";
	}
	
	std::cout << std::endl << "d: ";
	
	for(int k = 0; k < len; k++)
	{
		std::cout << "(" << k << "->" << d[k] << ") ";
	}
	
	std::cout << std::endl;
}

// cleanup the memory at exit
void cleanup(int *i, float *f, double *d)
{
	viewReg(i, f, d);
	
    // cleanup memory
	std::free(i);
	std::free(f);
	std::free(d);
}

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
	
	int lc = 1; // line counter
	
	while(!in.eof())
	{
		std::string line = "";
		std::getline(in, line);
		
		// manage comments
		int compos = 0;
		if((compos = line.find(';')) > -1)
		{
			line = line.substr(0, compos);
		}
		
		try {
			
			// interpreted code
			std::istringstream tokens(line);
			std::string cmd;
			if(!(tokens >> cmd))
			{
				throw 1;
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
			}
			
		} catch(...)
		{
			std::cout << "BADEXIT error at line " << lc << std::endl;
			in.close();
			cleanup(i, f, d);
			return 1;
		}
		lc++;
	}
	in.close();
	
	// view debug status
	viewReg(i, f, d);
}

int main()
{
	// intro
	std::cout << "Welcome to LowCode virtual machine!" << std::endl
	     << "Type in \"run <filename>\" to run a program" << std::endl;
	std::string command = "";
	
	// event loop
	while(true)
	{
		std::cout << "$ ";
		std::getline(std::cin, command);
		if(command == "exit")
		{
			std::cout << "Terminating...";
			return 0;
		} else if(command.substr(0, 3) == "run") // runs a code by calling runlow
		{
			runlow(command.substr(4));
		} else if(command.substr(0, 1) == "!") // run system commands
		{
			system(command.substr(1).c_str());
		} else if(command.substr(0, 5) == "debug")
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