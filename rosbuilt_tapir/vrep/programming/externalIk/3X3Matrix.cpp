// This file is part of the EXTERNAL IK for V-REP
// 
// Copyright 2006-2014 Coppelia Robotics GmbH. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// The EXTERNAL IK is licensed under the terms of EITHER:
//   1. EXTERNAL IK commercial license (contact us for details)
//   2. EXTERNAL IK educational license (see below)
// 
// EXTERNAL IK educational license:
// -------------------------------------------------------------------
// The EXTERNAL IK educational license applies only to EDUCATIONAL
// ENTITIES composed by following people and institutions:
// 
// 1. Hobbyists, students, teachers and professors
// 2. Schools and universities
// 
// EDUCATIONAL ENTITIES do NOT include companies, research institutions,
// non-profit organisations, foundations, etc.
// 
// An EDUCATIONAL ENTITY may use, modify, compile and distribute the
// modified/unmodified EXTERNAL IK under following conditions:
//  
// 1. Distribution should be free of charge.
// 2. Distribution should be to EDUCATIONAL ENTITIES only.
// 3. Usage should be non-commercial.
// 4. Altered source versions must be plainly marked as such and distributed
//    along with any compiled code.
// 5. The origin of the EXTERNAL IK must not be misrepresented. you must
//    not claim that you wrote the original software.
// 
// THE EXTERNAL IK IS DISTRIBUTED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY. THE USER WILL USE IT AT HIS/HER OWN RISK. THE ORIGINAL
// AUTHORS AND COPPELIA ROBOTICS GMBH WILL NOT BE LIABLE FOR DATA LOSS,
// DAMAGES, LOSS OF PROFITS OR ANY OTHER KIND OF LOSS WHILE USING OR
// MISUSING THIS SOFTWARE.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.1.2 on June 16th 2014

#include "3X3Matrix.h"
#include "4Vector.h"
#include "MyMath.h"


C3X3Matrix::C3X3Matrix()
{

}

C3X3Matrix::C3X3Matrix(const C3Vector& xAxis,const C3Vector& yAxis,const C3Vector& zAxis)
{
	(*this).axis[0]=xAxis;
	(*this).axis[1]=yAxis;
	(*this).axis[2]=zAxis;
}

C3X3Matrix::C3X3Matrix(const C4Vector& q)
{
	(*this)=q.getMatrix();
}

C3X3Matrix::C3X3Matrix(const C3X3Matrix& m)
{
	(*this).axis[0]=m.axis[0];
	(*this).axis[1]=m.axis[1];
	(*this).axis[2]=m.axis[2];
}

C3X3Matrix::~C3X3Matrix()
{

}

void C3X3Matrix::setEulerAngles(float a,float b,float g)
{ // a,b anf g are in radian!
	float A=(float)cos(a);
    float B=(float)sin(a);
    float C=(float)cos(b);
    float D=(float)sin(b);
    float E=(float)cos(g);
    float F=(float)sin(g);
    float AD=A*D;
    float BD=B*D;
    axis[0](0)=C*E;
    axis[1](0)=-C*F;
    axis[2](0)=D;
    axis[0](1)=BD*E+A*F;
    axis[1](1)=-BD*F+A*E;
    axis[2](1)=-B*C;
    axis[0](2)=-AD*E+B*F;
    axis[1](2)=AD*F+B*E;
    axis[2](2)=A*C;
}

void C3X3Matrix::setEulerAngles(const C3Vector& v)
{ // v(0), v(1), v(2) are in radian!
	setEulerAngles(v(0),v(1),v(2));
}

C3Vector C3X3Matrix::getEulerAngles() const
{ // Angles are in radians!! // THERE IS ANOTHER SUCH ROUTINE IN C4X4MATRIX
	C3Vector retV;
	float m02=axis[2](0);
	if (m02>1.0f)
		m02=1.0f;	// Just in case
	if (m02<-1.0f)
		m02=-1.0f;	// Just in case
	
	retV(1)=CMath::robustAsin(m02);
	if (m02<0.0f)
		m02=-m02;
	if (m02<0.999995f)
	{	// No gimbal lock
		retV(0)=(float)atan2(-axis[2](1),axis[2](2));
		retV(2)=(float)atan2(-axis[1](0),axis[0](0));
	}
	else
	{	// Gimbal lock has occured
		retV(0)=0.0f;
		retV(2)=(float)atan2(axis[0](1),axis[1](1));
	}
	return(retV);
}

