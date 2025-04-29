#include <iostream>
#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>


using namespace std;

struct Package
{
	string name;
	string type;
};

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
