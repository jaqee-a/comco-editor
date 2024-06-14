#pragma once

#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

#include "utils/UUID.h"

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
    Vector2 m_Velocity{0.f, 0.f};
    Vector2 m_Acceleration{0.f, 0.f};
    float_t m_Mass = 1.f;
    bool m_UseGravity = false;
    bool m_UseDrag = false;
    float_t m_Drag = 1.f;

    void Update(float deltaTime)
    {
      if(m_UseGravity)
      {
        std::cout << m_Mass << std::endl;
        ApplyForce({0, 9.1f * m_Mass});
      }
      m_Velocity.x += m_Acceleration.x * deltaTime;
      m_Velocity.y += m_Acceleration.y * deltaTime;
      m_Acceleration= {0.f, 0.f};

      if(m_UseDrag)
      {
        m_Velocity.x *= m_Drag;
        m_Velocity.y *= m_Drag;
      }
    }
  private:
    
    void ApplyForce(const Vector2& force)
    {
        Vector2 newAcceleration = {force.x * (1.0f / m_Mass ? m_Mass: 0.0001f),
                                   force.y * (1.0f / m_Mass ? m_Mass: 0.0001f)};
        m_Acceleration.x += newAcceleration.x;
        m_Acceleration.y += newAcceleration.y;
    }
  };

	template<typename... Component>
	struct ComponentGroup
	{ };

	using AllComponents = ComponentGroup<IDComponent, Tag, Transform, Sprite, Rigidbody>;

}
