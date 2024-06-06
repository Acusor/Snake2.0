#pragma once
#include <windows.h>
#include <cstdlib>

class Fruct
{
private:
	COORD pos;

public:
	
	void gen_fruct();
	COORD get_pos();
	void set_pos(const COORD& new_pos) {
		pos = new_pos;
	}
};

