#include "findSquares.h"
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

static void showImage(Mat image, const std::string displayName)
{
    const auto window_name = displayName;
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    cv::imshow(window_name, image);
    cv::waitKey(1);
}

static void help(const char* programName)
{
    cout << "\nA program using pyramid scaling, Canny, contours and contour simplification\n"
            "to find squares in a list of images (pic1-6.png)\n"
            "Returns sequence of squares detected on the image.\n"
            "Call:\n"
            "./"
         << programName
         << " [file_name (optional)]\n"
            "Using OpenCV version "
         << CV_VERSION << "\n"
         << endl;
}
int thresh = 50, N = 11;
const char* wndname = "Square Detection Demo";
// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}
// returns sequence of squares detected on the image.
void findSquares(const Mat& image, vector<vector<Point> >& squares)
{
    squares.clear();
    Mat pyr, timg, gray0(image.size(), CV_8U), gray;
    // down-scale and upscale the image to filter out the noise
    showImage(image, "Before pyramid scaling");
    pyrDown(image, pyr, Size(image.cols / 2, image.rows / 2));
    pyrUp(pyr, timg, image.size());
    showImage(timg, "After Pyramid Scaling");

    Mat dst, cdst, sqdst, itcdst;
    int ch[] = {0, 0};
    mixChannels(&timg, 1, &gray0, 1, ch, 1);

    Canny(gray0, dst, 0, 75, 3);
    showImage(dst, "Canny");
    dilate(dst, dst, Mat(), Point(-1, -1));
    showImage(dst, "DilatedCanny");
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cvtColor(dst, sqdst, COLOR_GRAY2BGR);
    cvtColor(dst, itcdst, COLOR_GRAY2BGR);

    // Standard Hough Line Transform
    // vector<Vec2f> lines; // will hold the results of the detection
    // HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection
    //// Draw the lines
    // for (size_t i = 0; i < lines.size(); i++) {
    //    float rho = lines[i][0], theta = lines[i][1];
    //    Point pt1, pt2;
    //    double a = cos(theta), b = sin(theta);
    //    double x0 = a * rho, y0 = b * rho;
    //    pt1.x = cvRound(x0 + 1000 * (-b));
    //    pt1.y = cvRound(y0 + 1000 * (a));
    //    pt2.x = cvRound(x0 - 1000 * (-b));
    //    pt2.y = cvRound(y0 - 1000 * (a));
    //    line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    //}
    // showImage(cdst, "Detected Lines (in red) - Standard Hough Line Transform");

    vector<vector<Point> > contours;
    // find squares in every color plane of the image
    /*for (int c = 0; c < 3; c++) {
        int ch[] = {c, 0};
    */    /*mixChannels(&timg, 1, &gray0, 1, ch, 1);
        showImage(gray0, "Before canny");*/
    // try several threshold levels
    // for (int l = 0; l < N; l++) {
    // hack: use Canny instead of zero threshold level.
    // Canny helps to catch squares with gradient shading
    // if (l == 0) {
    //    // apply Canny. Take the upper threshold from slider
    //    // and set the lower to 0 (which forces edges merging)
    //    Canny(gray0, gray, 0, thresh, 5);
    //    // dilate canny output to remove potential
    //    // holes between edge segments
    //    dilate(gray, gray, Mat(), Point(-1, -1));
    //}
    // else {
    //    // apply threshold if l!=0:
    //    //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
    //    gray = gray0 >= (l + 1) * 255 / N;
    //}
    // showImage(gray, "Canny");
    // find contours and store them all as a list
    findContours(dst, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    polylines(cdst, contours, true, Scalar(0, 255, 0), 3, LINE_AA);
    showImage(cdst, "With contours");

    vector<Point> approx;
    // test each contour
    for (size_t i = 0; i < contours.size(); i++) {
        // approximate contour with accuracy proportional
        // to the contour perimeter
        /*polylines(itcdst, contours[i], true, Scalar(0, 255, 0), 3, LINE_AA);
        showImage(itcdst, "With iter contoures");*/
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);
        // square contours should have 4 vertices after approximation
        // relatively large area (to filter out noisy contours)
        // and be convex.
        // Note: absolute value of an area is used because
        // area may be positive or negative - in accordance with the
        // contour orientation
        if (approx.size() == 4 && fabs(contourArea(approx)) > 1000 && isContourConvex(approx)) {
            double maxCosine = 0;
            for (int j = 2; j < 5; j++) {
                // find the maximum cosine of the angle between joint edges
                double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
                maxCosine = MAX(maxCosine, cosine);
            }
            // if cosines of all angles are small
            // (all angles are ~90 degree) then write quandrange
            // vertices to resultant sequence
            if (maxCosine < 0.3) squares.push_back(approx);
        }
    }
    polylines(sqdst, squares, true, Scalar(0, 255, 0), 3, LINE_AA);
    showImage(sqdst, "With squares");

    //}
    //}
}
