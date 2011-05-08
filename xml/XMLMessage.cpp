/**
 * XMLMessage.cpp
 * ~~~~~~~~~~~~~~
 *
 */


#include "XMLMessage.h"


#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


using namespace std;

/*
<action type="keypress" ctrl="0" shift="0">
	<key value="up" />
	<key value="right" />
</action>

<action type="keyrelease" ctrl="0" shift="0">
	<key value="up" />
	<key value="right" />
</action>

<action type="load_map" map_name="testmap1.xml" />
<action type="get_map_list" />
*/
	
const string XMLMessage::sAction()
{
	return _action;
}

const string XMLMessage::sMap_name()
{
	return _map_name;
}

void XMLMessage::parse_string(const string s)
{
	// reset properties
	_action = "";
	_map_name = "";
	

	TiXmlDocument doc;
	doc.Parse(s.data());
	
	if (doc.Error())
	{
		cout << "ERROR, xml_message::parse_string(), string: " << s << endl;
		return;
	}
	
	/*
	cout << "output: ";
	doc.Print();
	cout << endl;
	*/
	/*
	cout << "value of first element: ";
	cout << doc.FirstChild()->Value();
	cout << endl;
	*/
	
	
	const TiXmlElement* pElement = doc.FirstChildElement();
	
	if (pElement->ValueStr() == "action")
	{
		const TiXmlAttribute* pAttrib=pElement->FirstAttribute();
		//cout << "parsing action tag\n";
		
		while (pAttrib)
		{
			//cout << "parsing attribute: " << pAttrib->Name()
			//	<< "=\"" << pAttrib->Value() << "\"\n";
			
			if (string(pAttrib->Name()) == "type")
			{
				//cout << "setting type...\n";
				_action = pAttrib->ValueStr();
			}
			
			if (string(pAttrib->Name()) == "map_name")
				_map_name = pAttrib->ValueStr();
			
			pAttrib=pAttrib->Next();
		}
	}
};

