#include <Eigen/Eigen>
#include <igl/grad.h>
#include <igl/local_basis.h>
#include <imgui.h>

#include "viewer_proxy.h"

/*** insert any necessary libigl headers here ***/

using namespace std;
using namespace Eigen;
using Viewer = ViewerProxy;

#define CORE_3D viewer.core(1)
#define CORE_2D viewer.core(2)

// vertex array, #V x3
Eigen::MatrixXd V;

// face array, #F x3
Eigen::MatrixXi F;

// UV coordinates, #V x2
Eigen::MatrixXd UV;
const char *constraints[] = {"fixed boundary", "2 verts", "DOF"};
enum { UNIT_DISK_BOUNDARY, TWO_VERTICES_POSITIONS, NECESSARY_DOF };
int selected_constraint = 0;
float TextureResolution = 10;

void Redraw(ViewerProxy& viewer) {
  // Update the mesh in the viewer.
  ViewerProxy::Data mesh_data = viewer.data(0);
  ViewerProxy::Data uv_mesh_data = viewer.data(1);
  mesh_data.clear();
  mesh_data.set_mesh(V, F);
  mesh_data.set_face_based(false);
  uv_mesh_data.clear();
  if (UV.size() != 0) {
    mesh_data.set_uv(TextureResolution * UV);
    mesh_data.show_texture = true;
    uv_mesh_data.set_mesh(UV, F);
    CORE_2D.align_camera_center(UV);
  }
}

static void computeSurfaceGradientMatrix(SparseMatrix<double> &D1,
                                         SparseMatrix<double> &D2) {
  MatrixXd F1, F2, F3;
  SparseMatrix<double> DD, Dx, Dy, Dz;

  igl::local_basis(V, F, F1, F2, F3);
  igl::grad(V, F, DD);

  Dx = DD.topLeftCorner(F.rows(), V.rows());
  Dy = DD.block(F.rows(), 0, F.rows(), V.rows());
  Dz = DD.bottomRightCorner(F.rows(), V.rows());

  D1 = F1.col(0).asDiagonal() * Dx + F1.col(1).asDiagonal() * Dy +
       F1.col(2).asDiagonal() * Dz;
  D2 = F2.col(0).asDiagonal() * Dx + F2.col(1).asDiagonal() * Dy +
       F2.col(2).asDiagonal() * Dz;
}
static inline void SSVD2x2(const Eigen::Matrix2d &J, Eigen::Matrix2d &U,
                           Eigen::Matrix2d &S, Eigen::Matrix2d &V) {
  double e = (J(0) + J(3)) * 0.5;
  double f = (J(0) - J(3)) * 0.5;
  double g = (J(1) + J(2)) * 0.5;
  double h = (J(1) - J(2)) * 0.5;
  double q = sqrt((e * e) + (h * h));
  double r = sqrt((f * f) + (g * g));
  double a1 = atan2(g, f);
  double a2 = atan2(h, e);
  double rho = (a2 - a1) * 0.5;
  double phi = (a2 + a1) * 0.5;

  S(0) = q + r;
  S(1) = 0;
  S(2) = 0;
  S(3) = q - r;

  double c = cos(phi);
  double s = sin(phi);
  U(0) = c;
  U(1) = s;
  U(2) = -s;
  U(3) = c;

  c = cos(rho);
  s = sin(rho);
  V(0) = c;
  V(1) = -s;
  V(2) = s;
  V(3) = c;
}

void ConvertConstraintsToMatrixForm(const VectorXi &indices,
                                    const MatrixXd &positions,
                                    Eigen::SparseMatrix<double> &C,
                                    VectorXd &d) {
  // Convert the list of fixed indices and their fixed positions to a linear
  // system.
  // Hint: The matrix C should contain only one non-zero element per row
  // and d should contain the positions in the correct order.
}

