#include "htrLoader.h"


namespace gorp
{
	void HTRLoader(std::vector<std::vector<HierarchyObj*>> clipPoseList, HeaderData headerData, const std::string resourceFilePath)
	{
		std::ifstream fin(resourceFilePath);
		fileSectionHTR currentSection = htr_file;
		std::string buffer[2];
		std::string currentNode;

		while (!fin.eof())
		{
			std::string line;
			std::getline(fin, line);

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

					if (buffer[0].compare(headerComponents[htr_FileType]))
					{
						headerData.fileType = buffer[1];
					}
					else if (buffer[0].compare(headerComponents[htr_DataType]))
					{
						headerData.dataType = buffer[1];
					}
					else if (buffer[0].compare(headerComponents[htr_FileVersion]))
					{
						headerData.fileVersion = buffer[1];
					}
					else if (buffer[0].compare(headerComponents[htr_NumSegments]))
					{
						headerData.boneCount = std::stoi(buffer[1]);
					}
					else if (buffer[0].compare(headerComponents[htr_NumFrames]))
					{
						headerData.numFrames = std::stoi(buffer[1]);
					}
					else if (buffer[0].compare(headerComponents[htr_DataFrameRate]))
					{
						headerData.frameRate = std::stof(buffer[1]);
					}
					else if (buffer[0].compare(headerComponents[htr_EulerRotationOrder]))
					{
						headerData.eulerRotationOrder = buffer[1];

						//dumbass turnary operators cuz theyre fun
						/*eulerorder =
							tolower(buffer[1][0]) == 'x' ?
								(tolower(buffer[1][1]) == 'y' ? xyz : xzy) :
							tolower(buffer[1][0]) == 'y' ?
								(tolower(buffer[1][1]) == 'x' ? yxz : yzx) :
								(tolower(buffer[1][1]) == 'x' ? zxy : zyx);
						*/
					}
					else if (buffer[0].compare(headerComponents[htr_CalibrationUnits]))
					{
						headerData.calibrationUnits = buffer[1];
					}
					else if (buffer[0].compare(headerComponents[htr_RotationUnits]))
					{
						headerData.isDegrees = buffer[1].at(0) == 'd';
					}
					else if (buffer[0].compare(headerComponents[htr_GlobalAxisofGravity]))
					{
						headerData.globalAxisofGravity = buffer[1].at(0);
					}
					else if (buffer[0].compare(headerComponents[htr_BoneLengthAxis]))
					{
						headerData.boneLengthAxis = buffer[1].at(0);
					}
					else if (buffer[0].compare(headerComponents[htr_ScaleFactor]))
					{
						headerData.scaleFactor = std::stof(buffer[1]);
					}
					break;
				case htr_basepose:
					char* name;
					float Tx, Ty, Tz, Rx, Ry, Rz, BoneLength;
					sscanf(line.c_str(), "%s %f %f %f %f %f %f %f", name, Tx, Ty, Tz, Rx, Ry, Rz, BoneLength);
					break;
				case htr_nodepose:
					int index;
					float Tx, Ty, Tz, Rx, Ry, Rz, scale;
					sscanf(line.c_str(), "%d %f %f %f %f %f %f %f", index, Tx, Ty, Tz, Rx, Ry, Rz, scale);
					break;
				}
			}
		}
	}

}
