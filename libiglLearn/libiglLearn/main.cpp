#include <igl/readOFF.h>
#include <igl/writeOBJ.h>
#include <iostream>
//#include "tutorial_shared_path.h"

Eigen::MatrixXd V;
Eigen::MatrixXi F;

int main(int argc, char* argv[])
{
	// Load a mesh in OFF format
	igl::readOFF("C:/Users/16708/source/repos/yony1018/libiglGuide/MeshFiles/bunnyhole.off", V, F);

	// Print the vertices and faces matrices
	std::cout << "Vertices: " << std::endl << V << std::endl;
	std::cout << "Faces:    " << std::endl << F << std::endl;

	// Save the mesh in OBJ format
	igl::writeOBJ("cube.obj", V, F);
}