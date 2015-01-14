/*
tinyfiledialogs.c
Unique code file of tiny file dialogs library - tinyfd
created [November 9, 2014]
Copyright (c) 2014 Guillaume Vareille http://ysengrin.com
http://tinyfiledialogs.sourceforge.net

tiny file dialogs - tinyfd - version 1.5.5 [January 7, 2015] zlib licence.
Cross-platform dialogs in C/C++ WINDOWS OSX GNOME KDE SOLARIS CONSOLE

A single C file (just add it to your project) with 5 modal function calls:
- open file dialog (and multiple files)
- save file dialog
- select folder dialog
- message and question box
- color picker.

It compiles with C and C++ compilers.
Conceived as a fully independent complement to GLUT, GLUI and SDL,
it also provides CONSOLE dialogs. THERE IS NO MAIN LOOP.

On Windows:
- native code creates the dialogs.
On UNIX it tries successive command line calls:
- zenity : part of GTK+ desktops: Gnome, Xfce, Unity, Mate, Cinnamon, Lxde
- kdialog : part of Qt desktops: Kde, Razor
- python 2 / tkinter : part of mac OSX, Solaris CDE, JDS
- dialog (console / terminal / tty mode) : part of most unix systems.
This allows the same executable to run across various desktops and distributions.

Tested on Windows, OSX, Linux, Freebsd, Illumos, Solaris.


This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.  If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*
10.01.2015 - Small modifications done by S. Fürbringer (Commented as "// S.F").
Most of this code is still written by its original Copyright holder as seen
above. I've only made small modifications to get it up and
running for Microsoft's VC++ 2013 Compiler.
*/

#ifdef WIN32
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <Windows.h>
#include <Shlobj.h>
#include <stdio.h> // S.F
#else
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h> /* on old system try <sys/dir.h> instead */
#include <unistd.h>
#include <stdlib.h> /* for freebsd */
#endif /* WIN32 */

#include "tinyfiledialogs.h" /* not needed */

#define MAX_PATH_OR_CMD 1024 /* _MAX_PATH or MAX_PATH */
#define MAX_MULTIPLE 32

int tinyfd_forceConsole = 0; /* for UNIX only: 0 (default) or 1 */
/* 1 forces all dialogs into console mode even when the X server is present */

static char * tinyfd_getPathWithoutFinalSlash(
	char * const aoDestination, /* make sure it is allocated, use _MAX_PATH */
	char const * const aSource) /* aoDestination and aSource can be the same */
{
	char const * lTmp = strrchr(aSource, (int)* "/");
	if(!lTmp)
	{
		lTmp = strrchr(aSource, (int)* "\\");
	}
	if(lTmp)
	{
		strncpy(aoDestination, aSource, lTmp - aSource);
		aoDestination[lTmp - aSource] = '\0';
	}
	else
	{
		aoDestination[0] = '\0';
	}
	return aoDestination;
}


static char * tinyfd_GetLastName(
	char * const aoDestination, /* make sure it is allocated */
	char const * const aSource)
{
	/* copy the last name after '/' or '\' */
	char const * lTmp = strrchr(aSource, (int)* "/");
	if(!lTmp)
	{
		lTmp = strrchr(aSource, (int)* "\\");
	}
	if(lTmp)
	{
		strcpy(aoDestination, lTmp + 1);
	}
	else
	{
		strcpy(aoDestination, aSource);
	}
	return aoDestination;
}


static void Hex2RGB(char const aHexRGB[8],
	unsigned char aoResultRGB[3])
{
	char lColorChannel[8];
	strcpy(lColorChannel, aHexRGB);
	aoResultRGB[2] = (unsigned char)strtoul(lColorChannel + 5, NULL, 16);
	lColorChannel[5] = '\0';
	aoResultRGB[1] = (unsigned char)strtoul(lColorChannel + 3, NULL, 16);
	lColorChannel[3] = '\0';
	aoResultRGB[0] = (unsigned char)strtoul(lColorChannel + 1, NULL, 16);
	/* printf("%d %d %d\n", aoResultRGB[0], aoResultRGB[1], aoResultRGB[2]);//*/
}

static void RGB2Hex(unsigned char const aRGB[3],
	char aoResultHexRGB[8])
{
	// S.F
	printf(aoResultHexRGB, "#%02hhx%02hhx%02hhx", aRGB[0], aRGB[1], aRGB[2]);
	/* printf("aoResultHexRGB %s\n", aoResultHexRGB); //*/
}


#ifdef WIN32


