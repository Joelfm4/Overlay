#pragma once

#include <variant>
#include <vector>

#include <imgui/imgui.h>


struct Circle {

	ImColor color;

	ImVec2 center;
	float radius;

}; // Total = 32 bytes


struct Line {

	ImColor color;

	ImVec2 p1;
	ImVec2 p2;

	float thickness;


}; // Total = 48 bytes


struct Rect {

	ImColor color;

	ImVec2 min;
	ImVec2 max;


}; // Total = 32 bytes


struct RectFilled {

	ImColor color;

	ImVec2 min;
	ImVec2 max;

}; // Total = 32 bytes


struct Text {

	ImColor color;

	ImVec2 pos;
	const char* text;
	
}; // Total = 32 bytes


using Object = std::variant<Circle, Line, Rect, RectFilled, Text>;