void computeParameterization(int type) {
  VectorXi fixed_UV_indices;
  MatrixXd fixed_UV_positions;

  SparseMatrix<double> A;
  VectorXd b;
  Eigen::SparseMatrix<double> C;
  VectorXd d;
  // Find the indices of the boundary vertices of the mesh and put them in
  // fixed_UV_indices
  switch (selected_constraint) {
  case UNIT_DISK_BOUNDARY:
    // The boundary vertices should be fixed to positions on the unit disc. Find
    // these position and save them in the #V x 2 matrix fixed_UV_position.
    break;
  case TWO_VERTICES_POSITIONS:
    // Fix two UV vertices. This should be done in an intelligent way.
    // Hint: The two fixed vertices should be the two most distant one on the
    // mesh.
    break;
  case NECESSARY_DOF:
    // Add constraints for fixing only the necessary degrees of freedom for the
    // parameterization, avoiding an unnecessarily over-constrained system.
    break;
  }

  ConvertConstraintsToMatrixForm(fixed_UV_indices, fixed_UV_positions, C, d);

  // Find the linear system for the parameterization (1- Tutte, 2- Harmonic, 3-
  // LSCM, 4- ARAP) and put it in the matrix A. The dimensions of A should be
  // 2#V x 2#V.
  if (type == '1') {
    // Add your code for computing uniform Laplacian for Tutte parameterization
    // Hint: use the adjacency matrix of the mesh
  }

  if (type == '2') {
    // Add your code for computing cotangent Laplacian for Harmonic
    // parameterization Use can use a function "cotmatrix" from libIGL, but
    // ~~~~***READ THE DOCUMENTATION***~~~~
  }

  if (type == '3') {
    // Add your code for computing the system for LSCM parameterization
    // Note that the libIGL implementation is different than what taught in the
    // tutorial! Do not rely on it!!
  }

  if (type == '4') {
    // Add your code for computing ARAP system and right-hand side
    // Implement a function that computes the local step first
    // Then construct the matrix with the given rotation matrices
  }

  // Solve the linear system.
  // Construct the system as discussed in class and the assignment sheet
  // Use igl::cat to concatenate matrices
  // Use Eigen::SparseLU to solve the system. Refer to tutorial 4 for more
  // details.

  // Copy the solution to UV.
  // UV.col(0) =
  // UV.col(1) =
}

bool callback_key_down(Viewer &viewer, unsigned char key, int modifiers) {
  switch (key) {
  case '1':
  case '2':
  case '3':
  case '4':
    computeParameterization(key);
    break;
  case '+':
    TextureResolution /= 2;
    break;
  case '-':
    TextureResolution *= 2;
    break;
  }
  Redraw(viewer);
  return true;
}

bool load_mesh(Viewer& viewer, string filename) {
  viewer.load_mesh(filename, V, F);
  viewer.core().align_camera_center(V);

  return true;
}

bool callback_init(Viewer &viewer) {
  viewer.append_core();
  CORE_2D.orthographic = true;
  CORE_2D.disable_rotation();

  // Main mesh.
  viewer.data().set_visible(false, CORE_2D.id);
  // UV mesh.
  viewer.append_mesh().set_visible(false, CORE_3D.id);

  Redraw(viewer);

  return false;
}

int main(int argc, char *argv[]) {
  ViewerProxy& viewer = ViewerProxy::get_instance();
  if (argc != 2) {
    cout << "Usage ex4_bin <mesh.off/obj>" << endl;
    load_mesh(viewer, "../data/cathead.obj");
  } else {
    // Read points and normals
    load_mesh(viewer, argv[1]);
  }

  ViewerProxy::Menu menu = viewer.menu();
  menu.callback_draw_viewer_menu = [&]() {
    // Draw parent menu content
    menu.draw_viewer_menu();

    // Add new group
    if (ImGui::CollapsingHeader("Parmaterization",
                                ImGuiTreeNodeFlags_DefaultOpen)) {
      ImGui::Combo("Constraints", &selected_constraint, constraints,
                   IM_ARRAYSIZE(constraints));
      if (ImGui::SliderFloat("scale", &TextureResolution, 0, 40)) {
        Redraw(viewer);
      }

      // TODO: Add more parameters to tweak here...
    }
  };

  viewer.callback_key_down = callback_key_down;
  viewer.callback_init = callback_init;
  viewer.callback_post_resize = [&](Viewer &viewer, int w, int h) {
    CORE_2D.viewport = Eigen::Vector4f(0, 0, w / 2, h);
    CORE_3D.viewport = Eigen::Vector4f(w / 2, 0, w / 2, h);
    return false;
  };

  viewer.launch();
}
