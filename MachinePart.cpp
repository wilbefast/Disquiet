#include "MachinePart.hpp"

MachinePart::MachinePart(std::string str){
	type = MP_STRING;
	s = str;
}

MachinePart::MachinePart(double num){
	type = MP_NUMBER;
	n = num;
}

/*
MachinePart::MachinePart(lua_Object lobj){
	if (lua_isnumber(lobj))
		n = lua_getnumber(lobj)
		type = MP_NUMBER
	else if (lua_isstring(lobj))
		s = lua_getstring(lobj)
		type = MP_STRING
	else
		type = MP_ERROR
}
//*/