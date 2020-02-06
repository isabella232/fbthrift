/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <vector>

#include <folly/ExceptionWrapper.h>
#include <folly/Likely.h>

#include <thrift/lib/cpp2/transport/rocket/client/RequestContext.h>

namespace apache {
namespace thrift {
namespace rocket {

class RequestContextQueue {
 public:
  RequestContextQueue() = default;

  ~RequestContextQueue() {
    DCHECK(writeScheduledQueue_.empty());
    DCHECK(writeSendingQueue_.empty());
    DCHECK(writeSentQueue_.empty());
  }

  void enqueueScheduledWrite(RequestContext& req) noexcept;

  std::unique_ptr<folly::IOBuf> getNextScheduledWritesBatch() noexcept;

  template <typename F>
  void markNextSendingBatchAsSent(F&& foreachRequest) noexcept {
    for (bool lastInBatch = false; !lastInBatch;) {
      auto& req = writeSendingQueue_.front();
      writeSendingQueue_.pop_front();
      lastInBatch = req.lastInWriteBatch_;
      if (LIKELY(req.state() == State::WRITE_SENDING)) {
        req.state_ = State::WRITE_SENT;
        // Move req to the WRITE_SENT queue even if req is not a
        // REQUEST_RESPONSE request.
        writeSentQueue_.push_back(req);
      } else {
        DCHECK(req.state() == State::COMPLETE);
        req.baton_.post();
      }
      foreachRequest(req);
    }
  }

  void abortSentRequest(RequestContext& req) noexcept;

  void markAsResponded(RequestContext& req) noexcept;

  bool hasInflightWrites() const noexcept {
    return !writeSendingQueue_.empty();
  }

  void failAllScheduledWrites(transport::TTransportException ex);
  void failAllSentWrites(transport::TTransportException ex);

  RequestContext* getRequestResponseContext(StreamId streamId);

 private:
  using RequestResponseSet = RequestContext::UnorderedSet;

  static constexpr size_t kDefaultNumBuckets = 100;
  std::vector<RequestResponseSet::bucket_type> rrContextBuckets_{
      kDefaultNumBuckets};

  // Only REQUEST_RESPONSE contexts are ever inserted/looked up in this set.
  // Allows response payloads to be matched with requests. (Streams have a
  // different mechanism for doing this, since there are potentially many
  // response payloads per initiating REQUEST_STREAM context.)
  RequestResponseSet requestResponseContexts_{
      RequestResponseSet::bucket_traits{rrContextBuckets_.data(),
                                        rrContextBuckets_.size()}};

  using State = RequestContext::State;

  // Requests for which AsyncSocket::writev() has not been called yet
  RequestContext::Queue writeScheduledQueue_;
  // Requests for which AsyncSocket::writev() has been called but completion
  // of the write to the underlying transport (successful or otherwise) is
  // still pending.
  RequestContext::Queue writeSendingQueue_;
  // Once the attempt to write a request to the socket is complete, the
  // request moves to this queue. Note that the request flows into this queue
  // even if the write to the socket failed, i.e., regardless of whether
  // writeSuccess() or writeErr() was called.
  RequestContext::Queue writeSentQueue_;

  void failQueue(
      RequestContext::Queue& queue,
      transport::TTransportException ex);

  void trackIfRequestResponse(RequestContext& req) {
    if (req.isRequestResponse()) {
      if (UNLIKELY(
              requestResponseContexts_.size() > rrContextBuckets_.size())) {
        growBuckets();
      }
      requestResponseContexts_.insert(req);
    }
  }
  void untrackIfRequestResponse(RequestContext& req) {
    if (req.isRequestResponse()) {
      requestResponseContexts_.erase(req);
    }
  }

  void growBuckets();
};

} // namespace rocket
} // namespace thrift
} // namespace apache
