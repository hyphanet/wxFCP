/////////////////////////////////////////////////////////////////////////////
// Name:        src/fcp/message.cpp
// Purpose:     fcp message classes
// Author:      saces
// Modified by:
// Created:     16.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/fcp/message.h"

#define NORMAL_ENDMARKER "EndMessage"
#define DATA_ENDMARKER "Data"

wxFCPBaseMessage::wxFCPBaseMessage()
{
    m_name = wxString();
    m_endmarker = wxString();
    m_items = MessageItems();
}
    
wxFCPBaseMessage::~wxFCPBaseMessage() {
    Clear();
}

void wxFCPBaseMessage::Clear()
{
    m_name.Clear();
    m_endmarker.Clear();
    m_items.clear();
}

bool wxFCPBaseMessage::setName(wxString name)
{
    m_name = name;
    return true;
}

const wxString wxFCPBaseMessage::getName()
{
    return m_name;
}

bool wxFCPBaseMessage::setEndMarker(wxString endmarker)
{
    m_endmarker = endmarker;
    return true;
}

const wxString wxFCPBaseMessage::getEndMarker()
{
    return _T(NORMAL_ENDMARKER);
}

bool wxFCPBaseMessage::setItem(const wxString key, const wxString value)
{
    m_items[key] = value;
    return true;
}

wxString wxFCPBaseMessage::getItem(const wxString key)
{
    return m_items[key];
}

wxFCPNodeMessage::wxFCPNodeMessage() :
wxFCPBaseMessage()
{
    ;
}

bool wxFCPNodeMessage::isDataCarrying()
{
    return false;
}

bool wxFCPNodeMessage::isMessageName(const wxString name)
{
    return ( m_name == name );
}

//----

wxFCPCommand::wxFCPCommand() :
wxFCPBaseMessage()
{
    ;
}

bool wxFCPCommand::isDataCarrying()
{
    return false;
}

//----

wxFCPCommand* wxFCPCommandFactory::ClientHello(const wxString name)
{
    wxFCPCommand *ch = new wxFCPCommand();
    ch->setName(_T("ClientHello"));
    ch->setItem(_T("Name"), name);
    ch->setItem(_T("ExpectedVersion"), _T("2.0"));
    return ch;
};

wxFCPCommand* wxFCPCommandFactory::GenerateSSK()
{
    wxFCPCommand *ch = new wxFCPCommand();
    ch->setName(_T("GenerateSSK"));
    //ch->setItem(_T("Name"), name);
    //ch->setItem(_T("ExpectedVersion"), _T("2.0"));
    return ch;
};


