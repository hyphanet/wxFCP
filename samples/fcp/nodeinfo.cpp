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

// Overwrite defaults, less typing while testing
// or make it fit for your envirionment
//#define DEFAULT_FCP_PORT 9482
//#define DEFAULT_FCP_TIMEOUT 20
#include "wx/fcp/fcp.h"

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/cmdline.h>

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
        { wxCMD_LINE_SWITCH, _T("q"), _T("quiet"), _T("be quiet (don't log fcp)") },
        { wxCMD_LINE_OPTION, _T("o"), _T("fcphost"), _T("use given fcp host"),
            wxCMD_LINE_VAL_STRING },
        { wxCMD_LINE_OPTION, _T("p"), _T("fcpport"), _T("use given fcp port"),
            wxCMD_LINE_VAL_NUMBER },
        { wxCMD_LINE_OPTION, _T("t"), _T("fcptimeout"), _T("set connection timeout for fcp"),
            wxCMD_LINE_VAL_NUMBER },
        { wxCMD_LINE_NONE }
    };

    // init logging
    wxLog *logger=new wxLogStream(&std::cout);
    wxLog::SetActiveTarget(logger);

    wxCmdLineParser parser(cmdLineDesc, argc, wxArgv);
    switch ( parser.Parse(true) )
        {
        case -1:
            return 0;  // Help was shown, go away.
            break;

        case 0:
            // everything is ok; proceed
            break;

        default:
            wxLogFatalError(_T("Syntax error detected, aborting."));
            break;
    }

    wxString host;
    if ( !parser.Found(_T("o"), &host) )
    {
        if ( !wxGetEnv(_T(FCP_HOST_ENV_NAME), &host) )
        {
            host = _T(DEFAULT_FCP_HOST);
        }
    }

    long port;
    if ( !parser.Found(_T("p"), &port) )
    {
        wxString sport;
        if ( wxGetEnv(_T(FCP_PORT_ENV_NAME), &sport) )
        {
            if ( !sport.ToLong(&port) )
            {
                wxLogFatalError(_T("not a valid number"));
            }
        }
        else
        {
            port = DEFAULT_FCP_PORT;
        }
    }

    long timeout;
    if ( !parser.Found(_T("t"), &timeout) )
    {
        wxString stimeout;
        if ( wxGetEnv(_T(FCP_TIMEOUT_ENV_NAME), &stimeout) )
        {
            if ( !stimeout.ToLong(&timeout) )
            {
                wxLogFatalError(_T("not a valid number"));
            }
        }
        else
        {
            timeout = DEFAULT_FCP_TIMEOUT;
        }
    }

    // hack somewhat to get a first successfull hello

    wxFCPConnection conn = wxFCPConnection(&host, port, timeout);

    if ( !parser.Found(_T("q")) )
    {
        wxFCPSimpleLogger *fcplogger = new wxFCPSimpleLogger();
        conn.setFCPLogger(fcplogger);
    }

    conn.Connect();

    if (conn.IsConnected())
	    wxLogMessage(_T("Succeeded ! FCP Connection established (helo done)"));
    else
    {
	    wxLogMessage(_T("Can't connect/helo to the specified host"));
        return 1;
    }

    conn.sendCommand(wxFCPCommandFactory::GenerateSSK());

    wxFCPNodeMessage message = wxFCPNodeMessage();
    conn.readEndMessage(message);

    if ( !message.isMessageName(_T("SSKKeypair")) )
    {
        wxLogMessage(_T("Unexpected reply from node, generate ssk failed"));
        return 1;
    }

    wxString readkey = message.getItem(_T("RequestURI"));
    wxString writekey = message.getItem(_T("InsertURI"));

    wxLogMessage(_T("Got a keypair from node:\n  Insert URI: %s\n Request URI: %s"), writekey.c_str(), readkey.c_str());

    conn.Close(true);

    wxLogMessage(_T("Socket closed. Bye"));

    return 0;
}
