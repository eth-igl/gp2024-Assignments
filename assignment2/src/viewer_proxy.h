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
    Data();
    void clear();
    void compute_normals();
    void set_mesh(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F);
    void set_normals(const Eigen::MatrixXd& N);
    void set_colors(const Eigen::MatrixXd& colors);
    void add_points(const Eigen::MatrixXd& P, const Eigen::MatrixXd& C);
    void add_edges(const Eigen::MatrixXd& P, const Eigen::MatrixXd& E,
                   const Eigen::MatrixXd& C);

    float& point_size;
    unsigned int& show_lines;
    unsigned int& show_faces;
  };
  // Proxy for igl::opengl::ViewerCore.
  class Core {
   public:
    void align_camera_center(const Eigen::MatrixXd& V,
                             const Eigen::MatrixXi& F);
    void align_camera_center(const Eigen::MatrixXd& P);
  };

  // Proxy for igl::opengl::glfw::imgui::ImGuiMenu.
  class Menu {
   public:
    Menu();
    void draw_viewer_menu();

    std::function<void(void)>& callback_draw_viewer_menu;
  };

  static ViewerProxy& get_instance();

  void launch();
  Data& data() { return _data; }
  Core& core() { return _core; }
  Menu& menu() { return _menu; }

  std::function<bool(ViewerProxy& viewer, unsigned int key, int modifiers)>
      callback_key_down = [&](ViewerProxy& viewer, unsigned int key,
                              int modifiers) { return true; };

 protected:
  ViewerProxy() {}
  static ViewerProxy* _instance;
  Data _data;
  Core _core;
  Menu _menu;
};
