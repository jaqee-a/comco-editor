#pragma once

#include "core/AnimationNode.h"
#include "ui/Panel.h"
#include "utils/UUID.h"
#include <vector>

namespace ComcoEditor
{
  class Animator: public Panel
  {
  public:
    Animator(ImGuiLayer&);
    ~Animator();
    
    virtual void OnRender(Application& application) override;
  private:
    float m_CurrentTime = 0;
    bool m_IsPlaying = false;
    bool m_Record = false;

    std::vector<AnimationNode> m_AnimationNodes;
    std::pair<AnimationNode, AnimationNode> GetNextAnimationNode(UUID entityUUID, bool& hasPrev, bool& hasNext);
  };
}