char const * tinyfd_saveFileDialog(
	char const * const aTitle, /* "" */
	char const * const aDefaultPathAndFile, /* "" */
	int const aNumOfFileFilters, /* 0 */
	char const * const * const aFileFilters) /* NULL or {"*.jpg","*.png"} */
{
	static char lBuff[MAX_PATH_OR_CMD];
	char lDirname[MAX_PATH_OR_CMD];
	char lFileFilters[MAX_PATH_OR_CMD] = "";
	char lString[MAX_PATH_OR_CMD];
	int i;
	char * p;
	OPENFILENAME ofn;

	if(!aDefaultPathAndFile)
	{
		strcpy(lDirname, "");
		strcpy(lBuff, "");
	}
	else
	{
		tinyfd_getPathWithoutFinalSlash(lDirname, aDefaultPathAndFile);
		tinyfd_GetLastName(lBuff, aDefaultPathAndFile);
	}

	if(aNumOfFileFilters > 0)
	{
		strcat(lFileFilters, aFileFilters[0]);
		for(i = 1; i < aNumOfFileFilters; i++)
		{
			strcat(lFileFilters, ";");
			strcat(lFileFilters, aFileFilters[i]);
		}
		strcat(lFileFilters, "\n");
		strcpy(lString, lFileFilters);
		strcat(lFileFilters, lString);
		strcat(lFileFilters, "All Files\n*.*\n");
		p = lFileFilters;
		while((p = strchr(p, '\n')) != NULL)
		{
			*p = '\0';
			p++;
		}
	}

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = 0;
	ofn.hInstance = 0;
	ofn.lpstrFilter = (LPCWSTR)lFileFilters; // S.F
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = (LPWSTR)lBuff; // S.F
	ofn.nMaxFile = MAX_PATH_OR_CMD;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir = (LPCWSTR)lDirname; // S.F
	ofn.lpstrTitle = (LPCWSTR)aTitle; // S.F
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

	if(GetSaveFileName(&ofn) == 0)
	{
		return NULL;
	}
	else
	{
		return lBuff;
	}
}


/* in case of multiple files, the separator is | */
char const * tinyfd_openFileDialog(
	char const * const aTitle, /* "" */
	char const * const aDefaultPathAndFile, /* "" */
	int const aNumOfFileFilters, /* 0 */
	char const * const * const aFileFilters, /* NULL or {"*.jpg","*.png"} */
	int aAllowMultipleSelects) /* 0 or 1 */
{
	static char lBuff[MAX_MULTIPLE * MAX_PATH_OR_CMD];
	char lDirname[MAX_PATH_OR_CMD];
	char lFileFilters[MAX_PATH_OR_CMD] = "";
	char lTempString[MAX_PATH_OR_CMD];
	char * lPointers[MAX_MULTIPLE];
	size_t lLengths[MAX_MULTIPLE];
	int i, j;
	char * p;
	OPENFILENAME ofn;
	size_t lBuffLen;

	if(!aDefaultPathAndFile)
	{
		strcpy(lDirname, "");
		strcpy(lBuff, "");
	}
	else
	{
		tinyfd_getPathWithoutFinalSlash(lDirname, aDefaultPathAndFile);
		tinyfd_GetLastName(lBuff, aDefaultPathAndFile);
	}

	if(aNumOfFileFilters > 0)
	{
		strcat(lFileFilters, aFileFilters[0]);
		for(i = 1; i < aNumOfFileFilters; i++)
		{
			strcat(lFileFilters, ";");
			strcat(lFileFilters, aFileFilters[i]);
		}
		strcat(lFileFilters, "\n");
		strcpy(lTempString, lFileFilters);
		strcat(lFileFilters, lTempString);
		strcat(lFileFilters, "All Files\n*.*\n");
		p = lFileFilters;
		while((p = strchr(p, '\n')) != NULL)
		{
			*p = '\0';
			p++;
		}
	}

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = 0;
	ofn.hInstance = 0;
	ofn.lpstrFilter = (LPCWSTR)lFileFilters;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = (LPWSTR)lBuff; // S.F
	ofn.nMaxFile = MAX_PATH_OR_CMD;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir = (LPCWSTR)lDirname; // S.F
	ofn.lpstrTitle = (LPCWSTR)aTitle;
	ofn.Flags = OFN_EXPLORER; 
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

	if(aAllowMultipleSelects)
	{
		ofn.Flags |= OFN_ALLOWMULTISELECT;
	}

	if(GetOpenFileName(&ofn) == 0)
	{
		return NULL;
	}
	else
	{
		lBuffLen = strlen(lBuff);
		lPointers[0] = lBuff + lBuffLen + 1;
		if(!aAllowMultipleSelects || (lPointers[0][0] == '\0'))
			return lBuff;

		i = 0;
		do
		{
			lLengths[i] = strlen(lPointers[i]);
			lPointers[i + 1] = lPointers[i] + lLengths[i] + 1;
			i++;
		} while(lPointers[i][0] != '\0');
		i--;
		p = lBuff + sizeof(lBuff) - 1;
		*p = '\0';
		for(j = i; j >= 0; j--)
		{
			p -= lLengths[j];
			memcpy(p, lPointers[j], lLengths[j]);
			p--;
			*p = '\\';
			p -= lBuffLen;
			memcpy(p, lBuff, lBuffLen);
			p--;
			*p = '|';
		}
		p++;
		return p;
	}
}


