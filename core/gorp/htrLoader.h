#pragma once
#include "hierarchyObj.h"
#include <fstream>
#include <stdio.h>

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

void HTRLoader(HierarchyObj* root, const std::string resourceFilePath);