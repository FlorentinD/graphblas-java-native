#include "com_github_fabianmurariu_unsafe_GRAPHBLAS.h"
#include "com_github_fabianmurariu_unsafe_GRBMONOID.h"
#include <stdlib.h>
#include <jni.h>
#include "GraphBLAS.h"
#include <assert.h>
long check_grb_error(GrB_Info info);


            // generic functions
            <#list properties.types as prop>

            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_${prop.java_type}Type
            (JNIEnv * env, jclass cls) {
            return (*env)->NewDirectByteBuffer(env, GrB_${prop.grb_type}, 0);
            }

            </#list>

            <#list properties.types as prop>
            JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_setMatrixElement${prop.java_type?cap_first}
            (JNIEnv * env, jclass cls, jobject mat, jlong i, jlong j, j${prop.java_type} value) {
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
                GrB_Index I = i;
                GrB_Index J = j;
            check_grb_error( GrB_Matrix_setElement_${prop.grb_type}(A, value, I, J) ) ;
            }


            JNIEXPORT j${prop.java_type}Array JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_getMatrixElement${prop.java_type?cap_first}
            (JNIEnv * env, jclass cls, jobject mat, jlong i, jlong j) {
            ${prop.c_type} x;
            GrB_Matrix A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
                GrB_Index I = i;
                GrB_Index J = j;
            GrB_Info info = GrB_Matrix_extractElement_${prop.grb_type}(&x, A, I, J);
            j${prop.java_type}Array output;
            if (info == GrB_NO_VALUE) {
            output = (*env)->New${prop.java_type?cap_first}Array(env, 0);
            } else {
            output = (*env)->New${prop.java_type?cap_first}Array(env, 1);
            ${prop.c_type} xs[] = {x};
            (*env)->Set${prop.java_type?cap_first}ArrayRegion(env, output, 0, 1, xs);
            }
            return output;
            }

            </#list>

            <#list properties.types as prop>
                JNIEXPORT void JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_setVectorElement${prop.java_type?cap_first}
                (JNIEnv * env, jclass cls, jobject mat, jlong i, j${prop.java_type} value) {
                GrB_Vector A = (GrB_Matrix) (*env)->GetDirectBufferAddress(env, mat);
                GrB_Index I = i;
                check_grb_error( GrB_Vector_setElement_${prop.grb_type}(A, value, I) ) ;
                }


                JNIEXPORT j${prop.java_type}Array JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_getVectorElement${prop.java_type?cap_first}
                (JNIEnv * env, jclass cls, jobject mat, jlong i) {
                ${prop.c_type} x;
                GrB_Vector A = (GrB_Vector) (*env)->GetDirectBufferAddress(env, mat);
                GrB_Index I = i;
                GrB_Info info = GrB_Vector_extractElement_${prop.grb_type}(&x, A, I);
                j${prop.java_type}Array output;
                if (info == GrB_NO_VALUE) {
                output = (*env)->New${prop.java_type?cap_first}Array(env, 0);
                } else {
                output = (*env)->New${prop.java_type?cap_first}Array(env, 1);
                ${prop.c_type} xs[] = {x};
                (*env)->Set${prop.java_type?cap_first}ArrayRegion(env, output, 0, 1, xs);
                }
                return output;
                }

            </#list>

    <#list properties.types as prop>
        <#list properties.unary_ops as uop>
            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_${uop.name}UnaryOp${prop.java_type?cap_first}
            (JNIEnv * env, jclass cls) {
            return (*env)->NewDirectByteBuffer(env, ${uop.grb_name}_${prop.grb_type}, 0);
            }
        </#list>
    </#list>

    <#list properties.types as prop>
        <#list properties.binary_ops as op>
            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_${op.name}BinaryOp${prop.java_type?cap_first}
            (JNIEnv * env, jclass cls){
            return (*env)->NewDirectByteBuffer(env, ${op.grb_name}_${prop.grb_type}, 0);
            }
        </#list>
    </#list>

    <#list properties.types as prop>
        <#list properties.binary_ops_bool as op>
            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_${op.name}BinaryOp${prop.java_type?cap_first}
            (JNIEnv * env, jclass cls){
            return (*env)->NewDirectByteBuffer(env, ${op.grb_name}_${prop.grb_type}, 0);
            }
        </#list>
    </#list>

    <#list properties.binary_ops_bool_bool as op>
        JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRAPHBLAS_${op.name}BinaryOp
        (JNIEnv * env, jclass cls){
        return (*env)->NewDirectByteBuffer(env, ${op.grb_name}, 0);
        }
    </#list>

    <#list properties.types as prop>

JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBMONOID_createMonoid${prop.java_type?cap_first}
  (JNIEnv * env, jclass cls, jobject bin_op, j${prop.java_type} identity) {
        GrB_BinaryOp op = (GrB_BinaryOp) (*env)->GetDirectBufferAddress(env, bin_op);
        GrB_Monoid m;
        ${prop.c_type} id = identity;
        GrB_Info status = GrB_Monoid_new(&m, op, id);
        check_grb_error(status);
        return (*env)->NewDirectByteBuffer(env, m, 0);
  }

    <#if prop.java_type != "boolean" >
        <#list properties.monoids as op>
            JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBMONOID_${op.name}Monoid${prop.java_type?cap_first}
            (JNIEnv * env, jclass cls){
                return (*env)->NewDirectByteBuffer(env, ${op.grb_name}_${prop.grb_type}_MONOID, 0);
            }
        </#list>
    </#if>
    </#list>

    <#list properties.monoids_bool as op>
        JNIEXPORT jobject JNICALL Java_com_github_fabianmurariu_unsafe_GRBMONOID_${op.name}Monoid
        (JNIEnv * env, jclass cls){
            return (*env)->NewDirectByteBuffer(env, ${op.grb_name}_BOOL_MONOID, 0);
        }
    </#list>
