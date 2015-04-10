
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using std::cout;
using std::endl;

#include <armadillo>
using arma::vec;

#include "ray.h"
#include "scene.h"
#include "plane.h"
#include "sphere.h"
#include "config.h"

int window;

float framebuffer[HEIGHT][WIDTH][3];

void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels( WIDTH, HEIGHT, GL_RGB, GL_FLOAT, framebuffer );
    glFlush();
}

// Clears framebuffer to black
void onClearFramebuffer() {
	// init frame buffer to black
	for ( int i = 0; i < HEIGHT; i++ ) {
		for ( int j = 0; j < WIDTH; j++ ) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

void onRenderSceneOne()
{
	onClearFramebuffer();

	cout << "Rendering Scene 1... " << endl;

	scene scene(vec("-18 0 3"));

	// plane
	plane plane(	vec("0 0 -5"),
					vec("0 0 1"),
					fvec("0.3 0.3 0.3"),
					fvec("0.0 0.0 0.0"),
					0.0);
	scene.add_surface(&plane);

	// lights
	light light_forward(vec("0 0 18"),
						fvec("0.5 0.5 0.5"));
	scene.add_light(&light_forward);

	light light_back_left(	vec("18 -6 18"),
							fvec("1.0 0.0 0.0"));
	scene.add_light(&light_back_left);

	light light_back_right(	vec("18 6 18"),
							fvec("0.0 1.0 0.0"));
	scene.add_light(&light_back_right);

	// spheres
	sphere sphere_center(	vec("0 0 4"),
							1.0,
							fvec("0.0 0.8 0.0"),
							fvec("0.0 0.0 0.0"),
							0.0);
	scene.add_surface(&sphere_center);

	sphere sphere_center_bottom(vec("-6 0 0"),
								1.0,
								fvec("0.9 0.0 0.0"),
								fvec("0.1 0.0 0.0"),
								0.0);
	scene.add_surface(&sphere_center_bottom);

	sphere sphere_left(		vec("0 -7 0"),
							2.0,
							fvec("0.0 0.0 1.0"),
							fvec("0.0 0.0 0.0"),
							0.0);
	scene.add_surface(&sphere_left);

	sphere sphere_right(	vec("0 7 0"),
							2.0,
							fvec("0.0 0.0 1.0"),
							fvec("0.0 0.0 0.0"),
							0.0);
	scene.add_surface(&sphere_right);

	scene.render(framebuffer);

    glutPostRedisplay();
}

void onKeyPress( unsigned char key, int x, int y ) {
	switch ((char) key) {
	case 'q':
	case 27: // esc key
		cout << "Exiting..." << endl;
		glutDestroyWindow( window );
		exit( 0 );
		break;
	case '1':
		onClearFramebuffer();
		onRenderSceneOne();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    window = glutCreateWindow("Robert Timm - Homework 5");

    glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutKeyboardFunc( onKeyPress );
    glutDisplayFunc( onDisplay );

    cout << "Controls:" << endl;
    cout << "\t 'q' to quit" << endl;
    cout << "\t '1' to render scene 1" << endl;

    onRenderSceneOne();

    glutMainLoop();
    return 0;
}