char const * tinyfd_selectFolderDialog(
	char const * const aTitle, /* "" */
	char const * const aDefaultPath) /* "" */
{
	static char lBuff[MAX_PATH_OR_CMD];
	BROWSEINFO bInfo;
	LPITEMIDLIST lpItem;

	bInfo.hwndOwner = 0;
	bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = (LPWSTR)lBuff; // S.F
	bInfo.lpszTitle = (LPCWSTR)aTitle; // S.F
	bInfo.ulFlags = 0;
	bInfo.lpfn = NULL;
	bInfo.lParam = 0;
	bInfo.iImage = -1;

	lpItem = SHBrowseForFolder(&bInfo);
	if(lpItem)
	{									// S.F
		SHGetPathFromIDList(lpItem, (LPWSTR)lBuff);
	}

	return lBuff;
}


/* returns 0 for cancel/no , 1 for ok/yes */
int tinyfd_messageDialog(
	char const * const aTitle, /* "" */
	char const * const aMessage, /* "" */ /* may contain \n and \t */
	char const * const aDialogType, /* "ok" "okcancel" "yesno" */
	char const * const aIconType) /* "info" "warning" "error" "question" */
{
	int lBoxReturnValue;
	UINT aCode;

	if(!strcmp("warning", aIconType))
	{
		aCode = MB_ICONWARNING;
	}
	else if(!strcmp("error", aIconType))
	{
		aCode = MB_ICONERROR;
	}
	else if(!strcmp("question", aIconType))
	{
		aCode = MB_ICONQUESTION;
	}
	else
	{
		aCode = MB_ICONINFORMATION;
	}

	if(!strcmp("okcancel", aDialogType))
	{
		aCode += MB_OKCANCEL;
	}
	else if(!strcmp("yesno", aDialogType))
	{
		aCode += MB_YESNO;
	}
	else
	{
		aCode += MB_OK;
	}
	// S.F
	// Changed MessageBox to MessageBoxA
	lBoxReturnValue = MessageBoxA(NULL, aMessage, aTitle, aCode);
	if((!strcmp("ok", aDialogType))
		|| (lBoxReturnValue == IDOK)
		|| (lBoxReturnValue == IDYES))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/* returns the hexcolor as a string "#FF0000" */
/* aoResultRGB also contains the result */
/* aDefaultRGB is used only if aDefaultHexRGB is NULL */
/* aDefaultRGB and aoResultRGB can be the same array */
char const * tinyfd_colorChooser(
	char const * const aTitle, /* "" */
	char const * const aDefaultHexRGB, /* NULL or "#FF0000"*/
	unsigned char aDefaultRGB[3], /* { 0 , 255 , 255 } */
	unsigned char aoResultRGB[3]) /* { 0 , 0 , 0 } */
{
	static CHOOSECOLOR cc;
	static COLORREF crCustColors[16];
	static char lResultHexRGB[8];
	int lRet;

	if(aDefaultHexRGB)
	{
		Hex2RGB(aDefaultHexRGB, aDefaultRGB);
	}

	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = NULL;
	cc.hInstance = NULL;
	cc.rgbResult = RGB(aDefaultRGB[0], aDefaultRGB[1], aDefaultRGB[2]);
	cc.lpCustColors = crCustColors;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData = 0;
	cc.lpfnHook = NULL;
	cc.lpTemplateName = NULL;

	lRet = ChooseColor(&cc);

	if(!lRet)
	{
		return NULL;
	}

	aoResultRGB[0] = GetRValue(cc.rgbResult);
	aoResultRGB[1] = GetGValue(cc.rgbResult);
	aoResultRGB[2] = GetBValue(cc.rgbResult);

	RGB2Hex(aoResultRGB, lResultHexRGB);

	return lResultHexRGB;
}


#else /* unix */

static char gPython2Name[16];

static char gTitle[] = "missing software !" ;

static char gMessage[] = "tiny file dialogs on UNIX needs\n\t\
						 zenity (version 3 for the color chooser)\nor\tkdialog\nor\t\
						 python 2 with tkinter\nor\tdialog (display in console)\n" ;

static int graphicMode()
{
	return ( ! tinyfd_forceConsole ) && getenv ( "DISPLAY" ) ;
}


static int detectPresence ( char const * const aExecutable )
{
	FILE * lIn ;
	char lBuff [ MAX_PATH_OR_CMD ] ;
	char lTestedString [ MAX_PATH_OR_CMD ] = "which " ;
	strcat ( lTestedString , aExecutable ) ;
	lIn = popen ( lTestedString , "r" ) ;
	if ( ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
		&& ( ! strchr ( lBuff , ':' ) ) )
	{	/* present */
		pclose ( lIn ) ;
		return 1 ;
	}
	else
	{
		pclose ( lIn ) ;
		return 0 ;
	}
}


static int tryCommand ( char const * const aCommand )
{
	char lBuff [ MAX_PATH_OR_CMD ] ;
	FILE * lIn = popen ( aCommand , "r" ) ;
	if ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) == NULL )
	{	/* present */
		pclose ( lIn ) ;
		return 1 ;
	}
	else
	{
		pclose ( lIn ) ;
		return 0 ;
	}
}


static int whiptailPresent ( )
{
	static int lWhiptailPresent = -1 ;
	if ( lWhiptailPresent < 0 )
	{
		lWhiptailPresent = detectPresence ( "whiptail" ) ;
	}
	return lWhiptailPresent && isatty ( 1 ) ; /* verify console presence */
}


