#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

#define OriginalPhotoSplit 75     //一辺の画像枚数
#define WidthSize 4500             //構成画像の横ピクセル数

vector<int> OB, OG, OR;

//カンマ区切りで読み込む関数
vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int main()
{
    cv::Mat img; //画像格納変数
    cv::Mat img2; //画像格納変数

    //元画像を2025(=45 * 45)分割して，部分ごとに画素値の中央値を記述したファイルをopen
    ifstream ifs("../OriginalProcessing/OriginalResult.csv");

    //画素値読込
    string line;
    while (getline(ifs, line)) {

        vector<string> strvec = split(line, ',');
       
        OB.push_back(stoi(strvec.at(0)));
        OG.push_back(stoi(strvec.at(1)));
        OR.push_back(stoi(strvec.at(2)));
    }

    //画像読み込み
    img = cv::imread("../original/original.jpg", 1);
    img2 = cv::imread("../OutputImage/output.jpg", 1);

    double ResizeRate = (double)WidthSize / (double)img.size().width;
    cv::resize(img, img, cv::Size(), ResizeRate, ResizeRate);

    for(int y = 0; y < WidthSize / 3 * 2; y++){
        for(int x = 0; x < WidthSize; x++) {
            img2.at<cv::Vec3b>(y, x)[0] = 0.5 * (int)img2.at<cv::Vec3b>(y, x)[0] + 0.5 * (int)img.at<cv::Vec3b>(y, x)[0];
            img2.at<cv::Vec3b>(y, x)[1] = 0.5 * (int)img2.at<cv::Vec3b>(y, x)[1] + 0.5 * (int)img.at<cv::Vec3b>(y, x)[1];
            img2.at<cv::Vec3b>(y, x)[2] = 0.5 * (int)img2.at<cv::Vec3b>(y, x)[2] + 0.5 * (int)img.at<cv::Vec3b>(y, x)[2];
        }
    }
    //MosaicArtの書き込み
    cv::imwrite("../OutputImage/output2.jpg", img2);
    //MosaicArtの表示
    cv::imshow("PhotoMosaicArt",img2);
    cv::waitKey(0);
}