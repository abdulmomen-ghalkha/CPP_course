#include "RGBA/png.h"
#include "RGBA/rgbapixel.h"

#include <string>
#include <cmath>
#include <random>
#include <climits>

void rotate(const std::string & inputFile, const std::string & outputFile) {
	PNG pic(inputFile);
	// Your code here
	size_t width = pic.width();
	size_t height = pic.height();

	PNG rotatedPic(height, width);
	
	// Transpose the matrix 
	for (size_t i = 0; i < height; i++)
    {
      for (size_t j = 0; j < width; j++){
	      // Your code here
		  rotatedPic(i, j) =  pic(j, i);
      }
    }
	for (size_t j = 0; j < height; j++)
    {
      for (size_t i = 0; i < width / 2; i++){
	      // Your code here
		  std::swap(rotatedPic(j, i), rotatedPic(j, width - i - 1));
      }
    }
	

	rotatedPic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here
	std::random_device r;
	std::default_random_engine rng(r());
	std::uniform_int_distribution<int> uniform_dist(0, 255);
	

	for (size_t i = 0; i < height; i++)
    {
      for (size_t j = 0; j < width; j++){
	      // Your code here
		  uint8_t red = uniform_dist(rng);
		  uint8_t green = uniform_dist(rng);
		  uint8_t blue = uniform_dist(rng);
		  png(j, i).red =  red;
		  png(j, i).green = green;
		  png(j, i).blue = blue;
      }
    }

	return png;
}
