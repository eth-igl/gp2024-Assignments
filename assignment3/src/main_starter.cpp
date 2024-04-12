#include <iostream>
#include <igl/read_triangle_mesh.h>
#include <imgui.h>
#include "viewer_proxy.h"

#include <igl/jet.h>
#include <igl/gaussian_curvature.h>
#include <igl/invert_diag.h>
#include <igl/sum.h>
#include <igl/speye.h>
#include <igl/bfs.h>
#include <igl/cotmatrix.h>
#include <igl/principal_curvature.h>
#include <igl/barycenter.h>
#include <igl/knn.h>
#include <igl/octree.h>
/*** insert any libigl headers here ***/

using namespace std;
using Viewer = ViewerProxy;


// Vertex array, #Vx3
Eigen::MatrixXd V;
// Face array, #Fx3
Eigen::MatrixXi F;
//Face normals #Fx3
Eigen::MatrixXd FN;
//Vertex normals #Vx3
Eigen::MatrixXd VN;

// Per-vertex uniform normal array, #Vx3
Eigen::MatrixXd N_uniform;
// Per-vertex area-weighted normal array, #Vx3
Eigen::MatrixXd N_area;
// Per-vertex mean-curvature normal array, #Vx3
Eigen::MatrixXd N_meanCurvature;
// Per-vertex PCA normal array, #Vx3
Eigen::MatrixXd N_PCA;
// Per-vertex quadratic fitted normal array, #Vx3
Eigen::MatrixXd N_quadraticFit;

// Per-vertex mean curvature, #Vx3
Eigen::VectorXd K_mean;
// Per-vertex Gaussian curvature, #Vx3
Eigen::VectorXd K_Gaussian;
// Per-vertex minimal principal curvature, #Vx3
Eigen::VectorXd K_min_principal;
// Per-vertex maximal principal curvature, #Vx3
Eigen::VectorXd K_max_principal;
// Per-vertex color array, #Vx3
Eigen::MatrixXd colors_per_vertex;

// Explicitely smoothed vertex array, #Vx3
Eigen::MatrixXd V_expLap;
// Implicitely smoothed vertex array, #Vx3
Eigen::MatrixXd V_impLap;
// Bilateral smoothed vertex array, #Vx3
Eigen::MatrixXd V_bilateral;

