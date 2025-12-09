#include "htrLoader.h"

void TestHTRLoader(HierarchyList* out_hierarchy, HeaderData* headerData, const std::string resourceFilePath)
{
	std::ifstream fin(resourceFilePath);
	if (!fin.is_open())
	{
		printf("Error: Unable to open file!\n");
		return;
	}


	fileSectionHTR currentSection = htr_file;
	int animationIndex;
	std::string currentBone;
	std::string buffer[2];
	int basePoseCounter = 0;
	int animationTracker = 0;
	int nodeIndex = 0;
	int keyframeCounter = 0, totalKeyframeCounter = 0;

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

				if (buffer[0] == headerComponents[htr_FileType])
				{
					headerData->fileType = buffer[1];
				}
				else if (buffer[0] == headerComponents[htr_DataType])
				{
					headerData->dataType = buffer[1];
				}
				else if (buffer[0] == headerComponents[htr_FileVersion])
				{
					headerData->fileVersion = buffer[1];
				}
				else if (buffer[0] == headerComponents[htr_NumSegments])
				{
					headerData->boneCount = std::stoi(buffer[1]);
				}
				else if (buffer[0] == headerComponents[htr_NumFrames])
				{
					headerData->numFrames = std::stoi(buffer[1]);
				}
				else if (buffer[0] == headerComponents[htr_DataFrameRate])
				{
					headerData->frameRate = std::stof(buffer[1]);
				}
				else if (buffer[0] == headerComponents[htr_EulerRotationOrder])
				{
					headerData->eulerRotationOrder = buffer[1];
				}
				else if (buffer[0] == headerComponents[htr_CalibrationUnits])
				{
					headerData->calibrationUnits = buffer[1];
				}
				else if (buffer[0] == headerComponents[htr_RotationUnits])
				{
					headerData->isDegrees = buffer[1].at(0) == 'D';
				}
				else if (buffer[0] == headerComponents[htr_GlobalAxisofGravity])
				{
					headerData->globalAxisofGravity = buffer[1].at(0);
				}
				else if (buffer[0] == headerComponents[htr_BoneLengthAxis])
				{
					headerData->boneLengthAxis = buffer[1].at(0);
				}
				else if (buffer[0] == headerComponents[htr_ScaleFactor])
				{
					headerData->scaleFactor = std::stof(buffer[1]);
				}
				break;
			}
			case htr_basepose:
			{
				std::string name;
				float Tx, Ty, Tz, Rx, Ry, Rz, BoneLength;
				std::stringstream ss(line);
				ss >> name >> Tx >> Ty >> Tz >> Rx >> Ry >> Rz >> BoneLength;

				NodeTransform transform;
				transform.local.translate = glm::vec4(Tx, Ty, Tz, 1);
				transform.local.rotate = glm::vec4(Rx, Ry, Rz, 0);
				transform.local.scale = glm::vec4(1.0);

				out_hierarchy->nodePoseList->basePose.push_back(transform);

				out_hierarchy->nodePoseList->basePose[basePoseCounter].nodeIndex = basePoseCounter;
				out_hierarchy->nodePoseList->basePose[basePoseCounter].keyframeIndex = -1;

				basePoseCounter++;
		
				break;
			}
			case htr_nodepose:
			{
				int index;
				float Tx, Ty, Tz, Rx, Ry, Rz, scale;
				std::stringstream ss(line);
				ss >> index >> Tx >> Ty >> Tz >> Rx >> Ry >> Rz >> scale;

				NodeTransform transform;
				transform.local.translate = glm::vec4(Tx, Ty, Tz, 1);
				transform.local.rotate = glm::vec4(Rx, Ry, Rz, 0);
				transform.local.scale = glm::vec4(1.0);

				switch (animationTracker)
				{
				case 0:
					//out_hierarchy->nodePoseList->transformsList.push_back(transform);
					out_hierarchy->nodePoseList->transformsList.push_back(transform);
					
					out_hierarchy->nodePoseList->transformsList[totalKeyframeCounter].nodeIndex = nodeIndex;
					out_hierarchy->nodePoseList->transformsList[totalKeyframeCounter].keyframeIndex = index - 1;
					
					if (index % anim1keyframecount == 0)
					{
						nodeIndex++;
						keyframeCounter++;
					}
					
					totalKeyframeCounter++;
					if (totalKeyframeCounter > headerData->boneCount * anim1keyframecount)
					{
						animationTracker = 1;
						nodeIndex = 0;
					}
					break;
				case 1:
					out_hierarchy->nodePoseList->transformsList.push_back(transform);
					//out_hierarchy->nodePoseList[totalKeyframeCounter].transformsList.push_back(transform);

					out_hierarchy->nodePoseList->transformsList[totalKeyframeCounter].nodeIndex = nodeIndex;
					out_hierarchy->nodePoseList->transformsList[totalKeyframeCounter].keyframeIndex = index - 1;

					if (index % anim2keyframecount == 0)
					{
						nodeIndex++;
						keyframeCounter++;
					}

					totalKeyframeCounter++;
					if (totalKeyframeCounter > headerData->boneCount * anim2keyframecount)
					{
						animationTracker = 1;
						nodeIndex = 0;
					}
					break;
				case 2:
					out_hierarchy->nodePoseList->transformsList.push_back(transform);
					//out_hierarchy->nodePoseList[totalKeyframeCounter].transformsList.push_back(transform);

					out_hierarchy->nodePoseList->basePose[totalKeyframeCounter].nodeIndex = nodeIndex;
					out_hierarchy->nodePoseList->basePose[totalKeyframeCounter].keyframeIndex = index - 1;

					if (index % anim2keyframecount == 0)
					{
						nodeIndex++;
					}
					break;
				}

				//out_hierarchy->animList[animationIndex].tNode[currentBone][index].local = transform;
				//out_hierarchy->local.push_back(transform);
				break;
			}
			case htr_hierarchy:
			{
				std::stringstream ss(line);
				ss >> buffer[0] >> buffer[1];

				HierarchyNode currentNode;
				currentNode.name = buffer[0];

				if (buffer[1] == "GLOBAL")
				{
					currentNode.selfIndex = out_hierarchy->hierarchy->nodeList.size();
					currentNode.parentIndex = out_hierarchy->hierarchy->getNode(buffer[1]);
					out_hierarchy->hierarchy->addNode(currentNode);
					break;
				}

				if (buffer[1] == "crayfoish")
				{
					currentNode.selfIndex = out_hierarchy->hierarchy->nodeList.size() - 1;
					currentNode.parentIndex = -1;
					out_hierarchy->hierarchy->addNode(currentNode);
					break;
				}

				currentNode.selfIndex = out_hierarchy->hierarchy->nodeList.size() - 1;
				currentNode.parentIndex = out_hierarchy->hierarchy->getNode(buffer[1]);
				out_hierarchy->hierarchy->addNode(currentNode);

				break;
			}
			}
		}
	}

	NodeTransform transform;
	for (int i = 0; i < headerData->boneCount; i++)
	{
		out_hierarchy->nodePoseList->currentPose.push_back(transform);
		out_hierarchy->nodePoseList->objectSpaceBindToCurrent.push_back(transform);
	}


	fin.close();
}

