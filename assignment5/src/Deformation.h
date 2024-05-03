#ifndef ex6_Solution_h
#define ex6_Solution_h

#include <Eigen/Core>


class Deformation
{
public:
    // DO NOT change the signature of any public members.
    // DO NOT add/remove any new public members.
    Eigen::MatrixXi F;   // Faces of the original mesh
    void set_initial_mesh(const Eigen::MatrixXd& V_, const Eigen::MatrixXi& F_) {
        V_original = V_;
        F = F_;
    }
    void update_handle_vertex_selection(const Eigen::VectorXi&, const Eigen::VectorXi&);
    void get_smooth_mesh(Eigen::MatrixXd&);
    void get_deformed_smooth_mesh(const Eigen::MatrixXd&, Eigen::MatrixXd&);
    void get_deformed_mesh(const Eigen::MatrixXd&, Eigen::MatrixXd&);
    void get_deformed_mesh_deformation_transfer(const Eigen::MatrixXd&, Eigen::MatrixXd&);

private:
    // Add other private members and methods here as needed here.
    Eigen::MatrixXd V_original;  // Vertices of the original mesh
};

#endif
