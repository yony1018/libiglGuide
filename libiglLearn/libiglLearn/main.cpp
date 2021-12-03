#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "my_path.h"
#include"out_path.h"

#include <igl/readOFF.h>
#include <igl/writeOBJ.h>

#include <igl/opengl/glfw/Viewer.h>		//去vcpkg重载glfw版
//重载libigl后
//添加	#define _CRT_SECURE_NO_WARNINGS		到代码首
//在项目的属性>配置属性>高级中，将“字符集”由“使用Unicode字符集”改为“使用多字节字符集”

Eigen::MatrixXd V1,V2;
Eigen::MatrixXi F1,F2;
Eigen::MatrixXd C;


// This function is called every time a keyboard button is pressed
bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
	std::cout << "Key: " << key << " " << (unsigned int)key << std::endl;
	if (key == '1')
	{
		// Clear should be called before drawing the mesh
		viewer.data().clear();
		// Draw_mesh creates or updates the vertices and faces of the displayed mesh.
		// If a mesh is already displayed, draw_mesh returns an error if the given V and
		// F have size different than the current ones
		viewer.data().set_mesh(V1,F1);
		viewer.core().align_camera_center(V1,F1);
	}
	else if (key == '2')
	{
		viewer.data().clear();
		viewer.data().set_mesh(V2,F2);
		viewer.core().align_camera_center(V2,F2);
	}

	return false;
}


double SumAngleAroundVertex(Eigen::MatrixXd V,Eigen::MatrixXi F)
{
	return 0.0;
}

int main(int argc, char* argv[])
{
	// Load a mesh in OFF format
	igl::readOFF(MY_PATH "bunny.off", V1, F1);	//MY_PATH是定义的静态路径
	igl::readOFF(MY_PATH "BigHand.off", V2, F2);


	// Print the vertices and faces matrices
	//数据流显示太长注释掉了
	//std::cout << "Vertices: " << std::endl << V1 << std::endl;
	//std::cout << "Faces:    " << std::endl << F1 << std::endl;

	// Save the mesh in OBJ format
	igl::writeOBJ(OUT_PATH "bunny.obj", V1, F1);
	igl::writeOBJ(OUT_PATH "BigHand.obj", V2, F2);


	std::cout << "Wanna to open viewer? y/n" << std::endl;
	char c;
	std::cin >> c;
	if (c=='y'||c=='Y')
	{
		std::cout << R"(
1 Switch to bunny mesh
2 Switch to BigHand mesh (Caution! This mesh model is quite big one)
    )";

		// Plot the mesh
		igl::opengl::glfw::Viewer viewer;
		// Register a keyboard callback that allows to switch between
		// the two loaded meshes
		viewer.callback_key_down = &key_down;
		viewer.data().set_mesh(V1, F1);		//初始打开第一个模型

		std::cout << "Wanna to coloring? y/n" << std::endl;
		std::cin >> c;
		if (c=='y'||c=='Y')
		{
			// Use the (normalized) vertex positions as colors
			C =
				(V1.rowwise() - V1.colwise().minCoeff()).array().rowwise() /
				(V1.colwise().maxCoeff() - V1.colwise().minCoeff()).array();

			// Add per-vertex colors
			viewer.data().set_colors(C);
		}
		viewer.launch();
	}


	std::cout << "Here is a math prove about 高思博内定理" << std::endl;


}