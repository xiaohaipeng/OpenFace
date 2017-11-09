///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Tadas Baltrusaitis all rights reserved.
//
// ACADEMIC OR NON-PROFIT ORGANIZATION NONCOMMERCIAL RESEARCH USE ONLY
//
// BY USING OR DOWNLOADING THE SOFTWARE, YOU ARE AGREEING TO THE TERMS OF THIS LICENSE AGREEMENT.  
// IF YOU DO NOT AGREE WITH THESE TERMS, YOU MAY NOT USE OR DOWNLOAD THE SOFTWARE.
//
// License can be found in OpenFace-license.txt
//
//     * Any publications arising from the use of this software, including but
//       not limited to academic journal and conference publications, technical
//       reports and manuals, must cite at least one of the following works:
//
//       OpenFace: an open source facial behavior analysis toolkit
//       Tadas Baltrušaitis, Peter Robinson, and Louis-Philippe Morency
//       in IEEE Winter Conference on Applications of Computer Vision, 2016  
//
//       Rendering of Eyes for Eye-Shape Registration and Gaze Estimation
//       Erroll Wood, Tadas Baltrušaitis, Xucong Zhang, Yusuke Sugano, Peter Robinson, and Andreas Bulling 
//       in IEEE International. Conference on Computer Vision (ICCV),  2015 
//
//       Cross-dataset learning and person-speci?c normalisation for automatic Action Unit detection
//       Tadas Baltrušaitis, Marwa Mahmoud, and Peter Robinson 
//       in Facial Expression Recognition and Analysis Challenge, 
//       IEEE International Conference on Automatic Face and Gesture Recognition, 2015 
//
//       Constrained Local Neural Fields for robust facial landmark detection in the wild.
//       Tadas Baltrušaitis, Peter Robinson, and Louis-Philippe Morency. 
//       in IEEE Int. Conference on Computer Vision Workshops, 300 Faces in-the-Wild Challenge, 2013.    
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SEQUENCE_CAPTURE_h_
#define __SEQUENCE_CAPTURE_h_

// System includes
#include <fstream>
#include <sstream>
#include <vector>

// OpenCV includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Utilities
{

	//===========================================================================
	/**
	A class for capturing sequences from video, webcam, and image directories
	*/
	class SequenceCapture {

	public:

		// Default constructor
		SequenceCapture() {};

		// TODO block copy, move etc.

		// Opening based on command line arguments
		bool Open(std::vector<std::string> arguments);

		// Direct opening

		// Webcam
		bool OpenWebcam(int device_id, int image_width = 640, int image_height = 480, float fx = -1, float fy = -1, float cx = -1, float cy = -1);

		// Image sequence in the directory
		bool OpenImageSequence(std::string directory, float fx = -1, float fy = -1, float cx = -1, float cy = -1);

		// Video file
		bool OpenVideoFile(std::string video_file, float fx = -1, float fy = -1, float cx = -1, float cy = -1);

		// Getting the next frame
		cv::Mat GetNextFrame();

		// Getting the most recent grayscale frame (need to call GetNextFrame first)
		cv::Mat_<uchar> GetGrayFrame();

		// Parameters describing the sequence and it's progress
		double GetProgress();

		bool IsOpened();

		int frame_width;
		int frame_height;

		float fx, fy, cx, cy;

		double fps;

		double time_stamp;

		// Name of the video file, image directory, or the webcam
		std::string name;

	private:

		// Used for capturing webcam and video
		cv::VideoCapture capture;

		// Storing the latest captures
		cv::Mat latest_frame;
		cv::Mat latest_gray_frame;


		// Keeping track if we are opening a video, webcam or image sequence
		bool is_webcam;
		bool is_image_seq;

		// Keeping track of frame number and the files in the image sequence
		int  frame_num;
		std::vector<std::string> image_files;

		// Length of video allowing to assess progress
		int vid_length;

		bool img_grabbed;

		// If using a webcam, helps to keep track of time
		int64 start_time;
	};
}
#endif