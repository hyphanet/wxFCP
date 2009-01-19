/////////////////////////////////////////////////////////////////////////////
// Name:        src/fcp/connection.cpp
// Purpose:     fcp connection classes
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "wx/fcp/connection.h"

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

wxFCPConnection::wxFCPConnection(wxString *host, wxUint16 port, wxUint32 timeout, wxFCPLogger *logger) : wxFCPIOConnection()
{
#if wxUSE_IPV6
    m_sockaddress = wxIPV6address();
#else
    m_sockaddress = wxIPV4address();
#endif
    m_sockaddress.Hostname(*host);
    m_sockaddress.Service(port);
    m_timeout = timeout;
}

bool wxFCPConnection::Connect()
{
    wxFCPIOConnection::setTimeout(m_timeout);
    wxFCPIOConnection::Connect(m_sockaddress);

    wxFCPCommand *helocommand = wxFCPCommandFactory::ClientHello(_T("FüüBör"));

    sendCommand(helocommand);

    wxFCPNodeMessage *message = new wxFCPNodeMessage();
    readEndMessage(*message);

    if ( !message->isMessageName(_T("NodeHello")) )
    {
        wxLogMessage(_T("Unexpected reply from node, helo failed"));
        m_nodehellomessage = NULL;
        delete message;
        return false;
    }

    m_nodehellomessage = message;
    return true;
}

bool wxFCPConnection::Close(bool flush)
{
    return wxFCPIOConnection::Close(flush);
}

bool wxFCPConnection::readLine(wxString& line)
{
    return wxFCPIOConnection::readLine(line);
}

bool wxFCPConnection::readEndMessage(wxFCPNodeMessage& message)
{
    message.Clear();

    wxString line = wxString();
    readLine(line);
    message.setName(line);

    while ( true )
    {
    	readLine(line);
        int pos = line.Find('=');
        if (pos == wxNOT_FOUND)
        {
            message.setEndMarker(line);
            break;
        }
        else
        {
            wxString k = line.Left(pos);
            //wxLogMessage(_T("Key %s"), k.c_str());
            wxString v = line.Mid(pos+1);
            //wxLogMessage(_T("Val %s"), v.c_str());
            message.setItem(k, v);
        }
    }

    return true;
}

bool wxFCPConnection::IsConnected()
{
    if ( !wxFCPIOConnection::IsConnected() )
        return false;
    return ( m_nodehellomessage );  
}

bool wxFCPConnection::setFCPLogger(wxFCPLogger *logger)
{
    return wxFCPIOConnection::setFCPLogger(logger);
}

bool wxFCPConnection::sendCommand(wxFCPCommand *command)
{
    bool result = sendCommand(*command);
    if ( result )
        delete command;
    return result;
}

bool wxFCPConnection::sendCommand(wxFCPCommand& command)
{
    writeLine(command.getName());

    // iterate over all the items
    MessageItems::iterator it;
    for( it = command.m_items.begin(); it != command.m_items.end(); ++it )
    {
        wxString line = it->first;
        line += '=';
        line += it->second;
        writeLine(line);
    }

    writeLine(command.getEndMarker());

    return true;
}