static int dialogPresent ( )
{
	static int lDialogPresent = -1 ;
	if ( lDialogPresent < 0 )
	{
		lDialogPresent = detectPresence ( "dialog" ) ;
	}
	return lDialogPresent && isatty ( 1 ) ; /* verify console presence */
}


static int xmessagePresent ( )
{
	static int lXmessagePresent = -1 ;
	if ( lXmessagePresent < 0 )
	{
		lXmessagePresent = detectPresence("xmessage") ;
	}
	return lXmessagePresent && graphicMode ( ) ;
}


static int notifysendPresent ( )
{
	static int lNotifysendPresent = -1 ;
	if ( lNotifysendPresent < 0 )
	{
		lNotifysendPresent = detectPresence("notify-send") ;
	}
	return lNotifysendPresent && graphicMode ( ) ;
}


static int kdialogPresent ( )
{
	static int lKdialogPresent = -1 ;
	if ( lKdialogPresent < 0 )
	{
		lKdialogPresent = detectPresence("kdialog") ;
	}
	return lKdialogPresent && graphicMode ( ) ;
}


static int zenityPresent ( )
{
	static int lZenityPresent = -1 ;
	if ( lZenityPresent < 0 )
	{
		lZenityPresent = detectPresence("zenity") ;
	}
	return lZenityPresent && graphicMode ( ) ;
}


static int zenity3Present ( )
{
	static int lZenity3Present = -1 ;
	char lBuff [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;

	if ( lZenity3Present < 0 )
	{
		if ( ! zenityPresent() )
		{
			lZenity3Present = 0 ;
		}
		else
		{
			lIn = popen ( "zenity --version" , "r" ) ;
			if ( ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
				&& ( atoi(lBuff) >= 3 )
				&& ( atoi(strtok(lBuff,".")+1) >= 0 ) )
			{
				lZenity3Present = 1 ;
			}
			else
			{
				lZenity3Present = 0 ;
			}
			pclose ( lIn ) ;
		}
	}
	return lZenity3Present && graphicMode ( ) ;
}


static int tkinter2Present ( )
{
	static int lTkinter2Present = -1 ;
	char lPythonCommand[256];
	char lPythonParams[256] = "-c \"try:\n\timport Tkinter;\nexcept:\n\tprint(0);\"";
	int i;

	if ( lTkinter2Present < 0 )
	{
		strcpy(gPython2Name , "python" ) ;
		sprintf ( lPythonCommand , "%s %s" , gPython2Name , lPythonParams ) ;
		lTkinter2Present = tryCommand(lPythonCommand);		
		if ( ! lTkinter2Present )
		{
			strcpy(gPython2Name , "python2" ) ;
			sprintf ( lPythonCommand , "%s %s" , gPython2Name , lPythonParams ) ;
			lTkinter2Present = detectPresence(gPython2Name) && tryCommand(lPythonCommand);
		}
		if ( ! lTkinter2Present )
		{
			for ( i = 9 ; i >= 0 ; i -- )
			{
				sprintf ( gPython2Name , "python2.%d" , i ) ;
				sprintf ( lPythonCommand , "%s %s" , gPython2Name , lPythonParams ) ;
				lTkinter2Present = detectPresence(gPython2Name) && tryCommand(lPythonCommand);
				if ( lTkinter2Present )
				{
					break ;
				}
			}
		}
	}
	/* printf ("gPython2Name %s\n", gPython2Name) ; //*/
	return lTkinter2Present && graphicMode ( ) ;
}


static void replaceSubStr ( char const * const aSource ,
	char const * const aOldSubStr ,
	char const * const aNewSubStr ,
	char * const aoDestination )
{
	char const * pOccurence ;
	char const * p = aSource ;
	int lOldSubLen = strlen ( aOldSubStr ) ;
	* aoDestination = '\0' ;
	while ( ( pOccurence = strstr ( p , aOldSubStr ) ) != NULL )
	{
		strncat ( aoDestination , p , pOccurence - p ) ;
		strcat ( aoDestination , aNewSubStr ) ;
		p = pOccurence + lOldSubLen ;
	}
	strcat ( aoDestination , p ) ;
}


char const * tinyfd_saveFileDialog (
	char const * const aTitle , /* "" */
	char const * const aDefaultPathAndFile , /* "" */
	int const aNumOfFileFilters , /* 0 */
	char const * const * const aFileFilters ) /* NULL or {"*.jpg","*.png"} */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lString [ MAX_PATH_OR_CMD ] ;
	int i ;
	DIR * lDir ;
	FILE * lIn ;
	lBuff[0]='\0';

	if ( zenityPresent() )
	{
		strcpy ( lDialogString ,
			"zenity --file-selection --save --confirm-overwrite" ) ;

		if ( strlen(aTitle) ) 
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}

		if ( strlen(aDefaultPathAndFile) ) 
		{
			strcat(lDialogString, " --filename=\"") ;
			strcat(lDialogString, aDefaultPathAndFile) ;
			strcat(lDialogString, "\"") ;
		}

		if ( aNumOfFileFilters > 0 )
		{
			strcat ( lDialogString , " --file-filter='" ) ;
			for ( i = 0 ; i < aNumOfFileFilters ; i ++ )
			{
				strcat ( lDialogString , aFileFilters [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			strcat ( lDialogString , "' --file-filter='All files | *'" ) ;
		}
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --getsavefilename" ) ;
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " \"") ;
			strcat(lDialogString, aDefaultPathAndFile ) ;
			strcat(lDialogString , "\"" ) ;
		}
		else
		{
			strcat(lDialogString, " :" ) ;
		}
		if ( aNumOfFileFilters > 0 )
		{
			strcat(lDialogString , " \"" ) ;
			for ( i = 0 ; i < aNumOfFileFilters ; i ++ )
			{
				strcat ( lDialogString , aFileFilters [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			strcat ( lDialogString , "\"" ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) )
		{
			strcat ( lDialogString , " -i" ) ; /* for osx without console */
		}
		strcat ( lDialogString ,
			" -c \"import Tkinter,tkFileDialog;root=Tkinter.Tk();root.withdraw();");

#if defined( __APPLE__ )
		strcat ( lDialogString ,
			"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
			frontmost of process \\\"Python\\\" to true' ''');");
#endif /* __APPLE__ */

		strcat ( lDialogString , "print tkFileDialog.asksaveasfilename(");
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			tinyfd_getPathWithoutFinalSlash ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialdir='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
			tinyfd_GetLastName ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialfile='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
		}
		if ( ( aNumOfFileFilters > 1 )
			|| ( ( aNumOfFileFilters == 1 )  /* test because poor osx behaviour */
			&& ( aFileFilters[0][strlen(aFileFilters[0])-1] != '*' ) ) )
		{
			strcat(lDialogString , "filetypes=(" ) ;
			for ( i = 0 ; i < aNumOfFileFilters ; i ++ )
			{
				strcat ( lDialogString , "('','" ) ;
				strcat ( lDialogString , aFileFilters [ i ] ) ;
				strcat ( lDialogString , "')," ) ;
			}
			strcat ( lDialogString , "('All files','*'))" ) ;
		}
		strcat ( lDialogString , ")\"" ) ;
	}
	else if ( dialogPresent ( ) )
	{
		strcpy ( lDialogString , "(dialog " ) ;
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString , "--fselect \"" ) ;
		if ( strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, aDefaultPathAndFile) ;
		}
		strcat(lDialogString, "\" 0 0 >/dev/tty) 2>&1 ; echo >/dev/tty") ;
	}
	else
	{
		tinyfd_messageDialog (gTitle, gMessage,"ok","error" ) ;
		return NULL ;
	}
	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	tinyfd_getPathWithoutFinalSlash ( lString , lBuff ) ;
	if ( strlen ( lString ) > 0 )
	{
		lDir = opendir ( lString ) ;
		if ( ! lDir )
		{
			return NULL ;
		}
		closedir ( lDir ) ;
	}
	return lBuff ;
}


