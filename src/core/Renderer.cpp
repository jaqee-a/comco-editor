#include "core/Renderer.h"
#include "core/Component.h"
#include "raylib.h"

namespace ComcoEditor {
  void Renderer::DrawEntity(ComcoEditor::Entity entity)
  {
    if(!entity.HasComponent<ComcoEditor::Transform>()) return;
    if(!entity.HasComponent<ComcoEditor::Sprite>()) return;

    Transform transform = entity.GetComponent<ComcoEditor::Transform>();
    Sprite sprite = entity.GetComponent<ComcoEditor::Sprite>();

    Vector2 position = transform.m_Position;
    Vector2 scale = transform.m_Scale;
  
    Rectangle sourceRec = { 0.0f, 0.0f, (float)sprite.m_Texture.width, (float)sprite.m_Texture.height };
    Rectangle destRec = { position.x, position.y, scale.x, scale.y};

    DrawTexturePro(sprite.m_Texture, sourceRec, 
                destRec, {0, 0}, 0,
                Color(sprite.m_Color.x*255, 
                  sprite.m_Color.y*255, 
                  sprite.m_Color.z*255, 
                  sprite.m_Color.w*255));
    // DrawRectangle(position.x, position.y, scale.x, scale.y, 
    //               Color(sprite.m_Color.x*255, 
    //                     sprite.m_Color.y*255, 
    //                     sprite.m_Color.z*255, 
    //                     sprite.m_Color.w*255));
  }
}
