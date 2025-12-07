#include "htrLoader.h"


void HTRLoader(HierarchyState* out_hierarchy, HeaderData headerData, const std::string resourceFilePath)
{
	std::ifstream fin(resourceFilePath);
	fileSectionHTR currentSection = htr_file;
	int animationIndex;
	std::string currentBone;
	std::string buffer[2];

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
				currentSection = htr_nodepose;
				currentBone = line.substr(1, line.length() - 2);
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
				float Tx, Ty, Tz, Rx, Ry, Rz, BoneLength;
				std::stringstream ss(line);
				ss >> name >> Tx >> Ty >> Tz >> Rx >> Ry >> Rz >> BoneLength;

				Transform transform;
				transform.translate = glm::vec4(Tx, Ty, Tz, 1);
				transform.rotate = glm::vec4(Rx, Ry, Rz, 0);

				out_hierarchy->animList[animationIndex].tNode[currentBone][0].local = transform;
				break;
			}
			case htr_nodepose:
			{
				int index;
				float Tx, Ty, Tz, Rx, Ry, Rz, scale;
				std::stringstream ss(line);
				ss >> index >> Tx >> Ty >> Tz >> Rx >> Ry >> Rz >> scale;

				Transform transform;
				transform.translate = glm::vec4(Tx, Ty, Tz, 1);
				transform.rotate = glm::vec4(Rx, Ry, Rz, 0);

				out_hierarchy->animList[animationIndex].tNode[currentBone][index].local = transform;
				//out_hierarchy->local.push_back(transform);
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