/* in case of multiple files, the separator is | */
char const * tinyfd_openFileDialog (
	char const * const aTitle , /* "" */
	char const * const aDefaultPathAndFile , /* "" */
	int const aNumOfFileFilters , /* 0 */
	char const * const * const aFileFilters , /* NULL or {"*.jpg","*.png"} */
	int aAllowMultipleSelects ) /* 0 or 1 */
{
	static char lBuff [ MAX_MULTIPLE * MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lString [ MAX_PATH_OR_CMD ] ;
	int i ;
	FILE * lIn ;
	char * p ;
	lBuff[0]='\0';

	if ( zenityPresent() )
	{
		strcpy ( lDialogString ,"zenity --file-selection" ) ;
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , " --multiple" ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " --filename=\"") ;
			strcat(lDialogString, aDefaultPathAndFile) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aNumOfFileFilters > 0 )
		{
			strcat ( lDialogString , " --file-filter='" ) ; 
			for ( i = 0 ; i < aNumOfFileFilters ; i ++ )
			{
				strcat ( lDialogString , aFileFilters [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			strcat ( lDialogString , "' --file-filter='All files | *'" ) ;
		}
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --getopenfilename" ) ;
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " \"") ;
			strcat(lDialogString, aDefaultPathAndFile ) ;
			strcat(lDialogString , "\"" ) ;
		}
		else
		{
			strcat(lDialogString, " :" ) ;
		}
		if ( aNumOfFileFilters > 0 )
		{
			strcat(lDialogString , " \"" ) ;
			for ( i = 0 ; i < aNumOfFileFilters ; i ++ )
			{
				strcat ( lDialogString , aFileFilters [ i ] ) ;

				strcat ( lDialogString , " " ) ;
			}
			strcat ( lDialogString , "\"" ) ;
		}
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , " --multiple --separate-output" ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) )
		{
			strcat ( lDialogString , " -i" ) ; /* for osx without console */
		}
		strcat ( lDialogString ,
			" -c \"import Tkinter,tkFileDialog;root=Tkinter.Tk();root.withdraw();");

