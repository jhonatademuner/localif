#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>
#include <cmath>
#include <cstdlib>

// Calculate the Euclidean distance between two integer arrays
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_example_localif_ImageRecovery_getEuclideanDistance(JNIEnv *env, jobject thiz,
                                                            jintArray vector1, jintArray vector2) {
    jint *vector1Data = (*env).GetIntArrayElements(vector1, nullptr);
    jint *vector2Data = (*env).GetIntArrayElements(vector2, nullptr);
    if (vector1Data == nullptr || vector2Data == nullptr) {
        return -1;
    }

    jint size = (*env).GetArrayLength(vector1);
    double sum = 0;
    for (int i = 0; i < size; i++) {
        int diff = vector1Data[i] - vector2Data[i];
        sum += diff * diff;
    }

    (*env).ReleaseIntArrayElements(vector1, vector1Data, JNI_ABORT);
    (*env).ReleaseIntArrayElements(vector2, vector2Data, JNI_ABORT);

    return sqrt(sum);
}

// Calculate the SMD (Squared Mean Difference) distance between two double arrays
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_example_localif_ImageRecovery_getSmdDistance(JNIEnv *env, jobject thiz,
                                                      jdoubleArray vector1, jdoubleArray vector2) {
    jdouble *vector1Data = env->GetDoubleArrayElements(vector1, nullptr);
    jdouble *vector2Data = env->GetDoubleArrayElements(vector2, nullptr);

    jint size = (*env).GetArrayLength(vector1);
    double distance = 0.0;
    for (int i = 0; i < size; i++) {
        double diff = vector1Data[i] - vector2Data[i];
        distance += diff * diff;
    }

    distance = std::sqrt(distance);

    env->ReleaseDoubleArrayElements(vector1, vector1Data, JNI_ABORT);
    env->ReleaseDoubleArrayElements(vector2, vector2Data, JNI_ABORT);

    return distance;
}

// Calculate the histogram vector from a matrix of integer values
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_localif_ImageRecovery_getHistogramVector(JNIEnv *env, jobject thiz,
                                                          jobjectArray matrix) {
    jint height = env->GetArrayLength(matrix);
    jintArray rowArray = static_cast<jintArray>(env->GetObjectArrayElement(matrix, 0));
    jint width = env->GetArrayLength(rowArray);

    // Allocate memory for the vector
    jintArray vector = env->NewIntArray(256);
    jint *vectorData = env->GetIntArrayElements(vector, nullptr);
    std::memset(vectorData, 0, 256 * sizeof(jint));

    // Extract the histogram
    for (jint i = 0; i < height; i++) {
        jintArray rowArray = static_cast<jintArray>(env->GetObjectArrayElement(matrix, i));
        jint *rowData = env->GetIntArrayElements(rowArray, NULL);
        for (jint j = 0; j < width; j++) {
            vectorData[rowData[j]]++;
        }
        env->ReleaseIntArrayElements(rowArray, rowData, JNI_ABORT);
        env->DeleteLocalRef(rowArray);
    }

    // Release the vector data
    env->ReleaseIntArrayElements(vector, vectorData, 0);

    return vector;
}

// Calculate the mean of a matrix
void calcMean(int **matrix, int width, int height, double *mean) {
    double meanX = 0.0, meanY = 0.0;
    double countX = 0.0, countY = 0.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            meanX += matrix[i][j];
            countX++;
        }
    }

    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            meanY += matrix[i][j];
            countY++;
        }
    }

    meanX /= countX;
    meanY /= countY;

    mean[0] = meanX;
    mean[1] = meanY;
}

// Calculate the standard deviation of a matrix
void calcStandardDeviation(int **matrix, int width, int height, double *standardDeviation,
                           double *mean) {
    double standardDeviationX = 0.0, standardDeviationY = 0.0;
    double countX = 0.0, countY = 0.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            standardDeviationX += pow(matrix[i][j] - mean[0], 2);
            countX++;
        }
    }

    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            standardDeviationY += pow(matrix[i][j] - mean[1], 2);
            countY++;
        }
    }

    standardDeviationX = sqrt(standardDeviationX / countX);
    standardDeviationY = sqrt(standardDeviationY / countY);

    standardDeviation[0] = standardDeviationX;
    standardDeviation[1] = standardDeviationY;
}

