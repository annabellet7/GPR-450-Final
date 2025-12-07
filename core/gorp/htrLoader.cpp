#include "htrLoader.h"


namespace gorp
{
	void HTRLoader(HierarchyState* out_hierarchy, HeaderData headerData, const std::string resourceFilePath)
	{
		std::ifstream fin(resourceFilePath);
		fileSectionHTR currentSection = htr_file;
		std::string buffer[2];
		std::string currentNode;

		int index;
		float Tx, Ty, Tz, Rx, Ry, Rz;

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
				{
					std::stringstream ss(line);
					ss >> buffer[0] >> buffer[1];

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
				}
				case htr_basepose:
				{
					std::string name;
					float BoneLength;
					std::stringstream ss(line);
					ss >> name >> Tx >> Ty >> Tz >> Rx >> Ry >> Rz >> BoneLength;
					break;
				}
				case htr_nodepose:
				{
					int index;
					float scale;
					std::stringstream ss(line);
					ss >> index >> Tx >> Ty >> Tz >> Rx >> Ry >> Rz >> scale;
					break;
				}
				case htr_hierarchy:
				{
					std::stringstream ss(line);
					ss >> buffer[0] >> buffer[1];

					HierarchyNode currentNode;
					currentNode.name = buffer[0];
					currentNode.selfIndex = out_hierarchy->mHierarchy->nodeList.size();
					currentNode.parentIndex = out_hierarchy->mHierarchy->getNode(buffer[1]);

					out_hierarchy->mHierarchy->addNode(currentNode);

					break;
				}
				}
			}
		}
	}

}