#if defined( __APPLE__ )
		strcat ( lDialogString ,
			"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
			frontmost of process \\\"Python\\\" to true' ''');");
#endif /* __APPLE__ */

		strcat ( lDialogString , "lFiles=tkFileDialog.askopenfilename(");
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , "multiple=1," ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			tinyfd_getPathWithoutFinalSlash ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialdir='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
			tinyfd_GetLastName ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialfile='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
		}
		if ( ( aNumOfFileFilters > 1 )
			|| ( ( aNumOfFileFilters == 1 ) /* test because poor osx behaviour */
			&& ( aFileFilters[0][strlen(aFileFilters[0])-1] != '*' ) ) )
		{
			strcat(lDialogString , "filetypes=(" ) ;
			for ( i = 0 ; i < aNumOfFileFilters ; i ++ )
			{
				strcat ( lDialogString , "('','" ) ;
				strcat ( lDialogString , aFileFilters [ i ] ) ;
				strcat ( lDialogString , "')," ) ;
			}
			strcat ( lDialogString , "('All files','*'))" ) ;
		}
		strcat ( lDialogString , ");\
								 \nif not isinstance(lFiles, tuple):\n\tprint lFiles\nelse:\
								 \n\tlFilesString=''\n\tfor lFile in lFiles:\n\t\tlFilesString+=str(lFile)+'|'\
								 \n\tprint lFilesString[:-1]\n\"" ) ;
	}
	else if ( dialogPresent ( ) )
	{
		strcpy ( lDialogString , "(dialog " ) ;
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString , "--fselect \"" ) ;
		if ( strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, aDefaultPathAndFile) ;
		}
		strcat(lDialogString, "\" 0 0  >/dev/tty) 2>&1 ; echo >/dev/tty") ;
	}
	else
	{
		tinyfd_messageDialog (gTitle, gMessage,"ok","error" ) ;
		return NULL ;
	}
	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	lBuff[0]='\0';
	p=lBuff;
	while ( fgets ( p , sizeof ( lBuff ) , lIn ) != NULL )
	{
		p += strlen ( p );
	}
	pclose ( lIn ) ;
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	if ( aAllowMultipleSelects && kdialogPresent() )
	{
		p = lBuff ;
		while ( ( p = strchr ( p , '\n' ) ) )
			* p = '|' ;
	}
	/* printf ( "lBuff2: %s\n" , lBuff ) ; //*/
	if ( ! aAllowMultipleSelects )
	{
		lIn = fopen( lBuff , "r" ) ;
		if ( ! lIn )
		{
			return NULL ;
		}
		fclose ( lIn ) ;
	}
	/* printf ( "lBuff3: %s\n" , lBuff ) ; //*/
	return lBuff ;
}


char const * tinyfd_selectFolderDialog (
	char const * const aTitle , /* "" */
	char const * const aDefaultPath ) /* "" */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	DIR * lDir ;
	FILE * lIn ;
	lBuff[0]='\0';

	if ( zenityPresent() )
	{
		strcpy ( lDialogString , "zenity --file-selection --directory" ) ;
		if ( strlen(aTitle) ) 
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( strlen(aDefaultPath) ) 
		{
			strcat(lDialogString, " --filename=\"") ;
			strcat(lDialogString, aDefaultPath) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --getexistingdirectory" ) ;
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
			strcat(lDialogString, " \"") ;
			strcat(lDialogString, aDefaultPath ) ;
			strcat(lDialogString , "\"" ) ;
		}
		else
		{
			strcat(lDialogString, " :" ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) )
		{
			strcat ( lDialogString , " -i" ) ; /* for osx without console */
		}
		strcat ( lDialogString ,
			" -c \"import Tkinter,tkFileDialog;root=Tkinter.Tk();root.withdraw();");

#if defined( __APPLE__ )
		strcat ( lDialogString ,
			"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
			frontmost of process \\\"Python\\\" to true' ''');");
#endif /* __APPLE__ */

		strcat ( lDialogString , "print tkFileDialog.askdirectory(");
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
			strcat(lDialogString, "initialdir='") ;
			strcat(lDialogString, aDefaultPath ) ;
			strcat(lDialogString , "'" ) ;
		}
		strcat ( lDialogString , ")\"" ) ;
	}
	else if ( dialogPresent ( ) )
	{
		strcpy ( lDialogString , "(dialog " ) ;
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString , "--dselect \"" ) ;
		if ( strlen(aDefaultPath) )
		{
			strcat(lDialogString, aDefaultPath) ;
		}
		strcat(lDialogString, "\" 0 0 >/dev/tty) 2>&1 ; echo >/dev/tty") ;
	}
	else
	{
		tinyfd_messageDialog (gTitle, gMessage,"ok","error" ) ;
		return NULL ;
	}
	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	if ( strlen ( lBuff ) > 0 )
	{
		lDir = opendir ( lBuff ) ;
		if ( ! lDir )
		{
			return NULL ;
		}
		closedir ( lDir ) ;
	}
	return lBuff ;
}


