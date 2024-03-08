#include "viewer_proxy.h"

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

igl::opengl::glfw::Viewer viewer;
igl::opengl::glfw::imgui::ImGuiPlugin plugin;
igl::opengl::glfw::imgui::ImGuiMenu menu;
ViewerProxy* ViewerProxy::_instance = nullptr;

static void init_igl_viewer() {
  viewer.plugins.push_back(&plugin);
  plugin.widgets.push_back(&menu);
}

ViewerProxy& ViewerProxy::get_instance() {
  if (_instance == nullptr) {
    _instance = new ViewerProxy();
    init_igl_viewer();

    viewer.callback_key_down = [&](igl::opengl::glfw::Viewer& viewer,
                                   unsigned char key, int modifiers) {
      return _instance->callback_key_down(*_instance, key, modifiers);
    };
  }
  return *_instance;
}

void ViewerProxy::launch() { viewer.launch(); }

void ViewerProxy::Data::clear() { viewer.data().clear(); }
void ViewerProxy::Data::compute_normals() { viewer.data().compute_normals(); }
void ViewerProxy::Data::set_mesh(const Eigen::MatrixXd& V,
                                 const Eigen::MatrixXi& F) {
  viewer.data().set_mesh(V, F);
}
void ViewerProxy::Data::set_normals(const Eigen::MatrixXd& N) {
  viewer.data().set_normals(N);
}
void ViewerProxy::Data::set_colors(const Eigen::MatrixXd& colors) {
  viewer.data().set_colors(colors);
}

void ViewerProxy::Data::add_points(const Eigen::MatrixXd& P,
                                   const Eigen::MatrixXd& C) {
  viewer.data().add_points(P, C);
}

void ViewerProxy::Data::add_edges(const Eigen::MatrixXd& P,
                                  const Eigen::MatrixXd& E,
                                  const Eigen::MatrixXd& C) {
  viewer.data().add_edges(P, E, C);
}

void ViewerProxy::Core::align_camera_center(const Eigen::MatrixXd& V,
                                            const Eigen::MatrixXi& F) {
  viewer.core().align_camera_center(V, F);
}

void ViewerProxy::Core::align_camera_center(const Eigen::MatrixXd& P) {
  viewer.core().align_camera_center(P);
}

ViewerProxy::Data::Data()
    : point_size(viewer.data().point_size),
      show_lines(viewer.data().show_lines),
      show_faces(viewer.data().show_faces) {}

ViewerProxy::Menu::Menu()
    : callback_draw_viewer_menu(::menu.callback_draw_viewer_menu) {}
void ViewerProxy::Menu::draw_viewer_menu() { ::menu.draw_viewer_menu(); }