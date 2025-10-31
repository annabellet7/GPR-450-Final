#include "htrLoader.h"


namespace gorp
{
	void HTRLoader(HierarchyObj* root, const std::string resourceFilePath)
	{
		std::ifstream fin(resourceFilePath);
		fileSectionHTR currentSection = htr_file;
		std::string buffer[2];

		while (!fin.eof())
		{
			std::string line;
			std::getline(fin, line);//sscanf

			//Change of section
			if (line.at(0) == '[')
			{
				//Checking which section we are in
				if (line.compare(sectionStr[htr_header]) == 0) currentSection = htr_header;
				else if (line.compare(sectionStr[htr_hierarchy]) == 0) currentSection = htr_hierarchy;
				else if (line.compare(sectionStr[htr_basepose]) == 0) currentSection = htr_basepose;
				else if (line.compare(sectionStr[htr_eof]) == 0)
				{
					currentSection = htr_eof;
					break;
				}
				else
				{
					//read for frame pose
					//currentSection = htr_nodepose
				}
			}
			
			else if (line.at(0) != '#')
			{
				switch (currentSection)
				{
				case htr_header:
					sscanf(line.c_str(), "%s %s", buffer[0], buffer[1]);

					if (buffer[0].compare(headerComponents[htr_FileType]));
					else if (buffer[0].compare(headerComponents[htr_DataType]));
					else if (buffer[0].compare(headerComponents[htr_FileVersion]));

					else if (buffer[0].compare(headerComponents[htr_NumSegments]))
					{
						//atoi(buffer[1].c_str());
					}
					else if (buffer[0].compare(headerComponents[htr_NumFrames]))
					{
						//atoi(buffer[1].c_str());
					}
					else if (buffer[0].compare(headerComponents[htr_DataFrameRate]))
					{
						//fps = atoi(buffer[1].c_str());
						//seconds per sample = 1/
					}
					else if (buffer[0].compare(headerComponents[htr_EulerRotationOrder]))
					{
						//dumbass turnary operators cuz theyre fun
						/*eulerorder =
							tolower(buffer[1][0]) == 'x' ?
								(tolower(buffer[1][1]) == 'y' ? xyz : xzy) :
							tolower(buffer[1][0]) == 'y' ?
								(tolower(buffer[1][1]) == 'x' ? yxz : yzx) :
								(tolower(buffer[1][1]) == 'x' ? zxy : zyx);
						*/
					}
					else if (buffer[0].compare(headerComponents[htr_CalibrationUnits]));//will be degrees
					else if (buffer[0].compare(headerComponents[htr_RotationUnits]))
					{

					}

					else if (buffer[0].compare(headerComponents[htr_GlobalAxisofGravity]));
					else if (buffer[0].compare(headerComponents[htr_BoneLengthAxis]));

					else if (buffer[0].compare(headerComponents[htr_ScaleFactor]));//will be one
					break;
				}
			}
		}
	}

}
