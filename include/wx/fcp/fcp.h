/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fcp/fcp.h
// Purpose:     central header for fcp implementation
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _FCP_FCP_H_
#define _FCP_FCP_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#define DEFAULT_FCP_HOST "127.0.0.1"
#define DEFAULT_FCP_PORT 9481
#define DEFAULT_FCP_TIMEOUT 300

#define FCP_HOST_ENV_NAME "FCP_HOST"
#define FCP_PORT_ENV_NAME "FCP_PORT"
#define FCP_TIMEOUT_ENV_NAME "FCP_TIMEOUT"

#endif // ifndef _FCP_FCP_H_
