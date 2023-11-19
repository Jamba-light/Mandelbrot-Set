#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = Vector2i(pixelWidth, pixelHeight);
	m_aspectRatio = ((float)pixelHeight / pixelWidth);
	m_plane_center = (Vector2f(0, 0));
	m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_zoomCount = 0;
	m_state = CALCULATING;
	m_vArray = VertexArray(Points, pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_vArray);
}

void ComplexPlane::updateRender() {
	if (m_state == CALCULATING)
	{
		for (int j = 0; j < pixelWidth; j++)
		{
			for (int i; i < pixelHeight; i++)
			{
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };

				Vector2f coord = mapPixelToCoords(j, i);
				int iterations = countIterations(coord);

				Uint8 r, g, b;
				iterationsToRGB(iterations, r, g, b);

				m_vArray[j + i * pixelWidth].color = { r,g,b };

				m_state = DISPLAYING;
			}
		}
	}
}

void ComplexPlane::zoomIn() {
	m_zoomCount++;

	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x_size,y_size };
	m_state = CALCULATING;
}


void ComplexPlane::zoomOut() {
	m_zoomCount--;

	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM, m_zoomCount);
	m_plane_size = { x_size,y_size };
	m_state = CALCULATING;

}


void ComplexPlane::setCenter(Vector2i mousePixel) {
	Vector2f center = mapPixelToCoords(mousePixel.x, mousePixel.y);
	m_plane_center = center;
	m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousPixel) {

}

void ComplexPlane::loadText(Text& text) {
	stringstream ss;
	ss << "Mandelbrot set\n";
	ss << "Center: (" << < m_plane_center.x << "," << m_plane_center.y")\n";
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y")\n";
	ss << "Left-click to zoom in\n";
	ss << "Right-clock to zoom out\n";

	text.setstring(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord) {

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
	Vector2f newPixel;

	newPixel.x = ((mousePixel.x - m_plane_center.x) / (m_pixel_size.x - m_plane_center.x)) * (2 - (-2)) + (m_plane_center.x - m_plane_size.x / 2.0);
	newPixel.y = ((mousePixel.y - m_pixel_size.y) / (m_plane_center.y - m_pixel_size.y)) * (2 - (-2)) + (m_plane_center.y - m_plane_size.y / 2.0);

	return newPixel;
}