#include "htrLoader.h"



void HTRLoader(HierarchyObj* root, const std::string resourceFilePath)
{
	std::ifstream fin(resourceFilePath);
	fileSectionHTR currentSection;

	while (!fin.eof())
	{
		std::string line;
		std::getline(fin, line);//sscanf

		for (int i = 0; )
		{

		}


	}
}
