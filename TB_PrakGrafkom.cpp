#include <GL/glut.h>
#include <cmath>

float rotasiX = 0.0f; 
float rotasiY = 0.0f; 
float zoom = 50.0f; 
float bolaX = 0.0f;
float bolaZ = 0.0f;
bool hidden = false;
// Status pencahayaan
bool isLightOn = true;
GLfloat lightPos[] = {0.0f, 10.0f, 20.0f, 1.0f};

void hiddenCarte();

void Cartecius()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	
	glVertex3f(-100.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	
	glVertex3f(0.0, -100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	
	glVertex3f(0.0, 0.0, -100.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();
}

void setupLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Properti cahaya ambient dan diffuse
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

    // Atur cahaya sumber cahaya (LIGHT0)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void SaklarLighting() {
    if (isLightOn) {
        glDisable(GL_LIGHTING);
    } else {
        glEnable(GL_LIGHTING);
    }
    isLightOn = !isLightOn;
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    glEnable(GL_DEPTH_TEST); 
}

void drawLapang() {
	hiddenCarte();
	// Area untuk lari
    glColor3f(0.7, 0.23, 0.23); // Warna coklat muda untuk jalur lari
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, -0.6, 0.0); // Titik pusat oval
    float panjang = 25.0f; // Sumbu mayor oval (panjang)
    float lebar = 35.0f; // Sumbu minor oval (lebar)
    int ovalSegments = 100;     // Jumlah segmen untuk menggambar oval
    for (int i = 0; i <= ovalSegments; ++i) {
        float angle = 2.0f * 3.14159f * i / ovalSegments;
        float x = panjang * cos(angle);
        float z = lebar * sin(angle);
        glVertex3f(x, -0.6, z);
    }
    glEnd();
    
    //area hijau
    glColor3f(0.1, 0.2, 0.1); // Warna hijau semu gelap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, -0.2, 0.0); // Titik pusat oval sedikit lebih tinggi
    float greenOvalMajorAxis = 20.0f; // Sumbu mayor oval hijau (lebih kecil)
    float greenOvalMinorAxis = 28.0f; // Sumbu minor oval hijau (lebih kecil)
    for (int i = 0; i <= ovalSegments; ++i) {
        float angle = 2.0f * 3.14159f * i / ovalSegments;
        float x = greenOvalMajorAxis * cos(angle);
        float z = greenOvalMinorAxis * sin(angle);
        glVertex3f(x, -0.2, z);
    }
    glEnd();
    
     // Garis untuk jalur pelari
    glColor3f(1.0, 1.0, 1.0); // Warna putih untuk garis jalur
    glLineWidth(2);
    for (float offset = 0.5; offset <= 5.0; offset += 1.2) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= ovalSegments; ++i) {
            float angle = 4.0f * 3.14159f * i / ovalSegments;
            float x = (20 + offset) * cos(angle);
            float z = (30 + offset) * sin(angle);
            glVertex3f(x, -0.3, z);
        }
        glEnd();
    }
    
    // Bagian atas lapangan
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-11.0, 0.0, -21.0);
    glVertex3f(11.0, 0.0, -21.0);
    glVertex3f(11.0, 0.0, 21.0);
    glVertex3f(-11.0, 0.0, 21.0);
    glEnd();

    // Bagian bawah lapangan
    glColor3f(0.0, 0.8, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-11.0, -0.5, -21.0);
    glVertex3f(11.0, -0.5, -21.0);
    glVertex3f(11.0, -0.5, 21.0);
    glVertex3f(-11.0, -0.5, 21.0);
    glEnd();

    // Sisi-sisi lapangan
    glColor3f(0.0, 0.9, 0.0);
    glBegin(GL_QUADS);

    // Sisi depan
    glVertex3f(-11.0, 0.0, -21.0);
    glVertex3f(11.0, 0.0, -21.0);
    glVertex3f(11.0, -0.5, -21.0);
    glVertex3f(-11.0, -0.5, -21.0);

    // Sisi belakang
    glVertex3f(-11.0, 0.0, 21.0);
    glVertex3f(11.0, 0.0, 21.0);
    glVertex3f(11.0, -0.5, 21.0);
    glVertex3f(-11.0, -0.5, 21.0);

    // Sisi kiri
    glVertex3f(-11.0, 0.0, -21.0);
    glVertex3f(-11.0, 0.0, 21.0);
    glVertex3f(-11.0, -0.5, 21.0);
    glVertex3f(-11.0, -0.5, -21.0);

    // Sisi kanan
    glVertex3f(11.0, 0.0, -21.0);
    glVertex3f(11.0, 0.0, 21.0);
    glVertex3f(11.0, -0.5, 21.0);
    glVertex3f(11.0, -0.5, -21.0);

    glEnd();
}

