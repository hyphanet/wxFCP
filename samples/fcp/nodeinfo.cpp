/////////////////////////////////////////////////////////////////////////////
// Name:        samples/fcp/nodeinfo.cpp
// Purpose:     A simple demo, connect to node and print some info
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// IMPORTANT NOTE:
// This application is used more for testing rather than as sample.
// If you're looking at this file to learn how to use the wxFCP library,
// you may better use the generated api documentation instead.
 
#include "wx/cmdline.h"

#include "wx/fcp/fcp.h"

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

int main(int argc, char **argv)
{
#if !wxUSE_UNICODE
    #error The freenet node speaks UTF-8, so an UNICODE version of wxWidgets is required
#endif // !wxUSE_UNICODE

    wxChar **wxArgv = new wxChar *[argc + 1];

    {
        int n;
        for (n = 0; n < argc; n++ )
        {
            wxMB2WXbuf warg = wxConvertMB2WX(argv[n]);
            wxArgv[n] = wxStrdup(warg);
        }

        wxArgv[n] = NULL;
    }

    wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

    wxInitializer initializer;
    if ( !initializer )
    {
        fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
        return -1;
    }

    static const wxCmdLineEntryDesc cmdLineDesc[] =
    {
        { wxCMD_LINE_SWITCH, _T("h"), _T("help"), _T("show this help message"),
          wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
        { wxCMD_LINE_SWITCH, _T("v"), _T("verbose"), _T("be verbose") },
        { wxCMD_LINE_NONE }
    };

    wxCmdLineParser parser(cmdLineDesc, argc, wxArgv);
    switch ( parser.Parse() )
        {
        case -1:
            wxLogMessage(_T("Help was given, terminating."));
            break;

        case 0:
            // everything is ok; proceed
            break;

        default:
            wxLogMessage(_T("Syntax error detected, aborting."));
            break;
    }

    // do something useful here

    return 0;
}
