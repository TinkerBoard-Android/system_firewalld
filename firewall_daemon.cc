// Copyright 2014 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "firewall_daemon.h"

#include <string>

#include <base/logging.h>

namespace firewalld {

FirewallDaemon::FirewallDaemon()
    : chromeos::DBusServiceDaemon{kFirewallServiceName,
                                  dbus::ObjectPath{kFirewallServicePath}} {
}

void FirewallDaemon::RegisterDBusObjectsAsync(AsyncEventSequencer* sequencer) {
  firewall_service_.reset(
      new firewalld::FirewallService{object_manager_.get()});
  firewall_service_->RegisterAsync(
      sequencer->GetHandler("Service.RegisterAsync() failed.", true));
}

}  // namespace firewalld
