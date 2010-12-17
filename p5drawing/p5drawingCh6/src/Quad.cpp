#include "Quad.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Quad::Quad()
{
}

Quad::Quad(Vec3f vA, Vec3f vB, Vec3f vC, Vec3f vD)
{
    mVA = vA;
    mVB = vB;
    mVC = vC;
    mVD = vD;
    mColor = ColorAf(0.8f, 0.8f, 1.0f, 1.0f);
    mDie = false;
}

void Quad::draw()
{
    gl::color(mColor);
    glBegin(GL_QUADS);
    glVertex3f(mVA.x, mVA.y, mVA.z);
    glVertex3f(mVB.x, mVB.y, mVB.z);
    glVertex3f(mVC.x, mVC.y, mVC.z);
    glVertex3f(mVD.x, mVD.y, mVD.z);
    glEnd();
}

void Quad::update()
{
    mColor.a *= 0.992f;
    mVA.z = mVA.z * 1.01f - 0.5f;
    mVB.z = mVB.z * 1.01f - 0.5f;
    mVC.z = mVC.z * 1.01f - 0.5f;
    mVD.z = mVD.z * 1.01f - 0.5f;
    
    if(mColor.a < 0.0001f){
        mDie = true;
    }
}