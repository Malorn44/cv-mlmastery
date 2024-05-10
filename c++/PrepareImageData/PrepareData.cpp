#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv ) {
    if ( argc != 2 ) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    Mat image;
    image = imread( argv[1], IMREAD_COLOR );
    
    if ( !image.data ) {
        printf("No image data \n");
        return -1;
    }

    printf("=== Confirming Range ===\n");

    // rows, cols and channels
    printf("Rows: %d, Cols: %d, Channels: %d\n",image.rows, image.cols, image.channels());
    // min, max before normalizing
    double min, max;
    minMaxLoc(image, &min, &max);
    printf("Min: %.3f, Max: %.3f\n",min,max);
    
    // min, max after normalizing
    printf("=== Normalizing ===\n");
    
    image.convertTo(image, CV_32F, 1.0/255, 0);
    minMaxLoc(image, &min, &max);
    printf("Min: %.3f, Max: %.3f\n",min,max);

    // standardizing
    printf("=== Before Standardizing ===\n");

    Scalar mean, std;
    meanStdDev(image, mean, std);
    // * If we want to calculate mean and std dev across all channels
    // double mean_full = (mean[0] + mean[1] + mean[2]) / 3;
    // double std_full = (std[0] + std[1] + std[2]) / 3;
    for (int i = 0; i < image.channels(); i++) {
        printf("--- Channel %d ---\n", i+1);
        printf("Mean: %.3f, Std Dev: %.3f\n",mean[i],std[i]);
    }

    printf("=== After Standardizing ===\n");

    image = (image - mean) / std;
    meanStdDev(image, mean, std);
    for (int i = 0; i < image.channels(); i++) {
        printf("--- Channel %d ---\n", i+1);
        printf("Mean: %.3f, Std Dev: %.3f\n",mean[i],std[i]);
    }
    minMaxLoc(image, &min, &max);
    printf("Min: %.3f, Max: %.3f\n",min,max);

    return 0;
}