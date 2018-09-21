#pragma once

#include<vector>
#include<geGL/Fwd.h>

class ge::gl::VertexArrayImpl {
public:
  std::vector<Buffer*>buffers;
  Buffer*elementBuffer = nullptr;
};
