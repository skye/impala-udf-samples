// Copyright 2012 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef SAMPLES_UDA_H
#define SAMPLES_UDA_H

#include <impala_udf/udf.h>

using namespace impala_udf;

// This is an example of the COUNT aggregate function.
void CountInit(FunctionContext* context, BigIntVal* val);
void CountUpdate(FunctionContext* context, const IntVal& input, BigIntVal* val);
void CountMerge(FunctionContext* context, const BigIntVal& src, BigIntVal* dst);
BigIntVal CountFinalize(FunctionContext* context, const BigIntVal& val);

// This is an example of the AVG(double) aggregate function. This function needs to
// maintain two pieces of state, the current sum and the count. We do this using
// the BufferVal intermediate type. When this UDA is registered, it would specify
// 16 bytes (8 byte sum + 8 byte count) as the size for this buffer.
void AvgInit(FunctionContext* context, BufferVal* val);
void AvgUpdate(FunctionContext* context, const DoubleVal& input, BufferVal* val);
void AvgMerge(FunctionContext* context, const BufferVal& src, BufferVal* dst);
DoubleVal AvgFinalize(FunctionContext* context, const BufferVal& val);

// This is a sample of implementing the STRING_CONCAT aggregate function.
// Example: select string_concat(string_col, ",") from table
void StringConcatInit(FunctionContext* context, StringVal* val);
void StringConcatUpdate(FunctionContext* context, const StringVal& arg1,
    const StringVal& arg2, StringVal* val);
void StringConcatMerge(FunctionContext* context, const StringVal& src, StringVal* dst);
StringVal StringConcatFinalize(FunctionContext* context, const StringVal& val);

// This is a example of the variance aggregate function.
void VarianceInit(FunctionContext* context, StringVal* val);
void VarianceUpdate(FunctionContext* context, const DoubleVal& input, StringVal* val);
void VarianceMerge(FunctionContext* context, const StringVal& src, StringVal* dst);
DoubleVal VarianceFinalize(FunctionContext* context, const StringVal& val);

void KnuthVarianceInit(FunctionContext* context, StringVal* val);
void KnuthVarianceUpdate(FunctionContext* context, const DoubleVal& input, StringVal* val);
void KnuthVarianceMerge(FunctionContext* context, const StringVal& src, StringVal* dst);
DoubleVal KnuthVarianceFinalize(FunctionContext* context, const StringVal& val);

// The different steps of the UDA are composable. In this case, we'll the UDA will
// use the other steps from the variance computation.
DoubleVal StdDevFinalize(FunctionContext* context, const StringVal& val);

#endif
