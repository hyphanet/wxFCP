/////////////////////////////////////////////////////////////////////////////
// Name:        src/fcp/logger.cpp
// Purpose:     fcp logger classes
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/fcp/logger.h"

void wxFCPSimpleLogger::incomingLine(const wxString& line)
{
    wxLogMessage(_T("FCP in: %s"), line.c_str());
}

void wxFCPSimpleLogger::outgoingLine(const wxString& line)
{
    wxLogMessage(_T("FCP out: %s"), line.c_str());
}

void wxFCPSimpleLogger::incomingData(const wxUint32 nbytes)
{
    wxLogMessage(_T("FCP in: <%d> bytes of data"), nbytes);
}

void wxFCPSimpleLogger::outgoingData(const wxUint32 nbytes)
{
    wxLogMessage(_T("FCP out: <%d> bytes of data"), nbytes);
}