/* returns 0 for cancel/no , 1 for ok/yes */
int tinyfd_messageDialog (
	char const * const aTitle , /* "" */
	char const * const aMessage , /* "" */ /* may contain \n and \t */
	char const * const aDialogType , /* "ok" "okcancel" "yesno"*/
	char const * const aIconType ) /* "info" "warning" "error" "question" */
{
	char lBuff [ MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;
	int lResult ;
	lBuff[0]='\0';

	if ( zenityPresent() )
	{
		strcpy ( lDialogString , "zenity --" ) ;
		if ( ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString ,
				"question --ok-label=Ok --cancel-label=Cancel" ) ;
		}
		else if ( ! strcmp( "yesno" , aDialogType ) )
		{
			strcat ( lDialogString , "question" ) ;
		}
		else if ( ! strcmp( "error" , aIconType ) )
		{
			strcat ( lDialogString , "error" ) ;
		}
		else if ( ! strcmp( "warning" , aIconType ) )
		{
			strcat ( lDialogString , "warning" ) ;
		}
		else
		{
			strcat ( lDialogString , "info" ) ;
		}
		if ( strlen(aTitle) ) 
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( strlen(aMessage) ) 
		{
			strcat(lDialogString, " --text=\"") ;
			strcat(lDialogString, aMessage) ;
			strcat(lDialogString, "\"") ;
		}
		if ( zenity3Present ( ) )
		{
			strcat ( lDialogString , " --icon-name=dialog-" ) ;
			if ( ! strcmp( "question" , aIconType )
				|| ! strcmp( "error" , aIconType )
				|| ! strcmp( "warning" , aIconType ) )
			{
				strcat ( lDialogString , aIconType ) ;
			}
			else
			{
				strcat ( lDialogString , "info" ) ;
			}
		}
		strcat ( lDialogString , ";echo $?" ) ;
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --" ) ;
		if ( ( ! strcmp( "okcancel" , aDialogType ) )
			|| ( ! strcmp( "yesno" , aDialogType ) ) )
		{
			if ( ( ! strcmp( "warning" , aIconType ) )
				|| ( ! strcmp( "error" , aIconType ) ) )
			{
				strcat ( lDialogString , "warning" ) ;
			}
			strcat ( lDialogString , "yesno" ) ;
		}
		else if ( ! strcmp( "error" , aIconType ) )
		{
			strcat ( lDialogString , "error" ) ;
		}
		else if ( ! strcmp( "warning" , aIconType ) )
		{
			strcat ( lDialogString , "sorry" ) ;
		}
		else
		{
			strcat ( lDialogString , "msgbox" ) ;
		}
		strcat ( lDialogString , " \"" ) ;
		if ( aMessage )
		{
			strcat ( lDialogString , aMessage ) ;
		}
		strcat ( lDialogString , "\"" ) ;
		if ( ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString ,
				" --yes-label Ok --no-label Cancel" ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		strcat ( lDialogString , ";echo $?" ) ;
	}
	else if ( tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}

		strcat ( lDialogString ,
			" -c \"import Tkinter,tkMessageBox;root=Tkinter.Tk();root.withdraw();");

#if defined( __APPLE__ )
		strcat ( lDialogString ,
			"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
			frontmost of process \\\"Python\\\" to true' ''');");
#endif /* __APPLE__ */

		strcat ( lDialogString ,"res=tkMessageBox." ) ;
		if ( ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString , "askokcancel" ) ;
		}
		else if ( ! strcmp( "yesno" , aDialogType ) )
		{
			strcat ( lDialogString , "askyesno" ) ;
		}
		else
		{
			strcat ( lDialogString , "showinfo" ) ;
		}
		strcat ( lDialogString , "(icon='" ) ;
		if ( ! strcmp( "question" , aIconType )
			|| ! strcmp( "error" , aIconType )
			|| ! strcmp( "warning" , aIconType ) )
		{
			strcat ( lDialogString , aIconType ) ;
		}
		else
		{
			strcat ( lDialogString , "info" ) ;
		}
		strcat(lDialogString, "',") ;
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( strlen(aMessage) )
		{
			replaceSubStr ( aMessage , "\n" , "\\n" , lBuff ) ;
			strcat(lDialogString, "message='") ;
			strcat(lDialogString, lBuff) ;
			strcat(lDialogString, "'") ;
			lBuff[0]='\0';
		}
		strcat(lDialogString, ");\n\
							  if res==False :\n\tprint 1\n\
							  else :\n\tprint 0\n\"" ) ;
	}
	else if ( dialogPresent ( ) || whiptailPresent ( ) )
	{
		if ( dialogPresent ( ) )
		{
			strcpy ( lDialogString , "(dialog " ) ;
		}
		else
		{
			strcpy ( lDialogString , "(whiptail " ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		if ( ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString , "--yes-label \"Ok\" --no-label \"No\" --yesno " ) ;
		}
		else if ( ! strcmp( "yesno" , aDialogType ) )
		{
			strcat ( lDialogString , "--yesno" ) ;
		}
		else
		{
			strcat ( lDialogString , "--msgbox" ) ;
		}
		strcat ( lDialogString , " \"" ) ;
		if ( strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}
		strcat(lDialogString,
			"\" 0 0 >/dev/tty) 2>&1 ; ( echo $? ) 2>&1 ; echo >/dev/tty") ;
	}
	else if ( notifysendPresent ( ) )
	{
		strcpy ( lDialogString , "notify-send \"" ) ;
		strcat(lDialogString, gTitle) ;
		strcat ( lDialogString , "\n" ) ;
		strcat(lDialogString, gMessage) ;
		strcat ( lDialogString , "\"" ) ;
	}
	else if ( xmessagePresent ( ) )
	{
		strcpy ( lDialogString , "xmessage -center \"");
		strcat(lDialogString, gTitle) ;
		strcat ( lDialogString , "\n" ) ;
		strcat(lDialogString, gMessage) ;
		strcat ( lDialogString , "\"" ) ;
	}
	else
	{
		printf ("\n%s\n\n", gTitle);
		printf ("%s\n", gMessage);
		return 0 ;
	}

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return 0 ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	/* printf ( "lBuff: %s len: %d \n" , lBuff , strlen(lBuff) ) ; //*/
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff1: %s len: %d \n" , lBuff , strlen(lBuff) ) ; //*/
	lResult =  strcmp ( lBuff , "0" ) ? 0 : 1 ;
	/* printf ( "lResult: %d\n" , lResult ) ; //*/
	return lResult ;
}