void drawGarisLapang() {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(4);
    glBegin(GL_LINES);
    // Garis luar lapang
    glVertex3f(-10.0, 0.1, -20.0);
    glVertex3f(10.0, 0.1, -20.0);

    glVertex3f(10.0, 0.1, -20.0);
    glVertex3f(10.0, 0.1, 20.0);

    glVertex3f(10.0, 0.1, 20.0);
    glVertex3f(-10.0, 0.1, 20.0);

    glVertex3f(-10.0, 0.1, 20.0);
    glVertex3f(-10.0, 0., -20.0);

    // Garis tengah lapang
    glVertex3f(-10.0, 0.1, 0.0);
    glVertex3f(10.0, 0.1, 0.0);

    // Lingkaran tengah lapangan
    float radius = 4.0;
    int segments = 25;
    for (int i = 0; i < segments; ++i) {
        float theta1 = 2.0f * 3.14159f * i / segments;
        float theta2 = 2.0f * 3.14159f * (i + 1) / segments;
        glVertex3f(radius * cos(theta1), 0.1, radius * sin(theta1));
        glVertex3f(radius * cos(theta2), 0.1, radius * sin(theta2));
    }
    glEnd();

    //Gawang
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-3.0, -0.5, -19.9);
    glVertex3f(3.0, -0.5, -19.9);
    glVertex3f(3.0, 2.0, -19.9);
    glVertex3f(-3.0, 2.0, -19.9);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-3.0, -0.5, 19.9);
    glVertex3f(3.0, -0.5, 19.9);
    glVertex3f(3.0, 2.0, 19.9);
    glVertex3f(-3.0, 2.0, 19.9);
    glEnd();
    
    // Gambar jaring-jaring gawang
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(1);

    // jaring Gawang merah
    for (float y = 0.2f; y < 2.0f; y += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(-3.0, y, -21.0); 
        glVertex3f(3.0, y, -21.0);
        glEnd();
    }

    for (float x = -3.0f; x < 3.0f; x += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(x, 0.2f, -21.0);
        glVertex3f(x, 2.0f, -21.0);
        glEnd();
    }

    // jaring Gawang biru
    for (float y = 0.2f; y < 2.0f; y += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(-3.0, y, 21.0); 
        glVertex3f(3.0, y, 21.0);
        glEnd();
    }

    for (float x = -3.0f; x < 3.0f; x += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(x, 0.2f, 21.0);
        glVertex3f(x, 2.0f, 21.0);
        glEnd();
    }
	// jaring yang masuk kedalam
    // jaring gawang merah
    for (float y = 0.2f; y < 2.0f; y += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(-3.0, y, -19.9); 
        glVertex3f(-3.0, y, -21.0);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(3.0, y, -19.9);
        glVertex3f(3.0, y, -21.0);
        glEnd();
    }

    for (float x = -3.0f; x < 3.0f; x += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(x, 0.2f, -19.9);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(x, 2.0f, -19.9);
        glVertex3f(x, 2.0f, -21.0);
        glEnd();
    }
    
    // jaring gawang biru
    for (float y = 0.2f; y < 2.0f; y += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(3.0, y, 19.9);
        glVertex3f(3.0, y, 21.0);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(-3.0, y, 19.9);
        glVertex3f(-3.0, y, 21.0);
        glEnd();
    }

    for (float x = -3.0f; x < 3.0f; x += 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(x, 0.2f, 19.9);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(x, 2.0f, 19.9);
        glVertex3f(x, 2.0f, 21.0);
        glEnd();
    }
    // jaring-jaring di sisi lapangan
	// Sisi kiri
	for (float y = 0.2f; y < 8.0f; y += 0.2f) {
    glBegin(GL_LINES);
    glVertex3f(-11.0, y, -21.0);
    glVertex3f(-11.0, y, 21.0);
    glEnd();
	}

	for (float z = -21.0f; z < 21.0f; z += 0.5f) {
    glBegin(GL_LINES);
    glVertex3f(-11.0, 0.0f, z);
    glVertex3f(-11.0, 8.0f, z);
    glEnd();
	}

	// Sisi kanan
	for (float y = 0.2f; y < 8.0f; y += 0.2f) {
    glBegin(GL_LINES);
    glVertex3f(11.0, y, -21.0);
    glVertex3f(11.0, y, 21.0);
    glEnd();
	}

	for (float z = -21.0f; z < 21.0f; z += 0.5f) {
    glBegin(GL_LINES);
    glVertex3f(11.0, 0.0f, z);
    glVertex3f(11.0, 8.0f, z);
    glEnd();
	}
	
	// Sisi gawang merah
	for (float y = 0.2f; y < 8.0f; y += 0.2f) {
    glBegin(GL_LINES);
    glVertex3f(-11.0, y, -21.0);
    glVertex3f(11.0, y, -21.0);
    glEnd();
	}

	for (float x = -11.0f; x < 11.0f; x += 0.5f) {
    glBegin(GL_LINES);
    glVertex3f(x, 0.0f, -21.0);
    glVertex3f(x, 8.0f, -21.0);
    glEnd();
	}

	// Sisi gawang biru
	for (float y = 0.2f; y < 8.0f; y += 0.2f) {
    glBegin(GL_LINES);
    glVertex3f(11.0, y, 21.0);
    glVertex3f(-11.0, y, 21.0);
    glEnd();
	}

	for (float x = -11.0f; x < 11.0f; x += 0.5f) {
    glBegin(GL_LINES);
    glVertex3f(x, 0.0f, 21.0);
    glVertex3f(x, 8.0f, 21.0);
    glEnd();
	}

    // Area penalti
    glLineWidth(3);
    // Area penalti gawang merah
    glBegin(GL_LINES);
    glVertex3f(-5.0, 0.1, -16.0);
    glVertex3f(5.0, 0.1, -16.0);

    glVertex3f(5.0, 0.1, -20.0);
    glVertex3f(5.0, 0.1, -16.0);

    glVertex3f(-5.0, 0.1, -20.0);
    glVertex3f(-5.0, 0.1, -16.0);

    glEnd();

    // Area penalti gawang biru
    glBegin(GL_LINES);
    glVertex3f(5.0, 0.1, 16.0); 
    glVertex3f(-5.0, 0.1, 16.0);   

    glVertex3f(-5.0, 0.1, 20.0);   
    glVertex3f(-5.0, 0.1, 16.0);   

    glVertex3f(5.0, 0.1, 20.0);   
    glVertex3f(5.0, 0.1, 16.0);  
    glEnd();
}

