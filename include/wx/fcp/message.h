/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fcp/message.h
// Purpose:     declaration for fcp messages
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _FCP_MESSAGE_H_
#define _FCP_MESSAGE_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

WX_DECLARE_STRING_HASH_MAP( wxString, MessageItems );

class wxFCPBaseMessage
{
public:
    wxFCPBaseMessage();
    virtual ~wxFCPBaseMessage();
    wxString toString();

    virtual bool isDataCarrying()=0;

    void Clear();
    bool setName(wxString name);
    const wxString getName();
    bool setEndMarker(wxString endmarker);
    const wxString getEndMarker();
    bool setItem(const wxString key, const wxString value);
    wxString getItem(const wxString key);

public:
    wxString m_name;
    wxString m_endmarker;
    MessageItems m_items;
};

// node to client
class wxFCPNodeMessage : public wxFCPBaseMessage
{
public:
    wxFCPNodeMessage();
    bool isMessageName(const wxString name);
    virtual bool isDataCarrying();
};

// client to node
class wxFCPCommand : public wxFCPBaseMessage
{
public:
    wxFCPCommand();
    virtual bool isDataCarrying();
};

class wxFCPCommandFactory
{
public:
    static wxFCPCommand* VoidMessage();
    static wxFCPCommand* ClientHello(const wxString name);
    static wxFCPCommand* GenerateSSK();
};

#endif // ifndef _FCP_MESSAGE_H_
