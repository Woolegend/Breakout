#include "asset.h"

GLfloat c_block_A[][3]{
    {0, 0, 0},
    {227.0 / 255.0, 135.0 / 255.0, 43.0 / 255.0},
    {255.0 / 255.0, 177.0 / 255.0, 43.0 / 255.0},
    {255.0 / 255.0, 142.0 / 255.0, 28.0 / 255.0}
};

int block_A[16][16] = {
      //-0--1--2--3--4--5--6--7--8--9-10-11-12-13-14-15
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //0
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0}, //1
        {1, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0}, //2
        {1, 2, 2, 2, 2, 1, 3, 3, 3, 3, 2, 2, 2, 2, 2, 0}, //3
        {1, 2, 2, 2, 1, 1, 0, 0, 0, 3, 3, 2, 2, 2, 2, 0}, //4
        {1, 2, 2, 2, 1, 1, 0, 1, 1, 3, 3, 0, 2, 2, 2, 0}, //5
        {1, 2, 2, 2, 1, 1, 0, 1, 1, 3, 3, 0, 2, 2, 2, 0}, //6
        {1, 2, 2, 2, 2, 0, 0, 2, 3, 3, 3, 0, 2, 2, 2, 0}, //7
        {1, 2, 2, 2, 2, 2, 2, 3, 3, 0, 0, 0, 2, 2, 2, 0}, //8
        {1, 2, 2, 2, 2, 2, 2, 3, 3, 0, 2, 2, 2, 2, 2, 0}, //9
        {1, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 0}, //10
        {1, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 2, 2, 0}, //11
        {1, 2, 0, 2, 2, 2, 2, 3, 3, 0, 2, 2, 2, 0, 2, 0}, //12
        {1, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 0}, //13
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0}, //14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  //15
};

void Asset::drawBlockA(float x, float y) {
    float scale = SCALE / 16.0;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glTranslatef(-16 / 2 * scale, 16 / 2 * scale, 0);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            glColor3fv(c_block_A[block_A[i][j]]);
            glBegin(GL_POLYGON);
            glVertex2f(j * scale, -i * scale);
            glVertex2f((j + 1) * scale, -i * scale);
            glVertex2f((j + 1) * scale, -(i + 1) * scale);
            glVertex2f(j * scale, -(i + 1) * scale);
            glEnd();
        }
    }
    glPopMatrix();
}

GLfloat c_block_B[][3]{
    {0, 0, 0},
    {219.0 / 255.0, 95.0 / 255.0, 33.0 / 255.0},
    {230.0 / 255.0, 219.0 / 255.0, 197.0 / 255.0}
};

int block_B[16][16] = {
    //-0--1--2--3--4--5--6--7--8--9-10-11-12-13-14-15
      {1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 2, 2, 2, 2, 1}, //0
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0}, //1
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0}, //2
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0}, //3
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 1, 1, 1, 0}, //4
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1}, //5
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2, 0}, //6
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0}, //7
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0}, //8
      {2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0}, //9
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 0}, //10
      {2, 2, 0, 0, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 0}, //11
      {2, 1, 2, 2, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 0}, //12
      {2, 1, 1, 1, 2, 2, 2, 0, 2, 1, 1, 1, 1, 1, 1, 0}, //13
      {2, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 0, 0}, //14
      {1, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0 ,0 ,0 ,0, 1}  //15
};

void Asset::drawBlockB(float x, float y) {
    float scale = SCALE / 16.0;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glTranslatef(-16 / 2 * scale, 16 / 2 * scale, 0);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            glColor3fv(c_block_B[block_B[i][j]]);
            glBegin(GL_POLYGON);
            glVertex2f(j * scale, -i * scale);
            glVertex2f((j + 1) * scale, -i * scale);
            glVertex2f((j + 1) * scale, -(i + 1) * scale);
            glVertex2f(j * scale, -(i + 1) * scale);
            glEnd();
        }
    }
    glPopMatrix();
}

GLfloat c_pipe[][3]{
    {0, 0, 0},
    {9.0 / 255.0, 255.0 / 255.0, 0.0},
    {182.0 / 255.0, 255.0 / 255.0, 13.0 / 255.0}
};

int pipe_head[6][16] = {
    //-0--1--2--3--4--5--6--7--8--9-10-11-12-13-14-15
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
      {0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0}, //1
      {0, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 0}, //2
      {0, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 0}, //3
      {0, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 0}, //4
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  //5
};

int pipe_body[2][16]{
      {3, 0, 2, 2, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 0, 3},
      {3, 0, 2, 2, 2, 1, 1, 2, 2, 1, 2, 2, 1, 2, 0, 3},
};

