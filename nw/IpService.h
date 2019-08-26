//==============================================================================
//
//  IpService.h
//
//  Copyright (C) 2017  Greg Utas
//
//  This file is part of the Robust Services Core (RSC).
//
//  RSC is free software: you can redistribute it and/or modify it under the
//  terms of the GNU General Public License as published by the Free Software
//  Foundation, either version 3 of the License, or (at your option) any later
//  version.
//
//  RSC is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
//  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
//  details.
//
//  You should have received a copy of the GNU General Public License along
//  with RSC.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef IPSERVICE_H_INCLUDED
#define IPSERVICE_H_INCLUDED

#include "Protected.h"
#include <cstddef>
#include "IoThread.h"
#include "NbTypes.h"
#include "NwTypes.h"
#include "RegCell.h"
#include "SysTypes.h"

namespace NodeBase
{
   class CliText;
}

//------------------------------------------------------------------------------

namespace NetworkBase
{
class IpService : public NodeBase::Protected
{
   friend class NodeBase::Registry< IpService >;
public:
   //> The maximum number of IP services.
   //
   static const NodeBase::id_t MaxId;

   //  Deleted to prohibit copying.
   //
   IpService(const IpService& that) = delete;
   IpService& operator=(const IpService& that) = delete;

   //  Returns a string that identifies the service for display purposes.
   //
   virtual NodeBase::c_string Name() const = 0;

   //  Returns the IP protocol over which the service runs.
   //
   virtual IpProtocol Protocol() const = 0;

   //  Returns the port on which the service should be started during a
   //  restart.
   //
   virtual ipport_t Port() const = 0;

   //  Returns the scheduler faction for the service's I/O thread.
   //
   virtual NodeBase::Faction GetFaction() const = 0;

   //  Returns the size of the receive buffer for the service's I/O thread.
   //
   virtual size_t RxSize() const { return IoThread::MaxRxBuffSize; }

   //  Returns the size of the transmit buffer for the service's I/O thread.
   //
   virtual size_t TxSize() const { return IoThread::MaxTxBuffSize; }

   //  Creates a subclass of CliText for provisioning the service through
   //  the CLI.  [This is not currently invoked but has a few overrides that
   //  illustrate its purpose, which is to name a protocol whose port, and
   //  possibly other attributes, could be configured via a CLI command.]
   //
   virtual NodeBase::CliText* CreateText() const = 0;

   //  Returns true if applications share the I/O thread's primary socket.
   //  If it returns false, as it does for TCP-based services, application
   //  instances must allocate a socket before sending a message.
   //
   virtual bool HasSharedSocket() const = 0;

   //  Provides sizes of the receive and transmit buffers for application
   //  sockets.  Invoked to configure the socket when the service's I/O
   //  thread accepts a connection.  The default version generates a log
   //  and must be overridden by services that use a dedicated socket for
   //  each application instance.
   //
   virtual void GetAppSocketSizes(size_t& rxSize, size_t& txSize) const;

   //  Provisions the service on PID.
   //
   IpPort* Provision(ipport_t pid);

   //  Returns the service's identifier.
   //
   NodeBase::id_t Sid() const { return sid_.GetId(); }

   //  Returns the offset to sid_.
   //
   static ptrdiff_t CellDiff();

   //  Overridden for restarts.  Invokes CreatePort and CreateHandler to
   //  start the service on the port, if any, returned by GetPort.  May
   //  be overridden if, for example, the service needs to be started on
   //  multiple ports.
   //
   void Startup(NodeBase::RestartLevel level) override;

   //  Overridden to display member variables.
   //
   void Display(std::ostream& stream,
      const std::string& prefix, const NodeBase::Flags& options) const override;

   //  Overridden for patching.
   //
   void Patch(sel_t selector, void* arguments) override;
protected:
   //  Registers the service with IpServiceRegistry.  Protected because
   //  this class is virtual.
   //
   IpService();

   //  Removes the service from IpServiceRegistry.  Protected because
   //  subclasses should be singletons.
   //
   virtual ~IpService();
private:
   //  Creates an InputHandler that will host the service on PORT.
   //
   virtual InputHandler* CreateHandler(IpPort* port) const = 0;

   //  Creates an IpPort that will host the service on PID.  Overridden
   //  by each IpProtocol-based subclass.
   //
   virtual IpPort* CreatePort(ipport_t pid) = 0;

   //  The service's identifier.
   //
   NodeBase::RegCell sid_;
};
}
#endif
