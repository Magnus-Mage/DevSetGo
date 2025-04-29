// Divide the files later for more readibility


#include <iostream>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>

using namespace std;

// For Yaml reading

struct Package
{
	string name;
	string type;
};


// Parse YAML files to read and input

vector<Package> parseYAML(const std::string& filename)
{
	vector<Package> packages;

	try 
	{
		YAML::Node config = YAML::LoadFile(filename);
		for (const auto& pkg : config["packages"])
		{
			Package p;
			p.name = pkg["name"].as<string>();
			p.type = pkg["type"].as<string>();
			packages.push_back(p);
		}


	}
	catch (const YAML::Exception& e)
	{
		cerr << "YAML Error: " << e.what() << endl;
		exit(1);
	}

	return packages;
}

// Check linux versions

string getSystemPackageManager()
{
	ifstream osRelease("/etc/os-release");
	string line;
	string id;

	while(getline(osRelease, line))
	{
		if (line.rfind("ID=", 0) == 0)
		{
			id = line.substr(3);
			break;
		}
	}

	if(id.find("ubuntu") != string::npos || id.find("debian") != string::npos)
	{
		return "apt-get";
	}
	else if(id.find("fedora") != string::npos || id.find("rhel") != string::npos)
	{
		return "dnf";
	}
	else if(id.find("arch") != string::npos || id.find("manjaro") != string::npos)
	{
		return "pacman";
	}

	return ""; // Unknown or unsupported atm

}


// Parse for pip / python installations


string getPipCommand()
{
	int res = system("which pip3 > /dev/null 2>&1");
	if (res == 0) return "pip3";

	res = system("which pip > /dev/null 2>&1");
	if (res == 0) return "pip";

	res = system("python3 -m pip --version > /dev/null 2>&1");
	if (res == 0) return "python3 -m pip";

	return "";

}

//Package Installer logic


void installPackage(const Package& pkg)
{
	string pkgManager = getSystemPackageManager();
	string pipCommand = getPipCommand();

	if (pkg.type == "system")
	{

	}
}




// Main Driver Fnc

int main(int argc, char* argv[])
{
	if (argc !=2)
	{
		cerr << "Usage: ./dsg <yaml_file>\n";
		return 1;
	}

	string yamlFile = argv[1];
	auto packages = parseYAML(yamlFile);

	cout << "Packages found: \n";
	for (const auto& pkg : packages)
	{
		cout << "- " << pkg.name << " (" << pkg.type << ")\n";
	}
	
	
	
	return 0;
}