/* returns the hexcolor as a string "#FF0000" */
/* aoResultRGB also contains the result */
/* aDefaultRGB is used only if aDefaultHexRGB is NULL */
/* aDefaultRGB and aoResultRGB can be the same array */
char const * tinyfd_colorChooser(
	char const * const aTitle , /* "" */
	char const * const aDefaultHexRGB , /* NULL or "#FF0000"*/
	unsigned char aDefaultRGB[3] , /* { 0 , 255 , 255 } */
	unsigned char aoResultRGB[3] ) /* { 0 , 0 , 0 } */
{
	static char lBuff [ 16 ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lDefaultHexRGB[8];
	char * lpDefaultHexRGB;
	FILE * lIn ;

	lBuff[0]='\0';

	if ( aDefaultHexRGB )
	{
		Hex2RGB ( aDefaultHexRGB , aDefaultRGB ) ;
		lpDefaultHexRGB = (char *) aDefaultHexRGB ;
	}
	else
	{
		RGB2Hex( aDefaultRGB , lDefaultHexRGB ) ;
		lpDefaultHexRGB = (char *) lDefaultHexRGB ;
	}

	if ( zenity3Present() )
	{
		sprintf ( lDialogString ,
			"zenity --color-selection --show-palette --color=%s" , lpDefaultHexRGB ) ;
		if ( strlen(aTitle) ) 
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( kdialogPresent() )
	{
		sprintf ( lDialogString ,
			"kdialog --getcolor --default '%s'" , lpDefaultHexRGB ) ;
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}

		strcat ( lDialogString ,
			" -c \"import Tkinter,tkColorChooser;root=Tkinter.Tk();root.withdraw();");

#if defined( __APPLE__ )
		strcat ( lDialogString ,
			"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
			frontmost of process \\\"Python\\\" to true' ''');");
#endif /* __APPLE__ */

		strcat ( lDialogString , "res=tkColorChooser.askcolor(color='" ) ;
		strcat(lDialogString, lpDefaultHexRGB ) ;
		strcat(lDialogString, "'") ;
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, ",title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "'") ;
		}
		strcat ( lDialogString , ");\
								 \nif res[1] is not None:\n\tprint res[1]\"" ) ;
	}
	else if ( dialogPresent ( ) || whiptailPresent ( ) )
	{
		if ( dialogPresent ( ) )
		{
			strcpy ( lDialogString , "(dialog " ) ;
		}
		else
		{
			strcpy ( lDialogString , "(whiptail " ) ;
		}
		if ( strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString ,
			"--inputbox \"Enter hex rgb color\nie: #f5ca20\" 0 0 \"" ) ;
		strcat(lDialogString, lpDefaultHexRGB) ;
		strcat(lDialogString, "\" >/dev/tty) 2>&1 ; echo >/dev/tty") ;
	}
	else
	{
		tinyfd_messageDialog (gTitle, gMessage,"ok","error" ) ;
		return NULL ;
	}
	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{
	}
	pclose ( lIn ) ;
	if ( ! strlen ( lBuff ) )
	{
		return NULL ;
	}
	/* printf ( "lBuff0: %s\n" , lBuff ) ; //*/
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	if ( zenity3Present ( ) )
	{
		lBuff[3]=lBuff[5];
		lBuff[4]=lBuff[6];
		lBuff[5]=lBuff[9];
		lBuff[6]=lBuff[10];
		lBuff[7]='\0';
	}
	Hex2RGB(lBuff,aoResultRGB);
	/* printf("%d %d %d\n", aoResultRGB[0],aoResultRGB[1],aoResultRGB[2]); //*/
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	return lBuff ;
}


#endif /* WIN32 */

