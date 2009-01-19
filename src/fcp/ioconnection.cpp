/////////////////////////////////////////////////////////////////////////////
// Name:        src/fcp/ioconnection.cpp
// Purpose:     fcp connection io classes
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "wx/fcp/ioconnection.h"

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

const char nl = '\n';

wxFCPIOConnection::wxFCPIOConnection()
{
    m_sock = new wxSocketClient(wxSOCKET_WAITALL);
    m_sock->Notify(false);
    m_fcplogger = NULL;
}

wxFCPIOConnection::~wxFCPIOConnection()
{
    delete m_sock;	
}

bool wxFCPIOConnection::Connect(wxSockAddress& sockaddress)
{
    return m_sock->Connect(sockaddress, true);
}

bool wxFCPIOConnection::IsConnected()
{
    if ( !m_sock )
        return false;
    return m_sock->IsConnected();
}

bool wxFCPIOConnection::Close(bool flush)
{
    return false;
}

bool wxFCPIOConnection::setFCPLogger(wxFCPLogger *logger)
{
//  if ( !m_fcplogger )
//  {
        m_fcplogger = logger;
        return true;
//  }
//  return false;
}

void wxFCPIOConnection::setTimeout(wxUint32 timeout)
{
    m_sock->SetTimeout(timeout);
}

bool wxFCPIOConnection::writeLine(const wxString& line)
{
    // TODO wxString::utf8_str() is since 2.8.4,
    //      invent our own convert for older versions
    const wxCharBuffer cbuf = line.utf8_str();
    if ( m_fcplogger )
        m_fcplogger->outgoingLine(line);
    write(cbuf, strlen(cbuf));
    return write(&nl, 1);
}

bool wxFCPIOConnection::readLine(wxString& line)
{
    static const int MAX_LINE_LEN = 4096;

    line.Empty();

    int n;
    for ( n = 1; n < MAX_LINE_LEN; n++ )
    {
        char c;
        m_sock->Read( &c, 1 );
        int charsread = m_sock->LastCount();

        if ( charsread == 1 )
        {
            if ( c == '\n' )
                break;
            line += c;
        }
        else if ( charsread == 0 )
        {
            if ( n == 1 )
                return false;
            else
                break;
        }
    }
    if ( m_fcplogger )
        m_fcplogger->incomingLine(line);

// TODO static wxString   FromUTF8(const char* s)
    return true;
}

bool wxFCPIOConnection::writeData(const void* buffer, wxUint32 nbytes)
{
    m_sock->Write(buffer, nbytes);

    if ( m_fcplogger )
        m_fcplogger->outgoingData(nbytes);

    return !m_sock->Error();
}

bool wxFCPIOConnection::write(const void* buffer, wxUint32 nbytes)
{
    m_sock->Write(buffer, nbytes);
    return !m_sock->Error();
}

bool wxFCPIOConnection::readData(void* buffer, wxUint32 nbytes)
{
    m_sock->Read(buffer, nbytes);
    return !m_sock->Error();
}
