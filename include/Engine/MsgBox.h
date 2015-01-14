//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MsgBox.h
//////////////////////////////////////////////////

#ifndef MSGBOX_H
#define MSGBOX_H

#include "EngineExport.h"
#include "tinyfiledialogs.h"
#include <string>

namespace se
{
class SEVENGINEDLL_API MsgBox
{
public:
	// Dialog Icons
	enum Icon
	{
		Info,
		Warning,
		Error,
		Question
	};

	// Type of dialog
	enum Dialog
	{
		Ok,
		OkCancel,
		YesNo
	};

	int static show(std::string title, std::string msg,
		Icon mb_icon = Icon::Info,
		Dialog mb_dlg_type = Dialog::Ok);
private:
	static char* IconTypeCodes[4];
	static char* DlgTypeCodes[3];

	MsgBox();
	MsgBox(const MsgBox& mb);
	void operator=(const MsgBox& mb);
};
} // namespace SevEngine

#endif // MSGBOX_H
