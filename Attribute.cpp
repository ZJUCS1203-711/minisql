#include "Attribute.h"

Attribute::Attribute(string n, int t, bool i) {
	name = n.c_str();
	type = t;
	ifUnique = i;
	index = "";

}
