#include "com_github_fabianmurariu_unsafe_GRBCORE.h"
#include <stdlib.h>
#include <jni.h>
#include "GraphBLAS.h"
#include <assert.h>
void check_grb_error(GrB_Info info);

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_initNonBlocking
            (JNIEnv * env, jclass cls) {
            check_grb_error(GrB_init(GrB_NONBLOCKING) );
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_grbWait
            (JNIEnv * env, jclass cls) {
            check_grb_error(GrB_wait());
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_grbFinalize
            (JNIEnv * env, jclass cls) {
            check_grb_error(GrB_finalize());
            }

            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_createMatrix
            (JNIEnv * env, jclass cls, jobject tpe, jlong rows, jlong cols) {
            GrB_Type grb_type = (GrB_Type) (*env)->GetDirectBufferAddress(env, tpe);
            GrB_Matrix A;
            GrB_Index mat_rows = rows;
            GrB_Index mat_cols = cols;
            check_grb_error (GrB_Matrix_new(&A, grb_type, mat_rows, mat_cols) );
            return (*env)->NewDirectByteBuffer(env, A, 0);
            }

            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_createVector
            (JNIEnv * env, jclass cls, jobject tpe, jlong size) {
            GrB_Type grb_type = (GrB_Type) (*env)->GetDirectBufferAddress(env, tpe);
            GrB_Vector A;
            GrB_Index vec_size = size;
            check_grb_error (GrB_Vector_new(&A, grb_type, vec_size) );
            return (*env)->NewDirectByteBuffer(env, A, 0);
            }

            JNIEXPORT jlong JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_nvalsMatrix
            (JNIEnv * env, jclass cls, jobject mat) {
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
            GrB_Index n;
            check_grb_error(GrB_Matrix_nvals(&n, A) );
            return n;
            }

            JNIEXPORT jlong JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_nvalsVector
            (JNIEnv * env, jclass cls, jobject mat) {
            GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, mat);
            GrB_Index n;
            check_grb_error(GrB_Vector_nvals(&n, A) );
            return n;
            }

            JNIEXPORT jlong JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_nrows
            (JNIEnv * env, jclass cls, jobject mat) {
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
            GrB_Index n;
            check_grb_error(GrB_Matrix_nrows(&n, A) );
            return n;
            }


            JNIEXPORT jlong JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_ncols
            (JNIEnv * env, jclass cls, jobject mat) {
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
            GrB_Index n;
            check_grb_error(GrB_Matrix_ncols(&n, A) );
            return n;
            }

            JNIEXPORT jlong JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_size
            (JNIEnv * env, jclass cls, jobject mat) {
            GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, mat);
            GrB_Index n;
            check_grb_error(GrB_Vector_size(&n, A) );
            return n;
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_freeMatrix
            (JNIEnv * env, jclass cls, jobject mat) {
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
            check_grb_error(GrB_Matrix_free(&A) );
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_freeVector
            (JNIEnv * env, jclass cls, jobject vec) {
            GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, vec);
            check_grb_error(GrB_Vector_free(&A) );
            }

        JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_freeMonoid
          (JNIEnv * env, jclass cls, jobject monoid) {
            GrB_Monoid A = (GrB_Monoid) (*env)->GetDirectBufferAddress(env, monoid);
            check_grb_error(GrB_Monoid_free(&A));
          }
            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_resizeMatrix
            (JNIEnv * env, jclass cls, jobject mat, jlong rows, jlong cols) {
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
            GrB_Index mat_rows = rows;
            GrB_Index mat_cols = cols;
            check_grb_error(GxB_Matrix_resize(A, mat_rows, mat_cols));
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_resizeVector
            (JNIEnv * env, jclass cls, jobject vec, jlong size) {
            GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, vec);
            GrB_Index vec_size = size;
            check_grb_error(GxB_Vector_resize(A, vec_size));
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_matrixApply
            (JNIEnv * env, jclass cls, jobject out_mat, jobject mask, jobject acc, jobject unary_op, jobject input_mat, jobject desc) {

            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, out_mat);
            GrB_Matrix first_mat = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, input_mat);
            GrB_UnaryOp op = (GrB_UnaryOp) (*env)->GetDirectBufferAddress(env, unary_op);

            GrB_BinaryOp a = acc != NULL ? (GrB_BinaryOp) (*env)->GetDirectBufferAddress(env, acc): NULL;
            GrB_Matrix m = mask != NULL ? (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mask): NULL;
            GrB_Descriptor d = desc != NULL ? (GrB_Descriptor) (*env)->GetDirectBufferAddress(env, desc): NULL;

            check_grb_error(GrB_Matrix_apply(A, m, a, op, first_mat, d));
            }

            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_vectorApply
            (JNIEnv * env, jclass cls, jobject out_vec, jobject mask, jobject acc, jobject unary_op, jobject input_vec, jobject desc) {

            GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, out_vec);
            GrB_Vector first_vec = (GrB_Vector) (*env)->GetDirectBufferAddress(env, input_vec);
            GrB_UnaryOp op = (GrB_UnaryOp) (*env)->GetDirectBufferAddress(env, unary_op);

            GrB_BinaryOp a = acc != NULL ? (GrB_BinaryOp) (*env)->GetDirectBufferAddress(env, acc): NULL;
            GrB_Vector m = mask != NULL ? (GrB_Vector) (*env)->GetDirectBufferAddress(env, mask): NULL;
            GrB_Descriptor d = desc != NULL ? (GrB_Descriptor) (*env)->GetDirectBufferAddress(env, desc): NULL;

            check_grb_error(GrB_Vector_apply(A, m, a, op, first_vec, d));
            }

JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_createSemiring
  (JNIEnv * env, jclass cls, jobject add, jobject mul) {
        GrB_Monoid monoid_add = (GrB_Monoid) (*env)->GetDirectBufferAddress(env, add);
        GrB_BinaryOp binop_mul = (GrB_BinaryOp) (*env)->GetDirectBufferAddress(env, mul);
        GrB_Semiring s;
        check_grb_error(GrB_Semiring_new(&s, monoid_add, binop_mul));
        return (*env)->NewDirectByteBuffer(env, s, 0);
  }

JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_freeSemiring
  (JNIEnv * env, jclass cls, jobject semi) {
        GrB_Semiring semiring = (GrB_Semiring) (*env)->GetDirectBufferAddress(env, semi);
        check_grb_error(GrB_Semiring_free(&semiring));
  }

JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_dupMatrix
  (JNIEnv * env, jclass cls, jobject mat) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        GrB_Matrix C;
        GrB_Matrix_dup(&C, A);
        return (*env)->NewDirectByteBuffer(env, C, 0);
  }

JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_dupVector
  (JNIEnv * env, jclass cls, jobject vec) {
        GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, vec);
        GrB_Vector C;
        check_grb_error(GrB_Vector_dup(&C, A));
        return (*env)->NewDirectByteBuffer(env, C, 0);
  }

JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_makeCSC
  (JNIEnv * env, jclass cls, jobject mat) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        check_grb_error(GxB_Matrix_Option_set(A, GxB_FORMAT, GxB_BY_COL));
  }

JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_makeCSR
  (JNIEnv * env, jclass cls, jobject mat) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        check_grb_error(GxB_Matrix_Option_set(A, GxB_FORMAT, GxB_BY_ROW));
  }

JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_setHyperRatio
  (JNIEnv * env, jclass cls, jobject mat, jdouble ratio) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        double r = ratio;
        check_grb_error(GxB_Matrix_Option_set(A, GxB_HYPER, r));
  }

JNIEXPORT jdouble JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_getHyperRatio
  (JNIEnv * env, jclass cls, jobject mat) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        double r = 0;
        check_grb_error(GxB_Matrix_Option_get(A, GxB_HYPER, &r));
        return r;
  }

JNIEXPORT jint JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_getFormat
  (JNIEnv * env, jclass cls, jobject mat) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        GxB_Format_Value r = -1;
        check_grb_error(GxB_Matrix_Option_get(A, GxB_FORMAT, &r));
        return r;
  }

JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_neverHyper
  (JNIEnv * env, jclass cls, jobject mat) {
        GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
        check_grb_error(GxB_Matrix_Option_set(A, GxB_FORMAT, GxB_NEVER_HYPER));
  }


JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_createDescriptor
  (JNIEnv * env, jclass cls) {
    GrB_Descriptor d;
    check_grb_error(GrB_Descriptor_new(&d));
    return (*env)->NewDirectByteBuffer(env, d, 0);
  }


JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_setDescriptorValue
  (JNIEnv * env, jclass cls, jobject desc, jint field, jint value){
        GrB_Descriptor d = (GrB_Descriptor) (*env)->GetDirectBufferAddress(env, desc);
        GrB_Desc_Field f = field;
        GrB_Desc_Value v = value;
        check_grb_error(GrB_Descriptor_set(d, f, v));
  }

JNIEXPORT jint JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_getDescriptorValue
  (JNIEnv * env, jclass cls, jobject desc, jint field) {
        GrB_Descriptor d = (GrB_Descriptor) (*env)->GetDirectBufferAddress(env, desc);
        GrB_Desc_Field f = field;
        GrB_Desc_Value v = -1;
        check_grb_error(GxB_Descriptor_get(&v, d, f));
        return v;
  }

JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRBCORE_freeDescriptor
  (JNIEnv * env, jclass cls, jobject desc) {
    GrB_Descriptor d = (GrB_Descriptor) (*env)->GetDirectBufferAddress(env, desc);
    check_grb_error(GrB_Descriptor_free(&d));
  }