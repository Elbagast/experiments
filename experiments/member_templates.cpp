#include "member_templates.h"

template <>
void member_templates::MajorID_Manager::minorid_operation_1<member_templates::MajorID>(MinorID minorid)
{
	std::cout << "minorid_operation_1<MajorID>(MinorID)" << std::endl;
}

template <>
void member_templates::MajorID_Manager::minorid_operation_2<member_templates::MajorID>(MinorID minorid, MajorID const& value)
{
	std::cout << "minorid_operation_1<MajorID>(MinorID, MajorID const&)" << std::endl;
}

template <>
void member_templates::MajorID_Manager::minorid_operation_3<member_templates::MajorID>(MinorID minorid, int index, MajorID const& value)
{
	std::cout << "minorid_operation_1<MajorID>(MinorID, int, MajorID const&)" << std::endl;
}

template <>
void member_templates::MajorID_Manager::minorid_operation_4<member_templates::MajorID>(MinorID minorid, MajorID const& value, int index)
{
	std::cout << "minorid_operation_4<MajorID>(MinorID, MajorID const&, int)" << std::endl;
}


// Test this code section
void member_templates::test()
{
	std::cout << "Member Templates Specialisation Test" << std::endl;
	std::cout << std::endl;

	MajorID_Manager manager{};
	MajorID majorid{};
	MinorID minorid{};
	int index{ 5 };

	double type{ 0.454 };

	manager.minorid_operation_1<double>(minorid);
	manager.minorid_operation_1<MajorID>(minorid);

	manager.minorid_operation_2<double>(minorid, type);
	manager.minorid_operation_2<MajorID>(minorid, majorid);

	manager.minorid_operation_3<double>(minorid, index, type);
	manager.minorid_operation_3<MajorID>(minorid, index, majorid);

	manager.minorid_operation_4<double>(minorid, type, index);
	manager.minorid_operation_4<MajorID>(minorid, majorid, index);


	std::cout << std::endl;
}