#include "Deformation.h"


void Deformation::update_handle_vertex_selection(const Eigen::VectorXi &new_handle_id,
                                                 const Eigen::VectorXi &new_handle_vertices)
{
    // handle_id: the vertex-to-handle index, #V x1 (-1 if vertex is free)
    // handle_vertices: list of all vertices belonging to handles, #HV x1
    // Add your code for updating the handle vertex selection here ...
}

void Deformation::get_smooth_mesh(Eigen::MatrixXd &V_res) {
    // Get the smooth mesh B
    // Store the result to V_res
}

void Deformation::get_deformed_smooth_mesh(const Eigen::MatrixXd &handle_vertex_positions, Eigen::MatrixXd &V_res) {
    // Given the handle vertex positions, get the deformed smooth mesh B'
    // Store the result to V_res
}

void Deformation::get_deformed_mesh(const Eigen::MatrixXd &handle_vertex_positions, Eigen::MatrixXd &V_res) {
    // Given the handle vertex positions, get the deformed mesh with details S'
    // Store the result to V_res
}

void Deformation::get_deformed_mesh_deformation_transfer(const Eigen::MatrixXd &handle_vertex_positions, Eigen::MatrixXd &V_res)
{
    // Implement deformation transfer here.
    // Store the result to V_res
}
