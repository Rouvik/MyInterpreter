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
		return (double) i[regid];
	} else if(regname[0] == 'f')
	{
		return (double) f[regid];
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
		return (double) i[regid];
	} else if(regname[0] == 'f')
	{
		return (double) f[regid];
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
		i[regid] = (int) getRegValue(value, i, f, d);
	} else if(regname[0] == 'f')
	{
		f[regid] = (float) getRegValue(value, i, f, d);
	} else if(regname[0] == 'd')
	{
		d[regid] = getRegValue(value, i, f, d);
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