void Lampu(float x, float z) {
	// Lampu
    glPushMatrix();
    glTranslatef(x, 9.0f, z); // Posisi lampu di atas tiang
    glScalef(0.25, 0.25, 0.25);
    glRotatef(45.0, -5.0, 0.0, 0.0);
    glColor3f(1.0f, 0.8f, 0.0f); // Warna kuning untuk lampu
    glutWireDodecahedron(); // Objek lampu
    glPopMatrix();
    
    lightPos[0] = 0.0f;
    lightPos[1] = 9.0f;
    lightPos[2] = 30.0f;
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void TiangLampu(float x, float z) {
    // Tiang
    glPushMatrix();
    glTranslatef(x, 4.0f, z); // Posisi tiang lampu
    glScalef(0.5f, 35.0f, 0.5f); // Skala tiang (tinggi dan lebar)
    glColor3f(0.5f, 0.5f, 0.5f); // Warna abu-abu untuk tiang
    glutSolidCube(0.3);
    glPopMatrix();
}


void drawBola() {
    glColor3f(0.5, 0.4, 0.7);
    glPushMatrix();
    glTranslatef(bolaX, 0.3, bolaZ);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
}

// Tambahkan fungsi untuk menggambar papan skor
void drawPapanSkor() {
    // Gambar tiang papan skor
    glColor3f(0.6, 0.6, 0.6); // Warna abu-abu untuk tiang
    glPushMatrix();
        glTranslatef(-12.0f, 3.5f, 0.0f); // Posisi tiang di kiri atas gawang
        glScalef(0.1f, 3.5f, 0.1f); // Skala tiang
        glutSolidCube(2.0); // Tiang berbentuk kubus
    glPopMatrix();

    // Gambar papan skor
    glColor3f(0.0, 0.0, 1.0); // Warna hitam untuk papan skor
    glPushMatrix();
        glTranslatef(-12.0f, 7.0f, 0.0f); // Posisi papan di atas tiang
        glRotatef(90.0, 0.0, 10.0, 0.0);
        glScalef(3.0f, 1.5f, 0.2f); // Skala papan
        glutSolidCube(1.0); // Papan berbentuk kubus
    glPopMatrix();
}

void garisAngka(float radiusX, float radiusY, int segments, float x, float y, float z) {
    glPushMatrix(); // Simpan matriks transformasi saat ini
    glTranslatef(x, y, z); // Geser lingkaran ke posisi tertentu
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // Putar lingkaran 

    glBegin(GL_LINE_LOOP); // Gambar lingkaran sebagai garis tertutup
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * 3.14159f * i / segments; // Sudut lingkaran
        float x1 = radiusX * cos(theta); // Radius di sumbu X
        float z1 = radiusY * sin(theta); // Radius di sumbu Y
        glVertex3f(x1, 0.0f, z1); // Titik oval
    }
    glEnd();

    glPopMatrix(); // Kembalikan matriks transformasi sebelumnya
}

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(string); i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 20.0, zoom, 
              0.0, 0.0, 0.0,   
              0.0, 1.0, 0.0);  

    glRotatef(rotasiX,1.0, 0.0, 0.0); 
    glRotatef(rotasiY, 0.0, 1.0, 0.0); 
    drawLapang();
    drawGarisLapang();
    drawBola();
    drawPapanSkor();
     // Pastikan pencahayaan untuk objek-objek diaktifkan sesuai status
    if (isLightOn) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }
    TiangLampu(-11.0f, -22.0f); // Sudut kiri bawah
    TiangLampu(11.0f, -22.0f);  // Sudut kanan bawah
    TiangLampu(-11.0f, 22.0f);  // Sudut kiri atas
    TiangLampu(11.0f, 22.0f);   // Sudut kanan atas
    Lampu(-11.0f, -22.0f); // Sudut kiri bawah
    Lampu(11.0f, -22.0f);  // Sudut kanan bawah
    Lampu(-11.0f, 22.0f);  // Sudut kiri atas
    Lampu(11.0f, 22.0f);   // Sudut kanan atas
    // Gambar lingkaran tengah di posisi (-12, 7, 0)
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk lingkaran
    garisAngka(0.5f, 0.3f, 20, -11.8f, 7.0f, 0.6f);
    garisAngka(0.5f, 0.3f, 20, -11.8f, 7.0f, -0.6f);
    // Matikan pencahayaan untuk menggambar teks agar warna tetap putih
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk teks
    renderBitmapString(-5.0f, 15.0f, GLUT_BITMAP_TIMES_ROMAN_24, "WELCOME TO MINI SOCCER");
    // Aktifkan kembali pencahayaan jika sebelumnya aktif
    if (isLightOn) {
        glEnable(GL_LIGHTING);
    }
	glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 10.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        if (rotasiX > -8.0)	
			rotasiX -= 1.0f;
        break;
    case 's':
        if (rotasiX < 8.0)
			rotasiX += 1.0f;
        break;
    case 'd':
        rotasiY -= 2.0f;
        break;
    case 'a':
        rotasiY += 2.0f;
        break;
    case 'q': 
        zoom -= 2.0f;
        break;
    case 'p': 
        zoom += 2.0f;
        break;
    case 'i': 
        if (bolaZ > -20.5)
            bolaZ -= 0.5f;
        break;
    case 'k': 
        if (bolaZ < 20.5)
            bolaZ += 0.5f;
        break;
    case 'j': 
        if (bolaX > -10.5)
            bolaX -= 0.5f;
        break;
    case 'l': 
        if (bolaX < 10.5)
            bolaX += 0.5f;
        break;
    case 'h': hidden = !hidden; break;
    case 'z':
    	exit(0);
    }
    glutPostRedisplay();
}

void processMenu(int option) {
    switch (option) {
        case 1:
            SaklarLighting();
            break;
        case 2:
            exit(0);
            break;
    }
}

void createMenu() {
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Saklar Lampu", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void hiddenCarte()
{
	if (hidden)
	{
		Cartecius();
	}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lapang Mini Soccer");
    init();
    setupLighting();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    createMenu();
    glutMainLoop();
    return 0;
}
