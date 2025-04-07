/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "canvas.h"
#include <iostream>

Canvas::Canvas()
{
	// TODO constructor
	// Your code here
}

// Just delete the list, the individual layers are handled by main
Canvas::~Canvas()
{
	// TODO destructor
	// Your code here
}

// Add an layer at the end of the list
void Canvas::Add(size_t x, size_t y, const Vector2& pos, const Vector2& scale, const RGBAPixel& col, const std::string& name)
{
	// TODO instead of a single layer, have a list
	// Replace the code here
        layers.push_back(std::make_unique<PNGLayer>(x,y,pos,scale,col,name));
        layercount += 1;  
}

// Get the latest layer added to the canvas
// Return as pointer to allow editing or drawing on it
PNGLayer & Canvas::GetTopLayer(){
	// TODO instead of a single layer,
	// Return the latest/top layer from the list
	return *layers.back();
}

// Get a layer by its name
// Return by reference to allow editing or drawing on it
PNGLayer& Canvas::GetByName(const std::string& name) {
	// TODO instead of a single layer,
	// Return the layer with matching name
	// Report an error if it doesn't exist
	for (const auto& it:layers) {
		if (it -> getName() == name) {
			return *it;
		}
		//std::cout<< it -> getName() << "  " << name << std::endl;
	}

	//std::cout << name << std::endl;
	throw std::runtime_error("Requested layer wasn't found");
}

// Find and remove layer by name
// If layer is not found, do nothing
void Canvas::Remove(const std::string& name)
{
	// TODO instead of a single layer, should work for a list
	// This removes the frame for the logo in the collage
	// Your code here
	int idx = 0;
	for (const auto& it:layers) {
		if (it->getName() == name) {
			layers.erase(layers.begin() + idx);
			layercount--;
			break;
		}
		idx++;
	}
}

// Find given layers from list and swap their positions
// Swap only if both layers are found
void Canvas::Swap(const std::string& name1, const std::string& name2)
{
	// TODO needed for collage so the frames can be drawn before images
	// Your code here
	try {
		PNGLayer& layer1 = this->GetByName(name1);
		PNGLayer& layer2 = this->GetByName(name2);
		std::swap(layer1, layer2);
	} catch (const std::runtime_error& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
}

// Draws all layers in the list in order
// Blends the pixels colors of the layers with their layer color
// Draws the layers in their given position and scales them accordingly
// Blends drawn layers based on alpha channel (transparency)
void Canvas::draw(PNG& canvas) const
{
	
	for(size_t i=0; i<layercount; i++) {
		//update this line
		PNGLayer& layer = *layers[i];
		
		for(size_t x=0, xmax = layer.width(); x<xmax; x++){
			for(size_t y=0, ymax = layer.height(); y<ymax; y++){
				// This gets the pixel color blended with layer color
				// Check pnglayer.cpp
				RGBAPixel coli = layer.getBlendedPixel(x,y);
				Vector2 sc = layer.getScale();
				
				// TODO You should uncomment the below line and use in the section below
				Vector2 pos = layer.getPosition();
				
				// A loop is needed in case it must be scaled up, or we end up with gaps
				for(int xs=0; xs < std::abs((int)(sc.x()-0.001))+1; xs++){
					for(int ys=0; ys < std::abs((int)(sc.y()-0.001))+1; ys++){
						// Determine the position on the canvas based on 
						// layer position, scale, pixel position and adjacent pixel selection
						// TODO right now it just loops the pixels of the layer
						// x1, y1 should be coordinates of the canvas to draw to
						// So we should add layer position and adjacent pixel selection xs, ys
						// Multiply x and y by layer scale
						
						// Modify the two lines below
						int x1 = x * sc.x() + pos.x() + xs;
						int y1 = y * sc.y() + pos.y() + ys;
						
					  
						// Check that it's within bounds
						if(x1 >= 0 && x1 < (int)canvas.width() && y1 >= 0 && y1 < (int)canvas.height()) {
							// Current color of the canvas
							
							RGBAPixel& colc = canvas(x1,y1);
														
							// TODO Blend based on alpha.
							// Multiply layer color with alpha, canvas color with 255-alpha
							// Add them and divide by 255
							// In other words 255 = replace old pixel with new. 0 = don't draw.
							// 1-254 = partly new pixel, partly old
							
							// Modify the three lines below
							colc.red = (coli.red * coli.alpha + colc.red * (255 - coli.alpha)) / 255;
							colc.green = (coli.green * coli.alpha + colc.green * (255 - coli.alpha)) / 255;
							colc.blue = (coli.blue * coli.alpha + colc.blue * (255 - coli.alpha)) / 255;

							// We can keep the canvas opaque, no reason to change it
							colc.alpha = 255;
													
						}
					}
				}
			}
		}
	}
}
