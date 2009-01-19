/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fcp/ioconnection.h
// Purpose:     declaration for fcp io connections
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _FCP_IOCONNECTION_H_
#define _FCP_IOCONNECTION_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/fcp/logger.h"
#include <wx/socket.h>

class wxFCPIOConnection
{
protected:
    wxFCPIOConnection();
    ~wxFCPIOConnection();

    bool setFCPLogger(wxFCPLogger *fcplogger);
    void setTimeout(wxUint32 timeout);
    bool Connect(wxSockAddress& sockaddress);
    bool ReConnect();
    bool Close(bool flush=false);
    bool isOK();
    bool IsConnected();

    bool writeLine(const wxString& line);
    bool readLine(wxString& line);
    bool writeData(const void* buffer, wxUint32 nbytes);
    bool readData(void* buffer, wxUint32 nbytes);

private:
    wxSocketClient *m_sock;
    wxFCPLogger *m_fcplogger;
    bool write(const void* buffer, wxUint32 nbytes);
};

#endif // ifndef _FCP_IOCONNECTION_H_
