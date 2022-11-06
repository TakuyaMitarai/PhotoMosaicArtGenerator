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

#define WidthSize 120             //構成画像の横ピクセル数
#define OriginalPhotoSplit 75     //一辺の画像枚数
#define ArtPhotoNum     OriginalPhotoSplit * OriginalPhotoSplit      //モザイクアートの構成写真枚数

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
    string FolderName = "../material/R";    //ファイルパス共通部分
    string FN;    //ファイルパス

    //素材画像の並べ方を記述したファイルをopen
    ifstream ifs("../SE/Result.csv");

    int cnt;
    vector<int> s;
    vector<string> strvec;
    string line;
    while (getline(ifs, line)) {

        strvec = split(line, ',');
       
    }

    //読込
    for(int i = 0; i < ArtPhotoNum; i++) {
        s.push_back(stoi(strvec.at(i)));
        cout << i << " " << s[i] << endl;
    }
    cv::Mat img;
    cv::Mat x;
    cv::Mat y;
    int d = 1;
    int e = 1;
    int num;
    cnt = 0;

    for(int ys = 0; ys < OriginalPhotoSplit; ys++) {
        for(int xs = 0; xs < OriginalPhotoSplit; xs++) {
            if(d == 1) {
                /*
                s[cnt]++;
                for(int i = 0; i < 8; i++) {
                    if(s[cnt] > 4800 * i && s[cnt] <= 4800 * (i + 1)) {
                        num = s[cnt] - 4800 * i;
                        num--;
                        num /= 4;
                        num++;
                        cout << cnt << " " << num << " " << s[cnt] << endl;
                    }
                }
                */
                /*
                num = s[cnt] / 4 + 1;
                cout << cnt << " " << num << " " << s[cnt] << endl;
                */
                num = s[cnt] + 1;
                cout << cnt << " " << num << endl;

                //素材画像の読込
                if(num < 10) {
                    FN = FolderName + "0000" + to_string(num) + ".png";
                    x = cv::imread(FN, 0);
                } else if(num < 100) {
                    FN = FolderName + "000" + to_string(num) + ".png";
                    x = cv::imread(FN, 1);
                } else if(num  < 1000) {
                    FN = FolderName + "00" + to_string(num) + ".png";
                    x = cv::imread(FN, 1);
                } else if(num < 10000){
                    FN = FolderName + "0" + to_string(num) + ".png";
                    x = cv::imread(FN, 1);
                } else {
                    FN = FolderName + to_string(num) + ".png";
                    x = cv::imread(FN, 1);
                }
                //画像サイズを小さくする(120 × 80)
                double ResizeRate = (double)WidthSize / (double)x.size().width;
                cv::resize(x, x, cv::Size(), ResizeRate, ResizeRate);

                //画像を3 : 2に調整
                x = cv::Mat(x, cv::Rect(0, 0, 60, 40)).clone();
                d = 0;
                cnt++;
            }else {
                /*
                s[cnt]++;
                for(int i = 0; i < 8; i++) {
                    if(s[cnt] > 4800 * i && s[cnt] <= 4800 * (i + 1)) {
                        num = s[cnt] - 4800 * i;
                        num--;
                        num /= 4;
                        num++;
                        cout << cnt << " " << num << " " << s[cnt] << endl;
                    }
                }
                */
                /*
                num = s[cnt] / 4 + 1;
                cout << cnt << " " << num << " " << s[cnt] << endl;
                */
                num = s[cnt] + 1;
                cout << cnt << " " << num << endl;

                //素材画像の読込
                if(num  < 10) {
                    FN = FolderName + "0000" + to_string(num) + ".png";
                    y = cv::imread(FN, 1);
                } else if(num < 100) {
                    FN = FolderName + "000" + to_string(num) + ".png";
                    y = cv::imread(FN, 1);
                } else if(num < 1000) {
                    FN = FolderName + "00" + to_string(num) + ".png";
                    y = cv::imread(FN, 1);
                } else if(num < 10000){
                    FN = FolderName + "0" + to_string(num) + ".png";
                    y = cv::imread(FN, 1);
                } else {
                    FN = FolderName + to_string(num) + ".png";
                    y = cv::imread(FN, 1);
                }

                //画像サイズを小さくする(120 × 80)
                double ResizeRate = (double)WidthSize / (double)y.size().width;
                cv::resize(y, y, cv::Size(), ResizeRate, ResizeRate);

                //画像を3 : 2に調整
                y = cv::Mat(y, cv::Rect(0, 0, 60, 40)).clone();

                //画像を一枚ずつ横に合成
                cv::hconcat(x, y, x);
                cnt++;
            }
        }
        if(e == 1) {
            img = x;
            e = 0;
        } else {
            //一行全て並べられた画像を縦に合成
            vconcat(img, x, img);
        }
        d = 1;
    }
    //MosaicArtの書き込み
    cv::imwrite("../OutputImage/output.jpg", img);
    //MosaicArtの表示
    cv::imshow("PhotoMosaicArt",img);
    cv::waitKey(0);
}