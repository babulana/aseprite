// Aseprite Document Library
// Copyright (c) 2022 Igara Studio S.A.
// Copyright (c) 2016-2018 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef DOC_SELECTED_FRAMES_H_INCLUDED
#define DOC_SELECTED_FRAMES_H_INCLUDED
#pragma once

#include "doc/frames_iterators.h"

using namespace doc::frames;

namespace doc {

  // The FramesSequence class is based in several code of this class.
  // TODO: At some point we should remove the duplicated code between these
  // classes.
  class SelectedFrames {
  public:
    const_iterator begin() const { return const_iterator(m_ranges.begin()); }
    const_iterator end() const { return const_iterator(m_ranges.end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(m_ranges.rbegin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(m_ranges.rend()); }

    std::size_t size() const;
    std::size_t ranges() const { return m_ranges.size(); }
    bool empty() const { return m_ranges.empty(); }

    void clear();
    void insert(frame_t frame);
    void insert(frame_t fromFrame, frame_t toFrame);
    SelectedFrames filter(frame_t fromFrame, frame_t toFrame) const;

    bool contains(frame_t frame) const;

    frame_t firstFrame() const { return (!m_ranges.empty() ? m_ranges.front().fromFrame: -1); }
    frame_t lastFrame() const { return (!m_ranges.empty() ? m_ranges.back().toFrame: -1); }

    void displace(frame_t frameDelta);
    Reversed<SelectedFrames> reversed() const { return Reversed(*this); }

    SelectedFrames makeReverse() const;
    SelectedFrames makePingPong() const;

    bool operator==(const SelectedFrames& o) const {
      return m_ranges == o.m_ranges;
    }

    bool operator!=(const SelectedFrames& o) const {
      return !operator==(o);
    }

    bool write(std::ostream& os) const;
    bool read(std::istream& is);

  private:
    Ranges m_ranges;
  };

} // namespace doc

#endif  // DOC_SELECTED_FRAMES_H_INCLUDED
