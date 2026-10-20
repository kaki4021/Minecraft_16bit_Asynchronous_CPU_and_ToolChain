#pragma once

#include <string>

#define START_X 33
#define START_Y 87
#define START_Z 94
#define DX 8
#define DY -2
#define DZ 3

std::string setblock(int x, int y, int z, char b)
{
	std::string result = "";
	result += "setblock ";
	result += std::to_string(x) + " ";
	result += std::to_string(y) + " ";
	result += std::to_string(z) + " ";
	result += "minecraft:repeater[facing = west, locked = true, delay = 1, powered = ";
	result += (b == '1' ? "true" : "false");
	result += "]";

	return result;
}

std::string mcfunctions(const std::string& input)
{
	std::string result = "";

	int x = START_X;
	int y = START_Y;
	int z = START_Z;

	int yi = 0;
	int zi = 0;

	for (char i : input)
	{
		if (i == '\n')
			continue;

		result += setblock(x, y, z, i) + '\n';
		y += DY;
		yi += 1;
		if (yi == 8)
		{
			y += DY;
		}
		if (yi > 15)
		{
			result += '\n';
			y = START_Y;
			yi = 0;
			
			z += DZ;
			zi += 1;
			if (zi > 15)
			{
				z = START_Z;
				zi = 0;

				x += DX;
			}
		}
	}

	return result;
}