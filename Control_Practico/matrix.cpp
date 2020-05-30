#include <iostream>
#include <cmath>
using namespace std;

const int SIZE_ARRAY = 4;

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

        void print()
        {
            for(int i = 0; i < SIZE_ARRAY; i++)
            {
                for(int j = 0; j < SIZE_ARRAY;  j++)
                {
                    cout<<this->m_matrix[i]<<" ";
                }
                cout<<endl;
            }      
            cout<<endl;   
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

        Matrix4x4 &rotate(float angle, float x, float y, float z)
        {
            float co = cos(angle);
            float se = sin(angle);

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

        Matrix4x4 &Control(float angle, float x, float y, float z, int op)
        {
            float co = cos(angle);
            float se = sin(angle);
            Matrix4x4 rotationMatX, rotationMatY, rotationMatZ, translate, scale;
            
            if(op == 1)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                            1.0f, 0.0f, 0.0f, 0.0f,
                                            0.0f, co  , -se , 0.0f,
                                            0.0f, se  , co  , 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f,             
                                            };
                rotationMatX.set(b);
                return multiply(rotationMatX);
            }
            else if(op == 2)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                            co  , 0.0f, se  , 0.0f,
                                            0.0f, 1.0f, 0.0f, 0.0f,
                                            -se , 0.0f, co  , 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f,             
                                            };
                rotationMatY.set(b);
                return multiply(rotationMatY);           
            }
            else if(op == 3)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                            co  , -se , 0.0f, 0.0f,
                                            se  , co  , 0.0f, 0.0f,
                                            0.0f, 0.0f, 1.0f, 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f,             
                                            };
                rotationMatZ.set(b);
                return multiply(rotationMatZ);
            }
            else if(op == 4)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                                1.0f, 0.0f, 0.0f, 0.0f,
                                                0.0f, 1.0f, 0.0f, 0.0f,
                                                0.0f, 0.0f, 1.0f, 0.0f,
                                                x   , y   , z   , 1.0f,
                                              };
                translate.set(b);
                return multiply(translate);
            }
            else if(op == 5)
            {
                float b[SIZE_ARRAY * SIZE_ARRAY] = { 
                                                x,    0.0f, 0.0f, 0.0f,
                                                0.0f, y,    0.0f, 0.0f,
                                                0.0f, 0.0f, z,    0.0f,
                                                0.0f, 0.0f, 0.0f, 1.0f
                                              };
                scale.set(b);
                return multiply(scale); 
            }
        }
};
