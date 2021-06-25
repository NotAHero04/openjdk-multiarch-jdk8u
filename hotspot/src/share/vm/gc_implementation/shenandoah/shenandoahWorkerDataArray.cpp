/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "gc_implementation/shenandoah/shenandoahWorkerDataArray.inline.hpp"
#include "utilities/ostream.hpp"

template <>
size_t ShenandoahWorkerDataArray<size_t>::uninitialized() {
  return (size_t)-1;
}

template <>
double ShenandoahWorkerDataArray<double>::uninitialized() {
  return -1.0;
}

template <>
void ShenandoahWorkerDataArray<double>::WDAPrinter::summary(outputStream* out, double min, double avg, double max, double diff, double sum, bool print_sum) {
  out->print(" Min: %4.1lf, Avg: %4.1lf, Max: %4.1lf, Diff: %4.1lf", min * MILLIUNITS, avg * MILLIUNITS, max * MILLIUNITS, diff* MILLIUNITS);
  if (print_sum) {
    out->print(", Sum: %4.1lf", sum * MILLIUNITS);
  }
}

template <>
void ShenandoahWorkerDataArray<size_t>::WDAPrinter::summary(outputStream* out, size_t min, double avg, size_t max, size_t diff, size_t sum, bool print_sum) {
  out->print(" Min: " SIZE_FORMAT ", Avg: %4.1lf, Max: " SIZE_FORMAT ", Diff: " SIZE_FORMAT, min, avg, max, diff);
  if (print_sum) {
    out->print(", Sum: " SIZE_FORMAT, sum);
  }
}

template <>
void ShenandoahWorkerDataArray<double>::WDAPrinter::details(const ShenandoahWorkerDataArray<double>* phase, outputStream* out) {
  out->print("%-25s", "");
  for (uint i = 0; i < phase->_length; ++i) {
    double value = phase->get(i);
    if (value != phase->uninitialized()) {
      out->print(" %4.1lf", phase->get(i) * 1000.0);
    } else {
      out->print(" -");
    }
  }
  out->cr();
}

template <>
void ShenandoahWorkerDataArray<size_t>::WDAPrinter::details(const ShenandoahWorkerDataArray<size_t>* phase, outputStream* out) {
  out->print("%-25s", "");
  for (uint i = 0; i < phase->_length; ++i) {
    size_t value = phase->get(i);
    if (value != phase->uninitialized()) {
      out->print("  " SIZE_FORMAT, phase->get(i));
    } else {
      out->print(" -");
    }
  }
  out->cr();
}
