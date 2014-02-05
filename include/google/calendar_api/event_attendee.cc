// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// This code was generated by google-apis-code-generator 1.4.1
//   Build date: 2013-08-07 19:00:49 UTC
//   on: 2013-08-13, 01:30:06 UTC
//   C++ generator version:

// ----------------------------------------------------------------------------
// NOTE: This file is generated from Google APIs Discovery Service.
// Service:
//   Calendar API (calendar/v3)
// Description:
//   Lets you manipulate events and other calendar data.
// Classes:
//   EventAttendee
// Documentation:
//   https://developers.google.com/google-apps/calendar/firstapp

#include "google/calendar_api/event_attendee.h"
#include <string>
#include "googleapis/base/integral_types.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"


#include <string>
#include "googleapis/strings/strcat.h"

namespace google_calendar_api {
using namespace googleapis;


// Object factory method (static).
google_calendar_api::EventAttendee* google_calendar_api::EventAttendee::New() {
  return new client::JsonCppCapsule<EventAttendee>;
}

// Standard immutable constructor.
google_calendar_api::EventAttendee::EventAttendee(const Json::Value& storage)
  : client::JsonCppData(storage) {
}

// Standard mutable constructor.
google_calendar_api::EventAttendee::EventAttendee(Json::Value* storage)
  : client::JsonCppData(storage) {
}

// Standard destructor.
google_calendar_api::EventAttendee::~EventAttendee() {
}
}  // namespace google_calendar_api
