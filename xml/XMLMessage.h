/**
 * XMLMessage.h
 * ~~~~~~~~~~~~~~
 *
 */


#ifndef XML_MESSAGE_H
#define XML_MESSAGE_H

#include <cstdlib>
#include <iostream>

using std::string;

class XMLMessage
{
public :
	const string sAction();
	const string sMap_name();
	const string sValue();
	void parse_string(const string s);
	
private :
	string _action;
	string _map_name;
	string _value;
};


#endif	// XML_MESSAGE_H