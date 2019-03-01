// Copyright 2018 The MobileAIBench Authors. All Rights Reserved.
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

#include "aibench/executors/base_executor.h"

#include <numeric>
#include <map>
#include <memory>
#include <string>
#include <functional>

namespace aibench {

class BaseTensor::Impl {
 public:
  std::vector<int64_t> shape;
  std::shared_ptr<float> data;
};

BaseTensor::BaseTensor(const std::vector<int64_t> &shape,
                       std::shared_ptr<float> data) {
  impl_ = std::unique_ptr<BaseTensor::Impl>(new BaseTensor::Impl());
  impl_->shape = shape;
  impl_->data = data;
}

BaseTensor::BaseTensor() {
  impl_ = std::unique_ptr<BaseTensor::Impl>(new BaseTensor::Impl());
}

BaseTensor::BaseTensor(const BaseTensor &other) {
  impl_ = std::unique_ptr<BaseTensor::Impl>(new BaseTensor::Impl());
  impl_->shape = other.shape();
  impl_->data = other.data();
}

BaseTensor::BaseTensor(const BaseTensor &&other) {
  impl_ = std::unique_ptr<BaseTensor::Impl>(new BaseTensor::Impl());
  impl_->shape = other.shape();
  impl_->data = other.data();
}

BaseTensor &BaseTensor::operator=(const BaseTensor &other) {
  impl_->shape = other.shape();
  impl_->data = other.data();
  return *this;
}

BaseTensor &BaseTensor::operator=(const BaseTensor &&other) {
  impl_->shape = other.shape();
  impl_->data = other.data();
  return *this;
}

BaseTensor::~BaseTensor() = default;

const std::vector<int64_t> &BaseTensor::shape() const { return impl_->shape; }

const std::shared_ptr<float> BaseTensor::data() const { return impl_->data; }

int64_t BaseTensor::size() const {
  return std::accumulate(shape().begin(), shape().end(), 1,
                         std::multiplies<int64_t>());
}

std::shared_ptr<float> BaseTensor::data() { return impl_->data; }


}  // namespace aibench
