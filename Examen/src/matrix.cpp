#include <iostream>
#include <cmath>
using namespace std;

const int SIZE_ARRAY = 4;

class vector
{
    public:
    float m_vector[SIZE_ARRAY] = { 0.0f, 0.0f, 0.0f, 1.0f};
    vector(){}
    void set(float x, float y, float z)
    {
        m_vector[0] = x;
        m_vector[1] = y;
        m_vector[2] = z;
    }


};

class Matrix4x4
{
    public:
        float m_matrix[SIZE_ARRAY * SIZE_ARRAY]  = {1.0f, 0.0f, 0.0f, 0.0f,
                                                    0.0f, 1.0f, 0.0f, 0.0f,
                                                    0.0f, 0.0f, 1.0f, 0.0f,
                                                    0.0f, 0.0f, 0.0f, 1.0f
                                                   };

        Matrix4x4(){}

        void set(float mat[SIZE_ARRAY * SIZE_ARRAY])
        {
            for (int i = 0; i < SIZE_ARRAY * SIZE_ARRAY; i++)
            {
                this->m_matrix[i] = mat[i];
            }
            
        }
        
        const float *dataPtr() const 
        {
            return this->m_matrix; 
        }

        Matrix4x4 &multiply(const Matrix4x4 &mat)
        {
            const float *A = dataPtr();
            const float *B = mat.dataPtr();
            //float C[SIZE_ARRAY * SIZE_ARRAY];

            for(int i = 0; i < SIZE_ARRAY; i++)
            {
                for (int j = 0; j < SIZE_ARRAY; j++)
                {
                    this->m_matrix[i * SIZE_ARRAY + j] = A[0*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 0] + A[1*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 1] + A[2*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 2] +  A[3*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 3];
                }
            }
            return *this;
        }
        
        void multiply(float result[SIZE_ARRAY * SIZE_ARRAY], const Matrix4x4 &mat)
        {
            const float *A = dataPtr();
            const float *B = mat.dataPtr();
            //float C[SIZE_ARRAY * SIZE_ARRAY];

            for(int i = 0; i < SIZE_ARRAY; i++)
            {
                for (int j = 0; j < SIZE_ARRAY; j++)
                {
                    result[i * SIZE_ARRAY + j] = A[0*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 0] + A[1*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 1] + A[2*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 2] +  A[3*SIZE_ARRAY+j] * B[i*SIZE_ARRAY + 3];
                }
            }
        }

        Matrix4x4 &rotate(int angle, float x, float y, float z)
        {
            float angulo = (3.1415926*angle)/180.0;
            float co = cos(angulo);
            float se = sin(angulo);

            Matrix4x4 rotationMat;
            if(x == 1.0f)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                            1.0f, 0.0f, 0.0f, 0.0f,
                                            0.0f, co  , -se , 0.0f,
                                            0.0f, se  , co  , 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f,             
                                            };
                rotationMat.set(b);
            }
            else if(y == 1.0f)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                            co  , 0.0f, se  , 0.0f,
                                            0.0f, 1   , 0.0f, 0.0f,
                                            -se , 0.0f, co  , 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f,             
                                            };
                rotationMat.set(b);
            }
            else if(z == 1.0f)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                            co  , -se, 0.0f  , 0.0f,
                                            se , co   , 0.0f, 0.0f,
                                            0.0f , 0.0f, 1  , 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f,             
                                            };
                rotationMat.set(b);
            }
            
            return multiply(rotationMat);
        }

        Matrix4x4 &scale(float x, float y, float z)
        {
            Matrix4x4 scaleMat;
            float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                                x,    0.0f, 0.0f, 0.0f,
                                                0.0f, y,    0.0f, 0.0f,
                                                0.0f, 0.0f, z,    0.0f,
                                                0.0f, 0.0f, 0.0f, 1.0f
                                              };
            scaleMat.set(b);
            return multiply(scaleMat);
        }    
   
        Matrix4x4 &translate(float x, float y, float z)
        {
           Matrix4x4 transMat;
           float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                                1.0f, 0.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f, 0.0f,
                                                0.0f, 0.0f, 1.0f, 0.0f,
                                                x   , y   , z   , 1.0f,
                                              };
           transMat.set(b);
           return multiply(transMat);
        }

        void mul_rotZ(float entrada[SIZE_ARRAY * SIZE_ARRAY], float result[SIZE_ARRAY * SIZE_ARRAY], int angle)
        {
            float PI = 3.1415926;
            float angulo = (PI * angle) / 180.0;
            float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                                cos(angulo), -sin(angulo), 0.0f, 0.0f,
                                                sin(angulo), cos(angulo), 0.0f, 0.0f,
                                                0.0f, 0.0f, 1.0f, 0.0f,
                                                0.0f, 0.0f, 0.0f, 1.0f,
                                               };
            
        }
};

class Vector
{
    public:
        float m_matrix[SIZE_ARRAY];
        Vector();
        float get(int  row, int col);
        void set(int row, int col, float value);
        void setIdentity();

        float *AsArray();

};

