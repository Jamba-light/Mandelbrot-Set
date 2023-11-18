#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
	m_pixel_size = Vector2i(pixelWidth, pixelHeight);
	m_aspectRatio = ((float)pixelHeight / pixelWidth);
	m_plane_center = (Vector2f(0, 0));
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_zoomCount = 0;
	m_state = CALCULATING;
	m_vArray = VertexArray(Points, pixelWidth * pixelHeight);
}
/*
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {

}

void ComplexPlane::updateRender() {

}

void ComplexPlane::zoomIn() {

}

void ComplexPlane::zoomOut() {

}

void ComplexPlane::setCenter(Vector2i mousePixel) {

}

void ComplexPlane::setMouseLocation(Vector2i mousPixel) {

}

void ComplexPlane::loadText(Text& text) {

}

size_t ComplexPlane::countIterations(Vector2f coord) {

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {

}
/*