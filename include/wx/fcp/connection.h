/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fcp/connection.h
// Purpose:     declaration for fcp connections
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _FCP_CONNECTION_H_
#define _FCP_CONNECTION_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/socket.h>

#include "wx/fcp/ioconnection.h"
#include "wx/fcp/message.h"

class wxFCPConnection : protected wxFCPIOConnection
{
public:

    wxFCPConnection(wxString *host, wxUint16 port, wxUint32 timeout, wxFCPLogger *logger=NULL);

    bool setFCPLogger(wxFCPLogger *logger);
    bool Connect();
    bool ReConnect();
    bool Close(bool flush=false);
    bool IsConnected();
    bool readLine(wxString& line);

public:
    bool readEndMessage(wxFCPNodeMessage& message);
    bool sendCommand(wxFCPCommand *command);
    bool sendCommand(wxFCPCommand& command);
private:
#if wxUSE_IPV6
    wxIPV6address m_sockaddress;
#else
    wxIPV4address m_sockaddress;
#endif
    wxUint32 m_timeout;
    wxFCPNodeMessage* m_nodehellomessage;
};

// async stuff
class wxFCPConnectionRunner : protected wxFCPConnection
{
};

#endif // ifndef _FCP_CONNECTION_H_
