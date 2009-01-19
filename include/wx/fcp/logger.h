/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fcp/logger.h
// Purpose:     declaration for fcp logger
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _FCP_LOGGER_H_
#define _FCP_LOGGER_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class wxFCPLogger
{
public:
    wxFCPLogger() {};
    virtual ~wxFCPLogger() {};

    virtual void incomingLine(const wxString& line)=0;
    virtual void outgoingLine(const wxString& line)=0;
    virtual void incomingData(const wxUint32 nbytes)=0;
    virtual void outgoingData(const wxUint32 nbytes)=0;
};

class wxFCPNullLogger : public wxFCPLogger
{
public:
    virtual void incomingLine(const wxString& WXUNUSED(line)) { }
    virtual void outgoingLine(const wxString& WXUNUSED(line)) { }
    virtual void incomingData(const wxUint32 WXUNUSED(nbytes)) { }
    virtual void outgoingData(const wxUint32 WXUNUSED(nbytes)) { }
};

class wxFCPSimpleLogger : public wxFCPLogger
{
public:
    virtual void incomingLine(const wxString& line);
    virtual void outgoingLine(const wxString& line);
    virtual void incomingData(const wxUint32 nbytes);
    virtual void outgoingData(const wxUint32 nbytes);
};

#endif // ifndef _FCP_LOGGER_H_
