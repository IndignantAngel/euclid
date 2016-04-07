#pragma once

// vector framework
#include "vector/vector_forward.hpp"
#include "common.hpp"
#include "vector/vector_placeholder.hpp"
#include "vector/vector_expression.hpp"
#include "vector/vector_functional.hpp"

// vector implementation
#include "vector/expression/vector_expression_detail.hpp"
#include "vector/expression/vector_honmono.hpp"
#include "vector/expression/vector_proxy.hpp"
#include "vector/expression/vector_unary.hpp"
#include "vector/expression/vector_binary.hpp"
#include "vector/expression/vector_scalar.hpp"
#include "vector/expression/vector_reduce_unary.hpp"
#include "vector/expression/vector_reduce_binary.hpp"

// vector operator
#include "vector/operator/vetor_operator_detail.hpp"
#include "vector/vector_operator.hpp"