// Calculate the asymmetry of a matrix
void calcAssimetry(int **matrix, int width, int height, double *assimetry, double *mean,
                   double *standardDeviation) {
    double assimetryX = 0.0, assimetryY = 0.0;
    double countX = 0.0, countY = 0.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            assimetryX += pow(matrix[i][j] - mean[0], 3);
            countX++;
        }
    }

    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            assimetryY += pow(matrix[i][j] - mean[1], 3);
            countY++;
        }
    }

    assimetryX /= (countX * pow(standardDeviation[0], 3));
    assimetryY /= (countY * pow(standardDeviation[1], 3));

    assimetry[0] = assimetryX;
    assimetry[1] = assimetryY;
}

// Calculate the kurtosis of a matrix
void calcKurtosis(int **matrix, int width, int height, double *kurtosis, double *mean,
                  double *standardDeviation) {
    double kurtosisX = 0.0, kurtosisY = 0.0;
    double countX = 0.0, countY = 0.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            kurtosisX += pow(matrix[i][j] - mean[0], 4);
            countX++;
        }
    }

    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            kurtosisY += pow(matrix[i][j] - mean[1], 4);
            countY++;
        }
    }

    kurtosisX /= (countX * pow(standardDeviation[0], 4));
    kurtosisY /= (countY * pow(standardDeviation[1], 4));

    kurtosis[0] = kurtosisX;
    kurtosis[1] = kurtosisY;
}


extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_example_localif_ImageRecovery_getSmdVector(JNIEnv *env, jobject thiz,
                                                    jobjectArray matrix) {

    // Get the dimensions of the matrix
    jint height = env->GetArrayLength(matrix);
    jintArray rowArray = static_cast<jintArray>(env->GetObjectArrayElement(matrix, 0));
    jint width = env->GetArrayLength(rowArray);

    // Convert the matrix to a two-dimensional array
    int **nativeMatrix = new int *[height];
    for (int i = 0; i < height; i++) {
        jintArray rowArray = static_cast<jintArray>(env->GetObjectArrayElement(matrix, i));
        jint *rowElements = env->GetIntArrayElements(rowArray, 0);
        nativeMatrix[i] = new int[width];
        for (int j = 0; j < width; j++) {
            nativeMatrix[i][j] = rowElements[j];
        }
        env->ReleaseIntArrayElements(rowArray, rowElements, 0);
        env->DeleteLocalRef(rowArray);
    }

    // Allocate memory for the vectorSMD
    jdoubleArray vectorSMD = env->NewDoubleArray(6);
    jdouble *vectorSMDData = env->GetDoubleArrayElements(vectorSMD, NULL);
    std::memset(vectorSMDData, 0, 6 * sizeof(jdouble));

    // Calculate the mean
    double mean[2];
    calcMean(nativeMatrix, width, height, mean);

    // Calculate the standard deviation
    double standardDeviation[2];
    calcStandardDeviation(nativeMatrix, width, height, standardDeviation, mean);

    // Calculate the assimetry
    double assimetry[2];
    calcAssimetry(nativeMatrix, width, height, assimetry, mean, standardDeviation);

    // Calculate the kurtosis
    double kurtosis[2];
    calcKurtosis(nativeMatrix, width, height, kurtosis, mean, standardDeviation);

    // Store the moments in the descriptor
    vectorSMDData[0] = standardDeviation[0];
    vectorSMDData[1] = standardDeviation[1];
    vectorSMDData[2] = assimetry[0];
    vectorSMDData[3] = assimetry[1];
    vectorSMDData[4] = kurtosis[0];
    vectorSMDData[5] = kurtosis[1];

    // Release the vectorSMD data
    env->ReleaseDoubleArrayElements(vectorSMD, vectorSMDData, 0);

    // Delete the nativeMatrix
    for (int i = 0; i < height; i++) {
        delete[] nativeMatrix[i];
    }
    delete[] nativeMatrix;

    return vectorSMD;
}