void Asset::drawPipe(float x, float y, int l, float a) {
    float scale = 80.0 / 16.0;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(a, 0, 0, 1);
    glTranslatef(-16 / 2 * scale, 0, 0);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 16; j++) {
            glColor3fv(c_pipe[pipe_head[i][j]]);
            glBegin(GL_POLYGON);
            glVertex2f(j * scale, (i + l) * scale);
            glVertex2f((j + 1) * scale, (i + l) * scale);
            glVertex2f((j + 1) * scale, (i + l + 1) * scale);
            glVertex2f(j * scale, (i + l + 1) * scale);
            glEnd();
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < 16; j++) {
            if (j == 0 || j == 15) continue;
            glColor3fv(c_pipe[pipe_body[i%2][j]]);
            glBegin(GL_POLYGON);
            glVertex2f(j * scale, i * scale);
            glVertex2f((j + 1) * scale, i * scale);
            glVertex2f((j + 1) * scale, (i + 1) * scale);
            glVertex2f(j * scale, (i + 1) * scale);
            glEnd();
        }
    }
    
    glPopMatrix();
}

GLfloat c_mush[][3]{
    {0, 0, 0},
    {1, 0, 0},
    {1, 1, 1}
};

int mush[16][16] = {
    //-0--1--2--3--4--5--6--7--8--9-10-11-12-13-14-15
      {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, //0
      {0, 0, 0, 1, 1, 3, 3, 2, 2, 2, 2, 1, 1, 0, 0, 0}, //1
      {0, 0, 1, 3, 3, 3, 3, 2, 2, 2, 2, 3, 3, 1, 0, 0}, //2
      {0, 1, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 1, 0}, //3
      {0, 1, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 3, 1, 0}, //4
      {1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1}, //5
      {1, 2, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1}, //6
      {1, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 2, 2, 3, 1}, //7
      {1, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 2, 2, 3, 3, 1}, //8
      {1, 2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 1}, //9
      {1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 1}, //10
      {0, 1, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 1, 0}, //11
      {0, 0, 1, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 1, 0, 0}, //12
      {0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0}, //13
      {0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0}, //14
      {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}  //15
};

void Asset::drawMush(float x, float y, float a) {
    float scale = SCALE / 16.0;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(a, 0, 0, 1);
    glTranslatef(-16 / 2 * scale, 16 / 2 * scale, 0);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (mush[i][j] == 0) continue;
            glColor3fv(c_mush[mush[i][j] - 1]);
            glBegin(GL_POLYGON);
            glVertex2f(j * scale, -i * scale);
            glVertex2f((j + 1) * scale, -i * scale);
            glVertex2f((j + 1) * scale, -(i + 1) * scale);
            glVertex2f(j * scale, -(i + 1) * scale);
            glEnd();
        }
    }
    glPopMatrix();
}

GLfloat c_star[][3]{
    {0, 0, 0},
    {247.0/255.0, 232.0/255.0, 25.0/255.0},
    {249.0 / 255.0, 134.0 / 255.0, 29.0 / 255.0},
    {248.0 / 255.0, 190.0 / 255.0, 27.0 / 255.0}
};

int star[16][16] = {
    //-0--1--2--3--4--5--6--7--8--9-10-11-12-13-14-15
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, //0
      {0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0}, //1
      {0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0}, //2
      {0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0}, //3
      {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1}, //4
      {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1}, //5
      {0, 1, 3, 4, 2, 2, 1, 2, 2, 1, 2, 2, 4, 3, 1, 0}, //6
      {0, 0, 1, 3, 4, 2, 1, 2, 2, 1, 2, 4, 3, 1, 0, 0}, //7
      {0, 0, 0, 1, 3, 4, 1, 2, 2, 1, 4, 3, 1, 0, 0, 0}, //8
      {0, 0, 0, 1, 3, 4, 2, 2, 2, 2, 4, 3, 1 ,0, 0, 0}, //9
      {0, 0, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 0, 0}, //10
      {0, 0, 1, 3, 4, 4, 4, 3, 3, 4, 4, 4, 3, 1, 0, 0}, //11
      {0, 1, 3, 4, 4, 3, 3, 1, 1, 3, 3, 4, 4 ,3, 1, 0}, //12
      {0, 1, 3, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 3, 1, 0}, //13
      {1, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 3, 3, 1}, //14
      {1, 1, 1, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}  //15

};

void Asset::drawStar(float x, float y, float a) {
    float scale = SCALE / 16.0;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(a, 0, 0, 1);
    glTranslatef(-16 / 2 * scale, 16 / 2 * scale, 0);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (star[i][j] == 0) continue;
            glColor3fv(c_star[star[i][j] - 1]);
            glBegin(GL_POLYGON);
            glVertex2f(j * scale, -i * scale);
            glVertex2f((j + 1) * scale, -i * scale);
            glVertex2f((j + 1) * scale, -(i + 1) * scale);
            glVertex2f(j * scale, -(i + 1) * scale);
            glEnd();
        }
    }
    glPopMatrix();
}