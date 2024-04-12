#pragma once
#include <Eigen/Eigen>
#include <functional>

// Simple proxy around libigl's Viewer to cache the heavy compilation.
// We try to include all functions from libigl's Viewer
// (https://github.com/libigl/libigl/blob/main/include/igl/opengl/ViewerData.h)
// that you need, but we may have missed something. In that case you can add a
// the function here and in viewer_proxy.cpp following the examples that are
// already there. Editing the viewer_proxy.h/.cpp files will significantly slow
// down your compilation so we recommend to avoid editing it frequently.

class ViewerProxy {
public:
  // Proxy for igl::opengl::ViewerData.
  class Data {
  public:
    Data(void *data);
    void clear();
    void compute_normals();
    void set_mesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F);
    void set_normals(const Eigen::MatrixXd &N);
    void set_colors(const Eigen::MatrixXd &colors);
    void add_points(const Eigen::MatrixXd &P, const Eigen::MatrixXd &C);
    void add_edges(const Eigen::MatrixXd &P, const Eigen::MatrixXd &E,
                   const Eigen::MatrixXd &C);
    void set_face_based(bool face_based);
    void set_uv(const Eigen::MatrixXd &UV);
    void set_visible(bool visible, int core_id = 1);

    float &point_size;
    unsigned int &show_lines;
    unsigned int &show_faces;
    unsigned int &show_texture;
    void *_igl_viewer_data;
  };
  // Proxy for igl::opengl::ViewerCore.
  class Core {
  public:
    Core(void *igl_viewer_core);
    void align_camera_center(const Eigen::MatrixXd &V,
                             const Eigen::MatrixXi &F);
    void align_camera_center(const Eigen::MatrixXd &P);
    void disable_rotation();
    void *_igl_viewer_core;
    bool &orthographic;
    Eigen::Vector4f &viewport;
    unsigned int &id;
  };

  // Proxy for igl::opengl::glfw::imgui::ImGuiMenu.
  class Menu {
  public:
    Menu();
    void draw_viewer_menu();

    std::function<void(void)> &callback_draw_viewer_menu;
  };

  static ViewerProxy &get_instance();

  void launch();
  Data data(int mesh_id = -1);
  Data append_mesh(bool visible = true);
  Core core(unsigned core_id = 0);
  Core append_core(const Eigen::Vector4f& viewport = Eigen::Vector4f::Zero());
  Menu &menu() { return _menu; }

  // Callbacks.
  std::function<bool(ViewerProxy &viewer, unsigned int key, int modifiers)>
      callback_key_down = [&](ViewerProxy &viewer, unsigned int key,
                              int modifiers) { return false; };
  std::function<bool(ViewerProxy &)> callback_init = [&](ViewerProxy &) {
    return false;
  };
  std::function<bool(ViewerProxy &, int, int)> callback_post_resize =
      [](ViewerProxy &, int, int) { return false; };

  // Load a mesh from a file.
  void load_mesh(const std::string &filename, Eigen::MatrixXd &V,
                 Eigen::MatrixXi &F);
protected:
ViewerProxy() {}
  static ViewerProxy *_instance;
  Menu _menu;
};
