#pragma once

#include <imgui.h>

#include <algorithm>

namespace overworld_minimap {

struct Area {
  ImVec2 min, max;

  bool contains(ImVec2 point) const {
    return point.x >= min.x && point.x < max.x && point.y >= min.y && point.y < max.y;
  }
};

inline Area place(ImVec2 viewportMin, ImVec2 viewportMax, float aspect) {
  const float maxWidth = std::min(192.0f, (viewportMax.x - viewportMin.x) * 0.32f);
  const float maxHeight = std::min(144.0f, (viewportMax.y - viewportMin.y) * 0.35f);
  const float width = std::min(maxWidth, maxHeight * aspect);
  const float height = width / aspect;
  const ImVec2 topRight{viewportMax.x - 16.0f, viewportMin.y + 12.0f};
  return {{topRight.x - width, topRight.y}, {topRight.x, topRight.y + height}};
}

inline void draw(ImDrawList* dl, Area area, ImTextureRef texture, ImVec2 viewportMin, ImVec2 viewportMax,
                 ImVec2 party, auto&& drawFog) {
  const float width = area.max.x - area.min.x, height = area.max.y - area.min.y;
  const auto project = [=](ImVec2 p) {
    return ImVec2{area.min.x + p.x * width, area.min.y + p.y * height};
  };
  dl->PushClipRect(area.min, area.max, true);
  dl->AddImage(texture, area.min, area.max);
  drawFog(dl, area.min, width, height);
  dl->AddRect(project(viewportMin), project(viewportMax), IM_COL32(255, 222, 153, 240));
  const ImVec2 marker = project(party);
  dl->AddCircleFilled(marker, 5.0f, IM_COL32(20, 14, 9, 255));
  dl->AddCircleFilled(marker, 3.0f, IM_COL32(255, 223, 151, 255));
  dl->PopClipRect();
  dl->AddRect(area.min, area.max, IM_COL32(170, 132, 83, 255));
}

}  // namespace overworld_minimap
