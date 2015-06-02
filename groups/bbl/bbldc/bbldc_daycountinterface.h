// bbldc_daycountinterface.h                                          -*-C++-*-
#ifndef INCLUDED_BBLDC_DAYCOUNTINTERFACE
#define INCLUDED_BBLDC_DAYCOUNTINTERFACE

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide an interface for day-count calculations.
//
//@CLASSES:
//  bbldc::DayCountInterface: interface for day-count calculations
//
//@DESCRIPTION: This component provides an interface,
// 'bbldc::DayCountInterface', for implementing an arbitrary day-count
// convention.  Concrete implementations of this interface may implement, e.g.,
// the ISMA 30/360 day-count convention, or a custom day-count convention
// appropriate for some niche market.
//
// Several of the components in 'bbldc' already provide individual day-count
// convention support through interfaces that happen to be functionally
// identical to this contained abstract interface, except that they do not
// inherit from 'bbldc_DayCountInterface'.  In conjunction with the adapter
// components (i.e., 'bbldc::BasicDayCountAdapter'), this component interface
// is intended for allowing run-time binding of these and other similar
// day-count implementations.
//
///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Definition and Use of a Concrete Day-Count Convention
///- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// This example shows the definition and use of a simple concrete day-count
// convention.  This functionality suffices to demonstrate the requisite steps
// for having a working day-count convention:
//..
//  1. Define a concrete day-count type derived from 'bbldc_DayCountInterface'.
//  2. Implement the pure virtual 'daysDiff' and 'yearsDiff' methods.
//  3. Instantiate and use an object of the concrete type.
//..
// First define the (derived) 'my_DayCountConvention' class and implement its
// constructor inline (for convenience, directly within the derived-class
// definition):
//..
//  // my_daycountconvention.h
//
//  class my_DayCountConvention : public bbldc::DayCountInterface {
//    public:
//      my_DayCountConvention() { }
//      virtual ~my_DayCountConvention();
//      virtual int daysDiff(const bdlt::Date& beginDate,
//                           const bdlt::Date& endDate) const;
//          // Return the (signed) number of days between the specified ...
//      virtual double yearsDiff(const bdlt::Date& beginDate,
//                               const bdlt::Date& endDate) const;
//          // Return the (signed fractional) number of years between the ...
//  };
//..
// Then, implement the destructor.  Note, however, that we always implement a
// virtual destructor (non-inline) in the .cpp file (to indicate the *unique*
// location of the class's virtual table):
//..
//  // my_daycountconvention.cpp
//
//  // ...
//
//  my_DayCountConvention::~my_DayCountConvention() { }
//..
// Next, we implement the (virtual) 'daysDiff' and 'yearsDiff' methods, which
// incorporate the "policy" of what it means for this day-count convention to
// calculate these values.
//..
//  int my_DayCountConvention::daysDiff(const bdlt::Date& beginDate,
//                                      const bdlt::Date& endDate) const
//  {
//      return endDate - beginDate;
//  }
//
//  double my_DayCountConvention::yearsDiff(const bdlt::Date& beginDate,
//                                          const bdlt::Date& endDate) const
//  {
//      return static_cast<double>((endDate - beginDate) / 365.0);
//  }
//..
// Then, create two 'bdlt::Date' variables 'd1' and 'd2' to use with the
// 'my_DayCountConvention' object and its day-count convention methods.
//..
//  const bdlt::Date d1(2003, 10, 19);
//  const bdlt::Date d2(2003, 12, 31);
//..
// Next, we obtain a 'bbldc_DayCountInterface' reference from an instantiated
// 'my_DayCountConvention':
//..
//  my_DayCountConvention           myDcc;
//  const bbldc::DayCountInterface& dcc = myDcc;
//..
// Now, we compute the day-count between these two dates:
//..
//  const int daysDiff = dcc.daysDiff(d1, d2);
//  assert(73 == daysDiff);
//..
// Finally, we compute the year fraction between these two dates:
//..
//  const double yearsDiff = dcc.yearsDiff(d1, d2);
//  // Need fuzzy comparison since 'yearsDiff' is a double.  Expect
//  // '0.2 == yearsDiff'.
//  assert(0.1999 < yearsDiff);
//  assert(0.2001 > yearsDiff);
//..

#ifndef INCLUDED_BBLSCM_VERSION
#include <bblscm_version.h>
#endif

namespace BloombergLP {

namespace bdlt { class Date; }

namespace bbldc {

                         // =======================
                         // class DayCountInterface
                         // =======================

class DayCountInterface {
    // This 'class' provides an interface for determining values based on dates
    // according to derived implementations of specific day-count conventions.

  public:
    // CREATORS
    virtual ~DayCountInterface();
        // Destroy this object.

    // ACCESSORS
    virtual int daysDiff(const bdlt::Date& beginDate,
                         const bdlt::Date& endDate) const = 0;
        // Return the (signed) number of days between the specified 'beginDate'
        // and 'endDate'.  If 'beginDate <= endDate', then the result is
        // non-negative.  Note that reversing the order of 'beginDate' and
        // 'endDate' negates the result.

    virtual double yearsDiff(const bdlt::Date& beginDate,
                             const bdlt::Date& endDate) const = 0;
        // Return the (signed fractional) number of years between the specified
        // 'beginDate' and 'endDate'.  If 'beginDate <= endDate', then the
        // result is non-negative.  Note that reversing the order of
        // 'beginDate' and 'endDate' negates the result; specifically
        // '|yearsDiff(b, e) + yearsDiff(e, b)| <= 1.0e-15' for all dates 'b'
        // and 'e'.
};

}  // close package namespace
}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