C4Vector C3X3Matrix::getQuaternion() const
{	
	C4Vector retV;
	float trace=axis[0](0)+axis[1](1)+axis[2](2);
	if (trace>=0.0f)	// trace>0.00000001f)
	{
		float s=sqrtf(trace+1.0f)*2.0f;
		retV(1)=(axis[1](2)-axis[2](1))/s;
		retV(2)=(axis[2](0)-axis[0](2))/s;
		retV(3)=(axis[0](1)-axis[1](0))/s;
		retV(0)=0.25f*s;
	}
	else
	{
		if ((axis[0](0)>=axis[1](1))&&(axis[0](0)>=axis[2](2)))
		{
			float s=sqrtf(1.0f+axis[0](0)-axis[1](1)-axis[2](2))*2.0f;
			retV(1)=0.25f*s;
			retV(2)=(axis[0](1)+axis[1](0))/s;
			retV(3)=(axis[2](0)+axis[0](2))/s;
			retV(0)=(axis[1](2)-axis[2](1))/s;
		}
		else
		{
			if ((axis[1](1)>=axis[0](0))&&(axis[1](1)>=axis[2](2)))
			{
				float s=sqrtf(1.0f+axis[1](1)-axis[0](0)-axis[2](2))*2.0f;
				retV(1)=(axis[0](1)+axis[1](0))/s;
				retV(2)=0.25f*s;
				retV(3)=(axis[1](2)+axis[2](1))/s;
				retV(0)=(axis[2](0)-axis[0](2))/s;
			}
			else
			{
				float s=sqrtf(1.0f+axis[2](2)-axis[0](0)-axis[1](1))*2.0f;
				retV(1)=(axis[2](0)+axis[0](2))/s;
				retV(2)=(axis[1](2)+axis[2](1))/s;
				retV(3)=0.25f*s;
				retV(0)=(axis[0](1)-axis[1](0))/s;
			}
		}
	}
	retV.normalize(); // Really needed?
	return(retV);
}

void C3X3Matrix::buildInterpolation(const C3X3Matrix& fromThis,const C3X3Matrix& toThat,float t)
{	// Builds the interpolation (based on t) from 'fromThis' to 'toThat'
	C4Vector out;
	out.buildInterpolation(fromThis.getQuaternion(),toThat.getQuaternion(),t);
	(*this)=out;
}

void C3X3Matrix::buildXRotation(float angle)
{
	float c=(float)cos(angle);
	float s=(float)sin(angle);
	axis[0](0)=1.0f;
	axis[1](0)=0.0f;
	axis[2](0)=0.0f;
	axis[0](1)=0.0f;
	axis[1](1)=c;
	axis[2](1)=-s;
	axis[0](2)=0.0f;
	axis[1](2)=s;
	axis[2](2)=c;
}

void C3X3Matrix::buildYRotation(float angle)
{
	float c=(float)cos(angle);
	float s=(float)sin(angle);
	axis[0](0)=c;
	axis[1](0)=0.0f;
	axis[2](0)=s;
	axis[0](1)=0.0f;
	axis[1](1)=1.0f;
	axis[2](1)=0.0f;
	axis[0](2)=-s;
	axis[1](2)=0.0f;
	axis[2](2)=c;
}

void C3X3Matrix::buildZRotation(float angle)
{
	float c=(float)cos(angle);
	float s=(float)sin(angle);
	axis[0](0)=c;
	axis[1](0)=-s;
	axis[2](0)=0.0f;
	axis[0](1)=s;
	axis[1](1)=c;
	axis[2](1)=0.0f;
	axis[0](2)=0.0f;
	axis[1](2)=0.0f;
	axis[2](2)=1.0f;
}

C3Vector C3X3Matrix::getNormalVector() const
{ // returns the normal vector to the plane described by axis[0],axis[1],axis[2]
	C3Vector v0(axis[0]-axis[1]);
	C3Vector v1(axis[1]-axis[2]);
	return((v0^v1).getNormalized());
}
