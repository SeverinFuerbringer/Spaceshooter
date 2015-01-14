//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MsgBox.cpp
//////////////////////////////////////////////////

#include "MsgBox.h"

namespace se
{
char* MsgBox::IconTypeCodes[4]= { "info", "warning", "error", "question" };
char* MsgBox::DlgTypeCodes[3] = { "ok", "okcancel", "yesno" };

int MsgBox::show(std::string title, std::string msg, Icon mb_icon, Dialog mb_dlg)
{
	return tinyfd_messageDialog(title.c_str(), msg.c_str(),
		DlgTypeCodes[mb_dlg], IconTypeCodes[mb_icon]);
}
}