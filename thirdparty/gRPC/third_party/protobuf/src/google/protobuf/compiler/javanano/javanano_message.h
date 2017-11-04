﻿// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_MESSAGE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_MESSAGE_H__

#include <string>
#include <google/protobuf/compiler/javanano/javanano_helpers.h>
#include <google/protobuf/compiler/javanano/javanano_field.h>
#include <google/protobuf/compiler/javanano/javanano_params.h>
#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace javanano {

class MessageGenerator {
 public:
  explicit MessageGenerator(const Descriptor* descriptor, const Params& params);
  ~MessageGenerator();

  // All static variables have to be declared at the top-level of the file
  // so that we can control initialization order, which is important for
  // DescriptorProto bootstrapping to work.
  void GenerateStaticVariables(io::Printer* printer);

  // Output code which initializes the static variables generated by
  // GenerateStaticVariables().
  void GenerateStaticVariableInitializers(io::Printer* printer);

  // Generate the class itself.
  void Generate(io::Printer* printer);

 private:
  void GenerateMessageSerializationMethods(io::Printer* printer);
  void GenerateMergeFromMethods(io::Printer* printer);
  void GenerateParseFromMethods(io::Printer* printer);
  void GenerateSerializeOneField(io::Printer* printer,
                                 const FieldDescriptor* field);

  void GenerateClear(io::Printer* printer);
  void GenerateFieldInitializers(io::Printer* printer);
  void GenerateEquals(io::Printer* printer);
  void GenerateHashCode(io::Printer* printer);
  void GenerateClone(io::Printer* printer);

  const Params& params_;
  const Descriptor* descriptor_;
  FieldGeneratorMap field_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_MESSAGE_H__