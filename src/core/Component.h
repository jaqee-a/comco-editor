#pragma once

#include "raylib.h"
#include "utils/UUID.h"
#include <cstdlib>
#include <string>

namespace ComcoEditor 
{

  struct IDComponent
  {
    UUID ID;
  };

  struct Tag
  {
    std::string Tag;
  };

  struct Transform
  {
    Vector2 m_Position{0.f, 0.f};
    Vector2 m_Rotation;
    Vector2 m_Scale{50.f, 50.f};
  };

  struct Sprite
  {
  public:
    Vector4 m_Color{0.0f, 0.0f, 0.0f, 1.0f};
    Texture2D m_Texture;

    // ~Sprite()
    // { Unload(); }

    void Load(const std::string& filename)
    {
      this->m_Filename = filename;
      this->m_Image = LoadImage(filename.c_str());
      this->m_Texture = LoadTextureFromImage(this->m_Image);
    }

    void Unload()
    {
      if(this->m_Texture.id > 0)
      {
        UnloadTexture(this->m_Texture);
        this->m_Texture.id = 0;
      }

      if(this->m_Image.data != nullptr)
      {
        UnloadImage(this->m_Image);
        this->m_Image.data = nullptr;
      }
    }

  private:
    std::string m_Filename;
    Image m_Image;
  };

  struct Rigidbody
  {
  public:
    void Update()
    { }
  private:
    Vector2 m_Force{0.f, 0.f};
    Vector2 m_Acceleration{0.f, 0.f};
  };

	template<typename... Component>
	struct ComponentGroup
	{ };

	using AllComponents = ComponentGroup<IDComponent, Tag, Transform, Sprite, Rigidbody>;

}
