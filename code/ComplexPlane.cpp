#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <sstream>
using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
	m_pixel_size = Vector2i(pixelWidth, pixelHeight);
	m_aspectRatio = ((float)pixelHeight / (float)pixelWidth);
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
	int pixelHeight = m_pixel_size.y;
	int pixelWidth = m_pixel_size.x;

	if (m_state == CALCULATING)
	{
		for (int i = 0; i < pixelHeight; i++)
		{
			for (int j = 0; j < pixelWidth; j++)
			{
				m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };

				Vector2f coord = mapPixelToCoords(Vector2i(j, i));
				int iterations = countIterations(coord);

				Uint8 r, g, b;
				iterationsToRGB(iterations, r, g, b);

				m_vArray[j + i * pixelWidth].color = { r,g,b };
			}
		}
	}
	m_state = DISPLAYING;
}

void ComplexPlane::zoomIn() {
	++m_zoomCount;

	std::cout << "zoom: " << m_zoomCount << std::endl;

	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x_size,y_size };
	m_state = CALCULATING;
}


void ComplexPlane::zoomOut() {
	--m_zoomCount;

	std::cout << "zoom: " << m_zoomCount << std::endl;

	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x_size,y_size };
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousPixel) {
	m_mouseLocation = mapPixelToCoords(mousPixel);
}

void ComplexPlane::loadText(Text& text) {
	stringstream ss;
	ss << "Mandelbrot set\n";
	ss << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")\n";
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")\n";
	ss << "Left-click to zoom in\n";
	ss << "Right-clock to zoom out\n";

	text.setString(ss.str());
}


size_t ComplexPlane::countIterations(Vector2f coord) {
	Vector2f z = coord;
	size_t iterations = 0;

	for (iterations; iterations < MAX_ITER; iterations++) {
		float xtemp = pow(z.x, 2.0) - pow(z.y,2.0) + coord.x;
		z.y = 2 * z.x * z.y + coord.y;
		z.x = xtemp;

		if (z.x > 2.0 || z.y > 2.0) {
			break;
		}
	}
	return iterations;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
	const size_t maxIterations = MAX_ITER;

	if (count == maxIterations) {
		r = g = b = 0;
	}
	else {
		const size_t regionSize = maxIterations / 5;
		size_t region = count / regionSize;

		double t = static_cast<double>(count % regionSize) / static_cast<double>(regionSize);

		// Purple/Blue to Turquoise
		if (region == 0) {
			r = 0;
			g = static_cast<Uint8>(t * 255);
			b = static_cast<Uint8>((1.0 - t) * 255);
		}
		// Turquoise to Green
		else if (region == 1) {
			r = 0;
			g = static_cast<Uint8>((1.0 - t) * 255);
			b = static_cast<Uint8>(t * 255);
		}
		// Green to Yellow
		else if (region == 2) {
			r = static_cast<Uint8>(t * 255);
			g = 255;
			b = 0;
		}
		// Yellow to Red
		else if (region == 3) {
			r = 255;
			g = static_cast<Uint8>((1.0 - t) * 255);
			b = 0;
		}
		// Red
		else {
			r = 255;
			g = 0;
			b = 0;
		}
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) { //??
	Vector2f newPixel;

	newPixel.x = ((mousePixel.x - 0) / (float)(m_pixel_size.x)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0);
	newPixel.y = ((m_pixel_size.y - mousePixel.y) / (float)(m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0);

	return newPixel;
}
