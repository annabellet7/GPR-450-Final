#pragma once
#include "hierarchyState.h"
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

namespace gorp
{
	struct HeaderData
	{
		std::string fileType;
		std::string dataType;
		std::string fileVersion;
		int boneCount;
		int numFrames;
		float frameRate;
		std::string eulerRotationOrder;
		std::string calibrationUnits;
		bool isDegrees = true;
		char globalAxisofGravity = 'y';
		char boneLengthAxis = 'y';
		float scaleFactor = 1.0f;
	};

	//Enums and strings thanks to Dan Buckstein animal3D framework
	enum fileSectionHTR
	{
		htr_file,
		htr_header,
		htr_hierarchy,
		htr_basepose,
		htr_nodepose,
		htr_eof
	};

	// known section strings
	const std::string sectionStr[] = {
		"",
		"[Header]",
		"[SegmentNames&Hierarchy]",
		"[BasePosition]",
		"",
		"[EndOfFile]"
	};

	// known section components
	const std::string headerComponents[] = {
		"FileType",
		"DataType",
		"FileVersion",
		"NumSegments",
		"NumFrames",
		"DataFrameRate",
		"EulerRotationOrder",
		"CalibrationUnits",
		"RotationUnits",
		"GlobalAxisofGravity",
		"BoneLengthAxis",
		"ScaleFactor",
	};
	enum fileHeaderComponentHTR
	{
		htr_FileType,
		htr_DataType,
		htr_FileVersion,
		htr_NumSegments,
		htr_NumFrames,
		htr_DataFrameRate,
		htr_EulerRotationOrder,
		htr_CalibrationUnits,
		htr_RotationUnits,
		htr_GlobalAxisofGravity,
		htr_BoneLengthAxis,
		htr_ScaleFactor,
	};

	void HTRLoader(HierarchyState* out_hierarchy, HeaderData headerData, const std::string resourceFilePath);
}