bool callback_key_down(Viewer& viewer, unsigned char key, int modifiers) {
    if (key == '1') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        // Add your code for computing uniform vertex normals here:
        // store in N_uniform

        // Use igl::per_vertex_normals to orient your normals consistently (i.e. to choose consistent signs for the normals).

        // Set the viewer normals.
        N_uniform.rowwise().normalize();
        viewer.data().set_normals(N_uniform);
    }

    if (key == '2') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        // Add your code for computing area-weighted vertex normals here:
        // store in N_area

        // Use igl::per_vertex_normals to orient your normals consistently (i.e. to choose consistent signs for the normals).

        // Set the viewer normals.
        N_area.rowwise().normalize();
        viewer.data().set_normals(N_area);
    }

    if (key == '3') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        // Add your code for computing mean-curvature vertex normals here:
        // store in N_meanCurvature

        // Use igl::per_vertex_normals to orient your normals consistently (i.e. to choose consistent signs for the normals).
    
        // Set the viewer normals.
        N_meanCurvature.rowwise().normalize();
        viewer.data().set_normals(N_meanCurvature);
    }

    if (key == '4') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        // Add your code for computing PCA vertex normals here:
        // store in N_PCA

        // Use igl::per_vertex_normals to orient your normals consistently (i.e. to choose consistent signs for the normals).

        // Set the viewer normals.
        N_PCA.rowwise().normalize();
        viewer.data().set_normals(N_PCA);
    }

    if (key == '5') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        // Add your code for computing quadratic fitted vertex normals here:
        // store in N_quadraticFit

        // Use igl::per_vertex_normals to orient your normals consistently (i.e. to choose consistent signs for the normals).

        // Set the viewer normals.
        N_quadraticFit.rowwise().normalize();
        viewer.data().set_normals(N_quadraticFit);
    }

    if (key == '6') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        colors_per_vertex.setZero(V.rows(),3);
        // Add your code for computing the discrete mean curvature:
        // store in K_mean

        // For visualization, better to normalize the range of K_mean with the maximal and minimal curvatures.
        // store colors in colors_per_vertex

        // Set the viewer colors
        viewer.data().set_colors(colors_per_vertex);
    }

    if (key == '7') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        colors_per_vertex.setZero(V.rows(),3);
        // Add your code for computing the discrete Gaussian curvature:
        // store in K_Gaussian

        // For visualization, better to normalize the range of K_Gaussian with the maximal and minimal curvatures.
        // store colors in colors_per_vertex

        // Set the viewer colors
        viewer.data().set_colors(colors_per_vertex);
    }

    if (key == '8') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        colors_per_vertex.setZero(V.rows(),3);
        // Add your code for computing the discrete minimal principal curvature:
        // store in K_min_principal
       
        // For visualization, better to normalize the range of K_min_principal with the maximal and minimal curvatures.
        // store colors in colors_per_vertex

        // Uncomment the code below to draw a blue segment parallel to the minimal curvature direction, 
        
        // const double avg = igl::avg_edge_length(V,F);
        // Eigen::Vector3d blue(0.2,0.2,0.8);
        // viewer.data().add_edges(V + PD_min*avg, V - PD_min*avg, blue);
        
        // Set the viewer colors
        viewer.data().set_colors(colors_per_vertex);
    }

    if (key == '9') {
        viewer.data().clear();
        viewer.data().set_mesh(V, F);
        colors_per_vertex.setZero(V.rows(),3);
        // Add your code for computing the discrete maximal principal curvature:
        // store in K_max_principal

        // For visualization, better to normalize the range of K_max_principal with the maximal and minimal curvatures
        // store colors in colors_per_vertex
        
        // Uncomment the code below to draw a red segment parallel to the maximal curvature direction
        
        // const double avg = igl::avg_edge_length(V,F);
        // Eigen::Vector3d red(0.8,0.2,0.2);
        // viewer.data().add_edges(V + PD_max*avg, V - PD_max*avg, red);
        
        // Set the viewer colors
        viewer.data().set_colors(colors_per_vertex);
    }

    if (key == 'E') {
        // Add your code for computing explicit Laplacian smoothing here:
        // store the smoothed vertices in V_expLap
        V_expLap = V;

        // Set the smoothed mesh
        viewer.data().clear();
        viewer.data().set_mesh(V_expLap, F);
    }

    if (key == 'D'){
        // Implicit smoothing for comparison
        // store the smoothed vertices in V_impLap
        V_impLap = V;

        // Set the smoothed mesh
        viewer.data().clear();
        viewer.data().set_mesh(V_impLap, F);
    }

    if (key == 'B') {
        // Add your code for computing bilateral smoothing here:
        // store the smoothed vertices in V_bilateral
        // be careful of the sign mistake in the paper
        // use v' = v - n * (sum / normalizer) to update
        V_bilateral = V;

        // Set the smoothed mesh
        viewer.data().clear();
        viewer.data().set_mesh(V_bilateral, F);
    }


    return true;
}

bool load_mesh(Viewer& viewer,string filename, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
    igl::read_triangle_mesh(filename, V, F);
    viewer.data().clear();
    viewer.data().set_mesh(V,F);
    viewer.data().compute_normals();
    viewer.core().align_camera_center(V, F);
    return true;
}

int main(int argc, char *argv[]) {
    // Show the mesh
    Viewer& viewer = Viewer::get_instance();
    Viewer::Menu& menu = viewer.menu();
    viewer.callback_key_down = callback_key_down;

    std::string filename;
    if (argc == 2) {
        filename = std::string(argv[1]);
    }
    else {
        filename = std::string("../data/bumpy-cube.obj");
    }
    load_mesh(viewer,filename,V,F);

    callback_key_down(viewer, '1', 0);
    
    viewer.launch();
}
