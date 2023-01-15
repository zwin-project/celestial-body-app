#include <zukou.h>

#include "jpeg-texture.h"
#include "sphere.h"

class CelestialBody final : public zukou::IBoundedDelegate,
                            public zukou::ISystemDelegate
{
 public:
  CelestialBody(const char* texture_path)
      : system_(this),
        bounded_(&system_, this),
        region_(&system_),
        texture_path_(texture_path),
        sphere_(&system_, &bounded_, 8)
  {}

  bool Init(std::string& name, float radius)
  {
    if (!system_.Init()) return false;
    if (!bounded_.Init(glm::vec3(radius))) return false;
    if (!region_.Init()) return false;

    bounded_.SetTitle(name);

    // region_.AddCuboid(glm::vec3(radius), glm::vec3(0), glm::quat(glm::vec3(0)));
    // bounded_.SetRegion(&region_);

    auto jpeg_texture = std::make_unique<JpegTexture>(&system_);

    if (!jpeg_texture->Init()) return false;
    if (!jpeg_texture->Load(texture_path_)) return false;

    sphere_.Bind(std::move(jpeg_texture));

    return true;
  }

  int Run() { return system_.Run(); }

  void Configure(glm::vec3 half_size, uint32_t serial) override
  {
    float radius = glm::min(half_size.x, glm::min(half_size.y, half_size.z));
    sphere_.Render(radius, glm::mat4(1));

    bounded_.AckConfigure(serial);
    bounded_.NextFrame();
    bounded_.Commit();
  }

  // Implement the content of the function.
  void RayAxisFrame(const zukou::RayAxisEvent& /*event*/) override {}
  // void RayAxisFrame(const zukou::RayAxisEvent& event) override
  // {
  //   spin_angle_ += event.vertical;
  //   spin_angle_ %= 360;

  //   float theta = 2.0 * M_PI * spin_angle_ / 360.0;

  //   glm::mat4 transform = glm::rotate(glm::mat4(1), theta, glm::vec3(0, 1, 0));
  //   sphere_.Update(transform);

  //   bounded_.Commit();
  // }

  void Frame(uint32_t /*time*/) override {}

 private:
  zukou::System system_;
  zukou::Bounded bounded_;
  zukou::Region region_;

  const char* texture_path_;
  // int spin_angle_ = 0; // Add this line.

  Sphere sphere_;
};

int
main(void)
{
  // std::string path("./assets/earth.jpg");
  // std::string name("Earth");
  std::string path("./assets/moon.jpg");
  std::string name("Moon");
  CelestialBody celestial_body(path.c_str());

  if (!celestial_body.Init(name, 0.1)) return EXIT_FAILURE;

  return celestial_body.Run();
}
