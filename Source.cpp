#include <GL/glut.h>
#include <iostream>
const int n = 50;
const int k = 10;
int difficulty = 3; // the smaller the harder
int difficult = 35 + 15 * difficulty;

void myinit(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

class Cell
{
public:
    bool mine;
    bool flag;
    bool status;
    int CountAroundMine = 0;
    float x;
    float y;
};
Cell cell[k][k];

void Field()
{
    glColor3f(1, 1, 1);
    glLoadIdentity();
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            glVertex2f(-0.899 + 0.2 * i, -0.899 + 0.2 * j);

            cell[i][j].x = -0.899 + 0.2 * i;
            cell[i][j].y = -0.899 + 0.2 * j;

            if ((rand() % 100 + 1) > difficult) { cell[i][j].mine = true; }

            if (cell[i][j].mine == true)
            {
                if (i > 0 && i < 9 && j>0 && j < 9)
                {
                    cell[i - 1][j].CountAroundMine += 1;
                    cell[i + 1][j].CountAroundMine += 1;
                    cell[i][j + 1].CountAroundMine += 1;
                    cell[i][j - 1].CountAroundMine += 1;
                    cell[i + 1][j + 1].CountAroundMine += 1;
                    cell[i - 1][j + 1].CountAroundMine += 1;
                    cell[i + 1][j - 1].CountAroundMine += 1;
                    cell[i - 1][j - 1].CountAroundMine += 1;
                }
                if (i == 0 && j == 0)
                {
                    cell[i + 1][j].CountAroundMine += 1;
                    cell[i][j + 1].CountAroundMine += 1;
                    cell[i + 1][j + 1].CountAroundMine += 1;
                }
                if (i == 9 && j == 9)
                {
                    cell[i - 1][j].CountAroundMine += 1;
                    cell[i][j - 1].CountAroundMine += 1;
                    cell[i - 1][j - 1].CountAroundMine += 1;
                }
                if (i == 0 && j != 0)
                {
                    cell[i + 1][j].CountAroundMine += 1;
                    cell[i][j + 1].CountAroundMine += 1;
                    cell[i][j - 1].CountAroundMine += 1;
                    cell[i + 1][j + 1].CountAroundMine += 1;
                    cell[i + 1][j - 1].CountAroundMine += 1;
                }
                if (i == 9 && j != 9)
                {
                    cell[i - 1][j].CountAroundMine += 1;
                    cell[i][j + 1].CountAroundMine += 1;
                    cell[i][j - 1].CountAroundMine += 1;
                    cell[i - 1][j + 1].CountAroundMine += 1;
                    cell[i - 1][j - 1].CountAroundMine += 1;
                }
                if (j == 0 && i != 0)
                {
                    cell[i - 1][j].CountAroundMine += 1;
                    cell[i + 1][j].CountAroundMine += 1;
                    cell[i][j + 1].CountAroundMine += 1;
                    cell[i + 1][j + 1].CountAroundMine += 1;
                    cell[i - 1][j + 1].CountAroundMine += 1;
                }
                if (j == 9 && i != 9)
                {
                    cell[i - 1][j].CountAroundMine += 1;
                    cell[i + 1][j].CountAroundMine += 1;
                    cell[i][j - 1].CountAroundMine += 1;
                    cell[i + 1][j - 1].CountAroundMine += 1;
                    cell[i - 1][j - 1].CountAroundMine += 1;
                }
            }
        }
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void Mine(float x, float y)
{
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void Mine()
{
    glColor3f(1, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (cell[i][j].mine == true)
            {
                glVertex2f(cell[i][j].x, cell[i][j].y);
            }
        }
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void flag(float x, float y)
{
    float r = 0.025;
    glColor3f(0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2f(x + r, y + r * 2);
    glVertex2f(x + r, y - r * 2);
    glEnd();
    glPopMatrix();


    glColor3f(1, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex2f(x + r, y + r * 2);
    glVertex2f(x + r, y);
    glVertex2f(x - r, y + r);
    glEnd();
    glPopMatrix();

    glFlush();
}

void Num(int a, float x, float y)
{
    float r = 0.05;
    glColor3f(0, 0, 1);
    glLoadIdentity();
    glPushMatrix();
    glBegin(GL_LINES);
    switch (a)
    {
    case 1:
        glVertex2f(x, y + r);
        glVertex2f(x, y - r);
        glEnd();
        break;

    case 2:
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y);
        glVertex2f(x - r, y);
        glVertex2f(x - r, y - r);
        glVertex2f(x + r, y - r);
        glEnd();
        break;

    case 3:
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y - r);
        glVertex2f(x + r, y);
        glVertex2f(x - r, y);
        glVertex2f(x + r, y - r);
        glVertex2f(x - r, y - r);
        glEnd();
        break;

    case 4:
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y - r);
        glVertex2f(x - r, y + r);
        glVertex2f(x - r, y);
        glVertex2f(x - r, y);
        glVertex2f(x + r, y);
        glEnd();
        break;

    case 5:
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + r, y + r);
        glVertex2f(x - r, y + r);
        glVertex2f(x - r, y);
        glVertex2f(x + r, y);
        glVertex2f(x + r, y - r);
        glVertex2f(x - r, y - r);
        glEnd();
        break;

    case 6:
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x - r, y + r);
        glVertex2f(x - r, y - r);
        glVertex2f(x + r, y);
        glVertex2f(x - r, y);
        glVertex2f(x + r, y - r);
        glVertex2f(x - r, y - r);
        glVertex2f(x + r, y);
        glVertex2f(x + r, y - r);
        glEnd();
        break;

    case 7:
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x - r, y - r);
        glEnd();
        break;

    case 8:
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y - r);
        glVertex2f(x + r, y);
        glVertex2f(x - r, y);
        glVertex2f(x + r, y - r);
        glVertex2f(x - r, y - r);
        glVertex2f(x - r, y - r);
        glVertex2f(x - r, y + r);
        glEnd();
        break;

    case 9:
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y - r);
        glVertex2f(x + r, y);
        glVertex2f(x - r, y);
        glVertex2f(x + r, y - r);
        glVertex2f(x - r, y - r);
        glVertex2f(x - r, y);
        glVertex2f(x - r, y + r);
        glEnd();
        break;

    case 0:
        glVertex2f(x + r / 2, y + r);
        glVertex2f(x + r / 2, y - r);
        glVertex2f(x + r / 2, y - r);
        glVertex2f(x - r / 2, y - r);
        glVertex2f(x - r / 2, y - r);
        glVertex2f(x - r / 2, y + r);
        glVertex2f(x - r / 2, y + r);
        glVertex2f(x + r / 2, y + r);
        glEnd();

    default:
        glEnd();
        break;
    }
    glPopMatrix();
    glFlush();
}

void Num()
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            Num(cell[i][j].CountAroundMine, cell[i][j].x, cell[i][j].y);
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    //cout << button << "\t" << state << "\t" << x << "\t" << y << "\n";
    if (button == 0)
    {
        if (cell[x / 50][9 - y / 50].mine == false)
        {
            Num(cell[x / 50][9 - y / 50].CountAroundMine, cell[x / 50][9 - y / 50].x, cell[x / 50][9 - y / 50].y);
        }
        else { Num(); Mine(); }
    }

    if (button == 2)
    {
        flag(cell[x / 50][9 - y / 50].x, cell[x / 50][9 - y / 50].y);
    }
}

void display()
{
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(n - 1.0);
    Field();
    glPointSize(20.0);
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(n * 10, n * 10);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Saper");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}