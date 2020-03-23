/*
 * =====================================================================================
 *
 *       Filename:  opencv_cam.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/22/19 23:28:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main()
{
	Mat img_color;

	//\ube44\ub514\uc624 \ucea1\uccd0 \ucd08\uae30\ud654
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "\uc5d0\ub7ec - \uce74\uba54\ub77c\ub97c \uc5f4 \uc218 \uc5c6\uc2b5\ub2c8\ub2e4.\n";
		return -1;
	}


	while(1)
	{
		// \uce74\uba54\ub77c\ub85c\ubd80\ud130 \ucea1\uccd0\ud55c \uc601\uc0c1\uc744 frame\uc5d0 \uc800\uc7a5\ud569\ub2c8\ub2e4.
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "\ube48 \uc601\uc0c1\uc774 \ucea1\uccd0\ub418\uc5c8\uc2b5\ub2c8\ub2e4.\n";
			break;
		}

		// \uc601\uc0c1\uc744 \ud654\uba74\uc5d0 \ubcf4\uc5ec\uc90d\ub2c8\ub2e4. 
		imshow("Color", img_color);

            // ESC \ud0a4\ub97c \uc785\ub825\ud558\uba74 \ub8e8\ud504\uac00 \uc885\ub8cc\ub429\ub2c8\ub2e4. 

		if (waitKey(25) >= 0)
			break;
	}
	

	return 0;
}


